/**
**  @file nocs_nhtcsd.h
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset harness tests
**
**    This header file describes the API extensions of the CSD driver API
**    v3.3.3 that need to be implemented by the Chipset Manufacturer in
**    order to be able to comply with the Harness test toolkit provided by
**    Nagra.
**
**    Such extensions must be implemented by the Chipset Manufacturer the
**    same way as the Chipset Manufucturer has to implement the CSD driver
**    API.
**
**    Implementing the function extensions described in this API do not
**    release the Chipset Manufucturer for implementing all functions
**    described in the CSD driver API.
**
**    This API extension is intended to provide test facilities associated
**    to a NOCS certification by abstracting additional specific Chipset
**    Manufacturer resource handling not covered by the CSD API
**    (e.g: Video streaming, DMAs, etc...)
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

#ifndef NHT_CSD_H
#define NHT_CSD_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the version number of the CSD EAPI provided by Nagra.
 * Note that this version number does not correspond to the version
 * number of the EAPI implementation which is CM specific.
*/
#define NHTCSDAPI_VERSION_MAJOR  1
#define NHTCSDAPI_VERSION_MEDIUM 1
#define NHTCSDAPI_VERSION_MINOR  1

/** @page p_history History
 *
 *   - <b> 1.1.0 2012/06/05 Nicolas Grosclaude</b>
 *     - Introduce functions associated to CSD NOCS harness test.
 *       certification. Based on CSD API 3.3.3
 *   - <b> 1.1.1 2014/03/05 Nicolas Grosclaude</b>
 *     - Add 'nhtCsdOpenR2RKeyPathHandle()' and 'nhtCsdCloseR2RKeyPathHandle()' functions
 *     - Deprecate 'nhtCsdInitializeR2RKeyPathHandle()' and 'nhtCsdTerminateR2RKeyPathHandle()' functions.
 *     - Correct description associated to nhtCsdDeallocateSysBuffer()' function.
 *
 */

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "nocs_csd_impl.h"
#include "nocs_csd.h"


/***************************************************************************/
/*                                                                         */
/*                             OVERALL DOCUMENTATION                       */
/*                                                                         */
/***************************************************************************/

/**
 * @mainpage Overview
 * This API stands as an extension of the CSD API v3.3.3\n<hr>
 *
 *  - @subpage p_preface
 *  - @subpage p_history
 *  - @subpage p_dsc_scr_bg_processing
 *  - @subpage p_dsc_test
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
 *  This document is intended for the manufacturers of MPEG secure chipsets
 *  who are partners of Nagravision and whose chipset has to pass a NOCS
 *  CSD Harness test certification.\n
 *
 *  This header file describes an API extensions of the CSD driver API
 *  v3.3.3 that need to be implemented by the Chipset Manufacturer in
 *  order to comply with the CSD Harness test toolkit provided by Nagra.
 *
 *  Implementation of this API is mandatory for passing a NOCS CSD
 *  certification.
 *
 *  This API extension is first intended to provide test facilities
 *  associated to a NOCS CSD harness test certification by preventing
 *  the chipset manufacturer to implement its own CSD test application.
 *  CSD test applications will be provided by Nagra.
 *
 *  This API shall be implemented by the chipset manufacturers for any
 *  new NOCS secure chipset that is candidate to a Nagra NOCS certification.
 *  Such extensions must be implemented by the Chipset Manufacturer the same
 *  way as the Chipset Manufucturer has to implement the CSD driver API.
 *
 *  Implementing the CSD function extensions described in this API do not
 *  release the Chipset Manufucturer for implementing all functions
 *  described in the CSD driver API.
 *
 *  Good understanding of the CSD API v3.3.3 stands as a pre-requesite for
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

/** @page p_dsc_scr_bg_processing DSC and SCR test run background processing
 *
 *  Since DSC and SCR test runs require time critical streaming concerns,
 *  associated test runs are intended to be asynchronously processed
 *  (in background).
 *
 *  The way and means involved in such asynchronous test run is chipset
 *  system specific and shall be implemented by the chipset manufacturer.
 *
 *  In order to let the harness test application managing such concurrent
 *  test run processing, dedicated functions are introduced in this API
 *  for controling those concurrent test run processing (e.g: asynchronous
 *  start/stop functions)
 */

/** @page p_dsc_test DSC test run API
 *
 *  This sub-chapter introduces specific harness test concerns relative to
 *  DSC ressource testing.
 *
 * <hr><h2>Chipset extra resource handling</h2>
 *
 *  Since DSC test run require additional Chipset system resources not
 *  covered by the CSD-based API, dedicated functions are provided in order
 *  to abstract those Chipset Manufacturer's resource handling regarding
 *  the harness test tools provided Nagra.
 *
 *  DSC additional chipset resources may include Tuner, DEMUX, DMA, Video
 *  output, etc...).
 *
 *  Abstraction associated these additional API functions do not make any
 *  assumption about the nature, the type and the number of these additional
 *  chipset resources that might be involved in a DSC test run.
 *
 *  <hr><h2>Key setting abstraction</h2>
 *  DSC test run functions introduced in this API abstract the particular
 *  concerns associated to the key setting that may be involved in DSC test
 *  runs regarding the chipset manufacturer. This concerns applies to both:
 *  - keys that must be setup before starting a DSC test run
 *  - Keys that must be setup during the test run according to the stream
 *    (e.g: CW, ECM)
 *
 *  Concerns associated to key settings during DSC harness tests is let to
 *  the harness test applications provided by Nagra (because relative to
 *  test streams generated by Nagra).
 *
 *  <hr><h2>Key ladder physical resource abstraction</h2>
 *  DSC test run functions introduced in this API fully abstract the CSD
 *  API underlying DSC key path handles associated to physical engines
 *  involved in the test run.
 *
 *  Key setting functions introduced in this API overwrites the ones found
 *  in CSD base API. In these overwritten functions, key setting apply to
 *  all services associated to the test run (e.g: Video, Audio),
 *  independently of the number of key ladder physical resources involved by
 *  chipset system architecture.
 *
 *  This will be the responsibility of the chipset manufacturer to setup the
 *  key values to the involved chipset key ladders of the test run according
 *  to the chipset architecture.
 *
 */

/***************************************************************************/
/*                                                                         */
/*                              GROUPS DEFINITION                          */
/*                                                                         */
/***************************************************************************/

/** @defgroup nht_driversetting Harness Test resource Settings */

/** @defgroup nht_info Harness Test Chipset Configuration Info*/

/** @defgroup nht_scsboot Harness Test SCS & Boot Configuration */

/** @defgroup nht_ramprot Harness test Memory Protection */

/** @defgroup nht_ram2ram Harness test RAM 2 RAM Operations */

/** @defgroup nht_dsc Harness test DSC Functions */

/** @defgroup nht_scr Harness test SCR Functions*/


/***************************************************************************/
/*                                                                         */
/*                              VERSION TOOL                               */
/*                                                                         */
/***************************************************************************/

#ifndef NHT_CSD_TOOL_VERSION
#define NHT_CSD_TOOL_STRINGIFY(s) CSD_TOOL_TOSTRING(s)
#define NHT_CSD_TOOL_TOSTRING(s)  #s

#define NHT_CSD_TOOL_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
#define NHT_CSD_TOOL_VERSION_DOT(a, b, c) a ##.## b ##.## c
#define NHT_CSD_TOOL_VERSION(a, b, c) NHT_CSD_TOOL_VERSION_DOT(a, b, c)
#endif

#define NHTCSDAPI_VERSION_INTER CSD_TOOL_VERSION(CSDAPI_VERSION_MAJOR, \
              CSDAPI_VERSION_MEDIUM, \
              CSDAPI_VERSION_MINOR)

#define NHT_CSDAPI_VERSION_INT   \
  NHT_CSD_TOOL_VERSION_INT(NHTCSDAPI_VERSION_MAJOR, \
    NHTCSDAPI_VERSION_MEDIUM, \
    NHTCSDAPI_VERSION_MINOR)

#define NHTCSDAPI_VERSION_STRING  \
  "NHTCSDAPI_" NHT_CSD_TOOL_STRINGIFY(NHTCSDAPI_VERSION_INTER)



/***************************************************************************/
/*                                                                         */
/*                              TYPE DEFINITION                            */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup nht_scsboot
 *
 *  @brief
 *    Protecting key type expressed as a16 bytes MSBF array.
*/
typedef unsigned char TNhtProtectingKey[16];


/**
 *  @ingroup nht_scsboot
 *
 *  @brief
 *    Boot modes number type
*/
typedef TCsdUnsignedInt32 TNhtCsdBootModeNumber;


/**
 *  @ingroup nht_scsboot
 *
 *  @brief
 *    Boot mode descriptor structure
*/
typedef struct SNhtCsdBootModeDescriptor
{
  TCsdBootMode   bootModeId;
  /**<  The CSD BootMode CM's specific Id associated to this boot configuration.
   */
  TCsd20CharsString   bootMemoryName;
  /**<  The string name of the persistant memory on which the chipset is
        configured to boot on (must be \000 terminated) */
} TNhtCsdBootModeDescriptor;


/**
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    System buffer abstract handle
*/
typedef void * TNhtCsdSysBufferHandle;


typedef enum ENhtCsdTestRunStatus
{
  NHT_CSD_TEST_NO_ERROR,
  NHT_CSD_TEST_ERROR,
  NHT_CSD_TEST_ERROR_WOULD_BLOCK,
  NHT_CSD_TEST_ERROR_INVALID_PARAMETERS,
  NHT_CSD_TEST_ERROR_INVALID_FILE_PATHNAME,
  NHT_CSD_TEST_ERROR_SERVICE_CURRENTLY_IN_USED,
  NHT_CSD_TEST_ERROR_TEST_RUN_NOT_STARTED,
  NHT_CSD_TEST_ERROR_SERVICE_RUN_FAILLER

} TNhtCsdTestRunStatus;


/**
 *  @ingroup nht_scr
 *
 *  @brief
 *    SCR harness test run input parameter structure type
*/
typedef struct SNhtCsdScrTestRunParameters
{
  TCsdUnsignedInt16  emi;
  /**<  Cryptographic operating mode (EMI) identifier. */
  int                audioPid;
  /**<  Audio PID */
  int                videoPid;
  /**<  Video PID */
  int                pcrPid;
  /**<  PCR PID */
  const char * pInputFilePathname;
  /**<  Stream Input file pathname or NULL if stream shall be taken from
   *   the front-head. */
  TCsdBoolean        isForEncryption;
  /**<  Specify if the test run shall use encryption mode */
  const char * pOutputFilePathname;
  /**<  Stream Output file pathname or NULL if no recording is required.
   *    (In all cases, stream shall be at least be provided into the
   *    back-end (video/audio output) */
  /**<  ECM usage identifier */
} TNhtCsdScrTestRunParameters;


/**
 *  @ingroup nht_scr
 *
 *  @brief
 *    SCR test run handle type
*/
typedef void * TNhtCsdScrTestRunHandle;


/**
 *  @ingroup nht_dsc
 *
 *  @brief
 *    ECM call back private data opaque descritor type
*/
typedef void * TNhtCsdDscCallBackPrivateParameters;


/**
 *  @ingroup nht_dsc
 *
 *  @brief
 *    DCR test run handle type
*/
typedef void * TNhtCsdDscTestRunHandle;


/**
 *  @ingroup nht_dsc
 *
 *  @brief
 *    ECM call back function type.
 *
 *    Implementation of the DSC test is responsible to call it
 *    each time there is a new MPEG ECM tableId associated to an ECM PID found
 *    in the input stream.
*/
typedef TCsdStatus (*TNhtDscEcmContentCallBack) (
  TNhtCsdDscTestRunHandle               xDscTestRunHandle,
  /**<  test run handle identifier. */
  TNhtCsdDscCallBackPrivateParameters   xPrivateParameters,
  /**<  ECM callback private data (as given at DSC test run opening time) */
  TCsdUnsignedInt8                      xEcmTableId,
  /**<  ECM MPEG Table ID) */
  const TCsdUnsignedInt8              * pxEcmContent,
  /**<  ECM MPEG packet buffer */
  TCsdSize                              xEcmContentSize
  /**<  ECM MPEG packet buffer size */
);


/**
 *  @ingroup nht_dsc
 *
 *  @brief
 *    DSC harness test run input parameter structure type
*/
typedef struct SNhtCsdDscTestRunParameters
{
  TCsdUnsignedInt16  emi;
  /**<  Cryptographic operating mode (EMI) identifier. */
  int                audioPid;
  /**<  Audio PID */
  int                videoPid;
  /**<  Video PID */
  int                pcrPid;
  /**<  PCR PID */
  TCsdBoolean        isInClear;
  /**<  Specify if the test run shall use encryption mode */
  TCsdBoolean        isForEncryption;
  /**<  Specify if the test run is for an encryption */
  int                ecmPid;
  /**<  ECM PID (if ECM usage is required) */
  const char       * pInputFilePathname;
  /**<  Stream Input file pathname or NULL if stream shall be taken from
   *   the front-head. */
  const char       * pOutputFilePathname;
  /**<  Stream Output file pathname or NULL if no recording is required.
   *    (In all cases, stream shall be at least be provided into the
   *    back-end (video/audio output) */
  TCsdUnsignedInt8    iv[16];
  /**< Initial value (IV)  of the crypto algorithm if applicable according to
   *  the EMI identifier. */
  TCsdSize            ivSize;
  /**< Size of the initial value (IV) of the crypto algorithm if applicable according to
   *  the EMI identifier. */
  TNhtDscEcmContentCallBack ecmCallBackFct;
  /**< ECM call back function to be called each time a new MPEG ECM tableId is found
   * in the input stream */
  TNhtCsdDscCallBackPrivateParameters ecmCallBackPrivateData;
  /**< ECM call back function private data (opaque handler).
   * Implementation of this API is responsible to provide it at each call back to
   * the 'ecm call back function) if any. */
} TNhtCsdDscTestRunParameters;



/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup nht_driversetting
 *
 *  @brief
 *    Initialize the CSD harness test resource usage.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval   CSD_NO_ERROR
 *              Initialization was completed successfully.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function is intended to let the chipset manufacturer perform some
 *  potential specific pre-initialization before an instance of an application
 *  is enabled to successfully use the system resources involved in harness test.\n
 *  This includes pre-initialization of CSD SW/HW resource as well all other
 *  system resources not covered by the CSD driver basic-API such as video/audio
 *  descrambler, DMAs, etc...
 *
 *  The application is responsible to call this function at least once before using
 *  any other functions of the CSD APIs.\n
 *  If pre-initialization succeeds or  if this one was already successfully
 *  initialized for this process instance, return "CSD_NO_ERROR".
 *
 *  PS: If the CSD resource termination succeeds or if these ones where not
 *  initialized yet, return "CSD_NO_ERROR".
 *
 *  This function overwrites the CSD function named 'csdInitialize()' in
 *  harness test certification application tool.\n
 *  The use fo the CSD function named 'csdInitialize()' is deprecated
 *  when using this API.\n
 *  The implementation of this function shall implicitly make a call to the
 *  'csdInitialize()' CSD API underlaying function.
 *
 */
TCsdStatus nhtCsdInitialize (void);


/**
 *  @ingroup nht_driversetting
 *
 *  @brief
 *    Terminate the CSD harness test resource usage.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval   CSD_NO_ERROR
 *              Termination was completed successfully.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function terminates the CSD resource usage associated to an application
 *  instance.\n
 *  This function is intended to let the chipset manufacturer properly
 *  clean-up all CSD resources that were previously allocated (or engage)
 *  during the execution of the current harness test application instance for
 *  well-running of subsequent application instanciations.
 *
 *  CSD resource termination shall be implicite at application termination in
 *  order to ensure that subsequent application will run well.
 *
 *  After calling this function, subsequent CSD resources re-initializations (using
 *  the 'nhtCsdInitialize()' funtion) shall be supported.
 *
 *  This function overwrites the CSD function named 'csdTerminate()'
 *  in harness test certification application tool.\n
 *  The use fo the CSD function named 'csdTerminate()' is deprecated when
 *  using this API.\n
 *  The implementation of this function shall implicitly make a call to
 *  the 'csdTerminate()' CSD underlaying function.
 */
TCsdStatus nhtCsdTerminate (void);


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
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *
 *  This function get the NOCS version (or certification level) that the
 *  chipset claims to comply with.
 *
 *  Purpose of this function is to allow the remote harness test
 *  applications to get from the chipset target the NOCS certification
 *  level.\n
 *  It allows the harness test applications to establish which
 *  features and tests are relevant for the claimed NOCS certification.
 *
 *  Use the macro CSDAPI_VERSION_INT to assign the right value. If not,
 *  specified, the third digit of the NOCS version should be set up to
 *  0.
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying CSD driver API.
*/
TCsdStatus nhtCsdGetCertificationNOCSVersion
(
  TCsdUnsignedInt32 * pxVersion
);


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the current version of the Harness test CSD Driver extension
 *    Implementation.
 *
 *  @param[out]     xSoftwareVersion
 *                   20 characters string where the function has to write
 *                   the software version string.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the NHT CSD Driver extension
 *  implementation.\n
 *  It is represented as a character string, the internal
 *  format being chipset manufacturer dependent.\n
 *  However, the length of the string is fixed at 20 characters.\n
 *  The string must be terminated by the end character '\\0'.
 *
 *  Use the macro CSDAPI_VERSION_INT to assign the right value.
 *
 *  The CSD driver underlaying function called "csdGetSoftwareVersion()'
 *  that refers to the CSD driver implementation remains applicable.\n
 *  Both functions can be called by harness test applications.
 *
 *  This is a pure additional function associated to CSD harness test.\n
 *  This one does not stand as an an overwritten function of the
 *  'csdGetSoftwareVersion()' CSD driver function.
*/
TCsdStatus nhtCsdGetSoftwareVersion
(
  TCsd20CharsString  xSoftwareVersion
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
 *  @retval   CSD_NO_ERROR
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
 *  during certiciation (and from whom).
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying CSD driver API.
*/
TCsdStatus nhtCsdGetChipManufacturerName
(
  TCsd20CharsString xChipManufacturerName
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
 *  @retval   CSD_NO_ERROR
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
 *  underlaying CSD driver API.
*/
TCsdStatus nhtCsdGetChipName
(
  TCsd20CharsString xChipName
);


/**
 *  @ingroup nht_scsboot
 *
 * @brief
 *   Get the number of chipset manufacturer's specific boot modes
 *   supported by the chipset platform.
 *
 *  @pre
 *    None
 *
 *  @post
 *    None.
 *
 *  @param[out]   pxBootModeNumber
 *    Number of Boot modes defines in the CM's specific
 *    platform.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  This functions return the number of boot modes supported by the chipset
 *  or chipset evaluation board.
 *
 *  Number of boot modes stands as the number of ENUM values defines by the
 *  chipset manufacturer in the CSD underlaying driver enum type named
 *  'TCsdBootMode'.
 *
 *  Purpose of this function is to inform the harness test tools about the
 *  boot mode number featured by the chipset manufacturer.\n
 *  In particular, it makes this CSD Harness test API compliant with chipset
 *  manufucturer boot mode enum values specific setting.
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying CSD driver API.
*/
TCsdStatus nhtCsdGetBootModeNumber
(
  TNhtCsdBootModeNumber * pxBootModeNumber
);


/**
 *  @ingroup nht_scsboot
 *
 * @brief
 *   Get the descriptor set associated to the boot modes supported by the
 *   chipset.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]     xBootModeDescriptorNumber
 *    Number of pre-allocated boot Mode descriptors to be filled up.
 *
 *  @param[out]    pxBootModeDescriptors
 *    Address of the pre-allocated boot Mode descriptor array.
 *    (size of this pre-allocated array is defined by the
 *    'xBootModeDescriptorNumber' input parameter)
 *
 *  @param[out]    pxBootModeEffectiveNumber
 *    Effective descriptor number that has been filled-up.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  This function allows the application to get the info relative to
 *  the boot modes supported by the chipset manufacturer.
 *
 *  Implementation of this function is reponsible to fill-up the boot mode
 *  descriptors of the descriptor set with the
 *  following information fields:
 *
 *  - 'bootModeId' field:
 *      A CM's specific enum value defined in 'TCsdBootMode' enum type.
 *
 *  - 'bootMemoryName' field:
 *    A brief boot mode description string of the memory on which the chipset
 *    can boot (e.g: "NAND")
 *
 *  PS: Implementation of this function shall grant there is no
 *  'bootModeId' duplicated descriptor in the return set.
 *
 *  If the hardware chipset technology allows an unprogrammed state for the
 *  Boot Mode, it shall appear as a separated boot mode descriptor with an associated
 *  'bootMemoryName' description field  must be setup to the "UNPROGRAMMED" reserved value.
 *
 *  If the chipset does not have an internal configuration setting for boot,
 *  then this function shall return CSD_ERROR_OPERATION_NOT_SUPPORTED.\n
 *  No Boot mode descriptor set is returned in this case.
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying CSD driver API.
*/
TCsdStatus nhtCsdGetBootModeDescriptorSet
(
  TNhtCsdBootModeNumber       xBootModeDescriptorNumber,
  TNhtCsdBootModeDescriptor * pxBootModeDescriptors,
  TNhtCsdBootModeNumber     * pxBootModeEffectiveNumber
);


/**
 *  @ingroup nht_scsboot
 *
 * @brief
 *   Get the boot mode descriptor associated to a chipset manufucturer's
 *   specific boot mode Id,
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]     xBootModeId
 *    boot Mode Id for which one a boot mode descriptor is
 *    required.
 *
 *  @param[out]    pxBootModeDescriptor
 *    Address of the pre-allocated boot Mode descriptor.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  This function allows the application to get the boot mode descriptor
 *  associated to a chipset manufacturer specific boot mode Id.
 *
 *  If the boot mode Id does not fit a supported boot mode of the chipset,
 *  this function shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If the chipset does not have an internal configuration setting to boot,
 *  then the function shall return CSD_ERROR_OPERATION_NOT_SUPPORTED.\n
 *  No Boot mode descriptor set is returned in this case.
 *
 *  @remark
 *  This is a pure additional function introduced for harness test purpose.\n
 *  In particular, it does not overwrite any other function defined in the
 *  underlaying CSD driver API.
*/
TCsdStatus nhtCsdGetBootModeDescriptor
(
  TCsdBootMode                xBootModeId,
  TNhtCsdBootModeDescriptor * pxBootModeDescriptor
);


/**
 *  @ingroup nht_scsboot
 *
 *  @brief
 *    Get the chipset manufucturer specific PV expected buffer value length
 *    associated to a SCS Persistent Value Id.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]      xScsPvParamsId
 *    SCS Persistent Value Parameters Identification.
 *
 *  @param[in]      pxPvLength
 *    Size in bytes of the pxPvValue array
 *
 *  @retval   NHT_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   NHT_ERROR_INVALID_PARAMETERS
 *    One or several parameter are invalid.
 *
 *  @retval   NHT_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   NHT_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  This function get the chipset manufucturer specific persistent Value
 *  buffer size associated to a PV parameter ID. Expected buffer size is
 *  expressed in bytes.
 *
 *  This function is intended to inform the harness test applications about
 *  the size of the PV value buffer that shall be pre-allocated for
 *  successfully calling the CSD driver underlaying functions 'csdSetScsPv()'
 *  and 'csdGetScsPv()'.\n
 *  Conditionally, this function allows the harness
 *  test application to verify if the expected size fit the one that was
 *  agreed between the chipset manufacturer and Nagra.
 *
 *  If the chipset does not implement the PV parameter requested or it does
 *  not support this function, then the call shall return
 *  CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other function defined in the
 *    underlaying CSD driver API.
 */
TCsdStatus nhtCsdGetScsExpectedPvValueSize
(
  TCsdScsPvId         xScsPvParamsId,
  TCsdUnsignedInt16 * pxPvLength
);


/**
 *  @ingroup nht_scsboot
 *
 *  @brief
 *    Set some SCS Persistent Values associated to a PV Parameter ID.
 *
 *  @param[in]      xScsPvParamsId
 *                   SCS Persistent Value Parameters Identification.
 *  @param[in]      xPvLength
 *                   Size in bytes of pxPvValue arrays.
 *  @param[in]      pxPvValue
 *                   Pointer to the location where the to read the value of
 *                   the field
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *              The PV has already been set to a different value
 *              and has been locked.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested PV Parameter is not supported by the chipset.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function requests to switch the state of some NOCS related SCS
 *  Persistent Value bit fields identified by xScsPvParamsId to the state
 *  specified in pxPvValue.
 *
 *  This function overwrite the CSD API based function named 'csdSetScsPv()'.
 *  Purpose of this overwritten function is to abstract the chipset specific
 *  Pv handle structure type definition regarding the harness test
 *  applications.
 *
 *  Using this function, makes the chipset manufacturer responsible to
 *  properly initialize and handle the underlaying PV handle according
 *  to its specific features.
 *
 *  xPvLength specifies the length of the array of pxPvValue.
 *  The application is responsible to provide the expected length value
 *  as identified when using the 'nht_csdGetScsExpectedPvValueSize()'
 *  function. 'pxPvLength' is expressed in bytes.
 *
 *  pxPvValue stands as the array of bytes of size specifying associated
 *  chipset manufacturer defined bit fields.
 *
 *  If the Persistent Value configuration bit field is already in the
 *  requested state when this function is called or if the function has
 *  successfully set the Persistent Value configuration bit field in the
 *  requested state, the function shall return CSD_NO_ERROR.\n
 *  In all other cases, the call shall have no effect and the function shall return
 *  CSD_ERROR.
 *
 *  If the xScsPvParamsId is already set and the client software tries to
 *  set it to a different value, the function shall return
 *  CSD_ERROR_OPERATION_NOT_ALLOWED.
 *
 *  If the chipset does not implement the PV parameter requested or does
 *  not support this function, then the call shall return
 *  CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  @remark
 *   This function overwrite the CSD API based function named
 *   'csdSetScsPv()'.\n
 *   In particular, the function 'csdSetScsPv()' is never directly called.\n
 *   However, implementation of this function is required to implicitly
 *   perform a call to the csdSetScsPv()' CSD API underlaying function.
*/
TCsdStatus nhtCsdSetScsPv
(
  TCsdScsPvId               xScsPvParamsId,
  TCsdUnsignedInt16         xPvLength,
  const TCsdUnsignedInt8  * pxPvValue
);


/**
 *  @ingroup nht_scsboot
 *
 *  @brief
 *    Set some SCS Persistent Values associated to a PV Parameter ID.
 *
 *  @param[in]      xScsPvParamsId
 *                   SCS Persistent Value Parameters Identification.
 *
 *  @param[in]      xPvLength
 *                   Size in bytes of the pxPvValue array

 *  @param[in]      pxPvValue
 *                   Pointer to the location where the to read the value of
 *                   the field
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested PV Parameter is not supported by the chipset.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function get the current state of the NOCS related SCS Persistent
 *  Value bit fields associated to xScsPvParamsId.
 *
 *  This function overwrite the CSD API based function named 'csdGetScsPv()'.\n
 *  Purpose of this overwritten function is to abstract the chipset specific
 *  Pv handle structure type definition regarding the harness test
 *  applications.\n
 *  Using this function, makes the chipset manufacturer
 *  responsible to properly initialize and handle the underlaying PV handle
 *  according to its specific features.
 *
 *  xPvLength specifies the length of the array of pxPvValue.
 *  The application is responsible to provide the expected length value as
 *  identified when using the 'nht_csdGetScsExpectedPvValueSize()' function.
 *  'pxPvLength' is expressed in bytes.
 *
 *  pxPvValue stands as the array of bytes of size specifying associated
 *  chipset manufacturer defined bit fields.
 *
 *  If the chipset does not implement the PV parameter requested or does
 *  not support this function, then the call shall return
 *  CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  @remark
 *   This function overwrite the CSD API based function named 'csdGetScsPv()'.\n
 *   In particular, the function 'csdGetScsPv()' is never directly called
 *   However, implementation of this function is requested to implicitly
 *   perform a call to the csdGetScsPv()' CSD API underlaying function.
 */
TCsdStatus nhtCsdGetScsPv
(
  TCsdScsPvId         xScsPvParamsId,
  TCsdUnsignedInt16   xPvLength,
  TCsdUnsignedInt8  * pxPvValue
);


/**
 *  @ingroup nht_ramprot
 *
 *  @brief
 *    Get the expected RAM unscrambled Storage size holder length
 *    needed for getting the associated RAM unscambled Storage size value.
 *
 *  @param[out]  pxPvLength
 *    Size of the buffer needed to represent the current RAM unscrambled
 *    Storage size value.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              The passed parameter is invalid.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The function is not supported by the chipset.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function is intended to let the harness test applications know what
 *  is the minimal RAM unscrambled storage size holder to pre-allocated for
 *  getting the RAM unscramble storage size using the
 *  'csdGetRamUnscrambledStorageSize' function.
 *
 *  If at least one parameter is incorrect or not defined the function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If the function is not supported by the chipset, it shall return
 *  CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If the operation fails for any other reasons, the function shall
 *  return CSD_ERROR.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other function defined in the
 *    underlaying CSD driver API.

 */
TCsdStatus nhtcsdGetRamUnscrambledStorageSizeBufferLength
(
  TCsdUnsignedInt16 * pxPvLength
);


/***************************************************************************/
/*                                                                         */
/*               NOCS1.x RAM2RAM Functions                                 */
/*                                                                         */
/***************************************************************************/



/**
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Allocate a physical memory space mapped buffer.
 *
 *  @param[in]     xSize
 *                   size of the buffer.
 *
 *  @retval   NULL
 *              No buffer allocated (failure).
 *  @retval   <buffer address>
 *              Address of the buffer.
 *
 *  This function allocates a buffer which is granted to be physical memory
 *  contiguous.
 *
*/
TNhtCsdSysBufferHandle nhtCsdAllocateSysBuffer
(
  TCsdSize xSize
);


/**
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Deallocate a physical memory space mapped buffer.
 *
 *  @param[in]     xNhtCsdSysBufferHandle
 *                  Sys buffer handle.
 *  @retval   CSD_NO_ERROR
 *              Buffer successfully allocated.
 *  @retval   CSD_ERROR
 *              Fail to allocated buffer
 *
 *  This function deallocates a buffer previously allocated using
 *  the nhtCsdAllocateSysBuffer() function.
 *
*/
TCsdStatus nhtCsdDeallocateSysBuffer
(
  TNhtCsdSysBufferHandle xNhtCsdSysBufferHandle
);



/*!
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Initialize a R2R Key path handle (deprecated).
 *
 *  @param[in,out]  pxR2RKeyPathHandle
 *                   R2R key path handle to be initialized.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function initializes a chipset manufacturer pre-allocated R2R Key
 *  path handle passed in input of this function for CSD API R2R usage.
 *
 *  This function is intended to abstract the chipset manufacturer specific
 *  concerns associated to the initialization of such a pre-allocated handle
 *  regarding the harness test applications.
 *
 *  If 'pxR2RKeyPathHandle' parameter is passed as NULL, this function
 *  shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If the R2R key path handle passed in input parameter stands as an
 *  already intialized (and not terminated) handle, this function shall
 *  return CSD_ERROR.
 *
 *  For any other errors, this function shall return CSD_ERROR.
 *
 * After having successfully initialized a R2R key path handle, usage of
 * associated R2R operations defined in the CSD API shall be granted.
 *
 *  @remark
 *    This function is deprecated. It has been replaced by the nhtCsdOpenR2RKeyPathHandle()
 *    function.\n
 *    This is a pure additional function introduced for harness test purpose.
 *    In particular, it does not overwrite any other function defined in the
 *    underlaying CSD driver API.
*/
TCsdStatus nhtCsdInitializeR2RKeyPathHandle
(
  TCsdR2RKeyPathHandle * pxR2RKeyPathHandle
);



/*!
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Open a R2R session.
 *
 *  @param[out]     pxR2RKeyPathHandle
 *                   R2R session handle.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function opens a R2R session.
 *
 *  In case of success, implementation of this function is responsible to:
 *  - Allocate an associated session handle.
 *  - To initialize the R2R session handle structure accordingly.
 *  - To return the associated session handle to the caller.
 *
 *  After having successfully opened a R2R session, usage of
 *  of this one shall be granted.
 *
 *  If 'pxR2RKeyPathHandle' parameter is passed as NULL, this function
 *  shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  For any other errors, this function shall return CSD_ERROR.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.
 *    In particular, it does not overwrite any other function defined in the
 *    underlaying CSD driver API.\n
 *    This function is provided in replacement of the deprecated function
 *    nhtCsdInitializeR2RKeyPathHandle().
*/
TCsdStatus nhtCsdOpenR2RKeyPathHandle
(
  TCsdR2RKeyPathHandle ** pxR2RKeyPathHandle
);



/*!
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Terminate a R2R Key path handle usage (deprecated).
 *
 *  @param[in,out]  pxR2RKeyPathHandle
 *                   R2R key path handle to be terminated.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function terminates a chipset manufacturer R2R Key path handle that
 *  was previously initialized using the nhtCsdInitializeR2RKeyPathHandle()
 *  function.
 *
 *  This function is intended to let the chipset manufacturer implementation:
 *  - To properly release the associated resources it reserved (specific
 *    chipset manufacturer concern) during this key path handle life time.
 *
 *  PS: Since allocation of the key path handle is under the responsiblity of
 *  the caller, implementation of this function shall not include any
 *  deallocation of the the key path handle provided as input parameter.
 *
 *  If the R2R key path handle passed in input parameter stands as a
 *  non-alreday intialized handle, this function shall return
 *  CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If 'pxR2RKeyPathHandle' parameter is passed as NULL, this function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  For any other errors, this function shall return CSD_ERROR.
 *
 *  @remark
 *    This function is deprecated. It has been replaced by the nhtCsdCloseR2RKeyPathHandle()
 *    function.\n
 *    This is a pure additional function introduced for harness test purpose.
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.\n
*/
TCsdStatus nhtCsdTerminateR2RKeyPathHandle
(
  TCsdR2RKeyPathHandle * pxR2RKeyPathHandle
);



/*!
 *  @ingroup nht_ram2ram
 *
 *  @brief
 *    Close a R2R session.
 *
 *  @param[in]      pxR2RKeyPathHandle
 *                   Handle of the R2R session to close.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *
 *  This function closes a chipset manufacturer R2R session that was previously
 *  opened using the nhtCsdOpenR2RKeyPathHandle() function.
 *
 *  This function is intended to let the chipset manufacturer implementation:
 *  - To properly release the system resources currently in-used by this
 *    session.
 *  - To deallocate the associated session handle.
 *
 *  If 'pxR2RKeyPathHandle' is passed as NULL, this function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If 'pxR2RKeyPathHandle' stands as an invalid (not opened) handle, this
 *  function shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.\n
 *    This function is provided in replacement of the deprecated function
 *    nhtCsdTerminateR2RKeyPathHandle().
*/
TCsdStatus nhtCsdCloseR2RKeyPathHandle
(
  TCsdR2RKeyPathHandle * pxR2RKeyPathHandle
);



/***************************************************************************/
/*                                                                         */
/*                                    DSC                                  */
/*                                                                         */
/***************************************************************************/


/*!
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Open a DSC test run session
 *
 *  @param[in]  pxDscTestRunParameters
 *    DSC test run input parameters
 *
 *  @param[out]  pxDscTestRunHandle
 *    DSC test run handle
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function initializes a DSC test run session and return an
 *  associated DSC test run opaque handle.
 *
 *  The input parameter 'pxDscTestRunParameter' contains information
 *  associated to the test run instance to be initialized.\n
 *  Information provided in this input parameter stands as invariant data
 *  of the test run session.\
 *  In particular, These data are all fixed at test run initialization
 *  and cannot be modified during the DSC test run session life-duration.
 *
 *  Based on the invariant data passed as input parameter, this function is
 *  responsible to verify if the requested test run is supported by the
 *  chipset platform. If not, this function shall return
 *  NHT_CSD_TEST_ERROR_TEST_NOT_SUPPORTED.
 *
 *  If specified as an in-clear stream, no key setting is performed by the
 *  application. In this case no ECM processing is needed.
 *
 *  If the the stream is not in clear and no ECM call back is provided, the
 *  application is responsible to setup keys prior to start the test run.
 *  In this case no ECM handling is required.
 *
 *  If this is a supported test run but the associated chipset resources are current
 *  not available because in use by other test runs, this function shall
 *  return NHT_CSD_TEST_ERROR_SERVICE_CURRENTLY_IN_USED.
 *
 *  If some input parameters are invalid, this function shall return
 *  NHT_CSD_TEST_ERROR_INVALID_PARAMETERS.
 *
 *  If initialization succeeds, this function shall return
 *  NHT_CSD_TEST_NO_ERROR and shall provide an associated test run handle.\n
 *  In this case, usage of the chipset resources associated to this
 *  test run shall be granted by the platform until the end-of-life of
 *  this test run session of abortion of the harness test process
 *  (see also function '()').
 *
 *  After intialization of such a test run, harness test application are
 *  free to preset key values or to directly start the test run.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/
TCsdStatus nhtCsdOpenDscTestRunSession
(
  TNhtCsdDscTestRunParameters * pxDscTestRunParameters,
  TNhtCsdDscTestRunHandle     * pxDscTestRunHandle
);


/*!
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Asynchronously start a DSCtest run session identified by its handle.
 *
 *  @param[in,out]  xDscTestRunHandle
 *    DSC test run handle
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function starts a DSC scrambling/descrambling concurrent test run
 *  identified by its test run handle.
 *
 *  This function stands as a non blocking function.\n
 *  If successfully started, DSC associated test run shall be performed
 *  in background (= concurrently to the thread context of the caller of
 *  this function).\n
 *  This function shall return immediately independently of the normal
 *  or abnormal termination of the test run concurrent handling.
 *
 *  If some input parameters are invalid or if the test run handle wasn't
 *  successfully opened first, this function shall return
 *  NHT_CSD_TEST_ERROR_INVALID_PARAMETERS.
 *
 *  If the requested test run fails to start for other reasons, this function
 *  shall return NHT_CSD_TEST_ERROR.
 *
 *  PS: The harness test application implementation of the ECM callback function
 *  (if any) is granted to be non-blocking.\n
 *  Please note that depending of the harness test, key settings associated to
 *  an ECM may be done asynchronously to the execution of this call back
 *  function (e.g: if ECM need to be decrypted prior to be able to set the
 *  associated CWs)
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/

TNhtCsdTestRunStatus nhtCsdStartDscTestRun
(
  TNhtCsdDscTestRunHandle               xDscTestRunHandle
);


/*!
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Wait on completion of a DSC test run identified by its handle.
 *
 *  @param[in,out]  xDscTestRunHandle
 *    DSC test run handle
 *
 *  @param[in]  xTimeout
 *    Timeout
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function waits on completion of a DSC test service session
 *  identified by its DSC test run handle.
 *
 *  Parameter 'xTimeout' specifies a timeout for this function call.
 *  If this parameter is passed with a -1 value, no timeout restriction is required
 *  by the caller and this function shall block until normal or abnormal
 *  termination of the test run.
 *
 *  If not passed as -1, parameter 'xTimeout' is a timeout
 *  value expressed in second. If the associated service run is not finished
 *  yet at timeout expiration, this function shall return
 *  NHT_CSD_TEST_ERROR_WOULD_BLOCK.
 *
 *  At normal or abnormal completion of the service run, any pending call to
 *  this function shall immediately return.\n
 *  If the test run successfully terminated, this function shall immediately
 *  return NHT_CSD_TEST_NO_ERROR.\n
 *  Otherwize, it shall return NHT_CSD_TEST_ERROR_SERVICE_RUN_FAILER.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/

TNhtCsdTestRunStatus nhtCsdWaitOnDscTestRunCompletion
(
  TNhtCsdDscTestRunHandle xDscTestRunHandle,
  int                     xTimeout
);


/*!
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Stop of a DSC test run identified by its handle.
 *
 *  @param[in,out] xDscTestRunHandle
 *    DSC test run handle
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function immediately stops a DS test run identified by
 *  its DSC test run handle (if not already terminated).
 *
 *  If the test run already abnormally terminated before calling
 *  this function, this function shall return NHT_CSD_TEST_ERROR_SERVICE_RUN_FAILER.
 *  Otherwize, it shall return NHT_CSD_TEST_NO_ERROR.
 *
 *  The implementation of this function shall grant that no more ECM callback
 *  will be done after returning from this function.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/
TNhtCsdTestRunStatus nhtCsdStopDscTestRun
(
  TNhtCsdDscTestRunHandle   xDscTestRunHandle
);


/**
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Set the host keys associated to a CSD test run session.
 *
 *  @param[in,out]  xDscTestRunHandle
 *                   DSC test run handle.
 *  @param[in]      pxClearTextDscOddHostKey
 *                   Pointer to the location where the function has to
 *                   read the Clear Text DSC Odd Hostkey.
 *  @param[in]      xClearTextDscOddHostKeySize
 *                   Size in bytes of the Clear Text DSC Odd Hostkey.
 *  @param[in]      pxClearTextDscEvenHostKey
 *                   Pointer to the location where the function has to
 *                   read the Clear Text DSC Even Hostkey.
 *  @param[in]      xClearTextDscEvenHostKeySize
 *                   Size in bytes of the Clear Text DSC Even Hostkey.
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
 *  This function set the CWs provided in clear-text form of test run
 *  identified by its test run handle. In DSC test run, key setting
 *  implicitly apply to all service involved in the test (Video and Audio).
 *
 *  Host keys are expressed as MSBF byte array. If one of the CWs also
 *  called HostKeys (odd or even) is not available,
 *  the given pointer is set to NULL and its corresponding length to 0.\n
 *  The driver shall not change the previous CW in this case.
 *
 *  The size of these keys shall be:
 *      - 0 if the CW is not available.
 *      - 8 if the cryptographic algorithm associated to the EMI provided
 *        at handle intialization time is requesting 8 bytes.
 *      - 16 if the cryptographic algorithm associated to the EMI provided
 *        at handle intialization time requesting 16 bytes.
 *      - In all other cases, the function shall return
 *        CSD_ERROR_INVALID_PARAMETERS.
 *
 *  The implementation is responsible to ensure that this function can be
 *  called at any moment during a test run life duration (including before
 *  starting the test run).
 *
 *  @note
 *    This function overwrites the use of the 'csdSetClearTextDscHostKeys()'
 *    function defined in the CSD API.\
 *    The use fo the CSD function named 'csdSetClearTextDscHostKeys()' is
 *    deprecated when using this API.\n
 *    The implementation of this function shall implicitly make a call to the
 *    'csdSetClearTextDscHostKeys)' CSD API underlaying function.
 *
 *    EMI that applies to 'csdSetClearTextDscHostKeys()' function call
 *    implementation implicitly refers to the one that was setup at opening
 *    time of the test run session.
*/
TCsdStatus nhtCsdTestRunSetClearTextDscHostKeys
(
        TNhtCsdDscTestRunHandle   xDscTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextDscOddHostKey,
        TCsdSize                  xClearTextDscOddHostKeySize,
  const TCsdUnsignedInt8        * pxClearTextDscEvenHostKey,
        TCsdSize                  xClearTextDscEvenHostKeySize
);


/**
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Set the protected content key associated to a CSD test run session.
 *
 *  @param[in,out]  xDscTestRunHandle
 *                   DSC test run handle.
 *  @param[in]      pxDscCipheredProtectingKeys
 *                   Array of Ciphered Protecting Keys
 *  @param[in]      xCipheredProtectingKeyNumber
 *                   Number of input protecting keys provided as input
 *  @param[in]      pxCipheredDscOddContentKey
 *                   Pointer to the location where the function has to
 *                   read the
 *                   Ciphered DSC Odd Contentkey.
 *  @param[in]      xCipheredDscOddContentKeySize
 *                   Size in bytes of the Ciphered DSC Odd Contentkey.
 *  @param[in]      pxCipheredDscEvenContentKey
 *                   Pointer to the location where the function has to
 *                   read the
 *                   Ciphered DSC Even Contentkey.
 *  @param[in]      xCipheredDscEvenContentKeySize
 *                   Size in bytes of the Ciphered DSC Even Contentkey.
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
 *  This function configures the key ladder with the Ciphered Protecting
 *  Keys and set the CWs provided in protected form into the specified key
 *  ladders involved in the Video and Audio stream descrambling.
 *
 *  All keys are expressed as MSBF byte array.\n
 *  xDscCipheredProtectingKeys contains all the Ciphered Protecting Keys.
 *  The number of those keys contained in this array depends on the number
 *  of Key Ladder Elements which is defined by the constant.
 *
 *  PS: CSD_DSC_NB_OF_PROTECTING_KEYS is fixed to 2 for NOCS3.\n
 *
 *  If one of the ciphered CWs also called Ciphered ContentKey (odd or even)
 *  is not available, the given pointer is set to NULL and its corresponding
 *  length to 0. The driver shall not change the previous CW in this case.
 *
 *  The size of these keys shall be:
 *      - 0 if the CW is not available.
 *      - 8 if the cryptographic algorithm associated to the EMI provided
 *        at handle intialization time is requesting 8 bytes.
 *      - 16 if the cryptographic algorithm associated to the EMI provided
 *        at handle intialization time requesting 16 bytes.
 *      - In all other cases, the function shall return
 *        CSD_ERROR_INVALID_PARAMETERS.
 *
 *
 *  'pxDscCipheredProtectingKeys' array parameter structure and key ladder
 *  Key level values follows this rule (for 1 <= 'i' <= 'xCipheredProtectingKeyNumber',
 *  when 'i' is the protecting key level ):
 *
 *   - pxDscCipheredProtectingKeys[xCipheredProtectingKeyNumber - 'i']   refer to Key Ladder KL<'i'> key
 *
 *  The implementation is responsible to ensure that this function can be
 *  called at any moment during a test run life duration (including before
 *  starting the test run).
 *
 *  @note
 *    This function overwrites the use of the 'csdSetClearTextDscHostKeys()'
 *    function defined in the CSD API.\n
 *    The use fo the CSD function named ' csdSetProtectedDscContentKeys()'
 *    is deprecated when using this API.\n
 *    The implementation of this function shall implicitly make a call to the
 *    'csdSetProtectedDscContentKeys()' CSD API underlaying function.
 *
 *    EMI that applies to 'csdSetClearTextDscHostKeys()' function call
 *    implementation implicitly refer to the one setup that was setup at
 *    opening time of the test run session.
*/

TCsdStatus nhtCsdTestRunSetProtectedDscContentKeys
(
        TNhtCsdDscTestRunHandle         xDscTestRunHandle,
  const TNhtProtectingKey             * pxDscCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8              * pxCipheredDscOddContentKey,
        TCsdSize                        xCipheredDscOddContentKeySize,
  const TCsdUnsignedInt8              * pxCipheredDscEvenContentKey,
        TCsdSize                        xCipheredDscEvenContentKeySize
);


/*!
 *  @ingroup nht_dsc
 *
 *  @brief
 *    Close a DSC test run session identified by its handle.
 *
 *  @param[in,out]  xDscTestRunHandle
 *                   DSC test run handle to terminate.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function closes an already opened DSC test run session.
 *
 *  This function is intended to let chipset manufacturer implementation to
 *  properly release the associated test run resources it reserved (specific
 *  chipset manufacturer concern) for this test run.
 *
 *  Closing a DSC test run session shall implicitly stop the exection of the test
 *  run if still started.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/
TCsdStatus nhtCsdCloseDscTestRunSession
(
  TNhtCsdDscTestRunHandle  xDscTestRunHandle
);


/***************************************************************************/
/*                                                                         */
/*                                    SCR                                  */
/*                                                                         */
/***************************************************************************/

/*!
 *  @ingroup nht_scr
 *
 *  @brief
 *    Open a SCR test run session.
 *
 *  @param[in]  pxScrTestRunParameters
 *    SCR test run parameters
 *
 *  @param[out]  pxScrTestRunHandle
 *    SCR test run handle
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function opens a SCR test run session and returns an associated
 *  SCR test run handle.
 *
 *  The input parameter 'pxScrTestRunParameters' contains information
 *  associated to the test run session to open.
 *
 *  Information provided in this input parameter stands as invariant data
 *  of the test run session.\n
 *  In particular, These data are all fixed at test run session opening
 *  time and cannot be modified during the SCR test run session life-duration.
 *
 *  Based on the invariant data passed as parameter, this function is
 *  responsible to verify if the requested test run is supported by the
 *  chipset.\n
 *  If not, this function shall return NHT_CSD_TEST_ERROR_TEST_NOT_SUPPORTED.
 *
 *  If this is a supported test run but the chipset resources are current
 *  not available because in use by other test runs, this function shall
 *  return NHT_CSD_TEST_ERROR_SERVICE_CURRENTLY_IN_USED.
 *
 *  If some input parameters are invalid, this function shall return
 *  NHT_CSD_TEST_ERROR_INVALID_PARAMETERS.
 *
 *  If opening succeeds, this function shall return
 *  NHT_CSD_TEST_NO_ERROR and shall provide an associated test run handle.\n
 *  In this case, usage of the chipset resources associated to this
 *  test run shall be granted by the platform until the test run
 *  session is closed.
 *
 *  After opening of such a test run session, harness test application are
 *  free to preset key values or to directly start the test run.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/

TCsdStatus nhtCsdOpenScrTestRunSession
(
  const TNhtCsdScrTestRunParameters * pxScrTestRunParameters,
  TNhtCsdScrTestRunHandle           * pxScrTestRunHandle
);


/*!
 *  @ingroup nht_scr
 *
 *  @brief
 *    Asynchronously start a SCR test run identified by its handle.
 *
 *  @param[in,out]  xScrTestRunHandle
 *    SCR session handle
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function starts the asynchronous SCR test run identified by its
 *  handle.
 *
 *  This function stands as a non blocking function.\n
 *  The SCR started test run shall be executed in background
 *  (= concurrently to the thread context of the caller of this
 *  function).\n
 *  This function shall return immediately independently
 *  of the normal or abnormal termination of the test run
 *  executed in background.
 *
 *  Application is responsible for having successfully opened a SCR
 *  test run session prior to start such a test run.
 *
 *  The application is responsible to setup SCR keys prior to start
 *  such a SCR test run.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/

TNhtCsdTestRunStatus nhtCsdStartScrTestRun
(
  TNhtCsdScrTestRunHandle xScrTestRunHandle
);


/*!
 *  @ingroup nht_scr
 *
 *  @brief
 *    Wait on completion of a SCR test run identified by its handle.
 *
 *  @param[in,out] xScrTestRunHandle
 *    SCR test run handle
 *
 *  @param[in]  xTimeout
 *    Timeout
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function waits on completion of a SCR test run
 *  identified by its SCR test run session handle.
 *
 *  Parameter 'xTimeout' specifies a timeout for this function call.\n
 *  If this parameter is passed as -1, no timeout restriction is required
 *  by the caller and this function shall block until normal or abnormal
 *  termination of the service run.
 *
 *  If not passed as -1, parameter 'xTimeout' is a timeout
 *  value expressed in second.\n
 *  If the associated service run is not finished yet at timeout expiration,
 *  this function shall return NHT_CSD_TEST_ERROR_WOULD_BLOCK.
 *
 *  At normal or abnormal completion of the test run, any pending calls to
 *  this function shall immediately return.\n
 *  If the test run successfully terminated, this function shall immediately
 *  return NHT_CSD_TEST_NO_ERROR.\n
 *  Otherwize, it shall return NHT_CSD_TEST_ERROR_SERVICE_RUN_FAILER.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/

TNhtCsdTestRunStatus nhtCsdWaitOnScrTestRunCompletion
(
  TNhtCsdScrTestRunHandle xScrTestRunHandle,
  int                     xTimeout
);


/*!
 *  @ingroup nht_scr
 *
 *  @brief
 *    Stop a SCR test run identified by its handle.
 *
 *  @param[in,out] xScrTestRunHandle
 *    SCR test run handle.
 *
 *  @retval   NHT_CSD_TEST_NO_ERROR
 *              The SCR test run successfully started.
 *  @retval   NHT_CSD_TEST_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   NHT_CSD_TEST_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function immediately stops a SCR test run identified by
 *  its SCR test run handle if not already stopped.
 *
 *  If the test run already abnormally stopped, this function shall return
 *  NHT_CSD_TEST_ERROR_SERVICE_RUN_FAILER.
 *
 *  Otherwize, it shall return NHT_CSD_TEST_NO_ERROR.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/
TNhtCsdTestRunStatus nhtCsdStopScrTestRun
(
  TNhtCsdScrTestRunHandle   xScrTestRunHandle
);


/*!  @ingroup nht_scr
 *
 *  @brief
 *    Set the Host encryption key associated to SCR test run session
 *
 *  @param[in,out] xScrTestRunHandle
 *    Scr Service handle associated to the SCR service run
 *  @param[in]      pxClearTextScrHostKey
 *                   Pointer to the location where the function has to read the
 *                   Clear Text SCR Hostkey.
 *  @param[in]      xClearTextScrHostKeySize
 *                   Size in bytes of the Clear Text SCR Hostkey.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to read the
 *                   Initialization Vector or the first counter block.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
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
 *  This function set the encryption Clear Text SCR Hostkey (software provided
 *  key) associated to a SCR test run session.
 *
 *  pxClearTextScrHostKey contains the Clear Text HostKey. The size of this key
 *  must be a 16-byte vector. In all other cases, the function shall return
 *  CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If the EMI associated to this test run is set to one of the chaining mode,
 *  pxInitializationVector is used to pass the Initialization Vector to the
 *  Stream Crypto Engine(s) associated to the test run.
 *
 *  Size of this vector depends on the cryptographic algorithm (exemple: 16 bytes
 *  for AES and 8 bytes for TDES). In all other cases, the function shall return
 *  CSD_ERROR_INVALID_PARAMETERS.
 *
 *  @note
 *    This function overwrites the use of the 'csdSetClearTextScrEncryptionKey()'
 *    function defined in the CSD API. In particular, the
 *    'csdSetClearTextScrEncryptionKey()' is never directly called by the
 *    harness test application. However, implementation of this function
 *    shall include calls to the underlaying csdSetClearTextDscHostKeys()
 *    function.
 *
 *    EMI that applies to 'csdSetClearTextScrEncryptionKey()' function call in
 *    implementation implicitly refers to the one setup at test run session
 *    opening time.
 *
 */

TCsdStatus nhtCsdSetClearTextScrEncryptionKey
(
        TNhtCsdScrTestRunHandle   xScrTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextScrHostKey,
        TCsdSize                  xClearTextScrHostKeySize,
  const TCsdUnsignedInt8        * pxInitializationVector,
        TCsdSize                  xInitializationVectorSize
);


/** @ingroup nht_scr
 *
 *  @brief
 *    Set the Host decryption key associated to a SCR test run session.
 *
 *  @param[in,out]  xScrTestRunHandle
 *                   Scr test run handle.
 *  @param[in]      pxClearTextScrHostKey
 *                   Pointer to the location where the function has to read the
 *                   Clear Text SCR Hostkey.
 *  @param[in]      xClearTextScrHostKeySize
 *                   Size in bytes of the Clear Text SCR Hostkey.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to read the
 *                   Initialization Vector or the first counter block.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *              The key path handle passed as parameter are invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function set the decryption Clear Text SCR Hostkey (software provided
 *  key) associated to a SCR test run session.
 *
 *  pxClearTextScrHostKey contains the Clear Text HostKey.\n
 *  The size of this key must be a 16-byte vector.\n
 *  In all other cases, the function shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If the EMI of the test session was set to one of the chaining mode,
 *  pxInitializationVector is used to pass the Initialization Vector to the
 *  Stream Crypto Engine(s) associated to this test run.
 *
 *  The size of this vector depends on the cryptographic algorithm
 *  (exemple: 16 bytes  for AES and 8 bytes for TDES).\n
 *  In all other cases, the function shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  @note
 *    This function overwrites the use of the 'csdSetClearTextScrDecryptionKey()'
 *    function defined in the CSD API.\n
 *    In particular, the 'csdSetClearTextScrDecryptionKey()' is never directly
 *    called by the harness test application.\n
 *    However, implementation of this function shall include calls to the
 *    underlaying csdSetClearTextScrDecryptionKey() function.
 *
 *    EMI that applies to 'csdSetClearTextScrDecryptionKey()' function call in
 *    implementation implicitly refer to the one setup at test run session
 *    opening time.
*/
TCsdStatus nhtCsdSetClearTextScrDecryptionKey
(
        TNhtCsdScrTestRunHandle   xScrTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextScrHostKey,
        TCsdSize                  xClearTextScrHostKeySize,
  const TCsdUnsignedInt8        * pxInitializationVector,
        TCsdSize                  xInitializationVectorSize
);


/**  @ingroup nht_scr
 *
 *  @brief
 *    Set the Content key associated to a SCR test run session.
 *
 *  @param[in,out] xScrTestRunHandle
 *    Scr Service opaque handle associated to the SCR service run
 *  @param[in]      pxScrCipheredProtectingKeys
 *                   Array of Ciphered Protecting Keys
 *  @param[in]      xCipheredProtectingKeyNumber
 *                   size of the Protecting Keys array
 *  @param[in]      pxCipheredScrContentKey
 *                   Pointer to the location where the function has to read the
 *                   Ciphered SCR Contentkey.
 *  @param[in]      xCipheredScrContentKeySize
 *                   Size in bytes of the Ciphered SCR Contentkey.
 *  @param[in]      pxInitializationVector or the first counter block.
 *                   Pointer to the location where the function has to read the
 *                   InitializationVector.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
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
 *  This function configures the key ladder(s) associated to a SCR test run
 *  with the Ciphered Protecting Keys and set the CWs provided in protected
 *  form into the specified path of the Stream Crypto Engine.
 *
 *  'pxScrCipheredProtectingKeys' contains all the Ciphered Protecting Keys.\n
 *  The number of those keys contained in this array is defined by the
 *  constant CSD_SCR_NB_OF_PROTECTING_KEYS, fixed to 2 in NOCS3.
 *
 *  The size of these keys shall be:
 *      - 0 if the CW is not available.
 *      - 8 if the cryptographic algorithm is requesting 8 bytes.
 *      - 16 if the cryptographic algorithm  is requesting 16 bytes.
 *      - In all other cases, the function shall return
 *        CSD_ERROR_INVALID_PARAMETERS.
 *
 *  'pxScrCipheredProtectingKeys' array parameter structure and key ladder
 *  Key level values follows this rule (for 1 <= 'i' <= 'xCipheredProtectingKeyNumber',
 *  when 'i' is the protecting key level ):
 *
 *   - pxScrCipheredProtectingKeys[xCipheredProtectingKeyNumber - 'i']   refer to Key Ladder KL<'i'> key
 *
 *  If the xEmi set for the test run refers to a chaining mode,
 *  pxInitializationVector is used to pass the Initialization Vector to
 *  the Stream Crypto Engine.\n
 *  The size of this vector depends on the cryptographic algorithm
 *  (exemple: 16 bytes  for AES and 8 bytes for TDES).\n
 *  In all other cases, the function shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  @note
 *    This function overwrite the use of the 'csdSetProtectedScrDecryptionKey()'
 *    function defined in the CSD API.\n
 *    In particular, the 'csdSetProtectedScrDecryptionKey()' is never directly
 *    called by the harness test application.\n
 *    However, implementation of this function shall include calls to the
 *    underlaying csdSetProtectedScrDecryptionKey() function.
 *
 *    EMI that applies to 'csdSetProtectedScrDecryptionKey()' function call in
 *    implementation implicitly refer to the one setup at test run session
 *    opening time.
*/
TCsdStatus nhtCsdSetProtectedScrDecryptionKey
(
        TNhtCsdScrTestRunHandle         xScrTestRunHandle,
  const TNhtProtectingKey             * pxScrCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize
);

/** @ingroup nht_scr
 *
 *  @brief
 *    Set the Content key associated to a SCR test run session.
 *
 *  @param[in,out] xScrTestRunHandle
 *    Scr Service opaque handle associated to the SCR service run
 *  @param[in]      pxScrCipheredProtectingKeys
 *                   Array of Ciphered Protecting Keys
 *  @param[in]      xCipheredProtectingKeyNumber
 *                   size of the Protecting Keys array
 *  @param[in]      pxCipheredScrContentKey
 *                   Pointer to the location where the function has to
 *                   read the Ciphered SCR Contentkey.
 *  @param[in]      xCipheredScrContentKeySize
 *                   Size in bytes of the Ciphered SCR Contentkey.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to
 *                   read the InitializationVector or the first counter
 *                   block.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
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
 *  This function configures the key ladder(s) associated to a SCR test run
 *  with the Ciphered Protecting Keys and set the CWs provided in protected
 *  form.
 *
 *  'pxScrCipheredProtectingKeys' contains all the Ciphered Protecting Keys.\n
 *  The number of those keys contained in this array is defined by the
 *  constant CSD_SCR_NB_OF_PROTECTING_KEYS, fixed to 2 in NOCS3.
 *
 *  The size of these keys shall be:
 *      - 0 if the CW is not available.
 *      - 8 if the cryptographic algorithm is requesting 8 bytes.
 *      - 16 if the cryptographic algorithm  is requesting 16 bytes.
 *      - In all other cases, the function shall return
 *        CSD_ERROR_INVALID_PARAMETERS.
 *
 *  'pxScrCipheredProtectingKeys' array parameter structure and key ladder
 *  Key level values follows this rule (for 1 <= 'i' <= 'xCipheredProtectingKeyNumber',
 *  when 'i' is the protecting key level ):
 *
 *   - pxScrCipheredProtectingKeys[xCipheredProtectingKeyNumber - 'i']   refer to Key Ladder KL<'i'> key
 *
 *  If the xEmi set for this test run refers to a chaining mode,
 *  pxInitializationVector is used to pass the Initialization Vector
 *  to the Stream Crypto Engine(s) associated to this test run.
 *
 *  The size of this vector depends on the cryptographic algorithm
 *  (exemple: 16 bytes  for AES and 8 bytes for TDES).\n
 *  In all other cases, the function shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  @note
 *    This function overwrite the use of the 'csdSetProtectedScrEncryptionKey()'
 *    function defined in the CSD API.\n
 *    In particular, the 'csdSetProtectedScrEncryptionKey()' is never directly
 *    called by the harness test application.\n
 *    However, implementation of this function shall include calls to the
 *    underlaying csdSetProtectedScrEncryptionKey() function.
 *
 *    EMI that applies to 'csdSetProtectedScrEncryptionKey()' function call in
 *    implementation implicitly refer to the one setup at test run session
 *    opening time.
 */
TCsdStatus nhtCsdSetProtectedScrEncryptionKey
(
        TNhtCsdScrTestRunHandle         xScrTestRunHandle,
  const TNhtProtectingKey             * pxScrCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize
);


/**
 *  @ingroup nht_scr
 *
 *  @brief
 *    Close a SCR test run session
 *
 *  @param[in,out]  xScrTestRunHandle
 *                   SCR test run session handle.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function closes a SCR test run session that was previously opened
 *  using the 'nhtCsdOpenScrTestRunSession()' function.
 *
 *  This function is intended to let chipset manufacturer implementation to
 *  properly release the associated resources it reserved (specific
 *  chipset manufacturer concern) for this test run.
 *
 *  @remark
 *    This is a pure additional function introduced for harness test purpose.\n
 *    In particular, it does not overwrite any other functions defined in
 *    the underlaying CSD driver API.
*/
TCsdStatus nhtCsdCloseScrTestRunSession
(
  TNhtCsdScrTestRunHandle xScrTestRunHandle
);


#ifdef __cplusplus
}
#endif


#endif /* NHT_CSD_H */

/* nocs_csd.h */
