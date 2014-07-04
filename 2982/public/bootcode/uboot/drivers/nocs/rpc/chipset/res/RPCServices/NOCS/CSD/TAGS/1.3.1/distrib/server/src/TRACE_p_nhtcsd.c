/**
 * File: $Id:$
 *
 *  This file implements the server specific CSD API/EAPI function traces.
 *
 *  Copyright (c) 2013 Nagravision. All rights reserved.
 *  CH-1033 Cheseaux, Switzerland
 *  Tel: +41 21 7320311  Fax: +41 21 7320100
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
 *  Security Policy of Nagravision Kudelski Group
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 **/


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/TRACE_p_nhtcsd.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_strbuilder.h"

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


#ifdef _NHT_RPC_TRACE_ON_

/* */
TCsdStatus _CRPC(nhtCsdOpenR2RKeyPathHandle)
(
  TCsdR2RKeyPathHandle ** pxR2RKeyPathHandle
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdOpenR2RKeyPathHandle():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxR2RKeyPathHandle", (void*)pxR2RKeyPathHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdOpenR2RKeyPathHandle (pxR2RKeyPathHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdOpenR2RKeyPathHandle():\n");
    if (pxR2RKeyPathHandle && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxR2RKeyPathHandle", (void*)*pxR2RKeyPathHandle);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdCloseR2RKeyPathHandle)
(
  TCsdR2RKeyPathHandle * pxR2RKeyPathHandle
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdCloseR2RKeyPathHandle():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxR2RKeyPathHandle", (void*)pxR2RKeyPathHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdCloseR2RKeyPathHandle (pxR2RKeyPathHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdCloseR2RKeyPathHandle():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/******************************************************************************/
/*                                                                            */
/*               NOCS1.x RAM2RAM Functions                                    */
/*                                                                            */
/******************************************************************************/


/* */
TCsdStatus _CRPC(csdEncryptDataWithClearTextHostKey)
(
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TCsdR2RKeyPathHandle       * pxR2RKeyPathHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdEncryptDataWithClearTextHostKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xAlgorithm", (size_t)xAlgorithm, sizeof(TCsdR2RAlgorithm));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMode", (size_t)xMode, sizeof(TCsdR2RCryptoOperationMode));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextHostKeySize", (size_t)xClearTextHostKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextHostKey", (const void*)pxClearTextHostKey, (size_t)xClearTextHostKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (const void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xRefreshIv", (size_t)xRefreshIv, sizeof(TCsdBoolean));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxR2RKeyPathHandle", (void*)pxR2RKeyPathHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in:pxInputData", (const void*)pxInputData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputData", (void*)pxOutputData);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdEncryptDataWithClearTextHostKey (
    xAlgorithm,
    xMode,
    pxClearTextHostKey,
    xClearTextHostKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    pxR2RKeyPathHandle,
    pxInputData,
    pxOutputData,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdEncryptDataWithClearTextHostKey():\n");
    if (pxOutputData && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputData", (void*)pxOutputData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdDecryptDataWithClearTextHostKey)
(
        TCsdR2RAlgorithm             xAlgorithm,
        TCsdR2RCryptoOperationMode   xMode,
  const TCsdUnsignedInt8           * pxClearTextHostKey,
        TCsdSize                     xClearTextHostKeySize,
  const TCsdUnsignedInt8           * pxInitializationVector,
        TCsdSize                     xInitializationVectorSize,
        TCsdBoolean                  xRefreshIv,
        TCsdR2RKeyPathHandle       * pxR2RKeyPathHandle,
  const TCsdUnsignedInt8           * pxInputData,
        TCsdUnsignedInt8           * pxOutputData,
        TCsdSize                     xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdDecryptDataWithClearTextHostKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xAlgorithm", (size_t)xAlgorithm, sizeof(TCsdR2RAlgorithm));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMode", (size_t)xMode, sizeof(TCsdR2RCryptoOperationMode));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextHostKeySize", (size_t)xClearTextHostKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextHostKey", (const void*)pxClearTextHostKey, (size_t)xClearTextHostKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (const void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xRefreshIv", (size_t)xRefreshIv, sizeof(TCsdBoolean));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxR2RKeyPathHandle", (void*)pxR2RKeyPathHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in:pxInputData", (const void*)pxInputData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputData", (void*)pxOutputData);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdDecryptDataWithClearTextHostKey (
    xAlgorithm,
    xMode,
    pxClearTextHostKey,
    xClearTextHostKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    pxR2RKeyPathHandle,
    pxInputData,
    pxOutputData,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdDecryptDataWithClearTextHostKey():\n");
    if (pxOutputData && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputData", (void*)pxOutputData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdEncryptDataWithSecretContentKey)
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8              * pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8              * pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TCsdR2RKeyPathHandle          * pxR2RKeyPathHandle,
  const TCsdUnsignedInt8              * pxInputData,
        TCsdUnsignedInt8              * pxOutputData,
        TCsdSize                        xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdEncryptDataWithClearTextHostKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xAlgorithm", (size_t)xAlgorithm, sizeof(TCsdR2RAlgorithm));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMode", (size_t)xMode, sizeof(TCsdR2RCryptoOperationMode));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: xR2RCipheredProtectingKeys", &xR2RCipheredProtectingKeys[0][0], 16 * CSD_R2R_NB_OF_PROTECTING_KEYS);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: pxCipheredContentKey", &pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (const void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xRefreshIv", (size_t)xRefreshIv, sizeof(TCsdBoolean));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxR2RKeyPathHandle", (void*)pxR2RKeyPathHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputData", (const void*)pxInputData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputData", (void*)pxOutputData);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdEncryptDataWithSecretContentKey (
    xAlgorithm,
    xMode,
    xR2RCipheredProtectingKeys,
    pxCipheredContentKey,
    xCipheredContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    pxR2RKeyPathHandle,
    pxInputData,
    pxOutputData,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdEncryptDataWithClearTextHostKey():\n");
    if (pxOutputData && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputData", (void*)pxOutputData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdDecryptDataWithSecretContentKey)
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8*              pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8*              pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                   xRefreshIv,
        TCsdR2RKeyPathHandle*          pxR2RKeyPathHandle,
  const TCsdUnsignedInt8*              pxInputData,
        TCsdUnsignedInt8*              pxOutputData,
        TCsdSize                        xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdDecryptDataWithSecretContentKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xAlgorithm", (size_t)xAlgorithm, sizeof(TCsdR2RAlgorithm));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMode", (size_t)xMode, sizeof(TCsdR2RCryptoOperationMode));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: xR2RCipheredProtectingKeys", &xR2RCipheredProtectingKeys[0][0], 16 * CSD_R2R_NB_OF_PROTECTING_KEYS);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: pxCipheredContentKey", &pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (const void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xRefreshIv", (size_t)xRefreshIv, sizeof(TCsdBoolean));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxR2RKeyPathHandle", (void*)pxR2RKeyPathHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputData", (const void*)pxInputData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputData", (void*)pxOutputData);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdDecryptDataWithSecretContentKey (
    xAlgorithm,
    xMode,
    xR2RCipheredProtectingKeys,
    pxCipheredContentKey,
    xCipheredContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize,
    xRefreshIv,
    pxR2RKeyPathHandle,
    pxInputData,
    pxOutputData,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdDecryptDataWithSecretContentKey():\n");
    if (pxOutputData && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputData", (void*)pxOutputData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


#endif /* _NHT_RPC_TRACE_ON_ */
