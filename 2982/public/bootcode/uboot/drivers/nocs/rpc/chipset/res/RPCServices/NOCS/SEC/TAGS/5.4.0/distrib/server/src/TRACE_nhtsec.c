/**
 * File: $Id:$
 *
 *  This file implements the server/client common SEC API/EAPI function traces.
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


#include "inc/msgbuf_strbuilder.h"
#include "inc/TRACE_nhtsec.h"
#include "inc/avlset.h"
#include "inc/os/msgbuf_sys_mutex.h"
#include "inc/msgbuf_sys_malloc.h"


#ifdef _NHT_RPC_TRACE_ON_


static TSecFunctionTable    * pgSecFunctionTable = NULL;
static TSecFunctionTable      gTraceSecFunctionTable;
static TMsgbuf_thread_mutex   pgSecTransportIdSetMutex = NULL;
static TAVLSet                gSecTransportIdSet;

/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/

/* */
static TSecStatus _TRACE_secGetNuid
(
  TSecNuid * pxNuid
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secGetNuid():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNuid", (void*)&pxNuid[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secGetNuid (pxNuid);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secGetNuid():\n");
    if (pxNuid && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxNuid", (void*)&pxNuid[0], sizeof(TSecNuid));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}


/* */
static TSecStatus _TRACE_secGetChipsetRevision
(
  const TChar ** ppxChipsetRevision
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secGetChipsetRevision():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: ppxChipsetRevision", (void*)ppxChipsetRevision);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secGetChipsetRevision (ppxChipsetRevision);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secGetChipsetRevision():\n");
    if (ppxChipsetRevision && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "out: *ppxChipsetRevision", (const char *)*ppxChipsetRevision);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secEncryptData
(
        TUnsignedInt8 * pxOutput,
  const TUnsignedInt8 * pxInput,
        TSize           xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEncryptData():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TSize));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEncryptData (
    pxOutput,
    pxInput,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEncryptData():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secDecryptData
(
        TUnsignedInt8 * pxOutput,
  const TUnsignedInt8 * pxInput,
        TSize           xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secDecryptData():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TSize));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secDecryptData (
    pxOutput,
    pxInput,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secDecryptData():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secGenerateRandomBytes
(
  size_t          xNumOfBytes,
  TUnsignedInt8 * pxRandomBytes
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secGenerateRandomBytes():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xNumOfBytes", (size_t)xNumOfBytes, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxRandomBytes", (void*)pxRandomBytes);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secGenerateRandomBytes (
    xNumOfBytes,
    pxRandomBytes );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secGenerateRandomBytes():\n");

    if (pxRandomBytes && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxRandomBytes", (void*)pxRandomBytes, (size_t)xNumOfBytes);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secRsaGenerateKey
(
  size_t           xKeySize,
  TUnsignedInt32   xE,
  TUnsignedInt8  * pxN,
  TUnsignedInt8  * pxP,
  TUnsignedInt8  * pxQ,
  TUnsignedInt8  * pxDP,
  TUnsignedInt8  * pxDQ,
  TUnsignedInt8  * pxQInv
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secRsaGenerateKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxN", (void*)pxN);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxP", (void*)pxP);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxQ", (void*)pxQ);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDP", (void*)pxDP);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDQ", (void*)pxDQ);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxQInv", (void*)pxQInv);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secRsaGenerateKey (
    xKeySize,
    xE,
    pxN,
    pxP,
    pxQ,
    pxDP,
    pxDQ,
    pxQInv );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secRsaGenerateKey():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      if (pxN)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxN", (void*)pxN, (size_t)xKeySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxP)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxP", (void*)pxN, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxQ)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxQ", (void*)pxQ, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxDP)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxDP", (void*)pxDP, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxDQ)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxDQ", (void*)pxDQ, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxQInv)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxQInv", (void*)pxQInv, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secRsaPublicEncrypt
(
  const TUnsignedInt8  * pxInput,
        size_t           xInputSize,
        TUnsignedInt8  * pxOutput,
        TUnsignedInt32   xE,
  const TUnsignedInt8  * pxN,
        size_t           xKeySize,
        TSecRsaPadding   xPadding
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secRsaPublicEncrypt():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxN", (const void*)pxN, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInputSize", (size_t)xInputSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xInputSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPadding", (size_t)xPadding, sizeof(TSecRsaPadding));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secRsaPublicEncrypt (
    pxInput,
    xInputSize,
    pxOutput,
    xE,
    pxN,
    xKeySize,
    xPadding );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secRsaPublicEncrypt():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xKeySize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secRsaPrivateEncrypt
(
  const TUnsignedInt8  * pxInput,
        size_t           xInputSize,
        TUnsignedInt8  * pxOutput,
        TUnsignedInt32   xE,
  const TUnsignedInt8  * pxN,
  const TUnsignedInt8  * pxP,
  const TUnsignedInt8  * pxQ,
  const TUnsignedInt8  * pxDP,
  const TUnsignedInt8  * pxDQ,
  const TUnsignedInt8  * pxQInv,
        size_t           xKeySize,
        TSecRsaPadding   xPadding
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secRsaPrivateEncrypt():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxN", (const void*)pxN, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxP", (const void*)pxP, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxQ", (const void*)pxQ, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDP", (const void*)pxDP, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDQ", (const void*)pxDQ, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxQInv", (const void*)pxQInv, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInputSize", (size_t)xInputSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xInputSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPadding", (size_t)xPadding, sizeof(TSecRsaPadding));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secRsaPrivateEncrypt (
    pxInput,
    xInputSize,
    pxOutput,
    xE,
    pxN,
    pxP,
    pxQ,
    pxDP,
    pxDQ,
    pxQInv,
    xKeySize,
    xPadding );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secRsaPrivateEncrypt():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xKeySize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secRsaPublicDecrypt
(
  const TUnsignedInt8  * pxInput,
        TUnsignedInt8  * pxOutput,
        size_t         * pxOutputSize,
        TUnsignedInt32   xE,
  const TUnsignedInt8  * pxN,
        size_t           xKeySize,
        TSecRsaPadding   xPadding
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secRsaPublicDecrypt():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxN", (const void*)pxN, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputSize", (void*)pxOutputSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPadding", (size_t)xPadding, sizeof(TSecRsaPadding));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secRsaPublicDecrypt (
    pxInput,
    pxOutput,
    pxOutputSize,
    xE,
    pxN,
    xKeySize,
    xPadding );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secRsaPublicDecrypt():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      size_t _outSize;

      if (pxOutputSize)
      {
        msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxOutputSize", (size_t)*pxOutputSize, sizeof(size_t));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
        _outSize = (size_t)*pxOutputSize;
      }
      else _outSize = (size_t)xKeySize;

      if (pxOutput)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, _outSize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secRsaPrivateDecrypt
(
  const TUnsignedInt8  * pxInput,
        TUnsignedInt8  * pxOutput,
        size_t         * pxOutputSize,
        TUnsignedInt32   xE,
  const TUnsignedInt8  * pxN,
  const TUnsignedInt8  * pxP,
  const TUnsignedInt8  * pxQ,
  const TUnsignedInt8  * pxDP,
  const TUnsignedInt8  * pxDQ,
  const TUnsignedInt8  * pxQInv,
        size_t           xKeySize,
        TSecRsaPadding   xPadding
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secRsaPrivateDecrypt():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxN", (const void*)pxN, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxP", (const void*)pxP, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxQ", (const void*)pxQ, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDP", (const void*)pxDP, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDQ", (const void*)pxDQ, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxQInv", (const void*)pxQInv, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputSize", (void*)pxOutputSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPadding", (size_t)xPadding, sizeof(TSecRsaPadding));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secRsaPrivateDecrypt (
    pxInput,
    pxOutput,
    pxOutputSize,
    xE,
    pxN,
    pxP,
    pxQ,
    pxDP,
    pxDQ,
    pxQInv,
    xKeySize,
    xPadding );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secRsaPrivateDecrypt():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      size_t _outSize;

      if (pxOutputSize)
      {
        msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxOutputSize", (size_t)*pxOutputSize, sizeof(size_t));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
        _outSize = (size_t)*pxOutputSize;
      }
      else _outSize = (size_t)xKeySize;

      if (pxOutput)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, _outSize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secDhGenerateKey
(
  const TUnsignedInt8 * pxG,
  const TUnsignedInt8 * pxP,
  const TUnsignedInt8 * pxInputPrivKey,
        TUnsignedInt8 * pxOutputPrivKey,
        TUnsignedInt8 * pxPubKey,
        size_t          xKeySize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secDhGenerateKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxG", (const void*)pxG, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxP", (const void*)pxP, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputPrivKey", (const void*)pxInputPrivKey, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputPrivKey", (void*)pxOutputPrivKey);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPubKey", (void*)pxPubKey);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secDhGenerateKey (
    pxG,
    pxP,
    pxInputPrivKey,
    pxOutputPrivKey,
    pxPubKey,
    xKeySize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secDhGenerateKey():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      if (pxOutputPrivKey)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputPrivKey", (void*)pxOutputPrivKey, (size_t)xKeySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxPubKey)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxPubKey", (void*)pxPubKey, (size_t)xKeySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secDhComputeKey
(
  const TUnsignedInt8 * pxP,
  const TUnsignedInt8 * pxPrivKey,
  const TUnsignedInt8 * pxOtherPubKey,
        TUnsignedInt8 * pxSharedSecret,
        size_t          xKeySize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secDhComputeKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxP", (const void*)pxP, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPrivKey", (const void*)pxPrivKey, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxOtherPubKey", (const void*)pxOtherPubKey, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSharedSecret", (void*)pxSharedSecret);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secDhComputeKey (
    pxP,
    pxPrivKey,
    pxOtherPubKey,
    pxSharedSecret,
    xKeySize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secDhComputeKey():\n");

    if (pxSharedSecret && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxSharedSecret", (void*)pxSharedSecret, xKeySize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha1Init
(
  TSecHashContext * pxContext
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha1Init():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxContext", (void*)pxContext);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha1Init (pxContext);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha1Init():\n");

    if (pxContext && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxContext", (void*)*pxContext);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha1Update
(
        TSecHashContext   xContext,
  const TUnsignedInt8   * pxMessageChunk,
        size_t            xChunkSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha1Update():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xChunkSize", (size_t)xChunkSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessageChunk", (const void*)pxMessageChunk, (size_t)xChunkSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha1Update (
    xContext,
    pxMessageChunk,
    xChunkSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha1Update():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha1Final
(
  TSecHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha1Final():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMessageDigest", (void*)pxMessageDigest);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha1Final (
    xContext,
    pxMessageDigest );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha1Final():\n");

    if (pxMessageDigest && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxMessageDigest", (void*)pxMessageDigest, 20);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha256Init
(
  TSecHashContext * pxContext
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha256Init():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxContext", (void*)pxContext);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha256Init (pxContext);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha256Init():\n");

    if (pxContext && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxContext", (void*)*pxContext);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha256Update
(
        TSecHashContext   xContext,
  const TUnsignedInt8   * pxMessageChunk,
        size_t            xChunkSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha256Update():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xChunkSize", (size_t)xChunkSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessageChunk", (const void*)pxMessageChunk, (size_t)xChunkSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha256Update (
    xContext,
    pxMessageChunk,
    xChunkSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha256Update():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha256Final
(
  TSecHashContext  xContext,
  TUnsignedInt8  * pxMessageDigest
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha256Final():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMessageDigest", (void*)pxMessageDigest);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha256Final (
    xContext,
    pxMessageDigest );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha256Final():\n");

    if (pxMessageDigest && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxMessageDigest", (void*)pxMessageDigest, 32);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secHmacSha256Init
(
  const TUnsignedInt8   * pxKey,
        size_t            xKeySize,
        TSecHashContext * pxContext
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secHmacSha256Init():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxContext", (void*)pxContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxKey", (const void*)pxKey, (size_t)xKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secHmacSha256Init (
    pxKey,
    xKeySize,
    pxContext );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secHmacSha256Init():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secHmacSha256Update
(
        TSecHashContext   xContext,
  const TUnsignedInt8   * pxMessageChunk,
        size_t            xChunkSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secHmacSha256Update():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xChunkSize", (size_t)xChunkSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessageChunk", (const void*)pxMessageChunk, (size_t)xChunkSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secHmacSha256Update (
    xContext,
    pxMessageChunk,
    xChunkSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secHmacSha256Update():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secHmacSha256Final
(
  TSecHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secHmacSha256Final():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMessageDigest", (void*)pxMessageDigest);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secHmacSha256Final (
    xContext,
    pxMessageDigest );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secHmacSha256Final():\n");

    if (pxMessageDigest && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxMessageDigest", (void*)pxMessageDigest, 32);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static void _TRACE_secEcdsaPrintParams
(
  TSecEcParams     * pxParams,
  TMsgbufStrBuffer * pxStrBuffer
)
{
  msgbuf_strbuilder_setparam_pointer (pxStrBuffer, "in:  pxParams", (void*)pxParams);
  if (pxParams)
  {
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (pxStrBuffer, "in: pxParams->keySize", (size_t)pxParams->keySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->q", (void*)pxParams->q, (size_t)pxParams->keySize);
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->a", (void*)pxParams->a, (size_t)pxParams->keySize);
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->b", (void*)pxParams->b, (size_t)pxParams->keySize);
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->GX", (void*)pxParams->GX, (size_t)pxParams->keySize);
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->GY", (void*)pxParams->GY, (size_t)pxParams->keySize);
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->n", (void*)pxParams->n, (size_t)pxParams->keySize);
    msgbuf_strbuilder_add_string  (pxStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (pxStrBuffer, "in:  pxParams->h", (void*)pxParams->h, (size_t)pxParams->keySize);
  }
}

/* */
static TSecStatus _TRACE_secEcdsaGenerateKey
(
        TSecEcParams    xParams,
  const TUnsignedInt8 * pxInputPrivKey,
        TUnsignedInt8 * pxOutputPrivKey,
        TUnsignedInt8 * pxPubKeyX,
        TUnsignedInt8 * pxPubKeyY
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEcdsaGenerateKey():\n");
    _TRACE_secEcdsaPrintParams (&xParams, &msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputPrivKey", (const void*)pxInputPrivKey, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputPrivKey", (void*)pxOutputPrivKey);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPubKeyX", (void*)pxPubKeyX);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPubKeyY", (void*)pxPubKeyY);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEcdsaGenerateKey (
    xParams,
    pxInputPrivKey,
    pxOutputPrivKey,
    pxPubKeyX,
    pxPubKeyY );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEcdsaGenerateKey():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      if (pxOutputPrivKey)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputPrivKey", (void*)pxOutputPrivKey, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxPubKeyX)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxPubKeyX", (void*)pxPubKeyX, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxPubKeyY)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxPubKeyY", (void*)pxPubKeyY, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secEcdsaSign
(
        TSecEcParams    xParams,
        TSecHashType    xHashType,
  const TUnsignedInt8 * pxPrivKey,
  const TUnsignedInt8 * pxMessage,
        size_t          xMessageSize,
        TUnsignedInt8 * pxSigR,
        TUnsignedInt8 * pxSigS
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEcdsaSign():\n");
    _TRACE_secEcdsaPrintParams (&xParams, &msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xHashType", (size_t)xHashType, sizeof(TSecHashType));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPrivKey", (const void*)pxPrivKey, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessage", (const void*)pxMessage, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSigR", (void*)pxSigR);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSigS", (void*)pxSigS);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEcdsaSign (
    xParams,
    xHashType,
    pxPrivKey,
    pxMessage,
    xMessageSize,
    pxSigR,
    pxSigS );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEcdsaSign():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      if (pxSigR)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxSigR", (void*)pxSigR, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxSigS)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxSigS", (void*)pxSigS, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secEcdsaVerify
(
        TSecEcParams    xParams,
        TSecHashType    xHashType,
  const TUnsignedInt8 * pxPubKeyX,
  const TUnsignedInt8 * pxPubKeyY,
  const TUnsignedInt8 * pxMessage,
        size_t          xMessageSize,
  const TUnsignedInt8 * pxSigR,
  const TUnsignedInt8 * pxSigS
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEcdsaVerify():\n");
    _TRACE_secEcdsaPrintParams (&xParams, &msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xHashType", (size_t)xHashType, sizeof(TSecHashType));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPubKeyX", (const void*)pxPubKeyX, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPubKeyY", (const void*)pxPubKeyY, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessage", (const void*)pxMessage, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxSigR", (const void*)pxSigR, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxSigS", (const void*)pxSigS, (size_t)xParams.keySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEcdsaVerify (
    xParams,
    xHashType,
    pxPubKeyX,
    pxPubKeyY,
    pxMessage,
    xMessageSize,
    pxSigR,
    pxSigS );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEcdsaVerify():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secEcdhGenerateKey
(
        TSecEcParams    xParams,
  const TUnsignedInt8 * pxInputPrivKey,
        TUnsignedInt8 * pxOutputPrivKey,
        TUnsignedInt8 * pxPubKeyX,
        TUnsignedInt8 * pxPubKeyY
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEcdhGenerateKey():\n");
    _TRACE_secEcdsaPrintParams (&xParams, &msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputPrivKey", (const void*)pxInputPrivKey, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputPrivKey", (void*)pxOutputPrivKey);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPubKeyX", (void*)pxPubKeyX);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPubKeyY", (void*)pxPubKeyY);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEcdhGenerateKey (
    xParams,
    pxInputPrivKey,
    pxOutputPrivKey,
    pxPubKeyX,
    pxPubKeyY );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEcdhGenerateKey():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      if (pxOutputPrivKey)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputPrivKey", (void*)pxOutputPrivKey, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxPubKeyX)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxPubKeyX", (void*)pxPubKeyX, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxPubKeyY)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxPubKeyY", (void*)pxPubKeyY, (size_t)xParams.keySize);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secEcdhComputeKey
(
        TSecEcParams    xParams,
  const TUnsignedInt8 * pxPrivKey,
  const TUnsignedInt8 * pxOtherPubKeyX,
  const TUnsignedInt8 * pxOtherPubKeyY,
        TUnsignedInt8 * pxSharedSecret
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEcdhComputeKey():\n");
    _TRACE_secEcdsaPrintParams (&xParams, &msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPrivKey", (const void*)pxPrivKey, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxOtherPubKeyX", (const void*)pxOtherPubKeyX, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxOtherPubKeyY", (const void*)pxOtherPubKeyY, (size_t)xParams.keySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSharedSecret", (void*)pxSharedSecret);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEcdhComputeKey (
    xParams,
    pxPrivKey,
    pxOtherPubKeyX,
    pxOtherPubKeyY,
    pxSharedSecret );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEcdhComputeKey():\n");

    if (pxSharedSecret && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxSharedSecret", (void*)pxSharedSecret, (size_t)xParams.keySize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secOpenRam2RamEncryptSession
(
  TSecCipherSession * pxSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secOpenRam2RamEncryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSession", (void*)pxSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secOpenRam2RamEncryptSession (pxSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secOpenRam2RamEncryptSession():\n");

    if (pxSession && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secOpenRam2RamDecryptSession
(
  TSecCipherSession * pxSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secOpenRam2RamDecryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSession", (void*)pxSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secOpenRam2RamDecryptSession (pxSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secOpenRam2RamDecryptSession():\n");

    if (pxSession && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secCloseSession
(
  TSecCipherSession xSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secCloseSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secCloseSession (xSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secCloseSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSetClearTextKey
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8     * pxKeyId,
        size_t              xClearTextKeySize,
  const TUnsignedInt8     * pxClearTextKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSetClearTextKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyIdSize", (size_t)xKeyIdSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxKeyId", (void*)pxKeyId, (size_t)xKeyIdSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextKeySize", (size_t)xClearTextKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxClearTextKey", (const void*)pxClearTextKey, (size_t)xClearTextKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSetClearTextKey (
    xSession,
    xEmi,
    xKeyIdSize,
    pxKeyId,
    xClearTextKeySize,
    pxClearTextKey );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSetClearTextKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSet2LevelProtectedKey
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8     * pxKeyId,
        size_t              xCipheredContentKeySize,
  const TUnsignedInt8     * pxCipheredContentKey,
        size_t              xCipheredProtectingKeySize,
  const TUnsignedInt8     * pxL1CipheredProtectingKey,
  const TUnsignedInt8     * pxL2CipheredProtectingKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSet2LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyIdSize", (size_t)xKeyIdSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxKeyId", (void*)pxKeyId, (size_t)xKeyIdSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxCipheredContentKey", (const void*)pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeySize", (size_t)xCipheredProtectingKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxL1CipheredProtectingKey", (const void*)pxL1CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxL2CipheredProtectingKey", (const void*)pxL2CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSet2LevelProtectedKey (
    xSession,
    xEmi,
    xKeyIdSize,
    pxKeyId,
    xCipheredContentKeySize,
    pxCipheredContentKey,
    xCipheredProtectingKeySize,
    pxL1CipheredProtectingKey,
    pxL2CipheredProtectingKey );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSet2LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secUseCertKey
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8     * pxKeyId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secUseCertKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyIdSize", (size_t)xKeyIdSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxKeyId", (void*)pxKeyId, (size_t)xKeyIdSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secUseCertKey (
    xSession,
    xEmi,
    xKeyIdSize,
    pxKeyId );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secUseCertKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSessionEncrypt
(
        TSecCipherSession   xSession,
  const TUnsignedInt8     * pxInput,
        TUnsignedInt8     * pxOutput,
        size_t              xMessageSize,
  const TUnsignedInt8     * pxInitVector,
        size_t              xInitVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSessionEncrypt():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitVectorSize", (size_t)xInitVectorSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitVector", (const void*)pxInitVector, (size_t)xInitVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSessionEncrypt (
    xSession,
    pxInput,
    pxOutput,
    xMessageSize,
    pxInitVector,
    xInitVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSessionEncrypt():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, xMessageSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSessionDecrypt
(
        TSecCipherSession   xSession,
  const TUnsignedInt8     * pxInput,
        TUnsignedInt8     * pxOutput,
        size_t              xMessageSize,
  const TUnsignedInt8     * pxInitVector,
        size_t              xInitVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSessionDecrypt():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitVectorSize", (size_t)xInitVectorSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitVector", (const void*)pxInitVector, (size_t)xInitVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSessionDecrypt (
    xSession,
    pxInput,
    pxOutput,
    xMessageSize,
    pxInitVector,
    xInitVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSessionDecrypt():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xMessageSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secGetNuid64
(
  TSecNuid64 * pxNuid
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secGetNuid64():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNuid", (void*)pxNuid);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secGetNuid64 (pxNuid);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secGetNuid64():\n");

    if (pxNuid && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: *pxNuid", (void*)&(*pxNuid)[0], 8);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}


/* */
static TSecStatus _TRACE_secGetChipsetExtension
(
  const TChar ** ppxChipsetExtension
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secGetChipsetExtension():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: ppxChipsetExtension", (void*)ppxChipsetExtension);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secGetChipsetExtension (ppxChipsetExtension);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secGetChipsetExtension():\n");

    if (ppxChipsetExtension && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "out: *ppxChipsetExtension", (const char*)*ppxChipsetExtension);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha384Init
(
  TSecHashContext * pxContext
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha384Init():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxContext", (void*)pxContext);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha384Init (pxContext);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha384Init():\n");

    if (pxContext && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxContext", (void*)*pxContext);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha384Update
(
        TSecHashContext   xContext,
  const TUnsignedInt8   * pxMessageChunk,
        size_t            xChunkSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha384Update():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xChunkSize", (size_t)xChunkSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessageChunk", (const void*)pxMessageChunk, (size_t)xChunkSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha384Update (
    xContext,
    pxMessageChunk,
    xChunkSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha384Update():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSha384Final
(
  TSecHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSha384Final():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMessageDigest", (void*)pxMessageDigest);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSha384Final (
    xContext,
    pxMessageDigest );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSha384Final():\n");

    if (pxMessageDigest && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxMessageDigest", (void*)pxMessageDigest, 48);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secRsaComputeCrtParams
(
        size_t           xKeySize,
        TUnsignedInt32   xE,
  const TUnsignedInt8  * pxP,
  const TUnsignedInt8  * pxQ,
        TUnsignedInt8  * pxDP,
        TUnsignedInt8  * pxDQ,
        TUnsignedInt8  * pxQInv
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secRsaComputeCrtParams():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxP", (const void*)pxP, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxQ", (const void*)pxQ, (size_t)(xKeySize/2));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDP", (void*)pxDP);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDQ", (void*)pxDQ);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxQInv", (void*)pxQInv);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secRsaComputeCrtParams (
    xKeySize,
    xE,
    pxP,
    pxQ,
    pxDP,
    pxDQ,
    pxQInv );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secRsaComputeCrtParams():\n");

    if (secStatus == SEC_NO_ERROR)
    {
      if (pxDP)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxDP", (void*)pxDP, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxDQ)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxDQ", (void*)pxDQ, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }

      if (pxQInv)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxQInv", (void*)pxQInv, (size_t)(xKeySize/2));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secEncryptFlashProtKey
(
  const TUnsignedInt8 * pxInput,
        TUnsignedInt8 * pxOutput,
        size_t          xSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secEncryptFlashProtKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xSize", (size_t)xSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secEncryptFlashProtKey (
    pxInput,
    pxOutput,
    xSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secEncryptFlashProtKey():\n");

    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secUseFlashProtKey
(
  TSecCipherSession xSession,
  TUnsignedInt16    xEmi
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secUseFlashProtKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secUseFlashProtKey (
    xSession,
    xEmi );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secUseFlashProtKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secOpenStreamEncryptSession
(
  TSecCipherSession   * pxSession,
  TTransportSessionId   xTransportSessionId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secOpenStreamEncryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSession", (void*)pxSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secOpenStreamEncryptSession (
    pxSession,
    xTransportSessionId );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secOpenStreamEncryptSession():\n");

    if (pxSession && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secOpenStreamDecryptSession
(
  TSecCipherSession   * pxSession,
  TTransportSessionId   xTransportSessionId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secOpenStreamDecryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSession", (void*)pxSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secOpenStreamDecryptSession (
    pxSession,
    xTransportSessionId );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secOpenStreamDecryptSession():\n");

    if (pxSession && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSet0LevelProtectedKey
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8     * pxKeyId,
        size_t              xCipheredContentKeySize,
  const TUnsignedInt8     * pxCipheredContentKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSet0LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyIdSize", (size_t)xKeyIdSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxKeyId", (void*)pxKeyId, (size_t)xKeyIdSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxCipheredContentKey", (const void*)pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSet0LevelProtectedKey (
    xSession,
    xEmi,
    xKeyIdSize,
    pxKeyId,
    xCipheredContentKeySize,
    pxCipheredContentKey );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSet0LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secSet1LevelProtectedKey
(
        TSecCipherSession   xSession,
        TUnsignedInt16      xEmi,
        size_t              xKeyIdSize,
        TUnsignedInt8     * pxKeyId,
        size_t              xCipheredContentKeySize,
  const TUnsignedInt8     * pxCipheredContentKey,
        size_t              xCipheredProtectingKeySize,
  const TUnsignedInt8     * pxL1CipheredProtectingKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSet1LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyIdSize", (size_t)xKeyIdSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxKeyId", (void*)pxKeyId, (size_t)xKeyIdSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxCipheredContentKey", (const void*)pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeySize", (size_t)xCipheredProtectingKeySize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxL1CipheredProtectingKey", (const void*)pxL1CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSet1LevelProtectedKey (
    xSession,
    xEmi,
    xKeyIdSize,
    pxKeyId,
    xCipheredContentKeySize,
    pxCipheredContentKey,
    xCipheredProtectingKeySize,
    pxL1CipheredProtectingKey );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSet1LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}


/* */
static TSecStatus _TRACE_secSetMetadata
(
        TSecCipherSession   xSession,
        size_t              xMetadataSize,
  const TUnsignedInt8     * pxMetadata
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secSetMetadata():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMetadataSize", (size_t)xMetadataSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer(&msgStrBuffer, "in: pxMetadata", (const void*)pxMetadata, (size_t)xMetadataSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secSetMetadata (
    xSession,
    xMetadataSize,
    pxMetadata );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secSetMetadata():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TUnsignedInt8* _TRACE_secAllocateBuffer
(
  size_t xBufferSize
)
{
  TMsgbufStrBuffer   msgStrBuffer;
  int                callId;
  TUnsignedInt8    * pBuffer = NULL;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secAllocateBuffer():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xBufferSize", (size_t)xBufferSize, sizeof(size_t));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  pBuffer = pgSecFunctionTable->secAllocateBuffer (xBufferSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secAllocateBuffer():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "ret: pBuffer", (void*)pBuffer);
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return pBuffer;
}

/* */
static TSecStatus _TRACE_secFreeBuffer
(
  TUnsignedInt8 * pxBuffer
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secFreeBuffer():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBuffer", (void*)pxBuffer);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secFreeBuffer (pxBuffer);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secFreeBuffer():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
static TSecStatus _TRACE_secUseLegacyKey
(
  TSecCipherSession xSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@pSecGetFunctionTable->secUseLegacyKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = pgSecFunctionTable->secUseLegacyKey (xSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pSecGetFunctionTable->secUseLegacyKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(secGetNuid)
(
  TSecNuid * pxNuid
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@secGetNuid():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNuid", (void*)&pxNuid[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = secGetNuid (pxNuid);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@secGetNuid():\n");
    if (pxNuid && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxNuid", (void*)&pxNuid[0], sizeof(TSecNuid));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(secGetChipsetRevision)
(
  const TChar ** ppxChipsetRevision
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@secGetChipsetRevision():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: ppxChipsetRevision", (void*)ppxChipsetRevision);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = secGetChipsetRevision (ppxChipsetRevision);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@secGetChipsetRevision():\n");
    if (ppxChipsetRevision && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "out: *ppxChipsetRevision", (const char *)*ppxChipsetRevision);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(secEncryptData)
(
        TUnsignedInt8 * pxOutput,
  const TUnsignedInt8 * pxInput,
        TSize           xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@secEncryptData():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = secEncryptData (
    pxOutput,
    pxInput,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@secEncryptData():\n");
    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(secDecryptData)
(
        TUnsignedInt8 * pxOutput,
  const TUnsignedInt8 * pxInput,
        TSize           xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@secDecryptData():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (const void*)pxInput, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = secDecryptData (
    pxOutput,
    pxInput,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@secDecryptData():\n");
    if (pxOutput && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecFunctionTable * _CRPC(secGetFunctionTable) (void)
{
  TMsgbufStrBuffer    msgStrBuffer;
  int                 callId;
  TSecFunctionTable * pSecFunctionTable = pgSecFunctionTable;

  if (pSecFunctionTable) return &gTraceSecFunctionTable;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@secGetFunctionTable()\n");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (pgSecFunctionTable == NULL) pgSecFunctionTable = secGetFunctionTable();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@secGetFunctionTable():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "ret: pSecFunctionTable", (void*)pgSecFunctionTable);

    if (pgSecFunctionTable)
    {
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: pSecFunctionTable->secApiVersion", (size_t)pgSecFunctionTable->secApiVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secGetNuid", (void*)(size_t)pgSecFunctionTable->secGetNuid);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secGetChipsetRevision", (void*)(size_t)pgSecFunctionTable->secGetChipsetRevision);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEncryptData", (void*)(size_t)pgSecFunctionTable->secEncryptData);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secDecryptData", (void*)(size_t)pgSecFunctionTable->secDecryptData);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secGenerateRandomBytes", (void*)(size_t)pgSecFunctionTable->secGenerateRandomBytes);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secRsaGenerateKey", (void*)(size_t)pgSecFunctionTable->secRsaGenerateKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secRsaPublicEncrypt", (void*)(size_t)pgSecFunctionTable->secRsaPublicEncrypt);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secRsaPrivateEncrypt", (void*)(size_t)pgSecFunctionTable->secRsaPrivateEncrypt);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secRsaPublicDecrypt", (void*)(size_t)pgSecFunctionTable->secRsaPublicDecrypt);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secRsaPrivateDecrypt", (void*)(size_t)pgSecFunctionTable->secRsaPrivateDecrypt);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secDhGenerateKey", (void*)(size_t)pgSecFunctionTable->secDhGenerateKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secDhComputeKey", (void*)(size_t)pgSecFunctionTable->secDhComputeKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha1Init", (void*)(size_t)pgSecFunctionTable->secSha1Init);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha1Update", (void*)(size_t)pgSecFunctionTable->secSha1Update);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha1Final", (void*)(size_t)pgSecFunctionTable->secSha1Final);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha256Init", (void*)(size_t)pgSecFunctionTable->secSha256Init);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha256Update", (void*)(size_t)pgSecFunctionTable->secSha256Update);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha256Final", (void*)(size_t)pgSecFunctionTable->secSha256Final);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secHmacSha256Init", (void*)(size_t)pgSecFunctionTable->secHmacSha256Init);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secHmacSha256Update", (void*)(size_t)pgSecFunctionTable->secHmacSha256Update);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secHmacSha256Final", (void*)(size_t)pgSecFunctionTable->secHmacSha256Final);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEcdsaGenerateKey", (void*)(size_t)pgSecFunctionTable->secEcdsaGenerateKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEcdsaSign", (void*)(size_t)pgSecFunctionTable->secEcdsaSign);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEcdsaVerify", (void*)(size_t)pgSecFunctionTable->secEcdsaVerify);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEcdhGenerateKey", (void*)(size_t)pgSecFunctionTable->secEcdhGenerateKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEcdhComputeKey", (void*)(size_t)pgSecFunctionTable->secEcdhComputeKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secOpenRam2RamEncryptSession", (void*)(size_t)pgSecFunctionTable->secOpenRam2RamEncryptSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secOpenRam2RamDecryptSession", (void*)(size_t)pgSecFunctionTable->secOpenRam2RamDecryptSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secCloseSession", (void*)(size_t)pgSecFunctionTable->secCloseSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSetClearTextKey", (void*)(size_t)pgSecFunctionTable->secSetClearTextKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSet2LevelProtectedKey", (void*)(size_t)pgSecFunctionTable->secSet2LevelProtectedKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secUseCertKey", (void*)(size_t)pgSecFunctionTable->secUseCertKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSessionEncrypt", (void*)(size_t)pgSecFunctionTable->secSessionEncrypt);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSessionDecrypt", (void*)(size_t)pgSecFunctionTable->secSessionDecrypt);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secGetNuid64", (void*)(size_t)pgSecFunctionTable->secGetNuid64);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secGetChipsetExtension", (void*)(size_t)pgSecFunctionTable->secGetChipsetExtension);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha384Init", (void*)(size_t)pgSecFunctionTable->secSha384Init);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha384Update", (void*)(size_t)pgSecFunctionTable->secSha384Update);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSha384Final", (void*)(size_t)pgSecFunctionTable->secSha384Final);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secRsaComputeCrtParams", (void*)(size_t)pgSecFunctionTable->secRsaComputeCrtParams);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secEncryptFlashProtKey", (void*)(size_t)pgSecFunctionTable->secEncryptFlashProtKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secUseFlashProtKey", (void*)(size_t)pgSecFunctionTable->secUseFlashProtKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secOpenStreamEncryptSession", (void*)(size_t)pgSecFunctionTable->secOpenStreamEncryptSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secOpenStreamDecryptSession", (void*)(size_t)pgSecFunctionTable->secOpenStreamDecryptSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSet0LevelProtectedKey", (void*)(size_t)pgSecFunctionTable->secSet0LevelProtectedKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSet1LevelProtectedKey", (void*)(size_t)pgSecFunctionTable->secSet1LevelProtectedKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secSetMetadata", (void*)(size_t)pgSecFunctionTable->secSetMetadata);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secAllocateBuffer", (void*)(size_t)pgSecFunctionTable->secAllocateBuffer);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secFreeBuffer", (void*)(size_t)pgSecFunctionTable->secFreeBuffer);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pSecFunctionTable->secUseLegacyKey", (void*)(size_t)pgSecFunctionTable->secUseLegacyKey);
    }
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (pgSecFunctionTable && (pSecFunctionTable == NULL))
  {
    gTraceSecFunctionTable.secApiVersion = pgSecFunctionTable->secApiVersion;

    if (pgSecFunctionTable->secGetNuid) gTraceSecFunctionTable.secGetNuid = &_TRACE_secGetNuid;
    else gTraceSecFunctionTable.secGetNuid = NULL;

    if (pgSecFunctionTable->secGetChipsetRevision) gTraceSecFunctionTable.secGetChipsetRevision = &_TRACE_secGetChipsetRevision;
    else gTraceSecFunctionTable.secGetChipsetRevision = NULL;

    if (pgSecFunctionTable->secEncryptData) gTraceSecFunctionTable.secEncryptData = &_TRACE_secEncryptData;
    else gTraceSecFunctionTable.secEncryptData = NULL;

    if (pgSecFunctionTable->secDecryptData) gTraceSecFunctionTable.secDecryptData = &_TRACE_secDecryptData;
    else gTraceSecFunctionTable.secDecryptData = NULL;

    if (pgSecFunctionTable->secGenerateRandomBytes) gTraceSecFunctionTable.secGenerateRandomBytes = &_TRACE_secGenerateRandomBytes;
    else gTraceSecFunctionTable.secGenerateRandomBytes = NULL;

    if (pgSecFunctionTable->secRsaGenerateKey) gTraceSecFunctionTable.secRsaGenerateKey = &_TRACE_secRsaGenerateKey;
    else gTraceSecFunctionTable.secRsaGenerateKey = NULL;

    if (pgSecFunctionTable->secRsaPublicEncrypt) gTraceSecFunctionTable.secRsaPublicEncrypt = &_TRACE_secRsaPublicEncrypt;
    else gTraceSecFunctionTable.secRsaPublicEncrypt = NULL;

    if (pgSecFunctionTable->secRsaPrivateEncrypt) gTraceSecFunctionTable.secRsaPrivateEncrypt = &_TRACE_secRsaPrivateEncrypt;
    else gTraceSecFunctionTable.secRsaPrivateEncrypt = NULL;

    if (pgSecFunctionTable->secRsaPublicDecrypt) gTraceSecFunctionTable.secRsaPublicDecrypt = &_TRACE_secRsaPublicDecrypt;
    else gTraceSecFunctionTable.secRsaPublicDecrypt = NULL;

    if (pgSecFunctionTable->secRsaPrivateDecrypt) gTraceSecFunctionTable.secRsaPrivateDecrypt = &_TRACE_secRsaPrivateDecrypt;
    else gTraceSecFunctionTable.secRsaPrivateDecrypt = NULL;

    if (pgSecFunctionTable->secDhGenerateKey) gTraceSecFunctionTable.secDhGenerateKey = &_TRACE_secDhGenerateKey;
    else gTraceSecFunctionTable.secDhGenerateKey = NULL;

    if (pgSecFunctionTable->secDhComputeKey) gTraceSecFunctionTable.secDhComputeKey = &_TRACE_secDhComputeKey;
    else gTraceSecFunctionTable.secDhComputeKey = NULL;

    if (pgSecFunctionTable->secSha1Init) gTraceSecFunctionTable.secSha1Init = &_TRACE_secSha1Init;
    else gTraceSecFunctionTable.secSha1Init = NULL;

    if (pgSecFunctionTable->secSha1Update) gTraceSecFunctionTable.secSha1Update = &_TRACE_secSha1Update;
    else gTraceSecFunctionTable.secSha1Update = NULL;

    if (pgSecFunctionTable->secSha1Final) gTraceSecFunctionTable.secSha1Final = &_TRACE_secSha1Final;
    else gTraceSecFunctionTable.secSha1Final = NULL;

    if (pgSecFunctionTable->secSha256Init) gTraceSecFunctionTable.secSha256Init = &_TRACE_secSha256Init;
    else gTraceSecFunctionTable.secSha256Init = NULL;

    if (pgSecFunctionTable->secSha256Update) gTraceSecFunctionTable.secSha256Update = &_TRACE_secSha256Update;
    else gTraceSecFunctionTable.secSha256Update = NULL;

    if (pgSecFunctionTable->secSha256Final) gTraceSecFunctionTable.secSha256Final = &_TRACE_secSha256Final;
    else gTraceSecFunctionTable.secSha256Final = NULL;

    if (pgSecFunctionTable->secHmacSha256Init) gTraceSecFunctionTable.secHmacSha256Init = &_TRACE_secHmacSha256Init;
    else gTraceSecFunctionTable.secHmacSha256Init = NULL;

    if (pgSecFunctionTable->secHmacSha256Update) gTraceSecFunctionTable.secHmacSha256Update = &_TRACE_secHmacSha256Update;
    else gTraceSecFunctionTable.secHmacSha256Update = NULL;

    if (pgSecFunctionTable->secHmacSha256Final) gTraceSecFunctionTable.secHmacSha256Final = &_TRACE_secHmacSha256Final;
    else gTraceSecFunctionTable.secHmacSha256Final = NULL;

    if (pgSecFunctionTable->secEcdsaGenerateKey) gTraceSecFunctionTable.secEcdsaGenerateKey = &_TRACE_secEcdsaGenerateKey;
    else gTraceSecFunctionTable.secEcdsaGenerateKey = NULL;

    if (pgSecFunctionTable->secEcdsaSign) gTraceSecFunctionTable.secEcdsaSign = &_TRACE_secEcdsaSign;
    else gTraceSecFunctionTable.secEcdsaSign = NULL;

    if (pgSecFunctionTable->secEcdsaVerify) gTraceSecFunctionTable.secEcdsaVerify = &_TRACE_secEcdsaVerify;
    else gTraceSecFunctionTable.secEcdsaVerify = NULL;

    if (pgSecFunctionTable->secEcdhGenerateKey) gTraceSecFunctionTable.secEcdhGenerateKey = &_TRACE_secEcdhGenerateKey;
    else gTraceSecFunctionTable.secEcdhGenerateKey = NULL;

    if (pgSecFunctionTable->secEcdhComputeKey) gTraceSecFunctionTable.secEcdhComputeKey = &_TRACE_secEcdhComputeKey;
    else gTraceSecFunctionTable.secEcdhComputeKey = NULL;

    if (pgSecFunctionTable->secOpenRam2RamEncryptSession) gTraceSecFunctionTable.secOpenRam2RamEncryptSession = &_TRACE_secOpenRam2RamEncryptSession;
    else gTraceSecFunctionTable.secOpenRam2RamEncryptSession = NULL;

    if (pgSecFunctionTable->secOpenRam2RamDecryptSession) gTraceSecFunctionTable.secOpenRam2RamDecryptSession = &_TRACE_secOpenRam2RamDecryptSession;
    else gTraceSecFunctionTable.secOpenRam2RamDecryptSession = NULL;

    if (pgSecFunctionTable->secCloseSession) gTraceSecFunctionTable.secCloseSession = &_TRACE_secCloseSession;
    else gTraceSecFunctionTable.secCloseSession = NULL;

    if (pgSecFunctionTable->secSetClearTextKey) gTraceSecFunctionTable.secSetClearTextKey = &_TRACE_secSetClearTextKey;
    else gTraceSecFunctionTable.secSetClearTextKey = NULL;

    if (pgSecFunctionTable->secSet2LevelProtectedKey) gTraceSecFunctionTable.secSet2LevelProtectedKey = &_TRACE_secSet2LevelProtectedKey;
    else gTraceSecFunctionTable.secSet2LevelProtectedKey = NULL;

    if (pgSecFunctionTable->secUseCertKey) gTraceSecFunctionTable.secUseCertKey = &_TRACE_secUseCertKey;
    else gTraceSecFunctionTable.secUseCertKey = NULL;

    if (pgSecFunctionTable->secSessionEncrypt) gTraceSecFunctionTable.secSessionEncrypt = &_TRACE_secSessionEncrypt;
    else gTraceSecFunctionTable.secSessionEncrypt = NULL;

    if (pgSecFunctionTable->secSessionDecrypt) gTraceSecFunctionTable.secSessionDecrypt = &_TRACE_secSessionDecrypt;
    else gTraceSecFunctionTable.secSessionDecrypt = NULL;

    if (pgSecFunctionTable->secGetNuid64) gTraceSecFunctionTable.secGetNuid64 = &_TRACE_secGetNuid64;
    else gTraceSecFunctionTable.secGetNuid64 = NULL;

    if (pgSecFunctionTable->secGetChipsetExtension) gTraceSecFunctionTable.secGetChipsetExtension = &_TRACE_secGetChipsetExtension;
    else gTraceSecFunctionTable.secGetChipsetExtension = NULL;

    if (pgSecFunctionTable->secSha384Init) gTraceSecFunctionTable.secSha384Init = &_TRACE_secSha384Init;
    else gTraceSecFunctionTable.secSha384Init = NULL;

    if (pgSecFunctionTable->secSha384Update) gTraceSecFunctionTable.secSha384Update = &_TRACE_secSha384Update;
    else gTraceSecFunctionTable.secSha384Update = NULL;

    if (pgSecFunctionTable->secSha384Final) gTraceSecFunctionTable.secSha384Final = &_TRACE_secSha384Final;
    else gTraceSecFunctionTable.secSha384Final = NULL;

    if (pgSecFunctionTable->secRsaComputeCrtParams) gTraceSecFunctionTable.secRsaComputeCrtParams = &_TRACE_secRsaComputeCrtParams;
    else gTraceSecFunctionTable.secRsaComputeCrtParams = NULL;

    if (pgSecFunctionTable->secEncryptFlashProtKey) gTraceSecFunctionTable.secEncryptFlashProtKey = &_TRACE_secEncryptFlashProtKey;
    else gTraceSecFunctionTable.secEncryptFlashProtKey = NULL;

    if (pgSecFunctionTable->secUseFlashProtKey) gTraceSecFunctionTable.secUseFlashProtKey = &_TRACE_secUseFlashProtKey;
    else gTraceSecFunctionTable.secUseFlashProtKey = NULL;

    if (pgSecFunctionTable->secOpenStreamEncryptSession) gTraceSecFunctionTable.secOpenStreamEncryptSession = &_TRACE_secOpenStreamEncryptSession;
    else gTraceSecFunctionTable.secOpenStreamEncryptSession = NULL;

    if (pgSecFunctionTable->secOpenStreamDecryptSession) gTraceSecFunctionTable.secOpenStreamDecryptSession = &_TRACE_secOpenStreamDecryptSession;
    else gTraceSecFunctionTable.secOpenStreamDecryptSession = NULL;

    if (pgSecFunctionTable->secSet0LevelProtectedKey) gTraceSecFunctionTable.secSet0LevelProtectedKey = &_TRACE_secSet0LevelProtectedKey;
    else gTraceSecFunctionTable.secSet0LevelProtectedKey = NULL;

    if (pgSecFunctionTable->secSet1LevelProtectedKey) gTraceSecFunctionTable.secSet1LevelProtectedKey = &_TRACE_secSet1LevelProtectedKey;
    else gTraceSecFunctionTable.secSet1LevelProtectedKey = NULL;

    if (pgSecFunctionTable->secSetMetadata) gTraceSecFunctionTable.secSetMetadata = &_TRACE_secSetMetadata;
    else gTraceSecFunctionTable.secSetMetadata = NULL;

    if (pgSecFunctionTable->secAllocateBuffer) gTraceSecFunctionTable.secAllocateBuffer = &_TRACE_secAllocateBuffer;
    else gTraceSecFunctionTable.secAllocateBuffer = NULL;

    if (pgSecFunctionTable->secFreeBuffer) gTraceSecFunctionTable.secFreeBuffer = &_TRACE_secFreeBuffer;
    else gTraceSecFunctionTable.secFreeBuffer = NULL;

    if (pgSecFunctionTable->secUseLegacyKey) gTraceSecFunctionTable.secUseLegacyKey = &_TRACE_secUseLegacyKey;
    else gTraceSecFunctionTable.secUseLegacyKey = NULL;
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  if (pgSecFunctionTable) return &gTraceSecFunctionTable;
  else return NULL;
}


/* */
typedef struct SSecTraceEcmCallBackData
{
  TNhtsecEcmContentCallBack        ecmCallBackFct;
  TNhtsecCallBackPrivateParameters ecmCallBackPrivateData;

} TSecTraceEcmCallBackData;

/* */
typedef struct SRpcSecTransportHandle
{
  TAVLSet_iter               iter;
  TTransportSessionId        transportSessionId;
  TSecTraceEcmCallBackData * pEcmHandle;
} TRpcSecTransportHandle;


/* */
static int  _secTransportSessionId_compare
(
  TAVLSet_iter * pxIter1,
  TAVLSet_iter * pxIter2
)
{
  TRpcSecTransportHandle * pIter1 = (TRpcSecTransportHandle*)pxIter1;
  TRpcSecTransportHandle * pIter2 = (TRpcSecTransportHandle*)pxIter2;

  return (pIter1->transportSessionId - pIter2->transportSessionId);
}


/* */
TSecStatus _CRPC(nhtSecInitialize) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  if (pgSecTransportIdSetMutex == NULL)
  {
    AVLSet_init ( &gSecTransportIdSet, &_secTransportSessionId_compare, 0);
    pgSecTransportIdSetMutex = MSGBUF_SYS_createThreadMutex();
  }

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@nhtSecInitialize()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecInitialize ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecInitialize():");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(nhtSecTerminate) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@nhtSecTerminate()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecTerminate ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecTerminate():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(nhtSecGetSoftwareVersion)
(
  TUnsignedInt32 * pxSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@nhtSecGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSoftwareVersion", (void*)pxSoftwareVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecGetSoftwareVersion (pxSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecGetSoftwareVersion():\n");
    if (pxSoftwareVersion && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxSoftwareVersion", (size_t)*pxSoftwareVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(secGetSoftwareVersion)
(
  TUnsignedInt32 * pxSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@secGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSoftwareVersion", (void*)pxSoftwareVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = secGetSoftwareVersion (pxSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@secGetSoftwareVersion():\n");
    if (pxSoftwareVersion && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxSoftwareVersion", (size_t)*pxSoftwareVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/***************************************************************************/
/*                                                                         */
/*                        Transport session                                */
/*                                                                         */
/***************************************************************************/



/* RPC method: rpc_nhtcsd_tn_ecmCallBack
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
static TSecStatus _CRPC(secRpcEcmCallBackFunction)
(
  TTransportSessionId                xTransportSessionId,
  TNhtsecCallBackPrivateParameters   xPrivateParameters,
  TUnsignedInt8                      xEcmTableId,
  const TUnsignedInt8              * pxEcmContent,
  TSize                              xEcmContentSize
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TSecTraceEcmCallBackData * pRpcDscHandle;
  TSecStatus                 secStatus = SEC_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecEcmCallback():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xPrivateParameters", (void*)xPrivateParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEcmTableId", (size_t)xEcmTableId, sizeof(TUnsignedInt8));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEcmContentSize", (size_t)xEcmContentSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxEcmContent", (const void*)pxEcmContent, (size_t)xEcmContentSize);
    RPC_FTRACE_ENTER_SERVER_CALL (callId, msgStrBuffer.pBuffer);
  }

  pRpcDscHandle = (TSecTraceEcmCallBackData*)xPrivateParameters;

  if (pRpcDscHandle)
  {
    if (pRpcDscHandle->ecmCallBackFct)
    {
      secStatus = pRpcDscHandle->ecmCallBackFct (
        xTransportSessionId,
        pRpcDscHandle->ecmCallBackPrivateData,
        xEcmTableId,
        pxEcmContent,
        xEcmContentSize );
    }
  }

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecEcmCallback():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_SERVER_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return secStatus;
}

/* */
TSecStatus _CRPC(nhtSecOpenDscTransportSession)
(
  char                          * pxInputFileName,
  const TNhtSecDemuxServiceInfo * pxDemuxServiceInfo,
  int                             xIsInClear,
  const TNhtSecDemuxEcmInfo     * pxDemuxEcmInfo,
  char                          * pxOutputFileName,
  TTransportSessionId           * pxTransportSessionId
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TSecStatus                 secStatus;
  TSecTraceEcmCallBackData * pEcmHandle = NULL;
  TNhtSecDemuxEcmInfo        ecmInfo;
  TNhtSecDemuxEcmInfo      * pEcmInfo = NULL;

  if (pgSecTransportIdSetMutex == NULL)
  {
    AVLSet_init ( &gSecTransportIdSet, &_secTransportSessionId_compare, 0);
    pgSecTransportIdSetMutex = MSGBUF_SYS_createThreadMutex();
  }

  pEcmHandle = (TSecTraceEcmCallBackData*)MSGBUF_SYS_malloc(sizeof(TSecTraceEcmCallBackData));
  pEcmHandle->ecmCallBackFct         = NULL;
  pEcmHandle->ecmCallBackPrivateData = NULL;

  if (pxDemuxEcmInfo)
  {
    pEcmInfo = &ecmInfo;

    pEcmInfo->ecmCbfct = &TRACE_secRpcEcmCallBackFunction;
    pEcmInfo->ecmCbPrivateData = (void*)pEcmHandle;
    pEcmInfo->ecmPid = pxDemuxEcmInfo->ecmPid;
    pEcmHandle->ecmCallBackFct = pxDemuxEcmInfo->ecmCbfct;
    pEcmHandle->ecmCallBackPrivateData = pxDemuxEcmInfo->ecmCbPrivateData;
  }

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecOpenDscTransportSession():\n");
    msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxInputFileName", (const char*)pxInputFileName);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDemuxServiceInfo", (const void*)pxDemuxServiceInfo);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    if (pxDemuxServiceInfo)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxServiceInfo->videoPid", (size_t)pxDemuxServiceInfo->videoPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxServiceInfo->audioPid", (size_t)pxDemuxServiceInfo->audioPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxServiceInfo->pcrPid", (size_t)pxDemuxServiceInfo->pcrPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xIsInClear", (size_t)xIsInClear, sizeof(int));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDemuxEcmInfo", (const void*)pxDemuxEcmInfo);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    if (pxDemuxEcmInfo)
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDemuxEcmInfo->ecmCbfct", (const void*)(size_t)pEcmInfo->ecmCbfct);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDemuxEcmInfo->ecmCbPrivateData", (const void*)pEcmInfo->ecmCbPrivateData);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxEcmInfo->ecmPid", (size_t)pEcmInfo->ecmPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxOutputFileName", (const char*)pxOutputFileName);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxTransportSessionId", (void*)pxTransportSessionId);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecOpenDscTransportSession (
    pxInputFileName,
    pxDemuxServiceInfo,
    xIsInClear,
    pEcmInfo,
    pxOutputFileName,
    pxTransportSessionId );


  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecOpenDscTransportSession():\n");
    if (pxTransportSessionId && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxTransportSessionId", (size_t)*pxTransportSessionId, sizeof(TTransportSessionId));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if ((secStatus != SEC_NO_ERROR) || (pxTransportSessionId == NULL))
  {
    if (pEcmHandle) MSGBUF_SYS_free(pEcmHandle);
  }
  else
  {
    if (pEcmHandle)
    {
      TRpcSecTransportHandle * pTransportHandle;
      TAVLSet_iter           * pIter;

      pTransportHandle   = (TRpcSecTransportHandle*)MSGBUF_SYS_malloc(sizeof (TRpcSecTransportHandle));
      AVLSet_iterInit ((TAVLSet_iter*)pTransportHandle);
      pTransportHandle->transportSessionId = *pxTransportSessionId;
      pTransportHandle->pEcmHandle = pEcmHandle;

      MSGBUF_SYS_acquireThreadMutex (pgSecTransportIdSetMutex);
      pIter = AVLSet_insert (&gSecTransportIdSet, (TAVLSet_iter*)pTransportHandle);
      MSGBUF_SYS_releaseThreadMutex (pgSecTransportIdSetMutex);

      if (pIter == AVLSet_end(&gSecTransportIdSet)) MSGBUF_SYS_free(pTransportHandle);
    }
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(nhtSecOpenScrTransportSession)
(
  char                          * pxInputFileName,
  const TNhtSecDemuxServiceInfo * pxDemuxServiceInfo,
  int                             xIsForEncryption,
  char                          * pxOutputFileName,
  TTransportSessionId           * pxTransportSessionId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus;

  if (pgSecTransportIdSetMutex == NULL)
  {
    AVLSet_init ( &gSecTransportIdSet, &_secTransportSessionId_compare, 0);
    pgSecTransportIdSetMutex = MSGBUF_SYS_createThreadMutex();
  }

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecOpenScrTransportSession():\n");
    msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxInputFileName", (const char*)pxInputFileName);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDemuxServiceInfo", (const void*)pxDemuxServiceInfo);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    if (pxDemuxServiceInfo)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxServiceInfo->videoPid", (size_t)pxDemuxServiceInfo->videoPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxServiceInfo->audioPid", (size_t)pxDemuxServiceInfo->audioPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDemuxServiceInfo->pcrPid", (size_t)pxDemuxServiceInfo->pcrPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xIsForEncryption", (size_t)xIsForEncryption, sizeof(int));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxOutputFileName", (const char*)pxOutputFileName);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxTransportSessionId", (void*)pxTransportSessionId);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecOpenScrTransportSession (
    pxInputFileName,
    pxDemuxServiceInfo,
    xIsForEncryption,
    pxOutputFileName,
    pxTransportSessionId );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecOpenScrTransportSession():\n");

    if (pxTransportSessionId && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxTransportSessionId", (size_t)*pxTransportSessionId, sizeof(TTransportSessionId));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TNhtSecTransportStreamingStatus _CRPC(nhtSecStartTransportSessionStreaming)
(
  TTransportSessionId xTransportSessionId
)
{
  TMsgbufStrBuffer                msgStrBuffer;
  int                             callId;
  TNhtSecTransportStreamingStatus secTransportStreamingStatus = NHT_SEC_STREAMING_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecStartTransportSessionStreaming():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secTransportStreamingStatus = nhtSecStartTransportSessionStreaming (xTransportSessionId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecStartTransportSessionStreaming():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secTransportStreamingStatus", (size_t)secTransportStreamingStatus, sizeof(TNhtSecTransportStreamingStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secTransportStreamingStatus;
}

/* */
TNhtSecTransportStreamingStatus _CRPC(nhtSecWaitOnTransportSessionStreamingCompletion)
(
  TTransportSessionId xTransportSessionId,
  int                 xTimeout
)
{
  TMsgbufStrBuffer                msgStrBuffer;
  int                             callId;
  TNhtSecTransportStreamingStatus secTransportStreamingStatus = NHT_SEC_STREAMING_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecWaitOnTransportSessionStreamingCompletion():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTimeout", (size_t)xTimeout, sizeof(int));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secTransportStreamingStatus = nhtSecWaitOnTransportSessionStreamingCompletion (xTransportSessionId, xTimeout);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecWaitOnTransportSessionStreamingCompletion():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secTransportStreamingStatus", (size_t)secTransportStreamingStatus, sizeof(TNhtSecTransportStreamingStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secTransportStreamingStatus;
}

/* */
TNhtSecTransportStreamingStatus _CRPC(nhtSecStopTransportSessionStreaming)
(
  TTransportSessionId xTransportSessionId
)
{
  TMsgbufStrBuffer                msgStrBuffer;
  int                             callId;
  TNhtSecTransportStreamingStatus secTransportStreamingStatus = NHT_SEC_STREAMING_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecStopTransportSessionStreaming():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secTransportStreamingStatus = nhtSecStopTransportSessionStreaming (xTransportSessionId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecStopTransportSessionStreaming():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secTransportStreamingStatus", (size_t)secTransportStreamingStatus, sizeof(TNhtSecTransportStreamingStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secTransportStreamingStatus;
}

/* */
TSecStatus _CRPC(nhtSecCloseTransportSession)
(
  TTransportSessionId xTransportSessionId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecCloseTransportSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xTransportSessionId", (size_t)xTransportSessionId, sizeof(TTransportSessionId));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecCloseTransportSession (xTransportSessionId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecCloseTransportSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (secStatus == SEC_NO_ERROR)
  {
    TRpcSecTransportHandle   transportHandle;
    TRpcSecTransportHandle * pTransportHandle = NULL;
    TAVLSet_iter           * pIter;

    transportHandle.transportSessionId = xTransportSessionId;

    MSGBUF_SYS_acquireThreadMutex (pgSecTransportIdSetMutex);
    pIter = AVLSet_find (&gSecTransportIdSet, (TAVLSet_iter*)&transportHandle);
    if (pIter != AVLSet_end(&gSecTransportIdSet))
    {
      pTransportHandle = (TRpcSecTransportHandle*)pIter;
      if (pTransportHandle->pEcmHandle) MSGBUF_SYS_free (pTransportHandle->pEcmHandle);
      AVLSet_remove (&gSecTransportIdSet, pIter);
      MSGBUF_SYS_free (pIter);
    }

    MSGBUF_SYS_releaseThreadMutex (pgSecTransportIdSetMutex);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(nhtSecSetTransportSessionInitialValue)
(
  TSecCipherSession     xSession,
  size_t                xKeyIdSize,
  TUnsignedInt8       * pxKeyId,
  size_t                xInitVectorSize,
  const TUnsignedInt8 * pxInitVector
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecSetTransportSessionInitialValue():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyIdSize", (size_t)xKeyIdSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxKeyId", (void*)pxKeyId, (size_t)xKeyIdSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitVectorSize", (size_t)xInitVectorSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitVector", (const void*)pxInitVector, (size_t)xInitVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecSetTransportSessionInitialValue (
    xSession,
    xKeyIdSize,
    pxKeyId,
    xInitVectorSize,
    pxInitVector );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecSetTransportSessionInitialValue():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}

/* */
TSecStatus _CRPC(nhtSecGetNhtSecApiVersion)
(
  TUnsignedInt32 * pxApiVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TSecStatus       secStatus = SEC_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtSecGetNhtSecApiVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxApiVersion", (void*)pxApiVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  secStatus = nhtSecGetNhtSecApiVersion (pxApiVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtSecGetNhtSecApiVersion():\n");

    if (pxApiVersion && (secStatus == SEC_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxApiVersion", (size_t)*pxApiVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: secStatus", (size_t)secStatus, sizeof(TSecStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return secStatus;
}


#endif /* _NHT_RPC_TRACE_ON_ */
