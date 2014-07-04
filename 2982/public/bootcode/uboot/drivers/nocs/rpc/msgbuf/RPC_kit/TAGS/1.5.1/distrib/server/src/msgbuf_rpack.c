/**
 * File: $Id:$
 *
 *  This file implements the msgbuf reverse packing functions
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
#include "inc/msgbuf_sys_string.h"
#include <stddef.h>
#include "inc/app_msgbuf_report.h"
#include "src/msgbuf_rpack.h"


/* Get the pointer to the field of a structure based on its
 * byte offset. */
#define MSGBUF_GET_MEMBER_P(_pStruct,_fieldOffset)      \
  ((void *)((uint8_t*)(_pStruct)+(_fieldOffset)))


/****************************************************************************/
/* Static functions declaration                                             */
/****************************************************************************/

/*
 * Pack a 64-bit unsigned integer that fits in a 64-bit uint,
 * using base-128 encoding.
 */
static int msgbuf_rpack_uint64 (
  uint64_t   xValue,
  uint8_t ** pxOut );


/*
 * Pack a length-prefixed string.
 * The input string is NUL-terminated.
 *
 * The NULL pointer is treated as an empty string.
 *  This isn't really necessary, but it allows people
 *  to leave required strings blank.
 *  (See Issue 13 in the bug tracker for a
 * little more explanation).
 */
static int msgbuf_rpack_string (
  const char *  pxStr,
  uint8_t    ** pxOut );


static int msgbuf_rpack_bytes (
  const TMsgBuf_bytes *  pxData,
  uint8_t          ** pxOut );


static int msgbuf_rpack_prefixed_message (
  const TMsgBuf_message  * pxMessage,
  uint8_t               ** pxOut );


static int msgbug_rapck_required_field (
  const TMsgBuf_fieldDescriptor *  pxField,
  const void                    *  pxMember,
  uint8_t                       ** pxOut );


static int msgbuf_rpack_optional_field (
  const TMsgBuf_fieldDescriptor *  pxField,
  const TMsgBuf_bool            *  pxHas,
  const void                    *  pxMember,
  uint8_t                       ** pxOut );


static int msgbuf_rpack_repeated_field (
  const TMsgBuf_fieldDescriptor * pxField,
  int                           xCount,
  const void                     * pxMember,
  uint8_t                       ** pxOut );


/****************************************************************************/
/* Private Macro definition                                                 */
/****************************************************************************/


/*
 * Pack an unsigned 32-bit integer in base-128 encoding, and return
 * the number of bytes needed: this will be 5 or less.
 */
#define _MSGBUF_RPACK_UINT32(_value,_pOut)         \
{                                                  \
  uint32_t _tmpValue = (uint32_t)(_value);         \
                                                   \
  if (_tmpValue >= (1UL << 28))                    \
    *--_pOut = (uint8_t)(_tmpValue >> 28) | 0x80;  \
  if (_tmpValue >= (1UL << 21))                    \
    *--_pOut = (uint8_t)(_tmpValue >> 21) | 0x80;  \
  if (_tmpValue >= (1UL << 14))                    \
    *--_pOut = (uint8_t)(_tmpValue >> 14) | 0x80;  \
  if (_tmpValue >= (1UL << 7))                     \
    *--_pOut = (uint8_t)(_tmpValue >> 7 ) | 0x80;  \
  *--_pOut = (uint8_t)(_tmpValue) | 0x80;          \
}

/*
 * Pack an unsigned 32-bit integer in base-128 encoding, and return
 * the number of bytes needed: this will be 5 or less.
 */
#define MSGBUF_RPACK_UINT32(_value,_pOut,_len)    \
{                                                 \
  uint8_t * _pEnd = (_pOut);                      \
  _MSGBUF_RPACK_UINT32((_value),(_pOut));         \
  (_len) = (int)(_pEnd) - (int)(_pOut);     \
  *(_pEnd - 1) &= 0x7F;                           \
}


/*
 * Pack a 32-bit integer in zigwag encoding.
 */
#define MSGBUF_RPACK_SINT32(_value,_pOut,_len)  \
{                                               \
  int32_t  _orgValue = (int32_t)_value;         \
  uint32_t _modifValue;                         \
                                                \
  if (_orgValue < 0)                            \
    _modifValue = (-_orgValue) * 2 - 1;         \
  else                                          \
    _modifValue = _orgValue * 2;                \
                                                \
  MSGBUF_RPACK_UINT32 (                         \
      _modifValue, (_pOut),(_len));             \
}


/* Pack a 64-bit signed integer in zigzan encoding,
   return the size of the packed output.
   (Max returned value is 10) */
#define MSGBUF_RPACK_SINT64(_value,_pOut,_len)           \
{                                                        \
  int64_t  _orgValue = (int64_t)(_value);                \
  uint64_t _modifValue;                                  \
                                                         \
  if (_orgValue < 0)                                     \
    _modifValue = ((uint64_t)-_orgValue) * 2 -1;         \
  else                                                   \
    _modifValue = ((uint64_t)_orgValue) * 2;             \
                                                         \
  (_len) = msgbuf_rpack_uint64 (_modifValue, &(_pOut)); \
}


/* wire-type will be added in required_field_pack() */
/* XXX: just call uint64_pack on 64-bit platforms. */
#define MSGBUF_RPACK_TAG(_value,_pOut,_len)         \
{                                                   \
  if ((_value) <= (1UL << (32-3)))                  \
  { MSGBUF_RPACK_UINT32 (                           \
      ((_value)<< 3), (_pOut), (_len)); }           \
  else                                              \
  {                                                 \
    (_len) = msgbuf_rpack_uint64 (                 \
      ((uint64_t)(_value)) << 3, &(_pOut));         \
  }                                                 \
}


/* Pack a 64-bit fixed-length value.
   (Used for fixed64, sfixed64, double) */

#define MSGBUF_RPACK_FIXED32(_value,_pOut,_len) \
{                                               \
  uint8_t * _pCur;                              \
  uint32_t _tmpValue = (_value);                \
  (_pOut) -= 4;                                 \
  _pCur = (uint8_t*)(_pOut);                    \
  _pCur[0] = (uint8_t)_tmpValue;                \
  _pCur[1] = (uint8_t)(_tmpValue >> 8);         \
  _pCur[2] = (uint8_t)(_tmpValue >> 16);        \
  _pCur[3] = (uint8_t)(_tmpValue >> 24);        \
  (_len) = 4;                                   \
}


/* XXX: the big-endian impl is really only good for 32-bit machines,
   a 64-bit version would be appreciated, plus a way
   to decide to use 64-bit math where convenient. */
#define MSGBUF_RPACK_FIXED64(_value,_pOut,_len)     \
{                                                   \
  uint8_t * _pCur;                                  \
  uint64_t  _tmpValue = (_value);                   \
  (_pOut) -= 8;                                     \
  _pCur = (uint8_t*)(_pOut);                        \
  _pCur[0] = (uint8_t)_tmpValue;                    \
  _pCur[1] = (uint8_t)(_tmpValue >> 8);             \
  _pCur[2] = (uint8_t)(_tmpValue >> 16);            \
  _pCur[3] = (uint8_t)(_tmpValue >> 24);            \
  _pCur[0] = (uint8_t)(_tmpValue >> 32);            \
  _pCur[1] = (uint8_t)(_tmpValue >> 40);            \
  _pCur[2] = (uint8_t)(_tmpValue >> 48);            \
  _pCur[3] = (uint8_t)(_tmpValue >> 56);            \
  (_len) = 8;                                       \
}


/* Pack a boolean as 0 or 1, even though the protobuf_c_boolean
   can really assume any integer value. */
/* XXX: perhaps on some platforms "*out = !!value" would be
   a better impl, b/c that is idiotmatic c++ in some stl impls. */
#define MSGBUF_RPACK_BOOL(_value,_pOut,_len) \
{                                            \
  *--(_pOut) = (_value) ? 1 : 0;             \
  (_len) = 1;                                \
}


/****************************************************************************/
/* Public functions implementation                                          */
/****************************************************************************/


int msgbuf_rpack_message
(
  const TMsgBuf_message  * pxMessage,
  uint8_t                ** pxOut
)
{
  int i;
  int len = 0;
  int fieldLen = 0;

  for (i = pxMessage->pDescriptor->n_fields - 1; i >= 0; i--)
  {
    const TMsgBuf_fieldDescriptor * pField = pxMessage->pDescriptor->pFields + i;
    const void * pMember = (const void *)MSGBUF_GET_MEMBER_P(pxMessage, pField->offset);
    const void * pQmember = (const void *)MSGBUF_GET_MEMBER_P(pxMessage, pField->qoffset);

    if (pField->label == MSGBUF_TAGLABEL_REQUIRED)
      fieldLen = msgbug_rapck_required_field (pField, pMember, pxOut);
    else if (pField->label == MSGBUF_TAGLABEL_OPTIONAL)
      fieldLen = msgbuf_rpack_optional_field (pField, (const TMsgBuf_bool*)pQmember, pMember, pxOut);
    else
      fieldLen = msgbuf_rpack_repeated_field (pField, *(const size_t *)pQmember, pMember, pxOut);

    if (fieldLen < 0) return fieldLen;
    len += fieldLen;
  }

  return len;
}


/****************************************************************************/
/* Static functions implementation                                          */
/****************************************************************************/


/*
 * Pack a 64-bit unsigned integer that fits in a 64-bit uint,
 * using base-128 encoding.
 */
static int msgbuf_rpack_uint64
(
  uint64_t    xValue,
  uint8_t  ** pxOut
)
{
  int        len      = 0;
  uint8_t  * pEnd     = *pxOut;
  uint8_t  * _pOut    = *pxOut;
  uint32_t   upper32b = (uint32_t )(xValue >> 32);
  uint32_t   lower32b = (uint32_t )xValue;

  if (upper32b == 0)
  {
    _MSGBUF_RPACK_UINT32 (lower32b, _pOut);
  }
  else
  {
    if (upper32b >= (1UL << 3)) _MSGBUF_RPACK_UINT32 ((upper32b >> 3), _pOut);

    *--_pOut = (uint8_t)(lower32b >> 28) | (uint8_t)(upper32b << 4) | 0x80;
    *--_pOut = (uint8_t)(lower32b >> 21) | 0x80;
    *--_pOut = (uint8_t)(lower32b >> 14) | 0x80;
    *--_pOut = (uint8_t)(lower32b >> 7 ) | 0x80;
    *--_pOut = (uint8_t)(lower32b) | 0x80;
  }

  len = (int)pEnd - (int)_pOut;
  *pxOut = _pOut;
  *(pEnd -1) &= 0x7F;
  return (len);
}


/*
 * Pack a length-prefixed string.
 * The input string is NUL-terminated.
 *
 * The NULL pointer is treated as an empty string.
 *  This isn't really necessary, but it allows people
 *  to leave required strings blank.
 *  (See Issue 13 in the bug tracker for a
 * little more explanation).
 */
static int msgbuf_rpack_string
(
  const char *  pxStr,
  uint8_t    ** pxOut
)
{
  int len = 0;
  int bufLen;

  if (pxStr == NULL)
  {
    *--(*pxOut) = 0;
    return 1;
  }
  else
  {
    bufLen = MSGBUF_SYS_strlen (pxStr);
    *pxOut -= bufLen;
    MSGBUF_SYS_memcpy (*pxOut, pxStr, bufLen);
    MSGBUF_RPACK_UINT32 (bufLen, *pxOut, len);
    return (len + bufLen);
  }
}


/* */
static int msgbuf_rpack_bytes
(
  const TMsgBuf_bytes  * pxData,
  uint8_t             ** pxOut
)
{
  int len;
  int bufLen;

  if (pxData->pData)
  {
    bufLen = pxData->len;
    *pxOut -= bufLen;
    MSGBUF_SYS_memcpy (*pxOut, pxData->pData, bufLen);
  }
  else bufLen = 0;
  MSGBUF_RPACK_UINT32 (bufLen, *pxOut, len);
  return (len + bufLen);
}


/* */
static int msgbuf_rpack_prefixed_message
(
  const TMsgBuf_message  * pxMessage,
  uint8_t               ** pxOut
)
{
  int len;
  int pack_len;

  if (pxMessage == NULL)
  {
    *--(*pxOut) = 0;
    return 1;
  }
  else
  {
    len = msgbuf_rpack_message (pxMessage, pxOut);
    MSGBUF_RPACK_UINT32 (len, *pxOut, pack_len);
    return (len + pack_len);
  }
}


/* */
static int msgbug_rapck_required_field
(
  const TMsgBuf_fieldDescriptor  *  pxField,
  const void                     *  pxMember,
  uint8_t                        ** pxOut
)
{
  int    len;
  int    bufLen = 0;
  uint8_t   wire_type = 0;

  const TMsgBuf_bytes * pData;

  switch (pxField->type)
  {
    case MSGBUF_FIELDTYPE_ENUM:
    case MSGBUF_FIELDTYPE_UINT32:
      MSGBUF_RPACK_UINT32 (*(const uint32_t *)pxMember, *pxOut, bufLen);
      wire_type = MSGBUF_WIRE_TYPE_VARINT;
      break;

    case MSGBUF_FIELDTYPE_SINT32:
    case MSGBUF_FIELDTYPE_INT32:
      MSGBUF_RPACK_SINT32 (*(const int32_t *)pxMember, *pxOut, bufLen);
      wire_type = MSGBUF_WIRE_TYPE_VARINT;
      break;

    case MSGBUF_FIELDTYPE_UINT64:
      bufLen = msgbuf_rpack_uint64 (*(const uint64_t *)pxMember, pxOut);
      wire_type = MSGBUF_WIRE_TYPE_VARINT;
      break;

    case MSGBUF_FIELDTYPE_INT64:
    case MSGBUF_FIELDTYPE_SINT64:
      MSGBUF_RPACK_SINT64 (*(const int64_t *)pxMember, *pxOut, bufLen);
      wire_type = MSGBUF_WIRE_TYPE_VARINT;
      break;

    case MSGBUF_FIELDTYPE_SFIXED32:
    case MSGBUF_FIELDTYPE_FIXED32:
    case MSGBUF_FIELDTYPE_FLOAT:
      MSGBUF_RPACK_FIXED32 (*(const uint32_t*)pxMember, *pxOut, bufLen);
      wire_type = MSGBUF_WIRE_TYPE_32BIT;
      break;

    case MSGBUF_FIELDTYPE_SFIXED64:
    case MSGBUF_FIELDTYPE_FIXED64:
    case MSGBUF_FIELDTYPE_DOUBLE:
      MSGBUF_RPACK_FIXED64(*(const uint32_t*)pxMember, *pxOut, bufLen);
      wire_type = MSGBUF_WIRE_TYPE_64BIT;
      break;

    case MSGBUF_FIELDTYPE_BOOL:
      MSGBUF_RPACK_BOOL (*(const TMsgBuf_bool *)pxMember, *pxOut, bufLen);
      wire_type = MSGBUF_WIRE_TYPE_VARINT;
      break;

    case MSGBUF_FIELDTYPE_STRING:
      {
        char const * const * pCharMemberAdr = (char const * const *)pxMember;
        bufLen = msgbuf_rpack_string (*pCharMemberAdr, pxOut);
        wire_type = MSGBUF_WIRE_TYPE_LENGTH_PREFIXED;
      }
      break;

    case MSGBUF_FIELDTYPE_BYTES:
      pData = ((const TMsgBuf_bytes*)pxMember);
      bufLen =  msgbuf_rpack_bytes (pData, pxOut);
      wire_type = MSGBUF_WIRE_TYPE_LENGTH_PREFIXED;
      break;

    /* case MSGBUF_FIELDTYPE_GROUP: */ /* NOT SUPPORTED */

    case MSGBUF_FIELDTYPE_MESSAGE:
      bufLen = msgbuf_rpack_prefixed_message (
        *(TMsgBuf_message * const *)pxMember,
        pxOut);
      wire_type = MSGBUF_WIRE_TYPE_LENGTH_PREFIXED;
      break;

    default:
      APP_MSGBUF_report_error ("Unknown message field type identifier");
      return -1;
  }

  MSGBUF_RPACK_TAG (pxField->id, *pxOut, len);
  **pxOut |= wire_type;
  if (bufLen < 0) return bufLen;
  return (len + bufLen);
}


/* */
static int msgbuf_rpack_optional_field
(
  const TMsgBuf_fieldDescriptor  * pxField,
  const TMsgBuf_bool             * pxHas,
  const void                     * pxMember,
  uint8_t                       ** pxOut
)
{
  if (pxField->type == MSGBUF_FIELDTYPE_MESSAGE)
  {
    const TMsgBuf_message ** pMember;
    pMember = (const TMsgBuf_message **)pxMember;
    if (*pMember == NULL) return 0;
  }
  else if (pxField->type == MSGBUF_FIELDTYPE_STRING)
  {
    const void *pMember;
    pMember = *(const void * const *)pxMember;
    if ((pMember == NULL) ||
        (pMember == pxField->pDefaultValue))
      return 0;
  }
  else if (pxField->type == MSGBUF_FIELDTYPE_BYTES)
  {
    TMsgBuf_bytes * pBytesMember = (TMsgBuf_bytes*)pxMember;
    if (!pBytesMember->pData) return 0;
  }
  else if (!*pxHas) return 0;

  return msgbug_rapck_required_field (
    pxField,
    pxMember,
    pxOut);
}


/* */
static int msgbuf_rpack_repeated_field
(
  const TMsgBuf_fieldDescriptor  * pxField,
  int                              xCount,
  const void                     * pxMember,
  uint8_t                       ** pxOut
)
{
  char * pArray = * (char * const *)pxMember;
  int    i;
  int    len = 0;
  int    fieldLen = 0;
  const  unsigned char *pArr;
  int    field_size;

  if (xCount == 0) return 0;

  field_size = (int)pxField->sizeof_field;
  pArr = (const unsigned char *)pArray;
  pArr += xCount * field_size;

  if (pxField->packed)
  {
    switch (pxField->type)
    {
      case MSGBUF_FIELDTYPE_SINT32:
      case MSGBUF_FIELDTYPE_INT32:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            MSGBUF_RPACK_SINT32 (*(const int32_t *)pArr, *pxOut, fieldLen);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_ENUM:
      case MSGBUF_FIELDTYPE_UINT32:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            MSGBUF_RPACK_UINT32 (*(const uint32_t *)pArr, *pxOut, fieldLen);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_INT64:
      case MSGBUF_FIELDTYPE_SINT64:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            MSGBUF_RPACK_SINT64 (*(const int64_t *)pArr, *pxOut, fieldLen);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_UINT64:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            fieldLen = msgbuf_rpack_uint64 (*(const uint64_t *)pArr, pxOut);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_SFIXED32:
      case MSGBUF_FIELDTYPE_FIXED32:
      case MSGBUF_FIELDTYPE_FLOAT:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            MSGBUF_RPACK_FIXED32 (*(const uint32_t*)pArr, *pxOut, fieldLen);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_SFIXED64:
      case MSGBUF_FIELDTYPE_FIXED64:
      case MSGBUF_FIELDTYPE_DOUBLE:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            MSGBUF_RPACK_FIXED64 (*(const uint64_t *)pArr, *pxOut, fieldLen);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_BOOL:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            MSGBUF_RPACK_BOOL (*(const TMsgBuf_bool *)pArr, *pxOut, fieldLen);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_STRING:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            fieldLen = msgbuf_rpack_string (*(const char **)pArr, pxOut);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_BYTES:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            fieldLen = msgbuf_rpack_bytes ((const TMsgBuf_bytes *)pArr, pxOut);
            len += fieldLen;
          }
        }
        break;

      case MSGBUF_FIELDTYPE_MESSAGE:
        {
          for (i = 0; i < xCount; i++)
          {
            pArr -= field_size;
            fieldLen = msgbuf_rpack_message (*(const TMsgBuf_message **)pArr, pxOut);
            len += fieldLen;
          }
        }
        break;

      default:
        APP_MSGBUF_report_error ("Unknown message field type identifier");
        return -1;
    }

    MSGBUF_RPACK_UINT32(len, *pxOut , fieldLen)
    len += fieldLen;
    MSGBUF_RPACK_TAG (pxField->id, *pxOut, fieldLen);
    len += fieldLen;
  }
  else
  {
    for (i = 0; i < xCount; i++)
    {
      pArr -= field_size;
      fieldLen = msgbug_rapck_required_field (pxField, pArr, pxOut);
      if (fieldLen < 0) return fieldLen;
      len += fieldLen;
    }
  }

  return len;
}
