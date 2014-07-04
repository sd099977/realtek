/**
**  @file nv_nhtbsd.h
**
** @brief
**    RPC Chipset Security Driver specific API for NOCS Secure chipset harness tests
**
**    This header file describes the API of generic extensions for RPC server
**    related to BSD API v3.3.0.
**
**    Implementation of this API extension is provided by Nagra. Its usage
**    is reserved for harness test Nagra provided SW. Since harness test implementation
*     is provided by Nagra, chipset manufacturer does not need to take care of this API
**    (A Nagra internal API).
**
**    This file is part of the Nagra BSD RPC target application delivery package.
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

#ifndef NV_NHT_BSD_H
#define NV_NHT_BSD_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "nocs_nhtbsd.h"
#include "inc/nhtbsd_r2r_test_algo.h"

/**
 * @mainpage Overview
 *  - @subpage p_preface
 *
 *  <hr>Copyright &copy; 2012-2013 Nagravision. All rights reserved.\n
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
 *  associated to BSD API harness test framework.
 *
 *  Implementation of the functions described in this API are generic, meaning
 *  that the implementation is not chipset manufacturer specific. As a
 *  concequence, their implementation is provided by Nagra.
 *
 *  This header file describes an API extensions of the BSD RPC server
 *  associated to BSD API v3.3.2 that are needed by the harness test
 *  RPC-based framework.
 *
 *  This is a pure Nagra internal API.
 *
 *  Good understanding of the BSD API v3.3.2 stands as a pre-requesite for
 *  reading this API.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for MPEG secure chipset manufacturers
 *  implementing NOCS requirements and candidate to a NOCS certification.
 *
 *  <hr><h2>References</h2>
*/


 /** @defgroup rpc_nhtbsd_info BSD extended API info */

 /** @defgroup rpc_nhtbsd_ctrl_server RPC report functions */


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup rpc_nhtbsd_info
 *
 *  @brief
 *    Get the harness test CSD API version
 *
 *  @param[out]     pxNhtBsdApiVersion
 *                   32 bit value where the function has to write the BSD
 *                   driver API version using the macro NHT_BSD_TOOL_VERSION_INT.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   BSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   BSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the harness test BSD API.
 *  Use the macro NHT_BSD_TOOL_VERSION_INT to assign the right value.
*/
TBsdStatus nhtGetNhtBsdApiVersion
(
  TUnsignedInt32*  pxNhtBsdApiVersion
);


/**
 *  @ingroup rpc_nhtbsd_info
 *
 *  @brief
 *    Get the BSD status CM's specific offset value (BSD_STATUS_OFFSET)
 *
 *  @param[out]     pxBsdOffsetValue
 *                   32 bit value where the function has to write the BSD
 *                   driver API BSD_STATUS_OFFSET value.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   BSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   BSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the BSD status CM's specific offset value.
*/
TBsdStatus nhtBsdGetBsdStatusOffsetValue
(
  TUnsignedInt32 * pxBsdOffsetValue
);


/******************************************************************************/
/*                                                                            */
/*                             SERVER CTRL function                           */
/*                                                                            */
/******************************************************************************/


/*!
 *  @ingroup rpc_nhtbsd_r2r
 *
 *  @brief
 *    Locally perform Nagra R2R loop test procedure.
 *
 *  @param[in]      pxInputParams
 *                   Input test procedure parameters.
 *  @param[in]      pxOutputData
 *                   Buffer where the output result should be put in.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *              The key path handle passed as parameter is invalid.
 *  @retval   CSD_ERROR
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
 *    This function does not overwrite any other functions of the CSD.
 *
 *    Implementation of this function is provided by Nagra. In particular,
 *    its implementation makes usage of the other low-level R2R function
 *    described in this API header file.
 *
 *    As a result, all other R2R functions described in the API header file
 *    should have been implemented in order to successfully make usage of
 *    this function.
*/
TBsdStatus nhtbsd_r2r_monteCarlo_test_run (
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData );



/******************************************************************************/
/*                                                                            */
/*                             SERVER CTRL function                           */
/*                                                                            */
/******************************************************************************/



/**
 *  @ingroup rpc_nhtbsd_ctrl_server
 *
 *  @brief
 *    Terminate server activity
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval   CSD_NO_ERROR
 *              Server successfully terminated.
 *
*/
TBsdStatus nhtBsdServerTerminate (void);

#ifdef __cplusplus
}
#endif

#endif /* NV_NHT_BSD_H */

