/**
 * File: $Id:$
 *
 *  This file implements the R2R MonteCarlo test main function.
 *
 *  Copyright (c) 2012-2013 Nagravision. All rights reserved.
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

#include "inc/nhtbsd_r2r_test_algo.h"
#include "inc/nv_nhtbsd.h"
#include <stdio.h>
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/TRACE_nhtbsd.h"


/*----------------------------------------------------------------------------
 *   Static functions declaration
 *---------------------------------------------------------------------------*/

/* */
static TBsdStatus nhtbsd_r2r_testAlgo_doEncryptionTestRun (
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData );


/* */
static TBsdStatus nhtbsd_r2r_testAlgo_doDecryptionTestRun (
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8             * pxOutputData );


/* */
static void _nhtbsd_r2r_inc_MsbfByteArrayValue (
  unsigned char    * pxMsbfByteArray,
  int                xMsbfByteArraySize,
  unsigned int       xAddValue );

/*----------------------------------------------------------------------------
 *   Public function definition
 *---------------------------------------------------------------------------*/


TBsdStatus nhtbsd_r2r_testAlgo_run
(
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData
)
{
  TBsdStatus bsdStatus = BSD_NO_ERROR;


  /* Do the test (according to encryption or decryption */
  if (pxInputParams->isForEncryption)
  {
    bsdStatus = nhtbsd_r2r_testAlgo_doEncryptionTestRun (
      pxInputParams,
      pxOutputData );
  }
  else
  {
    bsdStatus = nhtbsd_r2r_testAlgo_doDecryptionTestRun (
      pxInputParams,
      pxOutputData );
  }

  return bsdStatus;
}


/* */
void nhtbsd_r2r_testAlgo_initParams
(
  TNhtBsd_r2r_test_algoParams * pxParams
)
{
  pxParams->isLegacy        = 0;
  pxParams->ivEmulate       = 0;
  pxParams->cipherSession   = NULL;
  pxParams->emi             = 0;
  pxParams->cryptoAlgorithm = BSD_R2R_ALGORITHM_AES;
  pxParams->cryptoMode      = NHTBSD_R2R_CRYPTO_OPERATION_MODE_ECB;
  pxParams->pIvc            = NULL;
  pxParams->ivcSize         = 0;
  pxParams->pInputData      = NULL;
  pxParams->dataSize        = 0;
  pxParams->isMonteCarlo    = 0;
  pxParams->runNumber       = 1;
  pxParams->isForEncryption = 0;
}


/* */
void nhtbsd_r2r_testAlgo_terminateParams
(
  TNhtBsd_r2r_test_algoParams * pxParams
)
{
  nhtbsd_r2r_testAlgo_initParams (pxParams);
}


/*----------------------------------------------------------------------------
 *   Static functions definition
 *---------------------------------------------------------------------------*/

/* */
static TBsdStatus nhtbsd_r2r_testAlgo_doEncryptionTestRun
(
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData

)
{
  TBsdStatus       bsdStatus = BSD_NO_ERROR;
  TBoolean         isMonteCarloNagraException = 0;
  TUnsignedInt8  * pOutData0 = NULL;
  TUnsignedInt8  * pOutData1 = NULL;
  TUnsignedInt8  * pInData   = NULL;
  TUnsignedInt8  * pIvcData  = NULL;
  TSize            dataSize;
  int              loopCounter = 0;
  TBoolean         ivRefresh = 0;

  /* Check for MonteCarlo Nagravision specific procedure */

  if (!pxInputParams->isLegacy)
  {
    if (pxInputParams->isMonteCarlo                                           &&
        (pxInputParams->cryptoMode == NHTBSD_R2R_CRYPTO_OPERATION_MODE_CBC)   &&
        ((pxInputParams->cryptoAlgorithm == BSD_R2R_ALGORITHM_TDES) ||
         (pxInputParams->cryptoAlgorithm == BSD_R2R_ALGORITHM_AES)))
      isMonteCarloNagraException = 1;
  }
  else isMonteCarloNagraException = 0;

  dataSize = pxInputParams->dataSize;

  if (pxInputParams->useDriverAlloc)
  {
    pOutData0 = _CRPC(bsdAllocateBuffer)((size_t)dataSize);
    pOutData1 = _CRPC(bsdAllocateBuffer)((size_t)dataSize);
  }
  else
  {
    pOutData0 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    pOutData1 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
  }

  if (pxInputParams->pInputData)
  {
    if (pxInputParams->useDriverAlloc)
      pInData = _CRPC(bsdAllocateBuffer)((size_t)dataSize);
    else
      pInData = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);

    MSGBUF_SYS_memcpy (pInData,  pxInputParams->pInputData, dataSize);
  }

  if (pxInputParams->pIvc)
  {
    if (pxInputParams->useDriverAlloc)
      pIvcData = _CRPC(bsdAllocateBuffer)((size_t)pxInputParams->ivcSize);
    else
      pIvcData = (TUnsignedInt8*)MSGBUF_SYS_malloc(pxInputParams->ivcSize);

    MSGBUF_SYS_memcpy (pIvcData, pxInputParams->pIvc, pxInputParams->ivcSize);
    MSGBUF_SYS_memcpy (pOutData1,pxInputParams->pIvc, pxInputParams->ivcSize);
    ivRefresh = 1;
  }
  else
  {
    pIvcData = NULL;
    ivRefresh = 0;
  }

  /* Encryption test run loop */
  while (loopCounter < (int)pxInputParams->runNumber)
  {
    if (pxInputParams->isLegacy)
    {
      bsdStatus = bsdEncryptDataWithSecretContentKey (
        (TBsdR2RAlgorithm)pxInputParams->cryptoAlgorithm,
        pInData,
        pOutData0,
        dataSize );
    }
    else
    {
      bsdStatus = bsdSessionEncrypt (
        pxInputParams->cipherSession,
        pInData,
        pOutData0,
        dataSize,
        pIvcData,
        pxInputParams->ivcSize );
    }

    if (bsdStatus != BSD_NO_ERROR) break;

    if (pxInputParams->isMonteCarlo)
    {
      if (isMonteCarloNagraException)
      {
        /* Copy (pInRefData, pOutRefData1); */
        /* Copy (pIvc, pOutRefData0) */
        if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData1, dataSize);
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pOutData0, pxInputParams->ivcSize);

        if (pxInputParams->isLegacy)
        {
          bsdStatus = bsdEncryptDataWithSecretContentKey (
            (TBsdR2RAlgorithm)pxInputParams->cryptoAlgorithm,
            pInData,
            pOutData1,
            dataSize );
        }
        else
        {
          bsdStatus = bsdSessionEncrypt (
            pxInputParams->cipherSession,
            pInData,
            pOutData1,
            dataSize,
            pIvcData,
           pxInputParams->ivcSize );
        }

        if (bsdStatus != BSD_NO_ERROR) break;

        /* Copy (pIvcRef, pDataOut1) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pOutData1, pxInputParams->ivcSize);
        loopCounter += 2;
      }
      else
      {
        if (!pxInputParams->isLegacy && (pxInputParams->cryptoMode == NHTBSD_R2R_CRYPTO_OPERATION_MODE_CTR))
          if (pIvcData) _nhtbsd_r2r_inc_MsbfByteArrayValue (pIvcData, pxInputParams->ivcSize, dataSize/pxInputParams->ivcSize);

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

  if (bsdStatus == BSD_NO_ERROR)
  {
    if (isMonteCarloNagraException)
      MSGBUF_SYS_memcpy (pxOutputData, pOutData1, dataSize);
    else MSGBUF_SYS_memcpy (pxOutputData, pOutData0, dataSize);

  }

  if (pxInputParams->useDriverAlloc)
  {
    if (pOutData0) _CRPC(bsdFreeBuffer) (pOutData0);
    if (pOutData1) _CRPC(bsdFreeBuffer) (pOutData1);
    if (pInData)   _CRPC(bsdFreeBuffer) (pInData);
    if (pIvcData)  _CRPC(bsdFreeBuffer) (pIvcData);
  }
  else
  {
    if (pOutData0) MSGBUF_SYS_free (pOutData0);
    if (pOutData1) MSGBUF_SYS_free (pOutData1);
    if (pInData)   MSGBUF_SYS_free (pInData);
    if (pIvcData)  MSGBUF_SYS_free (pIvcData);
  }

  return bsdStatus;
}


/* */
static TBsdStatus nhtbsd_r2r_testAlgo_doDecryptionTestRun
(
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData
)
{
  TBsdStatus       bsdStatus = BSD_NO_ERROR;
  TBoolean         isMonteCarloNagraException = 0;
  TUnsignedInt8  * pOutData0 = NULL;
  TUnsignedInt8  * pOutData1 = NULL;
  TUnsignedInt8  * pInData   = NULL;
  TUnsignedInt8  * pIvcData  = NULL;
  TSize            dataSize;
  TUnsignedInt32   loopCounter = 0;
  TBoolean         ivRefresh   = 0;

  if (!pxInputParams->isLegacy)
  {
    if (pxInputParams->isMonteCarlo                                              &&
        (pxInputParams->cryptoMode      == NHTBSD_R2R_CRYPTO_OPERATION_MODE_CBC) &&
        (pxInputParams->cryptoAlgorithm == BSD_R2R_ALGORITHM_AES))
      isMonteCarloNagraException = 1;
  }
  else isMonteCarloNagraException = 0;


  dataSize = pxInputParams->dataSize;

  if (pxInputParams->useDriverAlloc)
  {
    pOutData0 = _CRPC(bsdAllocateBuffer)((size_t)dataSize);
    pOutData1 = _CRPC(bsdAllocateBuffer)((size_t)dataSize);
  }
  else
  {
    pOutData0 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    pOutData1 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
  }

  if (pxInputParams->pInputData)
  {
    if (pxInputParams->useDriverAlloc)
      pInData   = _CRPC(bsdAllocateBuffer)((size_t)dataSize);
    else
      pInData   = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);

    MSGBUF_SYS_memcpy (pInData,  pxInputParams->pInputData, dataSize);
  }

  if (pxInputParams->pIvc)
  {
    if (pxInputParams->useDriverAlloc)
      pIvcData  = _CRPC(bsdAllocateBuffer)((size_t)pxInputParams->ivcSize);
    else
      pIvcData  = (TUnsignedInt8*)MSGBUF_SYS_malloc(pxInputParams->ivcSize);

    MSGBUF_SYS_memcpy (pIvcData, pxInputParams->pIvc, pxInputParams->ivcSize);
    MSGBUF_SYS_memcpy (pOutData1,pxInputParams->pIvc, dataSize);
    ivRefresh = 1;
  }

  /* Encryption test run loop */
  while (loopCounter <pxInputParams->runNumber)
  {
    if (pxInputParams->isLegacy)
    {
      bsdStatus = bsdDecryptDataWithSecretContentKey (
        (TBsdR2RAlgorithm)pxInputParams->cryptoAlgorithm,
        pInData,
        pOutData0,
        dataSize );
    }
    else
    {
      bsdStatus = bsdSessionDecrypt (
        pxInputParams->cipherSession,
        pInData,
        pOutData0,
        dataSize,
        pIvcData,
        pxInputParams->ivcSize );
    }

    if (bsdStatus != BSD_NO_ERROR) break;

    if (pxInputParams->isMonteCarlo)
    {
      if (isMonteCarloNagraException)
      {
        /* Copy (pRefIvc, pDataIn) */
        /* Copy (pRefDataIn, pDataout1) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, pxInputParams->ivcSize);
        if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData1, dataSize);

        if (pxInputParams->isLegacy)
        {
          bsdStatus = bsdDecryptDataWithSecretContentKey (
            (TBsdR2RAlgorithm)pxInputParams->cryptoAlgorithm,
            pInData,
            pOutData1,
            dataSize );
        }
        else
        {
          bsdStatus = bsdSessionDecrypt (
            pxInputParams->cipherSession,
            pInData,
            pOutData1,
            dataSize,
            pIvcData,
            pxInputParams->ivcSize );
        }

        if (bsdStatus != BSD_NO_ERROR) break;

        /* Copy (pIvcRef, pDataRefIn) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, pxInputParams->ivcSize);
        loopCounter += 2;
      }
      else
      {
        if (!pxInputParams->isLegacy && (pxInputParams->cryptoMode == NHTBSD_R2R_CRYPTO_OPERATION_MODE_CTR))
          if (pIvcData) _nhtbsd_r2r_inc_MsbfByteArrayValue (pIvcData, pxInputParams->ivcSize, dataSize/pxInputParams->ivcSize);

        loopCounter += 1;
      }

      if (!pxInputParams->isLegacy &&
          (pxInputParams->cryptoAlgorithm == BSD_R2R_ALGORITHM_TDES) &&
          (pxInputParams->cryptoMode      == NHTBSD_R2R_CRYPTO_OPERATION_MODE_CBC ))

      if (pIvcData) MSGBUF_SYS_memcpy(pIvcData, pInData, pxInputParams->ivcSize);
      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);
    }
    else
    {
      if (!pxInputParams->isLegacy &&
          (pxInputParams->cryptoAlgorithm == BSD_R2R_ALGORITHM_TDES) &&
          (pxInputParams->cryptoMode      == NHTBSD_R2R_CRYPTO_OPERATION_MODE_CBC ))

      if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, pxInputParams->ivcSize);
      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);

      loopCounter += 1;
    }
  }

  if (bsdStatus == BSD_NO_ERROR)
  {
    if (isMonteCarloNagraException)
      MSGBUF_SYS_memcpy (pxOutputData, pOutData1, dataSize);
    else MSGBUF_SYS_memcpy (pxOutputData, pOutData0, dataSize);
  }

  if (pxInputParams->useDriverAlloc)
  {
    if (pOutData0) _CRPC(bsdFreeBuffer) (pOutData0);
    if (pOutData1) _CRPC(bsdFreeBuffer) (pOutData1);
    if (pInData)   _CRPC(bsdFreeBuffer) (pInData);
    if (pIvcData)  _CRPC(bsdFreeBuffer) (pIvcData);
  }
  else
  {
    if (pOutData0) MSGBUF_SYS_free (pOutData0);
    if (pOutData1) MSGBUF_SYS_free (pOutData1);
    if (pInData)   MSGBUF_SYS_free (pInData);
    if (pIvcData)  MSGBUF_SYS_free (pIvcData);
  }

  return bsdStatus;
}


/* */
static void _nhtbsd_r2r_inc_MsbfByteArrayValue
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
