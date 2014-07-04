/**
 * File: $Id:$
 *
 *  This file implements the msgbuf message unpacking feature.
 *
 *  Copyright (c) 2012 Nagravision. All rights reserved.
 *  CH-1033 Cheseaux, Switzerland
 *  Tel: +41 21 7320311  Fax: +41 21 7320100
 *  http://www.nagra.com
 *
 *  All trademarks and registered trademarks are the property of their respective
 *  owners.
 *
 *  This document is supplied with an understanding that the notice(s) herein or
 *  any other contractual agreement(s) made that instigated the delivery of a
 *  hard copy, electronic copy, facsimile or file transfer of this document are
 *  strictly observed and maintained.
 *
 *  The information contained in this document is subject to change without notice.
 *
 *  Security Policy of Nagravision Kudelski Group
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 **/


/****************************************************************************/
/* INCLUDE                                                                  */
/****************************************************************************/

#include "inc/xsd-c.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "src/msgbuf_unpack.h"
#include "inc/app_msgbuf_report.h"
#include <stddef.h>

/****************************************************************************/
/* Static functions declaration                                             */
/****************************************************************************/


/* Function : msgbuf_unpack_uint32
 *
 * Unpack an unsigned 32-bit VARINT encoded integer.
 * Return the number of VARING encoded byte size in the input
 * data buffer (5 bytes or less)
 * In case of error, return -1;
 */
static int msgbuf_unpack_uint32 (
  uint32_t      * pxValue,
  uint8_t const * pxIn,
  int             xInitShift,
  uint8_t const * pxEnd );


/*
 * Unpack an unsigned 64-bit VARINT encoded integer.
 * Return the number of encoded byte size within the input
 * data buffer (10 bytes or less)
 */
static int msgbuf_unpack_uint64 (
  uint64_t      * pxValue,
  const uint8_t * pxIn,
  int             xInitShift,
  const uint8_t * pxEnd );


/* wire-type will be added in required_field_pack() */
/* XXX: just call uint64_pack on 64-bit platforms. */
static int msgbuf_unpack_tag_and_wire (
  uint32_t           * pxTag,
  TMsgBuf_wireType  * pxWire,
  uint8_t const      * pxIn,
  uint8_t const      * pxEnd );


/* Given a raw slab of packed-repeated values,
 * determine the number of elements.
 * This function detects certain kinds of errors
 * but not others; the remaining error checking is done by
 * parse_packed_repeated_member()
 */
static int msgbuf_count_packed_repeated_elements (
  TMsgBuf_wireType  xWireType,
  uint8_t const   * pxIn,
  uint8_t const   * pxEnd,
  int             * pxCount );


/* Given a raw slab of packed-repeated values,
 * determine the number of elements.
 * This function detects certain kinds of errors
 * but not others; the remaining error checking is done by
 * parse_packed_repeated_member()
 */
static int msgbuf_count_repeated_elements (
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  uint8_t const                 * pxIn,
  uint8_t const                 * pxEnd,
  int                        * pxCount );

/* Given a raw slab of packed-repeated values,
   determine the number of elements.
   This function detects certain kinds of errors
   but not others; the remaining error checking is done by
   parse_packed_repeated_member() */
static int msgbuf_unpack_field (
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  void                           * pxFieldAdr,
  uint8_t                          xWire,
  uint8_t const                  * pxIn,
  uint8_t const                  * pxEnd );


/****************************************************************************/
/* Private Macro definition                                                 */
/****************************************************************************/


/* Get the pointer to the field of a structure based on its
 * byte offset. */
#define MSGBUF_GET_MEMBER_P(_pStruct,_fieldOffset)      \
  ((void *)((uint8_t*)(_pStruct)+(_fieldOffset)))


#define MSGBUF_UNPACK_SINT32(_value,_pIn,_pEnd,_len)   \
{                                                      \
  uint32_t _tmpValue;                                  \
                                                       \
  (_len) = msgbuf_unpack_uint32 (                      \
    &_tmpValue, (_pIn), 0, (_pEnd));                   \
  if ((_len) > 0)                                      \
  {                                                    \
    if (_tmpValue & 1)                                 \
      (_value) = -(int32_t)(_tmpValue >> 1) - 1;       \
    else (_value) = (int32_t)(_tmpValue >> 1);         \
  }                                                    \
}


#define MSBUG_UNPACK_SINT64(_value,_pIn,_pEnd,_len)   \
{                                                     \
  uint64_t _tmpValue;                                 \
  (_len) = msgbuf_unpack_uint64 (                     \
    &_tmpValue, (_pIn), 0, (_pEnd));                  \
  if ((_len) > 0)                                     \
  {                                                   \
    if (_tmpValue & 1)                                \
      (_value) = -(int64_t)((_tmpValue) >> 1) - 1;    \
    else (_value) = (int64_t)(_tmpValue >> 1);        \
  }                                                   \
}


/* Pack a 32-bit value, little-endian.
   Used for fixed32, sfixed32, float) */
#define MSGBUF_UNPACK_FIXED32(_value,_pIn,_pEnd,_len) \
{                                                     \
  uint32_t _tmpValue = 0;                             \
  uint8_t const * _pCur = (uint8_t const*)(_pIn);     \
                                                      \
  if (((_pCur) + 4) > (_pEnd)) (_len) = -1;           \
  else                                                \
  {                                                   \
    (_len) = 4;                                       \
    _tmpValue |= (uint32_t)_pCur[3] << 24;            \
    _tmpValue |= (uint32_t)_pCur[2] << 16;            \
    _tmpValue |= (uint32_t)_pCur[1] <<  8;            \
    _tmpValue |= (uint32_t)_pCur[0] <<  0;            \
    (_value) = _tmpValue;                             \
  }                                                   \
}


/* Pack a 32-bit value, little-endian.
   Used for fixed32, sfixed32, float) */
#define MSGBUF_UNPACK_FIXED64(_value,_pIn,_pEnd,_len) \
{                                                     \
  uint64_t _tmpValue = 0;                             \
  uint8_t const * _pCur = (const uint8_t*)(_pIn);     \
                                                      \
  if ((_pCur + 8) > (_pEnd)) (_len) = -1;             \
  else                                                \
  {                                                   \
    (_len) = 8;                                       \
    _tmpValue |= (uint64_t)_pCur[7] << 56;            \
    _tmpValue |= (uint64_t)_pCur[6] << 48;            \
    _tmpValue |= (uint64_t)_pCur[5] << 40;            \
    _tmpValue |= (uint64_t)_pCur[4] << 32;            \
    _tmpValue |= (uint64_t)_pCur[3] << 24;            \
    _tmpValue |= (uint64_t)_pCur[2] << 16;            \
    _tmpValue |= (uint64_t)_pCur[1] <<  8;            \
    _tmpValue |= (uint64_t)_pCur[0] <<  0;            \
    (_value) = _tmpValue;                             \
  }                                                   \
}


/* Pack a boolean as 0 or 1, even though the protobuf_c_boolean
   can really assume any integer value. */
/* XXX: perhaps on some platforms "*out = !!value" would be
   a better impl, b/c that is idiotmatic c++ in some stl impls. */
#define MSGBUF_UNPACK_BOOLEAN(_value,_pIn,_pEnd,_len) \
{                                                     \
  if ((_pIn) >= (_pEnd)) (_len) = -1;                 \
  else                                                \
  {                                                   \
    (_value) = ((_pIn)[0]) ? 1 : 0;                   \
    (_len) = 1;                                       \
  }                                                   \
}


/****************************************************************************/
/* Static functions implementation                                          */
/****************************************************************************/


/* Function : msgbuf_unpack_uint32
 *
 * Unpack an unsigned 32-bit VARINT encoded integer.
 * Return the number of VARING encoded byte size in the input
 * data buffer (5 bytes or less)
 * In case of error, return -1;
 */
static int msgbuf_unpack_uint32
(
  uint32_t      * pxValue,
  uint8_t const * pxIn,
  int             xInitShift,
  uint8_t const * pxEnd
)
{
  uint8_t         byte;
  uint32_t        tmpValue = 0;
  uint8_t const * pCur = pxIn;

  /* Limit the number of VARINT encoded max size to 5 bytes
   * in any case */
  if (pxIn + 5 < pxEnd) pxEnd = pxIn + 5;

  /* Extract the uint32 value from input data buffer */
  while (pCur < pxEnd)
  {
    byte = *pCur++;
    tmpValue |= ((uint32_t)(byte & 0x7F)) << xInitShift;
    /* if ((uint32_t)byte >> (32 - xInitShift)) return -1; */
    if (!(byte & 0x80))
    {
      *pxValue = tmpValue;
      return ((int)pCur - (int)pxIn);
    }
    xInitShift += 7;
  };

  APP_MSGBUF_report_error ("Bad message packing format");
  return -1;
}


/*
 * Unpack an unsigned 64-bit VARINT encoded integer.
 * Return the number of encoded byte size within the input
 * data buffer (10 bytes or less)
 */
static int msgbuf_unpack_uint64
(
  uint64_t      * pxValue,
  const uint8_t * pxIn,
  int             xInitShift,
  const uint8_t * pxEnd
)
{
  uint8_t         byte;
  uint64_t        tmpValue = 0;
  const uint8_t * pCur = pxIn;

  if (pxIn + 10 < pxEnd) pxEnd = pxIn + 10;

  while (pCur < pxEnd)
  {
    byte = *pCur++;
    tmpValue |= ((uint64_t)(byte & 0x7F)) << xInitShift;
    /* if (byte >> (64 - xInitShift)) return -1; */
    if (!(byte & 0x80))
    {
      *pxValue = tmpValue;
      return ((int)pCur - (int)pxIn);
    }
    xInitShift += 7;
  };

  APP_MSGBUF_report_error ("Bad message packing format");
  return -1;
}


/* wire-type will be added in required_field_pack() */
/* XXX: just call uint64_pack on 64-bit platforms. */
static int msgbuf_unpack_tag_and_wire
(
  uint32_t           * pxTag,
  TMsgBuf_wireType   * pxWire,
  uint8_t const      * pxIn,
  uint8_t const      * pxEnd
)
{
  int   len = 0;
  uint8_t  firstByte;

  if (pxIn >= pxEnd)
  {
    APP_MSGBUF_report_error ("Bad message packing format");
    return -1;
  }

  firstByte = *pxIn++;
  *pxWire = (TMsgBuf_wireType)(firstByte & 0x07);

  if (firstByte & 0x80)
  {
    len = msgbuf_unpack_uint32 (pxTag, pxIn, 4, pxEnd);
    if (len < 1) return -1;

    *pxTag |= (uint32_t)((firstByte >> 3) & 0x0F);
  }
  else *pxTag = (uint32_t)(firstByte >> 3);

  return (len + 1);
}


static int msgbuf_count_repeated_elements
(
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  uint8_t const                 * pxIn,
  uint8_t const                 * pxEnd,
  int                           * pxCount
)
{
  int                  len = 0;
  int                  curLen;
  uint32_t             fieldLen;
  uint32_t             tag;
  TMsgBuf_wireType     wire_type;

  *pxCount = 0;

  for (;;)
  {
    if (pxIn == pxEnd) return len;

    /* Get the tag and wire value of the current field in the data stream */
    curLen = msgbuf_unpack_tag_and_wire (&tag, &wire_type, pxIn, pxEnd);
    if (curLen < 0) return -1;

    if (tag != pxFieldDesc->id) return len;
    pxIn += curLen; len += curLen;

    if (pxIn > pxEnd)
    {
      APP_MSGBUF_report_error ("Bad message packing format");
      return -1;
    }

    switch (wire_type)
    {
      case MSGBUF_WIRE_TYPE_VARINT:
        while ((*pxIn++ & 0x80))
        {
          len++;
          if (pxIn >= pxEnd)
          {
            APP_MSGBUF_report_error ("Bad message packing format");
            return -1;
          }
        }
        *pxCount += 1;
        break;

      case MSGBUF_WIRE_TYPE_64BIT:
        pxIn += 8;
        if (pxIn > pxEnd)
        {
          APP_MSGBUF_report_error ("Bad message packing format");
          return -1;
        }
        len += 8;
        *pxCount += 1;
        break;

      case MSGBUF_WIRE_TYPE_LENGTH_PREFIXED:
        curLen = msgbuf_unpack_uint32 (
          &fieldLen,
          pxIn,
          0,
          pxEnd);
        if (curLen < 0) return -1;
        pxIn += curLen; len += curLen;
        if (pxIn + fieldLen > pxEnd)
        {
          APP_MSGBUF_report_error ("Bad message packing format");
          return -1;
        }
        pxIn+= fieldLen; len += fieldLen;
        *pxCount += 1;
        break;

      case MSGBUF_WIRE_TYPE_32BIT:
        pxIn += 4;
        if (pxIn > pxEnd)
        {
          APP_MSGBUF_report_error ("Bad message packing format");
          return -1;
        }
        len += 4;
        *pxCount += 1;
        break;

      default:
        APP_MSGBUF_report_error ("Unknown message field type identifier");
        return -1;
    }
  }
}


/* Given a raw slab of packed-repeated values,
   determine the number of elements.
   This function detects certain kinds of errors
   but not others; the remaining error checking is done by
   parse_packed_repeated_member() */
static int msgbuf_count_packed_repeated_elements
(
  TMsgBuf_wireType  xWireType,
  uint8_t const   * pxIn,
  uint8_t const   * pxEnd,
  int          * pxCount
)
{
  int curCount = 0;
  int len = (int)pxEnd - (int)pxIn;

  switch (xWireType)
  {
    case MSGBUF_WIRE_TYPE_VARINT:
      while (pxIn < pxEnd)
      {
        if ((*pxIn++ & 0x80) == 0)
          ++curCount;
      }

      if (!(*(pxIn - 1) & 0x80))
      {
        APP_MSGBUF_report_error ("Bad message packing format");
        return -1;
      }
      break;

    case MSGBUF_WIRE_TYPE_32BIT:

      if (len % 4 != 0)
      {
        APP_MSGBUF_report_error ("Bad message packing format");
        return -1;
      }
      curCount = len / 4;
      break;

    case MSGBUF_WIRE_TYPE_64BIT:

      if (len % 8 != 0)
      {
        APP_MSGBUF_report_error ("Bad message packing format");
        return -1;
      }
      curCount = len / 8;
      break;

    case MSGBUF_WIRE_TYPE_LENGTH_PREFIXED:
      while (pxIn < pxEnd)
      {
        uint32_t        fieldLen;
        int          prefixLen;

        while (pxIn < pxEnd)
        {
          prefixLen = msgbuf_unpack_uint32 (
            &fieldLen,
            pxIn,
            0,
            pxEnd);

          if (prefixLen < 1) return -1;
          pxIn += fieldLen + prefixLen;
          if (pxIn > pxEnd)
          {
            APP_MSGBUF_report_error ("Bad message packing format");
            return -1;
          }

          curCount++;
        }
        break;
      }

    default:
      APP_MSGBUF_report_error ("Unknown message field type identifier");
      return -1;
  }

  *pxCount = curCount;
  return len;
}


/* Given a raw slab of packed-repeated values,
   determine the number of elements.
   This function detects certain kinds of errors
   but not others; the remaining error checking is done by
   parse_packed_repeated_member() */
static int msgbuf_unpack_field
(
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  void                          * pxFieldAdr,
  uint8_t                         xWire,
  uint8_t const                 * pxIn,
  uint8_t const                 * pxEnd
)
{
  int   len;

  switch (pxFieldDesc->type)
  {
    case MSGBUF_FIELDTYPE_INT32:
    case MSGBUF_FIELDTYPE_SINT32:
      {
        int32_t * pField = (int32_t*)pxFieldAdr;
        MSGBUF_UNPACK_SINT32(*pField, pxIn, pxEnd, len);
      }
      break;

    case MSGBUF_FIELDTYPE_ENUM:
    case MSGBUF_FIELDTYPE_UINT32:
      {
        uint32_t * pField = (uint32_t*)pxFieldAdr;
        len = msgbuf_unpack_uint32 (pField, pxIn, 0, pxEnd );
      }
      break;

    case MSGBUF_FIELDTYPE_SFIXED32:
    case MSGBUF_FIELDTYPE_FIXED32:
    case MSGBUF_FIELDTYPE_FLOAT:
      {
        uint32_t * pField = (uint32_t*)pxFieldAdr;
        MSGBUF_UNPACK_FIXED32(*pField, pxIn, pxEnd, len);
      }
      break;

    case MSGBUF_FIELDTYPE_INT64:
    case MSGBUF_FIELDTYPE_SINT64:
      {
        int64_t * pField = (int64_t*)pxFieldAdr;
        MSBUG_UNPACK_SINT64(*pField, pxIn, pxEnd, len);
      }
      break;

    case MSGBUF_FIELDTYPE_UINT64:
      {
        uint64_t * pField = (uint64_t*)pxFieldAdr;
        len = msgbuf_unpack_uint64 (pField, pxIn, 0, pxEnd );
      }
      break;

    case MSGBUF_FIELDTYPE_SFIXED64:
    case MSGBUF_FIELDTYPE_FIXED64:
    case MSGBUF_FIELDTYPE_DOUBLE:
      {
        uint64_t * pField = (uint64_t*)pxFieldAdr;
        MSGBUF_UNPACK_FIXED64( *pField, pxIn, pxEnd, len);
      }
      break;

    case MSGBUF_FIELDTYPE_BOOL:
      {
        TMsgBuf_bool * pField = (TMsgBuf_bool*)pxFieldAdr;
        MSGBUF_UNPACK_BOOLEAN (*pField, pxIn,pxEnd,len);
      }
      break;

    case MSGBUF_FIELDTYPE_BYTES:
      {
        TMsgBuf_bytes * pField = (TMsgBuf_bytes*)pxFieldAdr;
        uint32_t     bytesSize;
        len = msgbuf_unpack_uint32 (&bytesSize, pxIn, 0, pxEnd);

        if (len > 0)
        {
          pxIn += len;
          if (pxIn + bytesSize > pxEnd)
          {
            APP_MSGBUF_report_error ("Bad message packing format");
            len = -1;
          }
          else
          {
            /* If this field was not already provided, create it */
            /* Otherwise, drop the current packed field */
            if (pField->pData == NULL)
            {
              pField->pData = (uint8_t*)MSGBUF_SYS_malloc(bytesSize);
              MSGBUF_SYS_memcpy (pField->pData, pxIn, bytesSize);
              pField->len = bytesSize;
            }
            pxIn += bytesSize;
            len += bytesSize;
          }
        }
      }
      break;

    case MSGBUF_FIELDTYPE_STRING:
      {
        char ** pField = (char**)pxFieldAdr;
        uint32_t     bytesSize;
        len = msgbuf_unpack_uint32 (&bytesSize, pxIn, 0, pxEnd);

        if (len > 0)
        {
          pxIn += len;
          if (pxIn + bytesSize > pxEnd)
          {
            APP_MSGBUF_report_error ("Bad message packing format");
            len = -1;
          }
          else
          {
            if (*pField == NULL)
            {
              *pField = (char*)MSGBUF_SYS_malloc(bytesSize + 1);
              MSGBUF_SYS_memcpy (*pField, pxIn, bytesSize);
              (*pField)[bytesSize] = 0;
            }
            pxIn += len;
            len += bytesSize;
          }
        }
      }
      break;

    case MSGBUF_FIELDTYPE_MESSAGE:
      {
        TMsgBuf_message ** pField = (TMsgBuf_message**)pxFieldAdr;
        TMsgBuf_messageDescriptor * pMsgDesc =(TMsgBuf_messageDescriptor*)pxFieldDesc->pDescriptor;
        uint32_t     bytesSize;
        int          curLen = 0;

        len = msgbuf_unpack_uint32 (&bytesSize, pxIn, 0, pxEnd);

        if (len > 0)
        {
          pxIn += len;
          if (pxIn + bytesSize > pxEnd)
          {
            APP_MSGBUF_report_error ("Bad message packing format");
            len = -1;
          }
          else
          {
            len += bytesSize;

            if (*pField == NULL)
            {
              *pField = (TMsgBuf_message*)MSGBUF_SYS_malloc(pMsgDesc->sizeof_message);
              msgbuf_genericMessageInit (*pField, pMsgDesc);

              curLen = msgbuf_unpack_message_content (
                pMsgDesc, *pField, pxIn, pxIn + bytesSize );
            }

            if (curLen < 0) len = curLen;
          }
        }
      }
      break;

    default:
      APP_MSGBUF_report_error ("Unknown message field type identifier");
      len = -1;
  }

  return len;
}


static const TMsgBuf_fieldDescriptor * pGetFieldDesc
(
  const TMsgBuf_messageDescriptor * pxMsgDesc,
  uint32_t                          xId
)
{
  int minId, maxId, midId;

  minId = 0;
  maxId = pxMsgDesc->n_fields - 1;

  if (minId > maxId) return NULL;
  for (;;)
  {
    if (xId > pxMsgDesc->pFields[maxId].id) return NULL;
    if (xId < pxMsgDesc->pFields[minId].id) return NULL;
    midId = minId + (maxId - minId) /2;
    if (midId == minId)
    {
      if (xId == pxMsgDesc->pFields[minId].id) return &pxMsgDesc->pFields[minId];
      if (xId == pxMsgDesc->pFields[maxId].id) return &pxMsgDesc->pFields[maxId];
      return NULL;
    }
    if (xId < pxMsgDesc->pFields[midId].id) maxId = midId;
    else minId = midId;
  }
}


int msgbuf_unpack_message_content
(
  const TMsgBuf_messageDescriptor * pxMsgDesc,
  TMsgBuf_message                 * pxMessage,
  const uint8_t                    * pxIn,
  const uint8_t                    * pxEnd
)
{
  int             len;
  uint8_t const * pStart = pxIn;
  const uint8_t * pSubEnd;

  /* Get (unpack) all fields associated to the packed message */
  while (pxIn < pxEnd)
  {
    uint32_t                         tag;
    TMsgBuf_wireType                wire_type;
    const TMsgBuf_fieldDescriptor * pFieldDesc = NULL;

    /* Get the tag and wire value of the current field in the data stream */
    len = msgbuf_unpack_tag_and_wire (&tag, &wire_type, pxIn, pxEnd);
    if (len < 0) return -1;
    pxIn += len;

    /* Find the associated field descriptor for this message associated to this tag*/
    pFieldDesc = pGetFieldDesc (pxMsgDesc, tag);
    if (!pFieldDesc)
    {
      APP_MSGBUF_report_error ("Bad message packing format");
      return -1;
    }

    /* If this is a repeated field */
    if (pFieldDesc->label == MSGBUF_TAGLABEL_REPEATED)
    {
      void     ** pMemberAdr;
      uint32_t    repeatedFieldLen;
      uint8_t   * pRepeatedArray;
      int         count;
      int         i;

      if (pFieldDesc->packed)
      {
        len = msgbuf_unpack_uint32 (
          &repeatedFieldLen,
          pxIn,
          0,
          pxEnd );

        if (len < 1)
        {
          APP_MSGBUF_report_error ("Bad message packing format");
          return -1;
        }
        pxIn += len;

        if (pxIn + repeatedFieldLen > pxEnd)
        {
          APP_MSGBUF_report_error ("Bad message packing format");
          return -1;
        }

        pMemberAdr = (void**)MSGBUF_GET_MEMBER_P(pxMessage,pFieldDesc->offset);
        if (*pMemberAdr == NULL)
        {
          len = msgbuf_count_packed_repeated_elements (
            wire_type,
            pxIn,
            pxIn + repeatedFieldLen,
            &count );
          if (len < 0) return len;

          pRepeatedArray = (uint8_t*)MSGBUF_SYS_malloc(count * pFieldDesc->sizeof_field);
          *pMemberAdr = pRepeatedArray;
          *(uint32_t*)MSGBUF_GET_MEMBER_P(pxMessage,pFieldDesc->qoffset) = count;

          MSGBUF_SYS_memset (pRepeatedArray, 0, count * pFieldDesc->sizeof_field);
          for (i=0; i<count; i++)
          {
            len = msgbuf_unpack_field (
              pFieldDesc,
              (void*)pRepeatedArray,
              wire_type,
              pxIn,
              pxEnd );

            if (len < 0) return len;

            pxIn += len;
            pRepeatedArray += pFieldDesc->sizeof_field;
          }
        }
        else pxIn += repeatedFieldLen;
      }
      else
      {
        int singleFieldLen;

        pxIn -= len; len = 0;

        len = msgbuf_count_repeated_elements (
          pFieldDesc,
          pxIn,
          pxEnd,
          &count );

        if (pxIn + len > pxEnd)
        {
          APP_MSGBUF_report_error ("Bad message packing format");
          return -1;
        }

        pMemberAdr = (void**)MSGBUF_GET_MEMBER_P(pxMessage,pFieldDesc->offset);
        if (*pMemberAdr == NULL)
        {
          pRepeatedArray = (uint8_t*)MSGBUF_SYS_malloc(count * pFieldDesc->sizeof_field);
          *pMemberAdr = pRepeatedArray;
          *(size_t*)MSGBUF_GET_MEMBER_P(pxMessage,pFieldDesc->qoffset) = count;

          MSGBUF_SYS_memset (pRepeatedArray, 0, count * pFieldDesc->sizeof_field);
          pSubEnd = pxIn + len;

          for (i=0; i<count; i++)
          {
            /* Get the tag and wire value of the current field in the data stream */
            singleFieldLen = msgbuf_unpack_tag_and_wire (&tag, &wire_type, pxIn, pSubEnd);
            if (singleFieldLen < 0) return -1;
            pxIn += singleFieldLen;

            singleFieldLen = msgbuf_unpack_field (
              pFieldDesc,
              (void*)pRepeatedArray,
              wire_type,
              pxIn,
              pxEnd );

            if (singleFieldLen < 0) return -1;
            pxIn += singleFieldLen;
            pRepeatedArray += pFieldDesc->sizeof_field;
          }
        }
        else pxIn += len;
      }
      if (len < 0) return -1;
    }
    else
    {
      len = msgbuf_unpack_field (
        pFieldDesc,
        MSGBUF_GET_MEMBER_P(pxMessage, pFieldDesc->offset),
        wire_type,
        pxIn,
        pxEnd );

      if (len < 0) return -1;
      pxIn += len;

      if (pFieldDesc->label == MSGBUF_TAGLABEL_OPTIONAL)
      {
        if ((pFieldDesc->type != MSGBUF_FIELDTYPE_MESSAGE) &&
            (pFieldDesc->type != MSGBUF_FIELDTYPE_STRING)  &&
            (pFieldDesc->type != MSGBUF_FIELDTYPE_BYTES))
        {
          *(TMsgBuf_bool*)MSGBUF_GET_MEMBER_P(pxMessage, pFieldDesc->qoffset) = 1;
        }
      }
    }
    if (len < 0) return -1;
  }

  return ((int)pxIn - (int)pStart);
}
