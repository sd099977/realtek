/**
**  @file nv_nht_report.h
**
** @brief
**    Chipset Security Driver report API
**
**    This header file describes API associated to harness test printout
**    report.
**
**    Implementation of this API is provided by Nagra. This API is provided to
**    to the chipset manufacturer in order to let the chipset driver implementation
**    reporting information such as errors, info or debugging data to the harness
**    test application.
**
**    This API is provided as a test facility during NOCS certification.
**    In particular, this API is intended to abstract the concerns associated
**    to the harness test framework environment.
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
**   is stored on a network drive. So either the file shall be moved on
**   a local drive or add the following registry entry on Windows platform
**  (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/


#ifndef _NV_CLIENT_NHT_REPORT_H_
#define _NV_CLIENT_NHT_REPORT_H_


#ifdef __cplusplus
extern "C" {
#endif

/** @mainpage Overview
 *  - @subpage p_preface
 *  - @subpage p_fatal_report
 *  - @subpage p_error_report
 *  - @subpage p_warning_report
 *  - @subpage p_info_report
 *  - @subpage p_debug_report
 *
 *  <hr> <b>Note:\n</b>
 *  Depending on the platform, the CHM file may not open properly if it is stored on a network drive.
 *  So either the file should be moved on a local drive or add the following registry entry on
 *  Windows platform (regedit):
 *  [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\ItssRestrictions] "MaxAllowedZone"=dword:00000003
 *
 *  <hr>Copyright &copy; 2012 Nagravision. All rights reserved.\n
 *  CH-1033 Cheseaux, Switzerland\n
 *  Tel: +41 21 7320311  Fax: +41 21 7320100\n
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
 *  <b>Security Policy of Nagravision Kudelski Group</b>\n
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 */


/** @page p_preface Preface
 *
 *  <h2>Purpose</h2>
 *
 *  This document is intended for the manufacturers of MPEG secure chipsets
 *  who are partners of Nagravision and whose chipset has to pass a NOCS
 *  CSD Harness test certification.\n
 *
 *  This header file describes an API for reporting messages to the
 *  harness test framework (or application). Reported information
 *  are only intended to be handled by human during debugging or problem
 *  investigation during tests and harness certification.
 *
 *  Purpose of this interface is to provide a way to report and trace message
 *  in a way that abstract the harness test framework such as output stream,
 *  printout format and the final application that has to receive it (e.g: if
 *  harness test applications are running off-the-board).
 *
 *  Users are required not to use the low level function described in this API.
 *  Use the associated macros instead.
 *
 *  When using the API RPC server provided by Nagra, implementation of the
 *  low level function (described in this API) is provided by NAGRA.
 *  However, chipset manufacturer are free to provide their own implementation
 *  when using their own API test local applications.
 *
 *  Messages to report are split into 5 categories. Here are the
 *  ones that are defined (in decreasing order of relevance):
 *
 *  - FATAL (error) report
 *  - ERROR report
 *  - WARNING report
 *  - INFO report
 *  - DEBUG report
 *
 *  Please refer to each report category for more information about the role
 *  of each ones.
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

/** @page p_fatal_report FATAL report category
 *
 *  <h2>Purpose</h2>
 *
 *     Fatal reports are intended to report harness test operational errors
 *     encountered during execution of the code that prevent the implementation to
 *     work properly.
 *
 *     Such reports refer to harness test configuration trouble
 *     (e.g: File not found, etc...). These ones shall be solved prior
 *     to concider if a test fails or not. Please note that the fact that
 *     a test run fails or not is not concidered as FATAL (it might be
 *     normal in the case of a negative test)
 *
 *     For passing a harness test certification, no FATAL errors shall
 *     occurs during the certification (test environmnet setup should
 *     be OK first).
 *
 *     Use 'NHT_REPORT_FATAL()' macro for reporting FATAL errors.
 */

/** @page p_error_report ERROR report category
 *
 *  <h2>Purpose</h2>
 *
 *     ERROR reports are intended to provide additional info associated
 *     to errors returned by API functions.
 *
 *     Please note that the present of such error is not necessarily
 *     a certification failer. In case of negative test, presence of
 *     such errors might be required.
 *
 *     When using a Nagra application (provided SW), the chipset
 *     Manufacturer usually does not need to do such message type
 *     report by itself. In this case, such report type is done
 *     by Nagra.
 *
 *     Use 'NHT_REPORT_ERROR()' macro for reporting API function errors.
 */

 /** @page p_warning_report WARNING report category
 *
 *  <h2>Purpose</h2>
 *
 *    WARNING reports are intended to report detected degradated run mode
 *    that do not alter the well running of the API function calls nor
 *    the well running of the test to be executed.
 *
 *    Warning is only intended to notify the user that improvement in the
 *    test could be concidered.
 *
 *    WARNING reports are essentially used for improving the harness test
 *    framework.
 *
 *    Use 'NHT_REPORT_WARNING()' macro for reporting warnings.
 */

 /** @page p_info_report INFO report category
 *
 *  <h2>Purpose</h2>
 *
 *    INFO reports are intended to report important milestones
 *    during the execution of a test that are not related to the
 *    SW implementation. In particular, info report does not
 *    return source code filename and line number...
 *
 *    INFO repots only stands as a facility for tracking test and certification
 *    execution.
 *
 *    Use 'NHT_REPORT_INFO()' macro for reporting important milestone info.
 */

 /** @page p_debug_report DEBUG report category
 *
 *  <h2>Purpose</h2>
 *
 *    Debug report are intended to report debugging and traces information.
 *
 *    DEBUG repots stands as a facility for implementing an API
 *    or/and test applications.
 *
 *    PS: For optimization reason, DEBUG message type reporting is only
 *    effective if the compiling option NHT_REPORT_TRACE_ENABLE is
 *    defined to a non 0 value.
 *
 *    Use 'NHT_REPORT_DEBUG()' macro for reporting debugging or Traces info.
 */


/**
 * @defgroup report_macros Harness test REPORT macros
 */

/**
 * @defgroup ll_report_func Low level report functions (use MACROs instead)
 */

#include "inc/nht_report.h"
#include "inc/rpc_ftrace.h"


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Set the minimum report category level of the remote target
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]  xReportLevel
 *
*/
int nht_setReportLevel
(
  TNhtReportCategory xReportLevel
);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Report CM stdout text line(s)
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in] pxLineText
 *
*/
void nht_reportServerStdout
(
  const char * pxLineText
);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Report CM stderr text line(s)
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in] pxLineText
 *
*/
void nht_reportServerStderr
(
  const char * pxLineText
);

/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Report RPC chipset function tracing
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in] xFTraceType
 *  @param[in] pxFtraceLineText
 *
*/
void nht_reportServerFTrace
(
  int              xCallId,
  TRpcFTraceType   xFTraceType,
  const char     * pxFtraceLineText
);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Enable RPC chipset function tracing
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
int nht_enableServerFTrace (void);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *   Disable RPC chipset function tracing
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
int nht_disableServerFTrace (void);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Restore RPC chipset function tracing
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
int nht_restoreDefaultServerFTrace (void);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Get the CM-defined server version string
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
const char * nht_getCmServerVersion (void);


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Get the NHT server lib version string
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
const char * nht_getNhtServerComponentVersion (void);


#ifdef __cplusplus
}
#endif

#endif /* _NV_CLIENT_NHT_REPORT_H_ */
