/**
**  @file nht_term.h
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset harness tests
**
**    This header file describes the RPC terminal API to be implemented by
**    the Chipset Manufacturer in order to comply with the Harness test
**    toolkit provided by Nagra in the particular case of a Chipset
**    driver implementation not based on an OS.
**
**    This API extension is intended to provide test facilities associated
**    to a NOCS certification relative to on-Chip applications not base on
**    an OS (e.g: os-free BSD application, etc...)
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

#ifndef _NHT_TERM_H_
#define _NHT_TERM_H_


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the version number of the this API. Note also that this version
 * does not correspond to the identifier of the software implementation version.
 * @warning Do not update these values
*/
#define NHT_TERM_VERSION_MAJOR    1
#define NHT_TERM_VERSION_MEDIUM   2
#define NHT_TERM_VERSION_MINOR    0


/** @page p_history History
 *
 *   - <b> 1.2.0 2014/05/06 Nicolas Grosclaude</b>
 *     - Add CM debug printout facility (report performed in client env)
 *   - <b> 1.1.1 2014/19/03 Nicolas Grosclaude</b>
 *     - Modify read/write terminal timeout spec to 1s (instead of 4s)
 *     - Add particular concerns regarding RS232 terminal type
 *     - Update/Improve comments
 *   - <b> 1.1.0 2012/12/01 Nicolas Grosclaude</b>
 *     - First release
 */

/******************************************************************************/
/*                                                                            */
/*                               INCLUDE FILES                                */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                             OVERALL DOCUMENTATION                          */
/*                                                                            */
/******************************************************************************/


/**
 * @mainpage Overview
 *  - @subpage p_preface
 *  - @subpage p_timeout
 *  - @subpage p_debug_report
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
 *  This header file describes the RPC terminal API associated to the
 *  Nagra harness test framework provided by Nagra that shall apply in
 *  the particular case of a Chipset OS-free SW implementation (also called
 *  'bare-mode').
 *  Implementing this API is not mandatory for Chipset SW applications based on
 *  a posix compliant OS.
 *
 *  For Chipset non-OS based applications (e.g: os-free BSD server application),
 *  communication with the harness test framework provided by Nagra
 *  is performed accross a different port to the traditional Ethernet
 *  one (e.g: RS232).
 *
 *  Since implementation of such a particular communication means is chipset
 *  specific, implementation of these functions is under the responsibility
 *  of the chipset manufacturer.
 *
 *  However the terminal type (e.g R2R232) shall be agreed
 *  by both: the Chipset manufacturer and Nagra.
 *
 *  In any case, an RPC terminal is assumed to be running in RAW
 *  mode with an 8-bit per charaters. In particular, all 8bit values
 *  shall be read/write as there are provided in the interface.
 *
 *  Calling the functions described in this file is exclusivelly reserved
 *  for Nagra Harness test SW. Chipset driver implementation
 *  is not allowed to make direct calls to these functions for its own
 *  purpose.
 *
 *  RPC terminal is initialized by the Harness test framework independently
 *  of the Chipset driver particular concerns (e.g: BSD driver, etc..) using the
 *  nht_term_portOpen() dedicated function.
 */

/** @page p_timeout Timeout concerns
 *
 *  Starting with versions v1.1.1 of this document, timeout specification has
 *  been decreased to 1s in order to fit the new requirements associated to
 *  chipset reboot concerns.
 *
 *  Ensuring such a timeout value makes the implementation of this EAPI
 *  safe when using NHT-server-lib package versions that provide the
 *  terminal connecting timeout feature.
 *
 *  When building a server based on NHT server package versions that provide
 *  terminal connecting timeout feature, not fixing this timout value to 1s
 *  may lead terminal-based applications (e.g: bsd) to fail when attempting
 *  to connect to the server when this one is not already started
 *  (e.g: chipset rebooting).
 *
 *  Fixing the timeout value to 1s in this EAPI implementation remains fully
 *  down compatible with previous NHT-server-lib packages that were delivered
 *  in the past.
 */

/** @page p_debug_report CM debug printout facilities
 *
 *  Starting with versions v2.0.0 of this document, Chipset Manufacturer (CM)
 *  driver implementation debug printout facility has been added into this EAPI.
 *
 *  This facility has been introduced in order to overcome the removal
 *  of the 'nht_report' EAPI from the set of the NOCS harness test server
 *  interface.
 *  As a result, previous potential references to the "nht_report.h" functions
 *  in CM driver implementation must now be replaced and instead use this
 *  new report interface.
 *
 *  This facility includes stdout/stderr-like reporting ability when
 *  the server is operating in bare mode.
 *
 *  Note: 'nht_report.h' EAPI has been removed from the NOCS Harness Test
 *  server interfaces in order to prevent bad usage of its associated
 *  low-level functions in the CM's driver that were causing mishandling
 *  during certification runs.
 *
 *  Functions for reporting CM debug printout to the client applications
 *  (when server operates in bare mode) are now directly provided as callback
 *  functions. These ones are registered by the upper leverl of the server application at
 *  server startup using the new function 'nht_term_register_printout_cbfct()'.
 *
 *  @warning
 *  Such debug printout facilities do not apply for debugging the RPC
 *  low-level communication functions described in this document.
 *  None of the terminal communication low-level functions described in this
 *  EAPI are allowed to use this debug printout feature (at any time).\n\n
 *  The reason why is because of the fact that such debug printout facilities
 *  are themselves using the RPC low-level functions described in this document.
 */

/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/

/** @defgroup nht_term_com Harness Test Framework RPC communication API */
/** @defgroup nht_term_debug Harness Test Framework CM's debug API */


/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup nht_term_com
 *
 *  @brief
 *    This function opens/initializes the chipset RPC terminal used
 *    by the harness test framework provided by Nagra.
 *
 * @retval   Return 0 if successfully opened (or -1 in case of connection errors)
 *
 *    If successfully opened (or already opened), this function shall return 0.
 *    After having opened this terminal port, this one is assumed to be
 *    fully operational and thus without other extra initialization.
 *
 *    The implementation of this function is responsible to ensure that all
 *    input and output buffers of the terminal were implicitely flushed
 *    by this function call.
 *
 *    Please note that this function shall never fail since such an error
 *    cannot be reported to the harness test framework any way.
 *
 *    In case of a termination of the current application, this port is
 *    implicitely assumed as having been closed.
 *    Subsequent application execution are responsible to re-open this terminal
 *    at startup time.
 *
 *    Nagra provided harness test on-chips SW is responsible for having call
 *    this function at least once before testing any Chipset non-OS-based driver.
*/
int nht_term_portOpen (void);


/**
 *  @ingroup nht_term_com
 *
 *  @brief
 *    This function writes/sends data to the harness test framework across the
 *    RPC terminal connection (e.g: RS232) that both Nagra and the chipset manufacturer
 *    agreed with.
 *
 *    See nht_term_portOpen() functions for terminal port opening.
 *
 *  @param[in] pxBuffer
 *               Data buffer to be sent
 *  @param[in] xBufferSize
 *               Size of the data to be sent
 *
 *  @retval   The number of byte that have been effectivelly sent
 *            or -1 in case of connection failure
 *
 *    This function does not require any timeout mechanism. If no connection
 *    error is detected, this function shall always send the specified number
 *    of bytes into the terminal and return the xBufferSize value.
 *
 *    If a terminal connection error is detected, this function shall immediately
 *    return -1.
 *
 *    Note that implementation of this function does not need to wait until effective
 *    physical transmission of the data. However, this function shall ensure that all
 *    bytes are (will be) physically transmitted in the same order as given
 *    in the pxBuffer input parameter. Data provided in consecutive calls to
 *    this functions shall be physically transmitted in the same order as the
 *    function calls.
 *
 *    Only Nagra provided RPC software is allowed to call this function,
 *    since data streaming is strongly and exclusivelly related to the RPC
 *    communication protocol.
 *
 *  @warning
 *    Huge time consuming operations such as 'serial port debug printout'
 *    should be avoided in the core of this function. Violating this rule may
 *    lead to delay subsequent call to the nht_term_portRead() function and
 *    potentienly causing lost of incoming bytes sent by harness test client
 *    applications!!! (e.g: in RS232 UART with limited physical buffer size).
 *
*/
int nht_term_portWrite
(
  const void * pxBuffer,
  int          xBufferSize
);


/**
 *  @ingroup nht_term_com
 *
 *  @brief
 *    This function reads/receives data from the harness test framework across the
 *    RPC terminal connection (e.g: RS232) that both Nagra and the chipset manufacturer
 *    agreed with.
 *
 *    See nht_term_portOpen() functions for port opening.
 *
 *  @param[in] pxBuffer
 *               Input data buffer
 *  @param[in] xBufferSize
 *               Max size (max byte number) to be read
 *
 *  @retval   Return -1 if connection has been detected as lost, return -1.
 *
 *  @retval   Return the effective number of bytes that have been read.
 *
 *    This function stands as a blocking function with an implicite
 *    timeout of 1s. This function shall comply to the following
 *    rules listed in precedence priority order:
 *
 *    - Bytes shall be read in the same order as physically provided
 *      in the terminal connection. Bytes that were already physically
 *      received but not returned into the pxBuffer parameter shall be
 *      provided/presented during the next call to this functions.
 *
 *    - If not receiving a first byte associated to a call to this
 *      function, this function shall return after a timeout of 1s.\n
 *      In this case, the real time spent by this function call
 *      should not exceed 1.2s max.
 *
 *    - If during a call to this function, the delay for obtaining
 *      a subsequent byte exceeds 1s (timout), the function shall directly
 *      return to the caller with a value indicating the number of
 *      bytes that was effectively read so far
 *      (0 < 'return_value' < xBufferSize).\n
 *      In this case, the real duration between the last recieved
 *      byte and the return of this function call shall not exceed
 *      1.2s max.
 *
 *    - When the number of requested bytes are available, this function
 *      shall immediately return (without waiting on timeout) with
 *      a return value equal to xBufferSize.\n
 *
 *    The following concern applies to RS232 terminal type only:
 *
 *    - Character Framing errors that are detected during a call to
 *      this function shall lead the function to immediately return
 *      with a -1 value.
 *
 *    - Bytes detected as suffering of framing errors shall be disguarded
 *      and never be provided back to caller of this function.
 *      This concern apply to current function call as well as for
 *      subsequent calls to this function.
 *
 *    - Character Framing errors that are detected during a call to
 *      this function shall not remain persistant between
 *      two consecutive calls to this function. The implementation
 *      of this function shall ensure that Framing errors detected
 *      in previous calls to this function are cleaned up before
 *      starting to read the physical UART in a subsequent call to
 *      this function.
 *
 *    - Optionally, when a character framing error is detected,
 *      implementation of this function is allowed to flush the terminal
 *      input buffer before returning back to the caller. Also,
 *      implementation of this function is allowed to internally
 *      re-open the terminal connection (if needed).
 *
 *    Only Nagra provided RPC software is allowed to call this function,
 *    since data streaming is strongly and exclusivelly related to the RPC
 *    communication protocol.
 *
 *  @warning
 *    When calling this function, catching bytes from the physical
 *    terminal shall apply without any delay. In particular, extra
 *    huge time-consuming operations such as serial port debug printout
 *    should be avoided in the core of this function.
 *    Violating this rule may lead to loose incoming bytes sent by
 *    harness test client applications!!! (e.g: in RS232 UART
 *    with limited physical input buffer size).
 *
*/
int nht_term_portRead
(
  void * pxBuffer,
  int    xBufferSize
);


/**
 *  @ingroup nht_term_debug
 *
 *  @brief
 *    stdout/stderr-like debug printout callback function prototype.
 *
*/
typedef void (*TNhtTerm_printOutCallBack) (
  const char *  pxString
  /**<  CM debug printout to be reported. */
);


/**
 *  @ingroup nht_term_debug
 *
 *  @brief
 *    This function registers the CM debug printout callback functions
 *    for CM's driver implementation debug reporting (into client environment).
 *
 *  @param[in] xStdoutCallBack
 *               stdout-like callback function
 *  @param[in] xStderrCallBack
 *               stderr-like callback function
 *  The callback functions that have been registered using this function can
 *  be used later-on by CM driver implementation in order to report its own
 *  debug printout to the client applications.
 *
 *  @warning
 *    Do not use such callback function within the RPC terminal communication
 *    low-level functions described in this document.\n
 *    Such debug printout facility is only reserved for debugging implementation
 *    of the function defined in other EAPIs/APIs of the NOCS Harness test
 *    interface set.
*/
void nht_term_register_printout_cbfct
(
  TNhtTerm_printOutCallBack xStdoutCallBack,
  TNhtTerm_printOutCallBack xStderrCallBack
);


#ifdef __cplusplus
}
#endif


#endif /* _NHT_TERM_H_ */

/* nht_term.h */
