/**
**  @file nocs_nhtbsd.h
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset harness tests
**
**    This header file describes the API extensions of the BSD driver API
**    v3.4.3 that need to be implemented by the Chipset Manufacturer in
**    order to be able to comply with the Harness test toolkit provided by
**    Nagra.
**
**    Such extensions must be implemented by the Chipset Manufacturer the
**    same way as the Chipset Manufucturer has to implement the BSD driver
**    API.
**
**    Implementing the function extensions described in this API do not
**    release the Chipset Manufucturer for implementing all functions
**    described in the BSD driver API v 3.4.3.
**
**    This API extension is intended to provide test facilities associated
**    to a NOCS certification by abstracting additional specific Chipset
**    Manufacturer resource handling not covered by the BSD API
**    (e.g: customer's specific structures)
**
**  $Id:$
**  $Change:$
**
**    + Based on BSD EAPI version 1.0.0
**      + Remove buffer allocation functions in the EAPI because
**        declared now in the BSD base API v3.4.3.
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

#ifndef NHT_BSD_H
#define NHT_BSD_H


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the version number of the BSD API. Note also that this version number
 * does not correspond to the identifier of the software implementation version.
*/
#define NHTBSDAPI_VERSION_MAJOR    3
#define NHTBSDAPI_VERSION_MEDIUM   0
#define NHTBSDAPI_VERSION_MINOR    1


/** @page p_history History
 *
 *   - <b> 1.1.0 2012/10/29 Nicolas Grosclaude</b>
 *     - Introduce functions associated to BSD NOCS harness test.
 *       certification. Based on BSD API 3.4.3
 *
 */

/******************************************************************************/
/*                                                                            */
/*                               INCLUDE FILES                                */
/*                                                                            */
/******************************************************************************/

#include "nocs_bsd_impl.h"
#include "nocs_bsd.h"


/******************************************************************************/
/*                                                                            */
/*                             OVERALL DOCUMENTATION                          */
/*                                                                            */
/******************************************************************************/


/**
 * @mainpage Overview
 *  - @subpage p_preface
 *  - @subpage p_history
 *  - @subpage p_printout
 *  - @subpage p_debug
 *  - @subpage p_implementation
 *  - @subpage p_memory_allocation
 *
 *  <hr>Copyright &copy; 2012 Nagravision. All rights reserved.<br>
 *  CH-1033 Cheseaux, Switzerland<br>
 *  Tel: +41 21 7320311  Fax: +41 21 7320100<br>
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
 *  <b>Security Policy of Nagravision Kudelski Group</b><br>
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 *
 */


/** @page p_preface Preface
 *
 *  <h2>Purpose</h2>
 *
 *  This header file describes an API extensions of the BSD driver API
 *  v3.3.0 that needs to be implemented by the Chipset Manufacturer in
 *  order to comply with the BSD harness test toolkit provided by Nagra.
 *
 *  This API extension is first intended to provide test facilities
 *  associated to a NOCS BSD harness test certification by preventing
 *  the chipset manufacturer to implement its own BSD test application.
 *  BSD test applications will be provided by Nagra.
 *
 *  This API shall be implemented by the chipset manufacturers for any
 *  new NOCS secure chipset that is candidate to a Nagra NOCS certification.
 *
 *  Implementing the BSD function extensions described in this API do not
 *  release the Chipset Manufucturer for implementing all functions
 *  described in the BSD driver API.
 *
 *  Good understanding of the BSD API v3.3.0 stands as a pre-requesite for
 *  reading this API.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for MPEG secure chipset manufacturers
 *  implementing NOCS requirements and candidate to a NOCS certification.
 *
 *  <hr><h2>References</h2>
 *  [EMI] Nagravision, System Architecture, Encryption Method Indicator Specification,
 *         Version 1.0.7
 */


/** @page p_printout bsdPrint() usage restriction
 *
 *  The BSD driver implementation is not allowed to call the bsdPrint()
 *  function for its own purpose. Only the upper level application SW layer
 *  is allowed to call this function.
 *
 *  Since purpose of the harness test framework is to test all functions
 *  defined in the BSD base API, Chipset Manufacturer shall provide the
 *  implementation of bsdPrint() function any way.
 *
 *  See also chapter called "Harness test framework BSD debug facilities".
*/


/** @page p_debug Harness test framework BSD debug facilities
 *
 *  During SW development of the BSD, implementation of BSD driver is allowed
 *  to report its own string-based debug traces directly to the harness test
 *  framework provided by Nagra.
 *
 *  For this purpose, BSD driver implementation shall report debug info to the
 *  harness test framework using the NHT_REPORT_xxx() special functions
 *  (see file "nht_report.h").
 *
 *  Such debug printout may only be used as investigation facilities during
 *  BSD driver implementation toubleshooting when using the Nagra provided
 *  harness test framework. In any case, BSD driver debug
 *  printout does not serve for certifying a chipset using the harness test
 *  frame work.
 *
 *  Final version of the BSD driver shall never make direct calls to
 *  NHT_REPORT_xxx() functions by its own, since NHT_REPORT_xxx() implementation
 *  is only provided for (and with) harness test framework
 *
 *  Note: Implementation of the NHT_REPORT_xxx() functions as delivered with
 *  the BSD harness test framework  will take care to carry such string based
 *  debug traces to the harness test framework (e.g: for remote printout)
 *  according to the the RPC topology (e.g: Ethernet, RS232, etc...)
 *
*/

/** @page p_implementation NOCS non-mandatory functions implementation
 *
 *  Nagra BSD applications based on this extended API require that all
 *  functions defined in BSD driver API v3.3.0 are implemented (all ones
 *  are referenced in the BSD application src code).
 *
 *  As a concequence, functions that were mentioned as not required to be
 *  implemented shall be implemented at least as simple function returning
 *  "BSD_ERROR_NOT_IMPLEMENTED" error status.
 *
 *  If not, the application generation will fail at "link" time...
 *
 *  Such dummy implementation only applies for harness test application usage.
 *
 *  This concern does not apply to the BSD driver that shall be delivered
 *  to the STB manufucaturer. As a concequence, dummy implementation of such
 *  functions are part of the harness test framework extension that the chipset
 *  manufacturer shall implement, but not part of the BSD driver delivery-out
 *  itself.
 *  In particular, dummy implementation of such functions does not need to
 *  be part of the STB manufacturer delivery-out.
 */


/** @page p_memory_allocation Pool Memory allocation external resource
 *
 *  This chapter applies to non-OS based BSD application.
 *
 *  Since base BSD driver implementation implicitely requires resource
 *  memory allocation (static or dynamic allocation), a challenge may
 *  occur during the implementation of the BSD driver when considering
 *  dynamic allocation:
 *
 *  In a non-OS-based BSD application context, there is no heap memory
 *  allocation available (e.g: free() or malloc() functions).
 *
 *  One solution might be to consider memory pool allocation resource
 *  that provide dynamic allocation for the BSD driver from a
 *  statically allocated buffer.
 *
 *  Nagra harness test framework implicitely provides an implementation
 *  of such a memory pool for Nagra internal purpose . This resource
 *  implementation is however reserved for harness test framework.
 *
 *  In any case, this harness test memory pool implementation shall not be
 *  directly re-used or called internally of the BSD driver for its internal
 *  purpose. If considering memory pool allocation in the BSD driver
 *  implementation, Chipset Manufacturer is required to provide its own
 *  implementation of this resource.
 */


/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/

/** @defgroup nht_driversetting Driver Settings */

/** @defgroup nht_info Chipset Information */


/** @defgroup nht_ram2ram Block Ciphers (RAM2RAM) */

/******************************************************************************/
/*                                                                            */
/*                              VERSION TOOL                                  */
/*                                                                            */
/******************************************************************************/

#ifndef NHTBSD_TOOL_VERSION
#define NHTBSD_TOOL_STRINGIFY(s) BSD_TOOL_TOSTRING(s)
#define NHTBSD_TOOL_TOSTRING(s)  #s

#define NHTBSD_TOOL_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
#define NHTBSD_TOOL_VERSION(a, b, c) BSD_TOOL_VERSION_DOT(a, b, c)
#endif

#define NHTBSDAPI_VERSION_INTER NHTBSD_TOOL_VERSION(NHTBSDAPI_VERSION_MAJOR, \
              NHTBSDAPI_VERSION_MEDIUM, \
              NHTBSDAPI_VERSION_MINOR)

#define NHTBSDAPI_VERSION_INT   NHTBSD_TOOL_VERSION_INT(NHTBSDAPI_VERSION_MAJOR, \
            NHTBSDAPI_VERSION_MEDIUM, \
            NHTBSDAPI_VERSION_MINOR)

#define NHTBSDAPI_VERSION_STRING  "NHTBSDAPI_" NHTBSD_TOOL_STRINGIFY(NHTBSDAPI_VERSION_INTER)



/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup nht_driversetting
 *
 *  @brief
 *    Initialize the BSD harness test resource usage.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval   BSD_NO_ERROR
 *              Initialization was completed successfully.
 *  @retval   BSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function is intended to let the chipset manufacturer perform some
 *  potential specific pre-initialization before an application
 *  is enabled to successfully use the BSD driver resources involved in
 *  harness test.
 *  This includes pre-initialization of BSD software and hardware resources...
 *
 *  The application is responsible to call this function at least once before
 *  using any other functions of the BSD APIs.
 *
 *  If pre-initialization of the bsd system resources succeeds or if this
 *  one was already successfully initialized for this process instance,
 *  return "BSD_NO_ERROR".
 *
 *  PS: If the BSD resource was already terminated or if these ones where not
 *  initialized yet, return "BSD_NO_ERROR".
 *
 *  This function overwrites the BSD function named 'bsdInitialize()' in
 *  harness test certification application tool.\n
 *  The use fo the BSD function named 'bsdInitialize()' is deprecated
 *  when using this API.\n
 *  The implementation of this function shall implicitly make a call to the
 *  'bsdInitialize()' BSD API underlaying function.
 *
 * @remark
 *  This function is intended to abstract the chipset manufacturer specific
 *  structure called "TBsdInitParameters" regarding the BSD harness test
 *  application.
 */
TBsdStatus nhtBsdInitialize (void);


/**
 *  @ingroup nht_driversetting
 *
 *  @brief
 *    Terminate the BSD harness test resource usage.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval   BSD_NO_ERROR
 *              Termination was completed successfully.
 *  @retval   BSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function terminates the BSD driver resource usage associated to an
 *  application instance.\n
 *  This function is intended to let the chipset manufacturer properly
 *  clean-up all BSD resources that were previously allocated (or engage)
 *  during the execution of the current harness test application instance for
 *  well-running of subsequent application instanciations.
 *
 *  BSD resource termination shall be implicite at application termination in
 *  order to ensure well running of subsequent applications.
 *
 *  After calling this function, subsequent BSD driver resources
 *  re-initializations (using the nhtBsdInitialize() funtion) shall be
 *  supported.
 *
 *  @remark
 *  This function overwrites the BSD function named 'bsdTerminate()'
 *  in harness test certification application tool.\n
 *  The use fo the BSD function named 'bsdTerminate()' is deprecated when
 *  using this API.\n
 *  The implementation of this function shall implicitly make a call to
 *  the 'bsdTerminate()' BSD underlaying function.\n\n
 *  This function is intended to abstract the chipset manufacturer specific
 *  structure called "TBsdTerminateParameters" regarding the BSD harness test
 *  application.
 */
TBsdStatus nhtBsdTerminate (void);


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the expected NOCS certification version the chipset claims
 *    to comply with.
 *
 *  @param[out]    pxVersion
 *                   NOCS version that the chipset claims to be compliant
 *                   with.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *
 *  This function get the NOCS version (or certification level) that the
 *  chipset claims to comply with.
 *
 *  It allows the harness test BSD applications to establish which
 *  features, tests and functions are relevant for the claimed NOCS certification.
 *
 *  Expected format of the NOCS version shall be generated using the
 *  BSD_TOOL_VERSION_INT() macro (e.g: for NOCS3.1: '*pxVersion =
 *  BSD_TOOL_VERSION_INT(3,1,0)').
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying BSD driver API.
 *
 *  Please refer to chapter called "NOCS non-mandatory functions implementation"
 *  for BSD functions implementation concerns.
*/
TBsdStatus nhtBsdGetCertificationNOCSVersion
(
  TUnsignedInt32 * pxVersion
);


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the current version of the Harness test BSD Driver extension
 *    Implementation.
 *
 *  @param[out]     xSoftwareVersion
 *                   20 characters string where the function has to write
 *                   the software version string.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   BSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the NHT BSD Driver extension
 *  implementation.\n
 *  This version is represented as a character string, the internal
 *  format being chipset manufacturer dependent.\n
 *  However, the length of the string is fixed at 20 characters.\n
 *  The string must be terminated by the end character '\\0'.
 *
 *  @remark
 *  This is a pure additional function associated to BSD harness test.\n
 *  This one does not stand as an an overwritten function of the
 *  'bsdGetSoftwareVersion()' BSD driver function that applies to
 *  the underlaying BSD driver implementation.\n\n
 *  The BSD driver underlaying function called "bsdGetSoftwareVersion()'
 *  that refers to the BSD driver implementation remains applicable.
 *  Both functions can be called by harness test applications.
 *

*/
TBsdStatus nhtBsdGetSoftwareVersion
(
  TBsd20CharsString  xSoftwareVersion
);


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the string name of this chipset manufacturer name.
 *
 *  @param[out]     xChipManufacturerName
 *                   20 characters string where the function has to write
 *                   the chip manufacturer name string.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *
 *  This function returns the name of the chipset manufacturer.
 *  The internal format is chipset manufacturer dependent.\n
 *  However, this internal format has to be agreed with
 *  Nagravision and the chipset manufacturer.\n
 *  In any case, the size of the string returned by the function is a
 *  maximum size of 20 characters including the end character '\\0'.\n
 *  The string value setup by this function shall be agreed between the
 *  Chipset Manufacturer and Nagra.
 *
 *  Purpose of this function is to allow the remote harness test
 *  applications to report and verify which chipset is really tested
 *  during certification (and from whom).
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying BSD driver API.
*/
TBsdStatus nhtBsdGetChipManufacturerName
(
  TBsd20CharsString xChipManufacturerName
);


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the name of the chip
 *
 *  @param[out]    xChipName
 *                   20 characters string where the function has to write
 *                   the chip name string.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *
 *  This function get the name of the chip
 *
 *  Purpose of this function is to allow the remote harness test
 *  applications to get the name identifier of the chipset.\n
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying BSD driver API.
*/
TBsdStatus nhtBsdGetChipName
(
  TBsd20CharsString xChipName
);


/******************************************************************************/
/*                                                                            */
/*                                    RAM2RAM                                 */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Get the protecting key number of the chipset
 *    key ladders.
 *
 *  @param[out]     pxProtectingKeyNumber
 *                   Key ladder Protecting key number to be setup.
 *
 *  @retval   BSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   BSD_ERROR_INVALID_PARAMETERS
 *              pxProtectingKeyNumber parameter is invalid.
 *  @retval   BSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the Chipset key ladder protecting key number.
 *  Protecting key number is always defined as the key ladder level number - 1.
 *
 *  For NOCS3.x, this value shall always be set to 2.
 *  For NOCS1.x, this value can set to 2 or 1 depending of the Key ladder
 *  HW implementation.
 *
 *  Purpose of this function is to let the harness test frameword knows
 *  and verify that the Key ladder level of the chipset complies with
 *  the agreed specification for the chip.
 *
*/
TBsdStatus nhtBsdGetBsdProtectingKeyNumber
(
  TUnsignedInt32 * pxProtectingKeyNumber
);


#ifdef __cplusplus
}
#endif


#endif /* NHT_BSD_H */

/* nocs_nhtbsd.h */
