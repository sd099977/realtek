/**
 * File: $Id:$
 *
 *  This file implements the msgbug base allocation functions.
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

#include "inc/xsd-c.h"
#include <stddef.h>
#include "inc/msgbuf_sys_malloc.h"
#include "src/msgbuf_alloc.h"
#include "inc/app_msgbuf_report.h"
#include "inc/msgbuf_sys_string.h"

/* Get the pointer to the field of a structure based on its
 * byte offset. */
#define MSGBUF_GET_MEMBER_P(_pStruct, _fieldOffset)             \
    ((void *) ((uint8_t*) (_pStruct) + (_fieldOffset)))


/* Init a preallocated message content with its default value */

void msgbuf_genericMessageInit
(
  TMsgBuf_message                 * pxMessage,
  const TMsgBuf_messageDescriptor * pxMsgDesc
)
{
  /* int i; */

  MSGBUF_SYS_memcpy (pxMessage, pxMsgDesc->pInitValue, pxMsgDesc->sizeof_message);

#if 0
  for (i = 0; i < pxMsgDesc->n_fields; i++)
  {
    TMsgBuf_fieldDescriptor const   * pFieldDesc;
    TMsgBuf_message                 * pSubMessage = NULL;
    TMsgBuf_messageDescriptor const * pSubMessage_desc = NULL;

    pFieldDesc = &pxMsgDesc->pFields[i];

    switch (pFieldDesc->type)
    {
      case MSGBUF_FIELDTYPE_MESSAGE:
        if (pFieldDesc->label == MSGBUF_TAGLABEL_REQUIRED)
        {
          pSubMessage_desc = (TMsgBuf_messageDescriptor const *)pFieldDesc->pDescriptor;
          pSubMessage = (TMsgBuf_message*)MSGBUF_SYS_malloc(pSubMessage_desc->sizeof_message);

          *((TMsgBuf_message**)MSGBUF_GET_MEMBER_P(pxMessage, pFieldDesc->offset)) = pSubMessage;

          msgbuf_genericMessageInit (pSubMessage, pSubMessage_desc );
        }
        break;

      case MSGBUF_FIELDTYPE_INT32:
      case MSGBUF_FIELDTYPE_SINT32:
      case MSGBUF_FIELDTYPE_SFIXED32:
      case MSGBUF_FIELDTYPE_UINT32:
      case MSGBUF_FIELDTYPE_FIXED32:
      case MSGBUF_FIELDTYPE_FLOAT:
      case MSGBUF_FIELDTYPE_ENUM:
        /* MSGBUF_SYS_memcpy (pField, dv, sizeof(uint32_t)); */
        /* break; */

      case MSGBUF_FIELDTYPE_INT64:
      case MSGBUF_FIELDTYPE_SINT64:
      case MSGBUF_FIELDTYPE_SFIXED64:
      case MSGBUF_FIELDTYPE_UINT64:
      case MSGBUF_FIELDTYPE_FIXED64:
      case MSGBUF_FIELDTYPE_DOUBLE:
        /* MSGBUF_SYS_memcpy (pField, dv, sizeof(uint64_t)); */
        /* break; */

      case MSGBUF_FIELDTYPE_BOOL:
        /* MSGBUF_SYS_memcpy (pField, dv, sizeof (TMsgBuf_bool)); */
        break;

      case MSGBUF_FIELDTYPE_BYTES:
        /* MSGBUF_SYS_memcpy ((TMsgBuf_bytes*)pField, dv, sizeof (TMsgBuf_bytes)); */
        break;

      case MSGBUF_FIELDTYPE_STRING:
        /* *(void const**)pField = dv; */
        break;

      default:
        APP_MSGBUF_report_error ("Unknown message field type identifier");
        break;
    }
  }
#endif
}


static void msgbuf_deallocateField
(
  TMsgBuf_fieldDescriptor const  * pxFieldDesc,
  void                           * pxField
)
{
  switch (pxFieldDesc->type)
  {
    case MSGBUF_FIELDTYPE_INT32:
    case MSGBUF_FIELDTYPE_SINT32:
    case MSGBUF_FIELDTYPE_SFIXED32:
    case MSGBUF_FIELDTYPE_UINT32:
    case MSGBUF_FIELDTYPE_FIXED32:
    case MSGBUF_FIELDTYPE_FLOAT:
    case MSGBUF_FIELDTYPE_ENUM:
    case MSGBUF_FIELDTYPE_INT64:
    case MSGBUF_FIELDTYPE_SINT64:
    case MSGBUF_FIELDTYPE_SFIXED64:
    case MSGBUF_FIELDTYPE_UINT64:
    case MSGBUF_FIELDTYPE_FIXED64:
    case MSGBUF_FIELDTYPE_DOUBLE:
    case MSGBUF_FIELDTYPE_BOOL:
      break;

    case MSGBUF_FIELDTYPE_BYTES:
      {
        TMsgBuf_bytes * pBufHeader = (TMsgBuf_bytes*)pxField;
        if (pBufHeader->pData)
          if (!(pxFieldDesc->pDefaultValue) || (pBufHeader->pData != ((TMsgBuf_bytes const *)(pxFieldDesc->pDefaultValue))->pData))
            MSGBUF_SYS_free (pBufHeader->pData);
        pBufHeader->pData = NULL;
        pBufHeader->len = 0;
      }
      break;

    case MSGBUF_FIELDTYPE_STRING:
      {
        char ** pBufHeader = (char**)pxField;
        if ((*pBufHeader) &&
            (*pBufHeader != (char const *)pxFieldDesc->pDefaultValue))
          MSGBUF_SYS_free (*pBufHeader);
        *pBufHeader = NULL;
      }
      break;

    case MSGBUF_FIELDTYPE_MESSAGE:
      {
        TMsgBuf_message ** pSubMsg = (TMsgBuf_message**)pxField;
        if (*pSubMsg) msgbuf_genericMessageDeallocate (*pSubMsg);
        *pSubMsg = NULL;
      }
      break;

    default:
      APP_MSGBUF_report_error ("Unknown message field type identifier");
      break;
  }
}


void msgbuf_genericMessageDeallocate
(
  TMsgBuf_message * pxMessage
)
{
  TMsgBuf_messageDescriptor const * pMsgDesc = NULL;
  TMsgBuf_fieldDescriptor const   * pFieldDesc = NULL;
  size_t i;
  int    j;

  if (pxMessage == NULL) return;

  pMsgDesc = (TMsgBuf_messageDescriptor const *)pxMessage->pDescriptor;

  /* Only deallocated if the message was successfully initialized */
  if (pMsgDesc->magic != MSGBUF_MESSAGE_DESCRIPTOR_MAGIC_ID)
  {
    APP_MSGBUF_report_error ("Message deallocation failure: invalid MSGBUF message");
    return;
  }

  /* Scan all field */
  for (i = 0; i < pMsgDesc->n_fields; i++)
  {
    pFieldDesc = &pMsgDesc->pFields[i];

    if (pFieldDesc->label == MSGBUF_TAGLABEL_REPEATED)
    {
      void ** pArrayAdr  = (void **)MSGBUF_GET_MEMBER_P (pxMessage, pFieldDesc->offset);
      uint8_t   * pArray = (uint8_t*)(*pArrayAdr);
      if (pArray)
      {
        int32_t repeatedNum = *(int32_t*)MSGBUF_GET_MEMBER_P (pxMessage, pFieldDesc->qoffset);

        for (j=0; j < (int)repeatedNum; j++)
        {
          msgbuf_deallocateField (pFieldDesc, (void*)pArray);
          pArray += pFieldDesc->sizeof_field;
        }

        if (*pArrayAdr) MSGBUF_SYS_free (*pArrayAdr);
      }

      (*pArrayAdr) = NULL;
      *(int32_t*)MSGBUF_GET_MEMBER_P (pxMessage, pFieldDesc->qoffset) = 0;
    }
    else
    {
      msgbuf_deallocateField (pFieldDesc, MSGBUF_GET_MEMBER_P(pxMessage, pFieldDesc->offset));
    }
  }

  MSGBUF_SYS_free (pxMessage);
}


/* */
int msgbuf_genericTestEnum
(
  TMsgBuf_enumDescriptor const * pxEnumDescriptor,
  int                            xValue
)
{
  int minId, maxId, midId;

  minId = 0;
  maxId = pxEnumDescriptor->n_values -1;

  if (maxId < 0) return 0;

  for (;;)
  {
    if (xValue > pxEnumDescriptor->pValues[maxId].value) return 0;
    if (xValue < pxEnumDescriptor->pValues[minId].value) return 0;

    midId = minId + (maxId - maxId) / 2;
    if (midId == minId)
    {
      if (xValue == pxEnumDescriptor->pValues[minId].value) return 1;
      if (xValue == pxEnumDescriptor->pValues[maxId].value) return 1;
      return 0;
    }
    if (xValue < pxEnumDescriptor->pValues[midId].value) maxId = midId;
    else minId = midId;
  }
}

