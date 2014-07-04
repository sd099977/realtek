/**
**  @file nv_nhtcsd.h
**
** @brief
**    RPC Chipset Security Driver specific API for NOCS Secure chipset harness tests
**
**    This header file describes the API of generic extensions for RPC server
**    related to CSD API v3.3.3.
**
**    Implementation of this API extension is provided by Nagra. Its usage
**    is reserved for the RPC server. Since RPC server implementation is provided
**    by Nagra, chipset manufacturer does not need to take care of this API
**    (A Nagra internal API).
**
**    This file is part of the Nagra CSD RPC server application delivery package.
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

#ifndef NV_NHT_CSD_H
#define NV_NHT_CSD_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "nocs_nhtcsd.h"
#include "inc/nhtcsd_r2r_test_algo.h"

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
 *  associated to CSD API harness test RPC server.
 *
 *  Implementation of the functions described in this API are generic, meaning
 *  that the implementation is not chipset manufacturer specific. As a
 *  concequence, their implementation is provided by Nagra.
 *
 *  This header file describes an API extensions of the CSD RPC server
 *  associated to CSD API v3.3.3 that are needed by the harness test
 *  RPC-based framework.
 *
 *  This is a pure Nagra internal API.
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


 /** @defgroup rpccsd_group CSD RPC server extended API */

 /** @defgroup rpc_nhtcsd_r2r R2R RPC extended API */

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    R2R session abstract handle type definition
*/
typedef void * TNhtCsdR2RSessionHandle;


/**
 *  @ingroup rpccsd_group
 *
 *  @brief
 *    Get the harness test CSD API version
 *
 *  @param[out]     pxNhtCsdApiVersion
 *                   32 bit value where the function has to write the CSD
 *                   driver API version using the macro NHT_CSD_TOOL_VERSION_INT.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the version of the harness test CSD API.
 *  Use the macro NHT_CSD_TOOL_VERSION_INT to assign the right value.
*/
TCsdStatus nhtCsdGetNhtCsdApiVersion
(
  TCsdUnsignedInt32*  pxNhtCsdApiVersion
);


/**
 *  @ingroup rpccsd_group
 *
 *  @brief
 *    Get the CSD status CM's specific offset value (CSD_STATUS_OFFSET)
 *
 *  @param[out]     pxCsdOffsetValue
 *                   32 bit value where the function has to write the CSD
 *                   driver API CSD_STATUS_OFFSET value.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the CSD status CM's specific offset value.
*/
TCsdStatus nhtCsdGetCsdStatusOffsetValue
(
  TCsdUnsignedInt32 * pxCsdOffsetValue
);


/**
 *  @ingroup rpccsd_group
 *
 *  @brief
 *    Get the protecting key number of the chipset
 *    key ladders.
 *
 *  @param[out]     pxProtectingKeyNumber
 *                   Key ladder Protecting key number to be setup.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function returns the Chipset key ladder protecting key number
 *  as defined in CSD API macro named 'CSD_SCR_NB_OF_PROTECTING_KEYS'
 *
*/
TCsdStatus nhtCsdGetCsdProtectingKeyNumber
(
  TCsdUnsignedInt32 * pxProtectingKeyNumber
);


/**
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    Open a R2R Key path handle and return an associated key
 *    path handle instance.
 *
 *  @param[out]     pxR2RSessionHandle
 *                   handle to R2R session that has been opene opened.
 *
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function dynamically allocates a R2R session and initialize it.
 *  In case of success, return an abstract R2R session handle.
 *
 *  Purpose of this function is to provide an abstract instanciation of
 *  a chipset manufacturer specific R2R key path structure. This function
 *  is introduced here in order to make the harness test ready for
 *  remote processing (RPC).
 *
 *  Implementation of this function is responsible to initialize the associated
 *  key path handle structure using the 'nhtCsdInitializeR2RKeyPathHandle()'
 *  function.
 *
*/
TCsdStatus nhtCsdOpenR2RSession
(
  TNhtCsdR2RSessionHandle * pxR2RSessionHandle
);


/**
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    Close a R2R Key path handle.
 *
 *  @param[in,out]  xR2RSessionHandle
 *                   R2R session handle.
 *
 *  @retval   CSD_NO_ERROR
 *              The intended operation was executed successfully.
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              pxCsdApiVersion parameter is invalid.
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *              The requested operation is not supported by the chipset.
 *  @retval   CSD_ERROR
 *              The function terminated abnormally. The intended operation
 *              failed.
 *
 *  This function closes a R2R key path handle and free the resource
 *  that was dynamically allocated using the 'nhtCsdOpenR2RKeyPathHandle()'
 *  function.
 *
 *  Purpose of this function is to provide an abstract instanciation of
 *  a chipset manufacturer specific R2R key path structure. This function
 *  is introduced here in order to make the harness test ready for
 *  remote processing (RPC).
 *
 *  Implementation of this function is responsible to initialize the key path
 *  handle structure using the 'nhtCsdInitializeR2RKeyPathHandle()' function.
 *
*/
TCsdStatus nhtCsdCloseR2RSession
(
  TNhtCsdR2RSessionHandle xR2RSessionHandle
);


/*!
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    Set the software key and used the encryption RAM2RAM Engine.
 *
 *  @param[in]      xAlgorithm
 *                   Algorithm to which the RAM2RAM Crypto Engine is requested
 *                   to operate.
 *  @param[in]      xMode
 *                   Cryptographic operation mode (ECB, CBC) which has to be used
 *                   by the RAM2RAM Crypto Engine is requested to operate.
 *  @param[in]      pxClearTextHostKey
 *                   Pointer to the location where the function has to read the
 *                   Clear Text Hostkey.
 *  @param[in]      xClearTextHostKeySize
 *                   Size in bytes of the Clear Text Hostkey.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to read the
 *                   Initialization Vector.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
 *  @param[in]      xRefreshIv
 *                   If TRUE, the CBC chaining register shall be loaded with the
 *                   value pointed by pxInitializationVector.
 *  @param[in,out]  xR2RSessionHandle
 *                   R2R session handle.
 *  @param[in]      pxInputData
 *                   Pointer to the location where the function has to read the
 *                   Input Data.
 *  @param[out]     pxOutputData
 *                   Pointer to the location where the function has to read the
 *                   Output Data.
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
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
 *  This extended function set the Clear Text Hostkey (software provided key)
 *  associated to a R2R session and request an encryption of data.
 *
 *  pxClearTextHostKey contains the Clear Text HostKey. The size of this key
 *  must be a 16-byte vector. In all other cases, the function shall return
 *  CSD_ERROR_INVALID_PARAMETERS.
 *
 *  xAlgorithm selects the cryptographic algorithm used to encrypt the data and
 *  xMode selects the operation mode (ECB, CBC) of the cryptographic
 *  algorithm.
 *
 *  If the cryptographic algorithm mode is set to CBC and xRefreshIv is set to
 *  TRUE, pxInitializationVector is used to initialize the CBC chaining register
 *  to the Ram2Ram Crypto Engine. Otherwise the CBC chaining register shall not
 *  be changed. The size of this vector depends on the cryptographic algorithm
 *  (16 bytes for AES and 8 bytes for TDES). In all other cases, the function
 *  shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  The size of the input data block must be a multiple of the data block size
 *  of the cryptographic algorithm that will be used to encrypt it. For
 *  instance, the size of the input data block must be a multiple of 8 bytes
 *  if it must be encrypted with the TDES algorithm or a multiple of 16 bytes if
 *  it must be encrypted with the AES algorithm. Otherwise, the function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If a valid cryptographic algorithm and/or an operation mode selected by the
 *  client software but the chipset does not support it, the function shall
 *  return CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If the client software selects a wrong R2R session handle, the function
 *  shall return CSD_ERROR_INVALID_KEY_PATH_HANDLE.
 *
   @note
 *    This function overwrites the use of the 'csdEncryptDataWithClearTextHostKey()'
 *    function defined in the base CSD API regarding the RPC service\n.
 *
 *    The use fo the CSD function named 'csdEncryptDataWithClearTextHostKey()'
 *    is deprecated when using this API.\n
 *    The implementation of this function shall implicitly make a call to the
 *    'csdEncryptDataWithClearTextHostKey()' CSD API underlaying function.
*/
TCsdStatus nhtCsdEncryptDataWithClearTextHostKey
(
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TNhtCsdR2RSessionHandle      xR2RSessionHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize
);

/*!
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    Set the software key and used the decryption RAM2RAM Engine.
 *
 *  @param[in]      xAlgorithm
 *                   Algorithm to which the RAM2RAM Crypto Engine is requested
 *                   to operate.
 *  @param[in]      xMode
 *                   Cryptographic operation mode (ECB, CBC) which has to be used
 *                   by the RAM2RAM Crypto Engine is requested to operate.
 *  @param[in]      pxClearTextHostKey
 *                   Pointer to the location where the function has to read the
 *                   Clear Text Hostkey.
 *  @param[in]      xClearTextHostKeySize
 *                   Size in bytes of the Clear Text Hostkey.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to read the
 *                   Initialization Vector.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
 *  @param[in]      xRefreshIv
 *                   If TRUE, the CBC chaining register shall be loaded with the
 *                   value pointed by pxInitializationVector.
 *  @param[in,out]  xR2RSessionHandle
 *                   R2R session handle.
 *  @param[in]      pxInputData
 *                   Pointer to the location where the function has to read the
 *                   Input Data.
 *  @param[out]      pxOutputData
 *                   Pointer to the location where the function has to read the
 *                   Output Data.
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
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
 *  This extended function set the Clear Text Hostkey (software provided key)
 *  associated to a R2R session and request an decryption of data.
 *
 *  pxClearTextHostKey contains the Clear Text HostKey. The size of this key
 *  must be a 16-byte vector. In all other cases, the function shall return
 *  CSD_ERROR_INVALID_PARAMETERS.
 *
 *  xAlgorithm selects the cryptographic algorithm used to decrypt the data and
 *  xMode selects the operation mode (ECB, CBC) of the cryptographic
 *  algorithm.
 *
 *  If the cryptographic algorithm mode is set to CBC and xRefreshIv is set to
 *  TRUE, pxInitializationVector is used to initialize the CBC chaining register
 *  to the Ram2Ram Crypto Engine. Otherwise the CBC chaining register shall not
 *  be changed. The size of this vector depends on the cryptographic algorithm
 *  (16 bytes for AES and 8 bytes for TDES). In all other cases, the function
 *  shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  The size of the input data block must be a multiple of the data block size
 *  of the cryptographic algorithm that will be used to decrypt it. For
 *  instance, the size of the input data block must be a multiple of 8 bytes
 *  if it must be decrypted with the TDES algorithm or a multiple of 16 bytes if
 *  it must be decrypted with the AES algorithm. Otherwise, the function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If a valid cryptographic algorithm and/or an operation mode selected by the
 *  client software but the chipset does not support it, the function shall
 *  return CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If the client software selects a wrong R2R session handle, the function
 *  shall return CSD_ERROR_INVALID_KEY_PATH_HANDLE.
 *
 * @note
 *    This function overwrites the use of the 'csdDecryptDataWithClearTextHostKey()'
 *    function defined in the base CSD API regarding the RPC service\n.
 *
 *    The use fo the CSD function named 'csdDecryptDataWithClearTextHostKey()'
 *    is deprecated when using this API.\n
 *    The implementation of this function shall implicitly make a call to the
 *    'csdDecryptDataWithClearTextHostKey()' CSD API underlaying function.
*/
TCsdStatus nhtCsdDecryptDataWithClearTextHostKey
(
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TNhtCsdR2RSessionHandle      xR2RSessionHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize
);


/*!
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    Set the secret key and used the encryption RAM2RAM Engine.
 *
 *  @param[in]      xAlgorithm
 *                   Algorithm to which the RAM2RAM Crypto Engine is requested
 *                   to operate.
 *  @param[in]      xMode
 *                   Cryptographic operation mode (ECB, CBC) which has to be used
 *                   by the RAM2RAM Crypto Engine is requested to operate.
 *  @param[in]      xProtectingKeyNumber
 *                   Number of protecting keys
 *  @param[in]      pxR2RCipheredProtectingKeys
 *                   Array of Ciphered Protecting Keys.
 *  @param[in]      pxCipheredContentKey
 *                   Pointer to the location where the function has to read the
 *                   Ciphered Content Key.
 *  @param[in]      xCipheredContentKeySize
 *                   Size in bytes of the Ciphered Content Key.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to read the
 *                   Initialization Vector.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
 *  @param[in]      xRefreshIv
 *                   If TRUE, the CBC chaining register shall be loaded with the
 *                   value pointed by pxInitializationVector.
 *  @param[in,out]  xR2RSessionHandle
 *                   R2R session handle.
 *  @param[in]      pxInputData
 *                   Pointer to the location where the function has to read the
 *                   Input Data.
 *  @param[out]      pxOutputData
 *                   Pointer to the location where the function has to read the
 *                   Output Data.
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
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
 *  This extended function set the the Secret Content Key (key ladder provided key)
 *  associated to a R2R session and request an encryption of data.
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
 *  'pxR2RCipheredProtectingKeys' array parameter structure and key ladder
 *  Key level values follows this rule (for 1 <= 'i' <= 'xProtectingKeyNumber',
 *  when 'i' is the protecting key level ):
 *
 *   - pxR2RCipheredProtectingKeys[xProtectingKeyNumber - 'i']   refer to Key Ladder KL<'i'> key
 *
 *  xAlgorithm selects the cryptographic algorithm used to encrypt the data and
 *  xMode selects the operation mode (ECB, CBC) of the cryptographic
 *  algorithm.
 *
 *  If the cryptographic algorithm mode is set to CBC and xRefreshIv is set to
 *  TRUE, pxInitializationVector is used to initialize the CBC chaining register
 *  to the Ram2Ram Crypto Engine. Otherwise the CBC chaining register shall not
 *  be changed. The size of this vector depends on the cryptographic algorithm
 *  (16 bytes for AES and 8 bytes for TDES). In all other cases, the function
 *  shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  The size of the input data block must be a multiple of the data block size
 *  of the cryptographic algorithm that will be used to decrypt it. For
 *  instance, the size of the input data block must be a multiple of 8 bytes
 *  if it must be encrypted with the TDES algorithm or a multiple of 16 bytes if
 *  it must be encrypted with the AES algorithm. Otherwise, the function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If a valid cryptographic algorithm and/or an operation mode selected by the
 *  client software but the chipset does not support it, the function shall
 *  return CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If the client software selects a R2R session handle, the function
 *  shall return CSD_ERROR_INVALID_KEY_PATH_HANDLE.
 *
 *  The implementation is responsible to ensure that this function can be
 *  called at any moment during a test R2R session life duration.
 *
 * @note
 *    This function overwrites the use of the 'csdEncryptDataWithSecretContentKey()'
 *    function defined in the base CSD API regarding the RPC service\n.
 *
 *    The use fo the CSD function named 'csdEncryptDataWithSecretContentKey()'
 *    is deprecated when using this API.\n
 *    The implementation of this function shall implicitly make a call to the
 *    'csdEncryptDataWithSecretContentKey()' CSD API underlaying function.
 *
*/
TCsdStatus nhtCsdEncryptDataWithSecretContentKey
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
        TCsdUnsignedInt32               xProtectingKeyNumber,
  const TNhtProtectingKey             * pxR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8              * pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8              * pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TNhtCsdR2RSessionHandle         xR2RSessionHandle,
  const TCsdUnsignedInt8              * pxInputData,
        TCsdUnsignedInt8              * pxOutputData,
        TCsdSize                        xDataSize
);


/*!
 *  @ingroup rpc_nhtcsd_r2r
 *
 *  @brief
 *    Set the secret key and used the decryption RAM2RAM Engine.
 *
 *  @param[in]      xAlgorithm
 *                   Algorithm to which the RAM2RAM Crypto Engine is requested
 *                   to operate.
 *  @param[in]      xMode
 *                   Cryptographic operation mode (ECB, CBC, etc) which has to be
 *                   used by the RAM2RAM Crypto engine is requested to operate.
 *  @param[in]      xProtectingKeyNumber
 *                   Number of protecting keys
 *  @param[in]      pxR2RCipheredProtectingKeys
 *                   Array of Ciphered Protecting Keys.
 *  @param[in]      pxCipheredContentKey
 *                   Pointer to the location where the function has to read the
 *                   Ciphered Content Key.
 *  @param[in]      xCipheredContentKeySize
 *                   Size in bytes of the Ciphered Content Key.
 *  @param[in]      pxCipheredContentKey
 *                   Pointer to the location where the function has to read the
 *                   Ciphered Content Key.
 *  @param[in]      xCipheredContentKeySize
 *                   Size in bytes of the Ciphered Content Key.
 *  @param[in]      pxInitializationVector
 *                   Pointer to the location where the function has to read the
 *                   Initialization Vector.
 *  @param[in]      xInitializationVectorSize
 *                   Size in bytes of the Initialization Vector.
 *  @param[in]      xRefreshIv
 *                   If TRUE, the CBC chaining register shall be loaded with the
 *                   value pointed by pxInitializationVector.
 *  @param[in,out]  xR2RSessionHandle
 *                   R2R session handle.
 *  @param[in]      pxInputData
 *                   Pointer to the location where the function has to read the
 *                   Input Data.
 *  @param[out]      pxOutputData
 *                   Pointer to the location where the function has to read the
 *                   Output Data.
 *  @param[in]      xDataSize
 *                   Size in bytes of the Data.
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
 *  This extended function set the the Secret Content Key (key ladder provided key)
 *  associated to a R2R session and request a decryption of data.
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
 *  'pxR2RCipheredProtectingKeys' array parameter structure and key ladder
 *  Key level values follows this rule (for 1 <= 'i' <= 'xProtectingKeyNumber',
 *  when 'i' is the protecting key level ):
 *
 *   - pxR2RCipheredProtectingKeys[xProtectingKeyNumber - 'i']   refer to Key Ladder KL<'i'> key
 *
 *  xAlgorithm selects the cryptographic algorithm used to decrypt the data and
 *  xMode selects the operation mode (ECB, CBC) of the cryptographic
 *  algorithm.
 *
 *  If the cryptographic algorithm mode is set to CBC and xRefreshIv is set to
 *  TRUE, pxInitializationVector is used to initialize the CBC chaining register
 *  to the Ram2Ram Crypto Engine. Otherwise the CBC chaining register shall not
 *  be changed. The size of this vector depends on the cryptographic algorithm
 *  (16 bytes for AES and 8 bytes for TDES). In all other cases, the function
 *  shall return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  The size of the input data block must be a multiple of the data block size
 *  of the cryptographic algorithm that will be used to decrypt it. For
 *  instance, the size of the input data block must be a multiple of 8 bytes
 *  if it must be decrypted with the TDES algorithm or a multiple of 16 bytes if
 *  it must be decrypted with the AES algorithm. Otherwise, the function shall
 *  return CSD_ERROR_INVALID_PARAMETERS.
 *
 *  If a valid cryptographic algorithm and/or an operation mode selected by the
 *  client software but the chipset does not support it, the function shall
 *  return CSD_ERROR_OPERATION_NOT_SUPPORTED.
 *
 *  If the client software selects a wrong R2R session handle, the function
 *  shall return CSD_ERROR_INVALID_KEY_PATH_HANDLE.
 *
 *  The implementation is responsible to ensure that this function can be
 *  called at any moment during a test R2R session life duration.
 *
 * @note
 *    This function overwrites the use of the 'csdDecryptDataWithSecretContentKey()'
 *    function defined in the base CSD API regarding the RPC service\n.
 *
 *    The use fo the CSD function named 'csdDecryptDataWithSecretContentKey()'
 *    is deprecated when using this API.\n
 *    The implementation of this function shall implicitly make a call to the
 *    'csdDecryptDataWithSecretContentKey()' CSD API underlaying function.
 *
*/
TCsdStatus nhtCsdDecryptDataWithSecretContentKey
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
        TCsdUnsignedInt32               xProtectingKeyNumber,
  const TNhtProtectingKey             * pxR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8              * pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8              * pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TNhtCsdR2RSessionHandle         xR2RSessionHandle,
  const TCsdUnsignedInt8              * pxInputData,
        TCsdUnsignedInt8              * pxOutputData,
        TCsdSize                        xDataSize
);


/*!
 *  @ingroup rpc_nhtcsd_r2r
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
TCsdStatus nhtcsd_r2r_monteCarlo_test_run (
  const TNhtCsd_r2r_test_algoParams * pxInputParams,
  TCsdUnsignedInt8                  * pxOutputData );


#ifdef __cplusplus
}
#endif

#endif /* NV_NHT_CSD_H */
