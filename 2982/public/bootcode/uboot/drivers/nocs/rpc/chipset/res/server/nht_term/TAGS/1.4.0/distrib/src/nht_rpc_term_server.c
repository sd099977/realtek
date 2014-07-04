/**
 * File: $Id:$
 *
 *  This header file implements the MSGBUF RPC client generic functions.
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



#include "inc/term/rpc_term_server.h"
#include "inc/os/none/serial_rpc_service.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "nht_term.h"
#include <stddef.h>


#define RPCTERM_BUFFER_ALLOC_CHUNK  356


/* Stream handler info structure definition */
typedef struct SRpcTerm_streamInfo
{
  TPosixOutStreamReportCbfct   reportCbfct;
  char                       * pBuffer;
  int                          usedSize;
  int                          mallocSize;

} TRpcTerm_streamInfo;


static TMsgBuf_rpcHandler  gRpcHandle;
static TRpcTerm_streamInfo gRpcTerm_stdout_streamInfo = {NULL, NULL, 0, 0};
static TRpcTerm_streamInfo gRpcTerm_stderr_streamInfo = {NULL, NULL, 0, 0};
static int                 gIsReporting = 0;


/* */
static void rpcTerm_debug_report (
  const char          * pxString,
  TRpcTerm_streamInfo * pxStreamInfo );


/* */
static void rpcTerm_stdout_cbfct (const char * pxString)
{ rpcTerm_debug_report (pxString, &gRpcTerm_stdout_streamInfo); }


/* */
static void rpcTerm_stderr_cbfct (const char * pxString)
{ rpcTerm_debug_report (pxString, &gRpcTerm_stderr_streamInfo); }


/* */
static void rpcTerm_debug_report
(
  const char          * pxString,
  TRpcTerm_streamInfo * pxStreamInfo
)
{
  char const * pCurStringPtr = pxString;
  char       * pWritePtr;

  if (pxStreamInfo->reportCbfct == NULL) return;

  if (pxStreamInfo->pBuffer == NULL)
  {
    pxStreamInfo->pBuffer = (char*)MSGBUF_SYS_malloc (RPCTERM_BUFFER_ALLOC_CHUNK);
    pxStreamInfo->usedSize = 0;
    pxStreamInfo->mallocSize = RPCTERM_BUFFER_ALLOC_CHUNK;
  }

  pWritePtr = &pxStreamInfo->pBuffer[pxStreamInfo->usedSize];
  while (*pCurStringPtr != 0)
  {
    char curChar = *pCurStringPtr++;

    if (curChar == 0x0D)  continue;

    if (curChar == 0x0A)
    {
      pWritePtr[0] = 0;
      gIsReporting++;
      pxStreamInfo->reportCbfct (pxStreamInfo->pBuffer);
      gIsReporting--;
      pxStreamInfo->usedSize = 0;
      pWritePtr = pxStreamInfo->pBuffer;
      continue;
    }

    *pWritePtr++ = curChar;
    pxStreamInfo->usedSize++;
    if (pxStreamInfo->usedSize >= pxStreamInfo->mallocSize)
    {
      char * pTmpBuffer = pxStreamInfo->pBuffer;

      pxStreamInfo->mallocSize += RPCTERM_BUFFER_ALLOC_CHUNK;
      pxStreamInfo->pBuffer = (char*)MSGBUF_SYS_malloc (pxStreamInfo->mallocSize);
      MSGBUF_SYS_memcpy (pxStreamInfo->pBuffer, pTmpBuffer, pxStreamInfo->usedSize);
      MSGBUF_SYS_free (pTmpBuffer);
      pWritePtr = &pxStreamInfo->pBuffer[pxStreamInfo->usedSize];
    }
  }
}


/* */
static void rpcTerm_debug_flush
(
  TRpcTerm_streamInfo * pxStreamInfo
)
{
  if ((pxStreamInfo->usedSize > 0) && (gIsReporting == 0)) rpcTerm_debug_report ("\n", pxStreamInfo);
}


static int bsdrpc_term_read
(
  void  * pxFd,
  void  * pxBuffer,
  int     xSize
)
{
  /* Flush the stdout/stderr buffer when reading in any case in
   * order to ensure that data is always flushed before starting
   * a new connection to the bare mode server */
  rpcTerm_debug_flush (&gRpcTerm_stderr_streamInfo);
  rpcTerm_debug_flush (&gRpcTerm_stdout_streamInfo);

  return nht_term_portRead ((void *)pxBuffer, xSize);
}


static int bsdrpc_term_write
(
  void       * pxFd,
  const void * pxBuffer,
  int          xSize
)
{
  /* Flush the stdout/stderr buffer before writing the data
   * associated to this write() */
  rpcTerm_debug_flush (&gRpcTerm_stderr_streamInfo);
  rpcTerm_debug_flush (&gRpcTerm_stdout_streamInfo);

  return nht_term_portWrite ((const void *)pxBuffer, xSize);
}


/* */
int rpcTerm_startServer
(
  TProcessInitResourceFct       xProcessInitResFct,
  TProcessTerminateResourceFct  xProcessTerminateResFct,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct
)
{
  int status = 0;

  gRpcTerm_stdout_streamInfo.reportCbfct = xStdout_redirect_cbfct;
  gRpcTerm_stderr_streamInfo.reportCbfct = xStderr_redirect_cbfct;

  nht_term_register_printout_cbfct (&rpcTerm_stdout_cbfct, &rpcTerm_stderr_cbfct);

  nht_term_portOpen ();

  if (xProcessInitResFct) xProcessInitResFct ();

  gRpcHandle = pSerialRpcService_createHandle (
    NULL,
    xServiceNumber,
    pxServiceSet,
    &bsdrpc_term_write,
    &bsdrpc_term_read );

  if (!gRpcHandle) return -1;

  status = serialRpcService_start (gRpcHandle);

  if (xProcessTerminateResFct) xProcessTerminateResFct();
  return status;
}


/* */
void rpcTerm_stopServer
(
  TMsgBuf_rpcHandler xRpcHandle
)
{
  if (gRpcHandle)
    serialRpcService_closeHandle (gRpcHandle);

}

