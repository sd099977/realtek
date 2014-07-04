/**
 * File: $Id:$
 *
 *  This header file defines the MSGBUF main types.
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

#ifndef __MSGBUF_TYPES_H_
#define __MSGBUF_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Define int32_t, int64_t, uint32_t, uint64_t, uint8_t.
 *
 * Usually, just include <inttypes.h> to do the work.
 * XXX: should we use stdint.h?
 */

#ifndef PROTOBUF_C_SKIP_INTTYPES_H
#if defined(_MSC_VER)
  /* On windows, in ms visual studio, define the types ourselves */
#define int32_t      signed __int32
#define INT32_MIN    _I32_MIN
#define INT32_MAX    _I32_MAX
#define uint32_t     unsigned __int32
#define UINT32_MIN   _UI32_MIN
#define UINT32_MAX   _UI32_MAX
#define int64_t      signed __int64
#define INT64_MIN    _I64_MIN
#define INT64_MAX    _I64_MAX
#define uint64_t     unsigned __int64
#define UINT64_MIN   _UI64_MIN
#define UINT64_MAX   _UI64_MAX
#define uint8_t      unsigned char
#else
     /* Use the system inttypes.h */
#include <inttypes.h>
#include <sys/types.h>
#endif
#endif


typedef struct
{
  uint32_t   len;
  void     * pData;

} TMsgBuf_bytes;


typedef int          TMsgBuf_bool;
typedef const void * TMsgBuf_desc;
typedef void       * TMsgBuf_rpcHandler;
typedef const void * TMsgBuf_serviceHandle;

/* MSGBUF field types definition */
typedef enum
{
  RPC_STATUS_NO_ERROR         = 0,
  RPC_STATUS_MALLOC_ERROR,
  RPC_STATUS_FUNCTION_NOT_FEATURED,
  RPC_STATUS_MESSAGE_NOT_INITIALIZED,
  RPC_STATUS_ILLEGAL_PARAMETER,
  RPC_STATUS_CONNECTION_ERROR,
  RPC_STATUS_MSG_READ_TIMEOUT
} TRpc_status;


#ifdef __cplusplus
}
#endif

#endif /* define __MSGBUF_TYPES_H_ */
