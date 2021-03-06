/* DO NOT EDIT THIS FILE!!!
 * This file was automatically generated by msgbuf compiler!
 *
 * This file contains the msgbuf structure definitions associated
 * to the package nhtreport.proto
 */


/*****************************************************************************
 * include files                                                             *
 ****************************************************************************/

#include "inc/rpc_nhtreport.h"
#include "src/rpc_nhtreport_api.h"
#include "src/_msgbuf_nhtreport.h"



/*****************************************************************************
 * RPC service remote API implementation                                     *
 ****************************************************************************/

/* RPC method: rpc_nhtreport_tn_report_error
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtreport_tn_report_error
(
  TMsgBuf_rpcHandler                   xRpcHandler,
  const TNhtreport_ReportErrorInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg               ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtreport,
    0 );
}

/* RPC method: rpc_nhtreport_tn_report_trace
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtreport_tn_report_trace
(
  TMsgBuf_rpcHandler                   xRpcHandler,
  const TNhtreport_ReportTraceInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg               ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtreport,
    1 );
}

/* RPC method: rpc_nhtreport_tn_report_info
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtreport_tn_report_info
(
  TMsgBuf_rpcHandler                  xRpcHandler,
  const TNhtreport_ReportInfoInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg              ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtreport,
    2 );
}

/* RPC method: rpc_nhtreport_tn_report_stdout
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtreport_tn_report_stdout
(
  TMsgBuf_rpcHandler                  xRpcHandler,
  const TNhtreport_ReportTextInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg              ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtreport,
    4 );
}

/* RPC method: rpc_nhtreport_tn_report_stderr
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtreport_tn_report_stderr
(
  TMsgBuf_rpcHandler                  xRpcHandler,
  const TNhtreport_ReportTextInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg              ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtreport,
    5 );
}

/* RPC method: rpc_nhtreport_tn_report_ftrace
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtreport_tn_report_ftrace
(
  TMsgBuf_rpcHandler                    xRpcHandler,
  const TNhtreport_ReportFTraceInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg                ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtreport,
    6 );
}

