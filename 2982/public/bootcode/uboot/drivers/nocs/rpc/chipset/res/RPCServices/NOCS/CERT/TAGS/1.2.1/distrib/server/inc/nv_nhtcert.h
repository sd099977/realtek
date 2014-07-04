/**
**  @file nv_nhtcert.h
**
** @brief
**    RPC Chipset Security Driver specific API for NOCS Secure chipset harness tests
**
**    This header file describes the API of generic extensions for RPC server
**    related to CERT API v1.3.x.
**
**    Implementation of this API extension is provided by Nagra. Its usage
**    is reserved for harness test Nagra provided SW. Since harness test implementation
*     is provided by Nagra, chipset manufacturer does not need to take care of this API
**    (A Nagra internal API).
**
**    This file is part of the Nagra CERT RPC target application delivery package.
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

#ifndef NV_NHT_CERT_H
#define NV_NHT_CERT_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "ca_cert.h"
#include "ca_cert_impl.h"

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
 *  associated to CERT API harness test framework.
 *
 *  Implementation of the functions described in this API are generic, meaning
 *  that the implementation is not chipset manufacturer specific. As a
 *  concequence, their implementation is provided by Nagra.
 *
 *  This header file describes an API extensions of the CERT RPC server
 *  associated to CERT API v1.3.x that are needed by the harness test
 *  RPC-based framework.
 *
 *  This is a pure Nagra internal API.
 *
 *  Good understanding of the CERT API v1.3.x stands as a pre-requesite for
 *  reading this API.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for MPEG secure chipset manufacturers
 *  implementing NOCS requirements and candidate to a NOCS certification.
 *
 *  <hr><h2>References</h2>
*/


 /** @defgroup lockMgt CERT lock management */

 /** @defgroup rpc_nhtbsd_ctrl_server RPC report functions */




/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

typedef TCertUInt8 TNhtCert20CharsString[20];

/******************************************************************************/
/*                                                                            */
/*                           FUNCTION TABLE DEFINITION                        */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup rpc_nhtcert_info
 *
 *  @brief
 *    Get the RPC service name (here "CERT").
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[out]  xServiceName
 *                the service name
 *
 *  @retval   CERT_NO_ERROR
 *              Initialization was completed successfully.
 *
 *  Get the CERT service name. Since harness test API function is
 *  CERT specific, the function only return the "CERT" string patern.
*/

TCertStatus nhtCertGetServiceName
(
  TNhtCert20CharsString xServiceName
);


/**
 *  @ingroup rpc_nhtcert_info
 *
 *  @brief
 *    Get the harness test CERT API version
 *
 *  @param[out]     pxNhtCsdApiVersion
 *                   32 bit value where the function has to write the CERT
 *                   driver API version using the macro NHT_CERT_TOOL_VERSION_INT.
 *
 *  @retval   CERT_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CERT_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CERT_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
*/
TCertStatus nhtGetNhtCertApiVersion
(
  TCertUInt32 *  pxNhtCertApiVersion
);


#ifdef __cplusplus
}
#endif

#endif /* NV_NHT_CERT_H */

