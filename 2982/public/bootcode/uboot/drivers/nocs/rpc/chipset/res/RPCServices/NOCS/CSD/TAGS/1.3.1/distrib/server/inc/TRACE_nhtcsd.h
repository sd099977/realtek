/**
 * File: $Id:$
 *
 *  This file implements the server/client common CSD API/EAPI function traces.
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


#ifndef _TRACE_NHTCSD_H_
#define _TRACE_NHTCSD_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "inc/rpc_ftrace.h"
#include "inc/nv_nhtcsd.h"
#include "nocs_nhtcsd.h"


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


#ifdef _NHT_RPC_TRACE_ON_

/* */
TCsdStatus _CRPC(csdGetApiVersion) (
  TCsdUnsignedInt32 * pxCsdApiVersion );

/* */
TCsdStatus _CRPC(csdGetSoftwareVersion) (
  TCsd20CharsString  xSoftwareVersion );

/* */
TCsdStatus _CRPC(csdGetChipRevision) (
  TCsd20CharsString xChipRevision );

/* */
TCsdStatus _CRPC(csdGetChipExtension) (
  TCsd20CharsString xChipExtension );

/* */
TCsdStatus _CRPC(csdGetNuid) (
  TCsd4BytesVector xNuid );

/* */
TCsdStatus _CRPC(csdGetNuid64) (
  TCsd8BytesVector xNuid64 );

/* */
TCsdStatus _CRPC(csdGetNUIDCheckNumber) (
  TCsd4BytesVector xNUIDCheckNumber );

/* */
TCsdStatus _CRPC(csdGetCSCDCheckNumber) (
  const TCsdUnsignedInt8 xCSCData[16],
        TCsd4BytesVector xCSCDCheckNumber );

/* */
TCsdStatus _CRPC(csdGetSTBCASNCheckNumber) (
  const TCsdUnsignedInt8 xSTBCASNData[4],
        TCsd4BytesVector xSTBCASNCheckNumber );

/* */
TCsdStatus _CRPC(csdGetDataIntegrityCheckNumber) (
  const TCsdUnsignedInt8 * pxData,
  TCsdSize                 xDataSize,
  TCsd4BytesVector         xDataIntegrityCheckNumber );

/* */
TCsdStatus _CRPC(csdSetStbCaSn) (
  const TCsd4BytesVector xStbCaSn );

/* */
TCsdStatus _CRPC(csdGetStbCaSn) (
  TCsd4BytesVector xStbCaSn );

/* */
TCsdStatus _CRPC(csdSetMarketSegmentId) (
  const TCsd4BytesVector xMarketSegmentId );

/* */
TCsdStatus _CRPC(csdGetMarketSegmentId) (
  TCsd4BytesVector xMarketSegmentId );

/* */
TCsdStatus _CRPC(csdSetBootMode) (
  TCsdBootMode xBootMode );

/* */
TCsdStatus _CRPC(csdGetBootMode) (
  TCsdBootMode * pxBootMode );

/* */
TCsdStatus _CRPC(csdEnableScs) (void);

/* */
TCsdStatus _CRPC(csdGetScsActivationFlag) (
  TCsdActivationFlag * pxScsActivationFlagState );

/* */
TCsdStatus _CRPC(csdSetScsTotalAreaSize) (
  TCsdScsTotalAreaSize xScsTotalAreaSize );

/* */
TCsdStatus _CRPC(csdGetScsTotalAreaSize) (
  TCsdScsTotalAreaSize * pxTotalAreaSize );

/* */
TCsdStatus _CRPC(csdSetRamUnscrambledStorageSize) (
  TCsdUnsignedInt8  * pxPvRamUnscrambledStorageSize,
  TCsdUnsignedInt16   xPvLength );

/* */
TCsdStatus _CRPC(csdGetRamUnscrambledStorageSize) (
  TCsdUnsignedInt8*  pxPvRamUnscrambledStorageSize,
  TCsdUnsignedInt16   xPvLength );

/* */
TCsdStatus _CRPC(csdEnableRamScrambling) (void );

/* */
TCsdStatus _CRPC(csdGetScramblingActivationFlag) (
  TCsdActivationFlag* pxScramblingActivationFlagState );

/* */
TCsdStatus _CRPC(csdEnableFlashProtection) (void);

/* */
TCsdStatus _CRPC(csdGetFlashProtectionActivationFlag) (
  TCsdActivationFlag* pxFlashProtectionActivationFlagState );

/* */
TCsdStatus _CRPC(csdSelectDebugInterfaceProtectionLevel) (
  TCsdDebugInterfaceAccessMode xDebugInterfaceProtectionLevel );

/* */
TCsdStatus _CRPC(csdGetDebugInterfaceProtectionLevel) (
  TCsdDebugInterfaceAccessMode* pxDebugInterfaceProtectionLevel );

/* */
TCsdStatus _CRPC(csdDeactivateKeyLadder) (void );

/* */
TCsdStatus _CRPC(csdGetKeyLadderDeactivationFlag) (
 TCsdActivationFlag* pxKeyLadderDeactivationFlagState );

/* */
TCsdStatus _CRPC(csdGetDvrKey) (
  TCsdUnsignedInt8    xDvrKey[16] );

/* */
TCsdStatus _CRPC(nhtCsdInitialize) (void);

/* */
TCsdStatus _CRPC(nhtCsdTerminate) (void);

/* */
TCsdStatus _CRPC(nhtCsdGetNhtCsdApiVersion) (
  TCsdUnsignedInt32*  pxNhtCsdApiVersion );

TCsdStatus _CRPC(nhtCsdGetCsdStatusOffsetValue) (
  TCsdUnsignedInt32 * pxCsdOffsetValue );

/* */
TCsdStatus _CRPC(nhtCsdGetCsdProtectingKeyNumber) (
  TCsdUnsignedInt32 * pxProtectingKeyNumber );

/* */
TCsdStatus _CRPC(nhtCsdGetCertificationNOCSVersion) (
  TCsdUnsignedInt32 * pxVersion );

/* */
TCsdStatus _CRPC(nhtCsdGetSoftwareVersion) (
  TCsd20CharsString  xSoftwareVersion );

/* */
TCsdStatus _CRPC(nhtCsdGetChipManufacturerName) (
  TCsd20CharsString xChipManufacturerName );

/* */
TCsdStatus _CRPC(nhtCsdGetChipName) (
  TCsd20CharsString xChipName );

/* */
TCsdStatus _CRPC(nhtCsdGetBootModeNumber) (
  TNhtCsdBootModeNumber * pxBootModeNumber );

/* */
TCsdStatus _CRPC(nhtCsdGetBootModeDescriptorSet) (
  TNhtCsdBootModeNumber       xBootModeDescriptorNumber,
  TNhtCsdBootModeDescriptor * pxBootModeDescriptors,
  TNhtCsdBootModeNumber     * pxBootModeEffectiveNumber );

/* */
TCsdStatus _CRPC(nhtCsdGetBootModeDescriptor) (
  TCsdBootMode                xBootModeId,
  TNhtCsdBootModeDescriptor * pxBootModeDescriptor );

/* */
TCsdStatus _CRPC(nhtCsdGetScsExpectedPvValueSize) (
  TCsdScsPvId         xScsPvParamsId,
  TCsdUnsignedInt16 * pxPvLength );

/* */
TCsdStatus _CRPC(nhtCsdSetScsPv) (
  TCsdScsPvId              xScsPvParamsId,
  TCsdUnsignedInt16        xPvLength,
  const TCsdUnsignedInt8 * pxPvValue );

/* */
TCsdStatus _CRPC(nhtCsdGetScsPv) (
  TCsdScsPvId         xScsPvParamsId,
  TCsdUnsignedInt16   xPvLength,
  TCsdUnsignedInt8  * pxPvValue );

/* */
TCsdStatus _CRPC(nhtcsdGetRamUnscrambledStorageSizeBufferLength) (
  TCsdUnsignedInt16 * pxPvLength );


/***************************************************************************/
/*                                                                         */
/*               NOCS1.x RAM2RAM Functions                                 */
/*                                                                         */
/***************************************************************************/


/* */
TNhtCsdSysBufferHandle _CRPC(nhtCsdAllocateSysBuffer) (
  TCsdSize xSize );

/* */
TCsdStatus _CRPC(nhtCsdDeallocateSysBuffer) (
  TNhtCsdSysBufferHandle xNhtCsdSysBufferHandle );


/***************************************************************************/
/*                                                                         */
/*                                    DSC                                  */
/*                                                                         */
/***************************************************************************/


/* */
TCsdStatus _CRPC(nhtCsdOpenDscTestRunSession) (
  TNhtCsdDscTestRunParameters * pxDscTestRunParameters,
  TNhtCsdDscTestRunHandle     * pxDscTestRunHandle );

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdStartDscTestRun) (
  TNhtCsdDscTestRunHandle xDscTestRunHandle );

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdWaitOnDscTestRunCompletion) (
  TNhtCsdDscTestRunHandle xDscTestRunHandle,
  int                     xTimeout );

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdStopDscTestRun) (
  TNhtCsdDscTestRunHandle xDscTestRunHandle );

/* */
TCsdStatus _CRPC(nhtCsdTestRunSetClearTextDscHostKeys) (
        TNhtCsdDscTestRunHandle   xDscTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextDscOddHostKey,
        TCsdSize                  xClearTextDscOddHostKeySize,
  const TCsdUnsignedInt8        * pxClearTextDscEvenHostKey,
        TCsdSize                  xClearTextDscEvenHostKeySize );

/* */
TCsdStatus _CRPC(nhtCsdTestRunSetProtectedDscContentKeys) (
        TNhtCsdDscTestRunHandle         xDscTestRunHandle,
  const TNhtProtectingKey             * pxDscCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8              * pxCipheredDscOddContentKey,
        TCsdSize                        xCipheredDscOddContentKeySize,
  const TCsdUnsignedInt8              * pxCipheredDscEvenContentKey,
        TCsdSize                        xCipheredDscEvenContentKeySize );

/* */
TCsdStatus _CRPC(nhtCsdCloseDscTestRunSession) (
  TNhtCsdDscTestRunHandle  xDscTestRunHandle );


/***************************************************************************/
/*                                                                         */
/*                                    SCR                                  */
/*                                                                         */
/***************************************************************************/

/* */

TCsdStatus _CRPC(nhtCsdOpenScrTestRunSession) (
  const TNhtCsdScrTestRunParameters * pxScrTestRunParameters,
  TNhtCsdScrTestRunHandle           * pxScrTestRunHandle );

/* */

TNhtCsdTestRunStatus _CRPC(nhtCsdStartScrTestRun) (
  TNhtCsdScrTestRunHandle xScrTestRunHandle );

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdWaitOnScrTestRunCompletion) (
  TNhtCsdScrTestRunHandle xScrTestRunHandle,
  int                     xTimeout );

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdStopScrTestRun) (
  TNhtCsdScrTestRunHandle   xScrTestRunHandle );

/* */
TCsdStatus _CRPC(nhtCsdSetClearTextScrEncryptionKey) (
        TNhtCsdScrTestRunHandle   xScrTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextScrHostKey,
        TCsdSize                  xClearTextScrHostKeySize,
  const TCsdUnsignedInt8        * pxInitializationVector,
        TCsdSize                  xInitializationVectorSize );

/* */
TCsdStatus _CRPC(nhtCsdSetClearTextScrDecryptionKey) (
        TNhtCsdScrTestRunHandle   xScrTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextScrHostKey,
        TCsdSize                  xClearTextScrHostKeySize,
  const TCsdUnsignedInt8        * pxInitializationVector,
        TCsdSize                  xInitializationVectorSize );

/* */
TCsdStatus _CRPC(nhtCsdSetProtectedScrDecryptionKey) (
        TNhtCsdScrTestRunHandle         xScrTestRunHandle,
  const TNhtProtectingKey             * pxScrCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize );

/* */
TCsdStatus _CRPC(nhtCsdSetProtectedScrEncryptionKey) (
        TNhtCsdScrTestRunHandle         xScrTestRunHandle,
  const TNhtProtectingKey             * pxScrCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize );

/* */
TCsdStatus _CRPC(nhtCsdCloseScrTestRunSession) (
  TNhtCsdScrTestRunHandle xScrTestRunHandle );

#endif /* _NHT_RPC_TRACE_ON_ */


#ifdef __cplusplus
}
#endif

#endif /* _TRACE_NHTCSD_H_ */
