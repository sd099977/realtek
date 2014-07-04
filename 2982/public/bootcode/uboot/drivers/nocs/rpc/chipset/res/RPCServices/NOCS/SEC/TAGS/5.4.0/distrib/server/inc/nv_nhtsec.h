/**
**  @file nv_nhtcsd.h
**
** @brief
**    RPC Chipset Security Driver specific API for NOCS Secure chipset harness tests
**
**    This header file describes the API of generic extensions for RPC server
**    related to SEC API v5.5.1.
**
**    Implementation of this API extension is provided by Nagra. Its usage
**    is reserved for the RPC server. Since RPC server implementation is provided
**    by Nagra, chipset manufacturer does not need to take care of this API
**    (A Nagra internal API).
**
**    This file is part of the Nagra SEC RPC server application delivery package.
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
**   is stored on a network drive. So either the file should be moved on
**   a local drive or add the following registry entry on Windows platform
**  (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/

#ifndef NV_NHT_SEC_H
#define NV_NHT_SEC_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "ca_nhtsec.h"
#include "inc/nhtsec_r2r_test_algo.h"

/**
 * @mainpage Overview
 *  - @subpage p_preface
 *
 *  <hr>Copyright &copy; 2013 Nagravision. All rights reserved.\n
 *  CH-1033 Cheseaux, Switzerland\n
 *  Tel: +41 21 7320311  Fax: +41 21 7320100\n
 *  http://www.nagra.com
 *
 *  All trademarks and registered trademarks are the property of their
 *  respective owners.
 *
 *  This document is supplied with an understanding that the notice(s)
 *  herein or any other contractual agreement(s) made that instigated the
 *  delivery of a hard copy, electronic copy, facsimile or file transfer
 *  of this document are strictly observed and maintained.
 *
 *  The information contained in this document is subject to change without
 *  notice.
 *
 *  <b>Security Policy of Nagravision Kudelski Group</b>\n
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 */


/** @page p_preface Preface
 *
 *  <h2>Purpose</h2>
 *
 *  This document is intended to provide some additional generic functions
 *  associated to SEC API harness test RPC server.
 *
 *  Implementation of the functions described in this API are generic, meaning
 *  that the implementation is not chipset manufacturer specific. As a
 *  concequence, its implementation is provided by Nagra.
 *
 *  This header file describes an API extensions of the SEC RPC server
 *  associated to SEC API v4.1.0 that are needed by the harness test
 *  RPC-based framework.
 *
 *  This is a pure Nagra internal API.
 *
 *  Good understanding of the SEC API v4.1.0 stands as a pre-requesite for
 *  reading this API.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for MPEG secure chipset manufacturers
 *  implementing NOCS requirements and candidate to a NOCS certification.
 *
 *  <hr><h2>References</h2>
 *  - [EMI] Nagravision, System Architecture, Encryption Method Indicator
 *     Specification, Version 1.0.7\n
 *  - [NOCS3REQ] Nagravision, NOCS3.0 Security Requirements Specification\n
 *  - [...] SEC API documention
 */


 /** @defgroup rpcsec_group SEC RPC server extended API */

 /** @defgroup rpc_nhtsec_r2r R2R RPC extended API */

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup rpcsec_group
 *
 *  @brief
 *    Get the harness test SEC API version
 *
 *  @param[out]     pxApiVersion
 *                   32 bit value where the function has to write the SEC
 *                   driver API version using the macro NHT_SECAPI_VERSION_INT.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR_BAD_PARAMETER
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the harness test SEC API.
 *  Use the macro NHT_CSD_TOOL_VERSION_INT to assign the right value.
*/
TSecStatus nhtSecGetNhtSecApiVersion
(
  TUnsignedInt32 *  pxApiVersion
);


/*!
 *  @ingroup rpc_nhtsec_r2r
 *
 *  @brief
 *    Locally perform Nagra R2R loop test procedure.
 *
 *  @param[in]      pxInputParams
 *                   Input test procedure parameters.
 *  @param[in]      pxOutputData
 *                   Buffer where the output result should be put in.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR_NOT_IMPLEMENTED
 *              The requested operation is not implemented in the chipset.
 *  @retval   SEC_ERROR_BAD_PARAMETER
 *              At least one of the passed parameters is invalid.
 *  @retval   SEC_ERROR_BAD_EMI
 *              The input EMI handling is not supported by the SEC driver.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This extended upper level function implements loop R2R procedure
 *  (such as MonteCarlo test).
 *
 *  This function has been introduced in order to boost such a test execution
 *  in an RPC environment by executing the overall R2R elementary iterations
 *  of the test locally.
 *
 *  The application is responsible for providing IV and input data  with a
 *  size which strictly equal to a data crypto block size (usually 16 bytes).
 *
 *  Do not use this function is your intention is to encrypt or decrypt
 *  data having a size greater than the elementary crypto block size.
 *
 *  Application using this function is responsible for having pre-allocated
 *  the pxOutputBuffer prior to call this function. Allocation size of
 *  this buffer should fit the crypto elementary block size as well.
 *
 * @note
 *    This function does not overwrite any other functions of the SEC.
 *
 *    Implementation of this function is provided by Nagra. In particular,
 *    its implementation makes usage of the other low-level R2R function
 *    described in this API header file.
 *
 *    As a result, all other R2R functions described in the API header file
 *    should have been implemented in order to successfully make usage of
 *    this function.
*/
TSecStatus nhtsec_r2r_monteCarlo_test_run
(
  const TNhtSec_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData
);


#ifdef __cplusplus
}
#endif

#endif /* NV_NHT_SEC_H */

