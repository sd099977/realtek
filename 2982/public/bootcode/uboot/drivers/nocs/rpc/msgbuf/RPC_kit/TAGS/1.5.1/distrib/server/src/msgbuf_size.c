/**
 * File: $Id:$
 *
 *  This file implements the msgbuf buffer-sizing function(s).
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
#include "src/msgbuf_size.h"
#include "inc/app_msgbuf_report.h"
#include <stddef.h>

/****************************************************************************/
/* Static functions declaration                                             */
/****************************************************************************/

/*
 * Get serialized size of a single field in the message,
 * including the space needed by the identifying tag.
 */
static int msgbuf_size_required_field (
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  const void                    * pxMember );


/* Get serialized size of a single optional field in the message,
   including the space needed by the identifying tag.
   Returns 0 if the optional field isn't set. */
static int msgbuf_size_optional_field (
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  const TMsgBuf_bool            * pxHas,
  const void                    * pxMember );


/*
 * Get serialized size of a repeated field in the message,
 * which may consist of any number of values (including 0).
 * Includes the space needed by the identifying tags (as needed).
 */
static int msgbuf_size_repeated_field (
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  int                          xCount,
  const void                    * pxMember );


/****************************************************************************/
/* Private Macro definition                                                 */
/****************************************************************************/


/* Get the pointer to the field of a structure based on its
 * byte offset. */
#define MSGBUF_GET_MEMBER_P(_pStruct,_fieldOffset)      \
  ((void *)((uint8_t*)(_pStruct)+(_fieldOffset)))


/*
 * Return the number of bytes required to store the
 * tag for the field (which includes 3 bits for
 * the wire-type, and a single bit that denotes the end-of-tag.
 */
#define MSGBUF_SIZE_TAG(_value,_len)        \
{                                           \
  if ((_value) < (1<<4)) (_len) = 1;        \
  else if ((_value) < (1<<11)) (_len) = 2;  \
  else if ((_value) < (1<<18)) (_len) = 3;  \
  else if ((_value) < (1<<25)) (_len) = 4;  \
  else (_len) = 5;                          \
}


/*
 * Return the number of bytes required to pack an unsigned 32b value
 */
#define MSGBUF_SIZE_UINT32(_value,_len)     \
{                                           \
  if ((_value) < (1<<7)) (_len) = 1;        \
  else if ((_value) < (1<<14)) (_len) = 2;  \
  else if ((_value) < (1<<21)) (_len) = 3;  \
  else if ((_value) < (1<<28)) (_len) = 4;  \
  else (_len) = 5;                          \
}


/*
 * Return the number of bytes required to pack a signed 32b value
 */
#define MSGBUF_SIZE_SINT32(_value,_len)            \
{                                                  \
  uint32_t _modifValue;                            \
  if ((_value) < 0)                                \
    {_modifValue = ((uint32_t)-(_value)) * 2 - 1;} \
  else                                             \
    {_modifValue = ((uint32_t)(_value)) * 2;}      \
                                                   \
  MSGBUF_SIZE_UINT32 (                             \
    _modifValue, (_len));                          \
}


/*
 * Return the number of bytes required to pack an unsigned 64b value
 */
#define MSGBUF_SIZE_UINT64(_value,_len)            \
{                                                  \
  uint32_t _upper32b = (uint32_t)((_value) >> 32); \
  uint32_t _lower32b = (uint32_t)(_value);         \
  if (_upper32b == 0)                              \
    { MSGBUF_SIZE_UINT32 (_lower32b, (_len)); }    \
                                                   \
  else if (_upper32b < (1UL<<3))  (_len) = 5;      \
  else if (_upper32b < (1UL<<10)) (_len) = 6;      \
  else if (_upper32b < (1UL<<17)) (_len) = 7;      \
  else if (_upper32b < (1UL<<24)) (_len) = 8;      \
  else if (_upper32b < (1UL<<31)) (_len) = 9;      \
  else (_len) = 10;                                \
}


/*
 * Return the number of bytes required to pack an signed 64b value
 */
#define MSGBUF_SIZE_SINT64(_value,_len)              \
{                                                    \
  uint64_t _modifValue;                              \
  if ((_value) < 0)                                  \
    { _modifValue = ((uint64_t)-(_value)) * 2 - 1; } \
  else                                               \
    { _modifValue = ((uint64_t)(_value)) * 2; }      \
                                                     \
  MSGBUF_SIZE_UINT64 (                               \
    _modifValue, (_len));                            \
}


/****************************************************************************/
/* Public functions implementation                                          */
/****************************************************************************/


/*
 * Get the number of bytes that the message will occupy once serialized.
 */
int msgbuf_size_message
(
  const TMsgBuf_message * pxMessage
)
{
  uint32_t                          field_count;
  int                               len = 0;
  uint32_t                          n_fields;
  const TMsgBuf_fieldDescriptor   * pFieldDesc;
  TMsgBuf_messageDescriptor const * pMsgDesc;
  const void                      * pMember;
  const void                      * pQMember;
  int                               fieldLen = 0;

  /* Get the msgbuf file descriptor associated to this message */
  pMsgDesc = (TMsgBuf_messageDescriptor const*)pxMessage->pDescriptor;

  /* Verify that the message was successfully initialized */
  if (pMsgDesc->magic != MSGBUF_MESSAGE_DESCRIPTOR_MAGIC_ID) return -1;

  /* Get the number of fields */
  n_fields = pMsgDesc->n_fields;

  /* Scan each field of this message for size identification */
  for (field_count = 0; field_count < n_fields; field_count++)
  {
    pFieldDesc = pMsgDesc->pFields + field_count;

    pMember = (const void*)MSGBUF_GET_MEMBER_P(pxMessage, pFieldDesc->offset);
    pQMember = (const void*)MSGBUF_GET_MEMBER_P(pxMessage, pFieldDesc->qoffset);

    /* If this field is required for packing */
    if (pFieldDesc->label == MSGBUF_TAGLABEL_REQUIRED)
      fieldLen = msgbuf_size_required_field (pFieldDesc, pMember);
    else if (pFieldDesc->label == MSGBUF_TAGLABEL_OPTIONAL)
      fieldLen = msgbuf_size_optional_field (pFieldDesc, (const TMsgBuf_bool*)pQMember, pMember);
    else
      fieldLen = msgbuf_size_repeated_field (pFieldDesc, *(const size_t *)pQMember, pMember);

    if (fieldLen < 0) return fieldLen;
    len += fieldLen;
  }

  return len;
}


/****************************************************************************/
/* Static functions implementation                                          */
/****************************************************************************/

/*
 * Get serialized size of a single field in the message,
 * including the space needed by the identifying tag.
 */
static int msgbuf_size_required_field
(
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  const void                    * pxMember
)
{
  int       tagLen;
  int       len;
  int       bufLen;
  uint64_t  tmp;

  MSGBUF_SIZE_TAG (pxFieldDesc->id, tagLen);

  switch (pxFieldDesc->type)
  {
    case MSGBUF_FIELDTYPE_ENUM:
    case MSGBUF_FIELDTYPE_UINT32:
      MSGBUF_SIZE_UINT32 ((*(const uint32_t *)pxMember), len);
      break;

    case MSGBUF_FIELDTYPE_SINT32:
    case MSGBUF_FIELDTYPE_INT32:
      MSGBUF_SIZE_SINT32 ((*(const int32_t *)pxMember), len);
      break;

    case MSGBUF_FIELDTYPE_UINT64:
      tmp = *(const uint64_t *)pxMember;
      MSGBUF_SIZE_UINT64 ((*(const uint64_t *)pxMember), len);
      break;

    case MSGBUF_FIELDTYPE_INT64:
    case MSGBUF_FIELDTYPE_SINT64:
      MSGBUF_SIZE_SINT64 ((*(const int64_t *)pxMember), len);
      break;

    case MSGBUF_FIELDTYPE_SFIXED32:
    case MSGBUF_FIELDTYPE_FIXED32:
    case MSGBUF_FIELDTYPE_FLOAT:
      len = 4; break;

    case MSGBUF_FIELDTYPE_SFIXED64:
    case MSGBUF_FIELDTYPE_FIXED64:
    case MSGBUF_FIELDTYPE_DOUBLE:
      len = 8; break;

    case MSGBUF_FIELDTYPE_BOOL:
      len = 1; break;

    case MSGBUF_FIELDTYPE_STRING:
      {
        const char            * pStr;
        pStr = *(const char **)pxMember;
        bufLen = pStr ? MSGBUF_SYS_strlen (pStr) : 0;
        MSGBUF_SIZE_UINT32 ((uint32_t)bufLen, len);
        len += bufLen;
      }
      break;

    case MSGBUF_FIELDTYPE_BYTES:
      if (((const TMsgBuf_bytes*)pxMember)->pData)
        bufLen = ((const TMsgBuf_bytes *)pxMember)->len;
      else bufLen = 0;
      MSGBUF_SIZE_UINT32 ((uint32_t)bufLen, len);
      len += bufLen;
      break;

    /* case MSGBUF_FIELDTYPE_GROUP: */

    case MSGBUF_FIELDTYPE_MESSAGE:
      {
        TMsgBuf_message const * pMsg;
        pMsg = *(TMsgBuf_message const *const *)pxMember;
        bufLen = pMsg ? msgbuf_size_message (pMsg) : 0;
        MSGBUF_SIZE_UINT32 ((uint32_t)bufLen, len);
        len += bufLen;
      }
      break;

    default:
      APP_MSGBUF_report_error ("Unknown message field type identifier");
      return -1;
  }

  return (len + tagLen);
}


/* Get serialized size of a single optional field in the message,
   including the space needed by the identifying tag.
   Returns 0 if the optional field isn't set. */
static int msgbuf_size_optional_field
(
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  const TMsgBuf_bool            * pxHas,
  const void                    * pxMember
)
{
  if (pxFieldDesc->type == MSGBUF_FIELDTYPE_MESSAGE)
  {
     const TMsgBuf_message ** pMember = (const TMsgBuf_message **)pxMember;

    if (*pMember == NULL)
      return 0;
  }
  else if (pxFieldDesc->type == MSGBUF_FIELDTYPE_STRING)
  {
    const void * pMember = *(const void * const *)pxMember;

    if ((pMember == NULL) || (pMember == pxFieldDesc->pDefaultValue))
      return 0;
  }
  else if (pxFieldDesc->type == MSGBUF_FIELDTYPE_BYTES)
  {
    const TMsgBuf_bytes *pMember = (TMsgBuf_bytes*)pxMember;
    if (pMember->pData) msgbuf_size_required_field(pxFieldDesc, pxMember);
    else return 0;
  }

  else if (!(*pxHas)) return 0;
  return msgbuf_size_required_field(pxFieldDesc, pxMember);
}


/*
 * Get serialized size of a repeated field in the message,
 * which may consist of any number of values (including 0).
 * Includes the space needed by the identifying tags (as needed).
 */
static int msgbuf_size_repeated_field
(
  const TMsgBuf_fieldDescriptor * pxFieldDesc,
  int                          xCount,
  void const                    * pxMember
)
{
  int   headerLen;
  int   totalLen = 0;
  int   len;
  int   bufLen;
  int   counter;

  void const * pArray = *(void const **)pxMember;

  if (xCount == 0) return 0;

  MSGBUF_SIZE_TAG (pxFieldDesc->id, headerLen);
  if (!pxFieldDesc->packed) headerLen *= xCount;

  switch (pxFieldDesc->type)
  {
    case MSGBUF_FIELDTYPE_SINT32:
    case MSGBUF_FIELDTYPE_ENUM:
      for (counter = 0; counter < xCount; counter++)
      {
        MSGBUF_SIZE_SINT32 (((int32_t *)pArray)[counter], len);
        totalLen += len;
      }
      break;

    case MSGBUF_FIELDTYPE_INT32:
    case MSGBUF_FIELDTYPE_UINT32:
      for (counter = 0; counter < xCount; counter++)
      {
        MSGBUF_SIZE_UINT32(((uint32_t*)pArray)[counter], len);
        totalLen += len;
      }
      break;

    case MSGBUF_FIELDTYPE_INT64:
    case MSGBUF_FIELDTYPE_SINT64:
      for (counter = 0; counter < xCount; counter++)
      {
        MSGBUF_SIZE_SINT64(((int64_t*)pArray)[counter], len);
        totalLen += len;
      }
      break;

    case MSGBUF_FIELDTYPE_UINT64:
      for (counter = 0; counter < xCount; counter++)
      {
        MSGBUF_SIZE_UINT64(((uint64_t*)pArray)[counter], len);
        totalLen += len;
      }
      break;

    case MSGBUF_FIELDTYPE_SFIXED32:
    case MSGBUF_FIELDTYPE_FIXED32:
    case MSGBUF_FIELDTYPE_FLOAT:
      totalLen += (4 * xCount);
      break;

    case MSGBUF_FIELDTYPE_SFIXED64:
    case MSGBUF_FIELDTYPE_FIXED64:
    case MSGBUF_FIELDTYPE_DOUBLE:
      totalLen += (8 * xCount);
      break;

    case MSGBUF_FIELDTYPE_BOOL:
      totalLen += xCount;
      break;

    case MSGBUF_FIELDTYPE_STRING:
      for (counter = 0; counter < xCount; counter++)
      {
        if (((char const**)pArray)[counter])
          bufLen = MSGBUF_SYS_strlen (((char const**)pArray)[counter]);
        else bufLen = 0;
        MSGBUF_SIZE_UINT32((uint32_t)bufLen, len);
        totalLen += (len + bufLen);
      }
      break;

    case MSGBUF_FIELDTYPE_BYTES:
      for (counter = 0; counter < xCount; counter++)
      {
        if (((TMsgBuf_bytes*)pArray)[counter].pData)
          bufLen = ((TMsgBuf_bytes*)pArray)[counter].len;
        else bufLen = 0;
        MSGBUF_SIZE_UINT32((uint32_t)bufLen, len);
        totalLen += (len + bufLen);
      }
      break;

    case MSGBUF_FIELDTYPE_MESSAGE:
      for (counter = 0; counter < xCount; counter++)
      {
        bufLen = msgbuf_size_message (((TMsgBuf_message **)pArray)[counter]);
        MSGBUF_SIZE_UINT32((uint32_t)bufLen, len);
        totalLen += (len + bufLen);
      }
      break;

    /* case MSGBUF_FIELDTYPE_GROUP: */          /* NOT SUPPORTED */
    default:
      APP_MSGBUF_report_error ("Unknown message field type identifier");
      return -1;
  }

  if (pxFieldDesc->packed)
  {
    MSGBUF_SIZE_UINT32((uint32_t)totalLen, len);
    totalLen += len;
  }
  return (totalLen + headerLen);
}

