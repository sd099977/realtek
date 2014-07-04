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

#include "inc/nhtsec_r2r_test_algo.h"
#include "inc/nv_nhtsec.h"
#include <stdio.h>
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/TRACE_nhtsec.h"


/* TODO: Move this enum type into an associated emi.h file */
typedef enum ENhtEmi
{
  EMI_DVB_CSA2                    = 0x0000,
  EMI_DVB_CSA3                    = 0x0001,
  EMI_NAGRA_ASA                   = 0x0010,
  EMI_AES_128_CBC_IV_0_SCTE52     = 0x0020,
  EMI_AES_128_ECB_CLEAR           = 0x0021,
  EMI_AES_128_CBC_CLEAR           = 0x0022,
  EMI_TDES_ABA_CBC_IV_0_SCTE52    = 0x0040,
  EMI_TDES_ABA_ECB_CLEAR          = 0x0041,
  EMI_RAW_AES_128_CBC_IV_0_CLEAR  = 0x4020,
  EMI_RAW_AES_128_ECB_CLEAR       = 0x4021,
  EMI_RAW_0x4022                  = 0x4022,
  EMI_RAW_0x4023                  = 0x4023,
  EMI_RAW_0x4024                  = 0x4024,
  EMI_RAW_AES_128_CBC_CLEAR       = 0x4026,
  EMI_RAW_AES_128_COUNTER_CLEAR   = 0x4027,
  EMI_RAW_TDES_ABA_CBC_IV_0_CLEAR = 0x4040,
  EMI_RAW_TDES_ABA_ECB_CLEAR      = 0x4041,
  EMI_RAW_TDES_ABA_CBC_CLEAR      = 0x4043
} TNhtEmi;


/*----------------------------------------------------------------------------
 *   Static functions declaration
 *---------------------------------------------------------------------------*/

/* */
static TSecStatus nhtsec_r2r_testAlgo_doEncryptionTestRun (
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData,
  TSecCipherSession                   xSession,
  TSecFunctionTable                 * pxFunctionTable );


/* */
static TSecStatus nhtsec_r2r_testAlgo_doDecryptionTestRun (
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData,
  TSecCipherSession                   xSession,
  TSecFunctionTable                 * pxFunctionTable );


/* */
static void _nhtsec_r2r_inc_MsbfByteArrayValue (
  unsigned char    * pxMsbfByteArray,
  int                xMsbfByteArraySize,
  unsigned int       xAddValue );


/*----------------------------------------------------------------------------
 *   Public function definition
 *---------------------------------------------------------------------------*/


/* */
TSecStatus nhtsec_r2r_testAlgo_run
(
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData
)
{
  TSecStatus              secStatus;

  TSecFunctionTable * pSecFunctionTable = NULL;

  pSecFunctionTable = _CRPC(secGetFunctionTable) ();
  if (pSecFunctionTable)
  {
    /* Do the test (according to encryption or decryption */
    if (pxInputParams->isForEncryption)
    {
      secStatus = nhtsec_r2r_testAlgo_doEncryptionTestRun (
        pxInputParams,
        pxOutputData,
        pxInputParams->cipherSession,
        pSecFunctionTable );
    }
    else
    {
      secStatus = nhtsec_r2r_testAlgo_doDecryptionTestRun (
        pxInputParams,
        pxOutputData,
        pxInputParams->cipherSession,
        pSecFunctionTable );
    }

  }
  else secStatus = SEC_ERROR;

  return secStatus;
}


/* */
void nhtsec_r2r_testAlgo_initParams
(
  TNhtSec_r2r_test_algoParams * pxParams
)
{
  pxParams->cipherSession                = NULL;
  pxParams->keyIdSize                    = 0;
  pxParams->pKeyId                       = NULL;
  pxParams->isLegacy                     = 0;
  pxParams->ivEmulate                    = 0;
  pxParams->emi                          = 0x4000;
  pxParams->isForEncryption              = 0;
  pxParams->isMonteCarlo                 = 0;
  pxParams->runNumber                    = 1;
  pxParams->pIv                          = NULL;
  pxParams->ivSize                       = 0;
  pxParams->pInputData                   = NULL;
  pxParams->dataSize                     = 0;
}


/* */
void nhtsec_r2r_testAlgo_terminateParams
(
  TNhtSec_r2r_test_algoParams * pxParams
)
{
  nhtsec_r2r_testAlgo_initParams (pxParams);
}


/*----------------------------------------------------------------------------
 *   Static functions definition
 *---------------------------------------------------------------------------*/


/* */
static TSecStatus nhtsec_r2r_testAlgo_doEncryptionTestRun
(
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData,
  TSecCipherSession                   xSession,
  TSecFunctionTable                 * pxFunctionTable
)
{
  TSecStatus      secStatus                  = SEC_NO_ERROR;

  TBoolean        isMonteCarloNagraException = 0;
  TUnsignedInt8 * pOutData0                  = NULL;
  TUnsignedInt8 * pOutData1                  = NULL;
  TUnsignedInt8 * pInData                    = NULL;
  TUnsignedInt8 * pIvcData                   = NULL;
  TSize           dataSize                   = 0;
  TUnsignedInt32  loopCounter                = 0;
  TBoolean        ivRefresh                  = 0;

  dataSize = pxInputParams->dataSize;

  pOutData0 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
  pOutData1 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);

  if (pxInputParams->pInputData)
  {
    pInData   = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pInData,  pxInputParams->pInputData, dataSize);
  }

  if (pxInputParams->pIv)
  {
    pIvcData  = (TUnsignedInt8*)MSGBUF_SYS_malloc (pxInputParams->ivSize);
    MSGBUF_SYS_memcpy (pIvcData, pxInputParams->pIv, pxInputParams->ivSize);
    MSGBUF_SYS_memcpy (pOutData1,pxInputParams->pIv, dataSize);
    ivRefresh = 1;
  }
  else
  {
    pIvcData = NULL;
    ivRefresh = 0;
  }

  /* Check for MonteCarlo Nagravision specific procedure */
  if ( pxInputParams->isMonteCarlo &&
       ((pxInputParams->emi == EMI_RAW_AES_128_CBC_CLEAR)       ||
        (pxInputParams->emi == EMI_AES_128_CBC_CLEAR)           ||
        (pxInputParams->emi == EMI_RAW_0x4023)                  ||
        (pxInputParams->emi == EMI_RAW_0x4022)                  ||
        (pxInputParams->emi == EMI_RAW_AES_128_CBC_IV_0_CLEAR)  ||
        (pxInputParams->emi == EMI_TDES_ABA_CBC_IV_0_SCTE52)    ||
        (pxInputParams->emi == EMI_RAW_TDES_ABA_CBC_IV_0_CLEAR) ||
        (pxInputParams->emi == EMI_RAW_TDES_ABA_CBC_CLEAR)))
    isMonteCarloNagraException = 1;
  else isMonteCarloNagraException = 0;

  /* Encryption test run loop */
  while (loopCounter < pxInputParams->runNumber)
  {
    if (pxInputParams->isLegacy)
    {
      secStatus = secEncryptData (
        (TUnsignedInt8*)pInData,
        (TUnsignedInt8*)pOutData0,
        dataSize );
    }
    else
    {
      secStatus = pxFunctionTable->secSessionEncrypt (
        xSession,
        (TUnsignedInt8*)pInData,
        (TUnsignedInt8*)pOutData0,
        dataSize,
        pIvcData,
        pxInputParams->ivSize );
    }

    if (secStatus != SEC_NO_ERROR) break;

    if (pxInputParams->isMonteCarlo)
    {
      if (isMonteCarloNagraException)
      {
        /* Copy (pInRefData, pOutRefData1); */
        /* Copy (pIvc, pOutRefData0) */
        if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData1, dataSize);
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pOutData0, dataSize);

        if (pxInputParams->isLegacy)
        {
          secStatus = secEncryptData (
            (TUnsignedInt8*)pInData,
            (TUnsignedInt8*)pOutData1,
            dataSize );
        }
        else
        {
          secStatus = pxFunctionTable->secSessionEncrypt (
            xSession,
            (TUnsignedInt8*)pInData,
            (TUnsignedInt8*)pOutData1,
            dataSize,
            pIvcData,
            pxInputParams->ivSize );
        }

        if (secStatus != SEC_NO_ERROR) break;

        /* Copy (pIvcRef, pDataOut1) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pOutData1, dataSize);
        loopCounter += 2;
      }
      else
      {
        if ((pxInputParams->emi == EMI_RAW_AES_128_COUNTER_CLEAR) ||
            (pxInputParams->emi == EMI_RAW_0x4024))
          if (pIvcData) _nhtsec_r2r_inc_MsbfByteArrayValue (pIvcData, pxInputParams->ivSize, dataSize/pxInputParams->ivSize);

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

  if (secStatus == SEC_NO_ERROR)
  {
    if (isMonteCarloNagraException)
      MSGBUF_SYS_memcpy (pxOutputData, pOutData1, dataSize);
    else MSGBUF_SYS_memcpy (pxOutputData, pOutData0, dataSize);

  }

  if (pOutData0) MSGBUF_SYS_free (pOutData0);
  if (pOutData1) MSGBUF_SYS_free (pOutData1);
  if (pInData)   MSGBUF_SYS_free (pInData);
  if (pIvcData)  MSGBUF_SYS_free (pIvcData);

  return secStatus;
}


/* */
static TSecStatus nhtsec_r2r_testAlgo_doDecryptionTestRun
(
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData,
  TSecCipherSession                   xSession,
  TSecFunctionTable                 * pxFunctionTable
)
{
  TSecStatus          secStatus = SEC_NO_ERROR;

  TBoolean         isMonteCarloNagraException = 0;
  TUnsignedInt8  * pOutData0 = NULL;
  TUnsignedInt8  * pOutData1 = NULL;
  TUnsignedInt8  * pInData   = NULL;
  TUnsignedInt8  * pIvcData  = NULL;
  TSize            dataSize;
  TUnsignedInt32   loopCounter = 0;
  TBoolean         ivRefresh = 0;

  dataSize = pxInputParams->dataSize;

  pOutData0 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
  pOutData1 = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);

  if (pxInputParams->pInputData)
  {
    pInData   = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pInData,  pxInputParams->pInputData, dataSize);
  }

  if (pxInputParams->pIv)
  {
    pIvcData  = (TUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    MSGBUF_SYS_memcpy (pIvcData, pxInputParams->pIv, dataSize);
    MSGBUF_SYS_memcpy (pOutData1,pxInputParams->pIv, dataSize);
    ivRefresh = 1;
  }

  /* Check for MonteCarlo Nagravision specific procedure */
  if (pxInputParams->isMonteCarlo &&
      ((pxInputParams->emi == EMI_RAW_0x4023)                 ||
       (pxInputParams->emi == EMI_RAW_0x4022)                 ||
       (pxInputParams->emi == EMI_RAW_AES_128_CBC_IV_0_CLEAR) ||
       (pxInputParams->emi == EMI_RAW_AES_128_CBC_CLEAR)))
    isMonteCarloNagraException = 1;
  else isMonteCarloNagraException = 0;

  /* Encryption test run loop */
  while (loopCounter <pxInputParams->runNumber)
  {
    if (pxInputParams->isLegacy)
    {
      secStatus = secDecryptData (
        (TUnsignedInt8*)pOutData0,
        (TUnsignedInt8*)pInData,
        dataSize );
    }
    else
    {
      secStatus = pxFunctionTable->secSessionDecrypt (
        xSession,
        (TUnsignedInt8*)pInData,
        (TUnsignedInt8*)pOutData0,
        dataSize,
        pIvcData,
        pxInputParams->ivSize );
    }

    if (secStatus != SEC_NO_ERROR) break;

    if (pxInputParams->isMonteCarlo)
    {
      if (isMonteCarloNagraException)
      {
        /* Copy (pRefIvc, pDataIn) */
        /* Copy (pRefDataIn, pDataout1) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, dataSize);
        if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData1, dataSize);

        if (pxInputParams->isLegacy)
        {
          secStatus = secDecryptData (
            (TUnsignedInt8*)pInData,
            (TUnsignedInt8*)pOutData1,
            dataSize );
        }
        else
        {
          secStatus = pxFunctionTable->secSessionDecrypt (
            xSession,
            (TUnsignedInt8*)pInData,
            (TUnsignedInt8*)pOutData1,
            dataSize,
            pIvcData,
            pxInputParams->ivSize );
        }

        if (secStatus != SEC_NO_ERROR) break;

        /* Copy (pIvcRef, pDataRefIn) */
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, dataSize);
        loopCounter += 2;
      }
      else
      {
        if ((pxInputParams->emi == EMI_RAW_AES_128_COUNTER_CLEAR) ||
            (pxInputParams->emi == EMI_RAW_0x4024))
          if (pIvcData) _nhtsec_r2r_inc_MsbfByteArrayValue (pIvcData, pxInputParams->ivSize, dataSize/pxInputParams->ivSize);

        loopCounter += 1;
      }

      if ((pxInputParams->emi  == EMI_RAW_TDES_ABA_CBC_IV_0_CLEAR) ||
          (pxInputParams->emi  == EMI_RAW_TDES_ABA_CBC_CLEAR))
      {
        if (pIvcData) MSGBUF_SYS_memcpy(pIvcData, pInData, dataSize);
      }

      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);
    }
    else
    {
      if ((pxInputParams->emi == EMI_RAW_TDES_ABA_CBC_IV_0_CLEAR) ||
          (pxInputParams->emi == EMI_RAW_TDES_ABA_CBC_CLEAR))
      {
        if (pIvcData) MSGBUF_SYS_memcpy (pIvcData, pInData, dataSize);
      }

      if (pInData) MSGBUF_SYS_memcpy (pInData, pOutData0, dataSize);

      loopCounter += 1;
    }
  }

  if (secStatus == SEC_NO_ERROR)
  {
    if (isMonteCarloNagraException)
      MSGBUF_SYS_memcpy (pxOutputData, pOutData1, dataSize);
    else MSGBUF_SYS_memcpy (pxOutputData, pOutData0, dataSize);
  }

  if (pOutData0) MSGBUF_SYS_free (pOutData0);
  if (pOutData1) MSGBUF_SYS_free (pOutData1);
  if (pInData)   MSGBUF_SYS_free (pInData);
  if (pIvcData)  MSGBUF_SYS_free (pIvcData);

  return secStatus;
}


/* */
static void _nhtsec_r2r_inc_MsbfByteArrayValue
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
