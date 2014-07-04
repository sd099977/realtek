/**
 * File: $Id:$
 *
 *  This file implements the msgbuf RPC generic service functions.
 *
 *  Copyright (c) 2012-2014 Nagravision. All rights reserved.
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

#include "errno.h"
#include <fcntl.h>
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>
#include "src/os/posix/posix_rpc_service.h"
#include "inc/msgbuf_rpc_service.h"
#include "inc/app_rpc_report.h"
#include "src/rpc_rpcctrl_api.h"
#include "inc/avlset.h"
#include <stdio.h>

/*****************************************************************************
 * RPC transport stream specific definition
 ****************************************************************************/


/*****************************************************************************
 * RPC implementation specific type definition
 ****************************************************************************/

typedef struct SRpcHnd               TRpcHnd;

typedef struct SRpcPendingCallData    TRpcPendingCallData;
typedef struct SRpcPendingExecData    TRpcPendingExecData;
typedef struct SRpcPendingCallSet     TRpcPendingCallSet;
typedef struct SRpcPendingExecQueue   TRpcPendingExecQueue;


/* Simple double chaining structure */
typedef struct SDchain
{
  struct SDchain * pPrev;
  struct SDchain * pNext;

} TDchain;

/* RPC calls queue type definition */
struct SRpcPendingExecQueue
{
  TDchain           dchain;  /* Should be very first member of this structure */
  sem_t             _sem;    /* Semaphore for sem-based queue mechanism */
  pthread_mutex_t   _mutex;  /* Queue operation re-entrant mutext */
};


/* Pending RPC Set header descriptor */
/* This structure contains all data associated to pending RPC calls */
struct SRpcPendingCallSet
{
  TAVLSet           set;         /* Should be very first member of this structure */
  uint32_t          nextReqId;   /* Next unique request id */
  pthread_mutex_t   _mutex;      /* Queue operation re-entrant mutext */
};


/* RPC execution data structure */
/* This structure contains all data associated to a particular RPC call
 * to be executed. Such data structure is intended to be passed to
 * other thread context for execution of an RPC call */
struct SRpcPendingExecData
{
  TDchain           dchain;              /* Should be very first member of this structure */
  TRpcMessageData   rpcMessage;          /* socket descriptor */
  TRpcHnd         * pRpcHnd;
};


/* Pending RPC data structure */
/* This structure contains all data associated to a particular RPC call
 * that are pending on a call return. */
struct SRpcPendingCallData
{
  TAVLSet_iter      iter;              /* Should be very first member of this structure */
  TRpcMessageData   rpcMessage;        /* socket descriptor */
  TRpcHnd         * pRpcHnd;
  sem_t             _sem;              /* Queue operation re-entrant mutext */
};


/* RPC socket handler structure definition */
/* This handler holds all information relative an RPC connection */
struct SRpcHnd
{
  TRpcSocketHnd          rpcSocketHnd;
  TRpcPendingCallSet     rpcCallSet;
  TRpcPendingExecQueue   rpcPendingExecQueue;
  int                    strategyId;
  sem_t                  _rxBarrier;
  void                 * pPrivateData;
};


/* */
static int compareReqId
(
  TAVLSet_iter * pxIter1,
  TAVLSet_iter * pxIter2
);


static TRpcHnd * pgCurRpcHandle = NULL;


/*****************************************************************************/
/*                                                                           */
/* Static function prototype definition                                      */
/*                                                                           */
/*****************************************************************************/


/* */
static void * rpc_independent_exec_thread_main (
  void * pxArg );


/* */
static int process_rpc_independent_execution (
  TRpcPendingExecData * pxRpcExecData );


/* */
static void * rpc_sync_processing_thread_main (
  void * pxArg );


/*****************************************************************************/
/*                                                                           */
/* Public function implementation                                            */
/*                                                                           */
/*****************************************************************************/



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
  TRpcHnd             * pRpcHnd;
  TRpc_status           rpcStatus;
  TRpcSocketHnd       * pRpcSocketHnd;
  TRpcPendingCallData * pPendingCallData;
  uint32_t              reqId;

  TMsgBuf_serviceDescriptor const  * pServiceDescriptor;

  if (pxOutMsg) *pxOutMsg = NULL;

  if (xRpcHandler == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandler;

  if (pRpcHnd == NULL)
  {
    /* APP_RPC_report_error ("Illegal NULL connection handle"); */
    return RPC_STATUS_ILLEGAL_PARAMETER;
  }

  pServiceDescriptor = (TMsgBuf_serviceDescriptor const *)xServiceHandle;

  pRpcSocketHnd = &pRpcHnd->rpcSocketHnd;

  /* Initialize a pending call structure */
  pPendingCallData = (TRpcPendingCallData*)MSGBUF_SYS_malloc(sizeof(TRpcPendingCallData));
  if (pPendingCallData == NULL) return RPC_STATUS_MALLOC_ERROR;

  AVLSet_iterInit (&pPendingCallData->iter);
  /* Initialize the context locker associated this RPC call */
  sem_init (&pPendingCallData->_sem, 0, 0);

  rpcStatus = msgbuf_rpc_build_callHeader (
    pRpcSocketHnd,
    pRpcHnd,
    (TMsgBuf_message*)pxInMsg,
    xServiceHandle,
    xMethodId,
    &pPendingCallData->rpcMessage,
    0, /* By default set 0, will overwrite it afterward */
    0 );

  if (rpcStatus != RPC_STATUS_NO_ERROR)
  {
    MSGBUF_SYS_free (pPendingCallData);
    return rpcStatus;
  }

  pthread_mutex_lock (&pRpcHnd->rpcCallSet._mutex);

  /* Select a unique request id and put this call on pending call list */
  reqId = pRpcHnd->rpcCallSet.nextReqId++;
  pPendingCallData->rpcMessage.rpcBufHeader.requestIdx = reqId;

  /* Put this RPC call request in the pending RPC call list associated to this socked
   * handler. */

  AVLSet_insert (&pRpcHnd->rpcCallSet.set, &pPendingCallData->iter);

  pthread_mutex_unlock (&pRpcHnd->rpcCallSet._mutex);

  /* Effectivelly send the RPC call (and data) to the remote server */
  rpcStatus = msgbuf_rpc_send (
    pRpcSocketHnd,
    &pPendingCallData->rpcMessage.rpcBufHeader,
    pxInMsg );

  if (rpcStatus != RPC_STATUS_NO_ERROR)
  {
    /* If not sent, extract this call from the pending list */
    pthread_mutex_lock (&pRpcHnd->rpcCallSet._mutex);
    AVLSet_remove (&pRpcHnd->rpcCallSet.set, &pPendingCallData->iter);
    pthread_mutex_unlock (&pRpcHnd->rpcCallSet._mutex);

    MSGBUF_SYS_free (pPendingCallData);
    return rpcStatus;
  }

  /* Block the caller context of this function on RPC response */
  sem_wait (&pPendingCallData->_sem);

#if defined(RPC_TRACE_CALL_ENABLE) && (RPC_TRACE_CALL_ENABLE != 0)
  {
    char * pTraceText = (char*)MSGBUF_SYS_malloc(1024);
    MSGBUF_SYS_strcpy (pTraceText, "[RPC call return]: Method name: \"");
    MSGBUF_SYS_strcat (pTraceText, pPendingCallData->rpcMessage.pRpcServiceMethodDesc->pName);
    MSGBUF_SYS_strcat (pTraceText, "\"");
    APP_RPC_report_trace (pTraceText);
    if (pTraceText) MSGBUF_SYS_free (pTraceText);
    pTraceText = NULL;
  }
#endif

  rpcStatus = pPendingCallData->rpcMessage.rpcBufHeader.rpcStatus;
  if (pxOutMsg) *pxOutMsg = *(TMsgBuf_message * volatile *)&pPendingCallData->rpcMessage.pMsg;
  pPendingCallData->rpcMessage.pMsg = NULL;

  sem_destroy (&pPendingCallData->_sem);
  if (pPendingCallData) MSGBUF_SYS_free (pPendingCallData);

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
TRpc_status rpc_notify
(
  TMsgBuf_rpcHandler       xRpcHandler,
  const TMsgBuf_message  * pxInMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId
)
{
  TRpcHnd            * pRpcHnd;
  TRpcSocketHnd      * pRpcSocketHnd;
  TMsgBuf_serviceDescriptor const * pServiceDescriptor;
  TRpc_status           rpcStatus;

  if (xRpcHandler == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandler;

  if (pRpcHnd == NULL)
  {
    /* APP_RPC_report_error ("Illegal NULL connection handle"); */
    return RPC_STATUS_ILLEGAL_PARAMETER;
  }

  pServiceDescriptor = (TMsgBuf_serviceDescriptor const *)xServiceHandle;

  pRpcSocketHnd = &pRpcHnd->rpcSocketHnd;

  rpcStatus = msgbuf_rpc_notify (
    pRpcSocketHnd,
    pRpcHnd,
    pxInMsg,
    xServiceHandle,
    xMethodId );

  return rpcStatus;
}

/* */
TMsgBuf_rpcHandler pPosixRpcService_createHandle
(
  void                        * xFd,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TRpcWrite_cbfct               xWrite_cbfct,
  TRpcRead_cbfct                xRead_cbfct
)
{
  TRpcHnd * pRpcHnd = NULL;
  int             status = 0;

  /* Create a RPC socket handle */
  pRpcHnd = (TRpcHnd*)MSGBUF_SYS_malloc(sizeof(TRpcHnd));
  if (pRpcHnd == NULL)
  {
    APP_RPC_report_error ("Allocation failure");
    return (TMsgBuf_rpcHandler)NULL;
  }

  pRpcHnd->pPrivateData = NULL;

  status = msgbuf_rpc_initHandle (
    &pRpcHnd->rpcSocketHnd,
    xFd,
    xServiceNumber,
    pxServiceSet,
    xWrite_cbfct,
    xRead_cbfct );

  pgCurRpcHandle = pRpcHnd;

  AVLSet_init (&pRpcHnd->rpcCallSet.set, &compareReqId, 0);
  pRpcHnd->rpcCallSet.nextReqId = 0;
  pthread_mutex_init (&pRpcHnd->rpcCallSet._mutex, NULL);
  sem_init (&pRpcHnd->_rxBarrier, 0, 1);

  if (/* isSync */ 0)
  {
    pthread_attr_t  tattr;
    pthread_t       chld_thr;

    pRpcHnd->rpcPendingExecQueue.dchain.pPrev =
      pRpcHnd->rpcPendingExecQueue.dchain.pNext =
      &pRpcHnd->rpcPendingExecQueue.dchain;

    pthread_mutex_init (&pRpcHnd->rpcPendingExecQueue._mutex, NULL);
    sem_init (&pRpcHnd->rpcPendingExecQueue._sem, 0, 0);

    /* Create and initialize the execution thread of this RPC */
    status = pthread_attr_init(&tattr);

    status = pthread_create (
      &chld_thr,
      &tattr,
      &rpc_sync_processing_thread_main,
      (void*) pRpcHnd );

    if (!status) pthread_detach (chld_thr);
    else
    {
      APP_RPC_report_error ("Fail to create thread");
      return NULL;
    }
  }

  return pRpcHnd;
}


/* */
void posixRpcService_closeHandle
(
  TMsgBuf_rpcHandler xRpcHandle
)
{
  TRpcHnd * pRpcHnd = (TRpcHnd*)xRpcHandle;

  if (pRpcHnd == NULL) return;

  msgbuf_rpc_terminateHandle (&pRpcHnd->rpcSocketHnd);
  pgCurRpcHandle = NULL;
}


/* Main RPC service function */
void * posixRpcService_main
(
  TMsgBuf_rpcHandler xRpcHandler
)
{
  int        status;

  for (;;)
  {
    status = posixRpcService_serveOne (xRpcHandler);
    if (status < 0)
    {
      APP_RPC_report_info ("RPC synchronization lost");
      break;
    }
  }

  posixRpcService_abortPendingCalls (xRpcHandler);

  return (void*)0;
}


/* */
int posixRpcService_getFd
(
  TMsgBuf_rpcHandler    xRpcHandle,
  void               ** pxFd
)
{
  TRpcHnd             * pRpcHnd;

  if (xRpcHandle == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandle;

  if (pRpcHnd == NULL) return -1;

  if (pxFd) *pxFd = pRpcHnd->rpcSocketHnd.fd;
  return 0;
}


/* */
int posixRpcService_getPrivateData
(
  TMsgBuf_rpcHandler    xRpcHandle,
  void               ** pxPrivateData
)
{
  TRpcHnd             * pRpcHnd;

  if (xRpcHandle == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandle;

  if (pRpcHnd == NULL) return -1;

  if(pxPrivateData) *pxPrivateData = pRpcHnd->pPrivateData;
  return 0;
}


/* */
int posixRpcService_registerPrivateData
(
  TMsgBuf_rpcHandler    xRpcHandle,
  void                * pxPrivateData
)
{
  TRpcHnd             * pRpcHnd;

  if (xRpcHandle == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandle;

  if (pRpcHnd == NULL) return -1;

  pRpcHnd->pPrivateData = pxPrivateData;
  return 0;
}


/* */
int posixRpcService_rxBarrier_lock
(
  TMsgBuf_rpcHandler    xRpcHandle
)
{
  TRpcHnd             * pRpcHnd;

  if (xRpcHandle == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandle;

  if (pRpcHnd == NULL) return -1;

  sem_wait (&pRpcHnd->_rxBarrier);
  return 0;
}


/* */
int posixRpcService_rxBarrier_unlock
(
  TMsgBuf_rpcHandler    xRpcHandle
)
{
  TRpcHnd             * pRpcHnd;

  if (xRpcHandle == NULL) pRpcHnd = pgCurRpcHandle;
  else pRpcHnd = (TRpcHnd*)xRpcHandle;

  if (pRpcHnd == NULL) return -1;

  sem_post (&pRpcHnd->_rxBarrier);

  return 0;
}


static int compareReqId
(
  TAVLSet_iter * pxIter1,
  TAVLSet_iter * pxIter2
)
{
  TRpcPendingCallData * p1 = (TRpcPendingCallData*)pxIter1;
  TRpcPendingCallData * p2 = (TRpcPendingCallData*)pxIter2;

  return (p1->rpcMessage.rpcBufHeader.requestIdx - p2->rpcMessage.rpcBufHeader.requestIdx);

}

/*
 * RPC execution thread main function
 *
 * This is used when the RPC service is configured for
 * processing every RPC in a full asynchronous mode
 * (privilege option of the RPC service)
 */
static void * rpc_independent_exec_thread_main
(
  void * pxArg
)
{
  TRpc_status           rpcStatus;
  TRpcPendingExecData * pRpcExecCall;

  /* Extract the RPC execution data to be processed */
  pRpcExecCall = (TRpcPendingExecData*)pxArg;

  /* Execute the RPC function call */
  rpcStatus = msgbuf_rpc_execute (&pRpcExecCall->rpcMessage);

  /* Free the RPC execution data in any case before exiting
   * this RPC execution thread. */
  if (pRpcExecCall) MSGBUF_SYS_free (pRpcExecCall);
  pthread_exit ((void *)0);
  return NULL;
}


/* Force the execution of a particular RPC to run in a separated
 * thread context
 */
static int process_rpc_independent_execution
(
  TRpcPendingExecData * pxRpcExecData
)
{
  int              status = 0;
  pthread_attr_t   tattr;
  pthread_t        chld_thr;

  /* Create and initialize the execution thread of this RPC */
  status = pthread_attr_init(&tattr);

  status = pthread_create (
    &chld_thr,
    NULL,
    &rpc_independent_exec_thread_main,
    (void*)pxRpcExecData );

  if (!status)
  {
    pthread_detach (chld_thr);
  }
  else
  {
    APP_RPC_report_error ("Fail to create thread");
    status = -1;
  }
  return status;
}


/* Main thread function that executes all RPC in a serial way.
 *
 * This method is only used for RPC service that does not require
 * concurrent RPC execution (see RPC service strategy).
 */
static void * rpc_sync_processing_thread_main
(
  void * pxArg
)
{
  int                    status = 0;
  TRpc_status            rpcStatus;
  TRpcHnd              * pRpcHnd;
  TRpcPendingExecData  * pRpcExecData;
  TRpcPendingExecQueue * pExecQueue;

  pRpcHnd = (TRpcHnd*)pxArg;
  pExecQueue = &pRpcHnd->rpcPendingExecQueue;

  /* Loop RPC (serial) execution until death of the socket
   * connection. */
  do
  {
    pRpcExecData = NULL;

    /* Wait on a RPC to execute */
    status = sem_wait (&pExecQueue->_sem);

    /* Get the RPC data info */
    status = pthread_mutex_lock(&pExecQueue->_mutex);
    if (pExecQueue->dchain.pPrev != pExecQueue->dchain.pNext)
    {
      pRpcExecData = (TRpcPendingExecData*)pExecQueue->dchain.pNext;
      pRpcExecData->dchain.pNext->pPrev = pRpcExecData->dchain.pPrev;
      pRpcExecData->dchain.pPrev->pNext = pRpcExecData->dchain.pNext;
    }
    pthread_mutex_unlock(&pExecQueue->_mutex);

    /* Execute the RPC function */
    if (pRpcExecData)
    {
      rpcStatus = msgbuf_rpc_execute (&pRpcExecData->rpcMessage);
      /* Free the RPC input data in any case */
      MSGBUF_SYS_free (pRpcExecData);
      if (rpcStatus != RPC_STATUS_NO_ERROR) status = -1;
    }
    else status = -1;

  } while (status >= 0);

  pthread_exit ((void *)0);
  return ((void*)0);
}




/* RPC request handler of the RPC service
 *
 * Only treat one RPC message call at once
 */
int posixRpcService_serveOne
(
  TMsgBuf_rpcHandler xRpcHandler
)
{
  TRpcPendingCallData * pCurCallData;
  TRpcPendingExecData * pRpcExecData;
  int                   status = 0;
  TRpc_status           rpcStatus;
  TRpcHnd             * pRpcHnd = (TRpcHnd*)xRpcHandler;

  pRpcExecData = (TRpcPendingExecData*)MSGBUF_SYS_malloc(sizeof(TRpcPendingExecData));
  if (!pRpcExecData) return -1;

  pRpcExecData->rpcMessage.pRpcSocketHnd = &pRpcHnd->rpcSocketHnd;

  rpcStatus = msgbuf_rpc_recieve (&pRpcExecData->rpcMessage, xRpcHandler);

  if (rpcStatus != RPC_STATUS_NO_ERROR)
  {
    MSGBUF_SYS_free (pRpcExecData);

    if (rpcStatus == RPC_STATUS_MSG_READ_TIMEOUT) return 1;
    else return -1;
  }

  if (MSGBUF_RPC_isResponse(&pRpcExecData->rpcMessage.rpcBufHeader))
  {
    TAVLSet_iter        * pIter;
    TRpcPendingCallData   tmpPendingData;

    tmpPendingData.rpcMessage.rpcBufHeader.requestIdx =
      pRpcExecData->rpcMessage.rpcBufHeader.requestIdx;

    /* Scan all pending RPC requests in the RPC pending set */
    pthread_mutex_lock (&pRpcHnd->rpcCallSet._mutex);
    pIter = AVLSet_find (&pRpcHnd->rpcCallSet.set, &tmpPendingData.iter);
    if (pIter != AVLSet_end(&pRpcHnd->rpcCallSet.set))
      AVLSet_remove (&pRpcHnd->rpcCallSet.set, pIter);
    pthread_mutex_unlock (&pRpcHnd->rpcCallSet._mutex);

    if (pIter != AVLSet_end(&pRpcHnd->rpcCallSet.set))
    {
      pCurCallData = (TRpcPendingCallData*)pIter;
      pCurCallData->rpcMessage.pMsg = pRpcExecData->rpcMessage.pMsg;
      pCurCallData->rpcMessage.rpcBufHeader.rpcStatus = pRpcExecData->rpcMessage.rpcBufHeader.rpcStatus;
      pRpcExecData->rpcMessage.pMsg = NULL;

      /* Wakeup the RPC caller */
      sem_post (&pCurCallData->_sem);

      /* Rx Barrier */
      sem_wait (&pRpcHnd->_rxBarrier);
      sem_post (&pRpcHnd->_rxBarrier);
    }
    else
    {
      printf ("Unexpected response...\n");
#if defined(RPC_TRACE_CALL_ENABLE) && (RPC_TRACE_CALL_ENABLE != 0)
      {
        char * pTraceText = (char*)MSGBUF_SYS_malloc(1024);
        MSGBUF_SYS_strcpy (pTraceText, "[RPC unexpected call return]: Method name: \"");
        MSGBUF_SYS_strcat (pTraceText, pRpcExecData->rpcMessage.pRpcServiceMethodDesc->pName);
        MSGBUF_SYS_strcat (pTraceText, "\"");
        APP_RPC_report_error (pTraceText);
        if (pTraceText) MSGBUF_SYS_free (pTraceText);
        pTraceText = NULL;
      }
#endif

      if (pRpcExecData->rpcMessage.pMsg) msgbuf_genericMessageDeallocate (pRpcExecData->rpcMessage.pMsg);
      pRpcExecData->rpcMessage.pMsg = NULL;
    }

    MSGBUF_SYS_free (pRpcExecData);
    pRpcExecData = NULL;
  }

  /* if this is a RPC remote call */
  else
  {
    /* ServiceId = 0 is reserved for reporting!
     * As a main behavior, Notifications associated to ServiceId=0
     * shall be executed synchronously.
     * This behavior has been introduced in order to provide a mechanism
     * that preserves the report line ordering between client and server
     * (e.g: stdout/stderr reporting)
     * - Execution of a rpc notification execution associated to serviceId=0 shall
     *   be non-blocking. It shall never triggers any other call or notification back
     *   synchronously.
     * - Reporting rpc method shall all belong to serviceId=0 in order
     *   to ensure a proper ordering of the report.
     * - Acknoledging a report call associated to serviceId=0 is allowed.
     */
    if ((pRpcExecData->rpcMessage.rpcBufHeader.rpcServiceId == 0) &&
        MSGBUF_RPC_isNotification(&pRpcExecData->rpcMessage.rpcBufHeader))
    {
      msgbuf_rpc_execute (&pRpcExecData->rpcMessage);
      if (pRpcExecData) MSGBUF_SYS_free (pRpcExecData);
    }
    else
    {
      /* If the RPC service strategy is setup for full asynchronous
       * RPC execution */
      if (/* pxRpcHnd->strategyId == 0 */ 1)
      {
        status = process_rpc_independent_execution (pRpcExecData);
      }
      else
      {
        /* Pipe the RPC request to the RPC unique execution thread */
        status = pthread_mutex_lock(&pRpcHnd->rpcPendingExecQueue._mutex);

        pRpcExecData->dchain.pNext = &pRpcHnd->rpcPendingExecQueue.dchain;
        pRpcExecData->dchain.pPrev = pRpcHnd->rpcPendingExecQueue.dchain.pPrev;
        pRpcHnd->rpcPendingExecQueue.dchain.pPrev = &pRpcExecData->dchain;
        pRpcExecData->dchain.pPrev->pNext = &pRpcExecData->dchain;

        pthread_mutex_unlock(&pRpcHnd->rpcPendingExecQueue._mutex);

        status = sem_post (&pRpcHnd->rpcPendingExecQueue._sem);
      }
    }
  }

  return status;
}




/* Abort RPC response associated to a pending RPC request.
 *
 * If this response corresponds to a pending RPC request,
 * fill up the RPC output message and wake-up the caller
 * of the RPC requested.
 */
int posixRpcService_abortPendingCalls
(
  TMsgBuf_rpcHandler xRpcHandler
)
{
  TRpcPendingCallData * pCurCallData;
  TAVLSet_iter        * pIter;
  int                   counter = 0;
  TRpcHnd             * pRpcHnd = (TRpcHnd*)xRpcHandler;

  /* Scan all pending RPC requests in the RPC pending set */
  pthread_mutex_lock (&pRpcHnd->rpcCallSet._mutex);

  pIter = AVLSet_next (AVLSet_begin (&pRpcHnd->rpcCallSet.set));
  while (pIter != AVLSet_end(&pRpcHnd->rpcCallSet.set))
  {
    pCurCallData = (TRpcPendingCallData*)pIter;

    counter++;

    AVLSet_remove (&pRpcHnd->rpcCallSet.set, pIter);
    pCurCallData->rpcMessage.pMsg = NULL;

    /* Update the RPC header data for RPC caller */
    pCurCallData->rpcMessage.rpcBufHeader.rpcStatus = RPC_STATUS_CONNECTION_ERROR;
    pCurCallData->rpcMessage.rpcBufHeader.methodIdx |= RPC_METHOD_CALL_RESPONSE_FLAGMASK;

    pIter = AVLSet_next (AVLSet_begin (&pRpcHnd->rpcCallSet.set));

    /* Wakeup the RPC caller */
    sem_post (&pCurCallData->_sem);
  }

  pthread_mutex_unlock (&pRpcHnd->rpcCallSet._mutex);

  return counter;
}



