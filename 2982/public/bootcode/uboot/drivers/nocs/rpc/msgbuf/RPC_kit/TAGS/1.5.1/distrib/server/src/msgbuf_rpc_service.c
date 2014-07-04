/**
 * File: $Id:$
 *
 *  This file implements the msgbuf RPC generic service functions.
 *
 *  Copyright (c) 2012-2013 Nagravision. All rights reserved.
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

/*****************************************************************************
 * Include files
 ****************************************************************************/

#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "src/msgbuf_unpack.h"
#include "src/msgbuf_rpack.h"
#include "src/msgbuf_size.h"
#include "inc/msgbuf_rpc_service.h"
#include "inc/app_rpc_report.h"
#include "inc/rpc_rpcctrl.h"
#include "src/rpc_rpcctrl_api.h"
#include <stdio.h>

/*****************************************************************************
 * RPC transport stream specific definition
 ****************************************************************************/



/* RPC magic number (RPC transport layer specific to any "msgbug"-based RPC */
#define RPC_MAGIC_VALUE_ID            0x01020504
#define RPC_HANDLE_MAGIC_NUMBER       0x6A29ED15


/*****************************************************************************
 * Static function prototype definition
 ****************************************************************************/


/* */
static int findServiceId (
  TRpcSocketHnd                    * pxRpcSockHandle,
  TMsgBuf_serviceDescriptor const  * pxServiceDescriptor,
  uint32_t                         * pxServiceId );


/* */
static int findServiceDescriptor (
  TRpcSocketHnd                    * pxRpcSockHandle,
  uint32_t                           xServiceId,
  TMsgBuf_serviceDescriptor const ** pxServiceDescriptor );


/* */
static uint32_t uint32_from_le (uint32_t xValue);

/* */
static int _readPacket (
  TRpcSocketHnd      * pxRpcSocketHandler,
  TMsgBuf_rpcHandler   xRpcHandler,
  void               * pxBuffer,
  int                  xDataSize,
  int                  xIsRpcMsgHeader );


/*****************************************************************************
 * Public function implementations
 ****************************************************************************/


/* */
TRpc_status msgbuf_rpc_build_callHeader
(
  TRpcSocketHnd          * pxRpcSocketHandle,
  TMsgBuf_rpcHandler       xRpcHandler,
  TMsgBuf_message        * pxInMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId,
  TRpcMessageData        * pxWriteData,
  uint32_t                 xReqId,
  char                     xIsNotification
)
{
  int                  status = 0;
  uint32_t             serviceId;
  TMsgBuf_serviceDescriptor const  * pServiceDescriptor;

  pServiceDescriptor = (TMsgBuf_serviceDescriptor const *)xServiceHandle;

  if (pxRpcSocketHandle == NULL)
  {
    APP_RPC_report_error ("Illegal NULL service handler");
    return RPC_STATUS_ILLEGAL_PARAMETER;
  }

  status = findServiceId (pxRpcSocketHandle, pServiceDescriptor, &serviceId);
  if (status) return RPC_STATUS_ILLEGAL_PARAMETER;

  /* Check if the RPC method index exists and get its parameters methods */
  if (xMethodId >= (uint32_t)pServiceDescriptor->n_methods)
  {
    APP_RPC_report_error ("Unknown call method");
    return RPC_STATUS_ILLEGAL_PARAMETER;
  }

  pxWriteData->pRpcSocketHnd = pxRpcSocketHandle;   /* socket descriptor */
  pxWriteData->rpcHandler  = xRpcHandler;
  pxWriteData->pMsg        = pxInMsg;

  /* Build the associated RPC stream header */
  pxWriteData->rpcBufHeader.rpcMagicId     = RPC_MAGIC_VALUE_ID;  /* RPC msg buffer header */
  pxWriteData->rpcBufHeader.rpcServiceId   = serviceId;
  pxWriteData->rpcBufHeader.methodIdx      = xMethodId;
  pxWriteData->rpcBufHeader.rpcStatus      = RPC_STATUS_NO_ERROR;
  pxWriteData->rpcBufHeader.rpc_msbBuf_len = 0;
  pxWriteData->rpcBufHeader.requestIdx     = xReqId;

  pxWriteData->pRpcServiceMethodDesc = &pServiceDescriptor->pMethods[xMethodId];

  if (xIsNotification) pxWriteData->rpcBufHeader.methodIdx |= RPC_METHOD_NOTIFICATION_FLAGMASK;

#if defined(RPC_TRACE_CALL_ENABLE) && (RPC_TRACE_CALL_ENABLE != 0)
  {
    char * pTraceText = (char*)MSGBUF_SYS_malloc(1024);

    if (xIsNotification)
      MSGBUF_SYS_strcpy (pTraceText, "[RPC notify]: Method name: \"");
    else
      MSGBUF_SYS_strcpy (pTraceText, "[RPC call]: Method name: \"");

    MSGBUF_SYS_strcat (pTraceText, pxWriteData->pRpcServiceMethodDesc->pName);
    MSGBUF_SYS_strcat (pTraceText, "\"");
    APP_RPC_report_trace (pTraceText);
    if (pTraceText) MSGBUF_SYS_free (pTraceText);
    pTraceText = NULL;
  }
#endif

  return RPC_STATUS_NO_ERROR;
}


/* Send a RPC message accross a socket
 *
 * This lowel function converts an RPC message into a "msgbuf" serial
 * data structure and send it to a remote application via a the communication
 * channel.
 */
TRpc_status msgbuf_rpc_send
(
  TRpcSocketHnd         * pxRpcSocketHnd,
  const TRpcBufHeader   * pxRpcBufHeader,
  TMsgBuf_message const * pxMsg
)
{
  size_t          respLen = 0;
  size_t          len;
  TRpcBufHeader   rpcBufHeader;
  TRpcBufHeader * pRpcBufHeader;
  uint8_t       * pAllocatedBuffer = NULL;

  /* By default, use the default RPC header holder */
  pRpcBufHeader = &rpcBufHeader;

  /* If there is a message to send */
  if (pxMsg)
  {
    /* Serialize the message content in a buffer */
    respLen = msgbuf_size_message (pxMsg);
    if (respLen > 0)
    {
      pAllocatedBuffer = (uint8_t*)MSGBUF_SYS_malloc(respLen + sizeof(TRpcBufHeader));
      if (pAllocatedBuffer)
      {
        uint8_t * pEnd;
        pRpcBufHeader = (TRpcBufHeader *)pAllocatedBuffer;
        pEnd = pAllocatedBuffer + respLen + sizeof(TRpcBufHeader);
        len = msgbuf_rpack_message (pxMsg, &pEnd);
      }
      else
      {
        /* Allocation error here */
        APP_RPC_report_error ("Allocation failure");
        respLen = 0;
        return RPC_STATUS_MALLOC_ERROR;
      }
    }
  }

  /* Convert the RPC header into little endian for transport streaming */
  pRpcBufHeader->rpcMagicId     = uint32_from_le (pxRpcBufHeader->rpcMagicId);
  pRpcBufHeader->rpcServiceId   = uint32_from_le (pxRpcBufHeader->rpcServiceId);
  pRpcBufHeader->methodIdx      = uint32_from_le (pxRpcBufHeader->methodIdx);
  pRpcBufHeader->rpc_msbBuf_len = uint32_from_le ((uint32_t)respLen);
  pRpcBufHeader->requestIdx     = uint32_from_le (pxRpcBufHeader->requestIdx);
  pRpcBufHeader->rpcStatus      = uint32_from_le (pxRpcBufHeader->rpcStatus);

#if defined(RPC_DEBUG_PRINT_SEND_BUFFER) && (RPC_DEBUG_PRINT_SEND_BUFFER != 0)
  {
    int i;

    printf ("\nSend message:");
    for (i=0; i < (int)(sizeof(TRpcBufHeader) + respLen); i++)
    {
      if (!(i%16)) printf ("\n");
      printf ("%02X, ", (int)((uint8_t*)pRpcBufHeader)[i]);
    }
    printf ("\n");
  }
#endif

  /* write the RPC header into the socket */
  len = pxRpcSocketHnd->write (
    pxRpcSocketHnd->fd,
    pRpcBufHeader,
    sizeof(TRpcBufHeader) + respLen);

  if (len < sizeof(TRpcBufHeader) + respLen) return RPC_STATUS_CONNECTION_ERROR;

  if (pAllocatedBuffer) MSGBUF_SYS_free (pAllocatedBuffer);
  /* pAllocatedBuffer = NULL; */

  return RPC_STATUS_NO_ERROR;
}


/* RPC request handler of the RPC service
 *
 * Only treat one RPC message call at once
 */
TRpc_status msgbuf_rpc_recieve
(
  TRpcMessageData    * pxRpcReadData,
  TMsgBuf_rpcHandler   xRpcHandler
)
{
  int             len;
  int             status = 0;
  TRpc_status     rpcStatus = RPC_STATUS_NO_ERROR;
  uint32_t        method = 0;
  uint8_t       * pInputMessage = NULL;
  uint8_t       * pInputBuffer  = NULL;
  uint32_t        inputBufferSize = 0;
  TRpcSocketHnd * pRpcSocketHnd = pxRpcReadData->pRpcSocketHnd;
  TRpcBufHeader   rpcBufHeader;

  const TMsgBuf_messageDescriptor * pMessageDesc = NULL;
  TMsgBuf_methodDescriptor const  * pRpcMethodDesc = NULL;
  TMsgBuf_serviceDescriptor const * pServiceDesc   = NULL;

  pxRpcReadData->pMsg       = NULL;
  pxRpcReadData->rpcHandler = xRpcHandler;

  /* Read the RPC-based connection header data */
  len = _readPacket (
    pRpcSocketHnd,
    pxRpcReadData->rpcHandler,
    &rpcBufHeader,
    sizeof(TRpcBufHeader),
    1 );

  /* If RPC communication breakdown occurs */
  if (len < 0)
  {
    APP_RPC_report_info ("Connection lost");
    return RPC_STATUS_CONNECTION_ERROR;
  }
  
  /* If there is no new incoming msg (timout) */
  else if (len == 0)
  {
  	return RPC_STATUS_MSG_READ_TIMEOUT;
  }


#if defined(RPC_DEBUG_PRINT_SEND_BUFFER) && (RPC_DEBUG_PRINT_SEND_BUFFER != 0)
  {
    int i;
    unsigned char * pChar = (unsigned char*)&rpcBufHeader;

    printf ("\nReceived message header:");
    for (i=0; i < sizeof(TRpcBufHeader); i++)
    {
      if (!(i % 16)) printf ("\n");
      printf ("%02X, ", (int)((uint8_t*)pChar)[i]);
    }
    printf ("\n");
  }
#endif


  /* Convert the RPC buffer header into local machine endian */
  pxRpcReadData->rpcBufHeader.rpcMagicId     = uint32_from_le (rpcBufHeader.rpcMagicId);
  pxRpcReadData->rpcBufHeader.rpcServiceId   = uint32_from_le (rpcBufHeader.rpcServiceId);
  pxRpcReadData->rpcBufHeader.methodIdx      = uint32_from_le (rpcBufHeader.methodIdx);
  pxRpcReadData->rpcBufHeader.rpc_msbBuf_len = uint32_from_le (rpcBufHeader.rpc_msbBuf_len);
  pxRpcReadData->rpcBufHeader.requestIdx     = uint32_from_le (rpcBufHeader.requestIdx);
  pxRpcReadData->rpcBufHeader.rpcStatus      = uint32_from_le (rpcBufHeader.rpcStatus);

  /* Check the RPC-based connection magic number */
  if (pxRpcReadData->rpcBufHeader.rpcMagicId != RPC_MAGIC_VALUE_ID)
  {
    pRpcSocketHnd->isRpcConnectionLost = RPC_STATUS_CONNECTION_ERROR;
    return RPC_STATUS_CONNECTION_ERROR;
  }

  status = findServiceDescriptor (
    pRpcSocketHnd,
    pxRpcReadData->rpcBufHeader.rpcServiceId,
    &pServiceDesc);

  if (status)
  {
    APP_RPC_report_error ("Unknown service ID");
    return RPC_STATUS_CONNECTION_ERROR;
  }

  method = pxRpcReadData->rpcBufHeader.methodIdx & ~(RPC_METHOD_CALL_RESPONSE_FLAGMASK | RPC_METHOD_NOTIFICATION_FLAGMASK);

  /* Check if the RPC method index exists and get its parameters methods */
  if (method >= (uint32_t)pServiceDesc->n_methods)
  {
    APP_RPC_report_error ("Unknown call method");
    return RPC_STATUS_CONNECTION_ERROR;
  }

  pRpcMethodDesc = pxRpcReadData->pRpcServiceMethodDesc = &pServiceDesc->pMethods[method];

  inputBufferSize = pxRpcReadData->rpcBufHeader.rpc_msbBuf_len;
  if (inputBufferSize)
  {
    /* Allocate a data buffer for the RPC parameters */
    pInputBuffer = (uint8_t*)MSGBUF_SYS_malloc(inputBufferSize);
    if (!pInputBuffer)
    {
      APP_RPC_report_error ("Allocation failure");
      return RPC_STATUS_MALLOC_ERROR;
    }

    /* Read the packed data of this RPC request and put it in RAM buffer */
    len = _readPacket (
      pRpcSocketHnd,
      pxRpcReadData->rpcHandler,
      pInputBuffer,
      inputBufferSize,
      0 );

#if defined(RPC_DEBUG_PRINT_SEND_BUFFER) && (RPC_DEBUG_PRINT_SEND_BUFFER != 0)
  {
    int i;
    unsigned char * pChar = (unsigned char*)pInputBuffer;

    printf ("\nReceived message body:");
    for (i=0; i < inputBufferSize; i++)
    {
      if (!(i % 16)) printf ("\n");
      printf ("%02X, ", (int)((uint8_t*)pChar)[i]);
    }
    printf ("\n");
  }
#endif

    if (len < (int)inputBufferSize)
    {
      MSGBUF_SYS_free (pInputBuffer);
      return RPC_STATUS_CONNECTION_ERROR;
    }

    if (MSGBUF_RPC_isResponse(&pxRpcReadData->rpcBufHeader))
      pMessageDesc = pRpcMethodDesc->pOutput;
    else pMessageDesc = pRpcMethodDesc->pInput;

    pxRpcReadData->pMsg  = (TMsgBuf_message*)MSGBUF_SYS_malloc (pMessageDesc->sizeof_message);

    if (pxRpcReadData->pMsg == NULL)
    {
      APP_RPC_report_error ("Allocation failure");
      rpcStatus = RPC_STATUS_MALLOC_ERROR;
    }
    else
    {
      int len = 0;

      pMessageDesc->message_init (pxRpcReadData->pMsg, pMessageDesc);

      /* Unpack input message */
      len = msgbuf_unpack_message_content (
        pMessageDesc,
        pxRpcReadData->pMsg,
        pInputBuffer,
        pInputBuffer + inputBufferSize );

      if (len < 0)
      {
        MSGBUF_SYS_free (pxRpcReadData->pMsg);
        pxRpcReadData->pMsg = NULL;
        rpcStatus = RPC_STATUS_MESSAGE_NOT_INITIALIZED;
      }
    }
  }

  /* Free the input RAM buffer containing the RPC input parameter here,
   * since it will no more be used later on. */
  if (pInputMessage) MSGBUF_SYS_free (pInputMessage);

  return RPC_STATUS_NO_ERROR;
}



/* Execute a RPC request associated to a RPC remote call.
 * Associated paramter is provided as a RAM buffer containing
 * msgbuf packed format.
 *
 * Note that is function may be called in other context as the
 * one that take out the msgbuf from the input socket stream
 */
TRpc_status msgbuf_rpc_execute
(
  TRpcMessageData * pxRpcReadData
)
{
  uint32_t        status_code;
  size_t          respLen;
  TRpc_status     rpcStatus = RPC_STATUS_NO_ERROR;

  TMsgBuf_methodDescriptor const * pRpcMethodDesc;
  TMsgBuf_message                * pOutMsg = NULL;

  /* Get the RPC method descriptor */
  pRpcMethodDesc = pxRpcReadData->pRpcServiceMethodDesc;

  if ((pRpcMethodDesc->pOutput->n_fields) &&
      !(pxRpcReadData->rpcBufHeader.methodIdx & RPC_METHOD_NOTIFICATION_FLAGMASK))
  {
    /* Build/init the associated RPC output message */
    pOutMsg = (TMsgBuf_message*)MSGBUF_SYS_malloc (pRpcMethodDesc->pOutput->sizeof_message);
    if (pOutMsg == NULL)
    {
      APP_RPC_report_error ("Allocation failure");
      rpcStatus = RPC_STATUS_MALLOC_ERROR;
    }
    else pRpcMethodDesc->pOutput->message_init (pOutMsg, pRpcMethodDesc->pOutput);
  }

  if (rpcStatus == RPC_STATUS_NO_ERROR)
  {

#if defined(RPC_TRACE_EXEC_ENABLE) && (RPC_TRACE_EXEC_ENABLE != 0)
    char * pTraceText = NULL;

    pTraceText = (char*)MSGBUF_SYS_malloc(1024);
    if (pxRpcReadData->rpcBufHeader.methodIdx & RPC_METHOD_NOTIFICATION_FLAGMASK)
      MSGBUF_SYS_strcpy (pTraceText, "[RPC execute notification]: Method name: \"");
    else
      MSGBUF_SYS_strcpy (pTraceText, "[RPC execute call]: Method name: \"");

    MSGBUF_SYS_strcat (pTraceText, pRpcMethodDesc->pName);
    MSGBUF_SYS_strcat (pTraceText, "\"");
    APP_RPC_report_trace (pTraceText);
#endif

    /* Execute the RPC method */
    status_code = pRpcMethodDesc->rpcFctEntry (
      pxRpcReadData->rpcHandler,
      pxRpcReadData->pMsg,
      &pOutMsg );

    {
#if defined(RPC_TRACE_EXEC_ENABLE) && (RPC_TRACE_EXEC_ENABLE != 0)
      if (pxRpcReadData->rpcBufHeader.methodIdx & RPC_METHOD_NOTIFICATION_FLAGMASK)
        MSGBUF_SYS_strcpy (pTraceText, "[RPC execute notification ended]: Method name: \"");
      else
        MSGBUF_SYS_strcpy (pTraceText, "[RPC execute call return]: Method name: \"");

      MSGBUF_SYS_strcat (pTraceText, pRpcMethodDesc->pName);
      MSGBUF_SYS_strcat (pTraceText, "\"");
      APP_RPC_report_trace (pTraceText);

      if (pTraceText) MSGBUF_SYS_free (pTraceText);
      pTraceText = NULL;
#endif
   }
  }

  /* Deallocate the input message here, since it will no more used later one */
  if (pxRpcReadData->pMsg)
  {
    msgbuf_genericMessageDeallocate (pxRpcReadData->pMsg);
    pxRpcReadData->pMsg = NULL;
  }

  if (rpcStatus == RPC_STATUS_NO_ERROR)
  {
    if (!(pxRpcReadData->rpcBufHeader.methodIdx & RPC_METHOD_NOTIFICATION_FLAGMASK))
    {
      /* Get the packed buffer size associated to the output message to return back */
      if (pOutMsg) respLen = msgbuf_size_message (pOutMsg);
      else respLen = 0;

      /* Update the RPC header for responding back to the RPC call */
      pxRpcReadData->rpcBufHeader.rpc_msbBuf_len = (uint32_t)respLen;
      pxRpcReadData->rpcBufHeader.rpcStatus      = rpcStatus;

      /* Indicates that this is a method response */
      pxRpcReadData->rpcBufHeader.methodIdx |= RPC_METHOD_CALL_RESPONSE_FLAGMASK;

      /* Send the reponse (output message) back to the RPC caller */
      rpcStatus = msgbuf_rpc_send (
        pxRpcReadData->pRpcSocketHnd,
        &pxRpcReadData->rpcBufHeader,
        pOutMsg );
    }
  }

  /* Deallocate the output message here */
  /* PS: Note that this implementation absolutely requires that
  * potential nested messages (within the output message) should
  * dynamically be created by the method execution routine */
  if (pOutMsg) msgbuf_genericMessageDeallocate (pOutMsg);

  return rpcStatus;
}


/* Post a RPC async notification.
 *
 * Calling this function is only reserved for notification that
 * does not requires execution of the notification before returning
 * back from this function.
 *
 * Calling this function is only reserve for RPC method that does
 * not have any output data.
 *
 */
TRpc_status msgbuf_rpc_notify
(
  TRpcSocketHnd          * pxRpcSocketHandle,
  TMsgBuf_rpcHandler       xRpcHandler,
  const TMsgBuf_message  * pxInMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId
)
{
  TRpc_status          rpcStatus;
  TRpcMessageData      rpcWriteData;

  rpcStatus = msgbuf_rpc_build_callHeader (
    pxRpcSocketHandle,
    xRpcHandler,
    (TMsgBuf_message*)pxInMsg,
    xServiceHandle,
    xMethodId,
    &rpcWriteData,
    0,
    1 );

  if (rpcStatus != RPC_STATUS_NO_ERROR) return rpcStatus;

  /* Effectivelly send the RPC call (and data) to the remote server */
  rpcStatus = msgbuf_rpc_send (
    pxRpcSocketHandle,
    &rpcWriteData.rpcBufHeader,
    pxInMsg );

  return rpcStatus;
}


/* */
int msgbuf_rpc_isResponseOf
(
  TRpcMessageData * pxRpcReadData,
  TRpcMessageData * pxRpcWriteData
)
{
  if ((pxRpcReadData->rpcBufHeader.rpcServiceId == pxRpcWriteData->rpcBufHeader.rpcServiceId)                            &&
      (MSGBUF_RPC_getMethodId (&pxRpcReadData->rpcBufHeader) == MSGBUF_RPC_getMethodId (&pxRpcWriteData->rpcBufHeader))  &&
      (pxRpcReadData->rpcBufHeader.requestIdx    == pxRpcWriteData->rpcBufHeader.requestIdx ))
   return 1;
  else return 0;
}


/* */
int msgbuf_rpc_initHandle
(
  TRpcSocketHnd               * pxSocketHandle,
  void                        * xFd,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TRpcWrite_cbfct               xWrite_cbfct,
  TRpcRead_cbfct                xRead_cbfct
)
{
  int i;

  if (pxServiceSet)
  {
    pxSocketHandle->pRpcServiceDescSet = (TRpcServiceHnd*)MSGBUF_SYS_malloc(sizeof(TRpcServiceHnd) * xServiceNumber);
    if (pxSocketHandle->pRpcServiceDescSet == NULL)
    {
      APP_RPC_report_error ("Allocation failure");
      return -1;
    }
    pxSocketHandle->rpcServiceHandleNumber = xServiceNumber;
  }
  else
  {
    pxSocketHandle->rpcServiceHandleNumber = 0;
    pxSocketHandle->pRpcServiceDescSet = NULL;
  }

  for (i=0; i < pxSocketHandle->rpcServiceHandleNumber; i++)
  {
    pxSocketHandle->pRpcServiceDescSet[i].rpcServiceId = i;
    pxSocketHandle->pRpcServiceDescSet[i].rpcService = *pxServiceSet[i];
  }

  pxSocketHandle->magicNumber         = RPC_HANDLE_MAGIC_NUMBER;
  pxSocketHandle->write               = xWrite_cbfct;
  pxSocketHandle->read                = xRead_cbfct;
  pxSocketHandle->fd                  = xFd;
  pxSocketHandle->isRpcConnectionLost = RPC_STATUS_NO_ERROR;

  return 0;
}


/* */
void msgbuf_rpc_terminateHandle
(
  TRpcSocketHnd * pxSocketHandle
)
{
  if (pxSocketHandle == NULL) return;

  if (pxSocketHandle->magicNumber != RPC_HANDLE_MAGIC_NUMBER) return;

  pxSocketHandle->magicNumber = 0;
  if (pxSocketHandle->pRpcServiceDescSet) MSGBUF_SYS_free(pxSocketHandle->pRpcServiceDescSet);
  pxSocketHandle->pRpcServiceDescSet = NULL;
}


/* */
int msgbuf_rpc_getServiceHandleSet
(
  TMsgBuf_rpcHandler    xRpcHandle,
  TRpcServiceHnd     ** pxRpcServiceHandleSet
)
{
  TRpcSocketHnd * pRpcSocketHnd;
  pRpcSocketHnd = (TRpcSocketHnd*)xRpcHandle;

  if (pRpcSocketHnd == NULL) return -1;
  if (pRpcSocketHnd->magicNumber != RPC_HANDLE_MAGIC_NUMBER) return -1;

  if (pxRpcServiceHandleSet) *pxRpcServiceHandleSet = pRpcSocketHnd->pRpcServiceDescSet;
  return pRpcSocketHnd->rpcServiceHandleNumber;
}


/*****************************************************************************
 * Static function implementation
 ****************************************************************************/


/* */
static int findServiceId
(
  TRpcSocketHnd                    * pxRpcSockHandle,
  TMsgBuf_serviceDescriptor const  * pxServiceDescriptor,
  uint32_t                         * pxServiceId
)
{
  int i;

  if (pxServiceDescriptor == (TMsgBuf_serviceDescriptor const*)gRpcServiceHandle_rpcctrl)
  {
    *pxServiceId = 0xFFFFFFF0;
    return 0;
  }

  for (i=0; pxRpcSockHandle->rpcServiceHandleNumber; i++)
  {
    if ((TMsgBuf_serviceDescriptor const *)pxRpcSockHandle->pRpcServiceDescSet[i].rpcService == pxServiceDescriptor)
    {
      *pxServiceId = pxRpcSockHandle->pRpcServiceDescSet[i].rpcServiceId;
      return 0;
    }
  }
  return -1;
}


/* */
static int findServiceDescriptor
(
  TRpcSocketHnd                    * pxRpcSockHandle,
  uint32_t                           xServiceId,
  TMsgBuf_serviceDescriptor const ** pxServiceDescriptor
)
{
  int i;

  if (xServiceId == 0xFFFFFFF0)
  {
    *pxServiceDescriptor = (TMsgBuf_serviceDescriptor const*)gRpcServiceHandle_rpcctrl;
    return 0;
  }

  for (i=0; i < pxRpcSockHandle->rpcServiceHandleNumber; i++)
  {
    if (pxRpcSockHandle->pRpcServiceDescSet[i].rpcServiceId == xServiceId)
    {
      *pxServiceDescriptor = (TMsgBuf_serviceDescriptor const *)pxRpcSockHandle->pRpcServiceDescSet[i].rpcService;
      return 0;
    }
  }
  return -1;
}



static uint32_t uint32_from_le (uint32_t xValue)
{
  uint32_t  result = 0;
  uint8_t * pByte = (uint8_t*)&result;
  int i;

  for (i = 0; i < (int)sizeof(uint32_t); i++)
  {
    pByte[i] = (xValue & 0xFF);
    xValue >>= 8;
  }

  return result;
}


/* */
static int _readPacket
(
  TRpcSocketHnd      * pxRpcSocketHandler,
  TMsgBuf_rpcHandler   xRpcHandler,
  void               * pxBuffer,
  int                  xDataSize,
  int                  xIsRpcMsgHeader
)
{
  int    status;
  int    remSize = xDataSize;
  char * pBuf = (char*)pxBuffer;

  while (remSize > 0)
  {
    status = pxRpcSocketHandler->read (
      pxRpcSocketHandler->fd,
      pBuf,
      remSize );

    /* If there is a fatal error in RPC communication */
    if ((status == -1) ||
    	  ((status == 0) && ((remSize != xDataSize) || !xIsRpcMsgHeader)))
    {
      pxRpcSocketHandler->isRpcConnectionLost = RPC_STATUS_CONNECTION_ERROR;
      return -1;
    }
    
    /* If a timeout occurs when no incoming messsage have been started */
    /* Just return 0 to indicate a timeout */
    else if ((status == 0) && (remSize == xDataSize) && xIsRpcMsgHeader)
    { 
    	return 0;
    }

    pBuf += status;
    remSize -= status;
  }

  return (xDataSize);
}
