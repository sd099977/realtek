/**
 * File: $Id:$
 *
 *  This file implements the server/client common CERT API/EAPI function traces.
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
#include "inc/TRACE_nhtcert.h"


#ifdef _NHT_RPC_TRACE_ON_

static TCertFunctionTable * pgCertFunctionTable = NULL;
static TCertFunctionTable   gTraceCertFunctionTable;

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

/* */
static TCertStatus _CRPC(certLock)
(
  TCertResourceHandle * pxResourceHandle
)
{
  TMsgbufStrBuffer    msgStrBuffer;
  int                 callId;
  TCertStatus         certStatus = CERT_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@pCertFunctionTable->certLock():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxResourceHandle", (void*)pxResourceHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  certStatus = pgCertFunctionTable->certLock (pxResourceHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pCertFunctionTable->certLock():\n");
    if (pxResourceHandle && (certStatus == CERT_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxResourceHandle", (void*)*pxResourceHandle);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: certStatus", (size_t)certStatus, sizeof(TCertStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return certStatus;
}


/* */
static TCertStatus _CRPC(certUnlock)
(
  TCertResourceHandle xResourceHandle
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCertStatus      certStatus = CERT_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@pCertFunctionTable->certUnlock():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xResourceHandle", (void*)xResourceHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  certStatus = pgCertFunctionTable->certUnlock (xResourceHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pCertFunctionTable->certUnlock():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: certStatus", (size_t)certStatus, sizeof(TCertStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return certStatus;
}


/* */
static TCertStatus _CRPC(certExchange)
(
  TCertResourceHandle   xResourceHandle,
  size_t                xNumOfCommands,
  const TCertCommand  * pxCommands,
  size_t              * pxNumOfProcessedCommands
)
{
  TMsgbufStrBuffer   msgStrBuffer;
  int                callId;
  TCertStatus        certStatus = CERT_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    size_t i;

    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@pCertFunctionTable->certExchange():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xResourceHandle", (void*)xResourceHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xNumOfCommands", (size_t)xNumOfCommands, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNumOfProcessedCommands", (void*)pxNumOfProcessedCommands);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxCommands", (void*)pxCommands);

    for (i=0; i < xNumOfCommands; i++)
    {
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCommands[i].inputData", (void*)pxCommands[i].inputData, 32);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCommands[i].opcodes", (void*)pxCommands[i].opcodes, 4);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxCommands[i].timeout", (size_t)pxCommands[i].timeout, sizeof(TCertTimeoutType));
    }

    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  certStatus = pgCertFunctionTable->certExchange (
    xResourceHandle,
    xNumOfCommands,
    pxCommands,
    pxNumOfProcessedCommands );

  if (RPC_FTRACE_IS_ENABLED())
  {
    size_t i;

    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pCertFunctionTable->certExchange():\n");

    if (pxNumOfProcessedCommands)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxNumOfProcessedCommands", (size_t)*pxNumOfProcessedCommands, sizeof(size_t));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    if ((certStatus == CERT_NO_ERROR) && pxCommands)
    {
      for (i=0; i < xNumOfCommands; i++)
      {
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxCommands[i].outputData", (void*)pxCommands[i].outputData, 32);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
        msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxCommands[i].status", (void*)pxCommands[i].status, 4);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: certStatus", (size_t)certStatus, sizeof(TCertStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return certStatus;
}


/* */
static TCertStatus _CRPC(certUseEncryptionKey)
(
  TCertUInt16          xEmi,
  TCertKeyPathHandle * pxKeyPathHandle,
  TCertKeyParity       xKeyParity
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCertStatus      certStatus = CERT_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@pCertFunctionTable->certUseEncryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TCertUInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxKeyPathHandle", (void*)pxKeyPathHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyParity", (size_t)xKeyParity, sizeof(TCertKeyParity));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  certStatus = pgCertFunctionTable->certUseEncryptionKey (
    xEmi,
    pxKeyPathHandle,
    xKeyParity );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pCertFunctionTable->certUseEncryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: certStatus", (size_t)certStatus, sizeof(TCertStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return certStatus;

}


/* */
static TCertStatus _CRPC(certUseDecryptionKey)
(
  TCertUInt16          xEmi,
  TCertKeyPathHandle * pxKeyPathHandle,
  TCertKeyParity       xKeyParity
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCertStatus      certStatus = CERT_NO_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@pCertFunctionTable->certUseDecryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TCertUInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxKeyPathHandle", (void*)pxKeyPathHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyParity", (size_t)xKeyParity, sizeof(TCertKeyParity));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  certStatus = pgCertFunctionTable->certUseDecryptionKey (
    xEmi,
    pxKeyPathHandle,
    xKeyParity );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@pCertFunctionTable->certUseDecryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: certStatus", (size_t)certStatus, sizeof(TCertStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return certStatus;

}

/* */
TCertFunctionTable * _CRPC(certGetFunctionTable) (void)
{
  TMsgbufStrBuffer     msgStrBuffer;
  int                  callId;
  TCertFunctionTable * pCertFunctionTable = pgCertFunctionTable;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@certGetFunctionTable()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (pgCertFunctionTable == NULL) pgCertFunctionTable = certGetFunctionTable();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@certGetFunctionTable():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "ret: pCertFunctionTable", (void*)pgCertFunctionTable);

    if (pgCertFunctionTable)
    {
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pCertFunctionTable->certLock", (void*)(size_t)pgCertFunctionTable->certLock);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pCertFunctionTable->certUnlock", (void*)(size_t)pgCertFunctionTable->certUnlock);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pCertFunctionTable->certExchange", (void*)(size_t)pgCertFunctionTable->certExchange);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pCertFunctionTable->certUseEncryptionKey", (void*)(size_t)pgCertFunctionTable->certUseEncryptionKey);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: pCertFunctionTable->certUseDecryptionKey", (void*)(size_t)pgCertFunctionTable->certUseDecryptionKey);
    }
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (pgCertFunctionTable && (pCertFunctionTable == NULL))
  {
    gTraceCertFunctionTable.certApiVersion = pgCertFunctionTable->certApiVersion;

    if (pgCertFunctionTable->certLock) gTraceCertFunctionTable.certLock = &_CRPC(certLock);
    else gTraceCertFunctionTable.certLock = NULL;

    if (pgCertFunctionTable->certUnlock) gTraceCertFunctionTable.certUnlock = &_CRPC(certUnlock);
    else gTraceCertFunctionTable.certUnlock = NULL;

    if (pgCertFunctionTable->certExchange) gTraceCertFunctionTable.certExchange = &_CRPC(certExchange);
    else gTraceCertFunctionTable.certExchange = NULL;

    if (pgCertFunctionTable->certUseEncryptionKey) gTraceCertFunctionTable.certUseEncryptionKey = &_CRPC(certUseEncryptionKey);
    else gTraceCertFunctionTable.certUseEncryptionKey = NULL;

    if (pgCertFunctionTable->certUseDecryptionKey) gTraceCertFunctionTable.certUseDecryptionKey = &_CRPC(certUseDecryptionKey);
    else gTraceCertFunctionTable.certUseDecryptionKey = NULL;
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  if (pgCertFunctionTable) return &gTraceCertFunctionTable;
  else return NULL;
}

#endif /* _NHT_RPC_TRACE_ON_ */
