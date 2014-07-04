/**
**  @file ca_nhtsec.h
**
** @brief
**    Chipset Security Driver EAPI for NOCS Secure chipset harness tests
**
**    This header file describes the API extensions of the SEC driver API
**    v5.1.x that need to be implemented by the Chipset Manufacturer in
**    order to comply with the Harness test toolkit provided by Nagra.
**
**    Such extensions shall be implemented by the Chipset Manufacturer the
**    same way as the Chipset Manufucturer has to implement the SEC driver
**    API.
**
**    Implementing the function extensions described in this API do not
**    release the Chipset Manufucturer for implementing all functions
**    described in the SEC driver API.
**
**    This API extension is intended to provide test facilities associated
**    to a NOCS certification by abstracting additional specific Chipset
**    Manufacturer resource handling not covered by the SEC API
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

#ifndef NHT_SEC_H
#define NHT_SEC_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the version number of the SEC API. Note also that this version
 * number does not correspond to the version number of the software version.
 * @warning Do not update these values
*/
#define NHTSECAPI_VERSION_MAJOR  5
#define NHTSECAPI_VERSION_MEDIUM 0
#define NHTSECAPI_VERSION_MINOR  1


/** @page p_history History
 *
 *   - <b> 5.0.1 2013/07/31 Nicolas Grosclaude</b>
 *     - Replace transport stream opening with NOCS harness test specific
 *       functions for DSC and SCR.
 *   - <b> 3.3.3 2013/07/15 Nicolas Grosclaude</b>
 *     - First release of the SEC EAPI. Based on SEC API 5.1.x
 */

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "ca_sec.h"
#include "nocs_sec_impl.h"


/***************************************************************************/
/*                                                                         */
/*                             OVERALL DOCUMENTATION                       */
/*                                                                         */
/***************************************************************************/

/**
 * @mainpage Overview
 * This API stands as an extension of the SEC API v5.1.x\n<hr>
 *
 *  - @subpage p_preface
 *  - @subpage p_history
 *  - @subpage p_transportSession
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
 *  Harness test certification.\n
 *
 *  This header file describes an API extensions of the SEC driver API
 *  v5.1.x that need to be implemented by the Chipset Manufacturer in
 *  order to comply with the Harness test toolkit provided by Nagra.
 *
 *  Implementation of this API is mandatory for passing a NOCS
 *  certification.
 *
 *  This API extension is first intended to provide test facilities
 *  associated to a NOCS harness test certification by preventing
 *  the chipset manufacturer to implement its own SEC test application.
 *  SEC test applications will be provided by Nagra.
 *
 *  This extended API shall be implemented by the chipset manufacturers for any
 *  new NOCS secure chipset that is candidate to a Nagra NOCS certification.
 *  Such extensions must be implemented by the Chipset Manufacturer the same
 *  way as the Chipset Manufucturer has to implement the SEC driver API.
 *
 *  Implementing the SEC function extensions described in this API do not
 *  release the Chipset Manufucturer for implementing all functions
 *  described in the SEC driver API.
 *
 *  Good understanding of the SEC API v5.1.x stands as a pre-requesite for
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

/** @page p_transportSession Transport Session
 *
 *  <h2>Transport session management</h2>
 *
 *  SEC API v5.1.x NOCS harness tests require usage of transport session
 *  identifiers for processing streams.
 *  Because transport session characteristics settings are not covered by
 *  the SEC API, this EAPI introduces a set of additional functions in
 *  charge of handling the transport session that will apply to SEC
 *  NOCS harness test runs.
 *
 *  Note that this particular set of functions does not claim to cover the
 *  overall set of all possible transport session configurations associated to
 *  a potential STB product, but only the ones that are in the mission scope
 *  of the SEC NOCS harness test certification.
 *
 *  As a main characteristic, transport sessions require input/output
 *  data stream to be known at transport session creation time.
 *  Using such transport session type does not allow the user to manually
 *  and directly introduce or retrieved data or chunk of data in session
 *  pipe during the transport session life duration. Only keyring, EMI and
 *  intial values (IV) can be setup during the life duration of the transport
 *  session.
 *
 *  Usage of transport sessions applies to data streams that are subject to
 *  strong real-time concerns (e.g: video descrambling, etc...)
 *
 *  For NOCS harness tests, only fundamental transport streams such as DSC
 *  and SCR transport streams are required. DSC and SCR transport session
 *  definition complies with the ones found in CSD extended API.
 *
 *  Such fundamental tranport sessions only allow usage of a single cipher
 *  session (encryption or decryption).
 *
 *  For visual test control on Video/Audio back-end, please refer to the
 *  nhtSecOpenDscTransportSession() and nhtSecOpenScrTransportSession()
 *  description.
 *
 *  Here is the applicable function subset of this EAPI that applies to the
 *  transport session management:
 *  - nhtSecOpenDscTransportSession()
 *  - nhtSecOpenScrTransportSession()
 *  - nhtSecCloseTransportSession()
 *  - nhtSecStartTransportSessionStreaming()
 *  - nhtSecStopTransportSessionStreaming()
 *  - nhtSecWaitOnTransportSessionStreamingCompletion()
 *  - nhtSecSetTransportSessionInitialValue()
 */


/***************************************************************************/
/*                                                                         */
/*                              GROUPS DEFINITION                          */
/*                                                                         */
/***************************************************************************/

/** @defgroup nht_driversetting Harness Test resource Settings */

/** @defgroup nht_info Harness Test Chipset SW version*/

/** @defgroup nht_transport_session Harness Test Transport Session*/


/***************************************************************************/
/*                                                                         */
/*                              VERSION TOOL                               */
/*                                                                         */
/***************************************************************************/


#define NHT_SECAPI_VERSION_INTER SEC_TOOL_VERSION(NHTSECAPI_VERSION_MAJOR, \
              NHTSECAPI_VERSION_MEDIUM, \
              NHTSECAPI_VERSION_MINOR)

#define NHT_SECAPI_VERSION_INT   \
  SEC_TOOL_VERSION_INT(NHTSECAPI_VERSION_MAJOR, \
    NHTSECAPI_VERSION_MEDIUM, \
    NHTSECAPI_VERSION_MINOR)

#define NHT_SECAPI_VERSION_STRING  "NHTSECAPI_" SEC_TOOL_STRINGIFY(NHT_SECAPI_VERSION_INTER)



/***************************************************************************/
/*                                                                         */
/*                     SEC driver intialization                            */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup nht_driversetting
 *
 *  @brief
 *    Initialize the SEC harness test resource usage.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval   SEC_NO_ERROR
 *              Initialization was completed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function is intended to let the chipset manufacturer perform some
 *  potential specific pre-initialization before an instance of an application
 *  is enabled to successfully use the SEC resources involved in harness test.\n
 *
 *  The application is responsible to call this function at least once before using
 *  any other functions of the SEC APIs.\n
 *  If pre-initialization succeeds or  if this one was already successfully
 *  initialized for this process instance, return "SEC_NO_ERROR".
 *
 *  PS: If the SEC resource termination succeeds or if these ones where not
 *  initialized yet, return "SEC_NO_ERROR".
 */
TSecStatus nhtSecInitialize (void);


/**
 *  @ingroup nht_driversetting
 *
 *  @brief
 *    Terminate the SEC harness test resource usage.
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
 *  This function terminates the SEC resource usage associated to an application
 *  instance.\n
 *  This function is intended to let the chipset manufacturer properly
 *  clean-up all SEC resources that were previously allocated (or engage)
 *  during the execution of the current harness test application instance for
 *  well-running of subsequent application instanciations.
 *
 *  SEC resource termination shall be implicite at application termination in
 *  order to ensure that subsequent application will run well.
 *
 *  After calling this function, subsequent SEC resources re-initializations (using
 *  the 'nhtSecInitialize()' funtion) shall be supported.
 */
TSecStatus nhtSecTerminate (void);


/***************************************************************************/
/*                                                                         */
/*                     SEC API/EAPI SW versions                            */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the current version of the Harness test SEC Driver extension
 *    Implementation.
 *
 *  @param[out]     pxSoftwareVersion
 *                   Software version. Use the macro SEC_TOOL_VERSION_INT() to assign the
 *                   right value.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the NHT SEC Driver extension
 *  implementation.\n
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/
TSecStatus nhtSecGetSoftwareVersion
(
  TUnsignedInt32 * pxSoftwareVersion
);


/**
 *  @ingroup nht_info
 *
 *  @brief
 *    Get the current version of the SEC Driver API implementation.
 *
 *  @param[out]     pxSoftwareVersion
 *                   Software version. Use the macro SEC_TOOL_VERSION_INT() to assign the
 *                   right value.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the SEC Driver API
 *  implementation.\n
 *
 *  Use the macro SEC_TOOL_VERSION_INT(x,y,z) to assign the right value.
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/
TSecStatus secGetSoftwareVersion
(
  TUnsignedInt32 * pxSoftwareVersion
);


/***************************************************************************/
/*                                                                         */
/*                     Transport session handling                          */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Streaming status definition.
 *
*/
typedef enum ENhtSecTransportStreamingStatus
{
  NHT_SEC_STREAMING_NO_ERROR,                          /**<  The streaming was successfully executed. */
  NHT_SEC_STREAMING_ERROR,                             /**<  Error: Other non defined error. */
  NHT_SEC_STREAMING_ERROR_WOULD_BLOCK,                 /**<  Error: The wait on streaming completion times out (streaming still in progress). */
  NHT_SEC_STREAMING_ERROR_INVALID_PARAMETERS,          /**<  Error: Invalid transport streaming argument passed to the function. */
  NHT_SEC_STREAMING_ERROR_INVALID_FILE_PATHNAME,       /**<  Error: Input/Output stream file opening error. */
  NHT_SEC_STREAMING_ERROR_SERVICE_CURRENTLY_IN_USED,   /**<  Error: Transport streaming is currently running. */
  NHT_SEC_STREAMING_ERROR_TEST_RUN_NOT_STARTED,        /**<  Error: Transport streaming not started. */
  NHT_SEC_STREAMING_ERROR_SERVICE_RUN_FAILLER          /**<  Error: Transport streaming process fatal failure. */

} TNhtSecTransportStreamingStatus;




/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    ECM call back private data opaque descritor type
*/
typedef void * TNhtsecCallBackPrivateParameters;



/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    ECM call back function type.
 *
 *  @param[in]  xTransportSessionId
 *              Transport session identifier.
 *
 *  @param[in]  xPrivateParameters
 *              ECM callback private data (as given at transport session opening time).
 *
 *  @param[in]  xEcmTableId
 *              ECM MPEG Table ID (equal to 0x80 or 0x81).
 *
 *  @param[in]  pxEcmContent
 *              ECM MPEG packet (table) buffer content.
 *
 *  @param[in]  xEcmContentSize
 *              ECM MPEG packet (table) buffer size.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was successfully transmitted for ECM decryption.
 *  @retval   SEC_ERROR
 *              If any errors (e.g: illegal ECM table ID).
 *
*/
typedef TSecStatus (*TNhtsecEcmContentCallBack)
(
  TTransportSessionId                xTransportSessionId,
  TNhtsecCallBackPrivateParameters   xPrivateParameters,
  TUnsignedInt8                      xEcmTableId,
  const TUnsignedInt8              * pxEcmContent,
  TSize                              xEcmContentSize
);


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Transport session DEMUX service parameters
 *
*/
typedef struct SNhtSecDemuxServiceInfo
{
  int                               videoPid;
  /**<  Video Pid. */
  int                               audioPid;
  /**<  Audio Pid. */
  int                               pcrPid;
  /**<  PCR Pid. */

} TNhtSecDemuxServiceInfo;


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Transport session DEMUX ECM parameters
 *
*/
typedef struct SNhtSecDemuxEcmInfo
{
  TNhtsecEcmContentCallBack         ecmCbfct;
  /**<  ECM call back function). */
  TNhtsecCallBackPrivateParameters  ecmCbPrivateData;
  /**<  ECM call back function private data (as given at transport session opening time). */
  int                               ecmPid;
  /**<  ECM Pid (if an ECM call back function is provided). */

} TNhtSecDemuxEcmInfo;


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Open a new SCR elementary transport session.
 *
 *  @param[in]  pxInputFileName
 *              Input transport session filename. If passed as NULL, input
 *              source shall be taken from the TV tuner. Supporting NULL
 *              value is however not required in NOCS harness test
 *              certification.
 *
 *  @param[in]  pxDemuxServiceInfo
 *              Address of the structure containing the DEMUX
 *              parameters for the new created transport session.
 *              This parameter cannot be passed as NULL.
 *
 *  @param[in]  xIsForEncryption
 *              Indicate if the SCR transport session is dedicated to
 *              an encryption or a decryption operation.
 *
 *  @param[in]  pxOutputFileName
 *              Output file where the stream of the last stage of the
 *              transport pipe shall be written to.
 *
 *  @param[out] pxTransportSessionId
 *              Unique tranportId associated to the just created/opened
 *              transport session.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function opens an elementary SCR tranport session and return
 *  an associated transport ID.
 *
 *  Important note: opening a transport session does not start playing the
 *  stream itself. For starting to play the associated stream, please
 *  refer to the function called nhtSecStartTransportSessionStreaming().
 *
 *  The input parameter 'pxInputFileName' indicates the input file source
 *  that shall apply to this transport session.
 *
 *  Note: In NOCS harness test certification, the input source of a transport
 *  session will always be a file specified by its path within the chipset
 *  file system. 'pxInputFileName' will never be passed as NULL during a
 *  NOCS certification.
 *
 *  The 'pxDemuxServiceInfo' input parameter contains the DEMUX service data
 *  associated to this elementary transport session. It cannot be passed as NULL.
 *
 *  The parameter 'pxOutputFile' indicates the file where the output
 *  of the SCR session pipe shall be written. In NOCS harness test,
 *  this parameter is normally never provided as NULL.
 *
 *  The input parameters 'xIsForEncryption' indicates the encryption/decryption
 *  transport session type. This information is provided at transport session
 *  opening time in order to let the driver implementation anticipate the
 *  way to build the the pipes associated to this transport session.
 *
 *  Remember that output stream can only be sent to the video or audio
 *  backend (for visual/audio control) for SCR elementary transport
 *  decryption session (output stream in clear).
 *  For SCR elementary transport encryption session, only the input stream
 *  can  be sent to the video/audio backend for visual/audio control.
 *
 *  In case of success, this function shall return SEC_NO_ERROR and shall
 *  setup a unique TransportId number in the 'pxTransportSessionId' output
 *  parameter. At least, a transport session Id shall be unique per executable
 *  instance of the application.
 *
 *  If opening such an elementary SCR transport session, the application
 *  is then responsible for setting decryption or decryption data
 *  into this transport stream according to the specified encryption/decryption
 *  type specified by the 'xIsForEncryption' input parameter.
 *  (see: TSecOpenStreamDecryptSession() and TSecOpenStreamEncryptSession()
 *  function in the SEC API).

 *  This is a pure additional function associated to SEC harness test.\n
*/
TSecStatus nhtSecOpenScrTransportSession
(
  char                          * pxInputFileName,
  const TNhtSecDemuxServiceInfo * pxDemuxServiceInfo,
  int                             xIsForEncryption,
  char                          * pxOutputFileName,
  TTransportSessionId           * pxTransportSessionId
);


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Open an elementary DSC transport session.
 *
 *  @param[in]  pxInputFileName
 *              Input transport session filename. If passed as NULL, input
 *              source shall be taken from the TV tuner. Supporting NULL
 *              value is however not required in NOCS harness test
 *              certification.
 *
 *  @param[in]  pxDemuxServiceInfo
 *              Address of the structure containing the DEMUX engine
 *              PIDs specifications associated to the stream servicies
 *              (video, audio, pcr)..
 *
 *  @param[in]  xIsInClear
 *              Indicate the input stream is scrambled or in-clear.
 *              When in-clear, no encryption/decryption engine is involved
 *              in the DSC transport session.
 *
 *  @param[in]  pxDemuxEcmInfo
 *              Address of the structure containing the DEMUX engine
 *              ECM PID specifications associated to the stream servicies
 *              (if any)..
 *
 *  @param[in]  pxOutputFileName
 *              Output file where the stream of the last stage of the
 *              transport pipe shall be written to.
 *
 *  @param[out] pxTransportSessionId
 *              Unique tranportId associated to the just created/opened
 *              transport session.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function opens an elementary DSC tranport session and return an
 *  associated transport ID.
 *
 *  Important note: opening a transport session does not start playing the
 *  stream itself. For starting to play the associated stream, please
 *  refer to the function called nhtSecStartTransportSessionStreaming().
 *
 *  The input parameter 'pxInputFileName' indicates the input file source
 *  that shall apply to this transport session.
 *
 *  The 'pxDemuxServiceInfo' input parameter contains the DEMUX input data.
 *  associated to this elementary transport session. It cannot be passed as NULL.
 *
 *  The 'pxDemuxEcmInfo' gives the information of how the driver implementation
 *  shall handle the associated ECM in the stream. If passed as NULL, no ECM
 *  handling is required by the driver implementation for the transport session.
 *
 *  Input parameters 'xIsInClear' indicates if the input stream shall be
 *  concidered as ciphered (=0) or in-clear (=1).
 *
 *  Three cases shall be considered according to pxDemuxEcmInfo and xIsInClear
 *  parameters values.
 *
 *  1. If input stream is in-clear (xIsInClear != 0), no decryption engine
 *     is involved in this transport session and pxDemuxEcmInfo data are
 *     irrelevant (no ECM handling in any case).
 *
 *  2. If input stream is ciphered (xIsInClear = 0) and pxDemuxEcmInfo is not
 *     provided (=NULL), a decryption engine is involved in this tranport
 *     session, but keyring will be setup by the application before starting
 *     to play the stream. There is however no ECM handling any way).
 *
 *  3. If input stream is ciphered (xIsInClear = 0) and pxDemuxEcmInfo is
 *     provided (!= NULL), a decryption engine is involved keyring will be
 *     provided based on the ECM table content provided back by the driver
 *     during transport session streaming.
 *
 *  Note: In DSC elementary transport session, a crypto engine (if applicable)
 *  always applies for decryption (implicite here).
 *
 *  The parameter 'pxOutputFile' indicates the file where the output
 *  (last stage) of the session pipe shall be written in the chipset file
 *  system. In NOCS harness test, this parameter is normally never provided
 *  as NULL.
 *
 *  In case of success, this function shall return SEC_NO_ERROR and shall
 *  setup a unique TransportId number in the 'pxTransportSessionId' output
 *  parameter. This value shall be at least unique per
 *  executable instance of an application.
 *
 *  If opening such an elementary DSC transport session for an ciphered input
 *  stream (xIsInClear=0), the application is then responsible for registering
 *  a decryption streamSession (see: TSecOpenStreamDecryptSession()
 *  function in the SEC API).
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/
TSecStatus nhtSecOpenDscTransportSession
(
  char                          * pxInputFileName,
  const TNhtSecDemuxServiceInfo * pxDemuxServiceInfo,
  int                             xIsInClear,
  const TNhtSecDemuxEcmInfo     * pxDemuxEcmInfo,
  char                          * pxOutputFileName,
  TTransportSessionId           * pxTransportSessionId
);


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Start playing the stream associated to a transport session.
 *
 *  @param[in] xTransportSessionId
 *              Identifier of the transport session to start playing.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function start playing the stream associated to a transport session
 *  identified by its Transport session Id.
 *
 *  To stop or wait on a streaming completion, please refer to functions
 *  nhtSecCloseTransportSession() and nhtSecWaitOnTransportSessionStreamingCompletion().
 *
 *  If the streaming associated to this transport session was already
 *  started, return NHT_SEC_STREAMING_ERROR_SERVICE_CURRENTLY_IN_USED.
 *
 *  In case of success, this function shall immediately return with
 *  NHT_SEC_STREAMING_NO_ERROR and shall setup a unique TransportId number
 *  in the 'pxTransportId' output parameter. In a process re-entrant
 *  implementation of the SEC API, such transportId shall be unique in the
 *  system. In a only thread re-entrant implementation of the SEC,
 *  this value shall be at least unique per executable instance of
 *  the application.
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/

TNhtSecTransportStreamingStatus nhtSecStartTransportSessionStreaming
(
  TTransportSessionId xTransportSessionId
);


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Wait on transport stream play completion.
 *
 *  @param[in] xTransportSessionId
 *              Identifier of the transport session on which to wait
 *              on stream play completion.
 *
 *  @param[in] xTimeout
 *              Wait timeout (in second). value = -1 indicates that no
 *              timeout control is required.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function waits until at least one of the following conditions are met:
 *   1. The successfull completion of transport stream play.
 *   2. An explicite or implicite stop of the stream play.
 *   3. A fatal error in playing the stream occurs internally
 *      of the driver.
 *   4. The stream play wasn't started yet.
 *
 *  If the stream play wasn't started yet (case 4), the function shall
 *  immediately return with NHT_SEC_STREAMING_ERROR_TEST_RUN_NOT_STARTED
 *  value.
 *
 *  If the stream play already stopped when calling this function (case 2) or
 *  if the streaming completes, return the final associated streaming status.
 *
 *  If a fatal error occurs during the streaming operation (case 3),
 *  immediately return the the associated fatal error.
 *
 *  If the wait on completion times out (streaming still in progress),
 *  return with NHT_SEC_STREAMING_ERROR_WOULD_BLOCK value.
 *
 *  To stop or wait on a stream play completion please refer to functions
 *  nhtSecStopTransportSessionStreaming() and nhtSecWaitOnTransportSessionStreamingCompletion().
 *
 *  If streaming completes (or completed already), this function shall return
 *  NHT_SEC_STREAMING_NO_ERROR.

 *  This is a pure additional function associated to SEC harness test.\n
*/

TNhtSecTransportStreamingStatus nhtSecWaitOnTransportSessionStreamingCompletion
(
  TTransportSessionId xTransportSessionId,
  int                 xTimeout
);



/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Stop playing the stream associated to a transport session.
 *
 *  @param[in] xTransportSessionId
 *              Identifier of the transport session to start playing.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally. The intended operation failed.
 *
 *  This function stops (aborts) playing the stream associated to a
 *  transport session identified by its Transport session Id.
 *
 *  If the streaming associated to this transport session was never
 *  started yet, the function shall immediately return with
 *  NHT_SEC_STREAMING_ERROR_TEST_RUN_NOT_STARTED value.
 *
 *  If the streaming already stopped (implicitely or explicitely) when
 *  calling this function, this function shall immediately return the
 *  current streaming status. In particular, if a well running in-progress
 *  streaming was aborted by this function call, this function shall
 *  return NHT_SEC_STREAMING_NO_ERROR.
 *
 *  To wait on a streaming completion, please refer to function
 *  nhtSecWaitOnTransportSessionStreamingCompletion().
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/

TNhtSecTransportStreamingStatus nhtSecStopTransportSessionStreaming
(
  TTransportSessionId xTransportSessionId
);


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Close a transport session prevously opened using
 *   nhtSecOpenTransportSession().
 *
 *  @param[in] xTransportSessionId
 *              Identifier of the transport session to start playing.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function stops close a transport session previously
 *  opened (created) using nhtSecOpenTransportSession().
 *
 *  After closing a transport session, the associated TransportId
 *  value may recycled by the driver for over new potential transport
 *  session openings.
 *
 *  Important note:
 *    At normal or abnormal termination of an application, the driver
 *    implementation is responsible for implicitely closing all transport
 *    sessions that were opened by this application execution instance.
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/

TSecStatus nhtSecCloseTransportSession
(
  TTransportSessionId xTransportSessionId
);


/**
 *  @ingroup nht_transport_session
 *
 *  @brief
 *    Initialize the Initial value (IV) associated to a streamed
 *    cipher-session.
 *
 *  @param[in] xSession
 *              Identifier of the cipher stream session.
 *
 *  @param[in]  xKeyIdSize
 *    Size in bytes of the key ID (pxKeyId). If no key ID is required (e.g.
 *    RAM2RAM session), xKeyIdSize is set to 0.
 *
 *  @param[in]  pxKeyId
 *    Identifier of the key provided:
 *    - If no key ID is required (e.g. RAM2RAM session), pxKeyId is set to NULL.
 *    - The key ID is typically used for MPEG transport stream decryption session
 *      (i.e. stream session associated to EMI 0x00XX) and indicates the parity
 *      of the keys. In such a case, the function must consider the parity of
 *      the key ID as the parity of the key: for instance key ID = 0x00 => even
 *      key and key ID = 0x01 => odd key.
 *    - The key ID is also required to support key rotations with HLS (EMI
 *      0x4023) and MPEG/DASH (EMI 0x4024) standards. MPEG/DASH uses a key ID of
 *      16 bytes.
 *
 *  @param[in] xInitVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitVectorSize is set to zero.
 *
 *  @param[in] pxInitVector
 *    Buffer allocated by the caller containing the initialization vector (IV)
 *    required by CBC and CTR modes. These cipher modes of operation are part of
 *    the EMI definition. If no IV is required (e.g: ECB mode), this function
 *    might be called with pxInitVector is set to NULL.
 *    Normally the CTR mode requires a nonce and a counter that are then
 *    combined to produce the actual counter block encryption. In the current
 *    API the caller is in charge of providing the initial counter block instead
 *    of a nonce and a counter. This initial counter block is passed within
 *    pxInitVector buffer. The function TSecSessionDecrypt() is then in charge of
 *    incrementing the counter block of one unit for each block decryption.
 *
 *    The caller is in charge of providing a correct and consistent IV, even
 *    in case the data to be encrypted requires several calls to this function.
 *
 *  @retval   SEC_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   SEC_ERROR
 *              The function terminated abnormally.
 *              The intended operation failed.
 *
 *  This function allows the harness test application(s) to setup the very first
 *  IV that shall apply to a streamed cipher session associated to a transport
 *  stream. (e.g: CBC, CTR encryption/decryption mode).
 *
 *  This function only applies to cipher session associated to a transport session.
 *
 *  Introduction of this new function is mandatory in order:
 *  - To succcessfully pass NOCS harness test associated to EMIs having 'variable IV' defined.
 *  - To intialize the IV of SCR transport sessions.
 *
 *  The user application is responsible for having setup the EMI and keyring associated
 *  to the cipher session before setting up the IV. IV always refer to the last EMI that
 *  was set for this cipher session.
 *
 *  If an intial value is required, the user application is responsible for setting this
 *  intial value before starting to the play the stream.
 *
 *  PS: Calling this method is only mandatory for EMIs that require usage of IV.
 *
 *  This is a pure additional function associated to SEC harness test.\n
*/

TSecStatus nhtSecSetTransportSessionInitialValue
(
  TSecCipherSession     xSession,
  size_t                xKeyIdSize,
  TUnsignedInt8       * pxKeyId,
  size_t                xInitVectorSize,
  const TUnsignedInt8 * pxInitVector
);


#ifdef __cplusplus
}
#endif


#endif /* NHT_SEC_H */
