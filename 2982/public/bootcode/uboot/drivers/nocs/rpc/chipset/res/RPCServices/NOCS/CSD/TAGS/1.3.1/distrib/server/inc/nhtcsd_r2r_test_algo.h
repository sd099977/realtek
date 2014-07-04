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

#ifndef NHTCSD_R2R_TEST_ALGO_H
#define NHTCSD_R2R_TEST_ALGO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "nocs_nhtcsd.h"


typedef struct SNhtCsd_r2r_test_algoParams
{
  TCsdR2RAlgorithm             cryptoAlgorithm;
  TCsdR2RCryptoOperationMode   cryptoMode;
  TCsdUnsignedInt8           * pIvc;
  TCsdSize                     ivcSize;
  TCsdUnsignedInt8           * pInputData;
  TCsdSize                     dataSize;
  TCsdBoolean                  isMonteCarlo;
  TCsdUnsignedInt32            runNumber;
  TCsdBoolean                  useSwKey;
  TCsdBoolean                  isForEncryption;

  union
  {
    struct
    {
      TCsdUnsignedInt8       * pClearTextHostKey;
      TCsdSize                 clearTextHostKeySize;
    } sw;

    struct
    {
      TCsdUnsignedInt8       * pCipheredContentKey;
      TCsdSize                 cipheredContentKeySize;
      TNhtProtectingKey      * pCipheredProtectingKeys;
      TCsdUnsignedInt32        cipheredProtectingKeyNumber;
    } KL;
  } keys;

} TNhtCsd_r2r_test_algoParams;



TCsdStatus nhtcsd_r2r_testAlgo_run (
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8                  * pxOutputData );

/* */
void nhtcsd_r2r_testAlgo_initParams (
  TNhtCsd_r2r_test_algoParams * pxParams );


/* */
void nhtcsd_r2r_testAlgo_terminateParams (
  TNhtCsd_r2r_test_algoParams * pxParams );


#ifdef __cplusplus
}
#endif

#endif /* NHTCSD_R2R_TEST_ALGO_H */
