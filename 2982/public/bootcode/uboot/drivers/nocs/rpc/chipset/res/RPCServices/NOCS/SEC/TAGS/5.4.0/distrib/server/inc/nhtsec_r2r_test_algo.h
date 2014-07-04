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

#ifndef NHTSEC_R2R_TEST_ALGO_H
#define NHTSEC_R2R_TEST_ALGO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ca_nhtsec.h"


/* */
typedef struct SNhtSec_r2r_test_algoParams
{
  TSecCipherSession cipherSession;
  TBoolean          isLegacy;
  TBoolean          ivEmulate;
  TUnsignedInt16    emi;
  TBoolean          isForEncryption;
  TBoolean          isMonteCarlo;
  TUnsignedInt32    runNumber;
  TUnsignedInt8   * pIv;
  TSize             ivSize;
  TUnsignedInt8   * pInputData;
  TSize             dataSize;
  TSize             keyIdSize;
  TUnsignedInt8   * pKeyId;

} TNhtSec_r2r_test_algoParams;



TSecStatus nhtsec_r2r_testAlgo_run (
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData );

/* */
void nhtsec_r2r_testAlgo_initParams (
  TNhtSec_r2r_test_algoParams * pxParams );


/* */
void nhtsec_r2r_testAlgo_terminateParams (
  TNhtSec_r2r_test_algoParams * pxParams );


#ifdef __cplusplus
}
#endif

#endif /* NHTSEC_R2R_TEST_ALGO_H */
