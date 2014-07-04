/**
 * File: $Id:$
 *
 *  This file implements the server/client common CSD API/EAPI function traces.
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
#include "inc/TRACE_nhtcsd.h"


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


#ifdef _NHT_RPC_TRACE_ON_

/* */
TCsdStatus _CRPC(csdGetApiVersion)
(
  TCsdUnsignedInt32 * pxCsdApiVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetApiVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxCsdApiVersion", (void*)pxCsdApiVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetApiVersion (pxCsdApiVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetApiVersion():\n");
    if (pxCsdApiVersion && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxCsdApiVersion", (size_t)*pxCsdApiVersion, sizeof(TCsdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetSoftwareVersion)
(
  TCsd20CharsString  xSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSoftwareVersion", (void*)&xSoftwareVersion[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetSoftwareVersion (xSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetSoftwareVersion():\n");
    if (xSoftwareVersion && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xSoftwareVersion", (void*)&xSoftwareVersion[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetChipRevision)
(
  TCsd20CharsString xChipRevision
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetChipRevision():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xChipRevision", (void*)&xChipRevision[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetChipRevision (xChipRevision);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetChipRevision():\n");
    if (xChipRevision && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xChipRevision", (void*)&xChipRevision[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetChipExtension)
(
  TCsd20CharsString xChipExtension
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetChipExtension():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xChipExtension", (void*)&xChipExtension[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetChipExtension (xChipExtension);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetChipExtension():\n");
    if (xChipExtension && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xChipExtension", (void*)&xChipExtension[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(csdGetNuid)
(
  TCsd4BytesVector xNuid
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetNuid():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xNuid", (void*)&xNuid[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetNuid (xNuid);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetNuid():\n");
    if (xNuid && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xNuid", (void*)&xNuid[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetNuid64)
(
  TCsd8BytesVector xNuid64
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetNuid64():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xNuid64", (void*)&xNuid64[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetNuid64 (xNuid64);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetNuid64():\n");
    if (xNuid64 && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xNuid64", (void*)&xNuid64[0], sizeof(TCsd8BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetNUIDCheckNumber)
(
  TCsd4BytesVector xNUIDCheckNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetNUIDCheckNumber():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xNUIDCheckNumber", (void*)&xNUIDCheckNumber[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetNUIDCheckNumber (xNUIDCheckNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetNUIDCheckNumber():\n");
    if (xNUIDCheckNumber && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xNUIDCheckNumber", (void*)&xNUIDCheckNumber[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetCSCDCheckNumber)
(
  const TCsdUnsignedInt8 xCSCData[16],
        TCsd4BytesVector xCSCDCheckNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetCSCDCheckNumber():\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: xCSCData", (void*)&xCSCData[0], 16);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xCSCDCheckNumber", (void*)&xCSCDCheckNumber[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetCSCDCheckNumber (xCSCData, xCSCDCheckNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetCSCDCheckNumber():\n");
    if (xCSCDCheckNumber && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xCSCDCheckNumber", (void*)&xCSCDCheckNumber[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetSTBCASNCheckNumber)
(
  const TCsdUnsignedInt8 xSTBCASNData[4],
        TCsd4BytesVector xSTBCASNCheckNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetSTBCASNCheckNumber():\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: xSTBCASNData", (void*)&xSTBCASNData[0], 4);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSTBCASNCheckNumber", (void*)&xSTBCASNCheckNumber[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetSTBCASNCheckNumber (xSTBCASNData, xSTBCASNCheckNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetSTBCASNCheckNumber():\n");
    if (xSTBCASNCheckNumber && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xSTBCASNCheckNumber", (void*)&xSTBCASNCheckNumber[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetDataIntegrityCheckNumber)
(
  const TCsdUnsignedInt8 * pxData,
  TCsdSize                 xDataSize,
  TCsd4BytesVector         xDataIntegrityCheckNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetDataIntegrityCheckNumber():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDataSize", (size_t)xDataSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: pxData", (void*)pxData, xDataSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDataIntegrityCheckNumber", (void*)&xDataIntegrityCheckNumber[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetDataIntegrityCheckNumber (pxData, xDataSize, xDataIntegrityCheckNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetDataIntegrityCheckNumber():\n");
    if (xDataIntegrityCheckNumber && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xDataIntegrityCheckNumber", (void*)&xDataIntegrityCheckNumber[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdSetStbCaSn)
(
  const TCsd4BytesVector xStbCaSn
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdSetStbCaSn():\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: xStbCaSn", (void*)&xStbCaSn[0], sizeof(TCsd4BytesVector));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdSetStbCaSn (xStbCaSn);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSetStbCaSn():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetStbCaSn)
(
  TCsd4BytesVector xStbCaSn
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetStbCaSn():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xStbCaSn", (void*)&xStbCaSn[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetStbCaSn (xStbCaSn);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetStbCaSn():\n");
    if (xStbCaSn && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xStbCaSn", (void*)&xStbCaSn[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdSetMarketSegmentId)
(
  const TCsd4BytesVector xMarketSegmentId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdSetMarketSegmentId():\n");
    msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "in: xMarketSegmentId", (void*)&xMarketSegmentId[0], sizeof(TCsd4BytesVector));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdSetMarketSegmentId (xMarketSegmentId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSetMarketSegmentId():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetMarketSegmentId)
(
  TCsd4BytesVector xMarketSegmentId
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetMarketSegmentId():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xMarketSegmentId", (void*)&xMarketSegmentId[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetMarketSegmentId (xMarketSegmentId);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetMarketSegmentId():\n");
    if (xMarketSegmentId && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xMarketSegmentId", (void*)&xMarketSegmentId[0], sizeof(TCsd4BytesVector));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdSetBootMode)
(
  TCsdBootMode xBootMode
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdSetBootMode():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xBootMode", (size_t)xBootMode, sizeof(TCsdBootMode));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdSetBootMode (xBootMode);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSetBootMode():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetBootMode)
(
  TCsdBootMode * pxBootMode
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetBootMode():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBootMode", (void*)pxBootMode);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetBootMode (pxBootMode);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetBootMode():\n");
    if (pxBootMode && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxBootMode", (size_t)*pxBootMode, sizeof(TCsdBootMode));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdEnableScs)
(
  void
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdEnableScs()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdEnableScs ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdEnableScs():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetScsActivationFlag)
(
  TCsdActivationFlag * pxScsActivationFlagState
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetScsActivationFlag():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxScsActivationFlagState", (void*)pxScsActivationFlagState);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetScsActivationFlag (pxScsActivationFlagState);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetScsActivationFlag():\n");
    if (pxScsActivationFlagState && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxScsActivationFlagState", (size_t)*pxScsActivationFlagState, sizeof(TCsdActivationFlag));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdSetScsTotalAreaSize)
(
  TCsdScsTotalAreaSize xScsTotalAreaSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdSetScsTotalAreaSize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xScsTotalAreaSize", (size_t)xScsTotalAreaSize, sizeof(TCsdScsTotalAreaSize));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdSetScsTotalAreaSize (xScsTotalAreaSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSetScsTotalAreaSize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetScsTotalAreaSize)
(
  TCsdScsTotalAreaSize * pxTotalAreaSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetScsTotalAreaSize():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxTotalAreaSize", (void*)pxTotalAreaSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetScsTotalAreaSize (pxTotalAreaSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetScsTotalAreaSize():\n");
    if (pxTotalAreaSize && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxTotalAreaSize", (size_t)*pxTotalAreaSize, sizeof(TCsdScsTotalAreaSize));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(csdSetRamUnscrambledStorageSize)
(
  TCsdUnsignedInt8  * pxPvRamUnscrambledStorageSize,
  TCsdUnsignedInt16   xPvLength
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdSetRamUnscrambledStorageSize():\n");
    msgbuf_strbuilder_setparam_hex_value  (&msgStrBuffer, "in: xPvLength", (size_t)xPvLength, sizeof(TCsdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvRamUnscrambledStorageSize", (void*)pxPvRamUnscrambledStorageSize, (size_t)xPvLength);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdSetRamUnscrambledStorageSize (pxPvRamUnscrambledStorageSize, xPvLength);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSetRamUnscrambledStorageSize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetRamUnscrambledStorageSize)
(
  TCsdUnsignedInt8*  pxPvRamUnscrambledStorageSize,
  TCsdUnsignedInt16   xPvLength
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdSetRamUnscrambledStorageSize():\n");
    msgbuf_strbuilder_setparam_hex_value  (&msgStrBuffer, "in: xPvLength", (size_t)xPvLength, sizeof(TCsdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer  (&msgStrBuffer, "in: pxPvRamUnscrambledStorageSize", (void*)pxPvRamUnscrambledStorageSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetRamUnscrambledStorageSize (pxPvRamUnscrambledStorageSize, xPvLength);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSetRamUnscrambledStorageSize():\n");
    if (pxPvRamUnscrambledStorageSize && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer  (&msgStrBuffer, "out: pxPvRamUnscrambledStorageSize", (void*)pxPvRamUnscrambledStorageSize, (size_t)xPvLength);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdEnableRamScrambling)
(
  void
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdEnableRamScrambling()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdEnableRamScrambling ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdEnableRamScrambling():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetScramblingActivationFlag)
(
  TCsdActivationFlag* pxScramblingActivationFlagState
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetScramblingActivationFlag():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxScramblingActivationFlagState", (void*)pxScramblingActivationFlagState);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetScramblingActivationFlag (pxScramblingActivationFlagState);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetScramblingActivationFlag():\n");
    if (pxScramblingActivationFlagState && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxScramblingActivationFlagState", (size_t)*pxScramblingActivationFlagState, sizeof(TCsdActivationFlag));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdEnableFlashProtection)
(
  void
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdEnableFlashProtection()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdEnableFlashProtection ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdEnableFlashProtection():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetFlashProtectionActivationFlag)
(
  TCsdActivationFlag* pxFlashProtectionActivationFlagState
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetFlashProtectionActivationFlag():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxFlashProtectionActivationFlagState", (void*)pxFlashProtectionActivationFlagState);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetFlashProtectionActivationFlag (pxFlashProtectionActivationFlagState);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetFlashProtectionActivationFlag():\n");
    if (pxFlashProtectionActivationFlagState && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxFlashProtectionActivationFlagState", (size_t)*pxFlashProtectionActivationFlagState, sizeof(TCsdActivationFlag));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdSelectDebugInterfaceProtectionLevel)
(
  TCsdDebugInterfaceAccessMode xDebugInterfaceProtectionLevel
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@csdSelectDebugInterfaceProtectionLevel():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDebugInterfaceProtectionLevel", (size_t)xDebugInterfaceProtectionLevel, sizeof(TCsdDebugInterfaceAccessMode));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdSelectDebugInterfaceProtectionLevel (xDebugInterfaceProtectionLevel);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdSelectDebugInterfaceProtectionLevel():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetDebugInterfaceProtectionLevel)
(
  TCsdDebugInterfaceAccessMode* pxDebugInterfaceProtectionLevel
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string         (&msgStrBuffer, ">@csdGetDebugInterfaceProtectionLevel():\n");
    msgbuf_strbuilder_setparam_pointer   (&msgStrBuffer, "in: pxDebugInterfaceProtectionLevel", (void*)pxDebugInterfaceProtectionLevel);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetDebugInterfaceProtectionLevel (pxDebugInterfaceProtectionLevel);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetDebugInterfaceProtectionLevel():\n");
    if (pxDebugInterfaceProtectionLevel && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxDebugInterfaceProtectionLevel", (size_t)*pxDebugInterfaceProtectionLevel, sizeof(TCsdDebugInterfaceAccessMode));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdDeactivateKeyLadder)
(
  void
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdDeactivateKeyLadder()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdDeactivateKeyLadder ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdDeactivateKeyLadder():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetKeyLadderDeactivationFlag)
(
 TCsdActivationFlag* pxKeyLadderDeactivationFlagState
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetKeyLadderDeactivationFlag():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxKeyLadderDeactivationFlagState", (void*)pxKeyLadderDeactivationFlagState);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetKeyLadderDeactivationFlag (pxKeyLadderDeactivationFlagState);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetKeyLadderDeactivationFlag():\n");
    if (pxKeyLadderDeactivationFlagState && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxKeyLadderDeactivationFlagState", (size_t)*pxKeyLadderDeactivationFlagState, sizeof(TCsdActivationFlag));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(csdGetDvrKey)
(
  TCsdUnsignedInt8    xDvrKey[16]
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@csdGetDvrKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDvrKey", (void*)&xDvrKey[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = csdGetDvrKey (xDvrKey);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@csdGetDvrKey():\n");
    if (xDvrKey && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xDvrKey", (void*)&xDvrKey[0], 16);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdInitialize) (void)
{
  TCsdStatus       csdStatus;
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string  (&msgStrBuffer, ">@nhtCsdInitialize()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdInitialize ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdInitialize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdTerminate) (void)
{
  TCsdStatus       csdStatus;
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string  (&msgStrBuffer, ">@nhtCsdTerminate()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdTerminate ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdTerminate():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdGetNhtCsdApiVersion)
(
  TCsdUnsignedInt32*  pxNhtCsdApiVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">#nhtCsdGetNhtCsdApiVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNhtCsdApiVersion", (void*)pxNhtCsdApiVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetNhtCsdApiVersion (pxNhtCsdApiVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<#nhtCsdGetNhtCsdApiVersion():\n");
    if (pxNhtCsdApiVersion && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxNhtCsdApiVersion", (size_t)*pxNhtCsdApiVersion, sizeof(TCsdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdGetCsdStatusOffsetValue)
(
  TCsdUnsignedInt32 * pxCsdOffsetValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">#nhtCsdGetCsdStatusOffsetValue():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxCsdOffsetValue", (void*)pxCsdOffsetValue);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetCsdStatusOffsetValue (pxCsdOffsetValue);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<#nhtCsdGetCsdStatusOffsetValue():\n");
    if (pxCsdOffsetValue && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxCsdOffsetValue", (size_t)*pxCsdOffsetValue, sizeof(TCsdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdGetCsdProtectingKeyNumber)
(
  TCsdUnsignedInt32 * pxProtectingKeyNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">#nhtCsdGetCsdProtectingKeyNumber():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxProtectingKeyNumber", (void*)pxProtectingKeyNumber);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetCsdProtectingKeyNumber (pxProtectingKeyNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<#nhtCsdGetCsdProtectingKeyNumber():\n");
    if (pxProtectingKeyNumber && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxProtectingKeyNumber", (size_t)*pxProtectingKeyNumber, sizeof(TCsdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetCertificationNOCSVersion)
(
  TCsdUnsignedInt32 * pxVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetCertificationNOCSVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxVersion", (void*)pxVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetCertificationNOCSVersion (pxVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetCertificationNOCSVersion():\n");
    if (pxVersion && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxVersion", (size_t)*pxVersion, sizeof(TCsdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetSoftwareVersion)
(
  TCsd20CharsString  xSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSoftwareVersion", (void*)&xSoftwareVersion[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetSoftwareVersion (xSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetSoftwareVersion():\n");
    if (xSoftwareVersion && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xSoftwareVersion", (void*)&xSoftwareVersion[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdGetChipManufacturerName)
(
  TCsd20CharsString xChipManufacturerName
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetChipManufacturerName():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xChipManufacturerName", (void*)&xChipManufacturerName[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetChipManufacturerName (xChipManufacturerName);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetChipManufacturerName():\n");
    if (xChipManufacturerName && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xChipManufacturerName", (void*)&xChipManufacturerName[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetChipName)
(
  TCsd20CharsString xChipName
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetChipName():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xChipName", (void*)&xChipName[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetChipName (xChipName);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetChipName():\n");
    if (xChipName && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xChipName", (void*)&xChipName[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetBootModeNumber)
(
  TNhtCsdBootModeNumber * pxBootModeNumber
)
{
  TMsgbufStrBuffer      msgStrBuffer;
  int                   callId;
  TCsdStatus            csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetBootModeNumber():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBootModeNumber", (void*)pxBootModeNumber);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetBootModeNumber (pxBootModeNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetBootModeNumber():\n");
    if (pxBootModeNumber && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxBootModeNumber", (size_t)*pxBootModeNumber, sizeof(TNhtCsdBootModeNumber));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdGetBootModeDescriptorSet)
(
  TNhtCsdBootModeNumber       xBootModeDescriptorNumber,
  TNhtCsdBootModeDescriptor * pxBootModeDescriptors,
  TNhtCsdBootModeNumber     * pxBootModeEffectiveNumber
)
{
  TMsgbufStrBuffer      msgStrBuffer;
  int                   callId;
  TCsdStatus            csdStatus;
  TNhtCsdBootModeNumber maxBootModeNumber;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetBootModeDescriptorSet():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xBootModeDescriptorNumber", (size_t)xBootModeDescriptorNumber, sizeof(TNhtCsdBootModeNumber));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBootModeDescriptors", (void*)pxBootModeDescriptors);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBootModeEffectiveNumber", (void*)pxBootModeEffectiveNumber);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetBootModeDescriptorSet (
    xBootModeDescriptorNumber,
    pxBootModeDescriptors,
    pxBootModeEffectiveNumber );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetBootModeDescriptorSet():\n");
    if (csdStatus == CSD_NO_ERROR)
    {
      if (pxBootModeEffectiveNumber)
      {
        msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxBootModeEffectiveNumber", (size_t)*pxBootModeEffectiveNumber, sizeof(TNhtCsdBootModeNumber));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

        if (xBootModeDescriptorNumber < *pxBootModeEffectiveNumber) maxBootModeNumber = xBootModeDescriptorNumber;
        else maxBootModeNumber = *pxBootModeEffectiveNumber;
      }
      else maxBootModeNumber = xBootModeDescriptorNumber;

      if (pxBootModeDescriptors)
      {
        TNhtCsdBootModeNumber i;

        for (i=0; i < maxBootModeNumber; i++)
        {
          msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: pxBootModeDescriptors[i].bootModeId", (size_t)pxBootModeDescriptors[i].bootModeId, sizeof(TCsdBootMode));
          msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

          msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxBootModeDescriptors[i].bootMemoryName", (void*)&pxBootModeDescriptors[i].bootMemoryName[0], sizeof(TCsd20CharsString));
          msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
        }
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetBootModeDescriptor)
(
  TCsdBootMode                xBootModeId,
  TNhtCsdBootModeDescriptor * pxBootModeDescriptor
)
{
  TMsgbufStrBuffer      msgStrBuffer;
  int                   callId;
  TCsdStatus            csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetBootModeDescriptor():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xBootModeId", (size_t)xBootModeId, sizeof(TCsdBootMode));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBootModeDescriptor", (void*)pxBootModeDescriptor);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetBootModeDescriptor (
    xBootModeId,
    pxBootModeDescriptor );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetBootModeDescriptor():\n");
    if (pxBootModeDescriptor && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: pxBootModeDescriptor->bootModeId", (size_t)pxBootModeDescriptor->bootModeId, sizeof(TCsdBootMode));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxBootModeDescriptor->bootMemoryName", (void*)&pxBootModeDescriptor->bootMemoryName[0], sizeof(TCsd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetScsExpectedPvValueSize)
(
  TCsdScsPvId         xScsPvParamsId,
  TCsdUnsignedInt16 * pxPvLength
)
{
  TMsgbufStrBuffer      msgStrBuffer;
  int                   callId;
  TCsdStatus            csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetScsExpectedPvValueSize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xScsPvParamsId", (size_t)xScsPvParamsId, sizeof(TCsdScsPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvLength", (void*)pxPvLength);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetScsExpectedPvValueSize (
    xScsPvParamsId,
    pxPvLength );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetScsExpectedPvValueSize():\n");
    if (pxPvLength && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxPvLength", (size_t)*pxPvLength, sizeof(TCsdUnsignedInt16));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdSetScsPv)
(
  TCsdScsPvId              xScsPvParamsId,
  TCsdUnsignedInt16        xPvLength,
  const TCsdUnsignedInt8 * pxPvValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdSetScsPv():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xScsPvParamsId", (size_t)xScsPvParamsId, sizeof(TCsdScsPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvLength", (size_t)xPvLength, sizeof(TCsdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvValue", (void*)pxPvValue, (size_t)xPvLength);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdSetScsPv (
    xScsPvParamsId,
    xPvLength,
    pxPvValue );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdSetScsPv():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdGetScsPv)
(
  TCsdScsPvId         xScsPvParamsId,
  TCsdUnsignedInt16   xPvLength,
  TCsdUnsignedInt8  * pxPvValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdGetScsPv():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xScsPvParamsId", (size_t)xScsPvParamsId, sizeof(TCsdScsPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvLength", (size_t)xPvLength, sizeof(TCsdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvValue", (void*)pxPvValue);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdGetScsPv (
    xScsPvParamsId,
    xPvLength,
    pxPvValue );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdGetScsPv():\n");
    if (pxPvValue && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxPvValue", (void*)pxPvValue, (size_t)xPvLength);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtcsdGetRamUnscrambledStorageSizeBufferLength)
(
  TCsdUnsignedInt16 * pxPvLength
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtcsdGetRamUnscrambledStorageSizeBufferLength():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvLength", (void*)pxPvLength);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtcsdGetRamUnscrambledStorageSizeBufferLength (pxPvLength);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtcsdGetRamUnscrambledStorageSizeBufferLength():\n");
    if (pxPvLength && (csdStatus == CSD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxPvLength", (size_t)*pxPvLength, sizeof(TCsdUnsignedInt16));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/***************************************************************************/
/*                                                                         */
/*               NOCS1.x RAM2RAM Functions                                 */
/*                                                                         */
/***************************************************************************/



/* */
TNhtCsdSysBufferHandle _CRPC(nhtCsdAllocateSysBuffer)
(
  TCsdSize xSize
)
{
  TMsgbufStrBuffer       msgStrBuffer;
  int                    callId;
  TNhtCsdSysBufferHandle sysBufferHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdAllocateSysBuffer():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xSize", (size_t)xSize, sizeof(TCsdSize));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  sysBufferHandle = nhtCsdAllocateSysBuffer (xSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdAllocateSysBuffer():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "ret: buffer", (void*)sysBufferHandle);
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return sysBufferHandle;
}

/* */
TCsdStatus _CRPC(nhtCsdDeallocateSysBuffer)
(
  TNhtCsdSysBufferHandle xNhtCsdSysBufferHandle
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdDeallocateSysBuffer():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xNhtCsdSysBufferHandle", (void*)xNhtCsdSysBufferHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdDeallocateSysBuffer (xNhtCsdSysBufferHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdDeallocateSysBuffer():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/***************************************************************************/
/*                                                                         */
/*                                    DSC                                  */
/*                                                                         */
/***************************************************************************/


/* */
typedef struct STraceEcmCallBackData
{
  TNhtDscEcmContentCallBack            ecmCallBackFct;
  TNhtCsdDscCallBackPrivateParameters  ecmCallBackPrivateData;
  TNhtCsdDscTestRunHandle              dscTestRunHandle;

} TTraceEcmCallBackData;


/* RPC method: rpc_nhtcsd_tn_ecmCallBack
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
static TCsdStatus TRACE_rpcEcmCallBackFunction
(
        TNhtCsdDscTestRunHandle               xDscTestRunHandle,
        TNhtCsdDscCallBackPrivateParameters   xPrivateParameters,
        TCsdUnsignedInt8                      xEcmTableId,
  const TCsdUnsignedInt8                    * pxEcmContent,
        TCsdSize                              xEcmContentSize
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TTraceEcmCallBackData    * pRpcDscHandle;
  TCsdStatus                 csdStatus = CSD_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdEcmCallback():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunHandle", (void*)xDscTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xPrivateParameters", (void*)xPrivateParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEcmTableId", (size_t)xEcmTableId, sizeof(TCsdUnsignedInt8));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEcmContentSize", (size_t)xEcmContentSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxEcmContent", (void*)pxEcmContent, (size_t)xEcmContentSize);
    RPC_FTRACE_ENTER_SERVER_CALL (callId, msgStrBuffer.pBuffer);
  }

  pRpcDscHandle = (TTraceEcmCallBackData*)xPrivateParameters;

  if (pRpcDscHandle)
  {
    if (pRpcDscHandle->ecmCallBackFct)
    {
      csdStatus = pRpcDscHandle->ecmCallBackFct (
        (TNhtCsdDscTestRunHandle)xPrivateParameters,
        pRpcDscHandle->ecmCallBackPrivateData,
        xEcmTableId,
        pxEcmContent,
        xEcmContentSize );
    }
  }

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdEcmCallback():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_SERVER_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdOpenDscTestRunSession)
(
  TNhtCsdDscTestRunParameters * pxDscTestRunParameters,
  TNhtCsdDscTestRunHandle     * pxDscTestRunHandle
)
{
  TMsgbufStrBuffer              msgStrBuffer;
  int                           callId;
  TCsdStatus                    csdStatus;
  TNhtCsdDscTestRunParameters   dscTestRunParameter;
  TNhtCsdDscTestRunParameters * pDscTestRunParameter = NULL;
  TTraceEcmCallBackData       * pEcmHandle = NULL;
  TNhtCsdDscTestRunHandle     * pDscTestRunHandle = NULL;

  pEcmHandle = (TTraceEcmCallBackData*)MSGBUF_SYS_malloc(sizeof(TTraceEcmCallBackData));
  pEcmHandle->ecmCallBackFct         = NULL;
  pEcmHandle->ecmCallBackPrivateData = NULL;
  pEcmHandle->dscTestRunHandle       = NULL;

  if (pxDscTestRunParameters)
  {
    MSGBUF_SYS_memcpy (&dscTestRunParameter, pxDscTestRunParameters, sizeof(TNhtCsdDscTestRunParameters));
    pDscTestRunParameter = &dscTestRunParameter;

    if ( pxDscTestRunParameters->ecmCallBackFct)
    {
      pEcmHandle->ecmCallBackFct = pxDscTestRunParameters->ecmCallBackFct;
      dscTestRunParameter.ecmCallBackFct = &TRACE_rpcEcmCallBackFunction;
    }

    if (pxDscTestRunParameters->ecmCallBackPrivateData)
    {
      pEcmHandle->ecmCallBackPrivateData = pxDscTestRunParameters->ecmCallBackPrivateData;
      dscTestRunParameter.ecmCallBackPrivateData = pEcmHandle;
    }
  }

  if (pxDscTestRunHandle) pDscTestRunHandle = &pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdOpenDscTestRunSession():\n");

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunParameters", (void*)pxDscTestRunParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    if (pxDscTestRunParameters)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->emi", (size_t)dscTestRunParameter.emi, sizeof(TCsdUnsignedInt16));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->audioPid", (size_t)dscTestRunParameter.audioPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->videoPid", (size_t)dscTestRunParameter.videoPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->pcrPid", (size_t)dscTestRunParameter.pcrPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->isInClear", (size_t)dscTestRunParameter.isInClear, sizeof(TCsdBoolean));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->ecmPid", (size_t)dscTestRunParameter.ecmPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxDscTestRunParameters->pInputFilePathname", (const char*)dscTestRunParameter.pInputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxDscTestRunParameters->pOutputFilePathname", (const char*)dscTestRunParameter.pOutputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->ivSize", (size_t)dscTestRunParameter.ivSize, sizeof(TCsdSize));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDscTestRunParameters->iv", (const void*)dscTestRunParameter.iv, pxDscTestRunParameters->ivSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunParameters->ecmCallBackFct", (const void*)(size_t)dscTestRunParameter.ecmCallBackFct);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunParameters->ecmCallBackPrivateData", (const void*)dscTestRunParameter.ecmCallBackPrivateData);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunHandle", (void*)&pEcmHandle->dscTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdOpenDscTestRunSession (
    pDscTestRunParameter,
    pDscTestRunHandle );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdOpenDscTestRunSession():\n");
    if (csdStatus == CSD_NO_ERROR)
    {
      if (pxDscTestRunHandle)
      {
        msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxDscTestRunHandle", (const void*)*pDscTestRunHandle);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (csdStatus != CSD_NO_ERROR)
    MSGBUF_SYS_free(pEcmHandle);
  else if (pxDscTestRunHandle)
    *pxDscTestRunHandle = (TNhtCsdDscTestRunHandle)pEcmHandle;

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return csdStatus;
}

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdStartDscTestRun)
(
  TNhtCsdDscTestRunHandle xDscTestRunHandle
)
{
  TMsgbufStrBuffer          msgStrBuffer;
  int                       callId;
  TNhtCsdTestRunStatus      csdTestRunStatus;
  TNhtCsdDscTestRunHandle   subDscTestRunHandle = NULL;
  TTraceEcmCallBackData   * pEcmHandle = (TTraceEcmCallBackData*)xDscTestRunHandle;

  if (pEcmHandle) subDscTestRunHandle = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdStartDscTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xDscTestRunHandle", (void*)subDscTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdTestRunStatus = nhtCsdStartDscTestRun (subDscTestRunHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdStartDscTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdTestRunStatus", (size_t)csdTestRunStatus, sizeof(TNhtCsdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdTestRunStatus;
}

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdWaitOnDscTestRunCompletion)
(
  TNhtCsdDscTestRunHandle xDscTestRunHandle,
  int                     xTimeout
)
{
  TMsgbufStrBuffer          msgStrBuffer;
  int                       callId;
  TNhtCsdTestRunStatus      csdTestRunStatus;
  TNhtCsdDscTestRunHandle   subDscTestRunHandle = NULL;
  TTraceEcmCallBackData   * pEcmHandle = (TTraceEcmCallBackData*)xDscTestRunHandle;

  if (pEcmHandle) subDscTestRunHandle = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdWaitOnDscTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xDscTestRunHandle", (void*)subDscTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "int: xTimeout", (size_t)xTimeout, sizeof(int));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdTestRunStatus = nhtCsdWaitOnDscTestRunCompletion (subDscTestRunHandle, xTimeout);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdWaitOnDscTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdTestRunStatus", (size_t)csdTestRunStatus, sizeof(TNhtCsdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdTestRunStatus;
}

/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdStopDscTestRun)
(
  TNhtCsdDscTestRunHandle xDscTestRunHandle
)
{
  TMsgbufStrBuffer          msgStrBuffer;
  int                       callId;
  TNhtCsdTestRunStatus      csdTestRunStatus;
  TNhtCsdDscTestRunHandle   subDscTestRunHandle = NULL;
  TTraceEcmCallBackData   * pEcmHandle = (TTraceEcmCallBackData*)xDscTestRunHandle;

  if (pEcmHandle) subDscTestRunHandle = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdStopDscTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunHandle", (void*)subDscTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdTestRunStatus = nhtCsdStopDscTestRun (subDscTestRunHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdStopDscTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdTestRunStatus", (size_t)csdTestRunStatus, sizeof(TNhtCsdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdTestRunStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdTestRunSetClearTextDscHostKeys)
(
        TNhtCsdDscTestRunHandle   xDscTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextDscOddHostKey,
        TCsdSize                  xClearTextDscOddHostKeySize,
  const TCsdUnsignedInt8        * pxClearTextDscEvenHostKey,
        TCsdSize                  xClearTextDscEvenHostKeySize
)
{
  TMsgbufStrBuffer          msgStrBuffer;
  int                       callId;
  TCsdStatus                csdStatus;
  TNhtCsdDscTestRunHandle   subDscTestRunHandle = NULL;
  TTraceEcmCallBackData   * pEcmHandle = (TTraceEcmCallBackData*)xDscTestRunHandle;

  if (pEcmHandle) subDscTestRunHandle = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdTestRunSetClearTextDscHostKeys():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunHandle", (void*)subDscTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextDscOddHostKeySize", (size_t)xClearTextDscOddHostKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextDscOddHostKey", (void*)pxClearTextDscOddHostKey, xClearTextDscOddHostKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextDscEvenHostKeySize", (size_t)xClearTextDscEvenHostKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextDscEvenHostKey", (void*)pxClearTextDscEvenHostKey, xClearTextDscEvenHostKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdTestRunSetClearTextDscHostKeys (
    subDscTestRunHandle,
    pxClearTextDscOddHostKey,
    xClearTextDscOddHostKeySize,
    pxClearTextDscEvenHostKey,
    xClearTextDscEvenHostKeySize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdTestRunSetClearTextDscHostKeys():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdTestRunSetProtectedDscContentKeys)
(
        TNhtCsdDscTestRunHandle         xDscTestRunHandle,
  const TNhtProtectingKey             * pxDscCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8              * pxCipheredDscOddContentKey,
        TCsdSize                        xCipheredDscOddContentKeySize,
  const TCsdUnsignedInt8              * pxCipheredDscEvenContentKey,
        TCsdSize                        xCipheredDscEvenContentKeySize
)
{
  TMsgbufStrBuffer          msgStrBuffer;
  int                       callId;
  TCsdStatus                csdStatus;
  TNhtCsdDscTestRunHandle   subDscTestRunHandle = NULL;
  TTraceEcmCallBackData   * pEcmHandle = (TTraceEcmCallBackData*)xDscTestRunHandle;

  if (pEcmHandle) subDscTestRunHandle = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdTestRunSetProtectedDscContentKeys():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunHandle", (void*)subDscTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDscCipheredProtectingKeys", (void*)&pxDscCipheredProtectingKeys[0][0], 16 * xCipheredProtectingKeyNumber);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xCipheredProtectingKeyNumber", (size_t)xCipheredProtectingKeyNumber, sizeof(TCsdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredDscOddContentKeySize", (size_t)xCipheredDscOddContentKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredDscOddContentKey", (void*)pxCipheredDscOddContentKey, (size_t)xCipheredDscOddContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredDscEvenContentKeySize", (size_t)xCipheredDscEvenContentKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredDscEvenContentKey", (void*)pxCipheredDscEvenContentKey, (size_t)xCipheredDscEvenContentKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdTestRunSetProtectedDscContentKeys (
    subDscTestRunHandle,
    pxDscCipheredProtectingKeys,
    xCipheredProtectingKeyNumber,
    pxCipheredDscOddContentKey,
    xCipheredDscOddContentKeySize,
    pxCipheredDscEvenContentKey,
    xCipheredDscEvenContentKeySize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdTestRunSetProtectedDscContentKeys():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdCloseDscTestRunSession)
(
  TNhtCsdDscTestRunHandle  xDscTestRunHandle
)
{
  TMsgbufStrBuffer          msgStrBuffer;
  int                       callId;
  TNhtCsdDscTestRunHandle  subDscTestRunHandle = NULL;
  TCsdStatus                csdStatus;
  TTraceEcmCallBackData   * pEcmHandle = (TTraceEcmCallBackData*)xDscTestRunHandle;

  if (pEcmHandle) subDscTestRunHandle = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdCloseDscTestRunSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunHandle", (void*)subDscTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdCloseDscTestRunSession (subDscTestRunHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdCloseDscTestRunSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  if ((csdStatus == CSD_NO_ERROR) && pEcmHandle) MSGBUF_SYS_free (pEcmHandle);
  return csdStatus;
}


/***************************************************************************/
/*                                                                         */
/*                                    SCR                                  */
/*                                                                         */
/***************************************************************************/

/* */

TCsdStatus _CRPC(nhtCsdOpenScrTestRunSession)
(
  const TNhtCsdScrTestRunParameters * pxScrTestRunParameters,
  TNhtCsdScrTestRunHandle           * pxScrTestRunHandle
)
{
  TMsgbufStrBuffer              msgStrBuffer;
  int                           callId;
  TCsdStatus                    csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdOpenScrTestRunSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxScrTestRunParameters", (void*)pxScrTestRunParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    if (pxScrTestRunParameters)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->emi", (size_t)pxScrTestRunParameters->emi, sizeof(TCsdUnsignedInt16));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->audioPid", (size_t)pxScrTestRunParameters->audioPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->videoPid", (size_t)pxScrTestRunParameters->videoPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->pcrPid", (size_t)pxScrTestRunParameters->pcrPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->isForEncryption", (size_t)pxScrTestRunParameters->isForEncryption, sizeof(TCsdBoolean));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxScrTestRunParameters->pInputFilePathname", (const char*)pxScrTestRunParameters->pInputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxScrTestRunParameters-->pOutputFilePathname", (const char*)pxScrTestRunParameters->pOutputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxScrTestRunHandle", (void*)pxScrTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus =  nhtCsdOpenScrTestRunSession (
    pxScrTestRunParameters,
    pxScrTestRunHandle );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdOpenScrTestRunSession():\n");
    if (csdStatus == CSD_NO_ERROR)
    {
      if (pxScrTestRunHandle)
      {
        msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxScrTestRunHandle", (const void*)*pxScrTestRunHandle);
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */

TNhtCsdTestRunStatus _CRPC(nhtCsdStartScrTestRun)
(
  TNhtCsdScrTestRunHandle xScrTestRunHandle
)
{
  TMsgbufStrBuffer        msgStrBuffer;
  int                     callId;
  TNhtCsdTestRunStatus    csdTestRunStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdStartScrTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xScrTestRunHandle", (void*)xScrTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdTestRunStatus = nhtCsdStartScrTestRun (xScrTestRunHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdStartScrTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdTestRunStatus", (size_t)csdTestRunStatus, sizeof(TNhtCsdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdTestRunStatus;
}


/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdWaitOnScrTestRunCompletion)
(
  TNhtCsdScrTestRunHandle xScrTestRunHandle,
  int                     xTimeout
)
{
  TMsgbufStrBuffer        msgStrBuffer;
  int                     callId;
  TNhtCsdTestRunStatus    csdTestRunStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdWaitOnScrTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xScrTestRunHandle", (void*)xScrTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "int: xTimeout", (size_t)xTimeout, sizeof(int));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdTestRunStatus = nhtCsdWaitOnScrTestRunCompletion (xScrTestRunHandle, xTimeout);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdWaitOnScrTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdTestRunStatus", (size_t)csdTestRunStatus, sizeof(TNhtCsdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdTestRunStatus;
}


/* */
TNhtCsdTestRunStatus _CRPC(nhtCsdStopScrTestRun)
(
  TNhtCsdScrTestRunHandle   xScrTestRunHandle
)
{
  TMsgbufStrBuffer        msgStrBuffer;
  int                     callId;
  TNhtCsdTestRunStatus    csdTestRunStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdStopScrTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xScrTestRunHandle", (void*)xScrTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdTestRunStatus = nhtCsdStopScrTestRun (xScrTestRunHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdStopScrTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdTestRunStatus", (size_t)csdTestRunStatus, sizeof(TNhtCsdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdTestRunStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdSetClearTextScrEncryptionKey)
(
        TNhtCsdScrTestRunHandle   xScrTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextScrHostKey,
        TCsdSize                  xClearTextScrHostKeySize,
  const TCsdUnsignedInt8        * pxInitializationVector,
        TCsdSize                  xInitializationVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdSetClearTextScrEncryptionKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunHandle", (void*)xScrTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextScrHostKeySize", (size_t)xClearTextScrHostKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextScrHostKey", (void*)pxClearTextScrHostKey, xClearTextScrHostKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (void*)pxInitializationVector, xInitializationVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdSetClearTextScrEncryptionKey (
    xScrTestRunHandle,
    pxClearTextScrHostKey,
    xClearTextScrHostKeySize,
    pxInitializationVector,
    xInitializationVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdSetClearTextScrEncryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}


/* */
TCsdStatus _CRPC(nhtCsdSetClearTextScrDecryptionKey)
(
        TNhtCsdScrTestRunHandle   xScrTestRunHandle,
  const TCsdUnsignedInt8        * pxClearTextScrHostKey,
        TCsdSize                  xClearTextScrHostKeySize,
  const TCsdUnsignedInt8        * pxInitializationVector,
        TCsdSize                  xInitializationVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdSetClearTextScrDecryptionKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunHandle", (void*)xScrTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xClearTextScrHostKeySize", (size_t)xClearTextScrHostKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxClearTextScrHostKey", (void*)pxClearTextScrHostKey, xClearTextScrHostKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (void*)pxInitializationVector, xInitializationVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdSetClearTextScrDecryptionKey (
    xScrTestRunHandle,
    pxClearTextScrHostKey,
    xClearTextScrHostKeySize,
    pxInitializationVector,
    xInitializationVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdSetClearTextScrDecryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdSetProtectedScrDecryptionKey)
(
        TNhtCsdScrTestRunHandle         xScrTestRunHandle,
  const TNhtProtectingKey             * pxScrCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdSetProtectedScrDecryptionKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunHandle", (void*)xScrTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxScrCipheredProtectingKeys", (void*)&pxScrCipheredProtectingKeys[0][0], 16 * xCipheredProtectingKeyNumber);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeyNumber", (size_t)xCipheredProtectingKeyNumber, sizeof(TCsdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredScrContentKeySize", (size_t)xCipheredScrContentKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredScrContentKey", (void*)pxCipheredScrContentKey, (size_t)xCipheredScrContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdSetProtectedScrDecryptionKey (
    xScrTestRunHandle,
    pxScrCipheredProtectingKeys,
    xCipheredProtectingKeyNumber,
    pxCipheredScrContentKey,
    xCipheredScrContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdSetProtectedScrDecryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdSetProtectedScrEncryptionKey)
(
        TNhtCsdScrTestRunHandle         xScrTestRunHandle,
  const TNhtProtectingKey             * pxScrCipheredProtectingKeys,
        TCsdUnsignedInt32               xCipheredProtectingKeyNumber,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdSetProtectedScrEncryptionKey():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunHandle", (void*)xScrTestRunHandle);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxScrCipheredProtectingKeys", (void*)&pxScrCipheredProtectingKeys[0][0], 16 * xCipheredProtectingKeyNumber);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeyNumber", (size_t)xCipheredProtectingKeyNumber, sizeof(TCsdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredScrContentKeySize", (size_t)xCipheredScrContentKeySize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredScrContentKey", (void*)pxCipheredScrContentKey, (size_t)xCipheredScrContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCsdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdSetProtectedScrEncryptionKey (
    xScrTestRunHandle,
    pxScrCipheredProtectingKeys,
    xCipheredProtectingKeyNumber,
    pxCipheredScrContentKey,
    xCipheredScrContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdSetProtectedScrEncryptionKey():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

/* */
TCsdStatus _CRPC(nhtCsdCloseScrTestRunSession)
(
  TNhtCsdScrTestRunHandle xScrTestRunHandle
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCsdStatus       csdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCsdCloseScrTestRunSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunHandle", (void*)xScrTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  csdStatus = nhtCsdCloseScrTestRunSession (xScrTestRunHandle);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCsdCloseScrTestRunSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: csdStatus", (size_t)csdStatus, sizeof(TCsdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return csdStatus;
}

#endif /* _NHT_RPC_TRACE_ON_ */
