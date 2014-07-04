/**
 * File: $Id:$
 *
 *  This file implements the CSD RPC server glue code.
 *  This file stands as the customization of the template generated
 *  by the msgbuf compiler associated to CSD API.
 *
 *  Copyright (c) 2012 Nagravision. All rights reserved.
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

#include "src/rpc_nhtcsd_api.h"
#include "nocs_nhtcsd.h"
#include "inc/nv_nhtcsd.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/hndmng.h"
#include "inc/TRACE_nhtcsd.h"
#include "inc/TRACE_p_nhtcsd.h"


#define DSC_TEST_RUN_MAGIC_NUMBER   (0x12345678)


typedef struct SRpcDscTestRunHandle
{
  volatile uint32_t                    magicNumber;
  TMsgBuf_rpcHandler                   rpcHandler;
  TNhtCsdDscTestRunHandle              dscHandle;
  int64_t                              ecmCallBackHandle;
  TNhtCsdDscCallBackPrivateParameters  privateData;
  volatile TCsdUnsignedInt8            lastTableId;

} TRpcDscTestRunHandle;



/****************************************************************************
 * Static function prototypes                                               *
 ****************************************************************************/

static TCsdStatus rpcEcmCallBackFunction (
        TNhtCsdDscTestRunHandle               xDscTestRunHandle,
        TNhtCsdDscCallBackPrivateParameters   xPrivateParameters,
        TCsdUnsignedInt8                      xEcmTableId,
  const TCsdUnsignedInt8                    * pxEcmContent,
        TCsdSize                              xEcmContentSize );


/* */
static int _hndmng_sysBufferClose
(
  void * pxHandle
)
{
  TNhtCsdSysBufferHandle sysBuffer = (TNhtCsdSysBufferHandle)pxHandle;
  nhtCsdDeallocateSysBuffer (sysBuffer);
  return 0;
}

/*****************************************************************************
 * RPC methods implementation                                                *
 ****************************************************************************/

/* RPC method: rpc_nhtcsd_hc_nht_initializeResourceUsage
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_initializeResourceUsage
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtcsd_EmptyMsg   * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg ** pxOutputMessage
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(nhtCsdInitialize) ();

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_terminateResourceUsage
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_terminateResourceUsage
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtcsd_EmptyMsg   * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg ** pxOutputMessage
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(nhtCsdTerminate) ();

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getNhtCsdApiVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getNhtCsdApiVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_VersionRevisionOutMsg ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdUnsignedInt32   version;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetNhtCsdApiVersion) (&version);
    (*pxOutputMessage)->versionRevision = (uint32_t)version;
  }
  else csdStatus = _CRPC(nhtCsdGetNhtCsdApiVersion) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getCsdApiVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getCsdApiVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_VersionRevisionOutMsg ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdUnsignedInt32   version;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetApiVersion) (&version);
    (*pxOutputMessage)->versionRevision = (uint32_t)version;
  }
  else csdStatus = csdGetApiVersion (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getNhtCsdSoftwareVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getNhtCsdSoftwareVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_StringOutMsg          ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsd20CharsString   swVersionName;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetSoftwareVersion) (swVersionName);
    (*pxOutputMessage)->info = (char*)MSGBUF_SYS_malloc (sizeof(TCsd20CharsString) + 1);

    if ((*pxOutputMessage)->info == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->info, &swVersionName[0], sizeof(TCsd20CharsString));
    (*pxOutputMessage)->info[sizeof(TCsd20CharsString)] = 0;
  }
  else csdStatus = _CRPC(nhtCsdGetSoftwareVersion) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getCsdSoftwareVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getCsdSoftwareVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_StringOutMsg          ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsd20CharsString   swVersionName;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetSoftwareVersion) (swVersionName);
    (*pxOutputMessage)->info = (char*)MSGBUF_SYS_malloc (sizeof(TCsd20CharsString) + 1);

    if ((*pxOutputMessage)->info == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->info, &swVersionName[0], sizeof(TCsd20CharsString));
    (*pxOutputMessage)->info[sizeof(TCsd20CharsString)] = 0;
  }
  else csdStatus = _CRPC(csdGetSoftwareVersion) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getCsdStatusOffsetValue
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getCsdStatusOffsetValue
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_NumberOutMsg          ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsdUnsignedInt32  statusOffset;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetCsdStatusOffsetValue) (&statusOffset);
    (*pxOutputMessage)->has_value = 1;
    (*pxOutputMessage)->value  = (uint32_t)statusOffset;
  }
  else csdStatus = _CRPC(nhtCsdGetCsdStatusOffsetValue) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getNocsCertificationVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getNocsCertificationVersion
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_VersionRevisionOutMsg ** pxOutputMessage
)
{
  TCsdStatus        csdStatus;
  TCsdUnsignedInt32 version;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetCertificationNOCSVersion) (&version);
    (*pxOutputMessage)->versionRevision = (uint32_t)version;
  }
  else csdStatus = _CRPC(nhtCsdGetCertificationNOCSVersion) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getChipManufacturer
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getChipManufacturer
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_StringOutMsg          ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsd20CharsString   manufacturerName;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetChipManufacturerName) (manufacturerName);
    (*pxOutputMessage)->info = (char*)MSGBUF_SYS_malloc (sizeof(TCsd20CharsString) + 1);

    if ((*pxOutputMessage)->info == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->info, &manufacturerName[0], sizeof(TCsd20CharsString));
    (*pxOutputMessage)->info[sizeof(TCsd20CharsString)] = 0;
  }
  else csdStatus = _CRPC(nhtCsdGetChipManufacturerName) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getChipName
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getChipName
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_StringOutMsg          ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsd20CharsString   chipName;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetChipName) (chipName);
    (*pxOutputMessage)->info = (char*)MSGBUF_SYS_malloc (sizeof(TCsd20CharsString) + 1);

    if ((*pxOutputMessage)->info == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->info, &chipName[0], sizeof(TCsd20CharsString));
    (*pxOutputMessage)->info[sizeof(TCsd20CharsString)] = 0;
  }
  else csdStatus = _CRPC(nhtCsdGetChipName) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getChipRevision
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getChipRevision
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_StringOutMsg          ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsd20CharsString   chipRevision;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetChipRevision) (chipRevision);
    (*pxOutputMessage)->info = (char*)MSGBUF_SYS_malloc (sizeof(TCsd20CharsString) + 1);

    if ((*pxOutputMessage)->info == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->info, &chipRevision[0], sizeof(TCsd20CharsString));
    (*pxOutputMessage)->info[sizeof(TCsd20CharsString)] = 0;
  }
  else csdStatus = _CRPC(csdGetChipRevision) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
    return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getChipExtension
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getChipExtension
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_StringOutMsg          ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsd20CharsString   chipExtension;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetChipExtension) (chipExtension);
    (*pxOutputMessage)->info = (char*)MSGBUF_SYS_malloc (sizeof(TCsd20CharsString) + 1);

    if ((*pxOutputMessage)->info == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->info, &chipExtension[0], sizeof(TCsd20CharsString));
    (*pxOutputMessage)->info[sizeof(TCsd20CharsString)] = 0;
  }
  else csdStatus = _CRPC(csdGetChipExtension) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getProtectingKeyNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getProtectingKeyNumber
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_NumberOutMsg          ** pxOutputMessage
)
{
  TCsdStatus        csdStatus;
  TCsdUnsignedInt32 protectingKeyNumber;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetCsdProtectingKeyNumber) (&protectingKeyNumber);
    (*pxOutputMessage)->value = (uint32_t)protectingKeyNumber;
    (*pxOutputMessage)->has_value = 1;
  }
  else csdStatus = _CRPC(nhtCsdGetCsdProtectingKeyNumber) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getNuid
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getNuid
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg           ** pxOutputMessage
)
{
  TCsdStatus       csdStatus;
  TCsd4BytesVector nuid;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetNuid) (nuid);
    (*pxOutputMessage)->byteArray.pData = (void*)MSGBUF_SYS_malloc (sizeof(TCsd4BytesVector));

    if ((*pxOutputMessage)->byteArray.pData == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->byteArray.pData, &nuid[0], sizeof(TCsd4BytesVector));
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd4BytesVector);
  }
  else csdStatus = _CRPC(csdGetNuid) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getNuid64
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getNuid64
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg           ** pxOutputMessage
)
{
  TCsdStatus       csdStatus;
  TCsd8BytesVector nuid;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetNuid64) (nuid);
    (*pxOutputMessage)->byteArray.pData = (void*)MSGBUF_SYS_malloc (sizeof(TCsd8BytesVector));

    if ((*pxOutputMessage)->byteArray.pData == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->byteArray.pData, &nuid[0], sizeof(TCsd8BytesVector));
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd8BytesVector);
  }
  else csdStatus = _CRPC(csdGetNuid64) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getBootModeNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getBootModeNumber
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_NumberOutMsg          ** pxOutputMessage
)
{
  TCsdStatus            csdStatus;
  TNhtCsdBootModeNumber bootModeNumber;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtCsdGetBootModeNumber) (&bootModeNumber);
    (*pxOutputMessage)->value = (uint32_t)bootModeNumber;
    (*pxOutputMessage)->has_value = 1;
  }
  else csdStatus = _CRPC(nhtCsdGetBootModeNumber) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getBootModeDescriptorSet
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getBootModeDescriptorSet
(
  TMsgBuf_rpcHandler                    xRpcHandler,
  const TNhtcsd_BootModeDescSetInMsg  * pxInputMessage,
  TNhtcsd_BootModeDescSetOutMsg      ** pxOutputMessage
)
{
  TCsdStatus                   csdStatus;
  TNhtCsdBootModeNumber        bootModeNumber;
  TNhtCsdBootModeNumber        bootModeResNumber;
  TNhtCsdBootModeNumber      * pBootModeResNumber;
  TNhtCsdBootModeDescriptor  * pBootModeDescSet;
  TNhtcsd_BootModeDescType  ** pBootModeDescRpcArray;
  TNhtCsdBootModeNumber        i, j;

  bootModeNumber = (TNhtCsdBootModeNumber)pxInputMessage->bootModeNumber;

  if (pxInputMessage->has_output1)
  {
    pBootModeDescSet = (TNhtCsdBootModeDescriptor*)MSGBUF_SYS_malloc(sizeof(TNhtCsdBootModeDescriptor) * bootModeNumber);
    if (pBootModeDescSet == NULL) return RPC_STATUS_MALLOC_ERROR;
  }
  else pBootModeDescSet = NULL;

  if (pxInputMessage->has_output2) pBootModeResNumber = &bootModeResNumber;
  else pBootModeResNumber = NULL;

  csdStatus = _CRPC(nhtCsdGetBootModeDescriptorSet) (
    bootModeNumber,
    pBootModeDescSet,
    pBootModeResNumber );


  if (pBootModeResNumber && pBootModeDescSet)
  {
    pBootModeDescRpcArray = (TNhtcsd_BootModeDescType**)MSGBUF_SYS_malloc(sizeof(TNhtcsd_BootModeDescType*) * bootModeResNumber);
    if (pBootModeDescRpcArray == NULL)
    {
      MSGBUF_SYS_free (pBootModeDescSet);
      return RPC_STATUS_MALLOC_ERROR;
    }

    for (i=0; i < bootModeResNumber; i++)
    {
      pBootModeDescRpcArray[i] = pAlloc_Nhtcsd_BootModeDescType();

      pBootModeDescRpcArray[i]->bootModeId = (uint32_t)pBootModeDescSet[i].bootModeId;
      pBootModeDescRpcArray[i]->description = (char*)MSGBUF_SYS_malloc(sizeof(TCsd20CharsString) + 1);

      if (pBootModeDescRpcArray[i]->description != NULL)
      {
        pBootModeDescRpcArray[i]->description = (char*)MSGBUF_SYS_malloc(sizeof(TCsd20CharsString)+1);
        MSGBUF_SYS_memcpy (pBootModeDescRpcArray[i]->description, pBootModeDescSet[i].bootMemoryName, sizeof(TCsd20CharsString));
        pBootModeDescRpcArray[i]->description[sizeof(TCsd20CharsString)] = 0;
        pBootModeDescRpcArray[i]->bootModeId = (uint32_t)pBootModeDescSet[i].bootModeId;
      }
      else
      {
        for (j=0; j<i; j++) dealloc_Nhtcsd_BootModeDescType (pBootModeDescRpcArray[j]);
        MSGBUF_SYS_free (pBootModeDescRpcArray);
        MSGBUF_SYS_free (pBootModeDescSet);
        return RPC_STATUS_MALLOC_ERROR;
      }
    }

    (*pxOutputMessage)->n_bootDesc = (uint32_t)bootModeResNumber;
    (*pxOutputMessage)->bootDesc = pBootModeDescRpcArray;
  }
  else (*pxOutputMessage)->n_bootDesc = 0;

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getBootModeDescriptor
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getBootModeDescriptor
(
  TMsgBuf_rpcHandler                 xRpcHandler,
  const TNhtcsd_BootModeDescInMsg  * pxInputMessage,
  TNhtcsd_BootModeDescOutMsg      ** pxOutputMessage
)
{
  TCsdStatus                  csdStatus;
  TCsdBootMode                bootModeId;
  TNhtCsdBootModeDescriptor   bootModeDesc;
  TNhtCsdBootModeDescriptor * pBootModeDesc = NULL;
  TNhtcsd_BootModeDescType  * pBootModeDescType = NULL;

  bootModeId = (TNhtCsdBootModeNumber)pxInputMessage->bootModeNumber;

  if (pxInputMessage->has_output) pBootModeDesc = &bootModeDesc;
  else pBootModeDesc = NULL;

  csdStatus = _CRPC(nhtCsdGetBootModeDescriptor) (bootModeId, pBootModeDesc);

  if (pBootModeDesc && (csdStatus == CSD_NO_ERROR))
  {
    pBootModeDescType = pAlloc_Nhtcsd_BootModeDescType();
    if (pBootModeDescType == NULL) return RPC_STATUS_MALLOC_ERROR;

    pBootModeDescType->description = (char*)MSGBUF_SYS_malloc(sizeof(TCsd20CharsString)+1);
    if (pBootModeDescType->description == NULL)
    {
      dealloc_Nhtcsd_BootModeDescType(pBootModeDescType);
      return RPC_STATUS_MALLOC_ERROR;
    }

    (*pxOutputMessage)->bootDesc = pBootModeDescType;
    MSGBUF_SYS_strncpy (pBootModeDescType->description, (char*)&bootModeDesc.bootMemoryName[0], sizeof(TCsd20CharsString));
    pBootModeDescType->description[sizeof(TCsd20CharsString)] = 0;
    pBootModeDescType->bootModeId = (uint32_t)bootModeDesc.bootModeId;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setBootMode
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setBootMode
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_BootModeIdInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg       ** pxOutputMessage
)
{
  TCsdStatus   csdStatus;
  TCsdBootMode bootModeId = (TCsdBootMode)pxInputMessage->bootModeId;

  csdStatus = _CRPC(csdSetBootMode) (bootModeId);
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getBootMode
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getBootMode
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BootModeIdOutMsg      ** pxOutputMessage
)
{
  TCsdStatus    csdStatus;
  TCsdBootMode  bootModeId;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetBootMode) (&bootModeId);
    (*pxOutputMessage)->has_bootModeId = 1;
    (*pxOutputMessage)->bootModeId = (uint32_t)bootModeId;
  }
  else csdStatus = _CRPC(csdGetBootMode) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_enableSCS
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_enableSCS
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtcsd_EmptyMsg   * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg ** pxOutputMessage
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdEnableScs) ();
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getSCSactivationFlag
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getSCSactivationFlag
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_ActivationFlagOutMsg  ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsdActivationFlag activationFlag;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetScsActivationFlag) (&activationFlag);
    (*pxOutputMessage)->has_flag = 1;
    (*pxOutputMessage)->flag = (uint32_t)activationFlag;
  }
  else csdStatus = _CRPC(csdGetScsActivationFlag) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_deactivateKeyLadder
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_deactivateKeyLadder
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtcsd_EmptyMsg   * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg ** pxOutputMessage
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdDeactivateKeyLadder) ();
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getKeyLadderDeactivationFlag
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getKeyLadderDeactivationFlag
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_ActivationFlagOutMsg  ** pxOutputMessage
)
{
  TCsdStatus csdStatus;
  TCsdActivationFlag activationFlag;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetKeyLadderDeactivationFlag) (&activationFlag);
    (*pxOutputMessage)->has_flag = 1;
    (*pxOutputMessage)->flag = (uint32_t)activationFlag;
  }
  else csdStatus = _CRPC(csdGetKeyLadderDeactivationFlag) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_csdSetScsTotalAreaSize
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_csdSetScsTotalAreaSize
(
  TMsgBuf_rpcHandler                         xRpcHandler,
  const TNhtcsd_ScsTotalAreaSizeOnlyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                 ** pxOutputMessage
)
{
  TCsdStatus           csdStatus;
  TCsdScsTotalAreaSize totalAreaSize;

  totalAreaSize = (TCsdScsTotalAreaSize)pxInputMessage->areaSize;
  csdStatus = _CRPC(csdSetScsTotalAreaSize) (totalAreaSize);
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_csdGetScsTotalAreaSize
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_csdGetScsTotalAreaSize
(
  TMsgBuf_rpcHandler                xRpcHandler,
  const TNhtcsd_OptOutput1InMsg   * pxInputMessage,
  TNhtcsd_ScsTotalAreaSizeOutMsg ** pxOutputMessage
)
{
  TCsdStatus           csdStatus;
  TCsdScsTotalAreaSize totalAreaSize;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetScsTotalAreaSize) (&totalAreaSize);
    (*pxOutputMessage)->has_areaSize = 1;
    (*pxOutputMessage)->areaSize = (uint32_t)totalAreaSize;
  }
  else csdStatus = _CRPC(csdGetScsTotalAreaSize) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getSCSExpectedPvBufferLen
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getSCSExpectedPvBufferLen
(
  TMsgBuf_rpcHandler                xRpcHandler,
  const TNhtcsd_GetScsPvLenInMsg  * pxInputMessage,
  TNhtcsd_SizeOutMsg             ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdScsPvId         scsPvId;
  TCsdUnsignedInt16   pvBufLen;
  TCsdUnsignedInt16 * pPvBufLen;

  scsPvId = (TCsdScsPvId)pxInputMessage->pvId;

  if (pxInputMessage->has_output) pPvBufLen = &pvBufLen;
  else pPvBufLen = NULL;

  csdStatus = _CRPC(nhtCsdGetScsExpectedPvValueSize) (scsPvId, pPvBufLen);

  if (pPvBufLen)
  {
    (*pxOutputMessage)->has_value = 1;
    (*pxOutputMessage)->value = (uint32_t)pvBufLen;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_csdSetSCSPv
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_csdSetSCSPv
(
  TMsgBuf_rpcHandler             xRpcHandler,
  const TNhtcsd_SetScsPvInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg     ** pxOutputMessage
)
{
  TCsdStatus                csdStatus;
  TCsdScsPvId               scsPvId;
  TCsdUnsignedInt16         pvBufLen = 0;
  TCsdUnsignedInt8 const  * pPvBuffer = NULL;

  scsPvId = (TCsdScsPvId)pxInputMessage->pvId;

  pvBufLen = (TCsdUnsignedInt16)pxInputMessage->len_pvValue;
  if (pxInputMessage->pvValue.pData)
    pPvBuffer = (TCsdUnsignedInt8 const*)pxInputMessage->pvValue.pData;

  csdStatus = _CRPC(nhtCsdSetScsPv) (scsPvId, pvBufLen, pPvBuffer);
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_csdGetSCSPv
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_csdGetSCSPv
(
  TMsgBuf_rpcHandler             xRpcHandler,
  const TNhtcsd_GetScsPvInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg         ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdScsPvId         scsPvId;
  TCsdUnsignedInt16   pvBufLen;
  TCsdUnsignedInt8  * pPvBuffer;

  scsPvId = (TCsdScsPvId)pxInputMessage->pvId;

  pvBufLen = (TCsdUnsignedInt16)pxInputMessage->len_output;

  if (pxInputMessage->has_output)
  {
    pPvBuffer = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(pvBufLen);
    if (pPvBuffer == NULL) return RPC_STATUS_MALLOC_ERROR;
  }
  else pPvBuffer = NULL;

  csdStatus = _CRPC(nhtCsdGetScsPv) (scsPvId, pvBufLen, pPvBuffer);

  if (pPvBuffer)
  {
    (*pxOutputMessage)->byteArray.len = (uint32_t)pvBufLen;
    (*pxOutputMessage)->byteArray.pData = (void*)pPvBuffer;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setStbCaSn
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setStbCaSn
(
  TMsgBuf_rpcHandler          xRpcHandler,
  const TNhtcsd_BytesInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg  ** pxOutputMessage
)
{
  TCsdStatus        csdStatus;
  TCsd4BytesVector  stbCasSn;

  if (pxInputMessage->input.pData)
  {
    if ((int)pxInputMessage->input.len != (int)sizeof(TCsd4BytesVector))
      return RPC_STATUS_ILLEGAL_PARAMETER;

    MSGBUF_SYS_memcpy (&stbCasSn[0], pxInputMessage->input.pData, pxInputMessage->input.len);
    csdStatus = _CRPC(csdSetStbCaSn) (stbCasSn);
  }
  else csdStatus = _CRPC(csdSetStbCaSn) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getStbCaSn
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getStbCaSn
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg           ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsd4BytesVector   stbCaSn;
  void             * pRpcStbCaSn;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetStbCaSn) (stbCaSn);
    pRpcStbCaSn = (void*)MSGBUF_SYS_malloc(sizeof(TCsd4BytesVector));

    if (pRpcStbCaSn == NULL) return RPC_STATUS_MALLOC_ERROR;
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd4BytesVector);
    (*pxOutputMessage)->byteArray.pData = (void*)pRpcStbCaSn;
    MSGBUF_SYS_memcpy (pRpcStbCaSn, &stbCaSn[0], sizeof(TCsd4BytesVector));
  }
  else csdStatus = _CRPC(csdGetStbCaSn) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setMarketSegmentId
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setMarketSegmentId
(
  TMsgBuf_rpcHandler          xRpcHandler,
  const TNhtcsd_BytesInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg  ** pxOutputMessage
)
{
  TCsdStatus       csdStatus;
  TCsd4BytesVector segmentId;

  if (pxInputMessage->input.pData)
  {
    if ((int)pxInputMessage->input.len != (int)sizeof(TCsd4BytesVector))
      return RPC_STATUS_ILLEGAL_PARAMETER;

    MSGBUF_SYS_memcpy (&segmentId[0], pxInputMessage->input.pData, pxInputMessage->input.len);
    csdStatus = _CRPC(csdSetMarketSegmentId) (segmentId);
  }
  else csdStatus = _CRPC(csdSetMarketSegmentId) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getMarketSegmentId
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getMarketSegmentId
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg           ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsd4BytesVector   segmentId;
  void             * pRpcSegmentId;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetMarketSegmentId) (segmentId);
    pRpcSegmentId = (void*)MSGBUF_SYS_malloc(sizeof(TCsd4BytesVector));

    if (pRpcSegmentId == NULL) return RPC_STATUS_MALLOC_ERROR;

    (*pxOutputMessage)->byteArray.pData = pRpcSegmentId;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)sizeof(TCsd4BytesVector);
    MSGBUF_SYS_memcpy (pRpcSegmentId, &segmentId[0], sizeof (TCsd4BytesVector));
  }
  else csdStatus = _CRPC(csdGetMarketSegmentId) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setRamUnscrambledStorageSize
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setRamUnscrambledStorageSize
(
  TMsgBuf_rpcHandler             xRpcHandler,
  const TNhtcsd_VarBytesInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg     ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdUnsignedInt8  * pStorageSizeBuffer = NULL;
  TCsdUnsignedInt16   storageSizeBufferSize = 0;

  storageSizeBufferSize = (TCsdUnsignedInt16)pxInputMessage->len_input;
  if (pxInputMessage->input.pData)
    pStorageSizeBuffer = (TCsdUnsignedInt8*)pxInputMessage->input.pData;

  csdStatus = _CRPC(csdSetRamUnscrambledStorageSize) (pStorageSizeBuffer, storageSizeBufferSize);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_getRamUnscrambledStorageSizeBufferLen
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_getRamUnscrambledStorageSizeBufferLen
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_SizeOutMsg            ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsdUnsignedInt16  storageBufferSize;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(nhtcsdGetRamUnscrambledStorageSizeBufferLength) (&storageBufferSize);
    (*pxOutputMessage)->has_value = 1;
    (*pxOutputMessage)->value = (uint32_t)storageBufferSize;
  }
  else csdStatus = _CRPC(nhtcsdGetRamUnscrambledStorageSizeBufferLength) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getRamUnscrambleStorageSize
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getRamUnscrambleStorageSize
(
  TMsgBuf_rpcHandler            xRpcHandler,
  const TNhtcsd_GetSizeInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg        ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsdUnsignedInt8 * pBuffer = NULL;
  TCsdUnsignedInt16  bufferSize;

  bufferSize = (TCsdUnsignedInt16)pxInputMessage->value;

  if (pxInputMessage->has_output)
  {
    pBuffer = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(bufferSize);
    if (pBuffer == NULL) return RPC_STATUS_MALLOC_ERROR;
  }

  csdStatus = _CRPC(csdGetRamUnscrambledStorageSize) (pBuffer, bufferSize);

  if (pBuffer)
  {
    (*pxOutputMessage)->byteArray.pData = (void*)pBuffer;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)bufferSize;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getNuidCheckNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getNuidCheckNumber
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg           ** pxOutputMessage
)
{
  TCsdStatus       csdStatus;
  TCsd4BytesVector checkNumber;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetNUIDCheckNumber) (checkNumber);
    (*pxOutputMessage)->byteArray.pData = (void*)MSGBUF_SYS_malloc(sizeof(TCsd4BytesVector));

    if (((*pxOutputMessage)->byteArray.pData) == NULL) return RPC_STATUS_MALLOC_ERROR;
    MSGBUF_SYS_memcpy ((*pxOutputMessage)->byteArray.pData, &checkNumber[0], sizeof(TCsd4BytesVector));
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd4BytesVector);
  }
  else csdStatus = _CRPC(csdGetNUIDCheckNumber) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getCSDCDCheckNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getCSDCDCheckNumber
(
  TMsgBuf_rpcHandler                     xRpcHandler,
  const TNhtcsd_CheckNumberBytesInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                 ** pxOutputMessage
)
{
  TCsdStatus       csdStatus;
  TCsdUnsignedInt8 cscData[16];
  TCsd4BytesVector checkNumber;

  if (pxInputMessage->input.pData)
  {
    if ((int)pxInputMessage->input.len != 16)
      return RPC_STATUS_ILLEGAL_PARAMETER;
    MSGBUF_SYS_memcpy (&cscData[0], pxInputMessage->input.pData, 16);

    if (pxInputMessage->has_output)
      csdStatus = _CRPC(csdGetCSCDCheckNumber) (cscData, checkNumber);
    else csdStatus = _CRPC(csdGetCSCDCheckNumber) (cscData, NULL);
  }
  else
  {
    if (pxInputMessage->has_output)
      csdStatus = _CRPC(csdGetCSCDCheckNumber) (NULL, checkNumber);
    else csdStatus = _CRPC(csdGetCSCDCheckNumber) (NULL, NULL);
  }

  if (pxInputMessage->has_output)
  {
    (*pxOutputMessage)->byteArray.pData = (void*)MSGBUF_SYS_malloc(sizeof(TCsd4BytesVector));
    if (((*pxOutputMessage)->byteArray.pData) == NULL) return RPC_STATUS_MALLOC_ERROR;

    MSGBUF_SYS_memcpy ((*pxOutputMessage)->byteArray.pData, &checkNumber[0], sizeof(TCsd4BytesVector));
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd4BytesVector);
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getSTBCASNCheckNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getSTBCASNCheckNumber
(
  TMsgBuf_rpcHandler                     xRpcHandler,
  const TNhtcsd_CheckNumberBytesInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                 ** pxOutputMessage
)
{
  TCsdStatus       csdStatus;
  TCsdUnsignedInt8 caSn[4];
  TCsd4BytesVector checkNumber;

  if (pxInputMessage->input.pData)
  {
    if ((int)pxInputMessage->input.len != 4)
      return RPC_STATUS_ILLEGAL_PARAMETER;

    MSGBUF_SYS_memcpy (&caSn[0], pxInputMessage->input.pData, 4);
    if (pxInputMessage->has_output)
      csdStatus = _CRPC(csdGetSTBCASNCheckNumber) (caSn, checkNumber);
    else csdStatus = _CRPC(csdGetSTBCASNCheckNumber) (caSn, NULL);
  }
  else
  {
    if (pxInputMessage->has_output)
      csdStatus = _CRPC(csdGetSTBCASNCheckNumber) (NULL, checkNumber);
    else csdStatus = _CRPC(csdGetSTBCASNCheckNumber) (NULL, NULL);
  }

  if (pxInputMessage->has_output)
  {
    (*pxOutputMessage)->byteArray.pData = (void*)MSGBUF_SYS_malloc(sizeof(TCsd4BytesVector));
    if (((*pxOutputMessage)->byteArray.pData) == NULL) return RPC_STATUS_MALLOC_ERROR;

    MSGBUF_SYS_memcpy ((*pxOutputMessage)->byteArray.pData, &checkNumber[0], sizeof(TCsd4BytesVector));
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd4BytesVector);
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getDataIntegrityCheckNumber
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getDataIntegrityCheckNumber
(
  TMsgBuf_rpcHandler                     xRpcHandler,
  const TNhtcsd_CheckNumberBytesInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                 ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdUnsignedInt8  * pData = NULL;
  TCsdSize            dataSize;
  TCsd4BytesVector    checkNumber;

  dataSize = pxInputMessage->len_input;
  if (pxInputMessage->input.pData)
  {
    pData = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    if (pData == NULL) return RPC_STATUS_MALLOC_ERROR;

    MSGBUF_SYS_memcpy (pData, pxInputMessage->input.pData, (int)dataSize);
  }

  if (pxInputMessage->has_output)
    csdStatus = _CRPC(csdGetDataIntegrityCheckNumber) (pData, dataSize, checkNumber);
  else csdStatus = _CRPC(csdGetDataIntegrityCheckNumber) (pData, dataSize, NULL);

  if (pxInputMessage->has_output)
  {
    (*pxOutputMessage)->byteArray.pData = (void*)MSGBUF_SYS_malloc(sizeof(TCsd4BytesVector));
    if (((*pxOutputMessage)->byteArray.pData) == NULL) return RPC_STATUS_MALLOC_ERROR;

    MSGBUF_SYS_memcpy ((*pxOutputMessage)->byteArray.pData, &checkNumber[0], sizeof(TCsd4BytesVector));
    (*pxOutputMessage)->byteArray.len = (uint32_t)sizeof(TCsd4BytesVector);
  }

  if (pData) MSGBUF_SYS_free (pData);
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_enableRamScrambling
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_enableRamScrambling
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtcsd_EmptyMsg   * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg ** pxOutputMessage
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdEnableRamScrambling) ();
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getScramblingActivationFlag
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getScramblingActivationFlag
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_ActivationFlagOutMsg  ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdActivationFlag  activationFlag;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetScramblingActivationFlag) (&activationFlag);
   (*pxOutputMessage)->has_flag = 1;
   (*pxOutputMessage)->flag = (uint32_t)activationFlag;
  }
  else csdStatus = _CRPC(csdGetScramblingActivationFlag) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_enableFlashProtection
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_enableFlashProtection
(
  TMsgBuf_rpcHandler         xRpcHandler,
  const TNhtcsd_EmptyMsg   * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg ** pxOutputMessage
)
{
  TCsdStatus csdStatus;

  csdStatus = _CRPC(csdEnableFlashProtection) ();
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getFlashProtectionActivationFlag
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getFlashProtectionActivationFlag
(
  TMsgBuf_rpcHandler                xRpcHandler,
  const TNhtcsd_OptOutput1InMsg   * pxInputMessage,
  TNhtcsd_ActivationFlagOutMsg   ** pxOutputMessage
)
{
  TCsdStatus          csdStatus;
  TCsdActivationFlag  activationFlag;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetFlashProtectionActivationFlag) (&activationFlag);
    (*pxOutputMessage)->has_flag = 1;
    (*pxOutputMessage)->flag = (uint32_t)activationFlag;
  }
  else csdStatus = _CRPC(csdGetFlashProtectionActivationFlag) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_selectDebugInterfaceProtectionLevel
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_selectDebugInterfaceProtectionLevel
(
  TMsgBuf_rpcHandler                               xRpcHandler,
  const TNhtcsd_CsdDebugInterfaceAccesModeInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                       ** pxOutputMessage
)
{
  TCsdStatus                    csdStatus;
  TCsdDebugInterfaceAccessMode  debugAccessMode;

  debugAccessMode = (TCsdDebugInterfaceAccessMode)pxInputMessage->mode;
  csdStatus = _CRPC(csdSelectDebugInterfaceProtectionLevel) (debugAccessMode);
  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_getDebugInterfaceProtectionLevel
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getDebugInterfaceProtectionLevel
(
  TMsgBuf_rpcHandler                          xRpcHandler,
  const TNhtcsd_OptOutput1InMsg             * pxInputMessage,
  TNhtcsd_CsdDebugInterfaceAccesModeOutMsg ** pxOutputMessage
)
{
  TCsdStatus                    csdStatus;
  TCsdDebugInterfaceAccessMode  debugAccessMode;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetDebugInterfaceProtectionLevel) (&debugAccessMode);
    (*pxOutputMessage)->has_mode = 1;
    (*pxOutputMessage)->mode = (uint32_t)debugAccessMode;
  }
  else csdStatus = _CRPC(csdGetDebugInterfaceProtectionLevel) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_allocateDriverBuffer
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_allocateDriverBuffer
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_SizeInMsg        * pxInputMessage,
  TNhtcsd_CsdBufferHandleOutMsg ** pxOutputMessage
)
{
  TCsdSize                bufferSize;
  TNhtCsdSysBufferHandle  bufferHandle;

  bufferSize = (TCsdSize)pxInputMessage->value;

  bufferHandle = _CRPC(nhtCsdAllocateSysBuffer) (bufferSize);
  if (bufferHandle)
  {
    hndmng_register (bufferHandle, &_hndmng_sysBufferClose);
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)bufferHandle;
  }

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_deallocateDriverBuffer
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_deallocateDriverBuffer
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg   ** pxOutputMessage
)
{
  TNhtCsdSysBufferHandle  bufferHandle;
  TCsdStatus              csdStatus;

  bufferHandle = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->handle;

  if (pxInputMessage->has_handle)
  {
    csdStatus = _CRPC(nhtCsdDeallocateSysBuffer) (bufferHandle);
    hndmng_unregister ((void*)(size_t)pxInputMessage->handle);
  }
  else csdStatus = _CRPC(nhtCsdDeallocateSysBuffer) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_nht_openR2RSessionHandle
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_openR2RSessionHandle
(
  TMsgBuf_rpcHandler                xRpcHandler,
  const TNhtcsd_OptOutput1InMsg   * pxInputMessage,
  TNhtcsd_CsdHandleOutMsg        ** pxOutputMessage
)
{
  TCsdStatus                csdStatus;
  TNhtCsdR2RSessionHandle   r2RKeySessionHandle;
  TNhtCsdR2RSessionHandle * pR2RKeySessionHandle;

  if (pxInputMessage->has_output) pR2RKeySessionHandle = &r2RKeySessionHandle;
  else pR2RKeySessionHandle = NULL;

  csdStatus = nhtCsdOpenR2RSession (pR2RKeySessionHandle);

  if (pxInputMessage->has_output)
  {
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)r2RKeySessionHandle;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_closeR2RSessionHandle
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_closeR2RSessionHandle
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg   ** pxOutputMessage
)
{
  TCsdStatus               csdStatus;
  TNhtCsdR2RSessionHandle  r2RKeySessionHandle = NULL;

  if (pxInputMessage->has_handle)
    r2RKeySessionHandle = (TNhtCsdR2RSessionHandle)(size_t)pxInputMessage->handle;

  csdStatus = nhtCsdCloseR2RSession (r2RKeySessionHandle);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_encryptDataWithClearTextHostKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_encryptDataWithClearTextHostKey
(
  TMsgBuf_rpcHandler                                  xRpcHandler,
  const TNhtcsd_R2rCipherWithClearHostTextKeyInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                              ** pxOutputMessage
)
{
  TCsdStatus                   csdStatus;
  TCsdR2RAlgorithm             algo;
  TCsdR2RCryptoOperationMode   mode;
  TCsdUnsignedInt8           * pClearTextHostKey = NULL;
  TCsdSize                     clearTextHostKeySize;
  TCsdUnsignedInt8           * pIv = NULL;
  TCsdSize                     ivSize;
  TCsdBoolean                  refreshIv;
  TNhtCsdR2RSessionHandle      sessionHandle = NULL;
  TCsdUnsignedInt8           * pDataIn = NULL;
  TCsdUnsignedInt8           * pDataOut = NULL;
  TCsdUnsignedInt8           * pDataOutTmpBuffer = NULL;
  TCsdSize                     dataSize;
  TNhtCsdSysBufferHandle       inputSysBuffer   = NULL;
  TNhtCsdSysBufferHandle       outputSysBuffer  = NULL;

  algo                 = (TCsdR2RAlgorithm)pxInputMessage->algo;
  mode                 = (TCsdR2RCryptoOperationMode)pxInputMessage->mode;
  pClearTextHostKey    = (TCsdUnsignedInt8*)pxInputMessage->key.pData;
  clearTextHostKeySize = (TCsdSize)pxInputMessage->len_key;
  pIv                  = (TCsdUnsignedInt8*)pxInputMessage->IV.pData;
  ivSize               = (TCsdSize)pxInputMessage->len_IV;
  refreshIv            = (TCsdBoolean)pxInputMessage->refreshIV;
  dataSize             = (TCsdSize)pxInputMessage->len_inputData;

  if (pxInputMessage->has_sessionHandle)
    sessionHandle  = (TNhtCsdR2RSessionHandle)(size_t)pxInputMessage->sessionHandle;

  if (pxInputMessage->has_inputBufferHandle)
  {
    inputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->inputBufferHandle;
    if (pxInputMessage->inputData.pData)
    {
      pDataIn = (TCsdUnsignedInt8*)inputSysBuffer;
      MSGBUF_SYS_memcpy (pDataIn, pxInputMessage->inputData.pData, dataSize);
    }
    else pDataIn = NULL;
  }
  else pDataIn = (TCsdUnsignedInt8*)pxInputMessage->inputData.pData;

  if (pxInputMessage->has_output)
  {
    pDataOutTmpBuffer = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    if (pDataOutTmpBuffer == NULL) return RPC_STATUS_MALLOC_ERROR;
  }

  if (pxInputMessage->has_outputBufferHandle)
  {
    outputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->outputBufferHandle;
    pDataOut = (TCsdUnsignedInt8*)outputSysBuffer;
  }
  else pDataOut = pDataOutTmpBuffer;

  csdStatus = nhtCsdEncryptDataWithClearTextHostKey (
    algo,
    mode,
    pClearTextHostKey,
    clearTextHostKeySize,
    pIv,
    ivSize,
    refreshIv,
    sessionHandle,
    pDataIn,
    pDataOut,
    dataSize );

  if (pDataOutTmpBuffer && pDataOut && pDataOutTmpBuffer)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pDataOutTmpBuffer, pDataOut, dataSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pDataOutTmpBuffer;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)dataSize;
    pDataOutTmpBuffer = NULL;
  }

  if (pDataOutTmpBuffer) MSGBUF_SYS_free (pDataOutTmpBuffer);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_decryptDataWithClearTextHostKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_decryptDataWithClearTextHostKey
(
  TMsgBuf_rpcHandler                                  xRpcHandler,
  const TNhtcsd_R2rCipherWithClearHostTextKeyInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                              ** pxOutputMessage
)
{
  TCsdStatus                   csdStatus;
  TCsdR2RAlgorithm             algo;
  TCsdR2RCryptoOperationMode   mode;
  TCsdUnsignedInt8           * pClearTextHostKey = NULL;
  TCsdSize                     clearTextHostKeySize;
  TCsdUnsignedInt8           * pIv = NULL;
  TCsdSize                     ivSize;
  TCsdBoolean                  refreshIv;
  TNhtCsdR2RSessionHandle      sessionHandle = NULL;
  TCsdUnsignedInt8           * pDataIn = NULL;
  TCsdUnsignedInt8           * pDataOut = NULL;
  TCsdUnsignedInt8           * pDataOutTmpBuffer = NULL;
  TCsdSize                     dataSize;
  TNhtCsdSysBufferHandle       inputSysBuffer   = NULL;
  TNhtCsdSysBufferHandle       outputSysBuffer  = NULL;

  algo                 = (TCsdR2RAlgorithm)pxInputMessage->algo;
  mode                 = (TCsdR2RCryptoOperationMode)pxInputMessage->mode;
  pClearTextHostKey    = (TCsdUnsignedInt8*)pxInputMessage->key.pData;
  clearTextHostKeySize = (TCsdSize)pxInputMessage->len_key;
  pIv                  = (TCsdUnsignedInt8*)pxInputMessage->IV.pData;
  ivSize               = (TCsdSize)pxInputMessage->len_IV;
  refreshIv            = (TCsdBoolean)pxInputMessage->refreshIV;
  dataSize             = (TCsdSize)pxInputMessage->len_inputData;

  if (pxInputMessage->has_sessionHandle)
    sessionHandle = (TNhtCsdR2RSessionHandle)(size_t)pxInputMessage->sessionHandle;

  if (pxInputMessage->has_inputBufferHandle)
  {
    inputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->inputBufferHandle;
    if (pxInputMessage->inputData.pData)
    {
      pDataIn = (TCsdUnsignedInt8*)inputSysBuffer;
      MSGBUF_SYS_memcpy (pDataIn, pxInputMessage->inputData.pData, dataSize);
    }
    else pDataIn = NULL;
  }
  else pDataIn = (TCsdUnsignedInt8*)(size_t)pxInputMessage->inputData.pData;

  if (pxInputMessage->has_output)
  {
    pDataOutTmpBuffer = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    if (pDataOutTmpBuffer == NULL) return RPC_STATUS_MALLOC_ERROR;
  }

  if (pxInputMessage->has_outputBufferHandle)
  {
    outputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->outputBufferHandle;
    pDataOut = (TCsdUnsignedInt8*)outputSysBuffer;
  }
  else pDataOut = pDataOutTmpBuffer;

  csdStatus = nhtCsdDecryptDataWithClearTextHostKey (
    algo,
    mode,
    pClearTextHostKey,
    clearTextHostKeySize,
    pIv,
    ivSize,
    refreshIv,
    sessionHandle,
    pDataIn,
    pDataOut,
    dataSize );

  if (pDataOut && pDataOutTmpBuffer && pxInputMessage->has_output)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pDataOutTmpBuffer, pDataOut, dataSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pDataOutTmpBuffer;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)dataSize;
    pDataOutTmpBuffer = NULL;
  }

  if (pDataOutTmpBuffer) MSGBUF_SYS_free (pDataOutTmpBuffer);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_encryptDataWithSecretContentKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_encryptDataWithSecretContentKey
(
  TMsgBuf_rpcHandler                                  xRpcHandler,
  const TNhtcsd_R2rCipherWithSecretContentKeyInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                              ** pxOutputMessage
)
{
  TCsdStatus                      csdStatus;
  TCsdR2RAlgorithm                algo;
  TCsdR2RCryptoOperationMode      mode;
  TCsdUnsignedInt8              * pContentKey = NULL;
  TCsdSize                        contentKeySize;
  TCsdUnsignedInt8              * pIv = NULL;
  TCsdSize                        ivSize;
  TCsdBoolean                     refreshIv;
  TNhtCsdR2RSessionHandle         sessionHandle = NULL;
  TCsdUnsignedInt8              * pDataIn = NULL;
  TCsdUnsignedInt8              * pDataOut = NULL;
  TCsdSize                        dataSize;
  TCsdUnsignedInt32               protectingKeyNumber;
  TNhtCsdSysBufferHandle          inputSysBuffer   = NULL;
  TNhtCsdSysBufferHandle          outputSysBuffer  = NULL;
  TCsdUnsignedInt8              * pDataOutTmpBuffer = NULL;
  TNhtProtectingKey               protectingKeys[CSD_R2R_NB_OF_PROTECTING_KEYS];
  TNhtProtectingKey             * pProtectingKeys = NULL;
  TCsdUnsignedInt32               i;

  protectingKeyNumber = (TCsdUnsignedInt32)pxInputMessage->num_cipheredProtKeys;
  if (protectingKeyNumber != CSD_R2R_NB_OF_PROTECTING_KEYS)
    return RPC_STATUS_ILLEGAL_PARAMETER;

  if (pxInputMessage->cipheredProtKeys)
  {
    for (i=0; i < protectingKeyNumber; i++)
    {
      if ((int)pxInputMessage->cipheredProtKeys[i].len != 16)
        return RPC_STATUS_ILLEGAL_PARAMETER;
    }
  }

  algo                 = (TCsdR2RAlgorithm)pxInputMessage->algo;
  mode                 = (TCsdR2RCryptoOperationMode)pxInputMessage->mode;
  pIv                  = (TCsdUnsignedInt8*)pxInputMessage->IV.pData;
  ivSize               = (TCsdSize)pxInputMessage->len_IV;
  refreshIv            = (TCsdBoolean)pxInputMessage->refreshIV;
  dataSize             = (TCsdSize)pxInputMessage->len_inputData;
  pContentKey          = (TCsdUnsignedInt8*)pxInputMessage->cipheredContentKey.pData;
  contentKeySize       = (TCsdSize)pxInputMessage->len_cipheredContentKey;

  if (pxInputMessage->has_sessionHandle)
    sessionHandle = (TNhtCsdR2RSessionHandle)(size_t)pxInputMessage->sessionHandle;
  if (pxInputMessage->cipheredProtKeys)
  {
    pProtectingKeys = &protectingKeys[0];
    for (i=0; i < protectingKeyNumber; i++)
    {
      MSGBUF_SYS_memcpy (
        &protectingKeys[i][0],
        pxInputMessage->cipheredProtKeys[i].pData,
        pxInputMessage->cipheredProtKeys[i].len );
    }
  }

  if (pxInputMessage->has_inputBufferHandle)
  {
    inputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->inputBufferHandle;
    if (pxInputMessage->inputData.pData)
    {
      pDataIn = (TCsdUnsignedInt8*)inputSysBuffer;
      MSGBUF_SYS_memcpy (pDataIn, pxInputMessage->inputData.pData, dataSize);
    }
    else pDataIn = NULL;
  }
  else pDataIn = (TCsdUnsignedInt8*)pxInputMessage->inputData.pData;

  if (pxInputMessage->has_output)
  {
    pDataOutTmpBuffer = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    if (pDataOutTmpBuffer == NULL) return RPC_STATUS_MALLOC_ERROR;
  }

  if (pxInputMessage->has_outputBufferHandle)
  {
    outputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->outputBufferHandle;
    pDataOut = (TCsdUnsignedInt8*)outputSysBuffer;
  }
  else pDataOut = pDataOutTmpBuffer;

  csdStatus = nhtCsdEncryptDataWithSecretContentKey (
    algo,
    mode,
    protectingKeyNumber,
    (TNhtProtectingKey const *)pProtectingKeys,
    pContentKey,
    contentKeySize,
    pIv,
    ivSize,
    refreshIv,
    sessionHandle,
    pDataIn,
    pDataOut,
    dataSize );

  if (pDataOut && pDataOutTmpBuffer && pxInputMessage->has_output)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pDataOutTmpBuffer, pDataOut, dataSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pDataOutTmpBuffer;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)dataSize;
    pDataOutTmpBuffer = NULL;
  }

  if (pDataOutTmpBuffer) MSGBUF_SYS_free (pDataOutTmpBuffer);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_decryptDataWithSecretContentKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_decryptDataWithSecretContentKey
(
  TMsgBuf_rpcHandler                                  xRpcHandler,
  const TNhtcsd_R2rCipherWithSecretContentKeyInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                              ** pxOutputMessage
)
{
  TCsdStatus                      csdStatus;
  TCsdR2RAlgorithm                algo;
  TCsdR2RCryptoOperationMode      mode;
  TCsdUnsignedInt8              * pContentKey = NULL;
  TCsdSize                        contentKeySize;
  TCsdUnsignedInt8              * pIv = NULL;
  TCsdSize                        ivSize;
  TCsdBoolean                     refreshIv;
  TNhtCsdR2RSessionHandle         sessionHandle = NULL;
  TCsdUnsignedInt8              * pDataIn = NULL;
  TCsdUnsignedInt8              * pDataOut = NULL;
  TCsdSize                        dataSize;
  TCsdUnsignedInt32               protectingKeyNumber;
  TNhtCsdSysBufferHandle          inputSysBuffer   = NULL;
  TNhtCsdSysBufferHandle          outputSysBuffer  = NULL;
  TCsdUnsignedInt8              * pDataOutTmpBuffer = NULL;
  TNhtProtectingKey               protectingKeys[CSD_R2R_NB_OF_PROTECTING_KEYS];
  TNhtProtectingKey             * pProtectingKeys = NULL;
  TCsdUnsignedInt32               i;

  protectingKeyNumber = (TCsdUnsignedInt32)pxInputMessage->num_cipheredProtKeys;
  if (protectingKeyNumber != CSD_R2R_NB_OF_PROTECTING_KEYS)
    return RPC_STATUS_ILLEGAL_PARAMETER;

  if (pxInputMessage->cipheredProtKeys)
  {
    for (i=0; i < protectingKeyNumber; i++)
    {
      if ((int)pxInputMessage->cipheredProtKeys[i].len != sizeof(TNhtProtectingKey))
        return RPC_STATUS_ILLEGAL_PARAMETER;
    }
  }

  algo                 = (TCsdR2RAlgorithm)pxInputMessage->algo;
  mode                 = (TCsdR2RCryptoOperationMode)pxInputMessage->mode;
  pIv                  = (TCsdUnsignedInt8*)pxInputMessage->IV.pData;
  ivSize               = (TCsdSize)pxInputMessage->len_IV;
  refreshIv            = (TCsdBoolean)pxInputMessage->refreshIV;
  dataSize             = (TCsdSize)pxInputMessage->len_inputData;
  pContentKey          = (TCsdUnsignedInt8*)pxInputMessage->cipheredContentKey.pData;
  contentKeySize       = (TCsdSize)pxInputMessage->len_cipheredContentKey;

  if (pxInputMessage->has_sessionHandle)
    sessionHandle = (TNhtCsdR2RSessionHandle)(size_t)pxInputMessage->sessionHandle;

  if (pxInputMessage->cipheredProtKeys)
  {
    pProtectingKeys = &protectingKeys[0];
    for (i=0; i < protectingKeyNumber; i++)
    {
      MSGBUF_SYS_memcpy (
        &protectingKeys[i][0],
        pxInputMessage->cipheredProtKeys[i].pData,
        sizeof(TNhtProtectingKey) );
    }
  }

  if (pxInputMessage->has_inputBufferHandle)
  {
    inputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->inputBufferHandle;
    if (pxInputMessage->inputData.pData)
    {
      pDataIn = (TCsdUnsignedInt8*)inputSysBuffer;
      MSGBUF_SYS_memcpy (pDataIn, pxInputMessage->inputData.pData, dataSize);
    }
    else pDataIn = NULL;
  }
  else pDataIn = (TCsdUnsignedInt8*)pxInputMessage->inputData.pData;

  if (pxInputMessage->has_output)
  {
    pDataOutTmpBuffer = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(dataSize);
    if (pDataOutTmpBuffer == NULL) return RPC_STATUS_MALLOC_ERROR;
  }

  if (pxInputMessage->has_outputBufferHandle)
  {
    outputSysBuffer = (TNhtCsdSysBufferHandle)(size_t)pxInputMessage->outputBufferHandle;
    pDataOut = (TCsdUnsignedInt8*)outputSysBuffer;
  }
  else pDataOut = pDataOutTmpBuffer;

  csdStatus = nhtCsdDecryptDataWithSecretContentKey (
    algo,
    mode,
    protectingKeyNumber,
    (TNhtProtectingKey const *)pProtectingKeys,
    pContentKey,
    contentKeySize,
    pIv,
    ivSize,
    refreshIv,
    sessionHandle,
    pDataIn,
    pDataOut,
    dataSize );

  if (pDataOut && pDataOutTmpBuffer && pxInputMessage->has_output)
  {
    if (pxInputMessage->has_outputBufferHandle)
      MSGBUF_SYS_memcpy (pDataOutTmpBuffer, pDataOut, dataSize);

    (*pxOutputMessage)->byteArray.pData = (void*)pDataOutTmpBuffer;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)dataSize;
    pDataOutTmpBuffer = NULL;
  }

  if (pDataOutTmpBuffer) MSGBUF_SYS_free (pDataOutTmpBuffer);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_doMonteCarloTest
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_doMonteCarloTest
(
  TMsgBuf_rpcHandler                        xRpcHandler,
  const TNhtcsd_R2rMonteCarloParamsInMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg                    ** pxOutputMessage
)
{
  TCsdStatus                      csdStatus;
  TNhtCsd_r2r_test_algoParams     testInputParams;
  TCsdUnsignedInt8              * pOutputData = NULL;
  TNhtProtectingKey             * pProtectingKeys = NULL;

  nhtcsd_r2r_testAlgo_initParams (&testInputParams);

  testInputParams.cryptoAlgorithm = (TCsdR2RAlgorithm)pxInputMessage->cryptoAlgo;
  testInputParams.cryptoMode = (TCsdR2RCryptoOperationMode)pxInputMessage->cryptoMode;

  testInputParams.isMonteCarlo         = (TCsdBoolean)pxInputMessage->isMonteCarlo;
  testInputParams.runNumber            = (TCsdUnsignedInt32)pxInputMessage->runNumber;
  testInputParams.useSwKey             = (TCsdBoolean)pxInputMessage->useSwKey;
  testInputParams.isForEncryption      = (TCsdBoolean)pxInputMessage->isForEncryption;

  testInputParams.ivcSize = pxInputMessage->len_IV;
  if (pxInputMessage->IV.pData)
    testInputParams.pIvc    = pxInputMessage->IV.pData;
  else testInputParams.pIvc = NULL;

  testInputParams.dataSize    = pxInputMessage->len_dataIn;
  if (pxInputMessage->dataIn.pData)
    testInputParams.pInputData  = pxInputMessage->dataIn.pData;
  else testInputParams.pInputData = NULL;

  if (pxInputMessage->has_output)
  {
    pOutputData = (TCsdUnsignedInt8*)MSGBUF_SYS_malloc(testInputParams.dataSize);
    if (pOutputData == NULL)
    {
      return RPC_STATUS_MALLOC_ERROR;
    }
  }
  else pOutputData = NULL;

  if (testInputParams.useSwKey)
  {
    testInputParams.keys.sw.clearTextHostKeySize = pxInputMessage->len_clearHostKey;
    if (pxInputMessage->clearHostKey.pData)
      testInputParams.keys.sw.pClearTextHostKey    = pxInputMessage->clearHostKey.pData;
    else testInputParams.keys.sw.pClearTextHostKey = NULL;
  }
  else
  {
    if (pxInputMessage->cipheredProtKeys && ((int)pxInputMessage->n_cipheredProtKeys != CSD_R2R_NB_OF_PROTECTING_KEYS))
    {
      if (pOutputData) MSGBUF_SYS_free(pOutputData);
      return RPC_STATUS_ILLEGAL_PARAMETER;
    }

    testInputParams.keys.KL.cipheredContentKeySize = pxInputMessage->len_cipheredContentKey;
    if (pxInputMessage->cipheredContentKey.pData)
      testInputParams.keys.KL.pCipheredContentKey    = pxInputMessage->cipheredContentKey.pData;
    else testInputParams.keys.KL.pCipheredContentKey = NULL;

    if (pxInputMessage->cipheredProtKeys)
    {
      int i;

      pProtectingKeys = (TNhtProtectingKey*)MSGBUF_SYS_malloc(sizeof(TNhtProtectingKey) * pxInputMessage->n_cipheredProtKeys);
      if (pProtectingKeys == NULL)
      {
        if (pOutputData) MSGBUF_SYS_free(pOutputData);
        return RPC_STATUS_MALLOC_ERROR;
      }

      testInputParams.keys.KL.cipheredProtectingKeyNumber = (TCsdUnsignedInt32)pxInputMessage->n_cipheredProtKeys;
      testInputParams.keys.KL.pCipheredProtectingKeys = pProtectingKeys;

      for (i=0; i < (int)testInputParams.keys.KL.cipheredProtectingKeyNumber; i++)
      {
        MSGBUF_SYS_memcpy (
          &pProtectingKeys[i][0],
          pxInputMessage->cipheredProtKeys[i].pData,
          sizeof(TNhtProtectingKey));
      }
    }
  }


  csdStatus = nhtcsd_r2r_monteCarlo_test_run (&testInputParams, pOutputData);

  if (pOutputData)
  {
    (*pxOutputMessage)->byteArray.pData = (void*)pOutputData;
    (*pxOutputMessage)->byteArray.len   = (uint32_t)testInputParams.dataSize;
  }

  if (pProtectingKeys) MSGBUF_SYS_free (pProtectingKeys);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_getDvrKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_getDvrKey
(
  TMsgBuf_rpcHandler               xRpcHandler,
  const TNhtcsd_OptOutput1InMsg  * pxInputMessage,
  TNhtcsd_BytesOutMsg           ** pxOutputMessage
)
{
  TCsdStatus         csdStatus;
  TCsdUnsignedInt8   dvrKey[16];
  void             * pRpcDvrKey;

  if (pxInputMessage->has_output)
  {
    csdStatus = _CRPC(csdGetDvrKey) (dvrKey);
    pRpcDvrKey = (void*)MSGBUF_SYS_malloc(16);
    if (pRpcDvrKey == NULL) return RPC_STATUS_MALLOC_ERROR;

    MSGBUF_SYS_memcpy (pRpcDvrKey, &dvrKey[0], 16);
    (*pxOutputMessage)->byteArray.len = 16;
    (*pxOutputMessage)->byteArray.pData = pRpcDvrKey;
  }
  else csdStatus = _CRPC(csdGetDvrKey) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;
  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_openDscTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_openDscTestRun
(
  TMsgBuf_rpcHandler                    xRpcHandler,
  const TNhtcsd_DscTestRunParamInMsg  * pxInputMessage,
  TNhtcsd_CsdHandleOutMsg            ** pxOutputMessage
)
{
  TCsdStatus                    csdStatus;
  TNhtCsdDscTestRunParameters   dscTestRunParameters;
  TRpcDscTestRunHandle        * pRpcDscHandle = NULL;
  TMsgBuf_rpcHandler          * pRpcHandle = NULL;

  dscTestRunParameters.ivSize = (TCsdSize)pxInputMessage->len_IV;
  if (pxInputMessage->IV.pData)
  {
    if (pxInputMessage->IV.len > 16)
      return RPC_STATUS_ILLEGAL_PARAMETER;

    MSGBUF_SYS_memcpy (&dscTestRunParameters.iv[0], pxInputMessage->IV.pData, pxInputMessage->IV.len);
  }
  else MSGBUF_SYS_memset (&dscTestRunParameters.iv[0], 0, pxInputMessage->IV.len);

  pRpcDscHandle = (TRpcDscTestRunHandle*)MSGBUF_SYS_malloc(sizeof(TRpcDscTestRunHandle));
  if (pRpcDscHandle == NULL) return RPC_STATUS_MALLOC_ERROR;

  pRpcDscHandle->magicNumber       = DSC_TEST_RUN_MAGIC_NUMBER;
  pRpcDscHandle->ecmCallBackHandle = 0;
  pRpcDscHandle->lastTableId       = 0;
  pRpcDscHandle->privateData       = NULL;
  pRpcDscHandle->dscHandle         = (TNhtCsdDscTestRunHandle)NULL;
  pRpcDscHandle->rpcHandler        = xRpcHandler;

  dscTestRunParameters.emi                 = (TCsdUnsignedInt16)pxInputMessage->emi;
  dscTestRunParameters.audioPid            = (int)pxInputMessage->audioPid;
  dscTestRunParameters.videoPid            = (int)pxInputMessage->videoPid;
  dscTestRunParameters.pcrPid              = (int)pxInputMessage->pcrPid;
  dscTestRunParameters.isInClear           = (int)pxInputMessage->isInClear;
  dscTestRunParameters.ecmPid              = (int)pxInputMessage->ecmPid;
  dscTestRunParameters.isForEncryption     = (TCsdBoolean)pxInputMessage->isForEncryption;
  dscTestRunParameters.pInputFilePathname  = (char*)pxInputMessage->inputFilePathname;
  dscTestRunParameters.pOutputFilePathname = (char*)pxInputMessage->outputFilePathname;

  pRpcDscHandle->privateData = (TNhtCsdDscCallBackPrivateParameters)pRpcDscHandle;

  pRpcDscHandle->ecmCallBackHandle = (int64_t)pxInputMessage->ecmCallBack;

  if (pxInputMessage->has_ecmCallBack)
  {
    dscTestRunParameters.ecmCallBackFct         = rpcEcmCallBackFunction;
    dscTestRunParameters.ecmCallBackPrivateData = (TNhtCsdDscCallBackPrivateParameters)pRpcDscHandle;
  }
  else
  {
    dscTestRunParameters.ecmCallBackFct         = (TNhtDscEcmContentCallBack)NULL;
    dscTestRunParameters.ecmCallBackPrivateData = (TNhtCsdDscCallBackPrivateParameters)0;
  }

  if (pxInputMessage->has_output) pRpcHandle = &pRpcDscHandle->dscHandle;
  else pRpcHandle = NULL;

  csdStatus = _CRPC(nhtCsdOpenDscTestRunSession) (
    &dscTestRunParameters,
    pRpcHandle );

  if ((csdStatus == CSD_NO_ERROR) && pRpcHandle && *pRpcHandle)
  {
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)pRpcDscHandle;
  }
  else
  {
    if (pRpcDscHandle) MSGBUF_SYS_free (pRpcDscHandle);
    pRpcDscHandle = NULL;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_closeDscTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_closeDscTestRun
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg   ** pxOutputMessage
)
{
  TCsdStatus             csdStatus;
  TRpcDscTestRunHandle * pRpcDscHandle = NULL;

  if (pxInputMessage->has_handle)
    pRpcDscHandle = (TRpcDscTestRunHandle*)(size_t)pxInputMessage->handle;

  if (pRpcDscHandle)
    csdStatus = _CRPC(nhtCsdCloseDscTestRunSession) (pRpcDscHandle->dscHandle);
  else csdStatus = _CRPC(nhtCsdCloseDscTestRunSession) (NULL);

  if ((csdStatus == CSD_NO_ERROR) && pRpcDscHandle)
    MSGBUF_SYS_free (pRpcDscHandle);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_startDscTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_startDscTestRun
(
  TMsgBuf_rpcHandler                         xRpcHandler,
  const TNhtcsd_HandleInMsg                * pxInputMessage,
  TNhtcsd_TestStatusOutMsg                ** pxOutputMessage
)
{
  TNhtCsdTestRunStatus   csdTestRunStatus;
  TRpcDscTestRunHandle * pRpcDscHandle = NULL;

  if (pxInputMessage->has_handle)
    pRpcDscHandle = (TRpcDscTestRunHandle*)(size_t)pxInputMessage->handle;

  if (pRpcDscHandle)
  {
    pRpcDscHandle->privateData = (TNhtCsdDscCallBackPrivateParameters)pRpcDscHandle;
    csdTestRunStatus = _CRPC(nhtCsdStartDscTestRun) (pRpcDscHandle->dscHandle );
  }
  else csdTestRunStatus = _CRPC(nhtCsdStartDscTestRun) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtCsdTestRunStatus)csdTestRunStatus;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_waitOnDscTestRunCompletion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_waitOnDscTestRunCompletion
(
  TMsgBuf_rpcHandler                            xRpcHandler,
  const TNhtcsd_TestRunWaitOnCompletionInMsg  * pxInputMessage,
  TNhtcsd_TestStatusOutMsg                   ** pxOutputMessage
)
{
  TNhtCsdTestRunStatus   csdTestRunStatus;
  TRpcDscTestRunHandle * pRpcDscHandle = NULL;
  int                    timeout;

  if (pxInputMessage->has_testRunHandle)
    pRpcDscHandle = (TRpcDscTestRunHandle*)(size_t)pxInputMessage->testRunHandle;

  timeout       = (int)pxInputMessage->timeout;

  if (pRpcDscHandle)
    csdTestRunStatus = _CRPC(nhtCsdWaitOnDscTestRunCompletion) (pRpcDscHandle->dscHandle, timeout );
  else csdTestRunStatus = _CRPC(nhtCsdWaitOnDscTestRunCompletion) (NULL, timeout );

  (*pxOutputMessage)->retStatus = (TNhtCsdTestRunStatus)csdTestRunStatus;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_stopDscTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_stopDscTestRun
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_TestStatusOutMsg  ** pxOutputMessage
)
{
  TNhtCsdTestRunStatus csdTestRunStatus;
  TRpcDscTestRunHandle * pRpcDscHandle = NULL;

  if (pxInputMessage->has_handle)
    pRpcDscHandle = (TRpcDscTestRunHandle*)(size_t)pxInputMessage->handle;

  if (pRpcDscHandle)
    csdTestRunStatus = _CRPC(nhtCsdStopDscTestRun) (pRpcDscHandle->dscHandle);
  else csdTestRunStatus = _CRPC(nhtCsdStopDscTestRun) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtCsdTestRunStatus)csdTestRunStatus;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_setClearTextDscHostKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_setClearTextDscHostKey
(
  TMsgBuf_rpcHandler                        xRpcHandler,
  const TNhtcsd_DscClearTextHostKeyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                ** pxOutputMessage
)
{
  TCsdStatus csdStatus;
  TRpcDscTestRunHandle   * pRpcDscHandle = NULL;
  TCsdUnsignedInt8 const * pOddKey       = NULL;
  TCsdSize                 oddKeySize;
  TCsdUnsignedInt8 const * pEvenKey      = NULL;
  TCsdSize                 evenKeySize;

  if (pxInputMessage->has_handle)
    pRpcDscHandle = (TRpcDscTestRunHandle*)(size_t)pxInputMessage->handle;

  oddKeySize    = (TCsdSize)pxInputMessage->len_oddHostKey;
  if (pxInputMessage->oddHostKey.pData)
    pOddKey = (TCsdUnsignedInt8 const *)pxInputMessage->oddHostKey.pData;

  evenKeySize   = (TCsdSize)pxInputMessage->len_evenHostKey;
  if (pxInputMessage->evenHostKey.pData)
    pEvenKey      = (TCsdUnsignedInt8 const *)pxInputMessage->evenHostKey.pData;

  if (pRpcDscHandle)
    csdStatus = _CRPC(nhtCsdTestRunSetClearTextDscHostKeys) (
      pRpcDscHandle->dscHandle,
      pOddKey,
      oddKeySize,
      pEvenKey,
      evenKeySize );
  else
    csdStatus = _CRPC(nhtCsdTestRunSetClearTextDscHostKeys) (
      NULL,
      pOddKey,
      oddKeySize,
      pEvenKey,
      evenKeySize );

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_setProtectedDscContentKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_setProtectedDscContentKey
(
  TMsgBuf_rpcHandler                           xRpcHandler,
  const TNhtcsd_DscProtectedContentKeyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                   ** pxOutputMessage
)
{
  TCsdStatus             csdStatus;
  TRpcDscTestRunHandle * pRpcDscHandle = NULL;
  TCsdUnsignedInt32      cipheredProtectingKeyNumber;
  TCsdUnsignedInt32      i;
  TNhtProtectingKey    * pProtectingKeys = NULL;
  TCsdUnsignedInt8     * pOddKey = NULL;
  TCsdSize               oddKeySize;
  TCsdUnsignedInt8     * pEvenKey = NULL;
  TCsdSize               evenKeySize;

  if (pxInputMessage->has_handle)
    pRpcDscHandle = (TRpcDscTestRunHandle*)(size_t)pxInputMessage->handle;

  cipheredProtectingKeyNumber = (TCsdUnsignedInt32)pxInputMessage->num_cipheredProtKeys;

  if (pxInputMessage->cipheredProtKeys && ((int)cipheredProtectingKeyNumber != CSD_SCR_NB_OF_PROTECTING_KEYS))
    return RPC_STATUS_ILLEGAL_PARAMETER;

  if (pxInputMessage->cipheredProtKeys)
  {
    for (i=0; i<cipheredProtectingKeyNumber; i++)
    {
      if ((pxInputMessage->cipheredProtKeys[i].len != 16) ||
          (pxInputMessage->cipheredProtKeys[i].pData == NULL))
        return RPC_STATUS_ILLEGAL_PARAMETER;
    }
  }

  if (pxInputMessage->cipheredProtKeys)
  {
    pProtectingKeys = (TNhtProtectingKey*)MSGBUF_SYS_malloc(sizeof(TNhtProtectingKey) * cipheredProtectingKeyNumber);
    for (i=0; i<cipheredProtectingKeyNumber; i++)
    {
      MSGBUF_SYS_memcpy (&pProtectingKeys[i][0], pxInputMessage->cipheredProtKeys[i].pData, 16);
    }
  }

  oddKeySize  = (TCsdSize)pxInputMessage->len_oddContentKey;
  if (pxInputMessage->oddContentKey.pData)
    pOddKey     = (TCsdUnsignedInt8*)pxInputMessage->oddContentKey.pData;
  else pOddKey = NULL;

  evenKeySize = (TCsdSize)pxInputMessage->len_evenContentKey;
  if (pxInputMessage->evenContentKey.pData)
    pEvenKey    = (TCsdUnsignedInt8*)pxInputMessage->evenContentKey.pData;
  else pEvenKey = NULL;

  if (pRpcDscHandle)
    csdStatus = _CRPC(nhtCsdTestRunSetProtectedDscContentKeys) (
      pRpcDscHandle->dscHandle,
      (TNhtProtectingKey const *)pProtectingKeys,
      cipheredProtectingKeyNumber,
      pOddKey,
      oddKeySize,
      pEvenKey,
      evenKeySize );
   else
    csdStatus = _CRPC(nhtCsdTestRunSetProtectedDscContentKeys) (
      NULL,
      (TNhtProtectingKey const *)pProtectingKeys,
      cipheredProtectingKeyNumber,
      pOddKey,
      oddKeySize,
      pEvenKey,
      evenKeySize );

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  if (pProtectingKeys) MSGBUF_SYS_free(pProtectingKeys);

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_openScrTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_openScrTestRun
(
  TMsgBuf_rpcHandler                    xRpcHandler,
  const TNhtcsd_ScrTestRunParamInMsg  * pxInputMessage,
  TNhtcsd_CsdHandleOutMsg            ** pxOutputMessage
)
{
  TCsdStatus                    csdStatus;
  TNhtCsdScrTestRunParameters   scrTestRunParameters;
  TNhtCsdScrTestRunHandle       scrTestRunHandle;
  TNhtCsdScrTestRunHandle     * pScrTestRunHandle = NULL;

  scrTestRunParameters.emi      = (TCsdUnsignedInt16)pxInputMessage->emi;
  scrTestRunParameters.audioPid = (int)pxInputMessage->audioPid;
  scrTestRunParameters.videoPid = (int)pxInputMessage->videoPid;
  scrTestRunParameters.pcrPid   = (int)pxInputMessage->pcrPid;
  scrTestRunParameters.isForEncryption     = (int)pxInputMessage->isForEncryption;
  scrTestRunParameters.pInputFilePathname  = (char*)pxInputMessage->inputFilePathname;
  scrTestRunParameters.pOutputFilePathname = (char*)pxInputMessage->outputFilePathname;

  if (pxInputMessage->has_output) pScrTestRunHandle = &scrTestRunHandle;

  csdStatus = _CRPC(nhtCsdOpenScrTestRunSession) (
    (const TNhtCsdScrTestRunParameters*)&scrTestRunParameters,
    pScrTestRunHandle );

  if ((csdStatus == CSD_NO_ERROR) && pScrTestRunHandle && *pScrTestRunHandle)
  {
    (*pxOutputMessage)->has_handle = 1;
    (*pxOutputMessage)->handle = (int64_t)(size_t)scrTestRunHandle;
  }

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_closeScrTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_closeScrTestRun
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg   ** pxOutputMessage
)
{
  TCsdStatus               csdStatus;
  TNhtCsdScrTestRunHandle  csdScrTestRunHandle = NULL;

  csdScrTestRunHandle = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  if (pxInputMessage->has_handle && csdScrTestRunHandle)
    csdStatus = _CRPC(nhtCsdCloseScrTestRunSession) (csdScrTestRunHandle);
  else csdStatus = _CRPC(nhtCsdCloseScrTestRunSession) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_nht_startScrTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_startScrTestRun
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_TestStatusOutMsg  ** pxOutputMessage
)
{
  TNhtCsdTestRunStatus     csdTestRunStatus;
  TNhtCsdScrTestRunHandle  csdScrTestRunHandle = NULL;

  csdScrTestRunHandle = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  if (pxInputMessage->has_handle && csdScrTestRunHandle)
    csdTestRunStatus = _CRPC(nhtCsdStartScrTestRun) (csdScrTestRunHandle);
  else csdTestRunStatus = _CRPC(nhtCsdStartScrTestRun) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdTestRunStatus;

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtcsd_hc_nht_waitOnScrTestRunCompletion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_waitOnScrTestRunCompletion
(
  TMsgBuf_rpcHandler                            xRpcHandler,
  const TNhtcsd_TestRunWaitOnCompletionInMsg  * pxInputMessage,
  TNhtcsd_TestStatusOutMsg                   ** pxOutputMessage
)
{
  TNhtCsdTestRunStatus     csdTestRunStatus;
  TNhtCsdScrTestRunHandle  csdScrTestRunHandle = NULL;
  int                      timeout;

  timeout       = (int)pxInputMessage->timeout;

  csdScrTestRunHandle = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->testRunHandle;

  if (pxInputMessage->has_testRunHandle && csdScrTestRunHandle)
    csdTestRunStatus = _CRPC(nhtCsdWaitOnScrTestRunCompletion) (csdScrTestRunHandle, timeout);
  else csdTestRunStatus = _CRPC(nhtCsdWaitOnScrTestRunCompletion) (NULL, timeout);

  (*pxOutputMessage)->retStatus = (TNhtCsdTestRunStatus)csdTestRunStatus;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_nht_stopScrTestRun
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_nht_stopScrTestRun
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtcsd_HandleInMsg  * pxInputMessage,
  TNhtcsd_TestStatusOutMsg  ** pxOutputMessage
)
{
  TNhtCsdTestRunStatus csdTestRunStatus;
  TNhtCsdScrTestRunHandle  csdScrTestRunHandle = NULL;

  csdScrTestRunHandle = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  if (pxInputMessage->has_handle && csdScrTestRunHandle)
    csdTestRunStatus = _CRPC(nhtCsdStopScrTestRun) (csdScrTestRunHandle);
  else csdTestRunStatus = _CRPC(nhtCsdStopScrTestRun) (NULL);

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdTestRunStatus;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setClearTextScrEncryptionKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setClearTextScrEncryptionKey
(
  TMsgBuf_rpcHandler                        xRpcHandler,
  const TNhtcsd_ScrClearTextHostKeyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                ** pxOutputMessage
)
{
  TCsdStatus                csdStatus;
  TNhtCsdScrTestRunHandle   scrHandle = NULL;
  TCsdUnsignedInt8 const  * pHostKey;
  TCsdSize                  hostKeySize;
  TCsdUnsignedInt8 const  * pIv;
  TCsdSize                  ivSize;

  if (pxInputMessage->handle)
    scrHandle = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  pHostKey    = (TCsdUnsignedInt8 const *)pxInputMessage->clearHostKey.pData;
  hostKeySize = (TCsdSize)pxInputMessage->len_clearHostKey;
  pIv         = (TCsdUnsignedInt8 const *)pxInputMessage->IV.pData;
  ivSize      = (TCsdSize)pxInputMessage->len_IV;

  csdStatus = _CRPC(nhtCsdSetClearTextScrEncryptionKey) (
    scrHandle,
    pHostKey,
    hostKeySize,
    pIv,
    ivSize );

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setClearTextScrDecryptionKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setClearTextScrDecryptionKey
(
  TMsgBuf_rpcHandler                        xRpcHandler,
  const TNhtcsd_ScrClearTextHostKeyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                ** pxOutputMessage
)
{
  TCsdStatus                csdStatus;
  TNhtCsdScrTestRunHandle   scrHandle = NULL;
  TCsdUnsignedInt8 const  * pHostKey;
  TCsdSize                  hostKeySize;
  TCsdUnsignedInt8 const  * pIv;
  TCsdSize                  ivSize;

  if (pxInputMessage->has_handle)
    scrHandle   = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  pHostKey    = (TCsdUnsignedInt8 const *)pxInputMessage->clearHostKey.pData;
  hostKeySize = (TCsdSize)pxInputMessage->len_clearHostKey;
  pIv         = (TCsdUnsignedInt8 const *)pxInputMessage->IV.pData;
  ivSize      = (TCsdSize)pxInputMessage->len_IV;

  csdStatus = _CRPC(nhtCsdSetClearTextScrDecryptionKey) (
    scrHandle,
    pHostKey,
    hostKeySize,
    pIv,
    ivSize );

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setProtectedScrEncryptionKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setProtectedScrEncryptionKey
(
  TMsgBuf_rpcHandler                           xRpcHandler,
  const TNhtcsd_ScrProtectedContentKeyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                   ** pxOutputMessage
)
{
  TCsdStatus                csdStatus;
  TNhtCsdScrTestRunHandle   scrHandle = NULL;
  TCsdUnsignedInt8 const  * pCipheredContentKey;
  TCsdSize                  cipheredContentKeySize;
  TCsdUnsignedInt8 const  * pIv;
  TCsdSize                  ivSize;
  TCsdUnsignedInt32         cipheredProtectingKeyNumber;
  TNhtProtectingKey       * pProtectingKeys = NULL;
  TCsdUnsignedInt32      i;

  if (pxInputMessage->has_handle)
    scrHandle              = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  pCipheredContentKey    = (TCsdUnsignedInt8 const *)pxInputMessage->cipheredContentKey.pData;
  cipheredContentKeySize = (TCsdSize)pxInputMessage->len_cipheredContentKey;
  pIv                    = (TCsdUnsignedInt8 const *)pxInputMessage->IV.pData;
  ivSize                 = (TCsdSize)pxInputMessage->len_IV;

  cipheredProtectingKeyNumber = (TCsdUnsignedInt32)pxInputMessage->num_cipheredProtKeys;

  if (pxInputMessage->cipheredProtKeys)
  {
    if ((int)cipheredProtectingKeyNumber != CSD_SCR_NB_OF_PROTECTING_KEYS)
      return RPC_STATUS_ILLEGAL_PARAMETER;

    for (i=0; i<(TCsdUnsignedInt32)pxInputMessage->n_cipheredProtKeys; i++)
    {
      if ((pxInputMessage->cipheredProtKeys[i].len != 16) ||
          (pxInputMessage->cipheredProtKeys[i].pData == NULL))
        return RPC_STATUS_ILLEGAL_PARAMETER;
    }
  }

  if (pxInputMessage->cipheredProtKeys)
  {
    pProtectingKeys = (TNhtProtectingKey*)MSGBUF_SYS_malloc(sizeof(TNhtProtectingKey) * cipheredProtectingKeyNumber);
    for (i=0; i<cipheredProtectingKeyNumber; i++)
    {
      MSGBUF_SYS_memcpy (&pProtectingKeys[i][0], pxInputMessage->cipheredProtKeys[i].pData, 16);
    }
  }

  csdStatus = _CRPC(nhtCsdSetProtectedScrEncryptionKey) (
    scrHandle,
    *(TNhtProtectingKey const **)&pProtectingKeys,
    cipheredProtectingKeyNumber,
    pCipheredContentKey,
    cipheredContentKeySize,
    pIv,
    ivSize );

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  if (pProtectingKeys) MSGBUF_SYS_free(pProtectingKeys);

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtcsd_hc_setProtectedScrDecryptionKey
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtcsd_hc_setProtectedScrDecryptionKey
(
  TMsgBuf_rpcHandler                           xRpcHandler,
  const TNhtcsd_ScrProtectedContentKeyInMsg  * pxInputMessage,
  TNhtcsd_CsdStatusOutMsg                   ** pxOutputMessage
)
{
  TCsdStatus                csdStatus;
  TNhtCsdScrTestRunHandle   scrHandle = NULL;
  TCsdUnsignedInt8 const  * pCipheredContentKey;
  TCsdSize                  cipheredContentKeySize;
  TCsdUnsignedInt8 const  * pIv;
  TCsdSize                  ivSize;
  TCsdUnsignedInt32         cipheredProtectingKeyNumber;
  TNhtProtectingKey       * pProtectingKeys = NULL;
  TCsdUnsignedInt32      i;

  if (pxInputMessage->has_handle)
    scrHandle              = (TNhtCsdScrTestRunHandle)(size_t)pxInputMessage->handle;

  pCipheredContentKey    = (TCsdUnsignedInt8 const *)pxInputMessage->cipheredContentKey.pData;
  cipheredContentKeySize = (TCsdSize)pxInputMessage->len_cipheredContentKey;
  pIv                    = (TCsdUnsignedInt8 const *)pxInputMessage->IV.pData;
  ivSize                 = (TCsdSize)pxInputMessage->len_IV;

  cipheredProtectingKeyNumber = (TCsdUnsignedInt32)pxInputMessage->num_cipheredProtKeys;

  if (pxInputMessage->cipheredProtKeys)
  {
    if ((int)cipheredProtectingKeyNumber != CSD_SCR_NB_OF_PROTECTING_KEYS)
      return RPC_STATUS_ILLEGAL_PARAMETER;

    for (i=0; i< (TCsdUnsignedInt32)pxInputMessage->n_cipheredProtKeys; i++)
    {
      if ((pxInputMessage->cipheredProtKeys[i].len != 16) ||
          (pxInputMessage->cipheredProtKeys[i].pData == NULL))
        return RPC_STATUS_ILLEGAL_PARAMETER;
    }
  }

  if (pxInputMessage->cipheredProtKeys)
  {
    pProtectingKeys = (TNhtProtectingKey*)MSGBUF_SYS_malloc(sizeof(TNhtProtectingKey) * cipheredProtectingKeyNumber);
    for (i=0; i<cipheredProtectingKeyNumber; i++)
    {
      MSGBUF_SYS_memcpy (&pProtectingKeys[i][0], pxInputMessage->cipheredProtKeys[i].pData, 16);
    }
  }

  csdStatus = _CRPC(nhtCsdSetProtectedScrDecryptionKey) (
    scrHandle,
    *(TNhtProtectingKey const **)&pProtectingKeys,
    cipheredProtectingKeyNumber,
    pCipheredContentKey,
    cipheredContentKeySize,
    pIv,
    ivSize );

  (*pxOutputMessage)->retStatus = (TNhtcsd_CsdStatus)csdStatus - (TNhtcsd_CsdStatus)CSD_STATUS_OFFSET;

  if (pProtectingKeys) MSGBUF_SYS_free(pProtectingKeys);

  return RPC_STATUS_NO_ERROR;
}


/*****************************************************************************
 * RPC method calls API wrapper                                              *
 ****************************************************************************/

/* RPC method: rpc_nhtcsd_tn_ecmCallBack
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
static TCsdStatus rpcEcmCallBackFunction
(
        TNhtCsdDscTestRunHandle               xDscTestRunHandle,
        TNhtCsdDscCallBackPrivateParameters   xPrivateParameters,
        TCsdUnsignedInt8                      xEcmTableId,
  const TCsdUnsignedInt8                    * pxEcmContent,
        TCsdSize                              xEcmContentSize
)
{
  TRpcDscTestRunHandle     * pRpcDscHandle;
  TRpc_status                rpcStatus;
  TNhtcsd_EcmCallBackInMsg   rpcEcmCallBackInMsg;
  TNhtcsd_EmptyMsg         * pRpcEmptyMsg;

  pRpcDscHandle = (TRpcDscTestRunHandle*)xPrivateParameters;

  /* Only concider new tableId (in case if this wasn't filtered in the CM's
   * implementation. */
  if ((xEcmTableId == pRpcDscHandle->lastTableId) && (pRpcDscHandle->lastTableId != 0))
  {
    return CSD_NO_ERROR;
  }

  pRpcDscHandle->lastTableId = xEcmTableId;

  /* Export callback notification to the host */
  init_Nhtcsd_EcmCallBackInMsg (&rpcEcmCallBackInMsg);

  rpcEcmCallBackInMsg.tableId = (uint32_t)xEcmTableId;
  if (pRpcDscHandle->ecmCallBackHandle)
  {
    rpcEcmCallBackInMsg.ecmCallBackHandle = pRpcDscHandle->ecmCallBackHandle;
    rpcEcmCallBackInMsg.has_ecmCallBackHandle = 1;
  }

  if (pRpcDscHandle)
  {
    rpcEcmCallBackInMsg.testRunHandle     = (int64_t)(size_t)pRpcDscHandle;
    rpcEcmCallBackInMsg.has_testRunHandle = 1;
  }

  rpcEcmCallBackInMsg.len_ecm = (uint64_t)xEcmContentSize;
  if (pxEcmContent)
  {
    rpcEcmCallBackInMsg.ecm.pData = (void*)pxEcmContent;
    rpcEcmCallBackInMsg.ecm.len   = (uint64_t)xEcmContentSize;
  }

  rpcStatus =  rpc_nhtcsd_tn_ecmCallBack (
    pRpcDscHandle->rpcHandler,
    &rpcEcmCallBackInMsg,
    &pRpcEmptyMsg );

  if (rpcStatus == RPC_STATUS_NO_ERROR) return CSD_NO_ERROR;
  else return CSD_ERROR;
}
