/**
 * File: $Id:$
 *
 *  This file implements the R2R MonteCarlo test main function.
 *
 *  Copyright (c) 2012_2013 Nagravision. All rights reserved.
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

/*----------------------------------------------------------------------------
 *   Include files
 *---------------------------------------------------------------------------*/

#include "inc/nhtcsd_r2r_test_algo.h"
#include "inc/nv_nhtcsd.h"
#include <stdio.h>
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/TRACE_p_nhtcsd.h"


/*----------------------------------------------------------------------------
 *   Hook
 *---------------------------------------------------------------------------*/


/* CSD API down compatibility hook.
 *
 * Explanation:
 *
 * Versions anterior to CSD API v3.3.5 contain a crypto mode called
 * CSD_R2R_CRYPTO_OPERATION_MODE_CTR in TCsdR2RCryptoOperationMode enum
 * type. This one desappeared starting CSD API v3.3.5..
 *
 * In order to artificially maintain the down compatibility in harness test
 * framework, this value is here aliased.
 *
 * PS: Ideally, this CSD_R2R_CRYPTO_OPERATION_MODE_CTR value in the enum field
 * should have been kept and simply marked as deprecated in new CSD API
 * releases (but it wasn't done so).
 */

#define ALIAS_CSD_R2R_CRYPTO_OPERATION_MODE_CTR ((TCsdR2RCryptoOperationMode)2)


/*----------------------------------------------------------------------------
 *   Static functions declaration
 *---------------------------------------------------------------------------*/

/* */
static TCsdStatus nhtcsd_r2r_testAlgo_doEncryptionTestRun (
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8             * pxOutputData,
  TNhtCsdR2RSessionHandle        xR2rHandle );


/* */
static TCsdStatus nhtcsd_r2r_testAlgo_doDecryptionTestRun (
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8             * pxOutputData,
  TNhtCsdR2RSessionHandle        xR2rHandle );


/* */
static void _nhtcsd_r2r_inc_MsbfByteArrayValue (
  unsigned char    * pxMsbfByteArray,
  int                xMsbfByteArraySize,
  unsigned int       xAddValue );


/*----------------------------------------------------------------------------
 *   Public function definition
 *---------------------------------------------------------------------------*/


TCsdStatus nhtcsd_r2r_testAlgo_run
(
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8                  * pxOutputData
)
{
  TCsdStatus                   csdStatus;
  TCsdStatus                   tmpCsdStatus;
  TNhtCsdR2RSessionHandle      r2rHandle;

  /* Check for input data presence */
  /* status = _nhtcsd_r2r_check_inputParams_integrity (pxInputParams));
  if (status) return CSD_ERROR; */


  csdStatus = _CRPC(nhtCsdOpenR2RSession) (&r2rHandle);
  if (csdStatus != CSD_NO_ERROR) return csdStatus;

  /* Do the test (according to encryption or decryption */
  if (pxInputParams->isForEncryption)
  {
    csdStatus = nhtcsd_r2r_testAlgo_doEncryptionTestRun (
      pxInputParams,
      pxOutputData,
      r2rHandle );
  }
  else
  {
    csdStatus = nhtcsd_r2r_testAlgo_doDecryptionTestRun (
      pxInputParams,
      pxOutputData,
      r2rHandle );
  }

  tmpCsdStatus = _CRPC(nhtCsdCloseR2RSession) (r2rHandle);
  if (csdStatus == CSD_NO_ERROR) csdStatus = tmpCsdStatus;

  return csdStatus;
}



/* */
void nhtcsd_r2r_testAlgo_initParams
(
  TNhtCsd_r2r_test_algoParams * pxParams
)
{
  pxParams->cryptoAlgorithm                     = CSD_R2R_ALGORITHM_AES_128;
  pxParams->cryptoMode                          = CSD_R2R_CRYPTO_OPERATION_MODE_ECB;
  pxParams->pIvc                                = NULL;
  pxParams->ivcSize                             = 0;
  pxParams->pInputData                          = NULL;
  pxParams->dataSize                            = 0;
  pxParams->isMonteCarlo                        = 0;
  pxParams->runNumber                           = 1;
  pxParams->useSwKey                            = 0;
  pxParams->isForEncryption                     = 0;
  pxParams->keys.KL.pCipheredProtectingKeys     = NULL;
  pxParams->keys.KL.cipheredProtectingKeyNumber = 0;
  pxParams->keys.KL.pCipheredContentKey         = NULL;
  pxParams->keys.KL.cipheredContentKeySize      = 0;
  pxParams->keys.sw.pClearTextHostKey           = NULL;
  pxParams->keys.sw.clearTextHostKeySize        = 0;
}


/* */
void nhtcsd_r2r_testAlgo_terminateParams
(
  TNhtCsd_r2r_test_algoParams * pxParams
)
{
  nhtcsd_r2r_testAlgo_initParams (pxParams);
}


/*----------------------------------------------------------------------------
 *   Static functions definition
 *---------------------------------------------------------------------------*/

/* */
static TCsdStatus nhtcsd_r2r_testAlgo_doEncryptionTestRun
(
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8                  * pxOutputData,
  TNhtCsdR2RSessionHandle             xR2rHandle

)
{
  TCsdStatus          csdStatus = CSD_NO_ERROR;
  TCsdBoolean         isMonteCarloNagraException = 0;
  TCsdUnsignedInt8  * pOutData0 = NULL;
  TCsdUnsignedInt8  * pOutData1 = NULL;
  TCsdUnsignedInt8  * pInData   = NULL;
  TCsdUnsignedInt8  * pIvcData  = NULL;
  TCsdSize            dataSize;
  TCsdUnsignedInt32   loopCounter = 0;
  TCsdBoolean         ivRefresh = 0;

  dataSize = pxInputParams->dataSize;

  pOutData0 = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
  pOutData1 = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);

  if (pxInputParams->pInputData)
  {
    pInData   = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pInData,  pxInputParams->pInputData, dataSize);
  }

  if (pxInputParams->pIvc)
  {
    pIvcData  = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pIvcData, pxInputParams->pIvc, dataSize);
    MSGBUF_SYS_memcpy (pOutData1,pxInputParams->pIvc, dataSize);
    ivRefresh = 1;
  }
  else
  {
    pIvcData = NULL;
    ivRefresh = 0;
  }

  /* Check for MonteCarlo Nagravision specific procedure */
  if ((pxInputParams->cryptoMode == CSD_R2R_CRYPTO_OPERATION_MODE_CBC)      &&
      pxInputParams->isMonteCarlo                                  &&
       ((pxInputParams->cryptoAlgorithm == CSD_R2R_ALGORITHM_TDES_K1K2K1) ||
        (pxInputParams->cryptoAlgorithm == CSD_R2R_ALGORITHM_AES_128)))
    isMonteCarloNagraException = 1;
  else isMonteCarloNagraException = 0;

  /* Encryption test run loop */
  while (loopCounter < pxInputParams->runNumber)
  {
    if (pxInputParams->useSwKey)
    {
      csdStatus = _CRPC(nhtCsdEncryptDataWithClearTextHostKey) (
        pxInputParams->cryptoAlgorithm,
        pxInputParams->cryptoMode,
        pxInputParams->keys.sw.pClearTextHostKey,
        pxInputParams->keys.sw.clearTextHostKeySize,
        pIvcData,
        pxInputParams->ivcSize,
        ivRefresh,
        xR2rHandle,
        pInData,
        pOutData0,
        dataSize );
    }
    else
    {
      csdStatus = _CRPC(nhtCsdEncryptDataWithSecretContentKey) (
        pxInputParams->cryptoAlgorithm,
        pxInputParams->cryptoMode,
        pxInputParams->keys.KL.cipheredProtectingKeyNumber,
        *(const TNhtProtectingKey**)&pxInputParams->keys.KL.pCipheredProtectingKeys,
        pxInputParams->keys.KL.pCipheredContentKey,
        pxInputParams->keys.KL.cipheredContentKeySize,
        pIvcData,
        pxInputParams->ivcSize,
        ivRefresh,
        xR2rHandle,
        pInData,
        pOutData0,
        dataSize );
    }

    if (csdStatus != CSD_NO_ERROR) break;

    if (pxInputParams->isMonteCarlo)
    {
      if (isMonteCarloNagraException)
      {
        /* Copy (pInRefData, pOutRefData1); */
        /* Copy (pIvc, pOutRefData0) */
        if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData1, dataSize);
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pOutData0, dataSize);

        if (pxInputParams->useSwKey)
        {
          csdStatus = _CRPC(nhtCsdEncryptDataWithClearTextHostKey) (
            pxInputParams->cryptoAlgorithm,
            pxInputParams->cryptoMode,
            pxInputParams->keys.sw.pClearTextHostKey,
            pxInputParams->keys.sw.clearTextHostKeySize,
            pIvcData,
            pxInputParams->ivcSize,
            ivRefresh,
            xR2rHandle,
            pInData,
            pOutData1,
            dataSize );
        }
        else
        {
          csdStatus = _CRPC(nhtCsdEncryptDataWithSecretContentKey) (
            pxInputParams->cryptoAlgorithm,
            pxInputParams->cryptoMode,
            pxInputParams->keys.KL.cipheredProtectingKeyNumber,
            *(const TNhtProtectingKey**)&pxInputParams->keys.KL.pCipheredProtectingKeys,
            pxInputParams->keys.KL.pCipheredContentKey,
            pxInputParams->keys.KL.cipheredContentKeySize,
            pIvcData,
            pxInputParams->ivcSize,
            ivRefresh,
            xR2rHandle,
            pInData,
            pOutData1,
            dataSize );
        }

        if (csdStatus != CSD_NO_ERROR) break;

        /* Copy (pIvcRef, pDataOut1) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pOutData1, dataSize);
        loopCounter += 2;
      }
      else
      {
        if (pxInputParams->cryptoMode == ALIAS_CSD_R2R_CRYPTO_OPERATION_MODE_CTR)
          if (pIvcData) _nhtcsd_r2r_inc_MsbfByteArrayValue (pIvcData, pxInputParams->ivcSize, dataSize/pxInputParams->ivcSize);

        loopCounter += 1;
      }

      /* Copy (pDataIn, pDataOut0) */
      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);
    }
    else
    {
      /* Copy (DataIn, dataOut0) */
      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);
      loopCounter += 1;
    }
  }

  if (csdStatus == CSD_NO_ERROR)
  {
    if (isMonteCarloNagraException)
      MSGBUF_SYS_memcpy (pxOutputData, pOutData1, dataSize);
    else MSGBUF_SYS_memcpy (pxOutputData, pOutData0, dataSize);

  }

  if (pOutData0) MSGBUF_SYS_free (pOutData0);
  if (pOutData1) MSGBUF_SYS_free (pOutData1);
  if (pInData)   MSGBUF_SYS_free (pInData);
  if (pIvcData)  MSGBUF_SYS_free (pIvcData);

  return csdStatus;
}


/* */
static TCsdStatus nhtcsd_r2r_testAlgo_doDecryptionTestRun
(
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8                  * pxOutputData,
  TNhtCsdR2RSessionHandle             xR2rHandle

)
{
  TCsdStatus          csdStatus = CSD_NO_ERROR;
  TCsdBoolean         isMonteCarloNagraException = 0;
  TCsdUnsignedInt8  * pOutData0 = NULL;
  TCsdUnsignedInt8  * pOutData1 = NULL;
  TCsdUnsignedInt8  * pInData   = NULL;
  TCsdUnsignedInt8  * pIvcData  = NULL;
  TCsdSize            dataSize;
  TCsdUnsignedInt32   loopCounter = 0;
  TCsdBoolean         ivRefresh = 0;

  dataSize = pxInputParams->dataSize;

  pOutData0 = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
  pOutData1 = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);

  if (pxInputParams->pInputData)
  {
    pInData   = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pInData,  pxInputParams->pInputData, dataSize);
  }

  if (pxInputParams->pIvc)
  {
    pIvcData  = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pIvcData, pxInputParams->pIvc, dataSize);
    MSGBUF_SYS_memcpy (pOutData1,pxInputParams->pIvc, dataSize);
    ivRefresh = 1;
  }

  /* Check for MonteCarlo Nagravision specific procedure */
  if ((pxInputParams->cryptoMode == CSD_R2R_CRYPTO_OPERATION_MODE_CBC)      &&
      (pxInputParams->isMonteCarlo)                                &&
      (pxInputParams->cryptoAlgorithm == CSD_R2R_ALGORITHM_AES_128))
    isMonteCarloNagraException = 1;
  else isMonteCarloNagraException = 0;

  /* Encryption test run loop */
  while (loopCounter <pxInputParams->runNumber)
  {
    if (pxInputParams->useSwKey)
    {
      csdStatus = _CRPC(nhtCsdDecryptDataWithClearTextHostKey) (
        pxInputParams->cryptoAlgorithm,
        pxInputParams->cryptoMode,
        pxInputParams->keys.sw.pClearTextHostKey,
        pxInputParams->keys.sw.clearTextHostKeySize,
        pIvcData,
        pxInputParams->ivcSize,
        ivRefresh,
        xR2rHandle,
        pInData,
        pOutData0,
        dataSize );
    }
    else
    {
      csdStatus = _CRPC(nhtCsdDecryptDataWithSecretContentKey) (
        pxInputParams->cryptoAlgorithm,
        pxInputParams->cryptoMode,
        pxInputParams->keys.KL.cipheredProtectingKeyNumber,
        *(const TNhtProtectingKey**)&pxInputParams->keys.KL.pCipheredProtectingKeys,
        pxInputParams->keys.KL.pCipheredContentKey,
        pxInputParams->keys.KL.cipheredContentKeySize,
        pIvcData,
        pxInputParams->ivcSize,
        ivRefresh,
        xR2rHandle,
        pInData,
        pOutData0,
        dataSize );
    }

    if (csdStatus != CSD_NO_ERROR) break;

    if (pxInputParams->isMonteCarlo)
    {
      if (isMonteCarloNagraException)
      {
        /* Copy (pRefIvc, pDataIn) */
        /* Copy (pRefDataIn, pDataout1) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, dataSize);
        if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData1, dataSize);

        if (pxInputParams->useSwKey)
        {
          csdStatus = _CRPC(nhtCsdDecryptDataWithClearTextHostKey) (
            pxInputParams->cryptoAlgorithm,
            pxInputParams->cryptoMode,
            pxInputParams->keys.sw.pClearTextHostKey,
            pxInputParams->keys.sw.clearTextHostKeySize,
            pIvcData,
            pxInputParams->ivcSize,
            ivRefresh,
            xR2rHandle,
            pInData,
            pOutData1,
            dataSize );
        }
        else
        {
          csdStatus = _CRPC(nhtCsdDecryptDataWithSecretContentKey) (
            pxInputParams->cryptoAlgorithm,
            pxInputParams->cryptoMode,
            pxInputParams->keys.KL.cipheredProtectingKeyNumber,
            *(const TNhtProtectingKey**)&pxInputParams->keys.KL.pCipheredProtectingKeys,
            pxInputParams->keys.KL.pCipheredContentKey,
            pxInputParams->keys.KL.cipheredContentKeySize,
            pIvcData,
            pxInputParams->ivcSize,
            ivRefresh,
            xR2rHandle,
            pInData,
            pOutData1,
            dataSize );
        }

        if (csdStatus != CSD_NO_ERROR) break;

        /* Copy (pIvcRef, pDataRefIn) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, dataSize);
        loopCounter += 2;
      }
      else
      {
        if (pxInputParams->cryptoMode == ALIAS_CSD_R2R_CRYPTO_OPERATION_MODE_CTR)
          if (pIvcData) _nhtcsd_r2r_inc_MsbfByteArrayValue (pIvcData, pxInputParams->ivcSize, dataSize/pxInputParams->ivcSize);

        loopCounter += 1;
      }

      if ((pxInputParams->cryptoAlgorithm == CSD_R2R_ALGORITHM_TDES_K1K2K1) &&
          (pxInputParams->cryptoMode == CSD_R2R_CRYPTO_OPERATION_MODE_CBC ))
      {
        if (pIvcData) MSGBUF_SYS_memcpy(pIvcData, pInData, dataSize);
      }

      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);
    }
    else
    {
      if ((pxInputParams->cryptoAlgorithm == CSD_R2R_ALGORITHM_TDES_K1K2K1) &&
          (pxInputParams->cryptoMode == CSD_R2R_CRYPTO_OPERATION_MODE_CBC ))
      {
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, dataSize);
      }

      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);

      loopCounter += 1;
    }
  }

  if (csdStatus == CSD_NO_ERROR)
  {
    if (isMonteCarloNagraException)
      MSGBUF_SYS_memcpy (pxOutputData, pOutData1, dataSize);
    else MSGBUF_SYS_memcpy (pxOutputData, pOutData0, dataSize);
  }

  if (pOutData0) MSGBUF_SYS_free (pOutData0);
  if (pOutData1) MSGBUF_SYS_free (pOutData1);
  if (pInData)   MSGBUF_SYS_free (pInData);
  if (pIvcData)  MSGBUF_SYS_free (pIvcData);

  return csdStatus;
}


/* */
static void _nhtcsd_r2r_inc_MsbfByteArrayValue
(
  unsigned char    * pxMsbfByteArray,
  int                xMsbfByteArraySize,
  unsigned int       xAddValue
)
{
  unsigned int    i = xMsbfByteArraySize/sizeof(unsigned int);
  unsigned char * pCurByte = &pxMsbfByteArray[xMsbfByteArraySize];

  while (i > 0)
  {
    unsigned int value1, value2;

    value1  = ((unsigned int)(*--pCurByte)       );
    value1 |= ((unsigned int)(*--pCurByte)  << 8 );
    value1 |= ((unsigned int)(*--pCurByte)  << 16);
    value1 |= ((unsigned int)(*--pCurByte)  << 24);
    value2 = value1 + xAddValue;
    pCurByte[0] = (unsigned char)(value2 >> 24);
    pCurByte[1] = (unsigned char)(value2 >> 16);
    pCurByte[2] = (unsigned char)(value2 >> 8);
    pCurByte[3] = (unsigned char)(value2);

    if (value2 > value1) return;
    xAddValue = 1;
    i--;
  }
  return;
}
