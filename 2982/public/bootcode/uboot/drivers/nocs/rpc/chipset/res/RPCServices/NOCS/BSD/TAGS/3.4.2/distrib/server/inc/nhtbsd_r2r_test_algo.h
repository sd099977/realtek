/**
 * File: $Id:$
 *
 *  This header file implements the R2R MonteCarlo test main function.
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

#ifndef NHTBSD_R2R_TEST_ALGO_H
#define NHTBSD_R2R_TEST_ALGO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nocs_nhtbsd.h"


typedef enum
{
  NHTBSD_R2R_CRYPTO_OPERATION_MODE_ECB  = 0,
  NHTBSD_R2R_CRYPTO_OPERATION_MODE_CBC  = 1,
  NHTBSD_R2R_CRYPTO_OPERATION_MODE_CTR  = 2,
  LAST_NHTBSD_R2R_CRYPTO_OPERATION_MODE = 3,

} TNhtBsdCryptoMode;


/* */
typedef struct SNhtBsd_r2r_test_algoParams
{
  TBoolean           isLegacy;
  TBoolean           useDriverAlloc;
  TBoolean           ivEmulate;
  TBsdCipherSession  cipherSession;
  TUnsignedInt16     emi;
  TBsdR2RAlgorithm   cryptoAlgorithm;
  TNhtBsdCryptoMode  cryptoMode;
  TUnsignedInt8    * pIvc;
  TSize              ivcSize;
  TUnsignedInt8    * pInputData;
  TSize              dataSize;
  TBoolean           isMonteCarlo;
  TUnsignedInt32     runNumber;
  TBoolean           isForEncryption;

} TNhtBsd_r2r_test_algoParams;


/* */
TBsdStatus nhtbsd_r2r_testAlgo_run (
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData );


/* */
void nhtbsd_r2r_testAlgo_initParams (
  TNhtBsd_r2r_test_algoParams * pxParams );


/* */
void nhtbsd_r2r_testAlgo_terminateParams (
  TNhtBsd_r2r_test_algoParams * pxParams );


#ifdef __cplusplus
}
#endif

#endif /* NHTBSD_R2R_TEST_ALGO_H */
