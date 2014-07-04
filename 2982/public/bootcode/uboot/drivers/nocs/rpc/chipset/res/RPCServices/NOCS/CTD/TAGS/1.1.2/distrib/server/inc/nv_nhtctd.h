/**
**  @file nv_nhtcsd.h
**
** @brief
**    RPC Chipset Security Driver specific API for NOCS Secure chipset harness tests
**
**    This header file describes the API of generic extensions for RPC server
**    related to ECTD API vx.x.x.
**
**    Implementation of this API extension is provided by Nagra. Its usage
**    is reserved for the RPC server. Since RPC server implementation is provided
**    by Nagra, chipset manufacturer does not need to take care of this API
**    (A Nagra internal API).
**
**    This file is part of the Nagra CTD RPC server application delivery package.
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

#ifndef NV_NHT_CTD_H
#define NV_NHT_CTD_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "nocs_nhtctd.h"

/**
 * @mainpage Overview
 *  - @subpage p_preface
 *
 *  <hr>Copyright &copy; 2012 Nagravision. All rights reserved.\n
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
 *  associated to CTD API harness test RPC server.
 *
 *  Implementation of the functions described in this API are generic, meaning
 *  that the implementation is not chipset manufacturer specific. As a
 *  concequence, their implementation is provided by Nagra.
 *
 *  This header file describes an API extensions of the CTD RPC server
 *  associated to CTD API v3.3.3 that are needed by the harness test
 *  RPC-based framework.
 *
 *  This is a pure Nagra internal API.
 *
 *  Good understanding of the CTD API v3.3.3 stands as a pre-requesite for
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
 *  - [...] CSD API documention
 */


 /** @defgroup rpccTd_group CTD RPC server extended API */


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup rpcctd_group
 *
 *  @brief
 *    Get the harness test CTD API version
 *
 *  @param[out]     pxNhtCtdApiVersion
 *                   32 bit value where the function has to write the CSD
 *                   driver API version using the macro NHT_CSD_TOOL_VERSION_INT.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the harness test CSD API.
 *  Use the macro NHT_CSD_TOOL_VERSION_INT to assign the right value.
*/
TCtdStatus nhtCtdGetApiVersion
(
  TCtdUnsignedInt32*  pxNhtCtdApiVersion
);


#ifdef __cplusplus
}
#endif

#endif /* NV_NHT_CTD_H */

