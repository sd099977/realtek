/**
 * File: $Id:$
 *
 *  This file implements some printout utilitily functions.
 *
 *  Copyright (c) 2013 Nagravision. All rights reserved.
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

#include "inc/rpc_ftrace.h"
#include "inc/msgbuf_strbuilder.h"
#include "inc/os/msgbuf_sys_mutex.h"


#ifdef  _NHT_RPC_TRACE_ON_

volatile int  _gRpcFtraceEnable        = 0;
volatile int  _gRpcFtraceEnableDefault = 0;

volatile TRpcFTraceCbFct  _gNht_ftraceCbFct = (TRpcFTraceCbFct)0;


static TMsgbuf_thread_mutex gNht_ftraceMutex   = (TMsgbuf_thread_mutex)0;
static volatile int         gNht_ftraceId       = 0;


/* */
void _rpc_ftrace_fct
(
  int                xCallId,
  TRpcFTraceType     xFTraceType,
  const char       * pxMessage
)
{
  if (RPC_FTRACE_IS_ENABLED() && _gNht_ftraceCbFct) _gNht_ftraceCbFct (xCallId, xFTraceType, pxMessage);
}


/* */
int rpc_ftrace_init
(
  TRpcFTraceCbFct xFTraceCbFct
)
{
  gNht_ftraceMutex = MSGBUF_SYS_createThreadMutex ();
  _gNht_ftraceCbFct = xFTraceCbFct;
  return 0;
}


/* */
int rpc_ftrace_terminate (void)
{
  _gRpcFtraceEnable = 0;
  _gNht_ftraceCbFct = (TRpcFTraceCbFct)0;

  if (gNht_ftraceMutex) MSGBUF_SYS_deleteThreadMutex (gNht_ftraceMutex);
  gNht_ftraceMutex  = (TMsgbuf_thread_mutex)0;
  return 0;
}


/* */
int rpc_ftrace_get_callId (void)
{
  int traceId;

  MSGBUF_SYS_acquireThreadMutex (gNht_ftraceMutex);
  traceId = gNht_ftraceId++;
  MSGBUF_SYS_releaseThreadMutex (gNht_ftraceMutex);

  return traceId;
}

#endif /* _NHT_RPC_TRACE_ON_ */
