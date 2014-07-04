/**
 * File: $Id:$
 *
 *  This file implements trace call reporting base functions.
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


#ifndef _RPC_CALL_TRACE_H_
#define _RPC_CALL_TRACE_H_


#ifdef __cplusplus
extern "C" {
#endif

#define _BCRPC(x) TRACE_##x


#if defined (NHT_RPC_TRACE_ENABLED) && (NHT_RPC_TRACE_ENABLED != 0)
#define _NHT_RPC_TRACE_ON_
#define _CRPC(x) TRACE_##x
#else
#undef _NHT_RPC_TRACE_ON_
#define _CRPC(x) x
#endif

/***************************************************************************/
/*                                                                         */
/*                         TYPE DEFINITIONS                                */
/*                                                                         */
/***************************************************************************/

/* */
typedef enum ERpcFTraceType
{
  RPC_FTRACE_ENTER_CLIENT_CALL,
  RPC_FTRACE_EXIT_CLIENT_CALL,
  RPC_FTRACE_ENTER_SERVER_CALL,
  RPC_FTRACE_EXIT_SERVER_CALL

} TRpcFTraceType;


/* */
typedef void (*TRpcFTraceCbFct) (
  int              xCallId,
  TRpcFTraceType   xFTraceType,
  const char     * pxMsg );

#ifdef  _NHT_RPC_TRACE_ON_


/***************************************************************************/
/*                                                                         */
/*                   Function declarations                                 */
/*                                                                         */
/***************************************************************************/

/* */
int rpc_ftrace_init (TRpcFTraceCbFct xFTraceCbFct);

/* */
int rpc_ftrace_terminate (void);

/* */
int rpc_ftrace_get_callId (void);


#define RPC_FTRACE_ENTER_CLIENT_CALL(xCallId,pxMessage) _rpc_ftrace_fct(xCallId,RPC_FTRACE_ENTER_CLIENT_CALL,pxMessage)
#define RPC_FTRACE_EXIT_CLIENT_CALL(xCallId,pxMessage)  _rpc_ftrace_fct(xCallId,RPC_FTRACE_EXIT_CLIENT_CALL,pxMessage)
#define RPC_FTRACE_ENTER_SERVER_CALL(xCallId,pxMessage) _rpc_ftrace_fct(xCallId,RPC_FTRACE_ENTER_SERVER_CALL,pxMessage)
#define RPC_FTRACE_EXIT_SERVER_CALL(xCallId,pxMessage)  _rpc_ftrace_fct(xCallId,RPC_FTRACE_EXIT_SERVER_CALL,pxMessage)

/* */
#define RPC_FTRACE_DEFAULT_ENABLE()  { _gRpcFtraceEnableDefault = _gRpcFtraceEnable = 1; }
#define RPC_FTRACE_DEFAULT_DISABLE() { _gRpcFtraceEnableDefault = _gRpcFtraceEnable = 0; }
#define RPC_FTRACE_RESTORE_DEFAULT() { _gRpcFtraceEnable =_gRpcFtraceEnableDefault;}
#define RPC_FTRACE_ENABLE()          { _gRpcFtraceEnable = 1; }
#define RPC_FTRACE_DISABLE()         { _gRpcFtraceEnable = 0; }
#define RPC_FTRACE_IS_ENABLED()      (_gRpcFtraceEnable)


/* */
void _rpc_ftrace_fct (
  int                xCallId,
  TRpcFTraceType     xFTraceType,
  const char       * pxMessage );

/* */
extern volatile int             _gRpcFtraceEnable;
extern volatile int             _gRpcFtraceEnableDefault;
extern volatile TRpcFTraceCbFct  _gNht_ftraceCbFct;


#else /* _NHT_RPC_TRACE_ON_ */

#define rpc_ftrace_init
#define rpc_ftrace_terminate

#define RPC_FTRACE_DEFAULT_ENABLE()
#define RPC_FTRACE_DEFAULT_DISABLE()
#define RPC_FTRACE_RESTORE_DEFAULT()
#define RPC_FTRACE_ENABLE()
#define RPC_FTRACE_DISABLE()
#define RPC_FTRACE_IS_ENABLED()

#define RPC_FTRACE_ENTER_CLIENT_CALL(xCallId,pxMessage)
#define RPC_FTRACE_EXIT_CLIENT_CALL(xCallId,pxMessage)
#define RPC_FTRACE_ENTER_SERVER_CALL(xCallId,pxMessage)
#define RPC_FTRACE_EXIT_SERVER_CALL(xCallId,pxMessage)

#endif /* _NHT_RPC_TRACE_ON_ */

#ifdef __cplusplus
}
#endif

#endif /* _RPC_CALL_TRACE_H_ */
