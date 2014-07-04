/**
 * File: $Id:$
 *
 *  This file implements the server specific CSD API/EAPI function traces.
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


#ifndef _TRACE_NV_NHTCSD_H_
#define _TRACE_NV_NHTCSD_H_


#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "nocs_csd.h"
#include "nocs_nhtcsd.h"
#include "inc/nv_nhtcsd.h"
#include "inc/rpc_ftrace.h"


#ifdef _NHT_RPC_TRACE_ON_

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

#define TRACE_nhtCsdOpenR2RSession                  nhtCsdOpenR2RSession
#define TRACE_nhtCsdCloseR2RSession                 nhtCsdCloseR2RSession
#define TRACE_nhtCsdEncryptDataWithClearTextHostKey nhtCsdEncryptDataWithClearTextHostKey
#define TRACE_nhtCsdDecryptDataWithClearTextHostKey nhtCsdDecryptDataWithClearTextHostKey
#define TRACE_nhtCsdEncryptDataWithSecretContentKey nhtCsdEncryptDataWithSecretContentKey
#define TRACE_nhtCsdDecryptDataWithSecretContentKey nhtCsdDecryptDataWithSecretContentKey
#define TRACE_nhtcsd_r2r_monteCarlo_test_run        nhtcsd_r2r_monteCarlo_test_run

/* */
TCsdStatus _CRPC(nhtCsdOpenR2RKeyPathHandle) (
  TCsdR2RKeyPathHandle ** pxR2RKeyPathHandle );

/* */
TCsdStatus _CRPC(nhtCsdCloseR2RKeyPathHandle) (
  TCsdR2RKeyPathHandle * pxR2RKeyPathHandle );

/* */
TCsdStatus _CRPC(csdEncryptDataWithClearTextHostKey) (
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TCsdR2RKeyPathHandle       * pxR2RKeyPathHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize );

/* */
TCsdStatus _CRPC(csdDecryptDataWithClearTextHostKey) (
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TCsdR2RKeyPathHandle       * pxR2RKeyPathHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize );

/* */
TCsdStatus _CRPC(csdEncryptDataWithSecretContentKey) (
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8              * pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8              * pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TCsdR2RKeyPathHandle          * pxR2RKeyPathHandle,
  const TCsdUnsignedInt8              * pxInputData,
        TCsdUnsignedInt8              * pxOutputData,
        TCsdSize                        xDataSize );

/* */
TCsdStatus _CRPC(csdDecryptDataWithSecretContentKey) (
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8*              pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8*              pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                   xRefreshIv,
        TCsdR2RKeyPathHandle*          pxR2RKeyPathHandle,
  const TCsdUnsignedInt8*              pxInputData,
        TCsdUnsignedInt8*              pxOutputData,
        TCsdSize                        xDataSize );

#endif /*  _NHT_RPC_TRACE_ON_ */

#ifdef __cplusplus
}
#endif

#endif /* _TRACE_NV_NHTCSD_H_ */
