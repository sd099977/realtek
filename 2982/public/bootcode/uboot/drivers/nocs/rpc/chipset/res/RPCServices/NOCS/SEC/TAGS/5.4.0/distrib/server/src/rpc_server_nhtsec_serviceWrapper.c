/* DO NOT EDIT THIS FILE!!!
 * This file was automatically generated by msgbuf compiler!
 *
 * This file contains the msgbuf structure definitions associated
 * to the package nhtsec.proto
 */


/*****************************************************************************
 * include files                                                             *
 ****************************************************************************/

#include "inc/rpc_nhtsec.h"
#include "src/rpc_nhtsec_api.h"
#include "src/_msgbuf_nhtsec.h"



/*****************************************************************************
 * RPC service remote API implementation                                     *
 ****************************************************************************/

/* RPC method: rpc_nhtsec_tn_ecmCallBack
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtsec_tn_ecmCallBack
(
  TMsgBuf_rpcHandler              xRpcHandler,
  const TNhtsec_EcmCallBackMsg  * pxInputMessage,
  TNhtsec_EmptyMsg             ** pxOutputMessage
)
{
  return rpc_notify (
    xRpcHandler,
    (TMsgBuf_message const *)pxInputMessage,
    gRpcServiceHandle_nhtsec,
    68 );
}

