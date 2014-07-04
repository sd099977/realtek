/**
 * File: $Id:$
 *
 *  This file implements the server/client common SEC API/EAPI function traces.
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


#ifndef _TRACE_NHTSEC_H_
#define _TRACE_NHTSEC_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "inc/rpc_ftrace.h"
#include "inc/nv_nhtsec.h"
#include "ca_nhtsec.h"
#include "ca_sec.h"

#ifdef _NHT_RPC_TRACE_ON_


/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/


/* */
TSecStatus _CRPC(secGetNuid) (
  TSecNuid * pxNuid );

/* */
TSecStatus _CRPC(secGetChipsetRevision) (
  const TChar** ppxChipsetRevision );

/* */
TSecStatus _CRPC(secEncryptData) (
        TUnsignedInt8 * pxOutput,
  const TUnsignedInt8 * pxInput,
        TSize           xDataSize );

/* */
TSecStatus _CRPC(secDecryptData) (
        TUnsignedInt8 * pxOutput,
  const TUnsignedInt8 * pxInput,
        TSize           xDataSize );

/* */
TSecFunctionTable * _CRPC(secGetFunctionTable) (void);


/******************************************************************************/
/*                                                                            */
/*                     EXTENDED FUNCTION PROTOTYPES                           */
/*                                                                            */
/******************************************************************************/

/* */
TSecStatus _CRPC(nhtSecInitialize) (void);

/* */
TSecStatus _CRPC(nhtSecTerminate) (void);

/* */
TSecStatus _CRPC(nhtSecGetSoftwareVersion) (
  TUnsignedInt32 * pxSoftwareVersion );

/* */
TSecStatus _CRPC(secGetSoftwareVersion) (
  TUnsignedInt32 * pxSoftwareVersion );

/* */
TSecStatus _CRPC(nhtSecOpenScrTransportSession) (
  char                          * pxInputFileName,
  const TNhtSecDemuxServiceInfo * pxDemuxServiceInfo,
  int                             xIsForEncryption,
  char                          * pxOutputFileName,
  TTransportSessionId           * pxTransportSessionId );

/* */
TSecStatus _CRPC(nhtSecOpenDscTransportSession) (
  char                          * pxInputFileName,
  const TNhtSecDemuxServiceInfo * pxDemuxServiceInfo,
  int                             xIsInClear,
  const TNhtSecDemuxEcmInfo     * pxDemuxEcmInfo,
  char                          * pxOutputFileName,
  TTransportSessionId           * pxTransportSessionId );

/* */
TNhtSecTransportStreamingStatus _CRPC(nhtSecStartTransportSessionStreaming) (
  TTransportSessionId xTransportSessionId );

/* */
TNhtSecTransportStreamingStatus _CRPC(nhtSecWaitOnTransportSessionStreamingCompletion) (
  TTransportSessionId xTransportSessionId,
  int                 xTimeout );

/* */
TNhtSecTransportStreamingStatus _CRPC(nhtSecStopTransportSessionStreaming) (
  TTransportSessionId xTransportSessionId );

/* */
TSecStatus _CRPC(nhtSecCloseTransportSession) (
  TTransportSessionId xTransportSessionId );

/* */
TSecStatus _CRPC(nhtSecSetTransportSessionInitialValue) (
  TSecCipherSession     xSession,
  size_t                xKeyIdSize,
  TUnsignedInt8       * pxKeyId,
  size_t                xInitVectorSize,
  const TUnsignedInt8 * pxInitVector );

/* */
TSecStatus _CRPC(nhtSecGetNhtSecApiVersion) (
  TUnsignedInt32 * pxApiVersion );


#endif /* _NHT_RPC_TRACE_ON_ */


#ifdef __cplusplus
}
#endif

#endif /* _TRACE_NHTSEC_H_ */
