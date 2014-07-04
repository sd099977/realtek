/**
**  @file ca_sec.h
**
**  @brief
**   Secure Chipset management.
**
**   This file specifies the Secure Chipset API that allows Nagra CA
**   software to access security features of the MPEG chipset.
**
**  $Id: //CAK/components/secapi/MAIN/src/ca_sec.h#4 $
**
*/
/*
** REMARK:
**   Comments in this file use special tags to allow automatic API documentation
**   generation in HTML format, using the GNU-General Public Licensed Doxygen
**   tool. For more information about Doxygen, please check www.doxygen.org
**
**   Depending on the platform, the CHM file may not open properly if it is stored on a network drive.
**   So either the file should be moved on a local drive or add the following registry entry on
**   Windows platform (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/


#ifndef CA_SEC_H
#define CA_SEC_H

/**
 * Defines the version number of the SEC API. This version has to be included in
 * the function table returned by secGetFunctionTable(). To do so, use the macro
 * #SECAPI_VERSION_INT to put it in the right format.
*/
#define SECAPI_VERSION_MAJOR  5
#define SECAPI_VERSION_MEDIUM 1
#define SECAPI_VERSION_MINOR  1

/** @page p_history Changes history
 *
 *  - <b> 5.1.1 - 11-Jan-2013 </b>
 *    - Added secChipReset()
 *    - Clarified usage of SHA and HMAC context
 *    - Clarified management of buffers and forced usage of TSecAllocateBuffer()
 *      for RAM2RAM and digest functions.
 *    - Defined keySize parameter values for elliptic curves to be supported
 *    - Removed unwanted const qualifier on TSecFreeBuffer()
 *    - Clarified error management on inconsistent key ID and metadata parameters 
 *  .
 *  - <b> 5.0.1 - 27-Sep-2012 </b>
 *    - Added support for stream processing
 *    - Replaced key parity by key ID in all secSetXxxKey functions
 *    - Added TSecAllocateBuffer() and TSecFreeBuffer() to comply with DMA
 *      buffer constraints.
 *    - Added support of RAM2RAM in-place operations
 *    - Added TSecUseLegacyKey() for specific DRM use case
 *  .
 *  - <b> 4.1.0 - 04-May-2012 </b>
 *    - Added TSecUseFlashProtKey() and TSecEncryptFlashProtKey()
 *  .
 *  - <b> 4.0.3 - 16-Mar-2012 </b>
 *    - Clarified elliptic curves to be supported and domain parameters size.
 *    - Clarified the list of EMIs to be supported
 *  .
 *  - <b> 4.0.2 - 22-Feb-2012 </b>
 *    - Added global overview
 *    - Using CRT parameters instead of d to define an RSA private key
 *    - Added function to compute CRT parameters dP, dQ and qInv from p, q and e.
 *    - Changed ECDSA signature output format to return explicitely return r and
 *      s components.
 *    - Changed TSecEcdhComputeKey() in order to consider the shared secret as
 *      the X-coordinates of the computed point.
 *    - Added support of SHA-384
 *    - Clarified RAM2RAM use cases to be supported. In particular it should
 *      be possible to change the key within the same RAM2RAM session.
 *    - Corrected description of #SEC_ERROR_BAD_PARAMETER on TSecSessionEncrypt()
 *      and TSecSessionDecrypt().
 *    - Corrected few typos
 *  .
 *  - <b> 3.1.0 - 31-Oct-2011 </b>
 *    - Removed support of DES
*/

/******************************************************************************/
/*                                                                            */
/*                               INCLUDE FILES                                */
/*                                                                            */
/******************************************************************************/

#ifdef SEC_WRAP_2_1
#include "sec_2_1w.h"
#endif

#ifdef SEC_GLUE_2_1
#include "sec_2_1g.h"
#endif

#include "ca_defs.h"
#include "ca_defsx.h"


/******************************************************************************/
/*                                                                            */
/*                             OVERALL DOCUMENTATION                          */
/*                                                                            */
/******************************************************************************/

/** @mainpage Overview
 *  - @subpage p_history
 *  - @subpage p_preface
 *  - @subpage p_sw_stack
 *  - @subpage p_fct_table
 *  - @subpage p_thread_safety
 *  - @subpage p_bignum
 *  - @subpage p_buffer
 *  - @subpage p_key_sizes
 *  - @subpage p_block_cipher
 *  - @subpage p_ec
 *  - @subpage p_flash_prot
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

/* -------------------------------------------------------------------------- */

/** @page p_preface Preface
 *  <h2>Objectives</h2>
 *  This document specifies the Secure Chipset API that gives access to Nagra 
 *  security features of the MPEG chipset.
 *  
 *  It includes standard cryptographic functions such as symmetric block ciphers 
 *  (TDES, AES), asymmetric cryptographic functions (RSA, Diffie-Hellman) as 
 *  well as digest functions (SHA, HMAC). Cryptographic operations are based on 
 *  cleartext keys, secret keys protected by hardware key ladders or secret keys 
 *  protected by the Nagra custom hardware block (CERT IP block).
 *  
 *  Cryptographic functions are intended to be interfaced with hardware 
 *  accelerators to achieve better performances.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for developers in charge of implementing the SEC
 *  API and as well as developers that intend to use the SEC API in their
 *  application.
 *
 * <hr><h2>References</h2>
 *  - [EMI] Nagravision, System Architecture, Encryption Method Indicator
 *    Specification, Version 1.0.7\n
 *  - [NOCS3REQ] Nagravision, NOCS3.0 Security Requirements Specification\n
 *  - [FIPS186-3] Digital Signature Standard (DSS),
 *    http://csrc.nist.gov/publications/fips/fips186-3/fips_186-3.pdf
 *  - [FIPS46-3] Data Encryption Standard (DES),
 *    http://csrc.nist.gov/publications/fips/fips46-3/fips46-3.pdf
 *  - [DTCP-IP] DTCP Volume 1 Supplement E, http://www.dtcp.com/specifications.aspx
 *  - [NSA_ECDH] Suite B Implementer's Guide to NIST SP 800-56A,
 *    http://www.nsa.gov/ia/_files/SuiteB_Implementer_G-113808.pdf
 *  - [NSA_ECDSA] Suite B Implementer's Guide to FIPS 186-3 (ECDSA),
 *    http://www.nsa.gov/ia/_files/ecdsa.pdf
 *  - [SEC2] SEC 2 - Recommended Elliptic Curve Domain Parameters,
 *    http://www.secg.org/download/aid-386/sec2_final.pdf
 *  - [META] Nagravision, CAK, Metadata Format Specification, Version 1.4.x or
 *    higher
*/

/* -------------------------------------------------------------------------- */

/** @page p_sw_stack Software stack context
 *  The figure below depicts the context of the SEC component.
 *  @image html os_sw_stack.png
 *  @image rtf os_sw_stack.png
 *
 *  The SoC vendor is in charge of providing a reference implementation of the 
 *  SEC API to the STB manufacturer. A reference implementation of the CERT API 
 *  is also provided in case of NOCS3 chipset. The STB manufacturer has the 
 *  responsibility of the final implementation of these API on its hardware 
 *  platform. In particular, the STB manufacturer may need to modify the 
 *  reference implementation in order to control and manage hardware resource 
 *  allocation conflicts. 
 *
 *  It has to be noted that the support of stream encryption/decryption sessions 
 *  is usually strongly related to the middleware. Thus the SoC vendor will very 
 *  likely provide a basic reference implementation of this feature that will 
 *  have to be completed by the STB manufacturer or middleware provider.
 *
 *  The usage of the SEC API is not restricted to CA applications. It may be used
 *  by any application that would like to take benefit from these accelerated
 *  cryptographic primitives. As a result, implementation of the SEC API must be
 *  thread safe and reentrant.
 *
 *  The corollary is that the SEC API may be used only if the operating system is
 *  up and running. Thus it cannot be used during the secure boot phase. Access
 *  to cryptographic accelerators during the system boot is achieved through the
 *  <i>Bare Security Driver</i> (BSD). Refer to the documentation of this API
 *  for further information.
 *
*/

/* -------------------------------------------------------------------------- */

/** @page p_fct_table Function table
 *
 *  Functions of the SEC API are exposed to applications through a table of
 *  callback functions retrieved through a call to secGetFunctionTable().
 *
 *  The table also contains the version number of the implemented SEC API. It is 
 *  strongly recommended to use the macro #SECAPI_VERSION_INT to assign the 
 *  correct version number in the function table.
 *
 *  Functions that were defined before the introduction of the function table
 *  concept are kept for backward compatibility. However, they are also
 *  redefined as callback and inserted in the function table.
 *
 *  The list of functions to be implemented on the final product depends on the 
 *  version of the CAS integrated.  A \c NULL pointer has to be set in the 
 *  function table for each function that is not implemented.
*/

/* -------------------------------------------------------------------------- */

/** @page p_thread_safety Thread safety, reentrancy and mutual exclusion
 *
 *  The SEC API may be used by several software components running in different
 *  threads or processes. Thus, implementation of all functions of the SEC API
 *  must be thread safe and reentrant to manage concurrent access from different
 *  threads or processes.
 *
 *  If functions called concurrently from different threads or processes are
 *  accessing shared resources, the SEC API implementation must guarantee the
 *  mutual exclusion and serialize access to these resources.
 *
 *  Depending on the operating system architecture, inter-process communication
 *  (IPC) methods might be required to achieve the mutual exclusion.
 *
 *  On the other hand, a function may be called concurrently from different 
 *  threads or processes without sharing the same resource. For instance 
 *  TSecSessionEncrypt() may be called from two processes at the same time and 
 *  requires respectively an AES block cipher and TDES block cipher. This case 
 *  illustrates the reentrancy requirement.
*/ 

/* -------------------------------------------------------------------------- */

/** @page p_bignum Big numbers
 *
 *  Asymmetric cryptographic functions mainly consist in big numbers arithmetic
 *  calculations. SEC API functions use byte array buffers for passing in and
 *  out big number parameters. These buffers are always allocated by the caller
 *  and have a size that usually depends on the key size.
 *
 *  Big numbers are stored in byte array buffers in big endian format (MSBF). If
 *  the effective size of a number is smaller than the buffer size, it must be
 *  padded with leading zeros to match the buffer size.
 *
 *  The caller is also responsible to allocate buffers containing input messages
 *  to operate on as well as buffers to store output messages. Refer to \ref 
 *  p_buffer for special considerations about these allocations.
*/


/** @page p_buffer Buffers allocations management
 *
 *    Hardware cryptoprocessors may require special buffers (e.g. contiguous 
 *    pages in physical memory, limited address space, pages alignment, etc) to 
 *    work properly. TSecAllocateBuffer() and TSecFreeBuffer() are designed to 
 *    handle such buffers.
 *    
 *    Although many SEC API functions parameters are defined as byte array 
 *    buffers, it has been decided to force the usage of TSecAllocateBuffer() only 
 *    for RAM2RAM input/output messages and digest input messages. This choice 
 *    is motivated by the fact that these buffers can be relatively large. Thus 
 *    allocating these buffers directly in the right format avoids memory 
 *    reallocation and memory copies at the driver level.
 *    
 *    For all other parameters, the client can use standard memory allocation 
 *    functions or declare them on the stack or as static variables. The driver  
 *    is in charge of converting these parameters to the right format if required.
 *
 *    These considerations do not apply to secEncryptData() and 
 *    secDecryptData() functions, because of backward compatibility with older 
 *    client applications.
*/

/* -------------------------------------------------------------------------- */

/** @page p_key_sizes Key sizes range
 *
 *  The following table gives a summary of the cryptographic algorithms and
 *  maximum key size to be supported:
 *
 *  <table class="doxtable">
 *  <tr>
 *  <th>Algorithm</th><th>Key size range (bits)</th><th>Remarks</th></tr>
 *  <tr>
 *  <td>AES</td><td>128</td> <td>Although the API is designed to support
 *  different key sizes, it is not required to support AES keys of 192 and 256
 *  bits.</td> </tr>
 *  <tr>
 *  <td>Triple DES</td><td>2*64=128</td><td>Keying option 2 (K1=K3) is required
 *  only</td></tr>
 *  <tr>
 *  <td>RSA</td><td>[512..2048]</td><td>RSA implementation must support key size
 *  multiple of 64 bits from 512 bits to 2048 bits.</td></tr>
 *  <tr>
 *  <td>Diffie-Hellman</td> <td>[512..2048]</td> <td>DH implementation must
 *  support key size multiple of 64 bits from 512 bits to 2048 bits</td> </tr>
 *  <tr>
 *  <td>Elliptic Curve</td> <td>[160..384]</td> <td>ECDSA and ECDH must support
 *  prime curves of 160, 224, 256 and 384 bits.</td></tr>
 *  </table>
*/

/* ========================================================================== */

/** @page p_block_cipher Block Ciphers
 *
 *  - @subpage p_emi
 *  - @subpage p_tdes_key
 *  - @subpage p_keyladders
 *  - @subpage p_r2r_session
 *  - @subpage p_stream_session
 *  - @subpage p_key_set_strategy
 *  - @subpage p_bc_use_cases
*/

/* -------------------------------------------------------------------------- */

/** @page p_emi Encryption Method Indicator (EMI)
 *
 *  <h2>Introduction</h2>
 *  There are many ways to encrypt data. An encryption algorithm (like AES,
 *  TDES, ...) with optionally its associated mode of operation (like ECB, CBC
 *  or CTR, ...) has, of course, to be chosen but this is often not enough to
 *  specify unequivocally an encryption method. Indeed, some less obvious
 *  information like data handling and key formats have also to be well defined
 *  if interoperability between different platforms shall be ensured. Moreover
 *  it is impossible to build a pre-defined exhaustive list of parameters
 *  qualifying explicitly each Encryption Method because the parameters needed
 *  could be specific to a given Encryption Method only.
 *
 *  Therefore, in order to deal with this complexity and to have a mean to
 *  uniquely identify the way data are encrypted/decrypted, Nagravision
 *  allocates a unique 16-bits identifier, referred to as EMI, to all referenced
 *  Encryption Methods (see [EMI]). Each Encryption Method identified by its EMI
 *  has a dedicated detailed specification. That specification might either be
 *  an international standard or a Nagravision specification.
 *  
 *  <hr><h2>RAM2RAM Operations</h2>
 *  EMIs to be supported depend on their usage. For RAM2RAM operations, the SEC 
 *  driver must support all standard EMIs, except MPEG TS EMIs, that  is to say 
 *  all EMIs having the most significant byte equal to 0x40. Moreover, in this 
 *  context the driver only needs to care about the algorithm and chaining mode. 
 *  For instance if the MPEG/DASH EMI 0x4024 is provided to a RAM2RAM session, 
 *  the SEC driver must only take into account the AES algorithm and CTR 
 *  chaining mode and does not need to support the full MPEG/DASH stack. So from 
 *  this standpoint, EMIs 0x4024 and 0x4027 are strictly identical.
 *  
 *  The following table gives a summary of the cryptographic algorithms and 
 *  chaining modes to be supported by RAM2RAM sessions along with their 
 *  corresponding EMIs.
 *
 *  <table class="doxtable">
 *  <tr>
 *  <th>Algorithm</th><th>EMI [hex]</th></tr>
 *  <tr>
 *  <td>AES-128-ECB</td><td>4021</td></tr>
 *  <tr>
 *  <td>AES-128-CBC</td><td>4020, 4022, 4023, 4026</td></tr>
 *  <tr>
 *  <td>AES-128-CTR</td><td>4024, 4027</td></tr>
 *  <tr>
 *  <td>TDES-128-ECB</td><td>4041</td></tr>
 *  <tr>
 *  <td>TDES-128-CBC</td><td>4040, 4043</td></tr>
 *  </table>
 *  \n
 *
 *  <hr><h2>Stream Processing Operations</h2>
 *  Stream processing operations requires all EMIs 0x00xx (MPEG TS EMIs) and all
 *  EMIs 0x40xx to be supported. Moreover, unlike RAM2RAM operations, the SEC driver
 *  must not only focus on the algorithm and chaining mode, but is also responsible
 *  for managing the streams to operate on. Indeed, the SEC client is limited to
 *  providing a key and a reference to the streams (transport session ID).
 *
*/

/* -------------------------------------------------------------------------- */

/** @page p_tdes_key TDES key format
 *
 *  TDES operations use a 128-bit input key. Actually this key is broken down in
 *  two 64-bit keys K1 and K2 complying with the Keying Option 2 of FIPS PUB
 *  46-3. K1=K3 corresponds to the 8 most significant bytes of the 128-bit input
 *  key while K2 corresponds to the 8 least significant bytes as depicted in the
 *  figure below.
 *  @image html tdes_key_format.png
 *  @image rtf tdes_key_format.png
*/

/* -------------------------------------------------------------------------- */

/**  @page p_keyladders Key ladders and crypto-engine
 *
 *  A Block Cipher (also known as Crypto-Engine) encrypts/decrypts bulk data
 *  with a symmetric key, called hereafter Content Key.
 *
 *  The content key provided to the block cipher may come from different sources
 *  and may be protected by a key ladder. Following sections describes the
 *  different means to provide this content key to the block cipher.
 *
 *  A key ladder is based on a secret root key (RK) that is never available in 
 *  clear-text form outside of the chipset secure crypto-environment. In the 
 *  same way, the content key path between the output of a key ladder and the 
 *  input of a crypto-engine is also strongly protected to avoid exposing the 
 *  content key in in clear-text form.
 *
 *  <hr>@section s_bc_clearkey Clear-text content key
 *  A crypto engine may be fed with a clear-text content key. This is achieved by
 *  calling the SEC API function TSecSetClearTextKey(). The cryptographic
 *  algorithm of the crypto engine is selected by the caller through the EMI
 *  parameter.
 *  @image html bc_cleartext_key.png
 *  @image rtf bc_cleartext_key.png
 *
 *
 *  <hr>@section s_bc_rootkey Content key protected with root key
 *  A crypto engine may be fed with a root key derived from the Nagra secret.
 *  This is the use case supported by NOCS1.x devices and is achieved by calling
 *  SEC API functions secEncryptData() and secDecryptData(). These functions do
 *  not have any parameter, thus the choice of the root key and cryptographic
 *  algorithm is implicit and fixed to TDES.
 *  @image html bc_root_key.png
 *  @image rtf bc_root_key.png
 *
 *  <hr>@section s_bc_0kl_prot Content key protected with 0-level key ladder
 *  A crypto engine may be fed with a content key protected by a 0-level key
 *  ladder (key ladder made of 1 key ladder element). This is achieved by 
 *  calling the SEC API function TSecSet0LevelProtectedKey().
 *  @image html bc_0kl_prot_key.png
 *  @image rtf bc_0kl_prot_key.png
 *
 *  <hr>@section s_bc_1kl_prot Content key protected with 1-level key ladder
 *  A crypto engine may be fed with a content key protected by a 1-level key
 *  ladder (key ladder made of 2 key ladder elements). This is achieved by 
 *  calling the SEC API function TSecSet1LevelProtectedKey().
 *  @image html bc_1kl_prot_key.png
 *  @image rtf bc_1kl_prot_key.png
 *
 *  <hr>@section s_bc_2kl_prot Content key protected with 2-level key ladder
 *  A crypto engine may be fed with a content key protected by a 2-level key
 *  ladder (key ladder made of 3 key ladder elements). This is achieved by 
 *  calling the SEC API function TSecSet2LevelProtectedKey().
 *  @image html bc_2kl_prot_key.png
 *  @image rtf bc_2kl_prot_key.png
 *
 *  The cryptographic algorithm of the crypto engine is selected by the caller
 *  through the EMI parameter. This EMI has nothing to do with the cryptographic
 *  algorithm used in internal stages of a key ladder. Indeed, this latter
 *  algorithm is fixed to TDES-1 keying option 2 and cannot be changed by the
 *  caller.
 *
 *  <hr>@section s_bc_certkey Content key coming from CERT block
 *  A block cipher may be fed with a content key coming from the Nagra CERT
 *  block. This is achieved by calling the function TSecUseCertKey(). The
 *  cryptographic algorithm of the crypto engine is selected by the caller
 *  through the EMI parameter.
 *  @image html bc_cert_key.png
 *  @image rtf bc_cert_key.png
 */

/* ========================================================================== */

/** @page p_r2r_session RAM2RAM
 *
 *  - @subpage p_r2r_overview
 *  - @subpage p_r2r_inplace
 *  - @subpage p_r2r_fct_list
 *  - @subpage p_r2r_basic_scenario
*/

/* -------------------------------------------------------------------------- */

/** @page p_r2r_overview Overview
 *  
 *  The following figure describes how a crypto-engine is used in the context
 *  of a RAM2RAM session. It mainly shows that the SEC client is providing the
 *  key and the input and output buffers.
 *
 *  @image html "RAM2RAM overview.png"
 *  @image rtf "RAM2RAM overview.png"
*/

/* -------------------------------------------------------------------------- */

/** @page p_r2r_inplace In-place operations
 *  
 *    RAM2RAM crypto-engine must support in-place encryption/decryption
 *    operations in order to achieve better performance and save memory 
 *    allocations. In-place operations are enabled by providing the same input
 *    and output buffer (pxInput=pxOutput) to encryption/decryption functions.
 *  
*/

/* -------------------------------------------------------------------------- */

/** @page p_r2r_fct_list Function list
 *  
 *  The functions related to a RAM2RAM session are the following:
 *
 *  - TSecEncryptData()
 *  - TSecDecryptData()
 *  - TSecOpenRam2RamEncryptSession()
 *  - TSecOpenRam2RamDecryptSession()
 *  - TSecCloseSession()
 *  - TSecSetClearTextKey()
 *  - TSecSet2LevelProtectedKey()
 *  - TSecUseCertKey()
 *  - TSecUseFlashProtKey()
 *  - TSecSessionEncrypt()
 *  - TSecSessionDecrypt()
 *  - TSecAllocateBuffer()
 *  - TSecFreeBuffer()
 *
*/

/* -------------------------------------------------------------------------- */

/** @page p_r2r_basic_scenario Basic scenarios
 *  
 *  @section s_r2r_basic_use Encryption with clear-text key
 *  This figure shows a typical RAM2RAM encryption with a cleartext key.
 *  @image html bc_r2r_basic_use.png
 *  @image rtf bc_r2r_basic_use.png
 *
 *  <hr>@section s_r2r_cert_use Encryption with a CERT key
 *  This figure describes a RAM2RAM scenario with a key coming from the CERT block. 
 *  @image html bc_r2r_cert_use.png
 *  @image rtf bc_r2r_cert_use.png
 *  
 *  <hr>@section s_r2r_change_emi Changing the EMI during a RAM2RAM session
 *  This figure illustrates a case where the EMI is changed during a given
 *  session.
 *  @image html change_emi_session.png
 *  @image rtf change_emi_session.png
 *
 *  <hr>@section s_r2r_change_key Changing the key during a RAM2RAM session
 *  This figure illustrates a case where the key protection is updated during
 *  a given session.
 *  @image html change_key_session.png
 *  @image rtf change_key_session.png
*/

/* ========================================================================== */

/** @page p_stream_session Stream Processing
 *
 *  - @subpage p_stream_overview
 *  - @subpage p_tsid
 *  - @subpage p_stream_fct_list
 *  - @subpage p_stream_basic_scenario
*/

/* -------------------------------------------------------------------------- */

/** @page p_stream_overview Overview
 *
 *  The support of stream processing sessions has been introduced in the SEC API 
 *  to replace former DSC API and SCR API. The main advantage of this merge is a 
 *  single entry point the key management of required by the 
 *  encryption/decryption of media streams.
 *
 *  A SEC stream encryption session specifies the set of hardware resources 
 *  needed for locally encrypting a certain media stream. Similarly, a SEC 
 *  stream decryption session specifies the set of hardware resources needed to 
 *  decrypt locally a certain media stream. Media streams are identified in this 
 *  API by means of \ref p_tsid "Transport Session Identifiers". The STB 
 *  software is in charge of managing hardware resource allocation and the 
 *  mapping of media streams to SEC stream encryption and decryption sessions. A 
 *  typical application of stream encryption and decryption sessions is DVR 
 *  recording and playback sessions respectively.
 *
 *  The SEC client (CA software) is in charge of providing content keys to 
 *  successfully encrypt/decrypt media streams referenced by a transport session 
 *  ID.
 *  
 *  Content keys may be provided in clear-text form, protected by a chipset key 
 *  ladder or protected by the Nagra CERT IP block. SEC stream processing 
 *  sessions may also be used in a "legacy mode"; in this case, the content key 
 *  is directly handled by the SEC driver implementation.
 *
 *  The following diagram describes how a crypto-engine is used in the context
 *  of a stream processing session.
 *  @image html "Stream processing overview.png"
 *  @image rtf "Stream processing overview.png"
 *
*/

/* -------------------------------------------------------------------------- */

/** @page p_tsid Transport Session ID
 *
 *  Today's decoders may have various stream sources (satellite tuner, broadband 
 *  connection, terrestrial tuner, external hard drive) and several destinations 
 *  (TV output 1, TV output 2, hard drive, Ethernet port, etc.). A media stream 
 *  flowing from a source to a destination traverses a series of processing 
 *  elements such as MPEG2 demultiplexing, DVB-CSA descrambling, MPEG2 video/audio 
 *  decoding, and so on. The chipset crypto-engine is one of such processing 
 *  element. Figure below illustrates three different transport sessions, 
 *  connecting various sources, stream processing elements and destinations.
 *  @image html tsid_overview.png
 *  @image rtf tsid_overview.png
 *  
 *  A certain number of hardware resources are allocated in the decoder in order 
 *  to support this processing chain for that particular media stream. We will 
 *  denote the set of resources allocated to a certain media stream as a 
 *  transport session or simply a pipe. Each transport session is identified 
 *  uniquely by means of a so called transport session identifier (TSID).
 *
 *  Figure below illustrates an example of a live A/V stream that is being 
 *  recorded on the hard drive and a live A/V stream that is decoded and 
 *  presented on the TV screen. 
 *
 *  @image html tsid_usecase.png
 *  @image rtf tsid_usecase.png
 *
 *  In that example, two stream decryption sessions are opened with a 
 *  dedicated transport session identifier:
 *
 *  a) The first transport session is defined for descrambling the live content 
 *  to be stored on the hard drive. Note that two crypto-engine elements are 
 *  required in this case: one for descrambling the live content and another one 
 *  for re-scrambling it with another key before storing it on the hard drive.
 *  
 *  b) A second transport session is defined  for descrambling the live content 
 *  to be presented on the TV screen.
 *
 *  Each crypto-engine element of a transport session requires a dedicated SEC 
 *  API stream session (encryption or decryption) - see 
 *  TSecOpenStreamEncryptSession() and TSecOpenStreamDecryptSession().
 *  
 *  The transport session ID is the main criteria to attach a SEC stream session 
 *  to a crypto-engine element. However this criteria is not always sufficient. 
 *  In the use case above, two SEC sessions are opened with the transport 
 *  session ID 1. In this case, the SEC driver is in charge of associating the 
 *  SEC stream decryption session to the first crypto-engine element and the SEC 
 *  stream encryption session to the second crypto-engine element.
 *  
 *  Depending on the complexity of the use case to achieve, the cryptographic 
 *  algorithm (identified by an EMI) may be another criteria, in addition to the 
 *  transport session ID, to link the right SEC session to the right 
 *  crypto-engine element.
*/

/* -------------------------------------------------------------------------- */

/** @page p_stream_fct_list Function list
 *
 *  The functions related to a stream processing session are the following:
 *
 *  - TSecOpenStreamEncryptSession()
 *  - TSecOpenStreamDecryptSession()
 *  - TSecCloseSession()
 *  - TSecSetClearTextKey()
 *  - TSecSet0LevelProtectedKey()
 *  - TSecSet1LevelProtectedKey()
 *  - TSecSet2LevelProtectedKey()
 *  - TSecUseCertKey()
 *  - TSecSetMetadata()
 *  - TSecUseLegacyKey()
*/

/* -------------------------------------------------------------------------- */

/** @page p_stream_basic_scenario Basic scenarios
 *  
 *  @section s_stream_basic_mpeg2ts MPEG-2 TS descrambling
 *  This figure shows a typical stream processing usage to descramble an MPEG-2
 *  TS program. In this particular case, odd and even keys are provided in 
 *  clear-text form. The same scenario could apply with key ladder protected keys.
 *  @image html "Basic MPEG-2 descrambling.png"
 *  @image rtf "Basic MPEG-2 descrambling.png"
 *  
 *  <hr>@section s_stream_basic_record DVR recording
 *  This figure describes the sequence for a DVR recording session.
 *  @image html "Basic DVR recording.png"
 *  @image rtf "Basic DVR recording.png"
 *  
 *  <hr>@section s_stream_basic_playback DVR playback
 *  This figure describes the sequence for a DVR playback session.
 *  @image html "Basic DVR playback.png"
 *  @image rtf "Basic DVR playback.png"
 *  
 *  <hr>@section s_stream_basic_legacy DVR playback with legacy key
 *  This figure describes the sequence for a DVR playback session with the
 *  legacy key.
 *  @image html "Basic legacy key.png"
 *  @image rtf "Basic legacy key.png"
 *
*/

/* ========================================================================== */

/** @page p_key_set_strategy Setting keys in crypto-engine key table
 *
 *  The following figure describes how the way to set a key in the key table of 
 *  a crypto-engine is influenced by the type of session (RAM2RAM or stream), 
 *  the EMI and the KeyID.
 *
 *  One can see, for instance, that the KeyID is completely ignored in case of 
 *  a RAM2RAM session.
 *
 *  @image html "Crypto engine allocation strategy.png"
 *  @image rtf "Crypto engine allocation strategy.png"
 *
*/

/* -------------------------------------------------------------------------- */

/** @page p_bc_use_cases Use cases
 *  @section s_stream_full_mpeg2ts Descrambling an MPEG-2 TS stream
 *  This figure illustrates the descrambling of an MPEG-2 TS stream
 *  @image html "Full MPEG-2 descrambling.png"
 *  @image rtf "Full MPEG-2 descrambling.png"
 *
 *  <hr>@section s_stream_adaptive_streaming Adaptive streaming descrambling with key rotation
 *  This figure illustrates the adaptive streaming descrambling use case (e.g. HLS or MPEG/DASH)
 *  with key rotation support.
 *  @image html "Adaptive streaming descrambling with key rotation.png"
 *  @image rtf "Adaptive streaming descrambling with key rotation.png"
*/

/* -------------------------------------------------------------------------- */

/** @page p_ec Elliptic Curves
 *    It is required to support the prime curves P-224, P-256 and P-384
 *    recommended by NIST and defined in FIPS-186-3:
 *    - http://csrc.nist.gov/publications/fips/fips186-3/fips_186-3.pdf
 *
 *    In order to be compliant with DTCP-IP, it is also required to support
 *    P-160 prime curves secp160r1 and secp160r2 defined in SEC2:
 *    - http://www.secg.org/download/aid-386/sec2_final.pdf
 *    - http://www.dtcp.com/specifications.aspx
 *
 *    NSA Suite B Cryptography Implementation Guides:
 *    - Suite B Implementer's Guide to NIST SP 800-56A (ECDH), http://www.nsa.gov/ia/_files/SuiteB_Implementer_G-113808.pdf
 *    - Suite B Implementer's Guide to FIPS 186-3 (ECDSA), http://www.nsa.gov/ia/_files/ecdsa.pdf
 *
 *  @note Support of binary curves is not required
 *
 *  @see 
 *  - ecdsa 
 *  - ecdh
*/

/* -------------------------------------------------------------------------- */

/** @page p_flash_prot Flash Protection Key (FPK)
 *
 *  This section describes the context of the flash protection key (FPK)
 *  @image html flash_prot.png
 *  @image rtf flash_prot.png
 *
 *  @par STB production line
 *  - The cleartext version of the FPK is encrypted with the chipset specific
 *    flash protection root key. This encryption is performed by means of either
 *    the BSD API bsdEncryptFlashProtKey() function or the SEC API
 *    TSecEncryptFlashProtKey() function.
 *  - The encrypted version is then programmed in the flash SCS_Params_Area.
 *    Refer to the Chipset Integration Specification for further information
 *    about this process.
 *
 *  @par Secure chipset startup
 *  - SCS automatically decrypts the FPK located in the flash SCS_Params_Area.
 *    This decryption does not use any Nagravision NOCS API.
 *  - The resulting cleartext FPK is copied in RAM and authenticated.
 *  - SCS uses this authenticated FPK to decrypt the boot code, which is the
 *    original purpose of the FPK.
 *
 *  @par Boot context
 *  - The FPK copied in RAM in the previous step is available in the STB boot
 *    context for RAM2RAM encryption/decryption operations through the BSD API
 *    bsdUseFlashProtKey() function.
 *
 *  @par Application context
 *  - When the boot is completed and the OS is up and running, the FPK
 *    previously copied in RAM by the SCS remains available to applications for
 *    RAM2RAM encryption/decryption operations through the SEC API
 *    TSecUseFlashProtKey() function.
*/


/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/

/** @defgroup functionTable Function Table */

/** @defgroup chip_id Chipset Identification */
/** @defgroup reset Chipset Reset */

/** @defgroup flash_prot Flash Protection */

/** @defgroup buffer Buffers Management */

/** @defgroup cipher Block Ciphers
 *  @defgroup cipher_session Session Management
 *  @ingroup cipher
 *  @defgroup cipher_keys Setting Keys and Metadata
 *  @ingroup cipher
 *  @defgroup cipher_data Encrypting/Decrypting Data
 *  @ingroup cipher
*/

/** @defgroup async_crypto Asymmetric Cryptography
 *  @defgroup rsa RSA
 *  @ingroup async_crypto
 *
 *  @defgroup dh Diffie-Hellman (DH)
 *  @ingroup async_crypto
*/

/** @defgroup ec Elliptic Curve
 *  @defgroup ecdsa Elliptic Curve DSA (ECDSA)
 *  @ingroup ec
 *
 *  @defgroup ecdh Elliptic Curve Diffie-Hellman (ECDH)
 *  @ingroup ec
*/

/** @defgroup digest Digest
 *  @defgroup sha1 SHA-1
 *  @ingroup digest
 *
 *  @defgroup sha256 SHA-256
 *  @ingroup digest
 *
 *  @defgroup sha384 SHA-384
 *  @ingroup digest
 *
 *  @defgroup hmacsha256 HMAC-SHA-256
 *  @ingroup digest
*/

/** @defgroup rand  True Random Number Generator  */


/******************************************************************************/
/*                                                                            */
/*                              VERSION TOOL                                  */
/*                                                                            */
/******************************************************************************/

#ifndef SEC_TOOL_VERSION
#define SEC_TOOL_STRINGIFY(s) SEC_TOOL_TOSTRING(s)
#define SEC_TOOL_TOSTRING(s)  #s

#define SEC_TOOL_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
#define SEC_TOOL_VERSION_DOT(a, b, c) a ##.## b ##.## c
#define SEC_TOOL_VERSION(a, b, c) SEC_TOOL_VERSION_DOT(a, b, c)
#endif

#define SECAPI_VERSION_INTER SEC_TOOL_VERSION(SECAPI_VERSION_MAJOR, \
              SECAPI_VERSION_MEDIUM, \
              SECAPI_VERSION_MINOR)

#define SECAPI_VERSION_INT   SEC_TOOL_VERSION_INT(SECAPI_VERSION_MAJOR, \
            SECAPI_VERSION_MEDIUM, \
            SECAPI_VERSION_MINOR)

#define SECAPI_VERSION_STRING  "SECAPI_" SEC_TOOL_STRINGIFY(SECAPI_VERSION_INTER)




/******************************************************************************/
/*                                                                            */
/*                              TYPES DEFINITIONS                             */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup chip_id
 *
 *  @brief
 *    Type used to accommodate the 32-bit NUID programmed in NOCS 1.x chipset
*/
typedef TUnsignedInt8 TSecNuid[4];


/**
 *  @ingroup chip_id
 *
 *  @brief
 *    Type used to accommodate the 64-bit NUID programmed in NOCS 3.x chipset
*/
typedef TUnsignedInt8 TSecNuid64[8];


/**
 *  @brief
 *    Status code returned by functions of the SEC API.
 *
*/
typedef enum
{
  SEC_NO_ERROR,
   /**<  The intended operation was executed successfully.
    */
  SEC_ERROR,
   /**<  The function terminated abnormally. The intended operation failed.
    */
  SEC_ERROR_NOT_IMPLEMENTED,
   /**<  The function is not implemented.
    */
  SEC_ERROR_BAD_PARAMETER,
   /**<  Some of the parameters are missing or malformed.
    */
  SEC_ERROR_BAD_EMI,
   /**<  Given EMI is not supported
    */
  SEC_ERROR_BAD_USAGE,
   /**<  The usage is not allowed
    */
  SEC_ERROR_BAD_SIGNATURE,
   /**<  Verification of the signature failed
    */
  SEC_ERROR_BAD_PADDING,
   /**<  Verification of the padding occurring after a message decryption failed
    */
  LAST_SEC_STATUS
   /**<  Not used.
    */
} TSecStatus;


/**
 *  @brief
 *    Accepted hash types.
*/
typedef enum
{
  SEC_HASH_SHA1,
   /**<  SHA-1
    */
  SEC_HASH_SHA256,
   /**<  SHA-256
    */
  SEC_HASH_SHA384,
   /**<  SHA-384
    */
  LAST_SEC_HASH
   /**<  Internal use only
    */
}TSecHashType;



/******************************************************************************/
/*                                                                            */
/*                             CHIPSET IDENTIFICATION                         */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup chip_id
 *
 *  @brief
 *    This function returns a 4-byte array containing the 32-bit unique chipset
 *    identifier (NUID) that was programmed into the chipset's internal OTP
 *    memory by the chip manufacturer.
 *
 *  @param[out] pxNuid
 *    Address of the array in which the function has to write the 4-byte NUID.
 *    Watch out, in order to avoid any alignment or endianness issues, the
 *    NUID has to be handled as an array of bytes and not as a 32-bit unsigned
 *    integer.
 *
 *  @retval  SEC_NO_ERROR
 *    The NUID was read successfully.
 *
 *  @retval  SEC_ERROR
 *    Found problems while trying to read the NUID.
 *
*/
typedef TSecStatus (*TSecGetNuid)
(
  TSecNuid* pxNuid
);


/**
 *  @ingroup chip_id
 *
 *  @brief
 *    The prototype of this function is strictly identical to the callback
 *    TSecGetNuid. Its implementation is mandatory for backward compatibility
 *    with older client applications that are not aware of the function table
 *    TSecFunctionTable.
*/
TSecStatus secGetNuid
(
  TSecNuid* pxNuid
);


/**
 *  @ingroup chip_id
 *
 *  @brief
 *    This function returns an 8-byte array containing the 64-bit unique chipset
 *    identifier (NUID) that was programmed into the chipset's internal OTP
 *    memory by the chip manufacturer.
 *
 *  @param[out] pxNuid
 *    Address of the array in which the function has to write the 8-byte NUID.
 *    Watch out, in order to avoid any alignment or endianness issues, the
 *    NUID has to be handled as an array of bytes and not as a 64-bit unsigned
 *    integer.
 *
 *  @retval  SEC_NO_ERROR
 *    The NUID was read successfully.
 *
 *  @retval  SEC_ERROR
 *    Found problems while trying to read the NUID.
 *
*/
typedef TSecStatus (*TSecGetNuid64)
(
  TSecNuid64* pxNuid
);


/**
 *  @ingroup chip_id
 *
 *  @brief
 *    This function returns a null-terminated string containing the revision of
 *    the chipset (aka chipset cut).
 *
 *    The internal format of this revision string is manufacturer dependent but
 *    has to be approved by Nagravision.
 *
 *  @param[out] ppxChipsetRevision
 *    Pointer to be assigned to the buffer containing the chipset revision
 *    string. The SEC is in charge of allocating the buffer and must guarantee
 *    its integrity and never free it.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR
 *    The operation failed.
 *
*/
typedef TSecStatus (*TSecGetChipsetRevision)
(
  const TChar** ppxChipsetRevision
);


/**
 *  @ingroup chip_id
 *
 *  @brief
 *    The prototype of this function is strictly identical to the callback
 *    TSecGetChipsetRevision. Its implementation is mandatory for backward
 *    compatibility with older client applications that are not aware of the
 *    function table TSecFunctionTable.
*/
TSecStatus secGetChipsetRevision
(
  const TChar** ppxChipsetRevision
);


/**
 *  @ingroup chip_id
 *
 *  @brief
 *    This function returns a null-terminated string containing the extension of
 *    the chipset.

 *    The internal format of this extension string is manufacturer dependent but
 *    has to be approved by Nagravision.
 *
 *  @param[out] ppxChipsetExtension
 *    Pointer to be assigned to the buffer containing the chipset extension
 *    string. The SEC is in charge of allocating the buffer and must guarantee
 *    its integrity and never free it.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR
 *    The operation failed.
 *
*/
typedef TSecStatus (*TSecGetChipsetExtension)
(
  const TChar** ppxChipsetExtension
);



/******************************************************************************/
/*                                                                            */
/*                               FLASH PROTECTION                             */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup flash_prot
 *
 *  @brief
 *    This function encrypts the global flash protection key with the chipset
 *    specific flash protection root key.
 *
 *    This function is intended to be used on the STB production line to
 *    encrypt the flash protection key before programming it in the flash
 *    SCS_Params_Area. Refer to the "Secure Chipset Integration Specification"
 *    of the chipset family concerned for further information about the process
 *    related to this key.
 *
 *  @param[in]  pxInput
 *    Buffer allocated by the caller containing the flash protection key to be
 *    encrypted.
 *
 *  @param[out]  pxOutput
 *    Buffer allocated by the caller where to write the encrypted flash protection
 *    key.
 *
 *  @param[in]  xSize
 *    Size in bytes of the flash protection key to be encrypted. It is equal to
 *    16 bytes for the time being.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if:
 *    - pxInput and/or pxOutput is NULL
 *    - xSize is different from 16
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @note
 *    - The flash protection key is automatically decrypted, copied in RAM and
 *      authenticated by the secure chipset startup process (see [NOCS3REQ]).
 *      This key must be then available for RAM2RAM operations from the boot
 *      context through BSD API (refer to BSD API documentation for further
 *      information) and after the OS is up and running through the SEC API
 *      TSecUseFlashProtKey().
*/
typedef TSecStatus (*TSecEncryptFlashProtKey)
(
  const TUnsignedInt8*     pxInput,
        TUnsignedInt8*     pxOutput,
        size_t              xSize
);



/******************************************************************************/
/*                                                                            */
/*                                  RESET                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup reset
 *
 *  @brief
 *    This function performs a chipset reset. It must ensure the content of 
 *    volatile memories (registers, caches, internal and external memories) has 
 *    been cleared or is rendered inaccessible following the reset.
 *    
 *    This function does not return.
 *
*/
void secChipReset
(
  void
);



/******************************************************************************/
/*                                                                            */
/*                                BLOCK CIPHER                                */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup cipher_data
 *
 *  @brief
 *    This function asks the RAM2RAM crypto-engine to TDES encrypt a block of
 *    data stored in RAM with the RAM2RAM root key and write the result back in
 *    RAM. The choice of the encryption key and cryptographic algorithm is
 *    implicit.
 *
 *    If the caller provides the same input and output buffer (pxInput=pxOutput),
 *    the function must perform an in-place encryption.
 *
 *  @param[out] pxOutput
 *    Buffer allocated by the caller where to write the encrypted result
 *
 *  @param[in] pxInput
 *    Buffer containing the block of data to be encrypted.
 *
 *  @param[in] xDataSize
 *    Length in bytes of input and output data blocks to operate on. It shall
 *    be a multiple of 8.
 *
 *  @retval SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *    Also returned if xDataSize is not a multiple of 8 (TDES block cipher size).
 *
 *  @retval SEC_ERROR_NOT_IMPLEMENTED
 *    The function is not implemented
 *
 *  @note
 *    Unlike TSecSessionEncrypt(), this function does not require high
 *    throughput and must support standard input/output buffers to remain
 *    compatible with older client applications. Thus it should not be coupled
 *    with a DMA that requires special buffers. In other words, this function
 *    must work properly even if the caller did not allocate buffers with
 *    TSecAllocateBuffer().
 *
 *  @see
 *    \ref s_bc_rootkey
*/
typedef TSecStatus (*TSecEncryptData)
(
        TUnsignedInt8*  pxOutput,
  const TUnsignedInt8*  pxInput,
        TSize           xDataSize
);


/**
 *  @ingroup cipher_data
 *
 *  @brief
 *    The prototype of this function is strictly identical to the callback
 *    TSecEncryptData(). Its implementation is mandatory for backward
 *    compatibility with older client applications that are not aware of the
 *    function table TSecFunctionTable.
*/
TSecStatus secEncryptData
(
        TUnsignedInt8*  pxOutput,
  const TUnsignedInt8*  pxInput,
        TSize           xDataSize
);



/**
 *  @ingroup cipher_data
 *
 *  @brief
 *    This function asks the RAM2RAM crypto-engine to TDES decrypt a block of
 *    data stored in RAM with the RAM2RAM root key and write the result back in
 *    RAM. The choice of the encryption key and cryptographic algorithm is
 *    implicit.
 *
 *    If the caller provides the same input and output buffer (pxInput=pxOutput),
 *    the function must perform an in-place encryption.
 *
*  @param[out] pxOutput
 *    Buffer allocated by the caller where to write the decrypted result
 *
 *  @param[in] pxInput
 *    Buffer containing the block of data to be decrypted.
 *
 *  @param[in] xDataSize
 *    Length in bytes of input and output data blocks to operate on. It shall
 *    be a multiple of 8.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *    Also returned if xDataSize is not a multiple of 8 (TDES block cipher size).
 *
 *  @retval  SEC_ERROR_NOT_IMPLEMENTED
 *    The function is not implemented.
 *
 *  @note
 *    Unlike TSecSessionDecrypt(), this function does not require high
 *    throughput and must support standard input/output buffers to remain
 *    compatible with older client applications. Thus it should not be coupled
 *    with a DMA that requires special buffers. In other words, this function
 *    must work properly even if the caller did not allocate buffers with
 *    TSecAllocateBuffer().
 *
 *  @see
 *    \ref s_bc_rootkey
*/
typedef TSecStatus (*TSecDecryptData)
(
        TUnsignedInt8*  pxOutput,
  const TUnsignedInt8*  pxInput,
        TSize           xDataSize
);


/**
 *  @ingroup cipher_data
 *
 *  @brief
 *    The prototype of this function is strictly identical to the callback
 *    TSecDecryptData(). Its implementation is mandatory for backward
 *    compatibility with older client applications that are not aware of the
 *    function table TSecFunctionTable.
*/
TSecStatus secDecryptData
(
        TUnsignedInt8*  pxOutput,
  const TUnsignedInt8*  pxInput,
        TSize           xDataSize
);



/**
 *  @ingroup cipher_session
 *
 *  @brief
 *    Pointer to an opaque structure to be defined by the entity in charge of
 *    developing the SEC API and used as a handle for block cipher encryption
 *    and decryption sessions. The block cipher session may be either a RAM2RAM
 *    session or a stream session.
*/
typedef struct SSecCipherSession* TSecCipherSession;



/**
 *  @ingroup cipher_session
 *
 *  @brief
 *    This function opens a RAM2RAM encryption session and returns a session
 *    handle that will be used by other functions to set keys and encrypt data.
 *
 *    It is possible to change the encryption key and/or the encryption
 *    algorithm (EMI) during the same session. The protection of the encryption
 *    key (clear-text, key ladder, CERT) may also change during a session.
 *
 *  @param[out]  pxSession
 *    Session handle assigned by this function
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if pxSession is NULL.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @see
 *    - \ref p_r2r_fct_list "Functions applying to RAM2RAM sessions"
 *    - \ref p_r2r_basic_scenario "Basic RAM2RAM scenarios"
*/
typedef TSecStatus (*TSecOpenRam2RamEncryptSession)
(
  TSecCipherSession*     pxSession
);


/**
 *  @ingroup cipher_session
 *
 *  @brief
 *    This function opens a RAM2RAM decryption session and returns a session
 *    handle that will be used by other functions to set keys and decrypt data.
 *
 *    It is possible to change the decryption key and/or the decryption
 *    algorithm (EMI) during the same session. The protection of the decryption
 *    key (clear-text, key ladder, CERT) may also change during a session.
 *
 *  @param[out]  pxSession
 *    Session handle assigned by this function
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if pxSession is NULL.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @see
 *    - \ref p_r2r_fct_list "Functions applying to RAM2RAM sessions"
 *    - \ref p_r2r_basic_scenario "Basic RAM2RAM scenarios"
*/
typedef TSecStatus (*TSecOpenRam2RamDecryptSession)
(
  TSecCipherSession*     pxSession
);


/**
 *  @ingroup cipher_session
 *
 *  @brief
 *    This function opens a stream encryption session and returns a session
 *    handle that will be used by other functions to set keys.
 *
 *    It is possible to change the encryption key and/or the encryption
 *    algorithm (EMI) during the same session. The protection of the encryption
 *    key (clear-text, key ladder, CERT) may also change during a session.
 *
 *  @param[out]  pxSession
 *    Session handle assigned by this function
 *
 *  @param[in]  xTransportSessionId
 *    Transport session ID associated to the streams to be encrypted. It is
 *    defined and provided by the application component in charge of managing
 *    the streams.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if:
 *    - pxSession is NULL
 *    - xTransportSessionId is invalid (#TRANSPORT_SESSION_ID_INVALID)
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @note
 *    - Unlike RAM2RAM sessions, stream processing sessions do not directly
 *      handle data to be encrypted, it handles keys only. The relation between
 *      keys and streams is achieved thanks to the Transport Session ID and
 *      optionally the key ID provided by each secSetXxxKey() or secUseXxxKey()
 *      functions.
 *
 *  @see
 *    - \ref p_stream_fct_list "Functions applying to stream processing sessions"
 *    - \ref p_stream_basic_scenario "Basic stream processing scenarios"
 *    - \ref p_bc_use_cases "Comprehensive use cases"
*/
typedef TSecStatus (*TSecOpenStreamEncryptSession)
(
  TSecCipherSession*     pxSession,
  TTransportSessionId     xTransportSessionId
);


/**
 *  @ingroup cipher_session
 *
 *  @brief
 *    This function opens a stream decryption session and returns a session
 *    handle that will be used by other functions to set keys.
 *
 *    It is possible to change the decryption key and/or the decryption
 *    algorithm (EMI) during the same session. The protection of the decryption
 *    key (clear-text, key ladder, CERT) may also change during a session.
 *
 *  @param[out]  pxSession
 *    Session handle assigned by this function
 *
 *  @param[in]  xTransportSessionId
 *    Transport session ID associated to the streams to be decrypted. It is
 *    defined and provided by the application component in charge of managing
 *    the streams.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if:
 *    - pxSession is NULL
 *    - xTransportSessionId is invalid (#TRANSPORT_SESSION_ID_INVALID)
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @note
 *    - Unlike RAM2RAM sessions, stream processing sessions do not directly
 *      handle data to be decrypted, it handles keys only. The relation between
 *      keys and streams is achieved thanks to the Transport Session ID and
 *      optionally the key ID provided by each secSetXxxKey() or secUseXxxKey()
 *      functions.
 *
 *  @see
 *    - \ref p_stream_fct_list "Functions applying to stream processing sessions"
 *    - \ref p_stream_basic_scenario "Basic stream processing scenarios"
 *    - \ref p_bc_use_cases "Comprehensive use cases"
*/
typedef TSecStatus (*TSecOpenStreamDecryptSession)
(
  TSecCipherSession*     pxSession,
  TTransportSessionId     xTransportSessionId
);


/**
 *  @ingroup cipher_session
 *
 *  @brief
 *    This function closes any kind of block cipher session and frees the
 *    allocated resources.
 *
 *  @param[in]  xSession
 *    Handle of the session to be closed
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if xSession is NULL or does not correspond to a
 *    valid session.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @note
 *    If it is called to close a stream processing session, this function must 
 *    flush the related crypto-engine key table registers in order to 
 *    immediately stop the decryption/encryption of the media streams that are 
 *    potentially still flowing through this crypto-engine element.
*/ 
typedef TSecStatus (*TSecCloseSession)
(
  TSecCipherSession      xSession
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function sets a clear-text key in a crypto-engine for RAM2RAM or
 *    stream encryption/decryption operations.
 *
 *    The type of operation (encryption or decryption) is defined at session
 *    opening (TSecOpenXxxEncryptSession or TSecOpenXxxDecryptSession). The EMI
 *    provided as input parameter clearly identifies the cryptographic algorithm
 *    and chaining mode. At this stage the driver have all the information
 *    required to allocate hardware resources.
 *
 *    EMIs to be supported depend on the type of session. RAM2RAM sessions cover
 *    all EMIs 0x40xx while stream processing sessions cover all EMIs 0x40xx and
 *    all MPEG TS EMIs 0x00xx, except ASA. Refer to [EMI] specification for
 *    further information.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA) and block
 *    cipher modes (ECB, CBC, CTR) to be used by the crypto-engine.
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
 *  @param[in]  xClearTextKeySize
 *    Size in bytes of the clear-text key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
 *
 *  @param[in]  pxClearTextKey
 *    Buffer containing the clear-text key. The buffer is allocated by the
 *    caller. In case of TDES keying option 2, K1 and K2 are provided as follows:
 *    - K1=pxClearTextKey[0:7]
 *    - K2=pxClearTextKey[8:15]
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL clear-text key pointer
 *    - Size of key does not match the crypto algorithm defined by the EMI
 *    - Key ID parameters inconsistency (e.g. xKeyIdSize!=0 and pxKeyId=NULL,
 *      and vice-versa)
 *
 *  @retval  SEC_ERROR_BAD_EMI
 *    The EMI given as input parameter is not supported.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @remarks
 *    This function may be called at any time during a given session to change
 *    the EMI and/or the keys.
 *
 *  @see
 *    \ref s_bc_clearkey
*/
typedef TSecStatus (*TSecSetClearTextKey)
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8*     pxKeyId,
        size_t              xClearTextKeySize,
  const TUnsignedInt8*     pxClearTextKey
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function sets a protected content key in a 0-level key ladder 
 *    crypto-engine for stream encryption/decryption operations. It is not 
 *    intended to be used for RAM2RAM session.
 *
 *    The type of operation (encryption or decryption) is defined at session 
 *    opening (TSecOpenStreamEncryptSession or TSecOpenStreamDecryptSession). 
 *    The EMI provided as input parameter clearly identifies the cryptographic 
 *    algorithm and chaining mode. At this stage the driver have all the 
 *    information required to allocate hardware resources.
 *
 *    EMIs to be supported cover all EMIs 0x40xx and all MPEG TS EMIs 0x00xx, 
 *    except ASA. Refer to [EMI] specification for further information about the
 *    definition of EMI.
 *
 *    Beware that the key provided to the key ladder is protected with TDES-ECB 
 *    keying option 2. This key ladder algorithm must not be confused with the 
 *    crypto-engine algorithm signaled by the EMI.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  xKeyIdSize
 *    Size in bytes of the key ID (pxKeyId). If no key ID is required, 
 *    xKeyIdSize is set to 0.
 *
 *  @param[in]  pxKeyId
 *    Identifier of the key provided:
 *    - If no key ID is required, pxKeyId is set to NULL.
 *    - The key ID is typically used for MPEG transport stream decryption session
 *      (i.e. stream session associated to EMI 0x00XX) and indicates the parity
 *      of the keys. In such a case, the function must consider the parity of
 *      the key ID as the parity of the key: for instance key ID = 0x00 => even
 *      key and key ID = 0x01 => odd key.
 *    - The key ID is also required to support key rotations with HLS (EMI
 *      0x4023) and MPEG/DASH (EMI 0x4024) standards. MPEG/DASH uses a key ID of
 *      16 bytes.
 *
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA) and block
 *    cipher modes (ECB, CBC, CTR) to be used by the crypto-engine.
 *
 *  @param[in]  xCipheredContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
 *
 *  @param[in]  pxCipheredContentKey
 *    Buffer, allocated by the caller, containing the ciphered content key. It
 *    is equal to CipheredContentKey=TDES(ContentKey, RootKey).
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL key pointers
 *    - Size of content key does not match the crypto algorithm defined by the EMI
 *    - Unsupported protecting key size
 *    - Key ID parameters inconsistency (e.g. xKeyIdSize!=0 and pxKeyId=NULL,
 *      and vice-versa)
 *
 *  @retval  SEC_ERROR_BAD_EMI
 *    The EMI given as input parameter is not supported.
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This status is returned if xSession is not related to a stream session, i.e.
 *    session opened with TSecOpenStreamEncryptSession() or 
 *    TSecOpenStreamDecryptSession().
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @remarks
 *    This function may be called at any time during a given session to change
 *    the EMI and/or the keys.
 *
 *  @see
 *    \ref s_bc_0kl_prot
*/
typedef TSecStatus (*TSecSet0LevelProtectedKey)
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8*     pxKeyId,
        size_t              xCipheredContentKeySize,
  const TUnsignedInt8*     pxCipheredContentKey
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function sets protected keys required by the 1-level key ladder
 *    associated to the crypto-engine for stream encryption/decryption operations.
 *    It is not intended to be used for RAM2RAM session.
 *
 *    The type of operation (encryption or decryption) is defined at session 
 *    opening (TSecOpenStreamEncryptSession or TSecOpenStreamDecryptSession). 
 *    The EMI provided as input parameter clearly identifies the cryptographic 
 *    algorithm and chaining mode. At this stage the driver have all the 
 *    information required to allocate hardware resources.
 *
 *    EMIs to be supported cover all EMIs 0x40xx and all MPEG TS EMIs 0x00xx, 
 *    except ASA. Refer to [EMI] specification for further information about the
 *    definition of EMI.
 *
 *    Beware that keys provided to the key ladder are all protected with 
 *    TDES-ECB keying option 2. This key ladder algorithm must not be confused 
 *    with the crypto-engine algorithm signaled by the EMI.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  xKeyIdSize
 *    Size in bytes of the key ID (pxKeyId). If no key ID is required, 
 *    xKeyIdSize is set to 0.
 *
 *  @param[in]  pxKeyId
 *    Identifier of the key provided:
 *    - If no key ID is required, pxKeyId is set to NULL.
 *    - The key ID is typically used for MPEG transport stream decryption session
 *      (i.e. stream session associated to EMI 0x00XX) and indicates the parity
 *      of the keys. In such a case, the function must consider the parity of
 *      the key ID as the parity of the key: for instance key ID = 0x00 => even
 *      key and key ID = 0x01 => odd key.
 *    - The key ID is also required to support key rotations with HLS (EMI
 *      0x4023) and MPEG/DASH (EMI 0x4024) standards. MPEG/DASH uses a key ID of
 *      16 bytes.
 *
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA) and block
 *    cipher modes (ECB, CBC, CTR) to be used by the crypto-engine.
 *
 *  @param[in]  xCipheredContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
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
 *    key fed into the key ladder. It is equal to L1CipheredProtKey=TDES(L1ProtKey,
 *    RootKey).
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL key pointers
 *    - Size of content key does not match the crypto algorithm defined by the EMI
 *    - Unsupported protecting key size
 *    - Key ID parameters inconsistency (e.g. xKeyIdSize!=0 and pxKeyId=NULL,
 *      and vice-versa)
 *
 *  @retval  SEC_ERROR_BAD_EMI
 *    The EMI given as input parameter is not supported.
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This status is returned if xSession is not related to a stream session, i.e.
 *    session opened with TSecOpenStreamEncryptSession() or 
 *    TSecOpenStreamDecryptSession().
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @remarks
 *    This function may be called at any time during a given session to change
 *    the EMI and/or the keys.
 *
 *  @see
 *    \ref s_bc_1kl_prot
*/
typedef TSecStatus (*TSecSet1LevelProtectedKey)
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8*     pxKeyId,
        size_t              xCipheredContentKeySize,
  const TUnsignedInt8*     pxCipheredContentKey,
        size_t              xCipheredProtectingKeySize,
  const TUnsignedInt8*     pxL1CipheredProtectingKey
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function sets protected keys required by the 2-level key ladder
 *    associated to the crypto-engine for RAM2RAM or stream encryption/decryption
 *    operations.
 *
 *    The type of operation (encryption or decryption) is defined at session
 *    opening (TSecOpenXxxEncryptSession or TSecOpenXxxDecryptSession). The EMI
 *    provided as input parameter clearly identifies the cryptographic algorithm
 *    and chaining mode. At this stage the driver have all the information
 *    required to allocate hardware resources.
 *
 *    EMIs to be supported depend on the type of session. RAM2RAM sessions cover
 *    all EMIs 0x40xx while stream processing sessions cover all EMIs 0x40xx and
 *    all MPEG TS EMIs 0x00xx, except ASA. Refer to [EMI] specification for
 *    further information.
 *
 *    Beware that keys provided to the key ladder are all protected with 
 *    TDES-ECB keying option 2. This key ladder algorithm must not be confused 
 *    with the crypto-engine algorithm signaled by the EMI.
 *
 *  @param[in]  xSession
 *    Handle of the session
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
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA) and block
 *    cipher modes (ECB, CBC, CTR) to be used by the crypto-engine.
 *
 *  @param[in]  xCipheredContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
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
 *    key fed into the key ladder. It is equal to L2CipheredProtKey=TDES(L2ProtKey,
 *    RootKey)
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL key pointers
 *    - Size of content key does not match the crypto algorithm defined by the EMI
 *    - Unsupported protecting key size
 *    - Key ID parameters inconsistency (e.g. xKeyIdSize!=0 and pxKeyId=NULL,
 *      and vice-versa)
 *
 *  @retval  SEC_ERROR_BAD_EMI
 *    The EMI given as input parameter is not supported.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @remarks
 *    This function may be called at any time during a given session to change
 *    the EMI and/or the keys.
 *
 *  @see
 *    \ref s_bc_2kl_prot
*/
typedef TSecStatus (*TSecSet2LevelProtectedKey)
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8*     pxKeyId,
        size_t              xCipheredContentKeySize,
  const TUnsignedInt8*     pxCipheredContentKey,
        size_t              xCipheredProtectingKeySize,
  const TUnsignedInt8*     pxL1CipheredProtectingKey,
  const TUnsignedInt8*     pxL2CipheredProtectingKey
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function copies the key available on the CERT key output interface in
 *    a crypto-engine for RAM2RAM or stream encryption/decryption operations.
 *
 *    The type of operation (encryption or decryption) is defined at session
 *    opening (TSecOpenXxxEncryptSession or TSecOpenXxxDecryptSession). The EMI
 *    provided as input parameter clearly identifies the cryptographic algorithm
 *    and chaining mode. At this stage the driver have all the information
 *    required to allocate hardware resources.
 *
 *    This function also checks the usage rules related to the key. Finally, it
 *    acknowledges the CERT block to allow it to output another key.
 *
 *    EMIs to be supported depend on the type of session. RAM2RAM sessions cover
 *    all EMIs 0x40xx while stream processing sessions cover all EMIs 0x40xx and
 *    all MPEG TS EMIs 0x00xx, including ASA. Refer to [EMI] specification for
 *    further information.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA, ASA) and
 *    block cipher modes (ECB, CBC, CTR) to be used by the crypto-engine.
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
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - Key ID parameters inconsistency (e.g. xKeyIdSize!=0 and pxKeyId=NULL,
 *      and vice-versa)
 *
 *  @retval  SEC_ERROR_BAD_EMI
 *    The EMI given as input parameter is not supported.
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    Key usage rules are not respected, e.g. algorithm or operation (encryption,
 *    decryption) or key size is not allowed.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @remarks
 *    This function may be called at any time during a given session to change
 *    the EMI and/or the keys.
 *
 *  @warning
 *    - The CERT block must be acknowledged even in case the EMI provided is not
 *      supported (#SEC_ERROR_BAD_EMI) or in case of bad key usage
 *      (#SEC_ERROR_BAD_USAGE). Otherwise the CERT block will no longer be able
 *      output keys on the key output interface.
 *
 *  @see
 *    \ref s_bc_certkey
*/
typedef TSecStatus (*TSecUseCertKey)
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8*     pxKeyId
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function copies the flash protection key in a crypto-engine key table
 *    for RAM2RAM operations. It is not intended to be used for stream processing
 *    operations.
 *
 *    The type of operation (encryption or decryption) is defined at session
 *    opening (#TSecOpenRam2RamEncryptSession or #TSecOpenRam2RamDecryptSession).
 *
 *    The EMI provided as input parameter clearly identifies the cryptographic
 *    algorithm and chaining mode. At this stage the driver have all the
 *    information required to allocate hardware resources.
 *
 *    EMI to be supported cover TDES and AES algorithms with ECB, CBC and
 *    CTR block cipher modes of operation. It corresponds to all EMIs 0x40xx
 *    defined in [EMI] specification.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES) and block
 *    cipher modes (ECB, CBC, CTR) to be used by the RAM2RAM crypto-engine.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if xSession is NULL or does not correspond to a
 *    valid session.
 *
 *  @retval  SEC_ERROR_BAD_EMI
 *    The EMI given as input parameter is not supported.
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This status is returned if xSession is not related to a RAM2RAM session, 
 *    i.e. session opened with TSecOpenRam2RamEncryptSession() or 
 *    TSecOpenRam2RamDecryptSession().
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @remarks
 *    - This function may be called at any time during a given session to change
 *      the EMI and/or key associated to this session. A session is related to
 *      one single key at a time, the latest one set.
 *
 *  @note
 *    - This function must rely on the authenticated cleartext instance of the
 *      flash protection key made available by the secure chipset startup
 *      process. It must never access the original flash protection key located
 *      in the flash SCS_Params_Area.
 *
 *  @see TSecEncryptFlashProtKey()
*/
typedef TSecStatus (*TSecUseFlashProtKey)
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function uses the legacy secret key for stream processing operations.
 *    It is not intended to be used for RAM2RAM operations. 
 *
 *    The EMI associated to these operations is not explicitly given by the
 *    caller, but it is implicitly linked to this legacy key.
 *
 *    The main use case behind this function is the ability of playing back a 
 *    media content stored on the HDD protected with a custom key.
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    This status is returned if xSession is NULL or does not correspond to a
 *    valid session.
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This status is returned if xSession is not related to a stream session, i.e.
 *    session opened with TSecOpenStreamEncryptSession() or 
 *    TSecOpenStreamDecryptSession().
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @note
 *    This function replaces the scrSetLegacyDecryptionMode() function of the 
 *    deprecated SCR API.
*/
typedef TSecStatus (*TSecUseLegacyKey)
(
        TSecCipherSession   xSession
);


/**
 *  @ingroup cipher_keys
 *
 *  @brief
 *    This function associates metadata to a stream decryption session. It
 *    typically concerns content usage rules such as copy control information.
 *
 *    Metadata consists in a collection of TLV descriptors (1-byte length, 1-byte
 *    tag) complying with the format defined in [META].
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in] xMetadataLength
 *    Size in bytes of the metadata buffer.
 *
 *  @param[in] pxMetadata
 *    Buffer allocated by the caller containing metadata descriptors
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - Metadata parameters inconsistency (e.g. xMetadataSize!=0 and pxMetadata=NULL,
 *      and vice-versa)
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This status is returned if xSession is related to a RAM2RAM session, i.e.
 *    session opened with TSecOpenRam2RamEncryptSession() or 
 *    TSecOpenRam2RamDecryptSession().
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @note
 *    -# This function may be called any time during a stream session in case of
 *       change of metadata (descriptors added, removed or updated). In such a
 *       case, it is called before setting the key (secSetXxxKey or
 *       secUseXxxKey) and the metadata provided shall be considered as
 *       applicable until the next TSecSetMetadata() call.
 *    -# The removal of a given metadata descriptor implies the cancellation of
 *       the underlying feature. For instance, if a copy protection descriptor
 *       is no longer available in the metadata buffer, the driver shall no
 *       longer manage the copy control on this stream session.
 *    -# If all metadata descriptors are removed, TSecSetMetadata is called with
 *       pxMetadata set to NULL and xMetadataSize set to 0.
*/
typedef TSecStatus (*TSecSetMetadata)
(
        TSecCipherSession   xSession,
        size_t              xMetadataSize,
  const TUnsignedInt8*     pxMetadata
);


/**
 *  @ingroup cipher_data
 *
 *  @brief
 *    This function performs a RAM2RAM data encryption.
 *
 *    It encrypts the data contained in pxInput buffer and stores the resulted
 *    encrypted data in pxOutput buffer.
 *
 *    This function may be called several times during a given session in order
 *    to encrypt a message split in several chunks. If the block cipher modes of
 *    operation requests an initialization vector (IV), the caller is in charge
 *    of the consistency of the IV passed at each chunk.
 *
 *    The size of message to be encrypted does not need to be a multiple of the
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
 *    If the caller provides the same input and output buffer (pxInput=pxOutput),
 *    the function must perform an in-place encryption.
 *
 *  @pre
 *    The content key has been set through TSecSetClearTextKey(),
 *    TSecSet0LevelProtectedKey(), TSecSet1LevelProtectedKey(), 
 *    TSecSet2LevelProtectedKey(), TSecUseCertKey(), TSecUseLegacyKey() or 
 *    TSecUseFlashProtKey().
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  pxInput
 *    Buffer containing the input message to encrypt. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    the RAM2RAM cryptoprocessor constraints.
 *
 *  @param[out]  pxOutput
 *    Buffer where to write the encrypted message. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    the RAM2RAM cryptoprocessor constraints.
 *
 *  @param[in]  xMessageSize
 *    Size in bytes of messages (pxInput, pxOutput) to operate on. It does not
 *    need to be a multiple of the cipher block size.
 *
 *  @param[in] pxInitVector
 *    Buffer allocated by the caller containing the initialization vector (IV)
 *    required by CBC and CTR modes. These cipher modes of operation are part of
 *    the EMI definition. If no IV is required (ECB mode), pxInitVector is set
 *    to NULL.
 *
 *    Normally the CTR mode requires a nonce and a counter that are then
 *    combined to produce the actual counter block encryption. In the current
 *    API the caller is in charge of providing the initial counter block instead
 *    of a nonce and a counter. This initial counter block is passed within
 *    pxInitVector buffer. The function TSecSessionEncrypt() is then in charge of
 *    incrementing the counter block of one unit for each block encryption.
 *
 *    The caller is in charge of providing a correct and consistent IV, even 
 *    in case the data to be encrypted requires several calls to this function.
 *
 *  @param[in] xInitVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is required
 *    (ECB mode), xInitVectorSize is set to zero.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL input/output buffers
 *    - Unsupported IV size (not a multiple of cipher block size)
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This error status is returned if xSession refers to a decryption session.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
*/
typedef TSecStatus (*TSecSessionEncrypt)
(
        TSecCipherSession   xSession,
  const TUnsignedInt8*     pxInput,
        TUnsignedInt8*     pxOutput,
        size_t              xMessageSize,
  const TUnsignedInt8*     pxInitVector,
        size_t              xInitVectorSize
);


/**
 *  @ingroup cipher_data
 *
 *  @brief
 *    This function performs a RAM2RAM data decryption.
 *
 *    It decrypts the data contained in pxInput buffer and stores the resulted
 *    decrypted data in pxOutput buffer.
 *
 *    This function may be called several times during a given session in order
 *    to decrypt a message split in several chunks. If the block cipher modes of
 *    operation requests an initialization vector (IV), the caller is in charge
 *    of the consistency of the IV passed at each chunk.
 *
 *    The size of message to be decrypted does not need to be a multiple of the
 *    cipher block size. In such a case, the n residual bytes (with
 *    n = xMessageSize mod cipher block size) are left as is and simply
 *    copied from input to output buffer provided the mode of operation is ECB
 *    or CBC. For CTR mode, decryption actually consists in a simple XOR, thus
 *    residual bytes are decrypted as any other bytes of the message.
 *
 *    This function does not manage any padding. If the plaintext message was
 *    padded by the client, it is also in charge of removing it after the return
 *    of this function call.
 *
 *    If the caller provides the same input and output buffer (pxInput=pxOutput),
 *    the function must perform an in-place decryption.
 *
 *  @pre
 *    The content key has been set through TSecSetClearTextKey(),
 *    TSecSet0LevelProtectedKey(), TSecSet1LevelProtectedKey(), 
 *    TSecSet2LevelProtectedKey(), TSecUseCertKey(), TSecUseLegacyKey() or 
 *    TSecUseFlashProtKey().
 *
 *  @param[in]  xSession
 *    Handle of the session
 *
 *  @param[in]  pxInput
 *    Buffer containing the input message to decrypt. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    the RAM2RAM cryptoprocessor constraints.
 *
 *  @param[in]  pxOutput
 *    Buffer where to write the decrypted message. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    the RAM2RAM cryptoprocessor constraints.
 *
 *  @param[in]  xMessageSize
 *    Size in bytes of messages (pxInput, pxOutput) to operate on. It does not
 *    need to be a multiple of the cipher block size.
 *
 *  @param[in] pxInitVector
 *    Buffer allocated by the caller containing the initialization vector (IV)
 *    required by CBC and CTR modes. These cipher modes of operation are part of
 *    the EMI definition. If no IV is required (ECB mode), pxInitVector is set
 *    to NULL.
 *
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
 *  @param[in] xInitVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitVectorSize is set to zero.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown session
 *    - NULL input/output buffers
 *    - Unsupported IV size (not a multiple of cipher block size)
 *
 *  @retval  SEC_ERROR_BAD_USAGE
 *    This error status is returned if xSession refers to an encryption session.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
*/
typedef TSecStatus (*TSecSessionDecrypt)
(
        TSecCipherSession   xSession,
  const TUnsignedInt8*     pxInput,
        TUnsignedInt8*     pxOutput,
        size_t              xMessageSize,
  const TUnsignedInt8*     pxInitVector,
        size_t              xInitVectorSize
);


/**
 *  @ingroup buffer
 *
 *  @brief
 *    This function allocates a buffer that is compatible with hardware
 *    cryptoprocessor constraints.
 *
 *    The rational for this function is that hardware cryptoprocessors may 
 *    requires special buffers (e.g. contiguous pages in physical memory, limited
 *    address space, pages alignment, etc) to work properly.
 *
 *    Buffers allocated by this function are intended to be used as RAM2RAM 
 *    input/output messages and digest input messages.
 *
 *  @param[in] xBufferSize
 *    Size in bytes of the buffer to allocate
 *
 *  @returns
 *    - Pointer to the buffer allocated in case of success
 *    - NULL in case of failure
 *
 *  @see
 *    - TSecFreeBuffer
 *    - \ref p_buffer
*/
typedef TUnsignedInt8* (*TSecAllocateBuffer)
(
  size_t  xBufferSize
);


/**
 *  @ingroup buffer
 *
 *  @brief
 *    This function frees a buffer allocated by TSecAllocateBuffer().
 *
 *  @param[in] pxBuffer
 *    Pointer to the buffer to free
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully. This status is also returned if
 *    \c pxBuffer=NULL.
 *
 *  @retval  SEC_ERROR
 *    Any other errors
 *
 *  @see
 *    TSecAllocateBuffer
*/
typedef TSecStatus (*TSecFreeBuffer)
(
  TUnsignedInt8*     pxBuffer
);


/******************************************************************************/
/*                                                                            */
/*                                    RSA                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup rsa
 *
 *  @brief
 *    Padding schemes used together with RSA.
*/
typedef enum
{
  SEC_RSA_PKCS1_V1_5_PADDING,
   /**<  PKCS #1 V1.5 padding scheme. It generates an overhead of is 11 bytes.
    *    bytes.
    */
  SEC_RSA_OAEP_SHA_1_PADDING,
   /**<  OAEP padding scheme based on SHA-1. No label is provided. It generates
    *    an overhead of 42 bytes.
    */
  SEC_RSA_OAEP_SHA_256_PADDING,
   /**<  OAEP padding scheme based on SHA-256. No label is provided. It generates
    *    an overhead of 66 bytes.
    */
  SEC_RSA_NO_PADDING,
   /**<  No padding.
    */
  SEC_RSA_OAEP_SHA_384_PADDING,
   /**<  OAEP padding scheme based on SHA-384. No label is provided. It generates
    *    an overhead of 98 bytes.
    */
  LAST_SEC_RSA_PADDING
   /**<  Internal use only
    */
}TSecRsaPadding;


/**
 *  @ingroup rsa
 *
 *  @brief
 *    This function generates a RSA key (n, p, q, dP, dQ, qInv) from a public
 *    exponent e and for a given key size.
 *
 *  @param[in]  xKeySize
 *    RSA key size in bytes of key to be generated
 *
 *  @param[in]  xE
 *    Public RSA exponent e used as input parameter for the generation of the
 *    key. May be any of the following values: 3, 17, 65537.
 *
 *  @param[out]  pxN
 *    Buffer where to store the RSA modulus n generated. The buffer is allocated
 *    by the caller and is xKeySize bytes long.
 *
 *  @param[out]  pxP
 *    Buffer where to store the generated prime number p. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[out]  pxQ
 *    Buffer where to store the generated prime number q. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[out]  pxDP
 *    Buffer where to store the generated CRT exponent dP. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[out]  pxDQ
 *    Buffer where to store the generated CRT exponent dQ. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[out]  pxQInv
 *    Buffer where to store the generated CRT coefficient qInv. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Unsupported values of public exponent e
 *    - Unsupported key size
 *    - Missing parameter (NULL pointer)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @remarks
 *    -# All buffers used for passing input and output parameters are allocated
 *       by the caller. Refer to parameters description above for the size of
 *       each buffer.
 *       \n
 *    -# A big number output parameter (n, p, q, dP, dQ, qInv) is returned by
 *       this function through a byte array buffer in big endian format. If the
 *       effective size of the big number is smaller than the buffer size, this
 *       function must pad the output with leading zeros to match the buffer
 *       size.
*/
typedef TSecStatus (*TSecRsaGenerateKey)
(
  size_t                xKeySize,
  TUnsignedInt32        xE,
  TUnsignedInt8*       pxN,
  TUnsignedInt8*       pxP,
  TUnsignedInt8*       pxQ,
  TUnsignedInt8*       pxDP,
  TUnsignedInt8*       pxDQ,
  TUnsignedInt8*       pxQInv
);



/**
 *  @ingroup rsa
 *
 *  @brief
 *    This function computes CRT parameters dP, dQ and qInv from the two primes
 *    p and q and the public exponent e.
 *
 *  @param[in]  xKeySize
 *    RSA key size in bytes
 *
 *  @param[in]  xE
 *    Public RSA exponent e used as input parameter for the computation of CRT
 *    parameters. May be any of the following values: 3, 17, 65537.
 *
 *  @param[in]  pxP
 *    Buffer containing the prime number p used as input parameter for the
 *    computation of CRT parameters. The buffer is allocated by the caller and
 *    is xKeySize/2 bytes long.
 *
 *  @param[in]  pxQ
 *    Buffer containing the prime number q used as input parameter for the
 *    computation of CRT parameters. The buffer is allocated by the caller and
 *    is xKeySize/2 bytes long.
 *
 *  @param[out]  pxDP
 *    Buffer where to store the CRT exponent dP computed. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[out]  pxDQ
 *    Buffer where to store the CRT exponent dQ computed. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[out]  pxQInv
 *    Buffer where to store the CRT coefficient qInv computed. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Unsupported values of public exponent e
 *    - Unsupported key size
 *    - Missing parameter (NULL pointer)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @remarks
 *    -# All buffers used for passing input and output parameters are allocated
 *       by the caller. Refer to parameters description above for the size of
 *       each buffer.
 *       \n
 *    -# A big number input parameter (p, q) is provided by the caller through a
 *        byte array buffer in big endian format. If the effective size of the big
 *       number is smaller than the buffer size, it must be padded by the caller
 *       with leading zeros.
 *       \n
 *    -# A big number output parameter (dP, dQ, qInv) is returned by this function
 *       through a byte array buffer in big endian format. If the effective size
 *       of the big number is smaller than the buffer size, this function must
 *       pad the output with leading zeros to match the buffer size.
*/
typedef TSecStatus (*TSecRsaComputeCrtParams)
(
        size_t                xKeySize,
        TUnsignedInt32        xE,
  const TUnsignedInt8*       pxP,
  const TUnsignedInt8*       pxQ,
        TUnsignedInt8*       pxDP,
        TUnsignedInt8*       pxDQ,
        TUnsignedInt8*       pxQInv
);



/**
 *  @ingroup rsa
 *
 *  @brief
 *    This function pads a cleartext input message and RSA encrypts the padded
 *    message with the public key.
 *
 *    Padding schemes supported are OAEP and PKCS #1 v1.5. It is also possible
 *    to use this function with the special padding scheme #SEC_RSA_NO_PADDING.
 *    In such a case, the caller must ensure the input message size is equal to
 *    key size.
 *
 *  @param[in]  pxInput
 *    Input message to be encrypted.
 *
 *  @param[in]  xInputSize
 *    Size in bytes of input message to operate on. The maximum size depends on
 *    the key size and the padding scheme:
 *    - #SEC_RSA_PKCS1_V1_5_PADDING: maxSize = xKeySize - 11
 *    - #SEC_RSA_OAEP_SHA_1_PADDING: maxSize = xKeySize - 2*20 - 2
 *    - #SEC_RSA_OAEP_SHA_256_PADDING: maxSize = xKeySize - 2*32 - 2
 *    - #SEC_RSA_OAEP_SHA_384_PADDING: maxSize = xKeySize - 2*48 - 2
 *    .
 *    If #SEC_RSA_NO_PADDING is used, xInputSize must be equal to xKeySize
 *
 *  @param[out]  pxOutput
 *    Buffer where to write resulting encrypted message. This buffer is always
 *    xKeySize bytes long.
 *
 *  @param[in]  xE
 *    Public RSA exponent e used for the operation. May be any of the following
 *    values: 3, 17, 65537.
 *
 *  @param[in]  pxN
 *    Buffer containing the RSA modulus n used for the operation. Buffer size is
 *    equal to key size.
 *
 *  @param[in]  xKeySize
 *    RSA key size in bytes
 *
 *  @param[in]  xPadding
 *    One of the valid padding types defined in TSecRsaPadding. If xPadding is
 *    equal to #SEC_RSA_NO_PADDING, the caller must ensure the message size is
 *    equal to key size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Size of input message not consistent: either too long if a padding
 *      scheme is specified, or different from key size in case of no padding.
 *    - Unsupported exponent
 *    - Unsupported padding scheme
 *    - Unsupported key size
 *    - Missing parameter (NULL pointer)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @remarks
 *    -# All buffers are allocated by the caller.
*/
typedef TSecStatus (*TSecRsaPublicEncrypt)
(
  const TUnsignedInt8*       pxInput,
        size_t                xInputSize,
        TUnsignedInt8*       pxOutput,
        TUnsignedInt32        xE,
  const TUnsignedInt8*       pxN,
        size_t                xKeySize,
        TSecRsaPadding        xPadding
);



/**
 *  @ingroup rsa
 *
 *  @brief
 *    This function pads a cleartext input message and RSA encrypts the padded
 *    message with the private key.
 *
 *    Padding schemes supported are OAEP and PKCS #1 v1.5. It is also possible
 *    to use this function with the special padding scheme #SEC_RSA_NO_PADDING.
 *    In such a case, the caller must ensure the input message size is equal to
 *    key size.
 *
 *  @param[in]  pxInput
 *    Input message to be encrypted.
 *
 *  @param[in]  xInputSize
 *    Size in bytes of input message to operate on. The maximum size depends on
 *    the key size and the padding scheme:
 *    - #SEC_RSA_PKCS1_V1_5_PADDING: maxSize = xKeySize - 11
 *    - #SEC_RSA_OAEP_SHA_1_PADDING: maxSize = xKeySize - 2*20 - 2
 *    - #SEC_RSA_OAEP_SHA_256_PADDING: maxSize = xKeySize - 2*32 - 2
 *    - #SEC_RSA_OAEP_SHA_384_PADDING: maxSize = xKeySize - 2*48 - 2
 *    .
 *    If #SEC_RSA_NO_PADDING is used, xInputSize must be equal to xKeySize
 *
 *  @param[out]  pxOutput
 *    Buffer where to write resulting encrypted message. This buffer is always
 *    xKeySize bytes long.
 *
 *  @param[in]  xE
 *    Public RSA exponent e. May be any of the following values: 3, 17, 65537.
 *
 *  @param[in]  pxN
 *    Buffer containing the RSA modulus n used for the operation. Buffer size is
 *    equal to key size.
 *
 *  @param[in]  pxP
 *    Buffer containing the private key prime number p. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxQ
 *    Buffer containing the private key prime number q. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxDP
 *    Buffer containing the private key CRT exponent dP. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxDQ
 *    Buffer containing the private key CRT exponent dQ. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxQInv
 *    Buffer containing the private key CRT coefficient qInv. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  xKeySize
 *    RSA key size in bytes
 *
 *  @param[in]  xPadding
 *    One of the valid padding types defined in TSecRsaPadding. If xPadding is
 *    equal to #SEC_RSA_NO_PADDING, the caller must ensure the message size is
 *    equal to key size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Size of input message not consistent: either too long if a padding
 *      scheme is specified, or different from key size in case of no padding.
 *    - Unsupported exponent
 *    - Unsupported padding scheme
 *    - Unsupported key size
 *    - Missing parameter (NULL pointer)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @remarks
 *    -# Although the main purpose of this function is to make private key
 *       operations, the public key (e, n) may be required if the underneath RSA
 *       implementation makes use of the cryptographic blinding technique.
 *       \n
 *    -# All buffers are allocated by the caller.
 *       \n
 *    -# A big number input parameter (n, p, q, dP, dQ, qInv) is provided by the
 *       caller through a byte array buffer in big endian format. If the
 *       effective size of the big number is smaller than the buffer size, it
 *       must be padded by the caller with leading zeros.
*/
typedef TSecStatus (*TSecRsaPrivateEncrypt)
(
  const TUnsignedInt8*       pxInput,
        size_t                xInputSize,
        TUnsignedInt8*       pxOutput,
        TUnsignedInt32        xE,
  const TUnsignedInt8*       pxN,
  const TUnsignedInt8*       pxP,
  const TUnsignedInt8*       pxQ,
  const TUnsignedInt8*       pxDP,
  const TUnsignedInt8*       pxDQ,
  const TUnsignedInt8*       pxQInv,
        size_t                xKeySize,
        TSecRsaPadding        xPadding
);



/**
 *  @ingroup rsa
 *
 *  @brief
 *    This function RSA decrypts a ciphered input message with the public key
 *    and removes the padding.
 *
 *    Padding schemes supported are OAEP and PKCS #1 v1.5. It is also possible
 *    to use this function with the special padding scheme #SEC_RSA_NO_PADDING.
 *    In such a case, the output message size is equal to key size.
 *
 *  @param[in]  pxInput
 *    Input message to be decrypted. This buffer is always xKeySize bytes long.
 *
 *  @param[out]  pxOutput
 *    Buffer where to write resulting decrypted message. This buffer is always
 *    xKeySize bytes long although the size of the decrypted message
 *    (pxOutputSize) may be smaller. The output message must start in
 *    pxOutput[0] and end up in pxOutput[*pxOutputSize-1].
 *
 *  @param[out]  pxOutputSize
 *    Size in bytes of output message after decryption and padding removal.
 *
 *  @param[in]  xE
 *    Public RSA exponent e used for the operation. May be any of the following
 *    values: 3, 17, 65537.
 *
 *  @param[in]  pxN
 *    Buffer containing the RSA modulus n used for the operation. Buffer size is
 *    equal to key size.
 *
 *  @param[in]  xKeySize
 *    RSA key size in bytes
 *
 *  @param[in]  xPadding
 *    One of the valid padding types defined in TSecRsaPadding. If xPadding is
 *    equal to #SEC_RSA_NO_PADDING, the caller must ensure the message size is
 *    equal to key size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Unsupported exponent
 *    - Unsupported padding scheme
 *    - Unsupported key size
 *    - Missing parameter (NULL pointer)
 *
 *  @retval  SEC_ERROR_BAD_PADDING
 *    The verification of the padding occurring after the RSA decryption
 *    has failed.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @remarks
 *    -# All buffers are allocated by the caller.
*/
typedef TSecStatus (*TSecRsaPublicDecrypt)
(
  const TUnsignedInt8*       pxInput,
        TUnsignedInt8*       pxOutput,
        size_t*              pxOutputSize,
        TUnsignedInt32        xE,
  const TUnsignedInt8*       pxN,
        size_t                xKeySize,
        TSecRsaPadding        xPadding
);



/**
 *  @ingroup rsa
 *
 *  @brief
 *    This function RSA decrypts a ciphered input message with the private key
 *    and removes the padding.
 *
 *    Padding schemes supported are OAEP and PKCS #1 v1.5. It is also possible
 *    to use this function with the special padding scheme #SEC_RSA_NO_PADDING.
 *    In such a case, the output message size is equal to key size.
 *
 *  @param[in]  pxInput
 *    Input message to be decrypted. This buffer is always xKeySize bytes long.
 *
 *  @param[out]  pxOutput
 *    Buffer where to write resulting decrypted message. This buffer is always
 *    xKeySize bytes long although the size of the decrypted message
 *    (pxOutputSize) may be smaller. The output message must start in
 *    pxOutput[0] and end in pxOutput[*pxOutputSize-1].
 *
 *  @param[out]  pxOutputSize
 *    Size in bytes of output message after decryption and padding removal.
 *
 *  @param[in]  xE
 *    Public RSA exponent e. May be any of the following values: 3, 17, 65537.
 *
 *  @param[in]  pxN
 *    Buffer containing the RSA modulus n used for the operation. Buffer size is
 *    equal to key size.
 *
 *  @param[in]  pxP
 *    Buffer containing the private key prime number p. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxQ
 *    Buffer containing the private key prime number q. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxDP
 *    Buffer containing the private key CRT exponent dP. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxDQ
 *    Buffer containing the private key CRT exponent dQ. The buffer is allocated
 *    by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  pxQInv
 *    Buffer containing the private key CRT coefficient qInv. The buffer is
 *    allocated by the caller and is xKeySize/2 bytes long.
 *
 *  @param[in]  xKeySize
 *    RSA key size in bytes
 *
 *  @param[in]  xPadding
 *    One of the valid padding types defined in TSecRsaPadding. If xPadding is
 *    equal to #SEC_RSA_NO_PADDING, the caller must ensure the message size is
 *    equal to key size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Unsupported exponent
 *    - Unsupported padding scheme
 *    - Unsupported key size
 *    - Missing parameter (NULL pointer)
 *
 *  @retval  SEC_ERROR_BAD_PADDING
 *    The verification of the padding occurring after the RSA decryption
 *    has failed.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @remarks
 *    -# Although the main purpose of this function is to make private key
 *       operations, the public key (e, n) may be required if the underneath RSA
 *       implementation makes use of the cryptographic blinding technique.
 *    \n
 *    -# All buffers are allocated by the caller.
 *    \n
 *    -# A big number input parameter (n, p, q, dP, dQ, qInv) is provided by the
 *       caller through a byte array buffer in big endian format. If the
 *       effective size of the big number is smaller than the buffer size, it
 *       must be padded by the caller with leading zeros.
*/
typedef TSecStatus (*TSecRsaPrivateDecrypt)
(
  const TUnsignedInt8*       pxInput,
        TUnsignedInt8*       pxOutput,
        size_t*              pxOutputSize,
        TUnsignedInt32        xE,
  const TUnsignedInt8*       pxN,
  const TUnsignedInt8*       pxP,
  const TUnsignedInt8*       pxQ,
  const TUnsignedInt8*       pxDP,
  const TUnsignedInt8*       pxDQ,
  const TUnsignedInt8*       pxQInv,
        size_t                xKeySize,
        TSecRsaPadding        xPadding
);



/******************************************************************************/
/*                                                                            */
/*                               DIFFIE-HELLMAN                               */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup dh
 *
 *  @brief
 *    Generate Diffie-Hellman public/private key pair from g and p parameters.
 *    The public key is equal to g^x mod p, where x is random number considered
 *    as the private key. If the private key is provided as input, only the
 *    public key is generated.
 *
 *  @param[in]  pxG
 *    Buffer containing the DH generator g used for the operation. The buffer is
 *    allocated by the caller and is xKeySize bytes long. The caller ensures it
 *    is padded with leading zeros if the effective size of g is smaller than
 *    the buffer size.
 *
 *  @param[in]  pxP
 *    Buffer containing the DH prime modulus p used for the operation. The
 *    buffer is allocated by the caller and is xKeySize bytes long.
 *
 *  @param[in]  pxInputPrivKey
 *    Buffer containing an optional input private key from which the public has
 *    to be generated. The buffer is allocated by the caller and is xKeySize
 *    bytes long. The caller ensures it is padded with leading zeros if the
 *    effective size of this private key is smaller than the buffer size.
 *    If no private key is provided as input (\c pxInputPrivKey=NULL), this
 *    function generates a random private key and stores it in pxOutputPrivKey
 *    buffer.
 *
 *  @param[out]  pxOutputPrivKey
 *    Buffer where to write the generated private key, in case no private key is
 *    provided as input (pxInputPrivKey==NULL). The buffer is allocated by the
 *    caller and is xKeySize bytes long. It must be padded with leading zeros
 *    if the effective size of the private key is smaller than the buffer size.
 *
 *  @param[out]  pxPubKey
 *    Buffer where to write the generated public key. The buffer is allocated by
 *    the caller and is xKeySize bytes long. It must be padded with leading
 *    zeros if the effective size of the public key is smaller than the buffer
 *    size.
 *
 *  @param[in]  xKeySize
 *    DH key size in bytes
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - A mandatory parameter (pxG, pxP or pxPubKey) is missing (NULL pointer)
 *    - Both pxInputPrivKey and pxOutputPrivKey are NULL
 *    - Unsupported key size
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecDhGenerateKey)
(
  const TUnsignedInt8*   pxG,
  const TUnsignedInt8*   pxP,
  const TUnsignedInt8*   pxInputPrivKey,
        TUnsignedInt8*   pxOutputPrivKey,
        TUnsignedInt8*   pxPubKey,
        size_t            xKeySize
);



/**
 *  @ingroup dh
 *
 *  @brief
 *    Compute Diffie-Hellman shared secret as otherPubKey^privKey mod p.
 *
 *  @param[in]  pxP
 *    Buffer containing the DH prime modulus p used for the operation. The
 *    buffer is allocated by the caller and is xKeySize bytes long.
 *
 *  @param[in]  pxPrivKey
 *    Buffer containing the DH private key. The buffer is allocated by the
 *    caller and is xKeySize bytes long. The caller ensures it is padded with
 *    leading zeros if the effective size of this key is smaller than the buffer
 *    size.
 *
 *  @param[in]  pxOtherPubKey
 *    Buffer containing the DH public key of the other peer. The buffer is
 *    allocated by the caller and is xKeySize bytes long. The caller ensures it
 *    is padded with leading zeros if the effective size of this key is smaller
 *    than the buffer size.
 *
 *  @param[out]  pxSharedSecret
 *    Buffer where to write the computed shared secret. The buffer is allocated
 *    by the caller and is xKeySize bytes long. It must padded with leading
 *    zeros if the effective size of this key is smaller than the buffer size.
 *
 *  @param[in]  xKeySize
 *    DH key size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    - Missing parameter (NULL pointer)
 *    - Unsupported key size
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecDhComputeKey)
(
  const TUnsignedInt8*   pxP,
  const TUnsignedInt8*   pxPrivKey,
  const TUnsignedInt8*   pxOtherPubKey,
        TUnsignedInt8*   pxSharedSecret,
        size_t            xKeySize
);



/******************************************************************************/
/*                                                                            */
/*                                    SHA-1                                   */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup sha
 *
 *  @brief
 *    Type used to link a sequence of operations together in a given context
 *    (e.g. SHA init, update and final). It is defined as a pointer to an opaque
 *    structure to be defined by the entity in charge of implementing the SEC
 *    API.
*/
typedef struct SSecHashContext* TSecHashContext;


/**
 *  @ingroup sha1
 *
 *  @brief
 *    Initializes staged SHA-1 message digesting.
 *
 *  @param[out]  pxContext
 *    Context assigned to this SHA-1 message digesting. It is passed back to
 *    TSecSha1Update() and TSecSha1Final().
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL context address (\c pxContext=NULL)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - The driver must be able to process several digest contexts in parallel.
*/
typedef TSecStatus (*TSecSha1Init)
(
  TSecHashContext*    pxContext
);



/**
 *  @ingroup sha1
 *
 *  @brief
 *    This function processes the next chunk of the message to be hashed.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[in]  pxMessageChunk
 *    Buffer containing the message chunk to be processed. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    cryptoprocessor constraints.
 *
 *  @param[in]  xChunkSize
 *    Size in bytes of the message chunk.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message chunk pointer (\c pxMessageChunk=NULL) with an non-null 
 *      chunk size (\c xChunkSize>0). Note that an null chunk size is not 
 *      considered as an error, whatever the value of \c pxMessageChunk.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - This function must be able to process an empty message chunk
 *      (\c xChunkSize=0).
*/
typedef TSecStatus (*TSecSha1Update)
(
        TSecHashContext  xContext,
  const TUnsignedInt8*  pxMessageChunk,
        size_t           xChunkSize
);



/**
 *  @ingroup sha1
 *
 *  @brief
 *    Finalizes SHA-1 stages and returns the message digest.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[out]  pxMessageDigest
 *    Buffer where to write the resulting message digest. The buffer is
 *    allocated by the caller and is 20 bytes (160 bits) long.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message digest pointer (\c pxMessageDigest=NULL).
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @warning
 *    - This function must free the context whenever a valid \c xContext 
 *      parameter is provided. This must be done independently on whether  \c 
 *      pxMessageDigest parameter is valid or not, or whether this function is 
 *      able to finalize the digest or not. Otherwise, there is a risk that 
 *      resources are never deallocated. For instance, if the caller provides a 
 *      valid context with \c pxMessageDigest=NULL, the function must free the 
 *      context and return #SEC_ERROR_BAD_PARAMETER.
*/
typedef TSecStatus (*TSecSha1Final)
(
  TSecHashContext  xContext,
  TUnsignedInt8*  pxMessageDigest
);



/******************************************************************************/
/*                                                                            */
/*                                    SHA-256                                 */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup sha256
 *
 *  @brief
 *    Initializes a staged SHA-256 message digesting.
 *
 *  @param[out]  pxContext
 *    Context assigned to this SHA-256 message digesting. It is passed back to
 *    TSecSha256Update() and TSecSha256Final().
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL context address (\c pxContext=NULL)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - The driver must be able to process several digest contexts in parallel.
*/
typedef TSecStatus (*TSecSha256Init)
(
  TSecHashContext*    pxContext
);



/**
 *  @ingroup sha256
 *
 *  @brief
 *    This function processes the next chunk of the message to be hashed.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[in]  pxMessageChunk
 *    Buffer containing the message chunk to be processed. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    cryptoprocessor constraints.
 *
 *  @param[in]  xChunkSize
 *    Size in bytes of the message chunk
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message chunk pointer (\c pxMessageChunk=NULL) with an non-null 
 *      chunk size (\c xChunkSize>0). Note that an null chunk size is not 
 *      considered as an error, whatever the value of \c pxMessageChunk.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - This function must be able to process an empty message chunk
 *      (\c xChunkSize=0).
*/
typedef TSecStatus (*TSecSha256Update)
(
        TSecHashContext  xContext,
  const TUnsignedInt8*  pxMessageChunk,
        size_t           xChunkSize
);



/**
 *  @ingroup sha256
 *
 *  @brief
 *    Finalizes SHA stages and returns the message digest.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[out]  pxMessageDigest
 *    Buffer where to write the resulting message digest. The buffer is
 *    allocated by the caller and is 32 bytes (256 bits) long.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message digest pointer (\c pxMessageDigest=NULL).
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @warning
 *    - This function must free the context whenever a valid \c xContext 
 *      parameter is provided. This must be done independently on whether  \c 
 *      pxMessageDigest parameter is valid or not, or whether this function is 
 *      able to finalize the digest or not. Otherwise, there is a risk that 
 *      resources are never deallocated. For instance, if the caller provides a 
 *      valid context with \c pxMessageDigest=NULL, the function must free the 
 *      context and return #SEC_ERROR_BAD_PARAMETER.
*/
typedef TSecStatus (*TSecSha256Final)
(
  TSecHashContext  xContext,
  TUnsignedInt8*  pxMessageDigest
);


/******************************************************************************/
/*                                                                            */
/*                                    SHA-384                                 */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup sha384
 *
 *  @brief
 *    Initializes a staged SHA-384 message digesting.
 *
 *  @param[out]  pxContext
 *    Context assigned to this SHA-384 message digesting. It is passed back to
 *    TSecSha384Update() and TSecSha384Final().
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL context address (\c pxContext=NULL)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - The driver must be able to process several digest contexts in parallel.
*/
typedef TSecStatus (*TSecSha384Init)
(
  TSecHashContext*    pxContext
);



/**
 *  @ingroup sha384
 *
 *  @brief
 *    This function processes the next chunk of the message to be hashed.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[in]  pxMessageChunk
 *    Buffer containing the message chunk to be processed. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    cryptoprocessor constraints.
 *
 *  @param[in]  xChunkSize
 *    Size in bytes of the message chunk
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message chunk pointer (\c pxMessageChunk=NULL) with an non-null 
 *      chunk size (\c xChunkSize>0). Note that an null chunk size is not 
 *      considered as an error, whatever the value of \c pxMessageChunk.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - This function must be able to process an empty message chunk
 *      (\c xChunkSize=0).
*/
typedef TSecStatus (*TSecSha384Update)
(
        TSecHashContext  xContext,
  const TUnsignedInt8*  pxMessageChunk,
        size_t           xChunkSize
);



/**
 *  @ingroup sha384
 *
 *  @brief
 *    Finalizes SHA stages and returns the message digest.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[out]  pxMessageDigest
 *    Buffer where to write the resulting message digest. The buffer is
 *    allocated by the caller and is 48 bytes (384 bits) long.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message digest pointer (\c pxMessageDigest=NULL).
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @warning
 *    - This function must free the context whenever a valid \c xContext 
 *      parameter is provided. This must be done independently on whether  \c 
 *      pxMessageDigest parameter is valid or not, or whether this function is 
 *      able to finalize the digest or not. Otherwise, there is a risk that 
 *      resources are never deallocated. For instance, if the caller provides a 
 *      valid context with \c pxMessageDigest=NULL, the function must free the 
 *      context and return #SEC_ERROR_BAD_PARAMETER.
*/
typedef TSecStatus (*TSecSha384Final)
(
  TSecHashContext  xContext,
  TUnsignedInt8*  pxMessageDigest
);


/******************************************************************************/
/*                                                                            */
/*                                    HMAC                                    */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup hmacsha256
 *
 *  @brief
 *    Initializes a staged HMAC-SHA-256 message authentication digesting.
 *
 *  @param[in]  pxKey
 *    HMAC key used for the operation
 *
 *  @param[in]  xKeySize
 *    Size in bytes of the HMAC key. The maximum key size is equal to the
 *    SHA-256 block size, i.e. 64 bytes. If a longer key has to be used, the
 *    caller is in charge of hashing it beforehand.
 *
 *  @param[out]  pxContext
 *    Context assigned to this HMAC-SHA-256 message digesting. It is passed back
 *    to TSecHmacSha256Update() and TSecHmacSha256Final().
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL key (\c xKeySize=NULL) with a non-null key size (xKeySize>0). Note 
 *      that an null key size is not considered as an error, whatever the value 
 *      of \c pxKey.
 *    - Invalid key size (xKeySize>16)
 *    - NULL context (\c pxContext=NULL)
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - The driver must be able to process several digest contexts in parallel.
 *    - This function must be able to process a digest with an empty key
 *      (\c xKeySize=0).
*/
typedef TSecStatus (*TSecHmacSha256Init)
(
  const TUnsignedInt8*      pxKey,
        size_t               xKeySize,
        TSecHashContext*    pxContext
);


/**
 *  @ingroup hmacsha256
 *
 *  @brief
 *    Updates the staged HMAC-SHA-256 authentication digesting with the next
 *    message chunk.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[in]  pxMessageChunk
 *    Buffer containing the message chunk to be processed. It must be allocated by
 *    TSecAllocateBuffer() or a similar function that ensures compatibility with
 *    cryptoprocessor constraints.
 *
 *  @param[in]  xChunkSize
 *    Size in bytes of the message chunk
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message chunk pointer (\c pxMessageChunk=NULL) with an non-null 
 *      chunk size (\c xChunkSize>0). Note that an null chunk size is not 
 *      considered as an error, whatever the value of \c pxMessageChunk.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @note
 *    - This function must be able to process an empty message chunk
 *      (\c xChunkSize=0).
*/
typedef TSecStatus (*TSecHmacSha256Update)
(
        TSecHashContext  xContext,
  const TUnsignedInt8*  pxMessageChunk,
        size_t           xChunkSize
);


/**
 *  @ingroup hmacsha256
 *
 *  @brief
 *    Finalizes HMAC-SHA-256 stages and returns the message digest.
 *
 *  @param[in]  xContext
 *    Message hashing context
 *
 *  @param[out]  pxMessageDigest
 *    Buffer where to write the resulting message digest. The buffer is
 *    allocated by the caller and is 32 bytes (256 bits) long.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    An invalid parameter is provided:
 *    - NULL or unknown context
 *    - NULL message digest pointer (\c pxMessageDigest=NULL).
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
 *
 *  @warning
 *    - This function must free the context whenever a valid \c xContext 
 *      parameter is provided. This must be done independently on whether  \c 
 *      pxMessageDigest parameter is valid or not, or whether this function is 
 *      able to finalize the digest or not. Otherwise, there is a risk that 
 *      resources are never deallocated. For instance, if the caller provides a 
 *      valid context with \c pxMessageDigest=NULL, the function must free the 
 *      context and return #SEC_ERROR_BAD_PARAMETER.
*/ 
typedef TSecStatus (*TSecHmacSha256Final)
(
  TSecHashContext  xContext,
  TUnsignedInt8*  pxMessageDigest
);


/******************************************************************************/
/*                                                                            */
/*                                  RANDOM                                    */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup rand
 *
 *  @brief
 *    Generate a sequence of true random bytes and store it in specified buffer.
 *
 *    The random number shall be non-deterministic and, at a minimum, comply with
 *    random number generator tests as specified in FIPS 140-2, Security
 *    Requirements for Cryptographic Modules, section 4.9.1.
 *
 *  @param[in]  xNumOfBytes
 *    Number of random bytes to be generated. The maximum number is limited to
 *    1024 bytes.
 *
 *  @param[out]  pxRandomBytes
 *    Buffer where to write the xNumOfBytes generated random bytes.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    Missing or malformed parameters provided resulting in a premature
 *    termination of the operation.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and no random data could be generated.
*/
typedef TSecStatus (*TSecGenerateRandomBytes)
(
  size_t           xNumOfBytes,
  TUnsignedInt8*  pxRandomBytes
);


/******************************************************************************/
/*                                                                            */
/*                                    ECDSA                                   */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup ecdsa ecdh
 *
 *  @brief
 *    Elliptic curve domain parameters. Refer to \ref p_ec for further information
 *    about the curve to be supported.
 *
 *    All these domain parameters are considered as big numbers and are provided
 *    through SEC client's buffers being keySize bytes long. The SEC client is
 *    in charge padding each buffer with leading zeros if the effective size of
 *    the domain parameter conveyed is smaller than keySize.
*/
typedef struct
{
  TUnsignedInt8* q;
  /**<  Finite field: equal to p in case of prime field curves or equal
   *    to 2^n in case of binary field curves.
  */
  TUnsignedInt8* a;
  /**<  Curve parameter a (q-3 in Suite B)
  */
  TUnsignedInt8* b;
  /**<  Curve parameter b
  */
  TUnsignedInt8* GX;
  /**<  X coordinates of G which is a base point on the curve
  */
  TUnsignedInt8* GY;
  /**<  Y coordinates of G which is a base point on the curve
  */
  TUnsignedInt8* n;
  /**<  Prime which is the order of G point
  */
  TUnsignedInt8* h;
  /**<  Cofactor, which is the order of the elliptic curve divided by the order
   *    of the point G. For the Suite B curves, h = 1.
  */
  size_t         keySize;
  /**<  Key size in bytes. It corresponds to the size in bytes of the prime n
   *    and is equal to:
   *    - P-160: 21 bytes
   *    - P-224: 28 bytes
   *    - P-256: 32 bytes
   *    - P-384: 48 bytes
  */
} TSecEcParams;


/**
 *  @ingroup ecdsa
 *
 *  @brief
 *    Generate ECDSA public/private key pair.
 *
 *    A private key may be provided as input, in which case only the public is
 *    generated by this function.
 *
 *  @param[in]  xParams
 *    Elliptic curve domain parameters. They are considered as big numbers and
 *    are provided through buffers allocated by the caller and being
 *    xParams.keySize bytes long. The caller is in charge padding each buffer
 *    with leading zeros if the effective size of the domain parameter conveyed
 *    is smaller than xParams.keySize.
 *
 *  @param[in]  pxInputPrivKey
 *    Buffer containing an optional input private key from which the public has
 *    to be generated. The buffer is allocated by the caller and is
 *    xParams.keySize bytes long. The caller ensures it is padded with leading
 *    zeros if the effective size of this private key is smaller than the buffer
 *    size. If no private key is provided as input (pxInputPrivKey=NULL), this
 *    function generates a random private key and stores it in pxOutputPrivKey
 *    buffer.
 *
 *  @param[out]  pxOutputPrivKey
 *    Buffer where to write the generated private key, in case no private key is
 *    provided as input (pxInputPrivKey==NULL). The buffer is allocated by the
 *    caller and is xParams.keySize bytes long. It must be padded with leading
 *    zeros if the effective size of the private key is smaller than the buffer
 *    size.
 *
 *  @param[out]  pxPubKeyX
 *    Buffer where to write the X coordinates of the generated public key. The
 *    buffer is allocated by the caller and is xParams.keySize bytes long. It
 *    must be padded with leading zeros if the effective size of the public key
 *    X coordinates is smaller than the buffer size.
 *
 *  @param[out]  pxPubKeyY
 *    Buffer where to write the Y coordinates of the generated public key. The
 *    buffer is allocated by the caller and is xParams.keySize bytes long. It
 *    must be padded with leading zeros if the effective size of the public key
 *    Y coordinates is smaller than the buffer size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    Missing or malformed parameters provided resulting in a premature
 *    termination of the operation.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecEcdsaGenerateKey)
(
        TSecEcParams     xParams,
  const TUnsignedInt8*  pxInputPrivKey,
        TUnsignedInt8*  pxOutputPrivKey,
        TUnsignedInt8*  pxPubKeyX,
        TUnsignedInt8*  pxPubKeyY
);



/**
 *  @ingroup ecdsa
 *
 *  @brief
 *    Sign a message with ECDSA algorithm and returns an uncompressed signature
 *    made of the pair (r, s).
 *
 *  @param[in]  xParams
 *    Elliptic curve domain parameters. They are considered as big numbers and
 *    are provided through buffers allocated by the caller and being
 *    xParams.keySize bytes long. The caller is in charge padding each buffer
 *    with leading zeros if the effective size of the domain parameter conveyed
 *    is smaller than xParams.keySize.
 *
 *  @param[in]  xHashType
 *    One of the hash algorithm defined in TSecHashType
 *
 *  @param[in]  pxPrivKey
 *    Buffer containing the private key used for signing the message. The buffer
 *    is allocated by the caller and is xParams.keySize bytes long. The caller
 *    ensures it is padded with leading zeros if the effective size of this
 *    private key is smaller than the buffer size.
 *
 *  @param[in]  pxMessage
 *    Message to be signed.
 *
 *  @param[in]  pxMessageSize
 *    Size in bytes of message to be signed.
 *
 *  @param[out]  pxSigR
 *    Buffer where to write the uncompressed r component of the resulting
 *    signature. The buffer is allocated by the caller and is xParams.keySize
 *    bytes long. It must be padded with leading zeros if the effective size of
 *    r is smaller than the buffer size.
 *
 *  @param[out]  pxSigS
 *    Buffer where to write the uncompressed s component of the resulting
 *    signature. The buffer is allocated by the caller and is xParams.keySize
 *    bytes long. It must be padded with leading zeros if the effective size of
 *    s is smaller than the buffer size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    Missing or malformed parameters provided resulting in a premature
 *    termination of the operation.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecEcdsaSign)
(
        TSecEcParams     xParams,
        TSecHashType     xHashType,
  const TUnsignedInt8*  pxPrivKey,
  const TUnsignedInt8*  pxMessage,
        size_t           xMessageSize,
        TUnsignedInt8*  pxSigR,
        TUnsignedInt8*  pxSigS
);



/**
 *  @ingroup ecdsa
 *
 *  @brief
 *    Verify an ECDSA signature made of an uncompressed pair (r, s).
 *
 *  @param[in]  xParams
 *    Elliptic curve domain parameters. They are considered as big numbers and
 *    are provided through buffers allocated by the caller and being
 *    xParams.keySize bytes long. The caller is in charge padding each buffer
 *    with leading zeros if the effective size of the domain parameter conveyed
 *    is smaller than xParams.keySize.
 *
 *  @param[in]  xHashType
 *    One of the hash algorithm defined in TSecHashType
 *
 *  @param[in]  pxPubKeyX
 *    Buffer containing the public key X coordinates used for verifying the
 *    signature. The buffer is allocated by the caller and is xParams.keySize
 *    bytes long. It is padded by the caller with leading zeros if the effective
 *    size of this public key coordinates is smaller than the buffer size.
 *
 *  @param[in]  pxPubKeyY
 *    Buffer containing the public key Y coordinates used for verifying the
 *    signature. The buffer is allocated by the caller and is xParams.keySize
 *    bytes long. It is padded by the caller with leading zeros if the effective
 *    size of this public key coordinates is smaller than the buffer size.
 *
 *  @param[in]  pxMessage
 *    Signed message
 *
 *  @param[in]  pxMessageSize
 *    Size in bytes of signed message.
 *
 *  @param[in]  pxSigR
 *    Buffer containing the uncompressed r component of the signature to be
 *    verified. The buffer is allocated by the caller and is xParams.keySize
 *    bytes long. It is padded by the caller with leading zeros if the effective
 *    size of r is smaller than the buffer size.
 *
 *  @param[in]  pxSigS
 *    Buffer containing the uncompressed s component of the signature to be
 *    verified. The buffer is allocated by the caller and is xParams.keySize
 *    bytes long. It is padded by the caller with leading zeros if the effective
 *    size of s is smaller than the buffer size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed and the verification of the signature is OK.
 *
 *  @retval  SEC_ERROR_BAD_SIGNATURE
 *    The operation was completed but the verification of the signature failed.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    Missing or malformed parameters provided resulting in a premature
 *    termination of the operation.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecEcdsaVerify)
(
        TSecEcParams     xParams,
        TSecHashType     xHashType,
  const TUnsignedInt8*  pxPubKeyX,
  const TUnsignedInt8*  pxPubKeyY,
  const TUnsignedInt8*  pxMessage,
        size_t           xMessageSize,
  const TUnsignedInt8*  pxSigR,
  const TUnsignedInt8*  pxSigS
);



/******************************************************************************/
/*                                                                            */
/*                                    ECDH                                   */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup ecdh
 *
 *  @brief
 *    Generate ECDH public/private key pair.
 *
 *    A private key may be provided as input, in which case only the public is
 *    generated by this function.
 *
 *  @param[in]  xParams
 *    Elliptic curve domain parameters. They are considered as big numbers and
 *    are provided through buffers allocated by the caller and being
 *    xParams.keySize bytes long. The caller is in charge padding each buffer
 *    with leading zeros if the effective size of the domain parameter conveyed
 *    is smaller than xParams.keySize.
 *
 *  @param[in]  pxInputPrivKey
 *    Buffer containing an optional input private key from which the public has
 *    to be generated. The buffer is allocated by the caller and is
 *    xParams.keySize bytes long. It is padded by the caller with leading zeros
 *    if the effective size of this private key is smaller than the buffer size.
 *    If no private key is provided as input (pxInputPrivKey=NULL), this
 *    function generates a random private key and stores it in pxOutputPrivKey
 *    buffer.
 *
 *  @param[out]  pxOutputPrivKey
 *    Buffer where to write the generated private key, in case no private key is
 *    provided as input (pxInputPrivKey==NULL). The buffer is allocated by the
 *    caller and is xParams.keySize bytes long. It must be padded with leading
 *    zeros if the effective size of the private key is smaller than the buffer
 *    size.
 *
 *  @param[out]  pxPubKeyX
 *    Buffer where to write the X coordinates of the generated public key. The
 *    buffer is allocated by the caller and is xParams.keySize bytes long. It
 *    must be padded with leading zeros if the effective size of the public key
 *    X coordinates is smaller than the buffer size.
 *
 *  @param[out]  pxPubKeyY
 *    Buffer where to write the Y coordinates of the generated public key. The
 *    buffer is allocated by the caller and is xParams.keySize bytes long. It
 *    must be padded with leading zeros if the effective size of the public key
 *    Y coordinates is smaller than the buffer size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    Missing or malformed parameters provided resulting in a premature
 *    termination of the operation.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecEcdhGenerateKey)
(
        TSecEcParams     xParams,
  const TUnsignedInt8*  pxInputPrivKey,
        TUnsignedInt8*  pxOutputPrivKey,
        TUnsignedInt8*  pxPubKeyX,
        TUnsignedInt8*  pxPubKeyY
);



/**
 *  @ingroup ecdh
 *
 *  @brief
 *    Compute ECDH shared secret key. This key corresponds to the X coordinates
 *    of the computed P point.
 *
 *  @param[in]  xParams
 *    Elliptic curve domain parameters. They are considered as big numbers and
 *    are provided through buffers allocated by the caller and being
 *    xParams.keySize bytes long. The caller is in charge padding each buffer
 *    with leading zeros if the effective size of the domain parameter conveyed
 *    is smaller than xParams.keySize.
 *
 *  @param[in]  pxPrivKey
 *    Buffer containing the ECDH private key. The buffer is allocated by the
 *    caller and is xParams.keySize bytes long. It is padded by the caller with
 *    leading zeros if the effective size of this private key is smaller than
 *    the buffer size.
 *
 *  @param[in]  pxOtherPubKeyX
 *    Buffer containing the X coordinates of other peer's ECDH public key. The
 *    buffer is allocated by the caller and is xParams.keySize bytes long. It is
 *    padded by the caller with leading zeros if the effective size of the
 *    public key X coordinates is smaller than the buffer size.
 *
 *  @param[in]  pxOtherPubKeyY
 *    Buffer containing the Y coordinates of other peer's ECDH public key. The
 *    buffer is allocated by the caller and is xParams.keySize bytes long. It is
 *    padded by the caller with leading zeros if the effective size of the
 *    public key Y coordinates is smaller than the buffer size.
 *
 *  @param[out]  pxSharedSecret
 *    Buffer where to write the shared secret corresponding to the X coordinates
 *    of the computed P point. The buffer is allocated by the caller and is
 *    xParams.keySize bytes long. It must padded with leading zeros if the
 *    effective size of the shared secret is smaller than the buffer size.
 *
 *  @retval  SEC_NO_ERROR
 *    The operation was completed successfully.
 *
 *  @retval  SEC_ERROR_BAD_PARAMETER
 *    Missing or malformed parameters provided resulting in a premature
 *    termination of the operation.
 *
 *  @retval  SEC_ERROR
 *    Errors occurred and the operation could not be completed successfully.
*/
typedef TSecStatus (*TSecEcdhComputeKey)
(
        TSecEcParams     xParams,
  const TUnsignedInt8*  pxPrivKey,
  const TUnsignedInt8*  pxOtherPubKeyX,
  const TUnsignedInt8*  pxOtherPubKeyY,
        TUnsignedInt8*  pxSharedSecret
);



/******************************************************************************/
/*                                                                            */
/*                               FUNCTION TABLE                               */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup functionTable
 *
 *  @brief
 *    Structure defining the SEC function table.
 */
typedef struct
{
  TUnsignedInt32                secApiVersion;
  /**< Version of the SEC API. Use the macro SECAPI_VERSION_INT to assign the
   *   right value.
   */
  TSecGetNuid                   secGetNuid;
  /**< Get chipset NUID (32 bits)
    */
  TSecGetChipsetRevision        secGetChipsetRevision;
  /**< Get chipset revision
    */
  TSecEncryptData               secEncryptData;
  /**< RAM2RAM encryption
    */
  TSecDecryptData               secDecryptData;
  /**< RAM2RAM decryption
    */
  TSecGenerateRandomBytes       secGenerateRandomBytes;
  /**< Generate a sequence of random bytes
    */
  TSecRsaGenerateKey            secRsaGenerateKey;
  /**< Generate RSA private key
    */
  TSecRsaPublicEncrypt          secRsaPublicEncrypt;
  /**< RSA encryption using public key
    */
  TSecRsaPrivateEncrypt         secRsaPrivateEncrypt;
  /**< RSA encryption using private key
    */
  TSecRsaPublicDecrypt          secRsaPublicDecrypt;
  /**< RSA decryption using public key
    */
  TSecRsaPrivateDecrypt         secRsaPrivateDecrypt;
  /**< RSA decryption using private key
    */
  TSecDhGenerateKey             secDhGenerateKey;
  /**< Generate Diffie-Hellman keys
    */
  TSecDhComputeKey              secDhComputeKey;
  /**< Compute Diffie-Hellman shared secret
    */
  TSecSha1Init                  secSha1Init;
  /**< Initialize SHA-1 message digest
    */
  TSecSha1Update                secSha1Update;
  /**< Update SHA-1 message digest
    */
  TSecSha1Final                 secSha1Final;
  /**< Finalize SHA-1 message digest
    */
  TSecSha256Init                secSha256Init;
  /**< Initialize SHA-256 message digest
    */
  TSecSha256Update              secSha256Update;
  /**< Update SHA-256 message digest
    */
  TSecSha256Final               secSha256Final;
  /**< Finalize SHA-256 message digest
    */
  TSecHmacSha256Init            secHmacSha256Init;
  /**< Initialize HMAC-SHA-256 message digest
    */
  TSecHmacSha256Update          secHmacSha256Update;
  /**< Update HMAC-SHA-256 message digest
    */
  TSecHmacSha256Final           secHmacSha256Final;
  /**< Finalize HMAC-SHA-256 message digest
    */
  TSecEcdsaGenerateKey          secEcdsaGenerateKey;
  /**< Generate an ECDSA key pair
    */
  TSecEcdsaSign                 secEcdsaSign;
  /**< Sign a message with ECDSA
    */
  TSecEcdsaVerify               secEcdsaVerify;
  /**< Verify an ECDSA signature
    */
  TSecEcdhGenerateKey           secEcdhGenerateKey;
  /**< Generate ECDH public/private key pair
    */
  TSecEcdhComputeKey           secEcdhComputeKey;
  /**< Compute ECDH shared secret key
    */
  TSecOpenRam2RamEncryptSession secOpenRam2RamEncryptSession;
  /**< Open a RAM2RAM encryption session
    */
  TSecOpenRam2RamDecryptSession secOpenRam2RamDecryptSession;
  /**< Open a RAM2RAM decryption session
    */
  TSecCloseSession              secCloseSession;
  /**< Close a block cipher encryption or decryption session
    */
  TSecSetClearTextKey           secSetClearTextKey;
  /**< Set a clear-text key in a RAM2RAM key table
    */
  TSecSet2LevelProtectedKey     secSet2LevelProtectedKey;
  /**< Set protected keys in a 2-level key ladder crypto-engine
    */
  TSecUseCertKey                secUseCertKey;
  /**< Use the CERT key for RAM2RAM operations
    */
  TSecSessionEncrypt            secSessionEncrypt;
  /**< Perform RAM2RAM encryption operations
    */
  TSecSessionDecrypt            secSessionDecrypt;
  /**< Perform RAM2RAM decryption operations
    */
  TSecGetNuid64                 secGetNuid64;
  /**< Get chipset NUID (64 bits)
    */
  TSecGetChipsetExtension       secGetChipsetExtension;
  /**< Get chipset extension
    */
  TSecSha384Init                secSha384Init;
  /**< Initialize SHA-384 message digest
    */
  TSecSha384Update              secSha384Update;
  /**< Update SHA-384 message digest
    */
  TSecSha384Final               secSha384Final;
  /**< Finalize SHA-384 message digest
    */
  TSecRsaComputeCrtParams       secRsaComputeCrtParams;
  /**< Computes RSA CRT parameters dP, dQ and qInv.
    */
  TSecEncryptFlashProtKey       secEncryptFlashProtKey;
  /**< Encrypt the flash protection key with the flash protection root key
    */
  TSecUseFlashProtKey           secUseFlashProtKey;
  /**< Use the flash protection key for RAM2RAM operations
    */
  TSecOpenStreamEncryptSession secOpenStreamEncryptSession;
  /**< Open a stream encryption session
    */
  TSecOpenStreamDecryptSession secOpenStreamDecryptSession;
  /**< Open a stream decryption session
    */
  TSecSet0LevelProtectedKey    secSet0LevelProtectedKey;
  /**< Set protected keys in a 0-level key ladder crypto-engine
    */
  TSecSet1LevelProtectedKey    secSet1LevelProtectedKey;
  /**< Set protected keys in a 1-level key ladder crypto-engine
    */
  TSecSetMetadata              secSetMetadata;
  /**< Associate metadata to a stream encryption/decryption session
    */
  TSecAllocateBuffer           secAllocateBuffer;
  /**< Allocate a cryptoprocessor compliant buffer
    */
  TSecFreeBuffer               secFreeBuffer;
  /**< Free a cryptoprocessor compliant buffer
    */
  TSecUseLegacyKey             secUseLegacyKey;
  /**< Use the legacy secret key
    */
} TSecFunctionTable;


/**
 *  @ingroup functionTable
 *
 *  @brief
 *    This function returns a pointer to the SEC driver function table if
 *    successful, NULL in case of error.
 *
 *  @warning
 *    This function must not allocate memory for the function table because it
 *    will be never freed. The function table is purely static for a given
 *    implementation, thus it is much better and simpler to declare the table as
 *    a static global variable and simply returns its address as depicted in the
 *    sample code below.
 *    \code
  static TSecFunctionTable    gSecFunctionTable =
  {
      SECAPI_VERSION_INT,
      secGetNuid,
      ...
  };

  TSecFunctionTable* secGetFunctionTable(void)
  {
    return &gSecFunctionTable;
  }
 *    \endcode
 *
*/
TSecFunctionTable* secGetFunctionTable
(
  void
);



#endif /* CA_SEC_H */

/* END OF FILE */
