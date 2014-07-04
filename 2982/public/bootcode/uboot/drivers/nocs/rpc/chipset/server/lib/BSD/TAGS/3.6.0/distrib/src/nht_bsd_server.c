/**
 * File: nht_bsd_server.c
 *
 *  This file implements the CSD server application main function.
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
#include "inc/msgbuf_sys_malloc.h"
#include "inc/bsd_server.h"
#include "nocs_nhtbsd.h"
#include "inc/rpc_nhtbsd.h"
#include "inc/rpc_nhtcert.h"
#include "inc/rpc_nhtreport.h"
#include "inc/app_msgbuf_report.h"
#include "inc/app_rpc_report.h"
#include "inc/nht_report.h"
#include "inc/rpc_ftrace.h"
#include "inc/nv_nht_report.h"
#include <stdio.h>


static const TMsgBuf_serviceHandle *gRpcServiceTable[] =
{
  &gRpcServiceHandle_nhtreport,
  &gRpcServiceHandle_nhtbsd,
  &gRpcServiceHandle_nhtcert
};


static int processTerminateResource(void)
{
  nhtBsdTerminate ();
  return 0;
}


#if 0

/* */
static void app_msgbuf_report_info
(
  const char * pxString
)
{
  /* NHT_REPORT_INFO ("MSGBUF", pxString); */
  printf ("MSGBUF_INFO : %s\n", pxString);
}


/* */
static void app_msgbuf_report_error
(
  const char * pxString
)
{
  /* NHT_REPORT_FATAL ("MSGBUF", pxString); */
  printf ("MSGBUF_ERROR: %s\n", pxString);
}


/* */
static void app_rpc_report_info
(
  const char * pxString
)
{
  /* NHT_REPORT_INFO ("RPC", pxString); */
  printf ("APP_INFO: %s\n", pxString);
}


/* */
static void app_rpc_report_error
(
  const char * pxString
)
{
  /* NHT_REPORT_FATAL ("RPC", pxString); */
  printf ("APP_ERROR: %s\n", pxString);
}


/* */
static void app_rpc_report_trace
(
  const char * pxString
)
{
  /* NHT_REPORT_DEBUG ("RPC", pxString); */
  printf ("APP_TRACE: %s\n", pxString);
}

#endif


/* */
static int stdout_report_cbfct
(
  const char * pxText
)
{
  nht_reportServerStdout (pxText);
  return 0;
}

/* */
static int stderr_report_cbfct
(
  const char * pxText
)
{
  nht_reportServerStderr (pxText);
  return 0;
}


int bsd_startServer
(
  int xServerParamArg
)
{
  int status;
  printf("%s(%d) test5 [%s %s]\n",__func__,__LINE__,__DATE__,__TIME__);
  MSGBUF_SYS_init();

#ifdef  _NHT_RPC_TRACE_ON_
  rpc_ftrace_init (&nht_reportServerFTrace);
#endif

#if 0
  APP_MSGBUF_report_info_registerCBfct ( app_msgbuf_report_info);
  APP_MSGBUF_report_error_registerCBfct (app_msgbuf_report_error);
  APP_RPC_report_info_registerCBfct  ( app_rpc_report_info);
  APP_RPC_report_error_registerCBfct ( app_rpc_report_error);
  APP_RPC_report_trace_registerCBfct ( app_rpc_report_trace );
#endif

  nhtBsdInitialize();

  /* bsdPrint ("BSD RPC server just started\n"); */

  status = rpcTerm_startServer (
    NULL /* &processInitResource */,
    &processTerminateResource,
    sizeof (gRpcServiceTable)/sizeof(TMsgBuf_serviceHandle*),
    gRpcServiceTable,
    &stdout_report_cbfct,
    &stderr_report_cbfct );

  MSGBUF_SYS_terminate();

  return 0;
}
