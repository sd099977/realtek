/**
 * File: $Id:$
 *
 *  This header file implements the MSGBUF RPC generic service functions.
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

#ifndef _POSIX_RPC_SERVICE_H_
#define _POSIX_RPC_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "inc/xsd-c.h"
#include "inc/msgbuf_rpc_service.h"


/* Create a RPC socket handle
 *
 * The list of service descriptor handled by this socket is passed
 * as parameters.
 *
 * PS: This function does not open the socket. it only register it in
 * the RPC socket handle. User is responsible for opening it before
 * calling this function.
 *
 * Return the new associated RPC socket handle.
 *
 */
TMsgBuf_rpcHandler pPosixRpcService_createHandle (
  void                        * pxFd,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TRpcWrite_cbfct               xWrite_cbfct,
  TRpcRead_cbfct                xRead_cbfct );


/* Close a socket handle
 *
 * The user is responsible for having closed the socket file descriptor
 * before calling this function.
 *
 * PS: for getting the socket file descriptor associated to an already
 * created RPC handle, please refer to the 'rpcHandle_getSocketFd()'
 * function.
 */
void posixRpcService_closeHandle (
  TMsgBuf_rpcHandler xRpcHandle );


/* */
int posixRpcService_getFd (
  TMsgBuf_rpcHandler    xRpcHandle,
  void               ** pxFd );

int posixRpcService_getPrivateData (
  TMsgBuf_rpcHandler    xRpcHandle,
  void               ** pxPrivateData );

/* */
int posixRpcService_registerPrivateData (
  TMsgBuf_rpcHandler    xRpcHandle,
  void                * pxPrivateData );

/* */
int posixRpcService_rxBarrier_lock (
  TMsgBuf_rpcHandler    xRpcHandle );

/* */
int posixRpcService_rxBarrier_unlock (
  TMsgBuf_rpcHandler    xRpcHandle );

/*
 * Main RPC service function
 */
void * posixRpcService_main (
  TMsgBuf_rpcHandler xRpcHandler );

/* */
int posixRpcService_serveOne (
  TMsgBuf_rpcHandler xRpcHandler );

/* */
int posixRpcService_abortPendingCalls (
  TMsgBuf_rpcHandler xRpcHandler );


#ifdef __cplusplus
}
#endif

#endif /* #define _POSIX_RPC_SERVICE_H_ */
