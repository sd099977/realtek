/**
 * File: $Id:$
 *
 *  This file implements the Nagra specific extended CSD API functions.
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

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/TRACE_p_nhtcsd.h"

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


/* */
TCsdStatus nhtCsdGetNhtCsdApiVersion
(
  TCsdUnsignedInt32*  pxNhtCsdApiVersion
)
{
  if (pxNhtCsdApiVersion) *pxNhtCsdApiVersion = 0x00010102;
  return CSD_NO_ERROR;
}

/* */
TCsdStatus nhtCsdGetCsdStatusOffsetValue
(
  TCsdUnsignedInt32 * pxCsdOffsetValue
)
{
  if (pxCsdOffsetValue) *pxCsdOffsetValue = (TCsdUnsignedInt32)CSD_STATUS_OFFSET;
  return CSD_NO_ERROR;
}


/* */
TCsdStatus nhtCsdGetCsdProtectingKeyNumber
(
  TCsdUnsignedInt32 * pxProtectingKeyNumber
)
{
  if (pxProtectingKeyNumber) *pxProtectingKeyNumber = 2;
  return CSD_NO_ERROR;
}


/* */
TCsdStatus nhtCsdOpenR2RSession
(
  TNhtCsdR2RSessionHandle * pxR2RSessionHandle
)
{
  TCsdStatus             csdStatus;
  TCsdR2RKeyPathHandle * pR2RKeyPathHandle = NULL;

  csdStatus = _CRPC(nhtCsdOpenR2RKeyPathHandle) (&pR2RKeyPathHandle);

  if (pxR2RSessionHandle && (csdStatus == CSD_NO_ERROR))
    *pxR2RSessionHandle = (TNhtCsdR2RSessionHandle)pR2RKeyPathHandle;

  return csdStatus;
}


/* */
TCsdStatus nhtCsdCloseR2RSession
(
  TNhtCsdR2RSessionHandle xR2RSessionHandle
)
{
  TCsdStatus             csdStatus;
  TCsdR2RKeyPathHandle * pR2RKeyPathHandle;

  pR2RKeyPathHandle = (TCsdR2RKeyPathHandle *)xR2RSessionHandle;

  csdStatus = _CRPC(nhtCsdCloseR2RKeyPathHandle) (pR2RKeyPathHandle);

  return csdStatus;
}


/* */
TCsdStatus nhtCsdEncryptDataWithClearTextHostKey
(
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TNhtCsdR2RSessionHandle      xR2RSessionHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdEncryptDataWithClearTextHostKey) (
    xAlgorithm,
    xMode,
    pxClearTextHostKey,
    xClearTextHostKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    (TCsdR2RKeyPathHandle*)xR2RSessionHandle,
    pxInputData,
    pxOutputData,
    xDataSize );

  return csdStatus;
}


/* */
TCsdStatus nhtCsdDecryptDataWithClearTextHostKey
(
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TNhtCsdR2RSessionHandle      xR2RSessionHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdDecryptDataWithClearTextHostKey) (
    xAlgorithm,
    xMode,
    pxClearTextHostKey,
    xClearTextHostKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    (TCsdR2RKeyPathHandle*)xR2RSessionHandle,
    pxInputData,
    pxOutputData,
    xDataSize );

  return csdStatus;
}


/* */
TCsdStatus nhtCsdEncryptDataWithSecretContentKey
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
        TCsdUnsignedInt32               xProtectingKeyNumber,
  const TNhtProtectingKey             * pxR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8              * pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8              * pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TNhtCsdR2RSessionHandle         xR2RSessionHandle,
  const TCsdUnsignedInt8              * pxInputData,
        TCsdUnsignedInt8              * pxOutputData,
        TCsdSize                        xDataSize
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdEncryptDataWithSecretContentKey) (
    xAlgorithm,
    xMode,
    *(const TCsdR2RCipheredProtectingKeys *)pxR2RCipheredProtectingKeys,
    pxCipheredContentKey,
    xCipheredContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    (TCsdR2RKeyPathHandle*)xR2RSessionHandle,
    pxInputData,
    pxOutputData,
    xDataSize  );

  return csdStatus;
}


/* */
TCsdStatus nhtCsdDecryptDataWithSecretContentKey
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
        TCsdUnsignedInt32               xProtectingKeyNumber,
  const TNhtProtectingKey             * pxR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8              * pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8              * pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TNhtCsdR2RSessionHandle         xR2RSessionHandle,
  const TCsdUnsignedInt8              * pxInputData,
        TCsdUnsignedInt8              * pxOutputData,
        TCsdSize                        xDataSize
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdDecryptDataWithSecretContentKey) (
    xAlgorithm,
    xMode,
    *(const TCsdR2RCipheredProtectingKeys *)pxR2RCipheredProtectingKeys,
    pxCipheredContentKey,
    xCipheredContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    (TCsdR2RKeyPathHandle*)xR2RSessionHandle,
    pxInputData,
    pxOutputData,
    xDataSize  );

  return csdStatus;
}


TCsdStatus nhtcsd_r2r_monteCarlo_test_run
(
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8                  * pxOutputData
)
{
  return nhtcsd_r2r_testAlgo_run (pxInputParams, pxOutputData);
}
