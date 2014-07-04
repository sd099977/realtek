/**
 * File: $Id:$
 *
 *  This file implements the server/client common BSD API/EAPI function traces.
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


#ifndef _TRACE_NHTBSD_H_
#define _TRACE_NHTBSD_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "inc/rpc_ftrace.h"
#include "inc/nv_nhtbsd.h"
#include "nocs_nhtbsd.h"
#include "inc/nv_nhtbsd.h"


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

#ifdef _NHT_RPC_TRACE_ON_


/* */
TBsdStatus _CRPC(bsdGetApiVersion) (
  TUnsignedInt32 * pxBsdApiVersion );

/* */
TBsdStatus  _CRPC(bsdGetSoftwareVersion) (
  TBsd20CharsString xSoftwareVersion );

/* */
TBsdStatus _CRPC(bsdGetNuid) (
  TBsd4BytesVector xNuid );

/* */
TBsdStatus _CRPC(bsdGetNuid64) (
  TBsd8BytesVector xNuid64 );

/* */
TBsdStatus _CRPC(bsdSetStbCaSn) (
 const TBsd4BytesVector xStbCaSn );

/* */
TBsdStatus _CRPC(bsdGetStbCaSn) (
  TBsd4BytesVector xStbCaSn );

/* */
TBsdStatus _CRPC(bsdSetMarketSegmentId) (
  const TBsd4BytesVector xMarketSegmentId );

/* */
TBsdStatus _CRPC(bsdGetMarketSegmentId) (
  TBsd4BytesVector xMarketSegmentId );

/* */
TBsdStatus _CRPC(bsdGetNUIDCheckNumber) (
  TBsd4BytesVector xNUIDCheckNumber );

/* */
TBsdStatus _CRPC(bsdGetDataIntegrityCheckNumber) (
  const TUnsignedInt8 * pxData,
  TUnsignedInt32        xDataSize,
  TBsd4BytesVector      xDataIntegrityCheckNumber );

/* */
TBsdStatus _CRPC(bsdChipsetInformation) (
  TBsdInfoChipset * pxInfoChipset );


/******************************************************************************/
/*                                                                            */
/*                                    RAM2RAM                                 */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdOpenRam2RamEncryptSession) (
  TBsdCipherSession * pxSession );

/* */
TBsdStatus _CRPC(bsdOpenRam2RamDecryptSession) (
  TBsdCipherSession * pxSession );

/* */
TBsdStatus _CRPC(bsdCloseSession) (
  TBsdCipherSession xSession );

/* */
TBsdStatus _CRPC(bsdSetClearTextKey) (
  TBsdCipherSession     xSession,
  TUnsignedInt16        xEmi,
  TSize                 xClearTextKeySize,
  const TUnsignedInt8 * pxClearTextKey );

/* */
TBsdStatus _CRPC(bsdSet2LevelProtectedKey) (
  TBsdCipherSession     xSession,
  TUnsignedInt16        xEmi,
  TSize                 xCipheredContentKeySize,
  const TUnsignedInt8 * pxCipheredContentKey,
  TSize                 xCipheredProtectingKeySize,
  const TUnsignedInt8 * pxL1CipheredProtectingKey,
  const TUnsignedInt8 * pxL2CipheredProtectingKey );

/* */
TBsdStatus _CRPC(bsdEncryptFlashProtKey) (
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  size_t                xSize );

/* */
TBsdStatus _CRPC(bsdUseFlashProtKey) (
  TBsdCipherSession xSession,
  TUnsignedInt16    xEmi );

/* */
TBsdStatus _CRPC(bsdUseCertKey) (
  TBsdCipherSession xSession,
  TUnsignedInt16    xEmi );

/* */
TBsdStatus _CRPC(bsdSessionEncrypt) (
  TBsdCipherSession xSession,
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  TSize                 xMessageSize,
  const TUnsignedInt8 * pxInitVector,
  TSize                 xInitVectorSize );

/* */
TBsdStatus _CRPC(bsdSessionDecrypt) (
  TBsdCipherSession     xSession,
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  TSize                 xMessageSize,
  const TUnsignedInt8 * pxInitVector,
  TSize                 xInitVectorSize );

/******************************************************************************/
/*                                                                            */
/*                                    RSA                                     */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdRsaPublicEncrypt) (
  const TUnsignedInt8 * pxInput,
  TSize                 xInputSize,
  TUnsignedInt8       * pxOutput,
  TUnsignedInt32        xE,
  const TUnsignedInt8 * pxN,
  TSize                 xKeySize,
  TBsdRsaPadding        xPadding );

/* */
TBsdStatus _CRPC(bsdRsaPublicDecrypt) (
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  TSize               * pxOutputSize,
  TUnsignedInt32        xE,
  const TUnsignedInt8 * pxN,
  TSize                 xKeySize,
  TBsdRsaPadding        xPadding );

/******************************************************************************/
/*                                                                            */
/*                                    SHA-256                                 */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus  _CRPC(bsdSha256Init) (
  TBsdHashContext * pxContext );

/* */
TBsdStatus _CRPC(bsdSha256Update) (
  TBsdHashContext       xContext,
  const TUnsignedInt8 * pxMessageChunk,
  TSize                 xChunkSize );

/* */
TBsdStatus _CRPC(bsdSha256Final) (
  TBsdHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest );

/******************************************************************************/
/*                                                                            */
/*                                    HMAC                                    */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdHmacSha256Init) (
  const TUnsignedInt8 * pxKey,
  TSize                 xKeySize,
  TBsdHashContext     * pxContext );

/* */
TBsdStatus _CRPC(bsdHmacSha256Update) (
  TBsdHashContext       xContext,
  const TUnsignedInt8 * pxMessageChunk,
  TSize                 xChunkSize );

/* */
TBsdStatus _CRPC(bsdHmacSha256Final) (
  TBsdHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest );

/******************************************************************************/
/*                                                                            */
/*                                  RANDOM                                    */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdGenerateRandomBytes) (
  TSize           xNumOfBytes,
  TUnsignedInt8 * pxRandomBytes );


/******************************************************************************/
/*                                                                            */
/*                                  RESET                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup res
 *
 *  @brief
 *    Performs a chipset reset, this reset must clear the registers, caches and
 *    other volatile memories. This function does not return.
 *
 *  @applies
 *    NOCS3 only
 *
*/
void _CRPC(bsdChipReset) (void);


/******************************************************************************/
/*                                                                            */
/*                              RAM2RAM (legacy)                              */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdEncryptDataWithSecretContentKey) (
  TBsdR2RAlgorithm      xAlgorithm,
  const TUnsignedInt8 * pxInputData,
  TUnsignedInt8       * pxOutputData,
  TUnsignedInt32        xDataSize );

/* */
TBsdStatus _CRPC(bsdDecryptDataWithSecretContentKey) (
  TBsdR2RAlgorithm      xAlgorithm,
  const TUnsignedInt8 * pxInputData,
  TUnsignedInt8       * pxOutputData,
  TUnsignedInt32        xDataSize );

/* */
TUnsignedInt8* _CRPC(bsdAllocateBuffer) (
  size_t xBufferSize );

/* */
TBsdStatus _CRPC(bsdFreeBuffer) (
  TUnsignedInt8 * pxBuffer );

/* */
TBsdStatus _CRPC(nhtBsdInitialize) (void);

/* */
TBsdStatus _CRPC(nhtBsdTerminate) (void);

/* */
TBsdStatus _CRPC(nhtBsdGetCertificationNOCSVersion) (
  TUnsignedInt32 * pxVersion );

/* */
TBsdStatus _CRPC(nhtBsdGetSoftwareVersion) (
  TBsd20CharsString xSoftwareVersion );

/* */
TBsdStatus _CRPC(nhtBsdGetChipManufacturerName) (
  TBsd20CharsString xChipManufacturerName );

/* */
TBsdStatus  _CRPC(nhtBsdGetChipName) (
  TBsd20CharsString xChipName );

/* */
TBsdStatus _CRPC(nhtBsdGetBsdProtectingKeyNumber) (
  TUnsignedInt32 * pxProtectingKeyNumber );

/* */
TBsdStatus _CRPC(nhtGetNhtBsdApiVersion) (
  TUnsignedInt32 * pxNhtBsdApiVersion );

/* */
TBsdStatus _CRPC(nhtBsdGetBsdStatusOffsetValue) (
  TUnsignedInt32 * pxBsdOffsetValue );

/* */
TBsdStatus _CRPC(nhtBsdServerTerminate) (void);


#endif /* _TRACE_NHTBSD_H_ */

#endif /* _NHT_RPC_TRACE_ON_ */

#ifdef __cplusplus
}
#endif

