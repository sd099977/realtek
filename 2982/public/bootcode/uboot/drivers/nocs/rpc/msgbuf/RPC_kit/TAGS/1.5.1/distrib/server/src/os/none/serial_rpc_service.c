/**
 * File: $Id:$
 *
 *  This file implements the msgbuf RPC generic service functions.
 *
 *  Copyright (c) 2012_2014 Nagravision. All rights reserved.
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
#include "inc/msgbuf_rpc_service.h"
#include "inc/app_rpc_report.h"
#include "src/rpc_rpcctrl_api.h"
#include "inc/os/none/serial_rpc_service.h"
#include "inc/hndmng.h"


/*****************************************************************************
 * RPC transport stream specific definition
 ****************************************************************************/


/*****************************************************************************
 * RPC implementation specific type definition
 ****************************************************************************/

static TRpcSocketHnd * pgCurRpcHandle      = NULL;
static uint32_t        gNextReqId          = 0;
static volatile char   gServiceAbortStatus = 0;


/*****************************************************************************
 * Static function prototype definition
 ****************************************************************************/


/* Post a synchronous generic RPC call.
 *
 * The thread of the caller of this function is then blocked
 * until the RPC execution is completed on the remote machine.
 *
 * Potentially, provide back the OUTPUT parameters associated to
 * this method.
 *
 * Pre-requesite: 'pxOutMsg' should have allocated (and initialized)
 * prior to call the function.
 */
TRpc_status rpc_call
(
  TMsgBuf_rpcHandler       xRpcHandler,
  const TMsgBuf_message  * pxInMsg,
  TMsgBuf_message       ** pxOutMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId
)
{
  TRpc_status       rpcStatus;
  TRpcMessageData   rpcWriteData;
  TRpcSocketHnd   * pRpcHnd;

  if (xRpcHandler == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcSocketHnd*)xRpcHandler;

  if (pRpcHnd == NULL)
  {
    /* APP_RPC_report_error ("Illegal NULL connection handle"); */
    return RPC_STATUS_ILLEGAL_PARAMETER;
  }

  rpcStatus = msgbuf_rpc_build_callHeader (
    pRpcHnd,
    pRpcHnd,
    (TMsgBuf_message*)pxInMsg,
    xServiceHandle,
    xMethodId,
    &rpcWriteData,
    gNextReqId++,
    0 );

#if defined(RPC_TRACE_CALL_ENABLE) && (RPC_TRACE_CALL_ENABLE != 0)
  {
    char * pTraceText = NULL;

    pTraceText = (char*)MSGBUF_SYS_malloc(1024);
    sprintf (pTraceText, "[RPC call]: Method name: \"%s\"",rpcWriteData.pRpcServiceMethodDesc->pName);
    APP_RPC_report_trace (pTraceText);
    if (pTraceText) MSGBUF_SYS_free(pTraceText);
    pTraceText = NULL;
  }
#endif

  /* Effectivelly send the RPC call (and data) to the remote server */
  rpcStatus = msgbuf_rpc_send (
    pRpcHnd,
    &rpcWriteData.rpcBufHeader,
    pxInMsg );

  rpcWriteData.pMsg = NULL;

  if (rpcStatus == RPC_STATUS_NO_ERROR)
  {
    do
    {
      rpcStatus = serialRpcService_singleProcess (pRpcHnd, &rpcWriteData);
    } while (rpcStatus == RPC_STATUS_MSG_READ_TIMEOUT);

#if defined(RPC_TRACE_CALL_ENABLE) && (RPC_TRACE_CALL_ENABLE != 0)
    {
      char * pTraceText = (char*)MSGBUF_SYS_malloc(1024);

      sprintf (pTraceText, "[RPC call return]: Method name: \"%s\"", rpcWriteData.pRpcServiceMethodDesc->pName);
      APP_RPC_report_trace (pTraceText);
      if (pTraceText) MSGBUF_SYS_free (pTraceText);
      pTraceText = NULL;
    }
#endif

    if (pxOutMsg)
    {
      *pxOutMsg = rpcWriteData.pMsg;
      rpcWriteData.pMsg = NULL;
    }

    if (rpcStatus == RPC_STATUS_NO_ERROR) rpcStatus = rpcWriteData.rpcBufHeader.rpcStatus;
  }

  if (rpcWriteData.pMsg) msgbuf_genericMessageDeallocate (rpcWriteData.pMsg);

  return rpcStatus;
}


/* */
TRpc_status rpc_notify
(
  TMsgBuf_rpcHandler      xRpcHandler,
  const TMsgBuf_message * pxInMsg,
  TMsgBuf_serviceHandle   xServiceHandle,
  uint32_t                xMethodId
)
{
  TRpc_status     rpcStatus;
  TRpcSocketHnd * pRpcHnd;

  if (xRpcHandler == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcSocketHnd*)xRpcHandler;

  if (pRpcHnd == NULL)
  {
    /* APP_RPC_report_error ("Illegal NULL connection handle"); */
    return RPC_STATUS_ILLEGAL_PARAMETER;
  }

  rpcStatus = msgbuf_rpc_notify (
    pRpcHnd,
    pRpcHnd,
    pxInMsg,
    xServiceHandle,
    xMethodId );

  return rpcStatus;
}


/* */
int serialRpcService_start
(
  TMsgBuf_rpcHandler xRpcHandle
)
{
  TRpc_status     rpcStatus;
  TRpcSocketHnd * pHnd = (TRpcSocketHnd*)xRpcHandle;

  for (;;)
  {
    rpcStatus = serialRpcService_singleProcess (xRpcHandle, NULL);

    if (pHnd->isRpcConnectionLost)
    {
      hndmng_terminate ();
      pHnd->isRpcConnectionLost = 0;
    }

    if (gServiceAbortStatus) return 0;
  }
}


/* */
TMsgBuf_rpcHandler pSerialRpcService_createHandle
(
  void                        * pxFd,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TRpcWrite_cbfct               xWrite_cbfct,
  TRpcRead_cbfct                xRead_cbfct
)
{
  TRpcSocketHnd * pHnd = NULL;
  int             status = 0;

  /* Create a RPC socket handle */
  pHnd = (TRpcSocketHnd*)MSGBUF_SYS_malloc(sizeof(TRpcSocketHnd));
  if (pHnd == NULL)
  {
    APP_RPC_report_error ("Allocation failure");
    return (TMsgBuf_rpcHandler)NULL;
  }

  status = msgbuf_rpc_initHandle (
    pHnd,
    pxFd,
    xServiceNumber,
    pxServiceSet,
    xWrite_cbfct,
    xRead_cbfct );


  if (status)
  {
    MSGBUF_SYS_free (pHnd);
    pHnd = NULL;
  }

  pgCurRpcHandle = pHnd;
  return (TMsgBuf_rpcHandler)pHnd;
}


/* */
void serialRpcService_closeHandle
(
  TMsgBuf_rpcHandler xRpcHandle
)
{
  TRpcSocketHnd * pHnd = (TRpcSocketHnd*)xRpcHandle;

  if (pHnd == NULL) return;

  msgbuf_rpc_terminateHandle (pHnd);
  pgCurRpcHandle = NULL;
}


/* */
TRpc_status serialRpcService_singleProcess
(
  TMsgBuf_rpcHandler   xRpcHnd,
  TRpcMessageData    * pxRpcWriteData
)
{
  TRpc_status       rpcStatus = RPC_STATUS_NO_ERROR;
  TRpcMessageData * pRpcReadData;
  TRpcSocketHnd   * pRpcSocketHnd;

  pRpcSocketHnd = (TRpcSocketHnd*)xRpcHnd;

  pRpcReadData = (TRpcMessageData*)MSGBUF_SYS_malloc(sizeof(TRpcMessageData));
  if (pRpcReadData == NULL) return RPC_STATUS_MALLOC_ERROR;

  pRpcReadData->pRpcSocketHnd = pRpcSocketHnd;
  pRpcReadData->pMsg          = NULL;

  for (;;)
  {
    /* If the connection was marked as lost, drop the current processing */
    if (pRpcSocketHnd->isRpcConnectionLost)
    {
      rpcStatus = RPC_STATUS_CONNECTION_ERROR;
      break;
    }

    rpcStatus = msgbuf_rpc_recieve (
      pRpcReadData,
      pRpcSocketHnd);

    if (rpcStatus == RPC_STATUS_MSG_READ_TIMEOUT) break;

    /* If we detected a lost of connection, mark the connection as lost and */
    /* drop the current processing */
    else if (rpcStatus != RPC_STATUS_NO_ERROR)
    {
      pRpcSocketHnd->isRpcConnectionLost = 1;
      rpcStatus = RPC_STATUS_CONNECTION_ERROR;
      break;
    }

    /* if this is a RPC return call response */
    if (MSGBUF_RPC_isResponse(&pRpcReadData->rpcBufHeader))
    {
      if ((!pxRpcWriteData) || !msgbuf_rpc_isResponseOf (pRpcReadData, pxRpcWriteData))
      {
        rpcStatus = RPC_STATUS_CONNECTION_ERROR;
        break;
      }
      else
      {
        pxRpcWriteData->pMsg = pRpcReadData->pMsg;
        pRpcReadData->pMsg = NULL;
        pxRpcWriteData->rpcBufHeader.rpcStatus = pRpcReadData->rpcBufHeader.rpcStatus;
        rpcStatus = RPC_STATUS_NO_ERROR;
        break;
      }
    }
    else
    {
      rpcStatus = msgbuf_rpc_execute (pRpcReadData);
      if (rpcStatus != RPC_STATUS_NO_ERROR) break;

      if (pRpcReadData->pMsg) msgbuf_genericMessageDeallocate (pRpcReadData->pMsg);
      pRpcReadData->pMsg = NULL;
      continue;
    }
  }

  if (pRpcReadData)
  {
    if (pRpcReadData->pMsg) msgbuf_genericMessageDeallocate (pRpcReadData->pMsg);
    MSGBUF_SYS_free(pRpcReadData);
  }

  return rpcStatus;
}

/* */
void serialRpcService_terminate
(
  TMsgBuf_rpcHandler xRpcHandle
)
{
  gServiceAbortStatus = 1;
}
