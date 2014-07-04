/**
 * File: $Id:$
 *
 *  This file implements the server/client common BSD API/EAPI function traces.
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


#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_strbuilder.h"
#include "inc/TRACE_nhtbsd.h"


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

#ifdef _NHT_RPC_TRACE_ON_


/* */
TBsdStatus _CRPC(bsdGetApiVersion)
(
  TUnsignedInt32 * pxBsdApiVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetApiVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  pxBsdApiVersion", (void*)pxBsdApiVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetApiVersion (pxBsdApiVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetApiVersion():\n");
    if (pxBsdApiVersion)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxBsdApiVersion", (size_t)*pxBsdApiVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus  _CRPC(bsdGetSoftwareVersion)
(
  TBsd20CharsString  xSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSoftwareVersion", (void*)&xSoftwareVersion[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetSoftwareVersion (xSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetSoftwareVersion():\n");
    if (xSoftwareVersion && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xSoftwareVersion", (void*)&xSoftwareVersion[0], sizeof(TBsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdGetNuid)
(
  TBsd4BytesVector xNuid
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetNuid():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xNuid", (void*)&xNuid[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetNuid (xNuid);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetNuid():\n");
    if (xNuid && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xNuid", (void*)&xNuid[0], sizeof(TBsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdGetNuid64)
(
  TBsd8BytesVector xNuid64
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetNuid64():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xNuid64", (void*)&xNuid64[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetNuid64 (xNuid64);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetNuid64():\n");
    if (xNuid64 && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xNuid64", (void*)&xNuid64[0], sizeof(TBsd8BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdSetStbCaSn)
(
 const TBsd4BytesVector xStbCaSn
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdSetStbCaSn():\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in:  xStbCaSn", (void*)&xStbCaSn[0], sizeof(TBsd4BytesVector));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSetStbCaSn (xStbCaSn);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSetStbCaSn():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdGetStbCaSn)
(
  TBsd4BytesVector xStbCaSn
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetStbCaSn():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xStbCaSn", (void*)&xStbCaSn[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetStbCaSn (xStbCaSn);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetStbCaSn():\n");
    if (xStbCaSn && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xStbCaSn", (void*)&xStbCaSn[0], sizeof(TBsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdSetMarketSegmentId)
(
  const TBsd4BytesVector xMarketSegmentId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdSetMarketSegmentId():\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in:  xMarketSegmentId", (void*)&xMarketSegmentId[0], sizeof(TBsd4BytesVector));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSetMarketSegmentId (xMarketSegmentId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSetMarketSegmentId():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdGetMarketSegmentId)
(
  TBsd4BytesVector xMarketSegmentId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetMarketSegmentId():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xMarketSegmentId", (void*)&xMarketSegmentId[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetMarketSegmentId (xMarketSegmentId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetMarketSegmentId():\n");
    if (xMarketSegmentId && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xMarketSegmentId", (void*)&xMarketSegmentId[0], sizeof(TBsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdGetNUIDCheckNumber)
(
  TBsd4BytesVector xNUIDCheckNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdGetNUIDCheckNumber():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xNUIDCheckNumber", (void*)&xNUIDCheckNumber[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetNUIDCheckNumber (xNUIDCheckNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetNUIDCheckNumber():\n");
    if (xNUIDCheckNumber && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xNUIDCheckNumber", (void*)&xNUIDCheckNumber[0], sizeof(TBsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdGetDataIntegrityCheckNumber)
(
  const TUnsignedInt8 * pxData,
  TUnsignedInt32        xDataSize,
  TBsd4BytesVector      xDataIntegrityCheckNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdGetDataIntegrityCheckNumber():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxData", (void*)pxData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xDataIntegrityCheckNumber", (void*)&xDataIntegrityCheckNumber[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGetDataIntegrityCheckNumber (pxData, xDataSize, xDataIntegrityCheckNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGetDataIntegrityCheckNumber():\n");
    if (xDataIntegrityCheckNumber && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xDataIntegrityCheckNumber", (void*)&xDataIntegrityCheckNumber[0], sizeof(TBsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdChipsetInformation)
(
  TBsdInfoChipset * pxInfoChipset
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdChipsetInformation():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  pxInfoChipset", (void*)pxInfoChipset);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdChipsetInformation (pxInfoChipset);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdChipsetInformation():\n");
    if (pxInfoChipset && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxInfoChipset->BSD_CM", (void*)&pxInfoChipset->BSD_CM[0], 4);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxInfoChipset->BSD_CT", (void*)&pxInfoChipset->BSD_CT[0], 20);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxInfoChipset->BSD_CUT", (void*)&pxInfoChipset->BSD_CUT[0], 20);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxInfoChipset->BSD_EXT", (void*)&pxInfoChipset->BSD_EXT[0], 20);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/******************************************************************************/
/*                                                                            */
/*                                    RAM2RAM                                 */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdOpenRam2RamEncryptSession)
(
  TBsdCipherSession * pxSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdOpenRam2RamEncryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  pxSession", (void*)pxSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdOpenRam2RamEncryptSession (pxSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdOpenRam2RamEncryptSession():\n");
    if (pxSession && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdOpenRam2RamDecryptSession)
(
  TBsdCipherSession * pxSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdOpenRam2RamDecryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  pxSession", (void*)pxSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdOpenRam2RamDecryptSession (pxSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdOpenRam2RamDecryptSession():\n");
    if (pxSession && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdCloseSession)
(
  TBsdCipherSession xSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdCloseSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdCloseSession (xSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdCloseSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdSetClearTextKey)
(
  TBsdCipherSession     xSession,
  TUnsignedInt16        xEmi,
  TSize                 xClearTextKeySize,
  const TUnsignedInt8 * pxClearTextKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdSetClearTextKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextKeySize", (size_t)xClearTextKeySize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextKey", (void*)pxClearTextKey, (size_t)xClearTextKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSetClearTextKey (xSession, xEmi, xClearTextKeySize, pxClearTextKey);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSetClearTextKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdSet2LevelProtectedKey)
(
  TBsdCipherSession     xSession,
  TUnsignedInt16        xEmi,
  TSize                 xCipheredContentKeySize,
  const TUnsignedInt8 * pxCipheredContentKey,
  TSize                 xCipheredProtectingKeySize,
  const TUnsignedInt8 * pxL1CipheredProtectingKey,
  const TUnsignedInt8 * pxL2CipheredProtectingKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@bsdSet2LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredContentKey", (void*)pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeySize", (size_t)xCipheredProtectingKeySize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in:  pxL1CipheredProtectingKey", (void*) pxL1CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in:  pxL2CipheredProtectingKey", (void*) pxL2CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSet2LevelProtectedKey (
    xSession,
    xEmi,
    xCipheredContentKeySize,
    pxCipheredContentKey,
    xCipheredProtectingKeySize,
    pxL1CipheredProtectingKey,
    pxL2CipheredProtectingKey );


  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSet2LevelProtectedKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(bsdEncryptFlashProtKey)
(
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  size_t                xSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdEncryptFlashProtKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xSize", (size_t)xSize, sizeof(size_t));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  pxOutput", (void*)pxOutput);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdEncryptFlashProtKey (
    pxInput,
    pxOutput,
    xSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdEncryptFlashProtKey():\n");
    if (pxOutput && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, xSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}



/* */

TBsdStatus _CRPC(bsdUseFlashProtKey)
(
  TBsdCipherSession xSession,
  TUnsignedInt16    xEmi
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdUseFlashProtKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdUseFlashProtKey (xSession, xEmi);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdUseFlashProtKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(bsdUseCertKey)
(
  TBsdCipherSession xSession,
  TUnsignedInt16    xEmi
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdUseCertKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TUnsignedInt16));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdUseCertKey (xSession, xEmi);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdUseCertKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(bsdSessionEncrypt)
(
  TBsdCipherSession     xSession,
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  TSize                 xMessageSize,
  const TUnsignedInt8 * pxInitVector,
  TSize                 xInitVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdSessionEncrypt():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitVectorSize", (size_t)xInitVectorSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitVector", (void*)pxInitVector, (size_t)xInitVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSessionEncrypt (
    xSession,
    pxInput,
    pxOutput,
    xMessageSize,
    pxInitVector,
    xInitVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSessionEncrypt():\n");
    if (pxOutput && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xMessageSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(bsdSessionDecrypt)
(
  TBsdCipherSession     xSession,
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  TSize                 xMessageSize,
  const TUnsignedInt8 * pxInitVector,
  TSize                 xInitVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdSessionDecrypt():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitVectorSize", (size_t)xInitVectorSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitVector", (void*)pxInitVector, (size_t)xInitVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSessionDecrypt (
    xSession,
    pxInput,
    pxOutput,
    xMessageSize,
    pxInitVector,
    xInitVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSessionDecrypt():\n");
    if (pxOutput && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xMessageSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/******************************************************************************/
/*                                                                            */
/*                                    RSA                                     */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdRsaPublicEncrypt)
(
  const TUnsignedInt8 * pxInput,
  TSize                 xInputSize,
  TUnsignedInt8       * pxOutput,
  TUnsignedInt32        xE,
  const TUnsignedInt8 * pxN,
  TSize                 xKeySize,
  TBsdRsaPadding        xPadding
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdRsaPublicEncrypt():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInputSize", (size_t)xInputSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xInputSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxN", (void*)pxN, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPadding", (size_t)xPadding, sizeof(TBsdRsaPadding));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdRsaPublicEncrypt (
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
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdRsaPublicEncrypt():\n");
    if (pxOutput && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)xKeySize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdRsaPublicDecrypt)
(
  const TUnsignedInt8 * pxInput,
  TUnsignedInt8       * pxOutput,
  TSize               * pxOutputSize,
  TUnsignedInt32        xE,
  const TUnsignedInt8 * pxN,
  TSize                 xKeySize,
  TBsdRsaPadding        xPadding
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdRsaPublicDecrypt():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputSize", (void*)pxOutputSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xE", (size_t)xE, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxN", (void*)pxN, (size_t)xKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPadding", (size_t)xPadding, sizeof(TBsdRsaPadding));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdRsaPublicDecrypt (
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
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdRsaPublicDecrypt():\n");
    if (bsdStatus == BSD_NO_ERROR)
    {
      if (pxOutputSize)
      {
        msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxOutputSize", (size_t)*pxOutputSize, sizeof(TSize));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

        if (pxOutput)
        {
          msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutput", (void*)pxOutput, (size_t)*pxOutputSize);
          msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
        }
      }
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/******************************************************************************/
/*                                                                            */
/*                                    SHA-256                                 */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus  _CRPC(bsdSha256Init)
(
  TBsdHashContext * pxContext
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdSha256Init():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxContext", (void*)pxContext);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSha256Init (pxContext);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSha256Init():\n");

    if (pxContext && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxContext", (void*)*pxContext);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdSha256Update)
(
  TBsdHashContext       xContext,
  const TUnsignedInt8 * pxMessageChunk,
  TSize                 xChunkSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdSha256Update():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xChunkSize", (size_t)xChunkSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessageChunk", (void*)pxMessageChunk, (size_t)xChunkSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSha256Update (
    xContext,
    pxMessageChunk,
    xChunkSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSha256Update():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdSha256Final)
(
  TBsdHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdSha256Final():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMessageDigest", (void*)pxMessageDigest);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdSha256Final (xContext, pxMessageDigest);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdSha256Final():\n");

    if (pxMessageDigest && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxMessageDigest", (void*)pxMessageDigest, 32);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/******************************************************************************/
/*                                                                            */
/*                                    HMAC                                    */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdHmacSha256Init)
(
  const TUnsignedInt8 * pxKey,
  TSize                 xKeySize,
  TBsdHashContext     * pxContext
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdHmacSha256Init():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxContext", (void*)pxContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeySize", (size_t)xKeySize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxKey", (void*)pxKey, (size_t)xKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdHmacSha256Init (
    pxKey,
    xKeySize,
    pxContext );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdHmacSha256Init():\n");

    if (pxContext && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxContext", (void*)*pxContext);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdHmacSha256Update)
(
  TBsdHashContext       xContext,
  const TUnsignedInt8 * pxMessageChunk,
  TSize                 xChunkSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdHmacSha256Update():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xChunkSize", (size_t)xChunkSize, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMessageChunk", (void*)pxMessageChunk, (size_t)xChunkSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdHmacSha256Update (
    xContext,
    pxMessageChunk,
    xChunkSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdHmacSha256Update():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(bsdHmacSha256Final)
(
  TBsdHashContext   xContext,
  TUnsignedInt8   * pxMessageDigest
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdHmacSha256Final():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xContext", (void*)xContext);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMessageDigest", (void*)pxMessageDigest);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdHmacSha256Final (xContext, pxMessageDigest);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdHmacSha256Final():\n");

    if (pxMessageDigest && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxMessageDigest", (void*)pxMessageDigest, 32);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/******************************************************************************/
/*                                                                            */
/*                                  RANDOM                                    */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdGenerateRandomBytes)
(
  TSize           xNumOfBytes,
  TUnsignedInt8 * pxRandomBytes
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdGenerateRandomBytes():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xNumOfBytes", (size_t)xNumOfBytes, sizeof(TSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxRandomBytes", (void*)pxRandomBytes);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdGenerateRandomBytes (xNumOfBytes, pxRandomBytes);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdGenerateRandomBytes():\n");

    if (pxRandomBytes && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxRandomBytes", (void*)pxRandomBytes, (size_t)xNumOfBytes);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/******************************************************************************/
/*                                                                            */
/*                                  RESET                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup res
 *
 *  @brief
 *    Performs a chipset reset, this reset must clear the registers, caches and
 *    other volatile memories. This function does not return.
 *
 *  @applies
 *    NOCS3 only
 *
*/
void _CRPC(bsdChipReset) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string (&msgStrBuffer, ">@bsdChipReset():");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdChipReset ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdChipReset():");
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
}


/******************************************************************************/
/*                                                                            */
/*                              RAM2RAM (legacy)                              */
/*                                                                            */
/******************************************************************************/

/* */
TBsdStatus _CRPC(bsdEncryptDataWithSecretContentKey)
(
  TBsdR2RAlgorithm      xAlgorithm,
  const TUnsignedInt8 * pxInputData,
  TUnsignedInt8       * pxOutputData,
  TUnsignedInt32        xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdEncryptDataWithSecretContentKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xAlgorithm", (size_t)xAlgorithm, sizeof(TBsdR2RAlgorithm));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputData", (void*)pxInputData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputData", (void*)pxOutputData);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdEncryptDataWithSecretContentKey (
    xAlgorithm,
    pxInputData,
    pxOutputData,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdEncryptDataWithSecretContentKey():\n");

    if (pxOutputData && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputData", (void*)pxOutputData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(bsdDecryptDataWithSecretContentKey)
(
  TBsdR2RAlgorithm      xAlgorithm,
  const TUnsignedInt8 * pxInputData,
  TUnsignedInt8       * pxOutputData,
  TUnsignedInt32        xDataSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdDecryptDataWithSecretContentKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xAlgorithm", (size_t)xAlgorithm, sizeof(TBsdR2RAlgorithm));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInputData", (void*)pxInputData, (size_t)xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxOutputData", (void*)pxOutputData);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdDecryptDataWithSecretContentKey (
    xAlgorithm,
    pxInputData,
    pxOutputData,
    xDataSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdDecryptDataWithSecretContentKey():\n");

    if (pxOutputData && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxOutputData", (void*)pxOutputData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TUnsignedInt8 * _CRPC(bsdAllocateBuffer)
(
  size_t xBufferSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TUnsignedInt8 *  pBuffer;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@bsdAllocateBuffer():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xBufferSize", (size_t)xBufferSize, sizeof(size_t));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  pBuffer = bsdAllocateBuffer (xBufferSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdAllocateBuffer():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "ret: pBuffer", (void*)pBuffer);
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return pBuffer;
}

/* */
TBsdStatus _CRPC(bsdFreeBuffer)
(
  TUnsignedInt8 * pxBuffer
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@bsdFreeBuffer():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBuffer", (void*)pxBuffer);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = bsdFreeBuffer (pxBuffer);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@bsdFreeBuffer():\n");

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(nhtBsdInitialize) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdInitialize():");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdInitialize ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdInitialize():\n");

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdTerminate) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdTerminate():");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdTerminate ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdTerminate():\n");

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdGetCertificationNOCSVersion)
(
  TUnsignedInt32 * pxVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdGetCertificationNOCSVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxVersion", (void*)pxVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdGetCertificationNOCSVersion (pxVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdGetCertificationNOCSVersion():\n");

    if (pxVersion && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxVersion", (size_t)*pxVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdGetSoftwareVersion)
(
  TBsd20CharsString xSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSoftwareVersion", (void*)&xSoftwareVersion[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdGetSoftwareVersion (xSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdGetSoftwareVersion():\n");

    if (xSoftwareVersion && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xSoftwareVersion", (void*)&xSoftwareVersion[0], sizeof(TBsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdGetChipManufacturerName)
(
  TBsd20CharsString xChipManufacturerName
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdGetChipManufacturerName():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xChipManufacturerName", (void*)&xChipManufacturerName[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdGetChipManufacturerName (xChipManufacturerName);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdGetChipManufacturerName():\n");

    if (xChipManufacturerName && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xChipManufacturerName", (void*)&xChipManufacturerName[0], sizeof(TBsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdGetChipName)
(
  TBsd20CharsString xChipName
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdGetChipName():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xChipName", (void*)&xChipName[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdGetChipName (xChipName);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdGetChipName():\n");

    if (xChipName && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xChipName", (void*)&xChipName[0], sizeof(TBsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdGetBsdProtectingKeyNumber)
(
  TUnsignedInt32 * pxProtectingKeyNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdGetBsdProtectingKeyNumber():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxProtectingKeyNumber", (void*)pxProtectingKeyNumber);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdGetBsdProtectingKeyNumber (pxProtectingKeyNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdGetBsdProtectingKeyNumber():\n");

    if (pxProtectingKeyNumber && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxProtectingKeyNumber", (size_t)*pxProtectingKeyNumber, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(nhtGetNhtBsdApiVersion)
(
  TUnsignedInt32 * pxNhtBsdApiVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">#nhtGetNhtBsdApiVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNhtBsdApiVersion", (void*)pxNhtBsdApiVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtGetNhtBsdApiVersion (pxNhtBsdApiVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<#nhtGetNhtBsdApiVersion():\n");

    if (pxNhtBsdApiVersion && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxNhtBsdApiVersion", (size_t)*pxNhtBsdApiVersion, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


/* */
TBsdStatus _CRPC(nhtBsdGetBsdStatusOffsetValue)
(
  TUnsignedInt32 * pxBsdOffsetValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">#nhtBsdGetBsdStatusOffsetValue():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBsdOffsetValue", (void*)pxBsdOffsetValue);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdGetBsdStatusOffsetValue (pxBsdOffsetValue);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<#nhtBsdGetBsdStatusOffsetValue():\n");

    if (pxBsdOffsetValue && (bsdStatus == BSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxBsdOffsetValue", (size_t)*pxBsdOffsetValue, sizeof(TUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}

/* */
TBsdStatus _CRPC(nhtBsdServerTerminate) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TBsdStatus       bsdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtBsdServerTerminate():");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  bsdStatus = nhtBsdServerTerminate ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtBsdServerTerminate():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: bsdStatus", (size_t)bsdStatus, sizeof(TBsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return bsdStatus;
}


#endif /* _NHT_RPC_TRACE_ON_ */
