/**
**  @file nocs_nhtctd.c
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset harness tests
**
**    This header file describes the API of the CTD driver API
**    that need to be implemented by the Chipset Manufacturer in
**    order to be able to comply with the Harness test toolkit provided by
**    Nagra.
**
**  $Id:$
**  $Change:$
**
** REMARK:
**   Comments in this file use special tags to allow automatic API
**   documentation generation in HTML format, using the GNU-General
**   Public Licensed Doxygen tool. For more information about Doxygen,
**   please check www.doxygen.org
**
**   Depending on the platform, the CHM file may not open properly if it
**   is stored on a network drive. So either the file shall be moved on
**   a local drive or add the following registry entry on Windows platform
**  (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/


#ifndef _TRACE_NHTCTD_H_
#define _TRACE_NHTCTD_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/rpc_ftrace.h"
#include "inc/nv_nhtctd.h"
#include "nocs_nhtctd.h"


/******************************************************************************/
/*                                                                            */
/*                    CTD Resource Initialization                             */
/*                                                                            */
/******************************************************************************/

#ifdef _NHT_RPC_TRACE_ON_

/* */
TCtdStatus _CRPC(nhtCtdInitialize) (void);

/* */
TCtdStatus _CRPC(nhtCtdTerminate) (void);

/* */
TCtdStatus _CRPC(nhtCtdGetSoftwareVersion) (
  TCtd20CharsString  xSoftwareVersion );

/* */
TCtdStatus _CRPC(nhtCtdGetApiVersion) (
  TCtdUnsignedInt32*  pxNhtCtdApiVersion );

/* */
void _CRPC(nhtCtdChipReset) (
  TCtdResetType xResetType );

/* */
void _CRPC(nhtCtdChipSuspend2Ram) (void);

/* */
TCtdStatus _CRPC(nhtCtdSetBootMode) (
  TCtdFlashType xBootFlashType );

/* */
TCtdStatus _CRPC(nhtCtdGetBootMode) (
  TCtdFlashType * pxBootFlashType );

/* */
TCtdStatus _CRPC(nhtCtdSetDebugInterfaceMode) (
  TCtdDifMode xDifMode );

/* */
TCtdStatus _CRPC(nhtCtdGetDebugInterfaceMode) (
  TCtdDifMode * pxDifMode );

/* */
TCtdStatus _CRPC(nhtCtdEnableRamScrambling) (
  void );

/* */
TCtdStatus _CRPC(nhtCtdDisableRamScrambling) (
  void );

/* */
TCtdStatus _CRPC(nhtCtdIsRamScramblingEnabled) (
  TCtdBoolean * pxIsEnabled );

/* */
TCtdStatus _CRPC(nhtCtdGetFlashMemorySize) (
  TCtdFlashType   xFlashType,
  TCtdSize      * pxMemorySize );

/* */
TCtdStatus _CRPC(nhtCtdFlashRead) (
  TCtdFlashType      xFlashType,
  TCtdSize           xAddress,
  TCtdSize           xDataSize,
  TCtdUnsignedInt8 * pxData );

/* */
TCtdStatus _CRPC(nhtCtdFlashWrite) (
        TCtdFlashType      xFlashType,
        TCtdSize           xAddress,
        TCtdSize           xDataSize,
  const TCtdUnsignedInt8 * pxData );

/* */
TCtdStatus _CRPC(nhtCtdGetRamMemorySize) (
  TCtdSize * pxMemorySize );

/* */
TCtdStatus _CRPC(nhtCtdRamRead) (
  TCtdSize           xAddress,
  TCtdSize           xDataSize,
  TCtdUnsignedInt8 * pxData );

/* */
TCtdStatus _CRPC(nhtCtdRamWrite) (
  TCtdSize                 xAddress,
  TCtdSize                 xDataSize,
  const TCtdUnsignedInt8 * pxData );

/* */
TCtdStatus _CRPC(nhtCtdGetSpecificPvDescriptorNumber) (
  TCtdUnsignedInt32 * pxSpecificPvNumber );

/* */
TCtdStatus _CRPC(nhtCtdGetSpecificPvDescriptorSet) (
  TCtdUnsignedInt32          xSpecificPvNumber,
  TCtdSpecificPvDescriptor * pxSpecificPvDescriptors,
  TCtdUnsignedInt32        * pxSpecificPvEffectiveNumber );

/* */
TCtdStatus _CRPC(nhtCtdGetPvStatus) (
  TCtdPvId          xPvId,
  TCtdPvSetStatus * pxPvSetStatus );

/* */
TCtdStatus _CRPC(nhtCtdGetPvBufferSize) (
  TCtdPvId            xPvId,
  TCtdUnsignedInt32 * pxPvBufferSize );

/* */
TCtdStatus _CRPC(nhtCtdSetPv) (
  TCtdPvId                  xPvId,
  TCtdUnsignedInt32         xPvBufferSize,
  const TCtdUnsignedInt8  * pxPvBufferValue );

/* */
TCtdStatus _CRPC(nhtCtdGetPv) (
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvBufferSize,
  TCtdUnsignedInt8  * pxPvBufferValue );

/* */
TCtdStatus _CRPC(nhtCtdGetOtpBufferSize) (
  TCtdPvId            xPvId,
  TCtdUnsignedInt32 * pxPvBufferSize );

/* */
TCtdStatus _CRPC(nhtCtdGetOtpValueMask) (
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvMaskSize,
  TCtdUnsignedInt8  * pxMask );

/* */
TCtdStatus _CRPC(nhtCtdSetOtp) (
  TCtdPvId                  xPvId,
  TCtdUnsignedInt32         xPvBufferSize,
  const TCtdUnsignedInt8  * pxPvBufferValue,
  const TCtdUnsignedInt8  * pxPvBufferMask );

/* */
TCtdStatus _CRPC(nhtCtdGetOtp) (
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvBufferSize,
  TCtdUnsignedInt8  * pxPvBufferValue );

/* */
TCtdStatus _CRPC(nhtCtdOpenR2rEncryptSession) (
  TCtdR2RSession * pxSession );

/* */
TCtdStatus _CRPC(nhtCtdOpenR2rDecryptSession) (
  TCtdR2RSession * pxSession );

/* */
TCtdStatus _CRPC(nhtCtdCloseR2rSession) (
  TCtdR2RSession  xSession );

/* */
TCtdStatus _CRPC(nhtCtdSetR2RProtectedKeys) (
  TCtdR2RSession           xSession,
  TCtdUnsignedInt16        xKeyEmi,
  TCtdSize                 xCipheredContentKeySize,
  const TCtdUnsignedInt8 * pxCipheredContentKey,
  TCtdSize                 xCipheredProtectingKeySize,
  const TCtdUnsignedInt8 * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8 * pxL2CipheredProtectingKey );

/* */
TCtdStatus _CRPC(nhtCtdR2rSessionCryptoProcess) (
  TCtdR2RSession           xSession,
  TCtdUnsignedInt16        xEmi,
  const TCtdUnsignedInt8 * pxInput,
  TCtdUnsignedInt8       * pxOutput,
  TCtdSize                 xMessageSize,
  const TCtdUnsignedInt8 * pxInitVector,
  TCtdSize                 xInitVectorSize );

/******************************************************************************/
/*                                                                            */
/*                                    DSC                                     */
/*                                                                            */
/******************************************************************************/


/* */
TCtdStatus _CRPC(nhtCtdOpenDscTestRunSession) (
  TCtdDscTestRunParameters * pxDscTestRunParameters,
  TCtdDscTestRunSession    * pxDscTestRunSession );

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStartDscTestRun) (
  TCtdDscTestRunSession xDscTestRunSession );

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdWaitOnDscTestRunCompletion) (
  TCtdDscTestRunSession xDscTestRunSession,
  int                   xTimeout );

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStopDscTestRun) (
  TCtdDscTestRunSession xDscTestRunSession );

/* */
TCtdStatus _CRPC(nhtCtdSetDscProtectedKeys) (
        TCtdDscTestRunSession   xDscTestRunSession,
        TCtdUnsignedInt16       xKeyEmi,
        TCtdSize                xCipheredProtectingKeySize,
  const TCtdUnsignedInt8      * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8      * pxL2CipheredProtectingKey,
  const TCtdUnsignedInt8      * pxCipheredDscOddContentKey,
        TCtdSize                xCipheredDscOddContentKeySize,
  const TCtdUnsignedInt8      * pxCipheredDscEvenContentKey,
        TCtdSize                xCipheredDscEvenContentKeySize );

/* */
TCtdStatus _CRPC(nhtCtdCloseDscTestRunSession) (
  TCtdDscTestRunSession xDscTestRunSession );


/***************************************************************************/
/*                                                                         */
/*                                    SCR                                  */
/*                                                                         */
/***************************************************************************/


/* */
TCtdStatus _CRPC(nhtCtdOpenScrTestRunSession) (
  const TNhtCtdScrTestRunParameters * pxScrTestRunParameters,
  TNhtCtdScrTestRunSession          * pxScrTestRunSession );

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStartScrTestRun) (
  TNhtCtdScrTestRunSession xScrTestRunSession );

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdWaitOnScrTestRunCompletion) (
  TNhtCtdScrTestRunSession xScrTestRunSession,
  int                      xTimeout );

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStopScrTestRun) (
  TNhtCtdScrTestRunSession  xScrTestRunSession );

/* */
TCtdStatus _CRPC(nhtCtdSetScrProtectedKeys) (
        TNhtCtdScrTestRunSession   xScrTestRunSession,
        TCtdUnsignedInt16          xKeyEmi,
        TCtdSize                   xCipheredProtectingKeySize,
  const TCtdUnsignedInt8         * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8         * pxL2CipheredProtectingKey,
  const TCtdUnsignedInt8         * pxCipheredScrContentKey,
        TCtdSize                   xCipheredScrContentKeySize,
  const TCtdUnsignedInt8         * pxInitializationVector,
        TCtdSize                   xInitializationVectorSize );

/* */
TCtdStatus _CRPC(nhtCtdCloseScrTestRunSession) (
  TNhtCtdScrTestRunSession xScrTestRunSession );

#endif /* _NHT_RPC_TRACE_ON_ */


#ifdef __cplusplus
}
#endif

#endif /* _TRACE_NHTCTD_H_ */
