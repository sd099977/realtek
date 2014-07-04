/**
 * File: $Id:$
 *
 *  This file implements the BSD RPC server glue code.
 *  This file stands as the customization of the template generated
 *  by the msgbuf compiler associated to BSD API.
 *
 *  Copyright (c) 2012-2013 Nagravision. All rights reserved.
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


/*****************************************************************************
 * include files                                                             *
 ****************************************************************************/

#include "src/rpc_nhtbsd_api.h"
#include "nocs_nhtbsd.h"
#include "inc/nv_nhtbsd.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/hndmng.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/os/none/serial_rpc_service.h"
#include "inc/nhtbsd_r2r_test_algo.h"
#include "inc/TRACE_nhtbsd.h"
#include "inc/TRACE_p_nhtbsd.h"


static int _hndmng_r2rSessionClose
(
  void * pxHandle
)
{
  TBsdCipherSession r2rSession = (TBsdCipherSession)pxHandle;
  _CRPC(bsdCloseSession) (r2rSession);
  return 0;
}


static int _hndmng_hashSessionClose
(
  void * pxHandle
)
{
  TUnsignedInt8 buffer[32];

  TBsdHashContext hashSession = (TBsdHashContext)pxHandle;
  _CRPC(bsdSha256Final) (hashSession, buffer);
  return 0;
}


static int _hndmng_sysBufferClose
(
  void * pxHandle
)
{
  hndmng_unregister (pxHandle);
  return 0;
}

/*****************************************************************************
 * RPC methods implementation                                                *
 ****************************************************************************/

/* RPC method: rpc_nhtbsd_hc_nhtbsd_initialize
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nhtbsd_initialize
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtbsd_EmptyMsg   * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;

  bsdStatus = _CRPC(nhtBsdInitialize) ();

  if (bsdStatus == BSD_NO_ERROR) hndmng_terminate();

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nhtbsd_terminate
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nhtbsd_terminate
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtbsd_EmptyMsg   * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;

  hndmng_terminate();
  bsdStatus = _CRPC(nhtBsdTerminate) ();

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtbsd_hc_nht_getNhtBsdApiVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getNhtBsdApiVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_VersionRevisionOutMsg ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt32  version = 0;

  if (pxInputMessage->has_output)
    bsdStatus = _CRPC(nhtGetNhtBsdApiVersion) (&version);
  else bsdStatus = _CRPC(nhtGetNhtBsdApiVersion) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  (*pxOutputMessage)->versionRevision = (uint32_t)version;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getBsdApiVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getBsdApiVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_VersionRevisionOutMsg ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt32  version = 0;

  if (pxInputMessage->has_output)
    bsdStatus = _CRPC(bsdGetApiVersion) (&version);
  else bsdStatus = _CRPC(bsdGetApiVersion) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  (*pxOutputMessage)->versionRevision = (uint32_t)version;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_getNhtBsdSoftwareVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getNhtBsdSoftwareVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_StringOutMsg          ** pxOutputMessage
)
{
  TBsdStatus         bsdStatus;
  TBsd20CharsString  * pVersionStr = NULL;

  if (pxInputMessage->has_output)
  {
    pVersionStr = (TBsd20CharsString*)MSGBUF_SYS_malloc (sizeof(TBsd20CharsString) + 1);
    if (pVersionStr == NULL) return RPC_STATUS_MALLOC_ERROR;

    bsdStatus = _CRPC(nhtBsdGetSoftwareVersion) (*pVersionStr);

    if (pVersionStr) (*pVersionStr)[sizeof(TBsd20CharsString)] = 0;
    if (bsdStatus == BSD_NO_ERROR) (*pxOutputMessage)->info = (char*)&pVersionStr[0];
    else MSGBUF_SYS_free (pVersionStr);

  }
  else
    bsdStatus = _CRPC(nhtBsdGetSoftwareVersion) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getBsdSoftwareVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getBsdSoftwareVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_StringOutMsg          ** pxOutputMessage
)
{
  TBsdStatus         bsdStatus;
  TBsd20CharsString  * pVersionStr = NULL;

  if (pxInputMessage->has_output)
  {
    pVersionStr = (TBsd20CharsString*)MSGBUF_SYS_malloc (sizeof(TBsd20CharsString) + 1);
    if (pVersionStr == NULL) return RPC_STATUS_MALLOC_ERROR;

    bsdStatus = _CRPC(bsdGetSoftwareVersion) (*pVersionStr);

    if (pVersionStr) (*pVersionStr)[sizeof(TBsd20CharsString)] = 0;
    if (bsdStatus == BSD_NO_ERROR) (*pxOutputMessage)->info = (char*)&pVersionStr[0];
    else MSGBUF_SYS_free (pVersionStr);

  }
  else
    bsdStatus = _CRPC(bsdGetSoftwareVersion) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_getBsdStatusOffsetValue
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getBsdStatusOffsetValue
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_NumberOutMsg          ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt32  statusOffset = 0;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(nhtGetNhtBsdApiVersion) (&statusOffset);
    (*pxOutputMessage)->has_value = 1;
  }
  else bsdStatus = _CRPC(nhtGetNhtBsdApiVersion) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  (*pxOutputMessage)->value = (uint32_t)statusOffset;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_getNocsCertificationVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getNocsCertificationVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_VersionRevisionOutMsg ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt32  version = 0;

  if (pxInputMessage->has_output)
    bsdStatus = _CRPC(nhtBsdGetCertificationNOCSVersion) (&version);
  else bsdStatus = _CRPC(nhtBsdGetCertificationNOCSVersion) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  (*pxOutputMessage)->versionRevision = (uint32_t)version;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getChipsetInfo
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getChipsetInfo
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_String4OutMsg         ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TRpc_status     rpcStatus = RPC_STATUS_NO_ERROR;
  TBsdInfoChipset chipsetInfo;

  if (pxInputMessage->has_output)
  {
    char * pCM  = NULL;
    char * pCT  = NULL;
    char * pCUT = NULL;
    char * pEXT = NULL;

    bsdStatus = _CRPC(bsdChipsetInformation) (&chipsetInfo);

    if (bsdStatus == BSD_NO_ERROR)
    {
      pCM = (char*)MSGBUF_SYS_malloc (sizeof(chipsetInfo.BSD_CM) + 1);
      if (pCM) MSGBUF_SYS_strncpy (pCM, (char*)&chipsetInfo.BSD_CM[0], sizeof(chipsetInfo.BSD_CM));
      else rpcStatus = RPC_STATUS_MALLOC_ERROR;

      pCT = (char*)MSGBUF_SYS_malloc (sizeof(chipsetInfo.BSD_CT) + 1);
      if (pCT) MSGBUF_SYS_strncpy (pCT, (char*)&chipsetInfo.BSD_CT[0], sizeof(chipsetInfo.BSD_CT));
      else rpcStatus = RPC_STATUS_MALLOC_ERROR;

      pCUT = (char*)MSGBUF_SYS_malloc (sizeof(chipsetInfo.BSD_CUT) + 1);
      if (pCUT) MSGBUF_SYS_strncpy (pCUT, (char*)&chipsetInfo.BSD_CUT[0], sizeof(chipsetInfo.BSD_CUT));
      else rpcStatus = RPC_STATUS_MALLOC_ERROR;

      pEXT = (char*)MSGBUF_SYS_malloc (sizeof(chipsetInfo.BSD_EXT) + 1);
      if (pEXT) MSGBUF_SYS_strncpy (pEXT, (char*)&chipsetInfo.BSD_EXT[0], sizeof(chipsetInfo.BSD_EXT));
      else rpcStatus = RPC_STATUS_MALLOC_ERROR;

      if (rpcStatus == RPC_STATUS_MALLOC_ERROR)
      {
        if (pCT) MSGBUF_SYS_free(pCT);
        if (pCM) MSGBUF_SYS_free(pCM);
        if (pCUT) MSGBUF_SYS_free(pCUT);
        if (pEXT) MSGBUF_SYS_free(pEXT);
      }
      else
      {
        (*pxOutputMessage)->info1 = (char*)pCM;  pCM[sizeof(chipsetInfo.BSD_CM)] = 0;
        (*pxOutputMessage)->info2 = (char*)pCT;  pCT[sizeof(chipsetInfo.BSD_CT)] = 0;
        (*pxOutputMessage)->info3 = (char*)pCUT; pCUT[sizeof(chipsetInfo.BSD_CUT)] = 0;
        (*pxOutputMessage)->info4 = (char*)pEXT; pEXT[sizeof(chipsetInfo.BSD_EXT)] = 0;
      }
    }
  }
  else bsdStatus = _CRPC(bsdChipsetInformation) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return rpcStatus;
}

/* RPC method: rpc_nhtbsd_hc_nht_getChipManufacturerName
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getChipManufacturerName
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_StringOutMsg          ** pxOutputMessage
)
{
  TBsdStatus         bsdStatus;
  TBsd20CharsString  * pManufacturerName = NULL;

  if (pxInputMessage->has_output)
  {
    pManufacturerName = (TBsd20CharsString*)MSGBUF_SYS_malloc (sizeof(TBsd20CharsString) + 1);
    if (pManufacturerName == NULL) return RPC_STATUS_MALLOC_ERROR;

    bsdStatus = _CRPC(nhtBsdGetChipManufacturerName) (*pManufacturerName);

    if (pManufacturerName) (*pManufacturerName)[sizeof(TBsd20CharsString)] = 0;
    if (bsdStatus == BSD_NO_ERROR) (*pxOutputMessage)->info = (char*)&pManufacturerName[0];
    else MSGBUF_SYS_free (pManufacturerName);

  }
  else
    bsdStatus = _CRPC(nhtBsdGetChipManufacturerName) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_getChipName
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getChipName
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_StringOutMsg          ** pxOutputMessage
)
{
  TBsdStatus         bsdStatus;
  TBsd20CharsString  * pChipName = NULL;

  if (pxInputMessage->has_output)
  {
    pChipName = (TBsd20CharsString*)MSGBUF_SYS_malloc (sizeof(TBsd20CharsString) + 1);
    if (pChipName == NULL) return RPC_STATUS_MALLOC_ERROR;

    bsdStatus = _CRPC(nhtBsdGetChipName) (*pChipName);

    if (pChipName) (*pChipName)[sizeof(TBsd20CharsString)] = 0;
    if (bsdStatus == BSD_NO_ERROR) (*pxOutputMessage)->info = (char*)&pChipName[0];
    else MSGBUF_SYS_free (pChipName);

  }
  else
    bsdStatus = _CRPC(nhtBsdGetChipName) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_getProtectingKeyNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_getProtectingKeyNumber
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_NumberOutMsg          ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt32  number = 0;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(nhtBsdGetBsdProtectingKeyNumber) (&number);
    (*pxOutputMessage)->has_value = 1;
  }
  else bsdStatus = _CRPC(nhtBsdGetBsdProtectingKeyNumber) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  (*pxOutputMessage)->value = (uint32_t)number;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getNuid
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getNuid
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg           ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector nuid;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(bsdGetNuid) (nuid);
    if (bsdStatus == BSD_NO_ERROR)
    {
      void * pBytes;

      pBytes = (void*)MSGBUF_SYS_malloc (sizeof(TBsd4BytesVector));
      if (pBytes)
      {
        (*pxOutputMessage)->byteArray.pData = (void*)pBytes;
        (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TBsd4BytesVector);
        MSGBUF_SYS_memcpy (pBytes, nuid, sizeof(TBsd4BytesVector));
      }
      else return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else bsdStatus = _CRPC(bsdGetNuid) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getNuid64
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getNuid64
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg           ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd8BytesVector nuid64;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(bsdGetNuid64) (nuid64);
    if (bsdStatus == BSD_NO_ERROR)
    {
      void * pBytes;

      pBytes = (void*)MSGBUF_SYS_malloc (sizeof(TBsd8BytesVector));
      if (pBytes)
      {
        (*pxOutputMessage)->byteArray.pData = (void*)pBytes;
        (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TBsd8BytesVector);
        MSGBUF_SYS_memcpy (pBytes, nuid64, sizeof(TBsd8BytesVector));
      }
      else return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else bsdStatus = _CRPC(bsdGetNuid) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_setStbCaSn
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_setStbCaSn
(
  TMsgBuf_rpcHandler          xRpcHandler,
  const TNhtbsd_BytesInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg  ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector stbCaSn;

  if (pxInputMessage->input.pData)
  {
    MSGBUF_SYS_memcpy (&stbCaSn[0], pxInputMessage->input.pData, sizeof(TBsd4BytesVector));
    bsdStatus = _CRPC(bsdSetStbCaSn) (stbCaSn);
  }
  else bsdStatus = _CRPC(bsdSetStbCaSn) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getStbCaSn
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getStbCaSn
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg           ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector stbCaSn;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(bsdGetStbCaSn) (stbCaSn);
    if (bsdStatus == BSD_NO_ERROR)
    {
      void * pBytes;

      pBytes = (void*)MSGBUF_SYS_malloc (sizeof(TBsd4BytesVector));
      if (pBytes)
      {
        (*pxOutputMessage)->byteArray.pData = (void*)pBytes;
        (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TBsd4BytesVector);
        MSGBUF_SYS_memcpy (pBytes, stbCaSn, sizeof(TBsd4BytesVector));
      }
      else return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else bsdStatus = _CRPC(bsdGetStbCaSn) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_setMarketSegmentId
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_setMarketSegmentId
(
  TMsgBuf_rpcHandler          xRpcHandler,
  const TNhtbsd_BytesInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg  ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector segmentId;

  if (pxInputMessage->input.pData)
  {
    MSGBUF_SYS_memcpy (&segmentId[0], pxInputMessage->input.pData, sizeof(TBsd4BytesVector));
    bsdStatus = _CRPC(bsdSetMarketSegmentId) (segmentId);
  }
  else bsdStatus = _CRPC(bsdSetMarketSegmentId) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getMarketSegmentId
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getMarketSegmentId
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg           ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector segmentId;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(bsdGetMarketSegmentId) (segmentId);
    if (bsdStatus == BSD_NO_ERROR)
    {
      void * pBytes;

      pBytes = (void*)MSGBUF_SYS_malloc (sizeof(TBsd4BytesVector));
      if (pBytes)
      {
        (*pxOutputMessage)->byteArray.pData = (void*)pBytes;
        (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TBsd4BytesVector);
        MSGBUF_SYS_memcpy (pBytes, segmentId, sizeof(TBsd4BytesVector));
      }
      else return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else bsdStatus = _CRPC(bsdGetMarketSegmentId) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getNuidCheckNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getNuidCheckNumber
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg           ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector nuidCheckNumber;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(bsdGetNUIDCheckNumber) (nuidCheckNumber);
    if (bsdStatus == BSD_NO_ERROR)
    {
      void * pBytes;

      pBytes = (void*)MSGBUF_SYS_malloc (sizeof(TBsd4BytesVector));
      if (pBytes)
      {
        (*pxOutputMessage)->byteArray.pData = (void*)pBytes;
        (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TBsd4BytesVector);
        MSGBUF_SYS_memcpy (pBytes, nuidCheckNumber, sizeof(TBsd4BytesVector));
      }
      else return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else bsdStatus = _CRPC(bsdGetNUIDCheckNumber) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_getDataIntegrityCheckNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_getDataIntegrityCheckNumber
(
  TMsgBuf_rpcHandler                     xRpcHandler,
  const TNhtbsd_CheckNumberBytesInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg                 ** pxOutputMessage
)
{
  TBsdStatus       bsdStatus;
  TBsd4BytesVector checkNumber;

  if (pxInputMessage->has_output)
  {
    bsdStatus = _CRPC(bsdGetDataIntegrityCheckNumber) (
      (const TUnsignedInt8*)pxInputMessage->input.pData,
      (TUnsignedInt32)pxInputMessage->len_input,
      checkNumber );

    if (bsdStatus == BSD_NO_ERROR)
    {
      void * pBytes;

      pBytes = (void*)MSGBUF_SYS_malloc (sizeof(TBsd4BytesVector));
      if (pBytes)
      {
        (*pxOutputMessage)->byteArray.pData = (void*)pBytes;
        (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TBsd4BytesVector);
        MSGBUF_SYS_memcpy (pBytes, checkNumber, sizeof(TBsd4BytesVector));
      }
      else return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else
    bsdStatus = _CRPC(bsdGetDataIntegrityCheckNumber) (
      (const TUnsignedInt8*)pxInputMessage->input.pData,
      (TUnsignedInt32)pxInputMessage->len_input,
      NULL );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_bsdPrint
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_bsdPrint
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtbsd_StringInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg   ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;

  bsdStatus = _CRPC(bsdPrint) ((const TChar*)pxInputMessage->info);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_encryptFlashProtKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_encryptFlashProtKey
(
  TMsgBuf_rpcHandler                        xRpcHandler,
  const TNhtbsd_EncryptFlashProtKeyInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg                    ** pxOutputMessage
)
{
  TBsdStatus            bsdStatus;
  TUnsignedInt8       * pOutput = NULL;
  TUnsignedInt8       * pInput = NULL;
  TUnsignedInt8       * pInBufferInput = NULL;
  TUnsignedInt8       * pInBufferOutput = NULL;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (pxInputMessage->len_input);
    if (pOutput== NULL)
      return RPC_STATUS_MALLOC_ERROR;

    if (pxInputMessage->has_outputBufferHandle)
      pInBufferOutput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pInBufferOutput = pOutput;
  }

  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->inputBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, pxInputMessage->len_input);
    }
    else pInBufferInput = pInput;
  }
  else pInBufferInput = NULL;

  bsdStatus = _CRPC(bsdEncryptFlashProtKey) (
    pInBufferInput,
    pInBufferOutput,
    (size_t)pxInputMessage->len_input );

  if ((bsdStatus == BSD_NO_ERROR) && pInBufferOutput && pOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pInBufferOutput, pxInputMessage->len_input);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)pxInputMessage->len_input;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_allocateSysBuffer
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_allocateSysBuffer
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtbsd_SizeInMsg  * pxInputMessage,
  TNhtbsd_HandleOutMsg    ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus = BSD_NO_ERROR;
  TUnsignedInt8 * pSysBuffer;

  pSysBuffer = _CRPC(bsdAllocateBuffer) ((size_t)pxInputMessage->value);

  if (pSysBuffer)
  {
    hndmng_register (pSysBuffer, &_hndmng_sysBufferClose);
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)pSysBuffer;
  }
  else (*pxOutputMessage)->has_handle = 0;

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_deallocateSysBuffer
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_deallocateSysBuffer
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtbsd_HandleInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg   ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;

  if (pxInputMessage->has_handle)
  {
    bsdStatus = _CRPC(bsdFreeBuffer) ((TUnsignedInt8*)(size_t)pxInputMessage->handle);
    hndmng_unregister ((void*)(size_t)pxInputMessage->handle);
  }
  else bsdStatus = _CRPC(bsdFreeBuffer) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_openR2REncryptSession
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_openR2REncryptSession
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_HandleOutMsg          ** pxOutputMessage
)
{
  TBsdStatus          bsdStatus;
  TBsdCipherSession   session;

  if (pxInputMessage->has_output)
    bsdStatus = _CRPC(bsdOpenRam2RamEncryptSession) (&session);
  else bsdStatus = _CRPC(bsdOpenRam2RamEncryptSession) (NULL);

  if ((bsdStatus == BSD_NO_ERROR) && pxInputMessage->has_output)
  {
    hndmng_register (session, &_hndmng_r2rSessionClose);
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)session;
  }
  else (*pxOutputMessage)->has_handle = 0;

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_openR2RDecryptSession
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_openR2RDecryptSession
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_HandleOutMsg          ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdCipherSession session;

  if (pxInputMessage->has_output)
    bsdStatus = _CRPC(bsdOpenRam2RamDecryptSession) (&session);
  else bsdStatus = _CRPC(bsdOpenRam2RamDecryptSession) (NULL);

  if ((bsdStatus == BSD_NO_ERROR) && pxInputMessage->has_output)
  {
    hndmng_register (session, &_hndmng_r2rSessionClose);
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)session;
  }
  else (*pxOutputMessage)->handle = 0;

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_nht_closeR2RSessionHandle
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_nht_closeR2RSessionHandle
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtbsd_HandleInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg   ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;

  if (pxInputMessage->has_handle)
  {
    bsdStatus = _CRPC(bsdCloseSession) ((TBsdCipherSession)(size_t)pxInputMessage->handle);
    hndmng_unregister ((void*)(size_t)pxInputMessage->handle);
  }
  else bsdStatus = _CRPC(bsdCloseSession) (NULL);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_setClearTextKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_setClearTextKey
(
  TMsgBuf_rpcHandler                 xRpcHandler,
  const TNhtbsd_ClearTextKeyInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg         ** pxOutputMessage
)
{
  TBsdStatus          bsdStatus;
  TBsdCipherSession   session    = NULL;
  TUnsignedInt8     * pKey       = NULL;
  TUnsignedInt8     * pKeyBuffer = NULL;
  int                 keySize;

  if (pxInputMessage->has_handle)
    session = (TBsdCipherSession)(size_t) pxInputMessage->handle;
  else session = NULL;

  keySize = (int)pxInputMessage->keySize;
  pKey = (TUnsignedInt8*)pxInputMessage->key.pData;
  if (pKey)
  {
    if (pxInputMessage->has_keyHandle)
    {
      pKeyBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->keyHandle;
      MSGBUF_SYS_memcpy (pKeyBuffer, pKey, keySize);
    }
    else pKeyBuffer = pKey;
  }

  bsdStatus = _CRPC(bsdSetClearTextKey) (
    session,
    (TUnsignedInt16)         pxInputMessage->emi,
    (TSize)                  keySize,
    (const TUnsignedInt8*)   pKeyBuffer );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_set2LevelProtectedKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_set2LevelProtectedKey
(
  TMsgBuf_rpcHandler                       xRpcHandler,
  const TNhtbsd_Level2ProtectedKeyInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg               ** pxOutputMessage
)
{
  TBsdStatus          bsdStatus;
  TBsdCipherSession   session                        = NULL;
  TUnsignedInt8     * pCipheredContentKey            = NULL;
  TUnsignedInt8     * pCipheredContentKeyBuffer      = NULL;
  TUnsignedInt8     * pL1CipheredProtectingKey       = NULL;
  TUnsignedInt8     * pL1CipheredProtectingKeyBuffer = NULL;
  TUnsignedInt8     * pL2CipheredProtectingKey       = NULL;
  TUnsignedInt8     * pL2CipheredProtectingKeyBuffer = NULL;
  int                 cipheredContentKeySize;
  int                 cipheredProtectingKeySize;

  if (pxInputMessage->has_handle)
    session = (TBsdCipherSession)(size_t)pxInputMessage->handle;
  else session = NULL;

  cipheredContentKeySize = (int)pxInputMessage->cipheredContentKeySize;
  pCipheredContentKey = (TUnsignedInt8*)pxInputMessage->cipheredContentKey.pData;
  if (pCipheredContentKey)
  {
    if (pxInputMessage->has_cipheredContentKeyHandle)
    {
      pCipheredContentKeyBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->cipheredContentKeyHandle;
      MSGBUF_SYS_memcpy (pCipheredContentKeyBuffer, pCipheredContentKey, cipheredContentKeySize);
    }
    else pCipheredContentKeyBuffer = pCipheredContentKey;
  }

  cipheredProtectingKeySize = (int)pxInputMessage->cipheredProtectingKeySize;

  pL1CipheredProtectingKey = (TUnsignedInt8*)pxInputMessage->l1CipheredProtectingKey.pData;
  if (pL1CipheredProtectingKey)
  {
    if (pxInputMessage->has_l1CipheredProtectingKeyHandle)
    {
      pL1CipheredProtectingKeyBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->l1CipheredProtectingKeyHandle;
      MSGBUF_SYS_memcpy (pL1CipheredProtectingKeyBuffer, pL1CipheredProtectingKey, cipheredProtectingKeySize);
    }
    else pL1CipheredProtectingKeyBuffer = pL1CipheredProtectingKey;
  }

  pL2CipheredProtectingKey = (TUnsignedInt8*)pxInputMessage->l2CipheredProtectingKey.pData;
  if (pL2CipheredProtectingKey)
  {
    if (pxInputMessage->has_l2CipheredProtectingKeyHandle)
    {
      pL2CipheredProtectingKeyBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->l2CipheredProtectingKeyHandle;
      MSGBUF_SYS_memcpy (pL2CipheredProtectingKeyBuffer, pL2CipheredProtectingKey, cipheredProtectingKeySize);
    }
    else pL2CipheredProtectingKeyBuffer = pL2CipheredProtectingKey;
  }

  bsdStatus = _CRPC(bsdSet2LevelProtectedKey) (
    session,
    (TUnsignedInt16)        pxInputMessage->emi,
    (TSize)                 cipheredContentKeySize,
    (const TUnsignedInt8*)  pCipheredContentKeyBuffer,
    (TSize)                 cipheredProtectingKeySize,
    (const TUnsignedInt8*)  pL1CipheredProtectingKeyBuffer,
    (const TUnsignedInt8*)  pL2CipheredProtectingKeyBuffer );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_setFlashProtectingKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_setFlashProtectingKey
(
  TMsgBuf_rpcHandler                       xRpcHandler,
  const TNhtbsd_FlashProtectingKeyInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg               ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdCipherSession session = NULL;

  if (pxInputMessage->has_handle)
    session = (TBsdCipherSession)(size_t) pxInputMessage->handle;
  else session = NULL;

  bsdStatus = _CRPC(bsdUseFlashProtKey) (
    session,
    (TUnsignedInt16)         pxInputMessage->emi );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_useCertKey_inMsg
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_useCertKey_inMsg
(
  TMsgBuf_rpcHandler            xRpcHandler,
  const TNhtbsd_CertKeyInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg    ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdCipherSession session = NULL;

  if (pxInputMessage->has_handle)
    session = (TBsdCipherSession)(size_t) pxInputMessage->handle;
  else session = NULL;

  bsdStatus = _CRPC(bsdUseCertKey) (
    session,
    (TUnsignedInt16)         pxInputMessage->emi );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_r2rSessionEncrypt
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_r2rSessionEncrypt
(
  TMsgBuf_rpcHandler              xRpcHandler,
  const TNhtbsd_R2rCipherInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg          ** pxOutputMessage
)
{
  TBsdStatus          bsdStatus;
  TBsdCipherSession   session         = NULL;
  TUnsignedInt8     * pInput          = NULL;
  TUnsignedInt8     * pIv             = NULL;
  TUnsignedInt8     * pOutput         = NULL;
  TUnsignedInt8     * pInBufferInput  = NULL;
  TUnsignedInt8     * pInBufferOutput = NULL;
  TUnsignedInt8     * pInBufferIv     = NULL;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (pxInputMessage->inputSize);
    if (!pOutput) return RPC_STATUS_MALLOC_ERROR;

    if (pxInputMessage->has_outputBufferHandle)
      pInBufferOutput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pInBufferOutput = pOutput;
  }

  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->inputBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, pxInputMessage->inputSize);
    }
    else pInBufferInput = pInput;
  }

  pIv = (TUnsignedInt8*)pxInputMessage->iv.pData;
  if (pIv)
  {
    if (pxInputMessage->has_ivBufferHandle)
    {
      pInBufferIv = (TUnsignedInt8*)(size_t)pxInputMessage->ivBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferIv, pIv, pxInputMessage->ivSize);
    }
    else pInBufferIv = pIv;
  }

  if (pxInputMessage->has_handle)
    session = (TBsdCipherSession)(size_t) pxInputMessage->handle;
  else session = NULL;

  bsdStatus = _CRPC(bsdSessionEncrypt) (
    session,
    pInBufferInput,
    pInBufferOutput,
    (TSize) pxInputMessage->inputSize,
    pInBufferIv,
    (TSize) pxInputMessage->ivSize );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput && pInBufferOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pInBufferOutput, pxInputMessage->inputSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)pxInputMessage->inputSize;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_r2rSessionDecrypt
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_r2rSessionDecrypt
(
  TMsgBuf_rpcHandler              xRpcHandler,
  const TNhtbsd_R2rCipherInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg          ** pxOutputMessage
)
{
  TBsdStatus          bsdStatus;
  TBsdCipherSession   session         = NULL;
  TUnsignedInt8     * pInput          = NULL;
  TUnsignedInt8     * pIv             = NULL;
  TUnsignedInt8     * pOutput         = NULL;
  TUnsignedInt8     * pInBufferInput  = NULL;
  TUnsignedInt8     * pInBufferOutput = NULL;
  TUnsignedInt8     * pInBufferIv     = NULL;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (pxInputMessage->inputSize);
    if (!pOutput) return RPC_STATUS_MALLOC_ERROR;

    if (pxInputMessage->has_outputBufferHandle)
      pInBufferOutput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pInBufferOutput = pOutput;
  }

  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->inputBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, pxInputMessage->inputSize);
    }
    else pInBufferInput = pInput;
  }

  pIv = (TUnsignedInt8*)pxInputMessage->iv.pData;
  if (pIv)
  {
    if (pxInputMessage->has_ivBufferHandle)
    {
      pInBufferIv = (TUnsignedInt8*)(size_t)pxInputMessage->ivBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferIv, pIv, pxInputMessage->ivSize);
    }
    else pInBufferIv = pIv;
  }

  if (pxInputMessage->has_handle)
    session = (TBsdCipherSession)(size_t) pxInputMessage->handle;
  else session = NULL;

  bsdStatus = _CRPC(bsdSessionDecrypt) (
    session,
    pInBufferInput,
    pInBufferOutput,
    (TSize)                  pxInputMessage->inputSize,
    pInBufferIv,
    (TSize)                  pxInputMessage->ivSize );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput && pInBufferOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pInBufferOutput, pxInputMessage->inputSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)pxInputMessage->inputSize;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_r2rLegacyEncryptWithSecretKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_r2rLegacyEncryptWithSecretKey
(
  TMsgBuf_rpcHandler                       xRpcHandler,
  const TNhtbsd_R2rLegacyOperationInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg                   ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt8 * pInput          = NULL;
  TUnsignedInt8 * pOutput         = NULL;
  TUnsignedInt8 * pInBufferInput  = NULL;
  TUnsignedInt8 * pInBufferOutput = NULL;
  int             inputSize;

  inputSize = (int)pxInputMessage->inputSize;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (inputSize);

    if (pxInputMessage->has_outputBufferHandle)
      pInBufferOutput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pInBufferOutput = pOutput;
  }

  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, inputSize);
    }
    else pInBufferInput = pInput;
  }

  bsdStatus = _CRPC(bsdEncryptDataWithSecretContentKey) (
    (TBsdR2RAlgorithm) pxInputMessage->algo,
    pInBufferInput,
    pInBufferOutput,
    (TUnsignedInt32) inputSize );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput && pInBufferOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pInBufferOutput, inputSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)inputSize;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_r2rLegacyDecryptWithSecretKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_r2rLegacyDecryptWithSecretKey
(
  TMsgBuf_rpcHandler                       xRpcHandler,
  const TNhtbsd_R2rLegacyOperationInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg                   ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt8 * pInput = NULL;
  TUnsignedInt8 * pOutput = NULL;
  TUnsignedInt8 * pInBufferInput = NULL;
  TUnsignedInt8 * pInBufferOutput = NULL;
  int             inputSize;

  inputSize = (int)pxInputMessage->inputSize;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (inputSize);

    if (pxInputMessage->has_outputBufferHandle)
      pInBufferOutput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pInBufferOutput = pOutput;
  }

  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, inputSize);
    }
    else pInBufferInput = pInput;
  }

  bsdStatus = _CRPC(bsdDecryptDataWithSecretContentKey) (
    (TBsdR2RAlgorithm) pxInputMessage->algo,
    pInBufferInput,
    pInBufferOutput,
    (TUnsignedInt32) inputSize );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput && pInBufferOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pInBufferOutput, inputSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)inputSize;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtbsd_hc_doMonteCarloTest
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_doMonteCarloTest
(
  TMsgBuf_rpcHandler                        xRpcHandler,
  const TNhtbsd_R2rMonteCarloParamsInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg                    ** pxOutputMessage
)
{
  TBsdStatus                      bsdStatus;
  TNhtBsd_r2r_test_algoParams     testInputParams;
  TUnsignedInt8                 * pOutputData = NULL;

  nhtbsd_r2r_testAlgo_initParams (&testInputParams);

  if (pxInputMessage->has_sessionHandle) {testInputParams.cipherSession = (TBsdCipherSession)(size_t)pxInputMessage->sessionHandle; }
  else testInputParams.cipherSession = NULL;

  testInputParams.emi              = (TUnsignedInt16)pxInputMessage->emi;
  testInputParams.cryptoAlgorithm  = (TBsdR2RAlgorithm)pxInputMessage->cryptoAlgo;
  testInputParams.cryptoMode       = (TNhtBsdCryptoMode)pxInputMessage->cryptoMode;

  testInputParams.isMonteCarlo     = (TBoolean)pxInputMessage->isMonteCarlo;
  testInputParams.isLegacy         = (TBoolean)pxInputMessage->isLegacy;
  testInputParams.runNumber        = (TUnsignedInt32)pxInputMessage->runNumber;
  testInputParams.ivEmulate        = (TBoolean)pxInputMessage->hasIvEmulation;
  testInputParams.useDriverAlloc   = (TBoolean)pxInputMessage->useDriverAlloc;
  testInputParams.isForEncryption  = (TBoolean)pxInputMessage->isForEncryption;

  testInputParams.ivcSize = pxInputMessage->len_IV;
  if (pxInputMessage->IV.pData)
    testInputParams.pIvc    = (TUnsignedInt8*)pxInputMessage->IV.pData;
  else testInputParams.pIvc = NULL;

  testInputParams.dataSize    = pxInputMessage->len_dataIn;
  if (pxInputMessage->dataIn.pData)
    testInputParams.pInputData  = (TUnsignedInt8*)pxInputMessage->dataIn.pData;
  else testInputParams.pInputData = NULL;

  if (pxInputMessage->has_output)
  {
    pOutputData = (TUnsignedInt8*)MSGBUF_SYS_malloc(testInputParams.dataSize);
    if (pOutputData == NULL)
    {
      return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else pOutputData = NULL;


  bsdStatus = _CRPC(nhtbsd_r2r_monteCarlo_test_run) (&testInputParams, pOutputData);

  if (pOutputData)
  {
    (*pxOutputMessage)->byteArray.pData = (void*)pOutputData;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)testInputParams.dataSize;
  }

  (*pxOutputMessage)->retStatus = (int32_t)bsdStatus - (int32_t)BSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}



/* RPC method: rpc_nhtbsd_hc_rsaPublicEncrypt
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_rsaPublicEncrypt
(
  TMsgBuf_rpcHandler                     xRpcHandler,
  const TNhtbsd_RsaPublicEncryptInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg                 ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt8 * pOutput       = NULL;
  TUnsignedInt8 * pOutputBuffer = NULL;
  TUnsignedInt8 * pInput        = NULL;
  TUnsignedInt8 * pInputBuffer  = NULL;
  TUnsignedInt8 * pN            = NULL;
  TUnsignedInt8 * pNBuffer      = NULL;
  int             keySize;
  int             inputSize;

  keySize = (int)pxInputMessage->keySize;

  pN = (TUnsignedInt8*)pxInputMessage->n.pData;
  if (pN)
  {
    if (pxInputMessage->has_nHandle)
    {
      pNBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->nHandle;
      MSGBUF_SYS_memcpy (pNBuffer, pN, keySize);
    }
    else pNBuffer = pN;
  }

  inputSize = (int)pxInputMessage->inputSize;
  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInputBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->inputBufferHandle;
      MSGBUF_SYS_memcpy (pInputBuffer, pInput, inputSize);
    }
    else pInputBuffer = pInput;
  }

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (keySize);

    if (pxInputMessage->has_outputBufferHandle)
      pOutputBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pOutputBuffer = pOutput;
  }

  bsdStatus = _CRPC(bsdRsaPublicEncrypt) (
    (const  TUnsignedInt8*)pInput,
    (TSize) inputSize,
     pOutputBuffer,
     (TUnsignedInt32)       pxInputMessage->e,
     (const TUnsignedInt8*) pNBuffer,
     (TSize)                keySize,
     (TBsdRsaPadding)       pxInputMessage->padding );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pOutputBuffer, keySize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)keySize;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_rsaPublicDecrypt
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_rsaPublicDecrypt
(
  TMsgBuf_rpcHandler                      xRpcHandler,
  const TNhtbsd_RsaPublicDecryptInMsg   * pxInputMessage,
  TNhtbsd_BytesOutMsg                  ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;
  TUnsignedInt8 * pOutput       = NULL;
  TUnsignedInt8 * pOutputBuffer = NULL;
  TUnsignedInt8 * pInput        = NULL;
  TUnsignedInt8 * pInputBuffer  = NULL;
  TUnsignedInt8 * pN            = NULL;
  TUnsignedInt8 * pNBuffer      = NULL;
  TSize         * pOutputSize   = NULL;
  int             keySize;
  TSize           outputSize;

  keySize = (int)pxInputMessage->keySize;

  if (pxInputMessage->has_outputSize) pOutputSize = &outputSize;
  else pOutputSize = NULL;

  pInput = (TUnsignedInt8*)pxInputMessage->input.pData;
  if (pInput)
  {
    if (pxInputMessage->has_inputBufferHandle)
    {
      pInputBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->inputBufferHandle;
      MSGBUF_SYS_memcpy (pInputBuffer, pInput, keySize);
    }
    else pInputBuffer = pInput;
  }

  pN = (TUnsignedInt8*)pxInputMessage->n.pData;
  if (pN)
  {
    if (pxInputMessage->has_nHandle)
    {
      pNBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->nHandle;
      MSGBUF_SYS_memcpy (pNBuffer, pN, keySize);
    }
    else pNBuffer = pN;
  }

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (pxInputMessage->keySize);

    if (pxInputMessage->has_outputBufferHandle)
      pOutputBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->outputBufferHandle;
    else pOutputBuffer = pOutput;
  }

  bsdStatus = _CRPC(bsdRsaPublicDecrypt) (
    (const TUnsignedInt8*) pInputBuffer,
    pOutputBuffer,
    pOutputSize,
    (TUnsignedInt32)       pxInputMessage->e,
    (const TUnsignedInt8*) pNBuffer,
    (TSize)                keySize,
    (TBsdRsaPadding)       pxInputMessage->padding );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pOutputBuffer, keySize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    if (pOutputSize)
      (*pxOutputMessage)->byteArray.len = *pOutputSize;
    else (*pxOutputMessage)->byteArray.len = 0;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_sha256Init
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_sha256Init
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtbsd_OptOutput1InMsg  * pxInputMessage,
  TNhtbsd_HandleOutMsg          ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdHashContext   handle;
  TBsdHashContext * pHandle = NULL;

  if (pxInputMessage->has_output) pHandle = &handle;

  bsdStatus = _CRPC(bsdSha256Init) (pHandle);

  if (bsdStatus == BSD_NO_ERROR)
  {
    if (pHandle) hndmng_register (*pHandle, &_hndmng_hashSessionClose);
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)handle;
  }

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_sha256Update
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_sha256Update
(
  TMsgBuf_rpcHandler              xRpcHandler,
  const TNhtbsd_ShaUpdateInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg      ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdHashContext   context = NULL;
  TUnsignedInt8   * pInput = NULL;
  TUnsignedInt8   * pInBufferInput = NULL;

  pInput = (TUnsignedInt8*)pxInputMessage->chunk.pData;
  if (pInput)
  {
    if (pxInputMessage->has_chunkBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->chunkBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, pxInputMessage->chunkSize);
    }
    else pInBufferInput = pInput;
  }
  else pInBufferInput = NULL;

  if (pxInputMessage->has_handle)
    context = (TBsdHashContext)(size_t) pxInputMessage->handle;
  else context = NULL;

  bsdStatus = _CRPC(bsdSha256Update) (
    context,
    pInBufferInput,
    (TSize)                pxInputMessage->chunkSize );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_sha256Final
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_sha256Final
(
  TMsgBuf_rpcHandler                 xRpcHandler,
  const TNhtbsd_ShaTerminateInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg             ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TUnsignedInt8   * pOutput = NULL;
  TBsdHashContext   context = NULL;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (32);
    if (!pOutput) return RPC_STATUS_MALLOC_ERROR;
  }

  if (pxInputMessage->has_handle)
    context = (TBsdHashContext)(size_t) pxInputMessage->handle;
  else context = NULL;

  bsdStatus = _CRPC(bsdSha256Final) (
    context,
    pOutput );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput)
  {
    if (context) hndmng_unregister (context);
    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)32;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_hmacSha256Init
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_hmacSha256Init
(
  TMsgBuf_rpcHandler                xRpcHandler,
  const TNhtbsd_HmacShaInitInMsg  * pxInputMessage,
  TNhtbsd_HandleOutMsg           ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdHashContext   handle;
  TBsdHashContext * pHandle    = NULL;
  TUnsignedInt8   * pKey       = NULL;
  TUnsignedInt8   * pKeyBuffer = NULL;
  int               keySize;

  keySize = (int)pxInputMessage->keySize;

  if (pxInputMessage->has_output) pHandle = &handle;

  pKey = (TUnsignedInt8*)pxInputMessage->key.pData;
  if (pKey)
  {
    if (pxInputMessage->has_keyHandle)
    {
      pKeyBuffer = (TUnsignedInt8*)(size_t)pxInputMessage->keyHandle;
      MSGBUF_SYS_memcpy (pKeyBuffer, pKey, keySize);
    }
    else pKeyBuffer = pKey;
  }

  bsdStatus = _CRPC(bsdHmacSha256Init) (
    (const TUnsignedInt8*) pKeyBuffer,
    (TSize)                keySize,
    pHandle );

  if (bsdStatus == BSD_NO_ERROR)
  {
    if (pHandle) hndmng_register (*pHandle, &_hndmng_hashSessionClose);
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)handle;
  }

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_hmacSha256Update
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_hmacSha256Update
(
  TMsgBuf_rpcHandler              xRpcHandler,
  const TNhtbsd_ShaUpdateInMsg  * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg      ** pxOutputMessage
)
{
  TBsdStatus        bsdStatus;
  TBsdHashContext   context = NULL;
  TUnsignedInt8   * pInput = NULL;
  TUnsignedInt8   * pInBufferInput = NULL;

  pInput = (TUnsignedInt8*)pxInputMessage->chunk.pData;
  if (pInput)
  {
    if (pxInputMessage->has_chunkBufferHandle)
    {
      pInBufferInput = (TUnsignedInt8*)(size_t)pxInputMessage->chunkBufferHandle;
      MSGBUF_SYS_memcpy (pInBufferInput, pInput, pxInputMessage->chunkSize);
    }
    else pInBufferInput = pInput;
  }
  else pInBufferInput = NULL;

  if (pxInputMessage->has_handle)
    context = (TBsdHashContext)(size_t) pxInputMessage->handle;
  else context = NULL;

  bsdStatus = _CRPC(bsdHmacSha256Update) (
    context,
    pInBufferInput,
    (TSize) pxInputMessage->chunkSize );

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_hmacSha256Final
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_hmacSha256Final
(
  TMsgBuf_rpcHandler                 xRpcHandler,
  const TNhtbsd_ShaTerminateInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg             ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt8 * pOutput = NULL;
  TBsdHashContext context = NULL;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (32);
    if (!pOutput) return RPC_STATUS_MALLOC_ERROR;
  }

  if (pxInputMessage->has_handle)
    context = (TBsdHashContext)(size_t) pxInputMessage->handle;
  else context = NULL;

  bsdStatus = _CRPC(bsdHmacSha256Final) (
    context,
    pOutput );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput)
  {
    if (context) hndmng_unregister (context);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)32;
    pOutput = NULL;
  }

  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hc_generateRandomBytes
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_generateRandomBytes
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtbsd_RandomInMsg  * pxInputMessage,
  TNhtbsd_BytesOutMsg       ** pxOutputMessage
)
{
  TBsdStatus      bsdStatus;
  TUnsignedInt8 * pOutput         = NULL;
  TUnsignedInt8 * pInBufferOutput = NULL;
  int             randomSize;

  randomSize = (int)pxInputMessage->randomSize;

  if (pxInputMessage->has_output)
  {
    pOutput = (TUnsignedInt8 *)MSGBUF_SYS_malloc (pxInputMessage->randomSize);

    if (pxInputMessage->has_randomBufferHandle)
      pInBufferOutput = (TUnsignedInt8*)(size_t)pxInputMessage->randomBufferHandle;
    else pInBufferOutput = pOutput;
  }

  bsdStatus = _CRPC(bsdGenerateRandomBytes) (
    (TSize) randomSize,
    pInBufferOutput );

  if ((bsdStatus == BSD_NO_ERROR) && pOutput)
  {
    if (pxInputMessage->has_randomBufferHandle)
      MSGBUF_SYS_memcpy (pOutput, pInBufferOutput, randomSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pOutput;
    (*pxOutputMessage)->byteArray.len = (uint32_t)randomSize;
    pOutput = NULL;
  }
  if (pOutput) MSGBUF_SYS_free (pOutput);

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtbsd_hn_chipReset
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
TRpc_status rpc_nhtbsd_hn_chipReset
(
  TMsgBuf_rpcHandler        xRpcHandler,
  const TNhtbsd_EmptyMsg  * pxInputMessage,
  TNhtbsd_EmptyMsg       ** pxOutputMessage
)
{
  _CRPC(bsdChipReset) ();

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtbsd_hc_server_terminate
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtbsd_hc_server_terminate
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtbsd_EmptyMsg   * pxInputMessage,
  TNhtbsd_BsdStatusOutMsg ** pxOutputMessage
)
{
  TBsdStatus bsdStatus;

  bsdStatus = nhtBsdServerTerminate ();

  (*pxOutputMessage)->retStatus = (int32_t)(bsdStatus - (TBsdStatus)BSD_STATUS_OFFSET);
  return RPC_STATUS_NO_ERROR;
}
