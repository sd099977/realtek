/**
 * File: $Id:$
 *
 *  This file implements the CSD RPC server glue code.
 *  This file stands as the customization of the template generated
 *  by the msgbuf compiler associated to CSD API.
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

#include "src/rpc_nhtreport_api.h"
#include "inc/nht_report.h"
#include "inc/nv_nht_report.h"
#include "inc/rpc_ftrace.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include <stddef.h>


volatile TNhtReportCategory gReportMinimumCategory = NHT_REPORT_INFO_TYPE;


/****************************************************************************
 * Static function prototypes                                               *
 ****************************************************************************/


/*****************************************************************************
 * RPC methods implementation                                                *
 ****************************************************************************/



/* RPC method: rpc_nhtcsd_hc_nht_setReportLevel
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtreport_hc_nht_setReportLevel
(
  TMsgBuf_rpcHandler            xRpcHandler,
  const TNhtreport_SizeInMsg  * pxInputMessage,
  TNhtreport_EmptyMsg        ** pxOutputMessage
)
{
  gReportMinimumCategory = (TNhtReportCategory)pxInputMessage->value;

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtreport_hc_enable_ftrace
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtreport_hc_enable_ftrace
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtreport_EmptyMsg  * pxInputMessage,
  TNhtreport_EmptyMsg       ** pxOutputMessage
)
{
  RPC_FTRACE_ENABLE();

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtreport_hc_disable_ftrace
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtreport_hc_disable_ftrace
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtreport_EmptyMsg  * pxInputMessage,
  TNhtreport_EmptyMsg       ** pxOutputMessage
)
{
  RPC_FTRACE_DISABLE();

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtreport_hc_restore_ftrace
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtreport_hc_restore_ftrace
(
  TMsgBuf_rpcHandler           xRpcHandler,
  const TNhtreport_EmptyMsg  * pxInputMessage,
  TNhtreport_EmptyMsg       ** pxOutputMessage
)
{
  RPC_FTRACE_RESTORE_DEFAULT ();

  return RPC_STATUS_NO_ERROR;
}

/* RPC method: rpc_nhtreport_hc_getCmServerVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtreport_hc_getCmServerVersion
(
  TMsgBuf_rpcHandler             xRpcHandler,
  const TNhtreport_EmptyMsg    * pxInputMessage,
  TNhtreport_ReportTextOutMsg ** pxOutputMessage
)
{
  char       * pText = NULL;
  char const * pVersion;

  pVersion = nht_getCmServerVersion ();

  if (pxOutputMessage)
  {
    pText = (char*)MSGBUF_SYS_malloc(MSGBUF_SYS_strlen(pVersion) + 1);
    MSGBUF_SYS_strcpy (pText, pVersion);
    (*pxOutputMessage)->text = pText;
  }

  return RPC_STATUS_NO_ERROR;
}


/* RPC method: rpc_nhtreport_hc_getNhtServerComponentVersion
 *
 * This method stands as a synchronous function call.
 * Caller of this function only returns after completion of
 * its remote execution.
 */
TRpc_status rpc_nhtreport_hc_getNhtServerComponentVersion
(
  TMsgBuf_rpcHandler             xRpcHandler,
  const TNhtreport_EmptyMsg    * pxInputMessage,
  TNhtreport_ReportTextOutMsg ** pxOutputMessage
)
{
  char       * pText = NULL;
  char const * pVersion;

  pVersion = nht_getNhtServerComponentVersion();
  if (pxOutputMessage)
  {
    pText = (char*)MSGBUF_SYS_malloc(MSGBUF_SYS_strlen(pVersion) + 1);
    MSGBUF_SYS_strcpy (pText, pVersion);
    (*pxOutputMessage)->text = pText;
  }

  return RPC_STATUS_NO_ERROR;
}

/*****************************************************************************
 * RPC method calls API wrapper                                              *
 ****************************************************************************/


/* RPC method: rpc_nhtcsd_tn_report_error
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
void _nht_error_report
(
  TNhtReportCategory    xErrorLevel,
  int                   xErrorNumber,
  const char          * pxContext,
  const char          * pxMsg
)
{
  TNhtreport_ReportErrorInMsg   reportErrorMsg;
  TNhtreport_EmptyMsg         * pEmptyMsg;

  if (xErrorLevel >= gReportMinimumCategory)
  {
    init_Nhtreport_ReportErrorInMsg (&reportErrorMsg);

    reportErrorMsg.errorType   = (uint32_t)xErrorLevel;
    reportErrorMsg.errorNumber = (uint32_t)xErrorNumber;
    reportErrorMsg.context     = (char*)pxContext;
    reportErrorMsg.description = (char*)pxMsg;

    /* rpcStatus = */ rpc_nhtreport_tn_report_error (
      NULL,
      &reportErrorMsg,
      &pEmptyMsg );
  }
}

/* RPC method: rpc_nhtcsd_tn_report_trace
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
void _nht_trace_report
(
  TNhtReportCategory   xErrorLevel,
  const char         * pxFileName,
  int                  xLine,
  const char         * pxContext,
  const char         * pxMsg
)
{
  TNhtreport_ReportTraceInMsg   reportTraceMsg;
  TNhtreport_EmptyMsg         * pEmptyMsg;

  if (xErrorLevel >= gReportMinimumCategory)
  {
    init_Nhtreport_ReportTraceInMsg (&reportTraceMsg);

    reportTraceMsg.errorType   = (uint32_t)xErrorLevel;
    reportTraceMsg.filename    = (char*)pxFileName;
    reportTraceMsg.line        = (uint32_t)xLine;
    reportTraceMsg.context     = (char*)pxContext;
    reportTraceMsg.description = (char*)pxMsg;


    /* rpcStatus = */ rpc_nhtreport_tn_report_trace (
      NULL,
      &reportTraceMsg,
      &pEmptyMsg );
  }
}

/* RPC method: rpc_nhtcsd_tn_report_info
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
void _nht_report
(
  TNhtReportCategory    xErrorLevel,
  const char          * pxContext,
  const char          * pxMsg
)
{
  TNhtreport_ReportInfoInMsg   reportInfoMsg;
  TNhtreport_EmptyMsg        * pEmptyMsg = NULL;

  if (xErrorLevel >= gReportMinimumCategory)
  {
    init_Nhtreport_ReportInfoInMsg (&reportInfoMsg);

    reportInfoMsg.errorType    = (uint32_t)xErrorLevel;
    reportInfoMsg.context     = (char*)pxContext;
    reportInfoMsg.description = (char*)pxMsg;

    /* rpcStatus = */ rpc_nhtreport_tn_report_info (
      NULL,
      &reportInfoMsg,
      &pEmptyMsg );
  }
}

/* RPC method: rpc_nhtreport_tn_report_stdout
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
void nht_reportServerStdout
(
  const char * pxLineText
)
{
  TNhtreport_EmptyMsg        * pEmptyMsg = NULL;
  TNhtreport_ReportTextInMsg   inputMessage;

  init_Nhtreport_ReportTextInMsg (&inputMessage);

  inputMessage.text = (char*)pxLineText;

  rpc_nhtreport_tn_report_stdout (
    NULL,
    &inputMessage,
    &pEmptyMsg );

  if (pEmptyMsg) dealloc_Nhtreport_EmptyMsg (pEmptyMsg);
}


/* RPC method: rpc_nhtreport_tn_report_stdout
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
void nht_reportServerStderr
(
  const char * pxLineText
)
{
  TNhtreport_EmptyMsg        * pEmptyMsg = NULL;
  TNhtreport_ReportTextInMsg   inputMessage;

  init_Nhtreport_ReportTextInMsg (&inputMessage);

  inputMessage.text = (char*)pxLineText;

  rpc_nhtreport_tn_report_stderr (
    NULL,
    &inputMessage,
    &pEmptyMsg );

  if (pEmptyMsg) dealloc_Nhtreport_EmptyMsg (pEmptyMsg);
}


/* RPC method: rpc_nhtreport_tn_report_ftrace
 *
 * This method stands as an asynchronous notification function.
 * Caller of this function immediately returns without waiting
 * the completion of its remote execution.
 *
 * PS: param 'pxOutputMessage' is always assumed to be NULL.
 */
void nht_reportServerFTrace
(
  int              xCallId,
  TRpcFTraceType   xFTraceType,
  const char     * pxFtraceLineText
)
{
  TNhtreport_EmptyMsg          * pEmptyMsg = NULL;
  TNhtreport_ReportFTraceInMsg   inputMessage;

  init_Nhtreport_ReportFTraceInMsg (&inputMessage);

  inputMessage.callId = (uint32_t)xCallId;
  inputMessage.type   = (uint32_t)xFTraceType;
  inputMessage.text   = (char*)pxFtraceLineText;

  rpc_nhtreport_tn_report_ftrace (
    NULL,
    &inputMessage,
    &pEmptyMsg );

  if (pEmptyMsg) dealloc_Nhtreport_EmptyMsg (pEmptyMsg);
}