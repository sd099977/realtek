/**
**  @file nocs_nhtctd.c
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset harness tests
**
**    This header file describes the API of the CTD driver API
**    that need to be implemented by the Chipset Manufacturer in
**    order to be able to comply with the Harness test toolkit provided by
**    Nagra.
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


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_strbuilder.h"
#include "inc/TRACE_nhtctd.h"


/******************************************************************************/
/*                                                                            */
/*                    CTD Resource Initialization                             */
/*                                                                            */
/******************************************************************************/

#ifdef _NHT_RPC_TRACE_ON_

/* */
TCtdStatus _CRPC(nhtCtdInitialize) (void)
{
  TCtdStatus       ctdStatus;
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string  (&msgStrBuffer, ">@nhtCtdInitialize()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdInitialize ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdInitialize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret:ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdTerminate) (void)
{
  TCtdStatus       ctdStatus;
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string  (&msgStrBuffer, ">@nhtCtdTerminate()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdTerminate ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdTerminate():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret:ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdGetSoftwareVersion)
(
  TCtd20CharsString  xSoftwareVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetSoftwareVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSoftwareVersion", (void*)&xSoftwareVersion[0]);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetSoftwareVersion (xSoftwareVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetSoftwareVersion():\n");
    if (xSoftwareVersion && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: xSoftwareVersion", (void*)&xSoftwareVersion[0], sizeof(TCtd20CharsString));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdGetApiVersion)
(
  TCtdUnsignedInt32*  pxNhtCtdApiVersion
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">#nhtCtdGetApiVersion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxNhtCtdApiVersion", (void*)pxNhtCtdApiVersion);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetApiVersion (pxNhtCtdApiVersion);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<#nhtCtdGetApiVersion():\n");

    if (pxNhtCtdApiVersion && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxNhtCtdApiVersion", (size_t)*pxNhtCtdApiVersion, sizeof(TCtdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
void _CRPC(nhtCtdChipReset)
(
  TCtdResetType xResetType
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string  (&msgStrBuffer, ">@nhtCtdChipReset()");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xResetType", (size_t)xResetType, sizeof(TCtdResetType));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  nhtCtdChipReset (xResetType);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdChipReset()");
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return;
}

/* */
void _CRPC(nhtCtdChipSuspend2Ram) (void)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdChipSuspend2Ram()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  nhtCtdChipSuspend2Ram ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdChipSuspend2Ram()");
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return;
}

/* */
TCtdStatus _CRPC(nhtCtdSetBootMode)
(
  TCtdFlashType xBootFlashType
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetBootMode():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xBootFlashType", (size_t)xBootFlashType, sizeof(TCtdFlashType));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetBootMode (xBootFlashType);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetBootMode():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetBootMode)
(
  TCtdFlashType * pxBootFlashType
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetBootMode():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxBootFlashType", (void*)pxBootFlashType);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetBootMode (pxBootFlashType);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetBootMode():\n");
    if (pxBootFlashType && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxBootFlashType", (size_t)*pxBootFlashType, sizeof(TCtdFlashType));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdSetDebugInterfaceMode)
(
  TCtdDifMode xDifMode
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetDebugInterfaceMode():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xDifMode", (size_t)xDifMode, sizeof(TCtdDifMode));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetDebugInterfaceMode (xDifMode);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetDebugInterfaceMode():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetDebugInterfaceMode)
(
  TCtdDifMode * pxDifMode
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetDebugInterfaceMode():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDifMode", (void*)pxDifMode);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetDebugInterfaceMode (pxDifMode);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetDebugInterfaceMode():\n");
    if (pxDifMode && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxDifMode", (size_t)*pxDifMode, sizeof(TCtdDifMode));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdEnableRamScrambling)
(
  void
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdEnableRamScrambling()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdEnableRamScrambling ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdEnableRamScrambling():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdDisableRamScrambling)
(
  void
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdDisableRamScrambling()");
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdDisableRamScrambling ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdDisableRamScrambling():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdIsRamScramblingEnabled)
(
  TCtdBoolean * pxIsEnabled
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdIsRamScramblingEnabled():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxIsEnabled", (void*)pxIsEnabled);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdIsRamScramblingEnabled (pxIsEnabled);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdIsRamScramblingEnabled():\n");
    if (pxIsEnabled && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxIsEnabled", (size_t)*pxIsEnabled, sizeof(TCtdBoolean));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetFlashMemorySize)
(
  TCtdFlashType   xFlashType,
  TCtdSize      * pxMemorySize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetFlashMemorySize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xFlashType", (size_t)xFlashType, sizeof(TCtdFlashType));
     msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMemorySize", (void*)pxMemorySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetFlashMemorySize (xFlashType, pxMemorySize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetFlashMemorySize():\n");
    if (pxMemorySize && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxMemorySize", (size_t)*pxMemorySize, sizeof(TCtdSize));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdFlashRead)
(
  TCtdFlashType      xFlashType,
  TCtdSize           xAddress,
  TCtdSize           xDataSize,
  TCtdUnsignedInt8 * pxData
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdFlashRead():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xFlashType", (size_t)xFlashType, sizeof(TCtdFlashType));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xAddress", (size_t)xAddress, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xDataSize", (size_t)xDataSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxData", (void*)pxData);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdFlashRead (
    xFlashType,
    xAddress,
    xDataSize,
    pxData );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdFlashRead():\n");
    if (pxData && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxData", (void*)pxData, xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdFlashWrite)
(
        TCtdFlashType      xFlashType,
        TCtdSize           xAddress,
        TCtdSize           xDataSize,
  const TCtdUnsignedInt8 * pxData
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdFlashWrite():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xFlashType", (size_t)xFlashType, sizeof(TCtdFlashType));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xAddress", (size_t)xAddress, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xDataSize", (size_t)xDataSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxData", (void*)pxData, (size_t)xDataSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdFlashWrite (
    xFlashType,
    xAddress,
    xDataSize,
    pxData );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdFlashWrite():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdGetRamMemorySize)
(
  TCtdSize * pxMemorySize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetRamMemorySize():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMemorySize", (void*)pxMemorySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetRamMemorySize (pxMemorySize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetRamMemorySize():\n");
    if (pxMemorySize && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxMemorySize", (size_t)*pxMemorySize, sizeof(TCtdSize));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdRamRead)
(
  TCtdSize           xAddress,
  TCtdSize           xDataSize,
  TCtdUnsignedInt8 * pxData
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdRamRead():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xAddress", (size_t)xAddress, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xDataSize", (size_t)xDataSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxData", (void*)pxData);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdRamRead (
    xAddress,
    xDataSize,
    pxData );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdRamRead():\n");
    if (pxData && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxData", (void*)pxData, (size_t)xDataSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdRamWrite)
(
  TCtdSize                 xAddress,
  TCtdSize                 xDataSize,
  const TCtdUnsignedInt8 * pxData
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdRamWrite():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xAddress", (size_t)xAddress, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xDataSize", (size_t)xDataSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxData", (void*)pxData, (size_t)xDataSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdRamWrite (
    xAddress,
    xDataSize,
    pxData );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdRamWrite():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetSpecificPvDescriptorNumber)
(
  TCtdUnsignedInt32 * pxSpecificPvNumber
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetSpecificPvDescriptorNumber():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSpecificPvNumber", (void*)pxSpecificPvNumber);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetSpecificPvDescriptorNumber (pxSpecificPvNumber);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetSpecificPvDescriptorNumber():\n");
    if (pxSpecificPvNumber && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxSpecificPvNumber", (size_t)*pxSpecificPvNumber, sizeof(TCtdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdGetSpecificPvDescriptorSet)
(
  TCtdUnsignedInt32          xSpecificPvNumber,
  TCtdSpecificPvDescriptor * pxSpecificPvDescriptors,
  TCtdUnsignedInt32        * pxSpecificPvEffectiveNumber
)
{
  TMsgbufStrBuffer  msgStrBuffer;
  int               callId;
  TCtdStatus        ctdStatus;
  TCtdUnsignedInt32 maxPvNumber;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetSpecificPvDescriptorSet():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xSpecificPvNumber", (size_t)xSpecificPvNumber, sizeof(TCtdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSpecificPvDescriptors", (void*)pxSpecificPvDescriptors);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSpecificPvEffectiveNumber", (void*)pxSpecificPvEffectiveNumber);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetSpecificPvDescriptorSet (
    xSpecificPvNumber,
    pxSpecificPvDescriptors,
    pxSpecificPvEffectiveNumber );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetSpecificPvDescriptorSet():\n");
    if (ctdStatus == CTD_NO_ERROR)
    {
      if (pxSpecificPvEffectiveNumber)
      {
        msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out: *pxSpecificPvEffectiveNumber", (size_t)*pxSpecificPvEffectiveNumber, sizeof(TCtdUnsignedInt32));
        msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

        if (xSpecificPvNumber < *pxSpecificPvEffectiveNumber) maxPvNumber = xSpecificPvNumber;
        else maxPvNumber = *pxSpecificPvEffectiveNumber;
      }
      else maxPvNumber = xSpecificPvNumber;

      if (pxSpecificPvDescriptors)
      {
        TCtdUnsignedInt32 i;

        for (i=0; i < maxPvNumber; i++)
        {
          msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "out:pxSpecificPvDescriptors[i].pvId", (size_t)pxSpecificPvDescriptors[i].pvId, sizeof(TCtdPvId));
          msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

          msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "out: pxSpecificPvDescriptors[i].pvIdName", (void*)&pxSpecificPvDescriptors[i].pvIdName[0], sizeof(TCtd20CharsString));
          msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
        }
      }
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetPvStatus)
(
  TCtdPvId          xPvId,
  TCtdPvSetStatus * pxPvSetStatus
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetPvStatus():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvSetStatus", (void*)pxPvSetStatus);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetPvStatus (xPvId, pxPvSetStatus);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetPvStatus():\n");
    if (pxPvSetStatus && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxPvSetStatus", (size_t)*pxPvSetStatus, sizeof(TCtdPvSetStatus));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdGetPvBufferSize)
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32 * pxPvBufferSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetPvBufferSize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvBufferSize", (void*)pxPvBufferSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetPvBufferSize (xPvId, pxPvBufferSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetPvBufferSize():\n");
    if (pxPvBufferSize && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxPvBufferSize", (size_t)*pxPvBufferSize, sizeof(TCtdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdSetPv)
(
  TCtdPvId                  xPvId,
  TCtdUnsignedInt32         xPvBufferSize,
  const TCtdUnsignedInt8  * pxPvBufferValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetPv():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvBufferSize", (size_t)xPvBufferSize, sizeof(TCtdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvBufferValue", (void*)pxPvBufferValue, (size_t)xPvBufferSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetPv (xPvId, xPvBufferSize, pxPvBufferValue);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetPv():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetPv)
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvBufferSize,
  TCtdUnsignedInt8  * pxPvBufferValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetPv():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvBufferSize", (size_t)xPvBufferSize, sizeof(TCtdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvBufferValue", (void*)pxPvBufferValue);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus =nhtCtdGetPv (xPvId, xPvBufferSize, pxPvBufferValue);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetPv():\n");
    if (pxPvBufferValue && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvBufferValue", (void*)pxPvBufferValue, xPvBufferSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetOtpBufferSize)
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32 * pxPvBufferSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetOtpBufferSize():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvBufferSize", (void*)pxPvBufferSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetOtpBufferSize (xPvId, pxPvBufferSize);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetOtpBufferSize():\n");
    if (pxPvBufferSize && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: *pxPvBufferSize", (size_t)*pxPvBufferSize, sizeof(TCtdUnsignedInt32));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdGetOtpValueMask)
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvMaskSize,
  TCtdUnsignedInt8  * pxMask
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetOtpValueMask():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvMaskSize", (size_t)xPvMaskSize, sizeof(TCtdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxMask", (void*)pxMask);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetOtpValueMask (xPvId, xPvMaskSize, pxMask);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetOtpValueMask():\n");
    if (pxMask && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxMask", (void*)pxMask, xPvMaskSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdSetOtp)
(
  TCtdPvId                 xPvId,
  TCtdUnsignedInt32        xPvBufferSize,
  const TCtdUnsignedInt8 * pxPvBufferValue,
  const TCtdUnsignedInt8 * pxPvBufferMask
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetOtp():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvBufferSize", (size_t)xPvBufferSize, sizeof(TCtdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvBufferValue", (void*)pxPvBufferValue,  (size_t)xPvBufferSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvBufferMask", (void*)pxPvBufferMask,  (size_t)xPvBufferSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetOtp (
    xPvId,
    xPvBufferSize,
    pxPvBufferValue,
    pxPvBufferMask );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetOtp():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdGetOtp)
(
  TCtdPvId            xPvId,
  TCtdUnsignedInt32   xPvBufferSize,
  TCtdUnsignedInt8  * pxPvBufferValue
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdGetOtp():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvId", (size_t)xPvId, sizeof(TCtdPvId));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xPvBufferSize", (size_t)xPvBufferSize, sizeof(TCtdUnsignedInt32));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxPvBufferValue", (void*)pxPvBufferValue);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdGetOtp (xPvId, xPvBufferSize, pxPvBufferValue);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdGetPv():\n");
    if (pxPvBufferValue && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxPvBufferValue", (void*)pxPvBufferValue, xPvBufferSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdOpenR2rEncryptSession)
(
  TCtdR2RSession * pxSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdOpenR2rEncryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSession", (void*)pxSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdOpenR2rEncryptSession (pxSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdOpenR2rEncryptSession():\n");
    if (pxSession && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdOpenR2rDecryptSession)
(
  TCtdR2RSession * pxSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdOpenR2rDecryptSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxSession", (void*)pxSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdOpenR2rDecryptSession (pxSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdOpenR2rDecryptSession():\n");
    if (pxSession && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: *pxSession", (void*)*pxSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdCloseR2rSession)
(
  TCtdR2RSession  xSession
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdCloseR2rSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdCloseR2rSession (xSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdCloseR2rSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdSetR2RProtectedKeys)
(
  TCtdR2RSession           xSession,
  TCtdUnsignedInt16        xKeyEmi,
  TCtdSize                 xCipheredContentKeySize,
  const TCtdUnsignedInt8 * pxCipheredContentKey,
  TCtdSize                 xCipheredProtectingKeySize,
  const TCtdUnsignedInt8 * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8 * pxL2CipheredProtectingKey
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetR2RProtectedKeys():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyEmi", (size_t)xKeyEmi, sizeof(TCtdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredContentKeySize", (size_t)xCipheredContentKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredContentKey", (void*)pxCipheredContentKey, (size_t)xCipheredContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeySize", (size_t)xCipheredProtectingKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxL1CipheredProtectingKey", (void*)pxL1CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxL2CipheredProtectingKey", (void*)pxL2CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetR2RProtectedKeys (
    xSession,
    xKeyEmi,
    xCipheredContentKeySize,
    pxCipheredContentKey,
    xCipheredProtectingKeySize,
    pxL1CipheredProtectingKey,
    pxL2CipheredProtectingKey );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetR2RProtectedKeys():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdR2rSessionCryptoProcess)
(
  TCtdR2RSession           xSession,
  TCtdUnsignedInt16        xEmi,
  const TCtdUnsignedInt8 * pxInput,
  TCtdUnsignedInt8       * pxOutput,
  TCtdSize                 xMessageSize,
  const TCtdUnsignedInt8 * pxInitVector,
  TCtdSize                 xInitVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdR2rSessionCryptoProcess():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xSession", (void*)xSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEmi", (size_t)xEmi, sizeof(TCtdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xMessageSize", (size_t)xMessageSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInput", (void*)pxInput, (size_t)xMessageSize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:pxOutput", (void*)pxInput);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitVectorSize", (size_t)xInitVectorSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitVector", (void*)pxInitVector, (size_t)xInitVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdR2rSessionCryptoProcess (
    xSession,
    xEmi,
    pxInput,
    pxOutput,
    xMessageSize,
    pxInitVector,
    xInitVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdR2rSessionCryptoProcess():\n");
    if (pxOutput && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxOutput", (void*)pxOutput, (size_t)xMessageSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/******************************************************************************/
/*                                                                            */
/*                                    DSC                                     */
/*                                                                            */
/******************************************************************************/


/* */
typedef struct SCtdTraceEcmCallBackData
{
  TNhtCtdDscEcmCallBack             ecmCallBackFct;
  TCtdDscCallBackPrivateParameters  ecmCallBackPrivateData;
  TCtdDscTestRunSession             dscTestRunHandle;

} TCtdTraceEcmCallBackData;


/* RPC method: rpc_nhtcsd_tn_ecmCallBack
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
static TCtdStatus TRACE_ctdRpcEcmCallBackFunction
(
  TCtdDscTestRunSession              xDscTestRunSession,
  TCtdDscCallBackPrivateParameters   xPrivateParameters,
  TCtdUnsignedInt8                   xEcmTableId,
  const TCtdUnsignedInt8           * pxEcmContent,
  TCtdSize                           xEcmContentSize
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TCtdTraceEcmCallBackData * pRpcDscHandle;
  TCtdStatus                 ctdStatus = CTD_ERROR;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdEcmCallback():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunSession", (void*)xDscTestRunSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xPrivateParameters", (void*)xPrivateParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEcmTableId", (size_t)xEcmTableId, sizeof(TCtdUnsignedInt8));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xEcmContentSize", (size_t)xEcmContentSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxEcmContent", (void*)pxEcmContent, (size_t)xEcmContentSize);
    RPC_FTRACE_ENTER_SERVER_CALL (callId, msgStrBuffer.pBuffer);
  }

  pRpcDscHandle = (TCtdTraceEcmCallBackData*)xPrivateParameters;

  if (pRpcDscHandle)
  {
    if (pRpcDscHandle->ecmCallBackFct)
    {
      ctdStatus = pRpcDscHandle->ecmCallBackFct (
        (TCtdDscTestRunSession)xPrivateParameters,
        pRpcDscHandle->ecmCallBackPrivateData,
        xEcmTableId,
        pxEcmContent,
        xEcmContentSize );
    }
  }

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdEcmCallback():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_SERVER_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdOpenDscTestRunSession)
(
  TCtdDscTestRunParameters * pxDscTestRunParameters,
  TCtdDscTestRunSession    * pxDscTestRunSession
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TCtdStatus                 ctdStatus;
  TCtdDscTestRunParameters   dscTestRunParameter;
  TCtdDscTestRunParameters * pDscTestRunParameter = NULL;
  TCtdTraceEcmCallBackData * pEcmHandle = NULL;
  TCtdDscTestRunSession    * pDscTestRunHandle = NULL;


  pEcmHandle = (TCtdTraceEcmCallBackData*)MSGBUF_SYS_malloc(sizeof(TCtdTraceEcmCallBackData));
  pEcmHandle->ecmCallBackFct         = NULL;
  pEcmHandle->ecmCallBackPrivateData = NULL;
  pEcmHandle->dscTestRunHandle       = NULL;

  if (pxDscTestRunParameters)
  {
    MSGBUF_SYS_memcpy (&dscTestRunParameter, pxDscTestRunParameters, sizeof(TCtdDscTestRunParameters));
    pDscTestRunParameter = &dscTestRunParameter;

    if ( pxDscTestRunParameters->ecmCallBackFct)
    {
      pEcmHandle->ecmCallBackFct = pxDscTestRunParameters->ecmCallBackFct;
      dscTestRunParameter.ecmCallBackFct = &TRACE_ctdRpcEcmCallBackFunction;
    }

    if (pxDscTestRunParameters->ecmCallBackPrivateData)
    {
      pEcmHandle->ecmCallBackPrivateData = pxDscTestRunParameters->ecmCallBackPrivateData;
      dscTestRunParameter.ecmCallBackPrivateData = pEcmHandle;
    }
  }

  if (pxDscTestRunSession) pDscTestRunHandle = &pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdOpenDscTestRunSession():\n");

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunParameters", (void*)pxDscTestRunParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    if (pxDscTestRunParameters)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->engineEmi", (size_t)dscTestRunParameter.engineEmi, sizeof(TCtdUnsignedInt16));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->audioPid", (size_t)dscTestRunParameter.audioPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->videoPid", (size_t)dscTestRunParameter.videoPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->pcrPid", (size_t)dscTestRunParameter.pcrPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->isInClear", (size_t)dscTestRunParameter.isInClear, sizeof(TCtdBoolean));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->isForEncryption", (size_t)dscTestRunParameter.isForEncryption, sizeof(TCtdBoolean));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->ecmPid", (size_t)dscTestRunParameter.ecmPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxDscTestRunParameters->pInputFilePathname", (const char*)dscTestRunParameter.pInputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxDscTestRunParameters->pOutputFilePathname", (const char*)dscTestRunParameter.pOutputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxDscTestRunParameters->ivSize", (size_t)dscTestRunParameter.ivSize, sizeof(TCtdSize));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxDscTestRunParameters->pIv", (const void*)dscTestRunParameter.pIv, pxDscTestRunParameters->ivSize);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunParameters->ecmCallBackFct", (const void*)(size_t)dscTestRunParameter.ecmCallBackFct);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunParameters->ecmCallBackPrivateData", (const void*)dscTestRunParameter.ecmCallBackPrivateData);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxDscTestRunSession", (void*)&pEcmHandle->dscTestRunHandle);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdOpenDscTestRunSession (
    pDscTestRunParameter,
    pDscTestRunHandle );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdOpenDscTestRunSession():\n");
    if (pxDscTestRunSession && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxDscTestRunHandle", (const void*)*pDscTestRunHandle);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  if (ctdStatus != CTD_NO_ERROR)
    MSGBUF_SYS_free(pEcmHandle);
  else if (pxDscTestRunSession)
    *pxDscTestRunSession = (TCtdDscTestRunSession)pEcmHandle;

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  return ctdStatus;
}


/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStartDscTestRun)
(
  TCtdDscTestRunSession xDscTestRunSession
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TNhtCtdTestRunStatus       ctdTestRunStatus;
  TCtdDscTestRunSession      subDscTestRunSession = NULL;
  TCtdTraceEcmCallBackData * pEcmHandle = (TCtdTraceEcmCallBackData*)xDscTestRunSession;

  if (pEcmHandle) subDscTestRunSession = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdStartDscTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunSession", (void*)subDscTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdTestRunStatus = nhtCtdStartDscTestRun (subDscTestRunSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdStartDscTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdTestRunStatus", (size_t)ctdTestRunStatus, sizeof(TNhtCtdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdTestRunStatus;
}

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdWaitOnDscTestRunCompletion)
(
  TCtdDscTestRunSession xDscTestRunSession,
  int                   xTimeout
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TNhtCtdTestRunStatus       ctdTestRunStatus;
  TCtdDscTestRunSession      subDscTestRunSession = NULL;
  TCtdTraceEcmCallBackData * pEcmHandle = (TCtdTraceEcmCallBackData*)xDscTestRunSession;

  if (pEcmHandle) subDscTestRunSession = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdWaitOnDscTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunSession", (void*)subDscTestRunSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "int: xTimeout", (size_t)xTimeout, sizeof(int));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdTestRunStatus = nhtCtdWaitOnDscTestRunCompletion (subDscTestRunSession, xTimeout);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdWaitOnDscTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdTestRunStatus", (size_t)ctdTestRunStatus, sizeof(TNhtCtdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdTestRunStatus;
}

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStopDscTestRun)
(
  TCtdDscTestRunSession xDscTestRunSession
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TNhtCtdTestRunStatus       ctdTestRunStatus;
  TCtdDscTestRunSession      subDscTestRunSession = NULL;
  TCtdTraceEcmCallBackData * pEcmHandle = (TCtdTraceEcmCallBackData*)xDscTestRunSession;

  if (pEcmHandle) subDscTestRunSession = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdStopDscTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunSession", (void*)subDscTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdTestRunStatus = nhtCtdStopDscTestRun (subDscTestRunSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdStopDscTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdTestRunStatus", (size_t)ctdTestRunStatus, sizeof(TNhtCtdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdTestRunStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdSetDscProtectedKeys)
(
        TCtdDscTestRunSession   xDscTestRunSession,
        TCtdUnsignedInt16       xKeyEmi,
        TCtdSize                xCipheredProtectingKeySize,
  const TCtdUnsignedInt8      * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8      * pxL2CipheredProtectingKey,
  const TCtdUnsignedInt8      * pxCipheredDscOddContentKey,
        TCtdSize                xCipheredDscOddContentKeySize,
  const TCtdUnsignedInt8      * pxCipheredDscEvenContentKey,
        TCtdSize                xCipheredDscEvenContentKeySize
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TCtdStatus                 ctdStatus;
  TCtdDscTestRunSession      subDscTestRunSession = NULL;
  TCtdTraceEcmCallBackData * pEcmHandle = (TCtdTraceEcmCallBackData*)xDscTestRunSession;

  if (pEcmHandle) subDscTestRunSession = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetDscProtectedKeys():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunSession", (void*)subDscTestRunSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xKeyEmi", (size_t)xKeyEmi, sizeof(TCtdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in:xCipheredProtectingKeySize", (size_t)xCipheredProtectingKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxL1CipheredProtectingKey", (void*)pxL1CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxL2CipheredProtectingKey", (void*)pxL2CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredDscOddContentKeySize", (size_t)xCipheredDscOddContentKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredDscOddContentKey", (void*)pxCipheredDscOddContentKey,  (size_t)xCipheredDscOddContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredDscEvenContentKeySize", (size_t)xCipheredDscEvenContentKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredDscEvenContentKey", (void*)pxCipheredDscEvenContentKey, (size_t)xCipheredDscEvenContentKeySize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetDscProtectedKeys (
    subDscTestRunSession,
    xKeyEmi,
    xCipheredProtectingKeySize,
    pxL1CipheredProtectingKey,
    pxL2CipheredProtectingKey,
    pxCipheredDscOddContentKey,
    xCipheredDscOddContentKeySize,
    pxCipheredDscEvenContentKey,
    xCipheredDscEvenContentKeySize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetDscProtectedKeys():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

/* */
TCtdStatus _CRPC(nhtCtdCloseDscTestRunSession)
(
  TCtdDscTestRunSession xDscTestRunSession
)
{
  TMsgbufStrBuffer           msgStrBuffer;
  int                        callId;
  TCtdDscTestRunSession      subDscTestRunSession = NULL;
  TCtdStatus                 ctdStatus;
  TCtdTraceEcmCallBackData * pEcmHandle = (TCtdTraceEcmCallBackData*)xDscTestRunSession;

  if (pEcmHandle) subDscTestRunSession = pEcmHandle->dscTestRunHandle;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdCloseDscTestRunSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xDscTestRunHandle", (void*)subDscTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdCloseDscTestRunSession (subDscTestRunSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdCloseDscTestRunSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);

  if ((ctdStatus == CTD_NO_ERROR) && pEcmHandle) MSGBUF_SYS_free (pEcmHandle);
  return ctdStatus;
}

/***************************************************************************/
/*                                                                         */
/*                                    SCR                                  */
/*                                                                         */
/***************************************************************************/


/* */
TCtdStatus _CRPC(nhtCtdOpenScrTestRunSession)
(
  const TNhtCtdScrTestRunParameters * pxScrTestRunParameters,
  TNhtCtdScrTestRunSession          * pxScrTestRunSession
)
{
  TMsgbufStrBuffer              msgStrBuffer;
  int                           callId;
  TCtdStatus                    ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdOpenScrTestRunSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxScrTestRunParameters", (void*)pxScrTestRunParameters);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

    if (pxScrTestRunParameters)
    {
      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->engineEmi", (size_t)pxScrTestRunParameters->engineEmi, sizeof(TCtdUnsignedInt16));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->audioPid", (size_t)pxScrTestRunParameters->audioPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->videoPid", (size_t)pxScrTestRunParameters->videoPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->pcrPid", (size_t)pxScrTestRunParameters->pcrPid, sizeof(int));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: pxScrTestRunParameters->isForEncryption", (size_t)pxScrTestRunParameters->isForEncryption, sizeof(TCtdBoolean));
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxScrTestRunParameters->pInputFilePathname", (const char*)pxScrTestRunParameters->pInputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");

      msgbuf_strbuilder_setparam_string (&msgStrBuffer, "in: pxScrTestRunParameters-->pOutputFilePathname", (const char*)pxScrTestRunParameters->pOutputFilePathname);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: pxScrTestRunSession", (void*)pxScrTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus =  nhtCtdOpenScrTestRunSession (
    pxScrTestRunParameters,
    pxScrTestRunSession );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdOpenScrTestRunSession():\n");
    if (pxScrTestRunSession && (ctdStatus == CTD_NO_ERROR))
    {
      msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "out: *pxScrTestRunSession", (const void*)*pxScrTestRunSession);
      msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    }

    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */

TNhtCtdTestRunStatus _CRPC(nhtCtdStartScrTestRun)
(
  TNhtCtdScrTestRunSession xScrTestRunSession
)
{
  TMsgbufStrBuffer     msgStrBuffer;
  int                  callId;
  TNhtCtdTestRunStatus ctdTestRunStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdStartScrTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xScrTestRunSession", (void*)xScrTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdTestRunStatus = nhtCtdStartScrTestRun (xScrTestRunSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdStartScrTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdTestRunStatus", (size_t)ctdTestRunStatus, sizeof(TNhtCtdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdTestRunStatus;
}

/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdWaitOnScrTestRunCompletion)
(
  TNhtCtdScrTestRunSession xScrTestRunSession,
  int                      xTimeout
)
{
  TMsgbufStrBuffer     msgStrBuffer;
  int                  callId;
  TNhtCtdTestRunStatus ctdTestRunStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdWaitOnScrTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xScrTestRunSession", (void*)xScrTestRunSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "int: xTimeout", (size_t)xTimeout, sizeof(int));
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdTestRunStatus = nhtCtdWaitOnScrTestRunCompletion (xScrTestRunSession, xTimeout);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdWaitOnScrTestRunCompletion():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdTestRunStatus", (size_t)ctdTestRunStatus, sizeof(TNhtCtdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdTestRunStatus;
}



/* */
TNhtCtdTestRunStatus _CRPC(nhtCtdStopScrTestRun)
(
  TNhtCtdScrTestRunSession  xScrTestRunSession
)
{
  TMsgbufStrBuffer     msgStrBuffer;
  int                  callId;
  TNhtCtdTestRunStatus ctdTestRunStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdStopScrTestRun():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in:  xScrTestRunSession", (void*)xScrTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdTestRunStatus = nhtCtdStopScrTestRun (xScrTestRunSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdStopScrTestRun():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdTestRunStatus", (size_t)ctdTestRunStatus, sizeof(TNhtCtdTestRunStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdTestRunStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdSetScrProtectedKeys)
(
        TNhtCtdScrTestRunSession   xScrTestRunSession,
        TCtdUnsignedInt16          xKeyEmi,
        TCtdSize                   xCipheredProtectingKeySize,
  const TCtdUnsignedInt8         * pxL1CipheredProtectingKey,
  const TCtdUnsignedInt8         * pxL2CipheredProtectingKey,
  const TCtdUnsignedInt8         * pxCipheredScrContentKey,
        TCtdSize                   xCipheredScrContentKeySize,
  const TCtdUnsignedInt8         * pxInitializationVector,
        TCtdSize                   xInitializationVectorSize
)
{
  TMsgbufStrBuffer msgStrBuffer;
  int              callId;
  TCtdStatus       ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdSetScrProtectedKeys():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunHandle", (void*)xScrTestRunSession);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "int: xKeyEmi", (size_t)xKeyEmi, sizeof(TCtdUnsignedInt16));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredProtectingKeySize", (size_t)xCipheredProtectingKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxL1CipheredProtectingKey", (void*)pxL1CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxL2CipheredProtectingKey", (void*)pxL2CipheredProtectingKey, (size_t)xCipheredProtectingKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xCipheredScrContentKeySize", (size_t)xCipheredScrContentKeySize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxCipheredScrContentKey", (void*)pxCipheredScrContentKey, (size_t)xCipheredScrContentKeySize);
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "in: xInitializationVectorSize", (size_t)xInitializationVectorSize, sizeof(TCtdSize));
    msgbuf_strbuilder_add_string  (&msgStrBuffer,"\n");
    msgbuf_strbuilder_setparam_buffer (&msgStrBuffer, "in: pxInitializationVector", (void*)pxInitializationVector, (size_t)xInitializationVectorSize);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdSetScrProtectedKeys (
    xScrTestRunSession,
    xKeyEmi,
    xCipheredProtectingKeySize,
    pxL1CipheredProtectingKey,
    pxL2CipheredProtectingKey,
    pxCipheredScrContentKey,
    xCipheredScrContentKeySize,
    pxInitializationVector,
    xInitializationVectorSize );

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdSetScrProtectedKeys():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}


/* */
TCtdStatus _CRPC(nhtCtdCloseScrTestRunSession)
(
  TNhtCtdScrTestRunSession xScrTestRunSession
)
{
  TMsgbufStrBuffer      msgStrBuffer;
  int                   callId;
  TCtdStatus            ctdStatus;

  msgbuf_strbuilder_buffer_init (&msgStrBuffer);
  callId = rpc_ftrace_get_callId ();

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_add_string       (&msgStrBuffer, ">@nhtCtdCloseScrTestRunSession():\n");
    msgbuf_strbuilder_setparam_pointer (&msgStrBuffer, "in: xScrTestRunSession", (void*)xScrTestRunSession);
    RPC_FTRACE_ENTER_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  ctdStatus = nhtCtdCloseScrTestRunSession (xScrTestRunSession);

  if (RPC_FTRACE_IS_ENABLED())
  {
    msgbuf_strbuilder_buffer_empty (&msgStrBuffer);
    msgbuf_strbuilder_add_string  (&msgStrBuffer, "<@nhtCtdCloseScrTestRunSession():\n");
    msgbuf_strbuilder_setparam_hex_value (&msgStrBuffer, "ret: ctdStatus", (size_t)ctdStatus, sizeof(TCtdStatus));
    RPC_FTRACE_EXIT_CLIENT_CALL (callId, msgStrBuffer.pBuffer);
  }

  msgbuf_strbuilder_buffer_terminate (&msgStrBuffer);
  return ctdStatus;
}

#endif
