/**
**  @file ca_cert.h
**
**  @brief
**   CERT.
**
**   This file specifies the CERT API that allows Nagra CA
**   software to access the Nagra CERT block.
**
**  $Id: //CAK/components/certapi/MAIN/src/ca_cert.h#3 $
**  $Change: 142580 $
**
*/
/*
** REMARK:
**   Comments in this file use special tags to allow automatic API documentation
**   generation in HTML format, using the GNU-General Public Licensed Doxygen
**   tool. For more information about Doxygen, please check www.doxygen.org
**
**   Depending on the platform, the CHM file may not open properly if it is
**   stored on a network drive. So either the file should be moved on a local
**   drive or add the following registry entry on Windows platform (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/



#ifndef CA_CERT_H
#define CA_CERT_H

/**
 * Defines the version number of the CERT API to be implemented. This version
 * has to be included in the function table returned by certGetFunctionTable().
 * To do so, use the macro CERTAPI_VERSION_INT to put it in the right format.
*/
#define CERTAPI_VERSION_MAJOR  1
#define CERTAPI_VERSION_MEDIUM 3
#define CERTAPI_VERSION_MINOR  0

/** @page p_history Changes history
 *  - <b> 1.3.0 - 28-Sep-2012 </b>
 *    - Deprecated TCertUseEncryptionKey() and TCertUseDecryptionKey() and
 *      related types. These functions are now replaced by SEC API
 *      TSecUseCertKey().
 *
 *  - <b> 1.2.1 - 08-May-2012 </b>
 *    - Modified the overiew to require a bare implementation of the CERT API
 *      in addition to the OS-based implementation.
 *    - Added RAM2RAM use case
 *
 *  - <b> 1.1.0 - 25-Jan-2012 </b>
 *    - Added global overview
 *    - Added clarifications about mutual exclusion related to the sharing of
 *      the CERT resource
 *
 *  - <b> 1.0.3 - 03-Aug-2011 </b>
 *    - Defined API reference in HTML and moved it in a separate file
 *    - Updated software stack context diagram
 *
 *  - <b> 1.0.2 - 31-Jun-2011 </b>
 *    - First official issue
*/

/******************************************************************************/
/*                                                                            */
/*                           GENERAL INCLUDE FILES                            */
/*                                                                            */
/******************************************************************************/

#include <stddef.h>


/******************************************************************************/
/*                                                                            */
/*                             OVERALL DOCUMENTATION                          */
/*                                                                            */
/******************************************************************************/

/** @mainpage Overview
 *  - @subpage p_history
 *  - @subpage p_preface
 *  - @subpage p_conventions
 *  - @subpage p_sw_stack
 *  - @subpage p_fct_table
 *  - @subpage p_cert_lock
 *  - @subpage p_cert_cmd
 *  - @subpage p_use_cases
 *
 *  <hr>Copyright &copy; 2011 Nagravision. All rights reserved.\n
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
 *  <h2>Objectives</h2>
 *
 *  This document specifies the API that gives access the Nagravision NOCS 3.0
 *  proprietary IP block, called Concurrent Embedded Root of Trust (CERT).
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for developers in charge of implementing the CERT
 *  API and as well as developers that intend to use the CERT API in their
 *  application.
 *
 * <hr><h2>References</h2>
 *  - [NSR] Nagravision, NOCS 3.0 IP Block (CERT), Nagra Specific Request (NSR)
 *
 */

/** @page p_conventions Used conventions
 *  <h2>Bit indexing</h2>
 *  Bits inside one byte B are numbered from 7 (most significant bit) down to 0
 *  (least significant bit).
 *  @image html bit_index.png
 *  @image rtf bit_index.png
 *
 *  Accordingly, bits inside a N-bit string are numbered from N-1 (most
 *  significant bit) down to 0 (least significant bit). Where explicit bit
 *  indexing is needed, the bit range is indicated between square brackets, with
 *  MS index first, then a colon, and the LS index last. For instance the three
 *  least significant bits of byte B are written as B[2:0].
 *
 *  <hr><h2>Byte indexing</h2>
 *  Bits inside one byte B are numbered from 7 (most significant bit) down to 0
 *  (least significant bit).
 *  @image html byte_index.png
 *  @image rtf byte_index.png
 *
 *  Bytes inside a N-byte string VAL are numbered from 0 (most significant byte)
 *  to N-1 (least significant byte). This corresponds to a big-endian notation
 *  ordering.
 *
 *  Where explicit byte indexing is needed, the byte range is indicated between
 *  square brackets, with most significant index first, then a colon, and the
 *  least significant index last. For instance the four most significant bytes
 *  of VAL are written as VAL[0:3].
 *
 *  \note
 *  A N-byte string can also be viewed as a 8*N-bit string. In this case, bit
 *  indexing is used (e.g. the least significant byte will contain bits from 7
 *  down to 0, while the most significant byte will contain bits from 8*(N-1)+7
 *  down to 8*(N-1). In general, if we need to convert from a N-byte string to a
 *  8*N-bit string, then byte at index p will contain bits at indexes
 *  8*(N-1-p)+7 down to 8*(N-1-p). When not clear from the context, explicit
 *  disambiguation is needed to distinguish between byte-indexing and bit
 *  indexing of a value.
*/

/** @page p_sw_stack Software stack context
 *
 *  <b>Two implementations of the CERT API are required</b>: one in a bare
 *  environment, before the operating system is available and another one based
 *  on the operating system. The following sections highlight the CERT driver
 *  within this two contexts.
 *
 *  The SoC vendor is in charge of providing a reference implementation of the
 *  CERT driver for these two cases, although the final implementation remains
 *  under the responsibility of the STB manufacturer.
 *
 *  <hr>@section s_sw_stack_os OS-based software stack context
 *  @image html cert_software_stack_os.png
 *  @image rtf cert_software_stack_os.png
 *
 *  In this context the CERT API is used directly by CA applications (CAK,
 *  DVL,...) to lock/unlock the CERT block resource and send commands to it.
 *  Keys processed by the CERT block are then handled through the SEC API.
 *
 *  <hr>@section s_sw_stack_bare Bare software stack context
 *  @image html cert_software_stack_bare.png
 *  @image rtf cert_software_stack_bare.png
 *
 *  In this context, the CERT API is used directly by Nagra Security Services to
 *  send commands to the CERT block resource. Keys processed by the CERT block
 *  are then handled through the BSD API.
 *
 *  The bare CERT driver does not need to cope with thread safety and mutual
 *  exclusion. However, a "dummy" implementation of TCertLock() and
 *  TCertUnlock() must be provided in order to return the handle parameter
 *  required by TCertExchange().
 */

/** @page p_fct_table Function table
 *
 *  Functions of the CERT API are exposed to applications through a table of
 *  callback functions retrieved through a call to certGetFunctionTable().
 *
 *  The table also contains the version number of the implemented CERT API. It
 *  is strongly recommended to use the macro #CERTAPI_VERSION_INT to assign the
 *  correct version number in the function table.
 *
 *  All functions that are not deprecated have to be implemented. However, if a temporary partial
 *  implementation of the CERT API is provided, address of callbacks not
 *  implemented, or deprecated, has to be set to \c NULL.
 */

/** @page p_cert_lock Locking the CERT resource
 *
 *  In an OS-based environment the CERT block may be used by different independent
 *  CA applications with their own threads and processes. Before sending
 *  commands to the CERT block, a CA application must lock the resource for
 *  exclusive use in order to guaranty consistencies of commands processed. The
 *  resource is locked by calling TCertLock(). If this function is called while
 *  the CERT resource is already locked by another application, it blocks until
 *  the resource is freed.
 *
 *  In other words, the CERT driver is in charge of the mutual exclusion between
 *  CA applications with regards to the CERT resource. It implies the
 *  implementation of TCertLock() to be thread safe and reentrant. This
 *  constraint does not apply to all other functions of the CERT API, because
 *  they are already protected by the lock and are not allowed to be called
 *  outside of a lock section.
 *
 *  Depending on the operating system architecture, inter-process communication
 *  (IPC) methods might be required to achieve the mutual exclusion.
 *
 *  The CERT resource has to be released as soon as possible in order to avoid
 *  blocking another application too long. CA application architecture has to
 *  take this point into account.
 *
 *  The TCertLock() function returns a handle that is passed back to
 *  TCertExchange() and TCertUnlock() functions. This ensures TCertExchange() is
 *  called only if TCertLock() has been called previously.
 *
 *  The bare implementation of the CERT API does not need to cope with thread
 *  safety and mutual exclusion. However, a "dummy" implementation of TCertLock()
 *  and TCertUnlock() must be provided in order to return the handle parameter
 *  required by TCertExchange().
 */

/** @page p_cert_cmd CERT command handling
 *
 *  @section s_cmd_principle Principle of operations
 *
 *  A CERT command is a single request to the CERT hardware block. The CERT API
 *  TCertExchange() function sends a series of one or more commands to the CERT
 *  block. The CERT driver is responsible for handling each command by writing
 *  and reading the CERT block Common Interface registers.
 *
 *  Refer to [NSR] for the interface specification of the CERT block hardware as
 *  well as requirements associated to the integration of this block.
 *
 *  The mapping between the command structure TCertCommand provided to
 *  TCertExchange() and the CERT block Common Interface registers is defined as
 *  follows:
 *  @image html cert_registers.png
 *  @image rtf cert_registers.png
 *
 *  For each command provided to a TCertExchange() call, the CERT driver has to
 *  apply the following operations:
 *
 *  -# Write the 32-byte input data into the 8 CERT DATA_IN_X registers,
 *     starting from DATA_IN_0 to DATA_IN_7 as described in the figure above.
 *  \n
 *  -# Write the 4-byte opcodes into the COMMAND register. As the least
 *     significant bit of opcodes is set to 1, the CERT block starts the
 *     processing right after the COMMAND register is written.
 *  \n
 *  -# Wait for the command processing completion either by polling the least
 *     significant bit of the COMMAND register (this bit is cleared when the
 *     command is over) or wait for an interrupt to be triggered on the
 *     interrupt line out. When the interrupt is set, it must be cleared by
 *     writing the INTERRUPT register.
 *  \n
 *  -# Read the STATUS_AKL register and write it in the status field
 *  \n
 *  -# Read the 8 CERT DATA_OUT_X registers and write them into the output data
 *     structure, starting from DATA_OUT_0 to DATA_OUT_7 as described in figure
 *     above.
 *  \n
 *  -# If the least significant bit of STATUS_AKL is set to 1, it means the
 *     command failed. In such a case, the CERT driver must stop handling
 *     remaining commands and must return to the caller. Retries are managed by
 *     the CA software, not by the driver.
 *  \n
 *  -# If the command is successful, process the next command by repeating all
 *     steps above.
 *
 *  <hr>@section s_cmd_error_free Error free scenario
 *  @image html cert_cmd_error_free.png
 *  @image rtf cert_cmd_error_free.png
 *
 *  <hr>@section s_cmd_proc_error Processing error scenario
 *  @image html cert_cmd_proc_error.png
 *  @image rtf cert_cmd_proc_error.png
 *
 *  <hr>@section s_cmd_timeout_error Timeout error scenario
 *  @image html cert_cmd_timeout_error.png
 *  @image rtf cert_cmd_timeout_error.png
 *
 */

/** @page p_use_cases Use cases
 *
 *  @section s_ucase_descrambling Program descrambling
 *  Figure below depicts the scenario to descramble a program with control words
 *  protected by the CERT block.
 *  @image html cert_ucase_descrambling.png
 *  @image rtf cert_ucase_descrambling.png
 *
 *  (1)	The application starts a descrambling session for a given program. The
 *      application provides the related transport session ID (TSID) and the
 *      list of elementary stream to be descrambled (PIDs).
 *
 *  (2)	The CAK opens a SEC API stream decryption session to descramble the
 *      elementary streams referenced by the transport session ID.
 *
 *  (3)	The CAK provides program metadata if any (e.g. copy control)
 *
 *  (4)	The CERT block is reserved for exclusive use by the CAK
 *
 *  (5)	The CAK makes a first CERT exchange to process the even control word.
 *      The driver is then in charge of handling each command by writing/reading
 *      CERT registers. At the end of this sequence, the even control word is
 *      output on the CERT key interface bus.
 *
 *  (6) The CAK calls the SEC API secUseCertKey() function in order to gets the
 *      control word pending on the CERT block, copies it into the adequate slot
 *      of the descrambler key table and acknowledges the CERT block.
 *
 *  (7)	The odd control word is handled exactly the same way
 *
 *  (8)	Finally, the CERT resource is released
 *
 *  <hr>@section s_ucase_r2r RAM2RAM
 *  Figure below depicts the scenario of a RAM2RAM encryption with a key
 *  protected by the CERT block.
 *  @image html cert_ucase_r2r.png
 *  @image rtf cert_ucase_r2r.png
 *
 */

/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/

/** @defgroup functionTable Function Table */
/** @defgroup lockMgt Resource Lock Management */
/** @defgroup commandHandling Command Handling */



/******************************************************************************/
/*                                                                            */
/*                              VERSION TOOL                                  */
/*                                                                            */
/******************************************************************************/

#ifndef CERT_TOOL_VERSION
#define CERT_TOOL_STRINGIFY(s) CERT_TOOL_TOSTRING(s)
#define CERT_TOOL_TOSTRING(s)  #s

#define CERT_TOOL_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
#define CERT_TOOL_VERSION_DOT(a, b, c) a ##.## b ##.## c
#define CERT_TOOL_VERSION(a, b, c) CERT_TOOL_VERSION_DOT(a, b, c)
#endif

#define CERTAPI_VERSION_INTER CERT_TOOL_VERSION(CERTAPI_VERSION_MAJOR, \
              CERTAPI_VERSION_MEDIUM, \
              CERTAPI_VERSION_MINOR)

#define CERTAPI_VERSION_INT   CERT_TOOL_VERSION_INT(CERTAPI_VERSION_MAJOR, \
            CERTAPI_VERSION_MEDIUM, \
            CERTAPI_VERSION_MINOR)

#define CERTAPI_VERSION_STRING  "CERTAPI_" CERT_TOOL_STRINGIFY(CERTAPI_VERSION_INTER)




/******************************************************************************/
/*                                                                            */
/*                              TYPES DEFINITIONS                             */
/*                                                                            */
/******************************************************************************/

/**
 *  @brief
 *    Unsigned 8-bit type.
*/
typedef unsigned char         TCertUInt8;

/**
 *  @brief
 *    Unsigned 16-bit type.
*/
typedef unsigned short int    TCertUInt16;

/**
 *  @brief
 *    Unsigned 32-bit type.
*/
typedef unsigned long int     TCertUInt32;

/**
 *  @brief
 *    Status code returned by functions of the CERT API
*/
typedef enum
{
  CERT_NO_ERROR,
   /**< Requested operation was completed successfully
    */
  CERT_ERROR_BAD_HANDLE,
   /**< Handle provided is invalid or unknown
    */
  CERT_ERROR_BAD_EMI,
   /**< @deprecated
    */
  CERT_ERROR_BAD_USAGE,
   /**< @deprecated
    */
  CERT_ERROR_TIMEOUT,
   /**< Execution of a CERT command lasted too long
    */
  CERT_ERROR,
   /**< Requested operation failed
    */
  LAST_CERT_STATUS
   /**< Internal use only.
    */
} TCertStatus;



/**
 *  @ingroup commandHandling
 *
 *  @brief
 *    Type used to characterize the processing duration a CERT command.
 *    To be used by the CERT driver to determine how long to wait for the end of
 *    a command processing.
 *
 *  @warning
 *    This enum does not define timeout values but just timeout identifiers.
 *    Associated timeout values are chipset dependent and must be defined in the
 *    CERT driver, not in this header file.
 *
*/
typedef enum
{
  CERT_TIMEOUT_DEFAULT,
   /**<  Default timeout. Indicates that the associated command does not write
    *    in OTP.
    */
  CERT_TIMEOUT_OTP,
   /**<  The associated command is writing in OTP memory.
    */
  LAST_CERT_TIMEOUT
   /**<  Internal use only.
    */
} TCertTimeoutType;


/**
 *  @deprecated
 *    Replaced by SECAPI::KeyID
*/
typedef enum
{
  CERT_KEY_PARITY_EVEN,
   /**<  @deprecated
    */
  CERT_KEY_PARITY_ODD,
   /**<  @deprecated
    */
  CERT_KEY_PARITY_UNDEFINED,
   /**<  @deprecated
    */
  LAST_CERT_KEY_PARITY
   /**<  @deprecated
    */
} TCertKeyParity;


/**
 *  @brief
 *    Pointer to an opaque structure to be defined by the entity in charge of
 *    developing the CERT driver and used as a handle on the CERT block resource.
 *
 *    This handle is an output of TCertLock() and given back in input of
 *    TCertExchange() and TCertUnlock().
 */
typedef struct SCertResourceHandle* TCertResourceHandle;


/**
 *  @deprecated
 */
typedef struct SCertKeyPathHandle TCertKeyPathHandle;


/**
 *  @ingroup commandHandling
 *
 *  @brief
 *    Structure used to accommodate parameters of a CERT command.
 */
typedef struct
{
  TCertUInt8 inputData[32];
   /**< Input data to be written in the 8 32-bit CERT common interface DATA_IN_X
    *   registers. First 4 MSB inputData[0:3] shall be written in DATA_IN_0
    *   register, next 4 MSB inputData[4:7] in DATA_IN_1 register and so on.
    */
  TCertUInt8 outputData[32];
   /**< Buffer where to write values of the 8 32-bit CERT common interface
    *   DATA_OUT_X registers following the processing of a command. DATA_OUT_0
    *   register value shall be written in the first 4 MSB outputData[0:3],
    *   DATA_OUT_1 register in next 4 MSB outputData[4:7] and so on.
    */
  TCertUInt8 status[4];
   /**< Buffer where to write the value of the CERT common interface STATUS_AKL
    *   register following the processing of a command.
    */
  TCertUInt8 opcodes[4];
   /**< Command operation codes to be written in the CERT common interface
    *   COMMAND register. The least significant bit that acts as the command
    *   start bit is already set to 1.
    */
  TCertTimeoutType timeout;
   /**<  This field characterizes the processing duration of the command. It is
    *    not expressed as a duration. Associated timeout values is to be defined
    *    by the entity in charge of developing the CERT driver. This field is
    *    mainly used to know whether the command is going to write in OTP or
    *    not.
    */
} TCertCommand;


/******************************************************************************/
/*                                                                            */
/*                           FUNCTION TABLE DEFINITION                        */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup lockMgt
 *
 *  @brief
 *    This function reserves the CERT resource for exclusive use to the caller.
 *    It returns a handle to the CERT resource if it is not in use. Otherwise,
 *    the function blocks until the resource is freed.
 *
 *  @param[out] pxResourceHandle
 *    Handle assigned to the CERT resource.
 *
 *  @retval CERT_NO_ERROR
 *    The CERT resource was locked successfully
 *
 *  @retval CERT_ERROR
 *    Errors occurred and operation could not be completed successfully (e.g. OS
 *    errors). This status has nothing to do with the availability of the CERT
 *    resource.
 *
 *  @warning
 *    - The OS-based implementation of this function must ensure the mutual
 *    exclusion between threads and/or processes that need to access the CERT
 *    resource. Depending on the operating system architecture, inter-process
 *    communication (IPC) methods might be required to achieve this mutual
 *    exclusion.
 *    .
 *    - The bare implementation of this function does not need to ensure any mutual
 *    exclusion. It just needs to return a handle that will be passed back to
 *    TCertExchange().
*/
typedef TCertStatus (*TCertLock)
(
  TCertResourceHandle* pxResourceHandle
);


/**
 *  @ingroup lockMgt
 *
 *  @brief
 *    This function releases the CERT resource previously locked by
 *    TCertLock().
 *
 *  @param[in] xResourceHandle
 *    Handle to the CERT resource.
 *
 *  @retval CERT_NO_ERROR
 *    The operation was completed successfully and the CERT lock released.
 *
 *  @retval CERT_ERROR_BAD_HANDLE
 *    Handle provided is invalid or unknown. One typically drops in this case if
 *    this function is called while the CERT resource has not been locked.
 *
 *  @retval CERT_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
*/
typedef TCertStatus (*TCertUnlock)
(
  TCertResourceHandle xResourceHandle
);


/**
 *  @ingroup commandHandling
 *
 *  @brief
 *    This function is used to send a series of commands to the CERT block. For
 *    each command part pxCommands buffer, the CERT driver has to systematically
 *    write the 8 32-bit CERT input registers (DATA_IN_X), wait for the command
 *    processing completion and read the 8 32-bit CERT output registers
 *    (DATA_OUT_X) as well as the 32-bit status register (STATUS_AKL).
 *
 *    If a command fails (least significant bit of STATUS_AKL set to 1) or lasts
 *    longer than expected (timeout), TCertExchange must return to the caller
 *    without handling remaining commands, if any. The number of commands
 *    processed so far, including the command that failed, must be signaled
 *    accordingly in pxNumOfProcessedCommands. A command that timed out is not
 *    considered as processed, thus must not be counted in
 *    pxNumOfProcessedCommands. Values of DATA_OUT_X registers and STATUS_AKL
 *    register of the faulty command must be returned as well.
 *
 *  @param[in] xResourceHandle
 *    Handle to the CERT resource.
 *
 *  @param[in] xNumOfCommands
 *    Number of commands to be processed by the CERT block.
 *
 *  @param[in,out] pxCommands
 *    Buffer containing xNumOfCommands instantiations of TCertCommand structure.
 *    This structure is used to accommodate input parameters of each command as
 *    well as resulting output. The memory is allocated by the caller.
 *
 *  @param[out] pxNumOfProcessedCommands
 *    Number of commands actually processed by the CERT block. If all commands
 *    are processed successfully, this number is equal to xNumOfCommands. If a
 *    command fails or times out, this parameter indicates the number of
 *    commands processed so far, including the faulty command but not the timed
 *    out command.
 *
 *  @retval CERT_NO_ERROR
 *    All commands have been processed successfully. A command is successful if
 *    the least significant bit of STATUS_AKL is equal to 0 after the command
 *    completion.
 *
 *  @retval CERT_ERROR_BAD_HANDLE
 *    Handle provided is invalid or unknown. One typically drops in this case if
 *    this function is called while the CERT resource has not been locked.
 *
 *  @retval CERT_ERROR_TIMEOUT
 *    The timeout has expired and the CERT block is still processing a command
 *    (least significant bit of COMMAND register still to 1).
 *
 *  @retval CERT_ERROR
 *    Any other errors occurred at driver level or reported by the CERT block
 *    during the processing of a command (least significant bit of STATUS_AKL
 *    equal to 1).
 *
*/
typedef TCertStatus (*TCertExchange)
(
        TCertResourceHandle  xResourceHandle,
        size_t               xNumOfCommands,
  const TCertCommand*       pxCommands,
        size_t*             pxNumOfProcessedCommands
);


/**
 *  @deprecated
 *    This function is deprecated and replaced by SECAPI::secUseCertKey()
*/
typedef TCertStatus (*TCertUseEncryptionKey)
(
  TCertUInt16           xEmi,
  TCertKeyPathHandle*  pxKeyPathHandle,
  TCertKeyParity        xKeyParity
);


/**
 *  @deprecated
 *    This function is deprecated and replaced by SECAPI::secUseCertKey()
*/
typedef TCertStatus (*TCertUseDecryptionKey)
(
  TCertUInt16           xEmi,
  TCertKeyPathHandle*  pxKeyPathHandle,
  TCertKeyParity        xKeyParity
);



/**
 *  @ingroup functionTable
 *
 *  @brief
 *    Structure defining the CERT driver function table.
 */
typedef struct
{
  TCertUInt32 certApiVersion;
   /**< Version of the CERT API. Use the macro CERTAPI_VERSION_INT to assign the
    *   the right value.
    */
  TCertLock certLock;
   /**< Function to reserve the CERT resource for exclusive use
    */
  TCertUnlock certUnlock;
   /**< Function to release the CERT resource
    */
  TCertExchange certExchange;
   /**< Function to perform transactions with the CERT block
    */
  TCertUseEncryptionKey certUseEncryptionKey;
   /**< @deprecated
    */
  TCertUseDecryptionKey certUseDecryptionKey;
   /**< @deprecated
    */
} TCertFunctionTable;



/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup functionTable
 *
 *  @brief
 *    This function returns a pointer to the CERT driver function table if
 *    successful, NULL in case of error.
 *
 *  @note
 *    This function must not allocate memory for the function table because it
 *    will be never freed. The function table is purely static for a given
 *    implementation, thus it is much better and simpler to declare the table as
 *    a static global variable and simply returns its address as depicted in the
 *    sample code below.
 *    \code
  static TCertFunctionTable    gCertFunctionTable =
  {
      CERTAPI_VERSION_INT,
      certLock,
      ...
  };

  TCertFunctionTable* certGetFunctionTable(void)
  {
    return &gCertFunctionTable;
  }
 *    \endcode
*/
TCertFunctionTable* certGetFunctionTable
(
  void
);


//#define CONGIG_FAKE_CERT_TEST

#ifdef CONGIG_FAKE_CERT_TEST
#define FAKE_GEN_KEY_600        0
#define FAKE_GEN_KEY_700        0
#define FAKE_CERT_NATIVE_RPC    1
#endif //?#ifdef CONGIG_FAKE_CERT_TEST

#endif /* CA_CERT_H */

/* END OF FILE */
