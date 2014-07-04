/**
**  @file nocs_nhtctd.h
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset harness tests
**
**    This header file describes the API of the CTD driver API
**    that need to be implemented by the Chipset Manufacturer in
**    order to be able to comply with the Harness test toolkit provided by
**    Nagra.
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


#ifndef _CTD_NOCS_API_H_
#define _CTD_NOCS_API_H_


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Defines the version number of the CTD API. Note also that this version number
 * does not correspond to the version number of the software version.
 * @warning Do not update these values
*/
#define NHTCTDAPI_VERSION_MAJOR  1
#define NHTCTDAPI_VERSION_MEDIUM 1
#define NHTCTDAPI_VERSION_MINOR  1

/** @page p_history History
 *
 *   - <b> 1.0.0 2013/02/21 Nicolas Grosclaude</b>
 *     - Introduce functions associated to CTD NOCS harness test.
 *
 *   - <b> 1.1.0 2013/03/08 Nicolas Grosclaude</b>
 *     - Add CTD resource initialization/termination functions
 *     - Add CTD driver implementation info functions.
 *     - Improve PV function set for supporting chipset specific PVs.
 *        - Add chipset specific PVs reporting functions
 *     - Add OTP read/write low level functions
 *     - Update RAM scrambling enable/disable specification
 *       - Keep on-chipset fuse intact
 *     - Improve comments/documentation
 *
 *   - <b> 1.1.1 2013/07/05 Nicolas Grosclaude</b>
 *     - Add missing RAM_SCRAMBLING NOCS PV_ID
 *     - Suppress compilation warnings
 */

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include <stddef.h>

/***************************************************************************/
/*                                                                         */
/*                             OVERALL DOCUMENTATION                       */
/*                                                                         */
/***************************************************************************/

/**
 * @mainpage Overview
 * This API stands as the CTD API v1.1.1\n<hr>
 *
 *  - @subpage p_preface
 *  - @subpage p_history
 *  - @subpage p_ram_scrambling
 *  - @subpage p_mem_device_addressing_mode
 *  - @subpage pv_level
 *  - @subpage p_dsc_scr_bg_processing
 *  - @subpage p_dsc_test
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
 *  This document is intended for the manufacturers of MPEG secure chipsets
 *  who are partners of Nagravision and whose chipset has to pass a NOCS
 *  CTD Harness test certification.\n
 *
 *  This header file describes an API that need to be implemented by the
 *  Chipset Manufacturer in order to comply with the CTD Harness test
 *  toolkit provided by Nagra.
 *
 *  Implementation of this API is mandatory for passing a NOCS CTD
 *  certification.
 *
 *  This API is first intended to provide test facilities
 *  associated to a NOCS CTD harness test certification by preventing
 *  the chipset manufacturer to implement its own CTD test application.
 *  CTD test applications will be provided by Nagra.
 *
 *  This API shall be implemented by the chipset manufacturers for any
 *  new NOCS secure chipset that is candidate to a Nagra NOCS certification.
 *  Such extensions must be implemented by the Chipset Manufacturer the same
 *  way as the Chipset Manufucturer has to implement the CTD driver API.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for MPEG secure chipset manufacturers
 *  implementing NOCS requirements and candidate to a NOCS certification.
 *
 *  <hr><h2>References</h2>
 *  - [EMI] Nagravision, System Architecture, Encryption Method Indicator
 *     Specification, Version 1.0.7\n
 *  - [NOCS3REQ] Nagravision, NOCS3.0 Security Requirements Specification\n
 *  - [...] CTD API documention
 */

/** @page p_ram_scrambling Reversible RAM scrambling ON/OFF functions.
 *
 *  In addition to permanent RAM scrambling enabling features related to persistent
 *  value (PV) programming, this API introduces some additional functions
 *  intended to test the RAM scrambling ON/OFF in a reversible way regarding the
 *  chipset during a chipset certification.
 *
 *  These functions are:
 *   - nhtCtdEnableRamScrambling()
 *   - nhtCtdDisableRamScrambling()
 *
 *  For this purpose, these functions shall never alter persistent values of the chipset.
 *  These reversible RAM scrambling enabling/disabling functions can be implemented
 *  as 'sticky bit' or in-flash programming feature according to what what was
 *  agreed on for the chipset.
 */

/** @page p_mem_device_addressing_mode Memory device(s) read/write address expression.
 *
 *  This paragraph introduced the unified memory device addressing expression
 *  that applies to all memory devices (RAM, FLASHes) read and write operations
 *  in this API. This unified expression has been introduced for:
 *
 *  - Providing an addressing expression that fit to devices that can and those
 *    that can't be mapped in the CPU addressing space.\n
 *  - For memory that can be mapped in the CPU addressing space, avoid the
 *    confusion between physical and logical addressing concern.\n
 *  - Make this API independent of physical and logical mapping of devices
 *    that might depend of the board configuration (not necessarily of the
 *    chipset cut exclusivelly) [e.g: if SO-DIM memory is used on board].\n
 *  - Make this API independent of the number of physical devices of a same
 *    memory type that is implemented on a board. Regarding this API, a memory
 *    device type is allows unique independently of the number of associated physical
 *    devices that are effectivelly implemented on board.\n
 *  - For memory devices that can be mapped on CPU addressing space, make this
 *     API independent of potential discontinuity of physical memory devices
 *     accessibility in the CPU addressing space.\n
 *
 *  Here, the memory device type address expression is always expressed as an offset
 *  value associated to the memory device types. It is never expressed
 *  as a CPU logical or physical address pointer since such
 *  CPU addressing space map is incompatible with devices such as NAND-flash, SPI-flash, etc...
 *
 *  Because this memory device type relative addressing expression is not CPU addressing
 *  space related, physical or logical CPU addressing is here out of concern.
 *
 *  Chipset board implementing multiple phyical memory devices of a same type are
 *  viewed by the API as a single abstracted device having a size equal to
 *  the sum of all separated physical memory device of this type. In other word,
 *  this API definition is independent of device physical implementation on the board.
 *
 *  In this API, memory device address expression is viewed as a continuous space,
 *  independently of potential CPU addressing discontinuity associated
 *  to the board implementation (if CPU address space mapping is applicable).
 *
 *  Valid addressing values of a device type follows this rule: 0 <= address < mem_device_type_total_size(device_type)
 */

/** @page pv_level PV expression levels categories
 *
 *  In this API, the PV functions have been split into 2 categories representing
 *  different PV  input/output value expression levels:
 *    - PV (logical value) expression level functions (high level function).
 *    - PV OTP bit-field expression level functions (low level function).
 *
 *  PV logical expression level functions are functions for which input/output values
 *  express logical values. Expression of these values are independent of the Physical
 *  PV implementation in the chipset (e.g: independent of the underlying OTP of fuses).
 *
 *  Logical values that are applicable for a PV type result from (or condition)
 *    - A NOCS generic value system defintion (independent of the chipset: eg: STB CASN)
 *    - An chipset specific agreement between the CM and Nagra
 *
 *  PV OTP bit-field expression level function are functions for which input/output values
 *  are expressed as OTP bits. Functions of the category provide independent OTP bit
 *  programming mask allowing any OTP bit to be individually and conditionally programmed.
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
 *  Since DSC test run require additional Chipset system resources, dedicated
 *  functions are provided in order to abstract those Chipset Manufacturer's
 *  resource handling regarding the harness test tools provided Nagra.
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
 *  DSC test run functions introduced in this API fully abstract the CTD
 *  API underlying DSC key path handles associated to physical engines
 *  involved in the test run.
 *
 *  Key setting functions introduced in this API overwrites the ones found
 *  in CTD base API. In these overwritten functions, key setting apply to
 *  all services associated to the test run (e.g: Video, Audio),
 *  independently of the number of key ladder physical resources involved by
 *  chipset system architecture.
 *
 *  This will be the responsibility of the chipset manufacturer to setup the
 *  key values to the involved chipset key ladders of the test run according
 *  to the chipset architecture.
 *
 */

/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/
/** @defgroup gen_types General types definitions */

/** @defgroup init Chipset CTD resource initialization */

/** @defgroup info Chipset CTD implementation info */

/** @defgroup res Chipset Reset */

/** @defgroup ramprot RAM scrambling protection */

/** @defgroup mem_flash Flash Memory read/write interface */

/** @defgroup mem_RAM RAM Memory read/write interface */

/** @defgroup pvid PV identification interface*/

/** @defgroup pv PV logical read/write interface */

/** @defgroup phys_pv OTP read/write interface */

/** @defgroup r2r R2R encryption/decryption */

/** @defgroup dsc DSC encryption/decryption */

/** @defgroup scr SCR encryption/decryption */


/***************************************************************************/
/*                                                                         */
/*                              VERSION TOOL                               */
/*                                                                         */
/***************************************************************************/

#ifndef NHTCTD_TOOL_VERSION
#define NHTCTD_TOOL_STRINGIFY(s) NHTCTD_TOOL_TOSTRING(s)
#define NHTCTD_TOOL_TOSTRING(s)  #s

#define NHTCTD_TOOL_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
#define NHTCTD_TOOL_VERSION_DOT(a, b, c) a ##.## b ##.## c
#define NHTCTD_TOOL_VERSION(a, b, c) NHTCTD_TOOL_VERSION_DOT(a, b, c)
#endif

#define NHTCTDAPI_VERSION_INTER NHTCTD_TOOL_VERSION(CTDAPI_VERSION_MAJOR, \
              CTDAPI_VERSION_MEDIUM, \
              CTDAPI_VERSION_MINOR)

#define NHT_CTDAPI_VERSION_INT   \
  NHTCTD_TOOL_VERSION_INT(NHTCTDAPI_VERSION_MAJOR, \
    NHTCTDAPI_VERSION_MEDIUM, \
    NHTCTDAPI_VERSION_MINOR)

#define NHTCTDAPI_VERSION_STRING  \
  "NHTCTDAPI_" NHTCTD_TOOL_STRINGIFY(NHTCTDAPI_VERSION_INTER)


/******************************************************************************/
/*                                                                            */
/*                               TYPES & CONSTANTS                            */
/*                                                                            */
/******************************************************************************/

/**
 *  @brief
 *    Define the byte as an 8 bits vector.
 *
 *  Definition of the byte as an 8 bits vector. This type is the smallest piece
 *  of data in the API.
*/
typedef unsigned char TCtdUnsignedInt8;

/**
 *  @brief
 *    Define a type as an 16 bits vector.
 *
 *  Definition of a type as an 16 bits vector.
*/
typedef unsigned short int TCtdUnsignedInt16;

/**
 *  @brief
 *    Define a type as an 32 bits vector.
 *
 *  Definition of a type as an 32 bits vector.
*/
typedef unsigned long int TCtdUnsignedInt32;


/**
 *  @brief
 *    Define the CTD boolean type.
*/
typedef unsigned char TCtdBoolean;


/**
 *  @brief
 *    The boolean FALSE value.
*/
#ifndef FALSE
#define FALSE      0
#endif

#ifndef TRUE
/**
 *  @brief
 *    The boolean TRUE value.
*/
#define TRUE        (!FALSE)
#endif


/**
 *  @brief
 *    20 characters strings.
 *
 *  Defines a string buffer of 20 characters.
*/
typedef unsigned char TCtd20CharsString[20];


/**
 *  @ingroup gen_types
 *
 *  @brief
 *    Type definition of chipset size_t
*/
#ifndef _NHT_RPC_CLIENT_SIDE_
typedef size_t    TCtdSize;
#else
typedef uint64_t  TCtdSize;
#endif


/**
 *  @ingroup gen_types
 *
 *  @brief
 *    Define the NOCS set of flash types on the chipset board.
*/
typedef enum ECtdFlashType
{
  CTD_FLASH_NOR,
    /**< Parallel NOR Flash. */
  CTD_FLASH_SPI,
    /**< Serial NOR (SPI) Flash. */
  CTD_FLASH_EMMC,
    /**< eMMC Flash. */
  CTD_FLASH_NAND,
    /**< Standard NAND Flash. */
  LAST_CTD_FLASH
    /**< TCtdFlashType type upper boundary. */
} TCtdFlashType;


/**
 *  @ingroup gen_types
 *
 *  @brief
 *    Return values of the CTD functions.
 *
*/
typedef enum
{
  CTD_NO_ERROR,
    /**< The intended operation was executed successfully. */
  CTD_ERROR,
    /**< The function terminated abnormally. The intended operation failed. */
  CTD_ERROR_DRIVER_ALREADY_INITIALIZED,
    /**<  The CTD is already initialized. */
  CTD_ERROR_INVALID_PARAMETERS,
    /**< The passed parameters are invalid. */
  CTD_ERROR_NOT_SUPPORTED,
    /**< This function is not supported by the driver */
  CTD_ERROR_OPERATION_NOT_ALLOWED,
    /**< The operation is not allowed. */
  CTD_ERROR_BAD_USAGE,
    /**< The usage is not allowed. */
  CTD_ERROR_NOT_IMPLEMENTED,
    /**< The function is not implemented */
  LAST_CTD_STATUS
    /**< TCtdStatus type upper boundary. */
} TCtdStatus;


/**
 *  @ingroup gen_types
 *
 *  @brief
 *   Test run statuses type definition
 *
*/
typedef enum ENhtCtdTestRunStatus
{
  NHT_CTD_TEST_NO_ERROR,
    /**< The intended test operation was executed successfully. */
  NHT_CTD_TEST_ERROR,
    /**< The test operation encountered an internal failer. */
  NHT_CTD_TEST_ERROR_WOULD_BLOCK,
    /**< The test operation encountered would block. */
  NHT_CTD_TEST_ERROR_INVALID_PARAMETERS,
    /**< Invalid parameter error. */
  NHT_CTD_TEST_ERROR_INVALID_FILE_PATHNAME,
    /**< Invalid File pathname. */
  NHT_CTD_TEST_ERROR_SERVICE_CURRENTLY_IN_USED,
    /**< chipset resource currently in use. */
  NHT_CTD_TEST_ERROR_TEST_RUN_NOT_STARTED,
    /**< test run not started. */
  NHT_CTD_TEST_ERROR_SERVICE_RUN_FAILLER
    /**< test run execution failer. */

} TNhtCtdTestRunStatus;


/**
 *  @brief
 *    Dif mode.
 *
*/
typedef enum
{
  CTD_DIF_OPEN,
    /**< Open mode. */
  CTD_DIF_PWD,
    /**< Password Protected mode. */
  CTD_DIF_CLOSED,
    /**< Closed mode. */
  LAST_CTD_DIF
    /**< TCtdDifMode type upper boundary. */
} TCtdDifMode;

/******************************************************************************/
/*                                                                            */
/*                    CTD Resource Initialization                             */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup init
 *
 *  @brief
 *    Initialize the CTD harness test resource usage.
 *
 *  @retval   CTD_NO_ERROR
 *              Initialization was completed successfully.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function is intended to let the chipset manufacturer perform some
 *  potential specific pre-initialization before an instance of an application
 *  is enabled to successfully use the CTD system resources involved in harness test.\n
 *  This includes pre-initialization of CTD SW/HW resource as well all other
 *  system resources not covered by the CTD driver basic-API such as video/audio
 *  descrambler, DMAs, etc...
 *
 *  The application is responsible to call this function at least once before using
 *  any other functions of the CTD APIs.\n
 *  If pre-initialization succeeds or  if this one was already successfully
 *  initialized for this process instance, return "CTD_NO_ERROR".
 *
 *  PS: If the CTD resource termination succeeds or if these ones where not
 *  initialized yet, return "CTD_NO_ERROR".
 */
TCtdStatus nhtCtdInitialize (void);


/**
 *  @ingroup init
 *
 *  @brief
 *    Terminate the CTD harness test resource usage.
 *
 *  @retval   CTD_NO_ERROR
 *              Termination was completed successfully.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function terminates the CTD resource usage associated to an application
 *  instance.\n
 *  This function is intended to let the chipset manufacturer properly
 *  clean-up all CTD resources that were previously allocated (or engage)
 *  during the execution of the current harness test application instance for
 *  well-running of subsequent application instanciations.
 *
 *  CTD resource termination shall be implicite at application termination in
 *  order to ensure that subsequent application will run well.
 *
 *  After calling this function, subsequent CTD resources re-initializations (using
 *  the 'nhtCtdInitialize()' funtion) shall be supported.
 */
TCtdStatus nhtCtdTerminate (void);


/******************************************************************************/
/*                                                                            */
/*                            CTD Driver Info                                 */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup info
 *
 *  @brief
 *    Get the current version of the Harness test CTD Driver extension
 *    Implementation.
 *
 *  @param[out]     xSoftwareVersion
 *                   20 characters string where the function has to write
 *                   the software version string.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              Invalid input parameter (passed as NULL)
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the CTD Driver extension
 *  implementation.\n
 *  It is represented as a character string, the internal
 *  format being chipset manufacturer dependent.\n
 *  However, the length of the string is fixed at 20 characters.\n
 *  The string must be terminated by the end character '\\0'.
*/
TCtdStatus nhtCtdGetSoftwareVersion
(
  TCtd20CharsString  xSoftwareVersion
);


/******************************************************************************/
/*                                                                            */
/*                                  RESET                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup res
 *
 *  @brief
 *    Reset type definition.
 *
*/
typedef enum ECtdResetType
{
  CTD_HW_RESET_TYPE,
    /**< HW reset type. */
  CTD_SW_RESET_TYPE
    /**< SW reset type */
} TCtdResetType;


/**
 *  @ingroup res
 *
 *  @brief
 *    Performs a chipset reset.
 *
 *  @param[in]  xResetType
 *               Reset type identifier
 *
 * This function does not return.
*/
void nhtCtdChipReset
(
  TCtdResetType xResetType
);


/**
 *  @ingroup res
 *
 *  @brief
 *    Set the chipset in Suspend-to-RAM mode.
 *
 * This function does not return.
*/
void nhtCtdChipSuspend2Ram (void);



/******************************************************************************/
/*                                                                            */
/*                           RAM scrambling control                           */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup ramprot
 *
 *  @brief
 *    Enable the RAM Scrambling (reversible setting)
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_OPERATION_NOT_SUPPORTED
 *              The function is not allowed or supported by the chipset.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This low-level function enables the Scrambling mechanism in a reversible way.
 *
 *  This function is provided as a mean to test the RAM scrambling in a reversible
 *  way during harness test. In any case, using this function shall never alter
 *  any OTP value(s).
 *
 *  This function can be implemented as a sticky bit or as an in-Flash parameter
 *  according to the technology that was agreed for the chipset.
 *
 *  If the function is not supported by the chipset, it shall return
 *  CTD_ERROR_OPERATION_NOT_SUPPORTED.
*/
TCtdStatus nhtCtdEnableRamScrambling
(
  void
);

/**
 *  @ingroup ramprot
 *
 *  @brief
 *    Disable the RAM Scrambling (reversible setting)
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_OPERATION_NOT_SUPPORTED
 *              The function is not supported by the chipset.
 *  @retval   CTD_ERROR_OPERATION_NOT_ALLOWED
 *              The operation failed because RAM scrambling was permanently enabled
 *              (using fuse)
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function allows the client software to disable the RAM scrambling mechanism.
 *
 *  This function is provided as a mean to test the RAM scrambling in a
 *  reversible way during harness test. Disabling RAM scrambling is only
 *  applicable if RAM scrambling wasn't permanently enabled using OTP.
 *  If RAM scrambling was permanently fused on the chipset (OTP programming),
 *  shall return CTD_ERROR_OPERATION_NOT_ALLOWED.
 *
 *  This function shall never alter OTP programming. For permentently RAM scrambling
 *  enabling (using OTPs), please refer to PV setting functions here below.
 *
 *  If this function is not supported by the chipset, it shall return
 *  CTD_ERROR_OPERATION_NOT_SUPPORTED.
*/
TCtdStatus nhtCtdDisableRamScrambling
(
  void
);


/**
 *  @ingroup ramprot
 *
 *  @brief
 *    Get the RAM Scrambling enable status
 *
 *  @param[out]     pxIsEnabled
 *                   Pointer to the location where the function has to write the
 *                   'isEnabled" status.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              The passed parameter is invalid.
 *  @retval   CTD_ERROR_OPERATION_NOT_SUPPORTED
 *              The function is not supported by the chipset.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function allows the client software to read the current RAM scrambling
 *  SW enabled/disabled status. See functions nhtCtdEnableRamScrambling() and
 *  nhtCtdDisableRamScrambling() for SW activation/deactivttion of the RAM
 *  scrambling.
 *
 *  If the RAM scrambling was permanently enabled (using fuse), pxIsEnabled shall
 *  always be setup to 1. Note that
 *
 *  If an invalid parameter is passed to the function, the function shall return
 *  CTD_ERROR_INVALID_PARAMETERS.
 *
 *  If the function is not supported by the chipset, return
 *  CTD_ERROR_OPERATION_NOT_SUPPORTED.
*/
TCtdStatus nhtCtdIsRamScramblingEnabled
(
  TCtdBoolean * pxIsEnabled
);


/******************************************************************************/
/*                                                                            */
/*                           FLASH MEMORY ACCESS                              */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup mem_flash
 *
 *  @brief
 *    Get the Flash memory device(s) memory size (in bytes)
 *
 *  @param[in]      xFlashType
 *                   Flash type identifier.
 *
 *  @param[out]     pxMemorySize
 *                   Flash type memory size
 *
 *  @retval   CTD_NO_ERROR
 *              The specified flash devices is effectivelly present on
 *              the chipset board.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              The specified flash device type is not defined in the
 *              flash type enum.
 *
 *  @retval   CTD_ERROR_OPERATION_NOT_SUPPORTED
 *              The specified flash device(s) is defined but not supported
 *              or not HW implemented of the chipset board.
 *
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the memory size of a specified flash device(s) type.
 *  Size shall be expressed in bytes.
 *
 *  The flash device(s) type memory size stands as the sum of all associated
 *  flash physical devices memory on the chipset board. In other word,
 *  this function is board flash devices number agnostics.
 *
 *  This function is intended to let the harness test framework know the amount of
 *  on chipset-board memory size associated to a flash device(s) type. Such information
 *  may used by the test framework to identify which memory area are meaningful
 *  during read and write operations.
*/
TCtdStatus nhtCtdGetFlashMemorySize
(
  TCtdFlashType   xFlashType,
  TCtdSize      * pxMemorySize
);


/**
 *  @ingroup mem_flash
 *
 *  @brief
 *    Reads a block of data from Flash.
 *
 *  @param[in]      xFlashType
 *                   Type of Flash.
 *
 *  @param[in]      xAddress
 *                   Address where the Data should be read.
 *
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
 *
 *  @param[out]      pxData
 *                   Pointer to the location where the function has to
 *                   store the Data read from Flash.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxData parameter is invalid.
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *              Flash type not supported.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function read a block of data from a Flash device(s) type.
 *
 *  The 'xAddress' parameter is expressed as the memory device(s) offset relative to the
 *  flash device(s) type from where data shall be read. See chapter 'Memory read/write
 *  address expression' in the overview of this document for more information.
 *
 *  'xAddress' values are assumed to be supported within the following range:
 *     0 <= 'xAddress' < flash_memory_size : where flash_memory_size is given by the
 *     nhtCtdGetFlashMemorySize() function.
 *
 *  Memory offset value associated to 'xAddress' is on-board physical devices number agnostic.
 *  Multiple physical devices in HW implementation are always viewed as a single abstracted flash
 *  device regarding this function. This is the responsibility of the CTD driver implementation
 *  to handle read operations successfully (accross multiple flash physical devices HW implementation)
 *  in a offset continious value range expression.
 *
*/
TCtdStatus nhtCtdFlashRead
(
  TCtdFlashType      xFlashType,
  TCtdSize           xAddress,
  TCtdSize           xDataSize,
  TCtdUnsignedInt8 * pxData
);

/**
 *  @ingroup mem_flash
 *
 *  @brief
 *    Writes a block of data into Flash.
 *
 *  @param[in]      xFlashType
 *                   Identifier of the Flash device(s) type.
 *
 *  @param[in]      xAddress
 *                   Flash device memory Address where the Data shall be written.
 *
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data to be written.
 *
 *  @param[in]      pxData
 *                   Pointer to the location where the function has to
 *                   read the Data to be written in Flash.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxData parameter is invalid.
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *              Flash type not supported.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function writes a block of data from a Flash device(s) type.
 *
 *  The 'xAddress' parameter is expressed as the memory device(s) offset relative to the
 *  flash device(s) type from where data shall be read. See chapter 'Memory read/write
 *  address expression' in the overview of this document for more information.
 *
 *  'xAddress' values are assumed to be supported within the following range:
 *     0 <= 'xAddress' < flash_memory_size : where flash_memory_size is given by the
 *     nhtCtdGetFlashMemorySize() function.
 *
 *  Memory offset value associated to 'xAddress' is on-board physical devices number agnostic.
 *  Multiple physical devices in HW implementation are always viewed as a single abstracted flash
 *  device regarding this function. This is the responsibility of the CTD driver implementation
 *  to handle read operations successfully (accross multiple flash physical devices HW implementation)
 *  in a offset continious value range expression.
 *
 *  Only the area specified at function call shall be written. All other memory area
 *  shall remain unchanged after completion of this function.
*/
TCtdStatus nhtCtdFlashWrite
(
        TCtdFlashType      xFlashType,
        TCtdSize           xAddress,
        TCtdSize           xDataSize,
  const TCtdUnsignedInt8 * pxData
);


/******************************************************************************/
/*                                                                            */
/*                           RAM MEMORY ACCESS                                */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup mem_RAM
 *
 *  @brief
 *    Get the RAM device(s) memory size (in bytes) on the board.
 *
 *  @param[out]     pxMemorySize
 *                   RAM memory size
 *
 *  @retval   CTD_NO_ERROR
 *              Memory information successfully returned.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxMemorySize illegal parameter (e.g: passed as NULL)
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *              Function not implemented or not supported with the current
 *              CRT driver implementation.
 *
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the RAM memory size of a the RAM. Size shall be expressed in bytes.
 *
 *  The RAM memory size that shall be returned is the sum of all RAM physical
 *  RAM devices on the chipset board. In other word, this function RAM
 *  physical devices number agnostics regarding the board.
 *
 *  This function is intended to let the harness test framework know the amount of
 *  on chipset-board memory size associated to a flash device(s) type. Such information
 *  may used by the test framework to identify which memory area are meaningful
 *  during read and write operations.
*/
TCtdStatus nhtCtdGetRamMemorySize
(
  TCtdSize * pxMemorySize
);

/**
 *  @ingroup mem_RAM
 *
 *  @brief
 *    Reads a block of data from RAM.
 *
 *  @param[in]      xAddress
 *                   Address where the Data should be read.
 *
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
 *
 *  @param[out]      pxData
 *                   Pointer to the location where the function has to
 *                   store the Data read from RAM.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxData parameter is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function read a block of data from the RAM.
 *
 *  The 'xAddress' parameter is expressed as a physical memory offset relative to the
 *  RAM device(s) where data shall be written in.  See chapter 'Memory read/write
 *  address expression' in the overview of this document for more information.
 *
 *  'xAddress' values are assumed to be supported within the following range:
 *     0 <= 'xAddress' < flash_memory_size : where flash_memory_size is given by the
 *     ctdGetRamMemorySize() function.
 *
 *  Memory offset value associated to 'xAddress' is on-board physical devices number agnostic.
 *  Multiple physical devices in HW implementation are always viewed as a single abstracted flash
 *  device regarding this function. This is the responsibility of the CTD driver implementation
 *  to handle read operations successfully (accross multiple flash physical devices HW implementation)
 *  in a offset continious value range expression.
 *
*/
TCtdStatus nhtCtdRamRead
(
  TCtdSize           xAddress,
  TCtdSize           xDataSize,
  TCtdUnsignedInt8 * pxData
);

/**
 *  @ingroup mem_RAM
 *
 *  @brief
 *    Writes a block of data into RAM.
 *
 *  @param[in]      xAddress
 *                   Address where the Data should be written.
 *
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
 *
 *  @param[in]      pxData
 *                   Pointer to the location where the function has to
 *                   read the Data to be written in Flash.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxData parameter is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function writes a block of data into the RAM.
 *
 *  The 'xAddress' parameter is expressed as a physical memory offset relative to the
 *  RAM device(s) where data shall be written in. See chapter 'Memory read/write
 *  address expression' in the overview of this document for more information.
 *
 *  'xAddress' values are assumed to be supported within the following range:
 *     0 <= 'xAddress' < flash_memory_size : where flash_memory_size is given by the
 *     ctdGetRamMemorySize() function.
 *
 *  Memory offset value associated to 'xAddress' is on-board physical RAM devices number agnostic.
 *  Multiple physical devices in HW implementation are always viewed as a single abstracted flash
 *  device regarding this function. This is the responsibility of the CTD driver implementation
 *  to handle write operations successfully (accross multiple RAM physical devices HW implementation)
 *  in this offset contigeous value range expression.
 *
*/
TCtdStatus nhtCtdRamWrite
(
  TCtdSize                 xAddress,
  TCtdSize                 xDataSize,
  const TCtdUnsignedInt8 * pxData
);


/******************************************************************************/
/*                                                                            */
/*              PERSISTENT VALUES IDENTIFICATION INTERFACE                    */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup pvid
 *
 *  @brief
 *    Persistent Value Id type
 *
 *    A persitent Value Id identifies a particular PV type in the overall
 *    set of PVs types within a chipset.
 *
 *    Persistent Id values are separated in two categories:
 *    - NOCS standard PV category    (in value range 0x4000 - 0x7FFF)
 *    - chipset specific PV category (in value range 0x0000 - 0x3FFF)
 *
 *    NOCS standard PVs are generic Nagra-defined (reason why there are listed
 *    in this API). These ones correspond to PV that are NOCS
 *    defined (independently of the chipset). Normally, these ones
 *    shall all be supported, except for those for which a non-implementation
 *    agreement with Nagra was explicitly agreed.
 *
 *    Chipset specific PV Ids are defined by the CM. They correspond to additional
 *    PV types that are specifically defined for a particular chipset and that
 *    are not defined in generic NOCS specification.
 *
 *    If an existing PV type is not defined in the NOCS standard list here below,
 *    chipset manufacturer is required to create an associated PV type in the
 *    'chipset specific PV category' in respect with its Id value range.
 *
 *    Different PV types shall always have a unique ID value in the overall
 *    set of PVs of the chipset in order to un-ambigeously identify this one.
*/
typedef TCtdUnsignedInt32 TCtdPvId;


/*
 * NOCS standard predefined PV IDs
 */

#define CTD_NOCS_PVID_BOOTMODE_ID                     0x4000
/**< Bootmode PV type. */

#define CTD_NOCS_PVID_DIF_ID                          0x4001
/**< Debug interface PV type. */

#define CTD_NOCS_PVID_KLD_DEACTIVATION_ID             0x4002
/**< Key Ladder Deactivation PV type. */

#define CTD_NOCS_PV_FLASH_ACTIVATION_ID               0x4003
/**< Flash Protection Activation PV type. */

#define CTD_NOCS_PVID_SCS_ACTIVATION_ID               0x4004
/**< SCS activation PV type. */

#define CTD_NOCS_PVID_USS_ID                          0x4005
/**< Unscrambled Storage Size PV type. */

#define CTD_NOCS_PVID_MSID_ID                         0x4006
/**< Market Segment Id. */

#define CTD_NOCS_PVID_MSIDL_ID                        0x4007
/**< Lock of the Market Segment Id. */

#define CTD_NOCS_PVID_STBCASN_ID                      0x4008
/**< STB_CA_SN. */

#define CTD_NOCS_PVID_STBCASNL_ID                     0x4009
/**< STB_CA_SN Lock. */

#define CTD_NOCS_PVID_VER_ID                          0x400A
/**< Versioning_REF. */

#define CTD_NOCS_PVID_EBFDP_ID                        0x400B
/**< External Boot Flash Device Parameters (optional). */

#define CTD_NOCS_PVID_ERP_ID                          0x400C
/**< External RAM Parameters (optional). */

#define CTD_NOCS_PVID_SCS_DTE_Boot_Code_Area_ID       0x400D
/**< SCS_DTE_Boot_Code_area adress (optional). */

#define CTD_NOCS_PVID_AI_ID                           0x400E
/**< Active Indicator (optional). */

#define CTD_NOCS_PVID_SCSTASize_ID                    0x400F
/**< SCS_Total_Area size (optional). */

#define CTD_NOCS_PVID_ESCSFWUA_ID                     0x4010
/**< Full Ext_SCS_FW upgrade address (optional). */

#define CTD_NOCS_PVID_PESCSFWUA_ID                    0x4011
/**< Patch Ext_SCS_FW upgrade address (optional). */

#define CTD_NOCS_PVID_ESCSFWUS_ID                     0x4012
/**< Full Ext_SCS_FW upgrade size (optional). */

#define CTD_NOCS_PVID_PESCSFWUS_ID                    0x4013
/**< Patch Ext_SCS_FW upgrade size (optional). */

#define CTD_NOCS_PVID_RAM_SCRAMBLE_ACTIVATION_ID      0x4014
/**< RAM scrambling activation PV type. */


/**
 *  @ingroup pvid
 *
 *  @brief
 *    chipset specific PV set descriptor type
*/
typedef struct SCtdSpecificPvDescriptor
{
  TCtdPvId   pvId;
  /**<  The chipset specific Pv Id associated to this descriptor. */

  TCtd20CharsString   pvIdName;
  /**<  The string name of this PV (must be \000 terminated) */

} TCtdSpecificPvDescriptor;


/**
 *  @ingroup pvid
 *
 * @brief
 *   Get the number of chipset specific PV types of the chipset.
 *
 *  @pre
 *    None
 *
 *  @post
 *    None.
 *
 *  @param[out]   pxSpecificPvNumber
 *    Number of chipset specific PV types of the chipset
 *
 *  @retval   CTD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  This functions return the number of 'chipset specific PV' of the chipset.
 *
 *  Note that NOCS standard PVs (Id range 0x4000-0x7FFF) shall not be counted.
 *
 *  Purpose of this function is to inform the harness test tools about the
 *  specific PVs associated to the chipset.\n
 *
*/
TCtdStatus nhtCtdGetSpecificPvDescriptorNumber
(
  TCtdUnsignedInt32 * pxSpecificPvNumber
);


/**
 *  @ingroup pvid
 *
 * @brief
 *   Get the 'chipset specific PV descriptor set of the chipset.
 *
 *  @param[in]     xSpecificPvNumber
 *    Number of pre-allocated specific PV descriptors to be filled up.
 *
 *  @param[out]    pxSpecificPvDescriptors
 *    Address of the pre-allocated specific PV descriptor array.
 *    (size of this pre-allocated array is defined by the
 *    'xSpecificPvNumber' input parameter)
 *
 *  @param[out]    pxSpecificPvEffectiveNumber
 *    Effective descriptor number that has been filled-up.
 *
 *  @retval   CTD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  This function allows the application to get the info relative to
 *  the chipset specific PVs supported by the chipset.
 *
 *  Implementation of this function is reponsible to fill-up all
 *  specific PV descriptors of the descriptor set with the
 *  following information fields:
 *  - 'pvId' field:
 *      A CM's specific PV id value.
 *  - 'pvIdName' field:
 *    A brief PV description string
 *
 *  PV descriptors associated to PV Id in the "NOCS standard PV id category"
 *  (range 0x4000-0x7FFF) shall not be reported as descriptor when using this function.
 *
 *  PS: Implementation of this function shall grant that there is no
 *  'pvId' duplicated descriptor in the return set.
 *
*/
TCtdStatus nhtCtdGetSpecificPvDescriptorSet
(
  TCtdUnsignedInt32          xSpecificPvNumber,
  TCtdSpecificPvDescriptor * pxSpecificPvDescriptors,
  TCtdUnsignedInt32        * pxSpecificPvEffectiveNumber
);


/******************************************************************************/
/*                                                                            */
/*                        LOGICAL PV Interface                                */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup pv
 *
 *  @brief
 *    PV set status type definition
*/
typedef enum ECtdPvSetStatus
{
  CTD_PV_SET_STATUS_NOTSET,
    /**< PV is not set. */
  CTD_PV_SET_STATUS_SET,
    /**< PV is set (but not locked yet). */
  LAST_CTD_PV_SET_STATUS
    /**< TCtdPvStatus type upper boundary. */

} TCtdPvSetStatus;


/**
 *  @ingroup pv
 *
 *  @brief
 *    Get the programming status associated to a PV type ID.
 *
 *  @param[in]      xPvId
 *    Persistent Value type identifier.
 *
 *  @param[out]     pxPvStatus
 *    Programming status associated to the specified PV type.
 *
 *  @retval   CTD_NO_ERROR
 *    The function operated successfully.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *    One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested PV type is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  This function returns the 'programming status' associated to a PV type.
 *
 *  If some input parameters are invalid or if the PV ID is unknown,
 *  return CTD_ERROR_INVALID_PARAMETERS.
 *
 *  If the feature is currently not supported, return CTD_ERROR_NOT_SUPPORTED.
 *
 *  In case of success, return CTD_NO_ERROR and 'pxPvSetStatus' parameter shall be setup to:
 *     - CTD_PV_SET_STATUS_NOTSET
 *        If this PV is not programmed (or if it still contains
 *        a unprogrammed value that might be overwriten)
 *     - CTD_PV_SET_STATUS_SET
 *        If this PV is already programmed.
 *
 *  If the associated PV programming is/becomes inconsistant (neither set nor unset),
 *  this function shall return CTD_ERROR. Note that never set PVs are always considered
 *  as consistant.
*/
TCtdStatus nhtCtdGetPvStatus
(
  TCtdPvId          xPvId,
  TCtdPvSetStatus * pxPvStatus
);


/**
 *  @ingroup pv
 *
 * @brief
 *   Set the chipset active flash type that applies at boot time.
 *
 *  @param[in]      xBootFlashType
 *                   Mode which has to be used by the Boot Mode is requested to
 *                   be set.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              The boot mode passed as parameter is out of type.
 *  @retval   CTD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function allows the client software to configure the Flash Boot Mode PV of the
 *  chipset. Once this mode has been been set, the chipset will always boot in
 *  this Boot Mode.
 *
 *  This dedicated function allows the user application to specify on which
 *  flash device the chipset shall boot in a way that is chipset specific
 *  feature agnostic (NOCS generic expresssion).
 *
 *  If the flash type specified as parameter cannot serve as a boot device, this
 *  function shall return CTD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  PS: See for other bootmode setting mode, please refer to nhtCtdSetPv() and
 *  nhtCtdSetOtp() functions (with PV Id = 'CTD_NOCS_PVID_BOOTMODE_ID'.
 *
 *  According to the CTD API purpose, all bootmode change requests shall
 *  be operated to the chipset OTP without any SW check.
 *
 *  If the PV programming was effectivelly executed, this
 *  function shall return CTD_NO_ERROR. This concern applies independently
 *  of the associated OTPs well-programming
 *  (no embedded verification in the implementation of this function).
 *  PS: Well programming verification will explicitly and
 *  exclusivelly done by the the harness test framework.
 *
 *  PS: See for other bootmode getting mode, please refer to nhtCtdGetPv() and
 *  nhtCtdGetOtp() functions (with PV Id = 'CTD_NOCS_PVID_BOOTMODE_ID'.
 *
*/
TCtdStatus nhtCtdSetBootMode
(
  TCtdFlashType xBootFlashType
);


/**
 *  @ingroup pv
 *
 * @brief
 *   Get the selected flash type that applies at boot time.
 *
 *  @param[out]     pxBootFlashType
 *                   Current boot flash type to be returned
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              pxBootFlashType is NULL (invalid parameter).
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *              The requested function is not supported by the driver implementation
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function allows the client software to read the configured
 *  flash Boot Mode from the PV.
 *
 *  This dedicated function allows the user application to get the boot flash
 *  info in a way that is chipset specific feature agnostic (NOCS generic expresssion).
 *
 *  If an invalid parameter is provided at function call, this function
 *  shall return CTD_ERROR_INVALID_PARAMETERS.
 *
 *  If input parameters is valid but the feature is current not
 *  supported, this function shall return CTD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If no valid flash device identifier is currently programmed (or if the
 *  associated OTP programmng is inconstistant), this function shall return CTD_ERROR.
*/
TCtdStatus nhtCtdGetBootMode
(
  TCtdFlashType * pxBootFlashType
);


/**
 *  @ingroup pv
 *
 *  @brief
 *    Select the Debug Interfaces mode
 *
 *  @param[in]  xDifMode
 *                New protection level which has to be used by the Debug
 *                Interface Protection Level is requested to switch.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              The protection level passed as parameter is out of type.
 *  @retval   CTD_ERROR_OPERATION_NO_SUPPORTED
 *              The operation is not supported by the driver implementation.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function allows the client software to configure the debug
 *  interface mode PV of the chipset.
 *
 *  This dedicated function allows the user application to specify the
 *  debug interface boot in a way that is chipset specific
 *  feature agnostic (NOCS generic expresssion).
 *
 *  If the debug interface mode specified as parameter is not supported, this
 *  function shall return CTD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  PS: See for other debug interface setting mode, please refer to nhtCtdSetPv() and
 *  nhtCtdSetOtp() functions (with PV Id = 'CTD_NOCS_PVID_DIF_ID'.
 *
 *  According to the CTD API purpose, all debug interface mode change requests shall
 *  be operated to the chipset OTP without any SW check.
 *
 *  If the PV programming was effectivelly executed, this
 *  function shall return CTD_NO_ERROR. This concern applies independently
 *  of the associated OTP well-programming
 *  (no embedded verification in the implementation of this function).
 *  PS: Well programming verification will explicitly and
 *  exclusivelly done by the the harness test framework.
*/
TCtdStatus nhtCtdSetDebugInterfaceMode
(
  TCtdDifMode xDifMode
);

/**
 *  @ingroup pv
 *
 *  @brief
 *    Get the current debug interface mode.
 *
 *  @param[out]     pxDifMode
 *                   Pointer to the location where the function has to write the
 *                   current debug Interface Mode.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              The passed parameter is invalid.
 *  @retval   CTD_ERROR_OPERATION_NO_SUPPORTED
 *              The operation is not supported by the driver implementation.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function allows the client software to read the configured
 *  debug interface mode from the PV.
 *
 *  This dedicated function allows the user application to get the
 *  debug interface mode that applies to a chipset in a way that is
 *  chipset specific feature agnostic (NOCS generic expresssion).
 *
 *  If an invalid parameter is provided at function call, this function
 *  shall return CTD_ERROR_INVALID_PARAMETERS.
 *
 *  If input parameters is valid but the feature is current not
 *  supported, this function shall return CTD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If no valid flash device identifier is currently programmed (or if the
 *  PV programmng is inconstitant), this function shallreturn CTD_ERROR.
 *
 *  PS: See for other debug interface getting mode, please refer to nhtCtdGetPv() and
 *  nhtCtdGetOtp() functions (with PV Id = 'CTD_NOCS_PVID_DIF_ID'.
 *
 */
TCtdStatus nhtCtdGetDebugInterfaceMode
(
  TCtdDifMode * pxDifMode
);


/**
 *  @ingroup pv
 *
 *  @brief
 *    Get the chipset specific logical PV value/mask size
 *    associated to a PV type ID.
 *
 *  @param[in]      xPvId
 *   Persistent Value type Identifier.
 *
 *  @param[in]      pxPvBufferSize
 *    Size in bytes of pxPvValue array.
 *
 *  @retval   CTD_NO_ERROR
 *    No error
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  This function allows the application to know what is the chipset specific
 *  logical PV buffer size associated to a PV type.
 *
 *  The size is always expressed in bytes. This byte-size shall always be
 *  large enough for holding the entire PV logical value.
*/
TCtdStatus nhtCtdGetPvBufferSize
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32 * pxPvBufferSize
);



/**
 *  @ingroup pv
 *
 *  @brief
 *    This function programs a PV logic value associated to a PV type.
 *
 *  @param[in]      xPvId
 *    Persistent Value type Identifier.
 *
 *  @param[in]      xPvBufferSize
 *    Size in bytes of OTP bit-field buffer value/mask.
 *
 *  @param[in]      pxPvBufferValue
 *    Array containing the OTP bit-field value to be written
 *
 *  @retval   CTD_NO_ERROR
 *    The OTP bit-field value programming was successfully executed.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  This function programs a PV logical value associated to a PV type Id.
 *
 *  Logic values associated to a particular PV type shall be part of a CM/Nagra
 *  agreement. This agreement might be NOCS generic or specific per chipset.
 *
 *  The user application is responsible to provide logical value buffer
 *  size that complies to the one expected by the chipset. To obtain the
 *  PV associated expected buffer value size, refer to nhtCtdGetPvBufferSize()
 *  function.
 *
 *  Reprogramming of a PV value shall effectivelly be done at HW level
 *  by programming/re-programming OTPs (wihtout any SW internal check).
 *  If the OTP programmation was effectivelly executed at HW
 *  level, this function shall return CTD_NO_ERROR. This concern applies
 *  independently of the associated OTP well-programming
 *  (no embedded verification in the implementation of this function).
 *  PS: well programming verification will explicitly and
 *  exclusivelly done by the the harness test framework.
*/
TCtdStatus nhtCtdSetPv
(
  TCtdPvId                  xPvId,
  TCtdUnsignedInt32         xPvBufferSize,
  const TCtdUnsignedInt8  * pxPvBufferValue
);

/**
 *  @ingroup pv
 *
 *  @brief
 *    This functions reads a PV logic value associated to a PV type.
 *
 *  @param[in]      xPvId
 *                   Persistent Value type Identification.
 *
 *  @param[in]      xPvBufferSize
 *    Size in bytes of the value buffer (data/mask)
 *
 *  @param[out]      pxPvBufferValue
 *    Array where to copy the OTP bit-field
 *
 *  @retval   CTD_NO_ERROR
 *    The PV value was successfully read.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *    One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The feature is currently not supported by the driver or HW.
 *
 *  @retval   CTD_ERROR
 *    Any other error
 *
 *  This function read the logical value associated a persistent PV type.
 *
 *  The user application is responsible to provide logical value buffer
 *  size that complies to the one expected by the chipset. To obtain the
 *  PV associated expected buffer value size, refer to nhtCtdGetPvBufferSize()
 *  function.
 *
 *  Logic values associated to a particular PV type shall be part of a CM/Nagra
 *  agreement. This agreement might be NOCS generic or specific per chipset.
 *
 *  If the associated PV programming is inconsistant, this function shall
 *  return CTD_ERROR.
 */
TCtdStatus nhtCtdGetPv
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvBufferSize,
  TCtdUnsignedInt8  * pxPvBufferValue
);


/******************************************************************************/
/*                                                                            */
/*                      OTP Interface                                         */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup phys_pv
 *
 *  @brief
 *    Get the chipset specific OTP bit-field value/mask size
 *    associated to a PV type ID.
 *
 *  @param[in]      xPvId
 *   Persistent Value type Identifier.
 *
 *  @param[in]      pxOtpBufferSize
 *    Size in bytes of pxPvValue array.
 *
 *  @retval   CTD_NO_ERROR
 *    No error
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  This function allows the application to know what is the chipset specific
 *  OTP bit-field buffer size associated to a PV type.
 *  The size is always expressed in bytes. This byte-size shall always be
 *  large enough for holding all PV logical values.
 *
 *  Non-applicable bits in this bit-field arrays are handle separately using
 *  bit mask [see nhtCtdGetOtpValueMask() function].
*/
TCtdStatus nhtCtdGetOtpBufferSize
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32 * pxOtpBufferSize
);


/**
 *  @ingroup phys_pv
 *
 *  @brief
 *    Get the the OTP bit-field mask associated to a specified PV ID.
 *
 *  @param[in]      xPvId
 *    Persistent Value type Identifier.
 *
 *  @param[in]      xOtpMaskSize
 *    Size in bytes of the the OTP bit-field mask.
 *
 *  @param[out]      pxOtpMask
 *    OTP bit-field mask array to be filled up.
 *
 *  @retval   CTD_NO_ERROR
 *    No error
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  Get the the OTP bit-field mask associated to a specified PV ID.
 *
 *  This is the responsiblity of the caller to pre-allocate enough room
 *  for holding the OTP bit-field mask that shall be filled.
 *  The buffer size to be pre-allocated by the user application can be
 *  obtained using the nhtCtdGetOtpBufferSize() function.
 *
 *  If returning CTD_NO_ERROR, implementation of this function shall setup the
 *  associated OTP bit-field mask value. Bits in pxOtpMask
 *  that are meaningful (= effectivelly representing an OTP bit) shall
 *  be expressed as a 1. Otherwize, such bits shall be set to 0.
*/
TCtdStatus nhtCtdGetOtpValueMask
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xOtpMaskSize,
  TCtdUnsignedInt8  * pxOtpMask
);


/**
 *  @ingroup phys_pv
 *
 *  @brief
 *    This function programs OTP associated to a PV type with an
 *    OTP bit-field specified value.
 *
 *  @param[in]      xPvId
 *    Persistent Value type Identifier.
 *
 *  @param[in]      xOtpBufferSize
 *    Size in bytes of the OTP bit-field buffer value/mask.
 *
 *  @param[in]      pxOtpBufferValue
 *    Array containing the OTP bit-field value to be written
 *
 *  @param[in]      pxOtpBufferMask
 *    Array containing the OTP bit-field mask to be written
 *
 *  @retval   CTD_NO_ERROR
 *    The OTP bit-field value programming was successfully executed.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The requested PV type operation is not supported by the chipset.
 *
 *  @retval   CTD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  This function programs OTP associated to a PV type with an OTP bit-field specified value
 *  (parameter: pxOtpBufferValue).
 *
 *  'pxOtpBufferMask' stands as an OTP bit-field mask indicating which bits of
 *  the pxOtpBufferValue buffer shall be considered at programming time.
 *  Only related bits set to 1 in the pxOtpBufferMask shall be
 *  considered at programming time.
 *
 *  A 'to-be-programmed' OTP bit which must programmed/fused is represented by a
 *  bit set to 1 in pxOtpBufferValue.
 *  A 'to-be-programmed' OTP bit for which an unprogramming/unfusing attempt is
 *  expected is represented by a bit to 0 in pxOtpBufferValue,
 *
 *  According to the NOCS specification, once programmed/fused, an OTP could not be unfused.
 *  However, since purpose of this function is to verify that
 *  this characteristic is effectivelly handled by HW, attempting to unprogram/unfuse
 *  an OTP bit shall effectivelly be done at HW level (wihtout any SW internal check)
 *  if possible by the technology.
 *
 *  If the OTP associated programming was effectivelly executed at HW
 *  level, this function shall return CTD_NO_ERROR. This concern applies
 *  independently of the associated OTP well-programming
 *  (no embedded verification in the implementation of this function).
 *  PS: OTP well programming verification will explicitly and
 *  exclusivelly done by the the harness test framework.
*/
TCtdStatus nhtCtdSetOtp
(
  TCtdPvId                  xPvId,
  TCtdUnsignedInt32         xOtpBufferSize,
  const TCtdUnsignedInt8  * pxOtpBufferValue,
  const TCtdUnsignedInt8  * pxOtpBufferMask
);

/**
 *  @ingroup phys_pv
 *
 *  @brief
 *    This functions reads the OTP bit-field associated to a PV type.
 *
 *  @param[in]      xPvId
 *                   Persistent Value type Identification.
 *
 *  @param[in]      xOtpBufferSize
 *    Size in bytes of the OTP bit-field buffer (data/mask)
 *
 *  @param[out]      pxOtpBufferValue
 *    Array where to copy the OTP bit-field
 *
 *  @retval   CTD_NO_ERROR
 *    The OTP bit-field value was successfully read.
 *
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *    One or several parameter are invalid.
 *
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *    The feature is currently not supported by the driver or HW.
 *
 *  @retval   CTD_ERROR
 *    Any other error
 *
 *  This function reads the OTP bit-field value associated a persistent PV type.
 *
 *  An OTP bit which is programmed/fused is always represented by bit set to 1.
 *  An OTP bit wich is not-programmed/unfused is always represented by bit set to 0.
 *
 *  PS: Bits that are meaningfull in pxOtpBufferValue for a PV type can
 *  be obtain using the nhtCtdGetOtpValueMask() function.
 *
 *  In any case, reading an OTP bit-field shall keep OTPs unchanged.
 */
TCtdStatus nhtCtdGetOtp
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xOtpBufferSize,
  TCtdUnsignedInt8  * pxOtpBufferValue
);



/******************************************************************************/
/*                                                                            */
/*                       R2R cipher                                           */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup r2r
 *
 *  @brief
 *    Pointer to an opaque structure to be defined by the entity in charge of
 *    developing the CTD API and used as a handle for block cipher encryption
 *    and decryption sessions.
*/
typedef void * TCtdR2RSession;

/**
 *  @ingroup r2r
 *
 *  @brief
 *    This function opens a R2R encryption session and returns a session
 *    handle that will be used by other functions to set keys and encrypt data.
 *
 *    It is possible to change the encryption key and/or the encryption
 *    algorithm (EMI) during the same session. The protection of the encryption
 *    key (clear-text, key ladder) may also change during a session.
 *
 *  @param[out]  pxSession
 *    Session handle assigned by this function
 *  @retval  CTD_NO_ERROR
 *    The operation was completed successfully.
 *  @retval  CTD_ERROR_INVALID_PARAMETER
 *    This status is returned if pxSession is NULL.
 *  @retval  CTD_ERROR_UNSUPPORTED_OPERATION
 *    The session does not support this EMI.
 *  @retval  CTD_ERROR
 *    Any other errors
*/
TCtdStatus nhtCtdOpenR2rEncryptSession
(
  TCtdR2RSession * pxSession
);


/**
 *  @ingroup r2r
 *
 *  @brief
 *    This function opens a R2R decryption session and returns a session
 *    handle that will be used by other functions to set keys and decrypt data.
 *
 *    It is possible to change the decryption key and/or the decryption
 *    algorithm (EMI) during the same session. The protection of the decryption
 *    key (clear-text, key ladder, CERT) may also change during a session.
 *
 *  @param[out]  pxSession
 *    Session handle assigned by this function
 *
 *  @retval  CTD_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  CTD_ERROR_INVALID_PARAMETERS
 *    This status is returned if pxSession is NULL.
 *
 *  @retval  CTD_ERROR
 *    Any other errors
*/
TCtdStatus nhtCtdOpenR2rDecryptSession
(
  TCtdR2RSession * pxSession
);


/**
 *  @ingroup r2r
 *
 *  @brief
 *    This function closes an encryption or decryption session.
 *
 *  @param[in]  xSession
 *    Handle of the session to be closed
 *
 *  @retval  CTD_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  CTD_ERROR_INVALID_PARAMETERS
 *    An invalid session handle was provided.
 *
 *  @retval  CTD_ERROR
 *    Any other errors
*/
TCtdStatus nhtCtdCloseR2rSession
(
  TCtdR2RSession  xSession
);


/**
 *  @ingroup r2r
 *
 *  @brief
 *    This function sets protected keys required by the key ladder
 *    associated to a R2R encryption or decryption ciphering operations.
 *
 *  @param[in]  xSession
 *    Session handle
 *
 *  @param[in]  xKeyEmi
 *    Emi that identifies the key type associated to a key ladder.
 *
 *  @param[in]  xCipheredContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes. The keying option is signaled in
 *      the EMI. However, today only keying option 2 (K1=K3) is supported.
 *    - AES: 16 bytes
 *
 *  @param[in]  pxCipheredContentKey
 *    Buffer, allocated by the caller, containing the ciphered content key. It
 *    is equal to CipheredContentKey=TDES(ContentKey, L1ProtKey).
 *
 *  @param[in]  xCipheredProtectingKeySize
 *    Size in bytes of the intermediate level protecting keys used within the
 *    key ladder. It is always equal to 16 bytes for NOCS chipset.
 *
 *  @param[in]  pxL1CipheredProtectingKey
 *    Buffer, allocated by the caller, containing the first ciphered protecting
 *    key fed into the key ladder. It is equal to
 *    L1CipheredProtKey=TDES(L1ProtKey, L2ProtKey).
 *
 *  @param[in]  pxL2CipheredProtectingKey
 *    Buffer, allocated by the caller, containing the second ciphered protecting
 *    key fed into the key ladder. It is equal to
 *    L2CipheredProtKey=TDES(L2ProtKey, R2rRootKey) where R2rRootKey is the
 *    R2R crypto engine root key.
 *
 *  @retval  CTD_NO_ERROR
 *    The operation was completed successfully.
 *  @retval  CTD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL key pointers
 *    - Size of content key does not match the crypto algorithm defined by the EMI
 *    - Unsupported protecting key size
 *  @retval  CTD_ERROR_NOT_SUPPORTED
 *    The EMI given as input parameter is not supported.
 *  @retval  CTD_ERROR
 *    Any other errors
 *
 *  The type of operation (encryption or decryption) is defined at session
 *  opening. See nhtCtdOpenR2rEncryptSession() or nhtCtdOpenR2rDecryptSession()
 *  functions for more information.
 *
 *  The EMI provided as input parameter identifies the keyring type that
 *  shall applies. It differs from the EMI provided in R2R encryption/decryption
 *  functions which described R2R algorithm and cryptographic mode.
 *
 *  @remarks
 *    This function may be called at any time during a given session to change
 *    the EMI associated keyring.
*/
TCtdStatus nhtCtdSetR2RProtectedKeys
(
  TCtdR2RSession           xSession,
  TCtdUnsignedInt16        xKeyEmi,
  TCtdSize                 xCipheredContentKeySize,
  const TCtdUnsignedInt8 * pxCipheredContentKey,
  TCtdSize                 xCipheredProtectingKeySize,
  const TCtdUnsignedInt8 * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8 * pxL2CipheredProtectingKey
);

/**
 *  @ingroup r2r
 *
 *  @brief
 *    This function performs a R2R data encryption or encryption according
 *    to a R2R session.
 *
 *  @pre
 *    nhtCtdSetR2RProtectedKeys() must have been called
 *    before calling this function.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES) and block
 *    cipher modes (ECB, CBC, CTR) to be used by the R2R crypto engine.
 *  @param[in]  pxInput
 *    Buffer containing the input message to be encrypted/decrypted. It is allocated by
 *    the caller.
 *  @param[out]  pxOutput
 *    Buffer where to write the encrypted message. It is allocated by
 *    the caller.
 *  @param[in]  xMessageSize
 *    Size in bytes of messages (pxInput, pxOutput) to operate on. It does not
 *    need to be a multiple of the cipher block size.
 *  @param[in] pxInitVector
 *    Buffer allocated by the caller containing the initialization vector (IV)
 *    required by CBC and CTR modes. These cipher modes of operation are part of
 *    the EMI definition. If no IV is required (ECB mode), pxInitVector is set
 *    to NULL.\n
 *    Normally the CTR mode requires a nonce and a counter that are then
 *    combined to produce the actual counter block encryption/decryption. In the current
 *    API the caller is in charge of providing the initial counter block instead
 *    of a nonce and a counter. This initial counter block is passed within
 *    pxInitVector buffer. The function TSecSessionEncrypt() is then in charge of
 *    incrementing the counter block of one unit for each block encryption.
 *  @param[in] xInitVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitVectorSize is set to zero.
 *
 *  @retval  CTD_NO_ERROR
 *    The operation was completed successfully.
 *  @retval  CTD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL input/output buffers
 *    - Unsupported IV size
 *  @retval  CTD_ERROR
 *    Any other errors
 *
 *    This function encrypts or decrypt the data contained in pxInput buffer and stores the
 *    encrypted data result in pxOutput buffer. It is assumed that the encryption
 *    content key has already been set by calling nhtCtdSetR2RProtectedKeys().
 *
 *    PS: Encryption or decryption operating mode is defined at R2R session opening.
 *
 *    The EMI provided as input parameter identifies the cryptographic
 *    algorithm and chaining mode. It differs from the one specified
 *    in nhtCtdSetR2RProtectedKeys() which identifies a Keyring type. This distinction
 *    in this API is intended to test the keyring usage protection during CTD
 *    harness certification and test.
 *
 *    This function may be called several times during the life-time of a given session
 *    in order to encrypt a message split in several chunks. If the block cipher modes of
 *    operation requests an initialization vector (IV), the caller is responsible
 *    to at least initialize the very first IV that applies to the first chunk of the
 *    session.
 *
 *    The size of message to be encrypted/decrypted does not need to be a multiple of the
 *    cipher block size. In such a case, the n residual bytes (with
 *    n = xMessageSize mod cipher block size) are left in the clear and simply
 *    copied from input to output buffer provided the mode of operation is ECB
 *    or CBC. For CTR mode, encryption actually consists in a simple XOR, thus
 *    residual bytes are encrypted as any other bytes of the message.
 *
 *    This function does not manage any padding. If a padding schema is required,
 *    the caller is in charge of applying it to the input message before calling
 *    this function.
 *
*/
TCtdStatus nhtCtdR2rSessionCryptoProcess
(
  TCtdR2RSession           xSession,
  TCtdUnsignedInt16        xEmi,
  const TCtdUnsignedInt8 * pxInput,
  TCtdUnsignedInt8       * pxOutput,
  TCtdSize                 xMessageSize,
  const TCtdUnsignedInt8 * pxInitVector,
  TCtdSize                 xInitVectorSize
);


/******************************************************************************/
/*                                                                            */
/*                                    DSC                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup dsc
 *
 *  @brief
 *    DCR test run session handle
*/
typedef void * TCtdDscTestRunSession;

/**
 *  @ingroup dsc
 *
 *  @brief
 *    DCR ECM call back private data opaque descritor type
*/
typedef void * TCtdDscCallBackPrivateParameters;


/**
 *  @ingroup dsc
 *
 *  @brief
 *    ECM call back function type.
 *
 *    Implementation of the DSC test is responsible to call it
 *    each time there is a new MPEG ECM tableId associated to an ECM PID found
 *    in the input stream.
*/
typedef TCtdStatus (*TNhtCtdDscEcmCallBack)
(
  TCtdDscTestRunSession               xDscTestRunSession,
    /**<  test run session identifier. */
  TCtdDscCallBackPrivateParameters   xPrivateParameters,
    /**<  ECM callback private data (as given at DSC test run opening time) */
  TCtdUnsignedInt8                      xEcmTableId,
    /**<  ECM MPEG Table ID) */
  const TCtdUnsignedInt8              * pxEcmContent,
    /**<  ECM MPEG packet buffer */
  TCtdSize                              xEcmContentSize
    /**<  ECM MPEG packet buffer size */
);


/**
 *  @ingroup dsc
 *
 *  @brief
 *    DSC harness test run input parameter structure type
*/
typedef struct SCtdDscTestRunParameters
{
  TCtdUnsignedInt16  engineEmi;
  /**<  EMI of the descrambler engine */

  int audioPid;
  /**<  Audio PID */

  int videoPid;
  /**<  Video PID */

  int pcrPid;
  /**<  PCR PID */

  TCtdBoolean  isInClear;
  /**<  Specify if the test run shall use encryption mode */

  TCtdBoolean  isForEncryption;
  /**<  Specify if the test run is for an encryption */

  int ecmPid;
  /**<  ECM PID (if ECM usage is required) */

  const char * pInputFilePathname;
  /**<  Stream Input file pathname or NULL if stream shall be taken from the front-head. */

  const char * pOutputFilePathname;
  /**<  Stream Output file pathname or NULL if no recording is required.
   *    (In all cases, stream shall be at least be provided into the
   *    back-end (video/audio output) */

  TCtdUnsignedInt8 * pIv;
  /**< Initial value (IV)  of the crypto algorithm if applicable according to
   *  the EMI identifier. */

  TCtdSize  ivSize;
  /**< Size of the initial value (IV) of the crypto algorithm if applicable according to
   *  the EMI identifier. */

  TNhtCtdDscEcmCallBack ecmCallBackFct;
  /**< ECM call back function to be called each time a new MPEG ECM tableId is found
   * in the input stream */

  TCtdDscCallBackPrivateParameters ecmCallBackPrivateData;
  /**< ECM call back function private data (opaque handler).
   * Implementation of this API is responsible to provide it at each call back to
   * the 'ecm call back function) if any. */

} TCtdDscTestRunParameters;


/*!
 *  @ingroup dsc
 *
 *  @brief
 *    Open a DSC test run session
 *
 *  @param[in]  pxDscTestRunParameters
 *    DSC test run input parameters
 *
 *  @param[out]  pxDscTestRunSession
 *    DSC test run handle
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function initializes a DSC test run session and return an
 *  associated DSC test run opaque handle.
 *
 *  The input parameter 'pxDscTestRunParameter' contains information
 *  associated to the test run instance to be initialized.
 *  Information provided in this input parameter stands as invariant data
 *  of the test run session. These ones are all fixed at test run initialization
 *  and cannot be modified during the DSC test run session life-duration.
 *
 *  Note that the engineEmi field in the 'TCtdDscTestRunParameters' structure
 *  refers to EMI identifying the crypto engine, not the applicable keyring selection.
 *  Applicable keyring selection is fixed using the nhtCtdSetDscProtectedKeys() function.
 *
 *  Based on the invariant data passed as input parameter, this function is
 *  responsible to verify if the requested test run is supported by the
 *  chipset platform. If not, this function shall return
 *  NHT_CTD_TEST_ERROR_TEST_NOT_SUPPORTED.
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
 *  return NHT_CTD_TEST_ERROR_SERVICE_CURRENTLY_IN_USED.
 *
 *  If some input parameters are invalid, this function shall return
 *  NHT_CTD_TEST_ERROR_INVALID_PARAMETERS.
 *
 *  If initialization succeeds, this function shall return
 *  NHT_CTD_TEST_NO_ERROR and shall provide an associated test run handle.\n
 *  In this case, usage of the chipset resources associated to this
 *  test run shall be granted by the platform until the end-of-life of
 *  this test run session of abortion of the harness test process
 *  (see also function '()').
 *
 *  After intialization of such a test run, harness test application are
 *  free to preset key values or to directly start the test run.
*/
TCtdStatus nhtCtdOpenDscTestRunSession
(
  TCtdDscTestRunParameters * pxDscTestRunParameters,
  TCtdDscTestRunSession    * pxDscTestRunSession
);


/*!
 *  @ingroup dsc
 *
 *  @brief
 *    Asynchronously start a DSC test run associated to a DSC session.
 *
 *  @param[in,out]  xDscTestRunSession
 *    DSC test run handle
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally. The intended operation failed.
 *
 *  This function starts the DSC scrambling/descrambling concurrent test run
 *  associated to a DSC session.
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
 *  NHT_CTD_TEST_ERROR_INVALID_PARAMETERS.
 *
 *  If the requested test run fails to start for other reasons, this function
 *  shall return NHT_CTD_TEST_ERROR.
 *
 *  PS: The harness test application implementation of the ECM callback function
 *  (if any) is granted to be non-blocking.\n
 *  Please note that depending of the harness test, key settings associated to
 *  an ECM may be done asynchronously to the execution of this call back
 *  function (e.g: if ECM need to be decrypted prior to be able to set the
 *  associated CWs)
*/
TNhtCtdTestRunStatus nhtCtdStartDscTestRun
(
  TCtdDscTestRunSession xDscTestRunSession
);


/*!
 *  @ingroup dsc
 *
 *  @brief
 *    Wait on completion of a DSC test run associated to a DSC session.
 *
 *  @param[in,out]  xDscTestRunSession
 *    DSC test run handle
 *
 *  @param[in]  xTimeout
 *    Timeout
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
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
 *  NHT_CTD_TEST_ERROR_WOULD_BLOCK.
 *
 *  At normal or abnormal completion of the service run, any pending call to
 *  this function shall immediately return.\n
 *  If the test run successfully terminated, this function shall immediately
 *  return NHT_CTD_TEST_NO_ERROR.\n
 *  Otherwize, it shall return NHT_CTD_TEST_ERROR_SERVICE_RUN_FAILER.
*/

TNhtCtdTestRunStatus nhtCtdWaitOnDscTestRunCompletion
(
  TCtdDscTestRunSession xDscTestRunSession,
  int                  xTimeout
);


/*!
 *  @ingroup dsc
 *
 *  @brief
 *    Stop of a DSC test run associated to a DSC session.
 *
 *  @param[in,out] xDscTestRunSession
 *    DSC test run handle
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function immediately stops a DS test run identified by
 *  its DSC test run handle (if not already terminated).
 *
 *  If the test run already abnormally terminated before calling
 *  this function, this function shall return NHT_CTD_TEST_ERROR_SERVICE_RUN_FAILER.
 *  Otherwize, it shall return NHT_CTD_TEST_NO_ERROR.
 *
 *  The implementation of this function shall grant that no more ECM callback
 *  will be done after returning from this function.
*/
TNhtCtdTestRunStatus nhtCtdStopDscTestRun
(
  TCtdDscTestRunSession   xDscTestRunSession
);

/**
 *  @ingroup dsc
 *
 *  @brief
 *    Set the protected content key associated to a CTD test run session.
 *
 *  @param[in,out]  xDscTestRunSession
 *    DSC test run handle.
 *
 *  @param[in]  xKeyEmi
 *    Emi that identifies the key type associated to a key ladder.
 *
 *  @param[in]  xCipheredProtectingKeySize
 *    Size in bytes of the intermediate level protecting keys used within the
 *    key ladder. It is always equal to 16 bytes for NOCS chipset.
 *
 *  @param[in]  pxL1CipheredProtectingKey
 *    Buffer, allocated by the caller, containing the first ciphered protecting
 *    key fed into the key ladder. It is equal to
 *    L1CipheredProtKey=TDES(L1ProtKey, L2ProtKey).
 *
 *  @param[in]  pxL2CipheredProtectingKey
 *    Buffer, allocated by the caller, containing the second ciphered protecting
 *    key fed into the key ladder. It is equal to
 *    L2CipheredProtKey=TDES(L2ProtKey, R2rRootKey) where R2rRootKey is the
 *    R2R crypto engine root key.
 *
 *  @param[in]      pxCipheredDscOddContentKey
 *    Pointer to the location where the function has to
 *    read the Ciphered DSC Odd Contentkey.
 *
 *  @param[in]      xCipheredDscOddContentKeySize
 *    Size in bytes of the Ciphered DSC Odd Contentkey.
 *
 *  @param[in]      pxCipheredDscEvenContentKey
 *    Pointer to the location where the function has to
 *    read the Ciphered DSC Even Contentkey.
 *
 *  @param[in]      xCipheredDscEvenContentKeySize
 *    Size in bytes of the Ciphered DSC Even Contentkey.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function configures the key ladder keyring with the Ciphered Protecting
 *  Keys and set the CWs provided in protected form into the specified key
 *  ladders involved in the Video and Audio stream descrambling.
 *
 *  All keys are expressed as MSBF byte array.
 *
 *  PS: for NOCS3.x, both L1 and L2 protecting keys shall be provided
 *  since 3-level key ladders are required. On NOCS1.x, L2 might be
 *  unrelevant when 2-level key ladders are involved on chipset. In this
 *  case, pxL2CipheredProtectingKey could be passed as NULL.
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
 *        CTD_ERROR_INVALID_PARAMETERS.
 *
 *  The implementation is responsible to ensure that this function can be
 *  called at any moment during a test run life duration (including before
 *  starting the test run).
*/

TCtdStatus nhtCtdSetDscProtectedKeys
(
        TCtdDscTestRunSession   xDscTestRunSession,
        TCtdUnsignedInt16       xKeyEmi,
        TCtdSize                xCipheredProtectingKeySize,
  const TCtdUnsignedInt8      * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8      * pxL2CipheredProtectingKey,
  const TCtdUnsignedInt8      * pxCipheredDscOddContentKey,
        TCtdSize                xCipheredDscOddContentKeySize,
  const TCtdUnsignedInt8      * pxCipheredDscEvenContentKey,
        TCtdSize                xCipheredDscEvenContentKeySize
);


/*!
 *  @ingroup dsc
 *
 *  @brief
 *    Close a DSC test run session identified by its handle.
 *
 *  @param[in,out]  xDscTestRunSession
 *                   DSC test run handle to terminate.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
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
*/
TCtdStatus nhtCtdCloseDscTestRunSession
(
  TCtdDscTestRunSession  xDscTestRunSession
);

/***************************************************************************/
/*                                                                         */
/*                                    SCR                                  */
/*                                                                         */
/***************************************************************************/

/**
 *  @ingroup scr
 *
 *  @brief
 *    SCR harness test run input parameter structure type
*/
typedef struct SNhtCtdScrTestRunParameters
{
  TCtdUnsignedInt16  engineEmi;
  /**<  EMI of the descrambler engine */
  int                audioPid;
  /**<  Audio PID */
  int                videoPid;
  /**<  Video PID */
  int                pcrPid;
  /**<  PCR PID */
  const char * pInputFilePathname;
  /**<  Stream Input file pathname or NULL if stream shall be taken from
   *   the front-head. */
  TCtdBoolean        isForEncryption;
  /**<  Specify if the test run shall use encryption mode */
  const char * pOutputFilePathname;
  /**<  Stream Output file pathname or NULL if no recording is required.
   *    (In all cases, stream shall be at least be provided into the
   *    back-end (video/audio output) */
  /**<  ECM usage identifier */
} TNhtCtdScrTestRunParameters;


/**
 *  @ingroup scr
 *
 *  @brief
 *    SCR test run session handle
*/
typedef void * TNhtCtdScrTestRunSession;


/*!
 *  @ingroup scr
 *
 *  @brief
 *    Open a SCR test run session.
 *
 *  @param[in]  pxScrTestRunParameters
 *    SCR test run parameters
 *
 *  @param[out]  pxScrTestRunSession
 *    SCR test run handle
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
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
 *  Note that the engineEmi field in the 'TNhtCtdScrTestRunParameters' structure
 *  refers to EMI identifying the crypto engine, not the applicable keyring selection.
 *  Applicable keyring selection is fixed using the nhtCtdSetScrProtectedKeys() function.
 *
 *  Based on the invariant data passed as parameter, this function is
 *  responsible to verify if the requested test run is supported by the
 *  chipset. If not, this function shall return NHT_CTD_TEST_ERROR_TEST_NOT_SUPPORTED..
 *
 *  If this is a supported test run but the chipset resources are current
 *  not available because in use by other test runs, this function shall
 *  return NHT_CTD_TEST_ERROR_SERVICE_CURRENTLY_IN_USED.
 *
 *  If some input parameters are invalid, this function shall return
 *  NHT_CTD_TEST_ERROR_INVALID_PARAMETERS.
 *
 *  If opening succeeds, this function shall return
 *  NHT_CTD_TEST_NO_ERROR and shall provide an associated test run handle.\n
 *  In this case, usage of the chipset resources associated to this
 *  test run shall be granted by the platform until the test run
 *  session is closed.
 *
 *  After opening of such a test run session, harness test application are
 *  free to preset key values or to directly start the test run.
*/

TCtdStatus nhtCtdOpenScrTestRunSession
(
  const TNhtCtdScrTestRunParameters * pxScrTestRunParameters,
  TNhtCtdScrTestRunSession          * pxScrTestRunSession
);


/*!
 *  @ingroup scr
 *
 *  @brief
 *    Asynchronously start a SCR test run identified by its handle.
 *
 *  @param[in,out]  xScrTestRunSession
 *    SCR session handle
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
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
*/

TNhtCtdTestRunStatus nhtCtdStartScrTestRun
(
  TNhtCtdScrTestRunSession xScrTestRunSession
);


/*!
 *  @ingroup scr
 *
 *  @brief
 *    Wait on completion of a SCR test run identified by its handle.
 *
 *  @param[in,out] xScrTestRunSession
 *    SCR test run handle
 *
 *  @param[in]  xTimeout
 *    Timeout
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
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
 *  this function shall return NHT_CTD_TEST_ERROR_WOULD_BLOCK.
 *
 *  At normal or abnormal completion of the test run, any pending calls to
 *  this function shall immediately return.\n
 *  If the test run successfully terminated, this function shall immediately
 *  return NHT_CTD_TEST_NO_ERROR.\n
 *  Otherwize, it shall return NHT_CTD_TEST_ERROR_SERVICE_RUN_FAILER.
*/

TNhtCtdTestRunStatus nhtCtdWaitOnScrTestRunCompletion
(
  TNhtCtdScrTestRunSession xScrTestRunSession,
  int                      xTimeout
);


/*!
 *  @ingroup scr
 *
 *  @brief
 *    Stop a SCR test run identified by its handle.
 *
 *  @param[in,out] xScrTestRunSession
 *    SCR test run handle.
 *
 *  @retval   NHT_CTD_TEST_NO_ERROR
 *              The SCR test run successfully started.
 *  @retval   NHT_CTD_TEST_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   NHT_CTD_TEST_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function immediately stops a SCR test run identified by
 *  its SCR test run handle if not already stopped.
 *
 *  If the test run already abnormally stopped, this function shall return
 *  NHT_CTD_TEST_ERROR_SERVICE_RUN_FAILER.
 *
 *  Otherwize, it shall return NHT_CTD_TEST_NO_ERROR.
*/
TNhtCtdTestRunStatus nhtCtdStopScrTestRun
(
  TNhtCtdScrTestRunSession  xScrTestRunSession
);


/** @ingroup scr
 *
 *  @brief
 *    Set the Content key associated to a SCR test run session.
 *
 *  @param[in,out] xScrTestRunSession
 *    SCR session handle
 *
 *  @param[in]  xKeyEmi
 *    Emi that identifies the key type associated to a key ladder.
 *
 *  @param[in]  xCipheredProtectingKeySize
 *    Size in bytes of the intermediate level protecting keys used within the
 *    key ladder. It is always equal to 16 bytes for NOCS chipset.
 *
 *  @param[in]  pxL1CipheredProtectingKey
 *    Buffer, allocated by the caller, containing the first ciphered protecting
 *    key fed into the key ladder. It is equal to
 *    L1CipheredProtKey=TDES(L1ProtKey, L2ProtKey).
 *
 *  @param[in]  pxL2CipheredProtectingKey
 *    Buffer, allocated by the caller, containing the second ciphered protecting
 *    key fed into the key ladder. It is equal to
 *    L2CipheredProtKey=TDES(L2ProtKey, R2rRootKey) where R2rRootKey is the
 *    R2R crypto engine root key.
 *
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
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function configures the key ladder keyring associated to a SCR test run
 *  session with the Ciphered Protecting Keys and set the CWs provided in protected
 *  form.
 *
 *  All keys are expressed as MSBF byte array.
 *
 *  PS: for NOCS3.x, both L1 and L2 protecting keys shall be provided
 *  since 3-level key ladders are required. On NOCS1.x, L2 might be
 *  unrelevant when 2-level key ladders are involved on chipset. In this
 *  case, pxL2CipheredProtectingKey could be passed as NULL.
 *
 *  The size of these keys shall be:
 *      - 0 if the CW is not available.
 *      - 8 if the cryptographic algorithm is requesting 8 bytes.
 *      - 16 if the cryptographic algorithm  is requesting 16 bytes.
 *      - In all other cases, the function shall return
 *        CTD_ERROR_INVALID_PARAMETERS.
 *
 *  If the xEmi set for this test run refers to a chaining mode,
 *  pxInitializationVector is used to pass the Initialization Vector
 *  to the Stream Crypto Engine(s) associated to this test run.
 *
 *  The size of this vector depends on the cryptographic algorithm
 *  (exemple: 16 bytes  for AES and 8 bytes for TDES).\n
 *  In all other cases, the function shall return CTD_ERROR_INVALID_PARAMETERS.
 */
TCtdStatus nhtCtdSetScrProtectedKeys
(
        TNhtCtdScrTestRunSession   xScrTestRunSession,
        TCtdUnsignedInt16          xKeyEmi,
        TCtdSize                   xCipheredProtectingKeySize,
  const TCtdUnsignedInt8         * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8         * pxL2CipheredProtectingKey,
  const TCtdUnsignedInt8         * pxCipheredScrContentKey,
        TCtdSize                   xCipheredScrContentKeySize,
  const TCtdUnsignedInt8         * pxInitializationVector,
        TCtdSize                   xInitializationVectorSize
);


/**
 *  @ingroup scr
 *
 *  @brief
 *    Close a SCR test run session
 *
 *  @param[in,out]  xScrTestRunSession
 *                   SCR test run session handle.
 *
 *  @retval   CTD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CTD_ERROR_INVALID_PARAMETERS
 *              At least one of the passed parameters is invalid.
 *  @retval   CTD_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function closes a SCR test run session that was previously opened
 *  using the 'nhtCtdOpenScrTestRunSession()' function.
 *
 *  This function is intended to let chipset manufacturer implementation to
 *  properly release the associated resources it reserved (specific
 *  chipset manufacturer concern) for this test run.
*/
TCtdStatus nhtCtdCloseScrTestRunSession
(
  TNhtCtdScrTestRunSession xScrTestRunSession
);


#ifdef __cplusplus
}
#endif

#endif /* _CTD_NOCS_API_H_ */
