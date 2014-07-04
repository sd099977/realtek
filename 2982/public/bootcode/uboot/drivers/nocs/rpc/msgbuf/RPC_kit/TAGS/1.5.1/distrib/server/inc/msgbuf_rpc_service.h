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


#ifndef _MSGBUF_RPC_SERVICE_H_
#define _MSGBUF_RPC_SERVICE_H_


#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/


#include "inc/xsd-c.h"
#include "inc/msgbuf_types.h"


/******************************************************************************/
/*                                                                            */
/*                               TYPES & CONSTANTS                            */
/*                                                                            */
/******************************************************************************/


typedef struct SRpcBufHeader   TRpcBufHeader;
typedef struct SRpcMessageData TRpcMessageData;
typedef struct SRpcServiceHnd  TRpcServiceHnd;
typedef struct SRpcSocketHnd   TRpcSocketHnd;


/* */
typedef int (*TRpcWrite_cbfct) (
  void          * pxFd,
  const void    * pxBuffer,
  int             xSize );


/* */
typedef int (*TRpcRead_cbfct) (
  void    * pxFd,
  void    * pxBuffer,
  int       xSize );


/**
 *  @brief
 *   RPC standard transport stream header
 *   This structure stands as the RPC transaction header.
 *
 *   This header structure only depends of the RPC transaction format.
 *   In particular, its definition does not depend of the topology or the
 *   programming laguage in which the RPC is implemented.
 */
struct SRpcBufHeader
{
  uint32_t rpcMagicId;
  uint32_t rpcServiceId;
  uint32_t methodIdx;
  uint32_t rpc_msbBuf_len;
  uint32_t requestIdx;
  uint32_t rpcStatus;
};

/**
 *  @brief
 *    RPC execution data structure
 *    This structure contains all data associated to a particular RPC transaction.
 */
struct SRpcMessageData
{
  TRpcSocketHnd                  * pRpcSocketHnd;          /* socket descriptor */
  TMsgBuf_rpcHandler               rpcHandler;
  TRpcBufHeader                    rpcBufHeader;           /* RPC msg buffer header */
  TMsgBuf_message                * pMsg;
  TMsgBuf_methodDescriptor const * pRpcServiceMethodDesc;
};


/**
 *  @brief
 *    RPC service set handler structure definition */
/*    This handler holds all information relative to services
 *    supported by a RPC server or client
 */
struct SRpcServiceHnd
{
  TMsgBuf_serviceHandle rpcService;
  uint32_t              rpcServiceId;

};


/**
 *  @brief
 *   RPC msgbuf handler structure definition
 */
struct SRpcSocketHnd
{
  uint32_t           magicNumber;
  void             * fd;
  void             * pPrivateServiceData;
  int                rpcServiceHandleNumber;
  TRpcServiceHnd  *  pRpcServiceDescSet;
  TRpcWrite_cbfct    write;
  TRpcRead_cbfct     read;
  TRpc_status        isRpcConnectionLost;
};


#define RPC_METHOD_CALL_RESPONSE_FLAGMASK (0x80000000)
#define RPC_METHOD_NOTIFICATION_FLAGMASK  (0x40000000)



/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/



/**
 *  @brief
 *    Post a synchronous generic RPC call.
 *
 *  Build the RPC transaction header associated to a call request
 */
TRpc_status msgbuf_rpc_build_callHeader (
  TRpcSocketHnd          * pxRpcSocketHandler,
  TMsgBuf_rpcHandler       xRpcHandler,
  TMsgBuf_message        * pxInMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId,
  TRpcMessageData        * pxWriteData,
  uint32_t                 xReqId,
  char                     xIsNotification );


/**
 *  @brief
 *    Send a RPC message transaction to the remote side of the connection.
 *
 * This lowel function converts an RPC message into a "msgbuf" serial
 * data structure and send it to a remote application via a the communication
 * channel.
 */
TRpc_status msgbuf_rpc_send (
  TRpcSocketHnd         * pxRpcSocketHnd,
  const TRpcBufHeader   * pxRpcBufHeader,
  TMsgBuf_message const * pxMsg );


/**
 *  @brief
 *    Receive one RPC transaction from the connection socket
 */
TRpc_status msgbuf_rpc_recieve (
  TRpcMessageData    * pxRpcReadData,
  TMsgBuf_rpcHandler   xRpcHandler );


/**
 *  @brief
 *    Execute a RPC request associated to a RPC remote call.
 */
TRpc_status msgbuf_rpc_execute (
  TRpcMessageData * pxRpcReadData );


/**
 *  @brief
 *    Check if an RPC transaction may stands as a reponse to a
 *    a call request.
 */
int msgbuf_rpc_isResponseOf (
  TRpcMessageData * pxRpcReadData,
  TRpcMessageData * pxRpcWriteData );


/* */
#define MSGBUF_RPC_isResponse(_pxRpcBufHeader) \
  ((_pxRpcBufHeader)->methodIdx & RPC_METHOD_CALL_RESPONSE_FLAGMASK)

/* */
#define MSGBUF_RPC_isNotification(_pxRpcBufHeader) \
  ((_pxRpcBufHeader)->methodIdx & RPC_METHOD_NOTIFICATION_FLAGMASK)


#define MSGBUF_RPC_getMethodId(_pxRpcBufHeader) \
  ((_pxRpcBufHeader)->methodIdx & ~(RPC_METHOD_CALL_RESPONSE_FLAGMASK | RPC_METHOD_NOTIFICATION_FLAGMASK))


/**
 *  @brief
 *    Post a RPC async notification (low level function).
 *
 * Calling this function is only reserved for notification that
 * does not requires execution of the notification before returning
 * back from this function.
 *
 * Calling this function is only reserve for RPC method that does
 * not have any output data.
 */
TRpc_status msgbuf_rpc_notify (
  TRpcSocketHnd          * pxRpcSocketHandler,
  TMsgBuf_rpcHandler       xRpcHandler,
  const TMsgBuf_message  * pxInMsg,
  TMsgBuf_serviceHandle    xServiceHandle,
  uint32_t                 xMethodId );



/**
 *  @brief
 *    Initialize a RPC connection handle (low level function)
 *
 * The list of service descriptor handled by this socket is passed
 * as parameters.
 *
 * PS: This function does not open the socket. it only register it in
 * the RPC socket handle. User is responsible for opening it before
 * calling this function.
 *
 * Return 0 if successfully intialized
 */
int msgbuf_rpc_initHandle (
  TRpcSocketHnd               * pxSocketHandle,
  void                        * xFd,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TRpcWrite_cbfct               xWrite_cbfct,
  TRpcRead_cbfct                xRead_cbfct );


/**
 *  @brief
 *    Terminate a RPC connection handle (low level function)
 */
void msgbuf_rpc_terminateHandle (
  TRpcSocketHnd * pxSocketHandle );


/**
 *  @brief
 *    Terminate a RPC connection handle (low level function)
 */
int msgbuf_rpc_getServiceHandleSet (
  TMsgBuf_rpcHandler    xRpcHandle,
  TRpcServiceHnd     ** pxRpcServiceHandleSet );


#ifdef __cplusplus
}
#endif

#endif /* #define _MSGBUF_RPC_SERVICE_H_ */
