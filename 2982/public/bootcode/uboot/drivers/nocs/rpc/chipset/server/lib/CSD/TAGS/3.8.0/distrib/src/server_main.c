/**
 * File: $Id:$
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

#include "inc/rpc_nhtcsd.h"
#include "inc/rpc_nhtctd.h"
#include "inc/rpc_nhtsec.h"
#include "inc/rpc_nhtcert.h"
#include "inc/rpc_nhtreport.h"
#include "inc/tcpip/rpc_tcpip_server.h"
#include "inc/app_msgbuf_report.h"
#include "inc/app_rpc_report.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "inc/nht_report.h"
#include "nocs_nhtcsd.h"
#include "nocs_nhtctd.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/nv_nht_report.h"
#include "inc/rpc_ftrace.h"
#include "inc/msgbuf_strbuilder.h"


/*----------------------------------------------------------
 * Static variable definitions
 *---------------------------------------------------------*/

/* RPC service table */
static const TMsgBuf_serviceHandle *gRpcServiceTable[] =
{
  &gRpcServiceHandle_nhtreport,
  &gRpcServiceHandle_nhtcsd,
  &gRpcServiceHandle_nhtctd,
  &gRpcServiceHandle_nhtsec,
  &gRpcServiceHandle_nhtcert
};

/* */
typedef struct SNhtTcpIpServerCfgData
{
  uint16_t                   portNumber;
  TPosixOutStreamReportCbfct stdoutReportCbfct;
  TPosixOutStreamReportCbfct stderrReportCbfct;

} TNhtTcpIpServerCfgData;


/*----------------------------------------------------------
 * Static function declarations
 *---------------------------------------------------------*/

/* */
static void print_help (
  int     xArgc,
  char ** pxArgv );

/* */
static void _APP_MSGBUF_report_info_cbfct (
  const char * pxString );

/* */
static void _APP_MSGBUF_report_error_cbfct (
  const char * pxString );

/* */
static void _APP_RPC_report_info_cbfct (
  const char * pxString );

/* */
static void _APP_RPC_report_error_cbfct (
  const char * pxString );

/* */
static void _APP_RPC_report_trace_cbfct (
  const char * pxString );

/* */
static int processTerminateResource(void);


static int stdout_report_cbfct (
  const char * pxText );

static int stderr_report_cbfct (
  const char * pxText );

static void nhtserver_cfgInit (
  TNhtTcpIpServerCfgData * pxCfgData );

static void nhtserver_cfgTerminate (
  TNhtTcpIpServerCfgData * pxCfgData );

static int nhtserver_cmdLineParser (
  int                       xArgc,
  char                   ** pxArgv,
  TNhtTcpIpServerCfgData  * pxCfgData );


/* */
#if 0
static int processInitResource(void);
#endif


/*----------------------------------------------------------
 * Main function
 *---------------------------------------------------------*/

int main (int argc, char * argv[])
{
  int                    status = 0;
  TNhtTcpIpServerCfgData cfgData;

  if ((argc == 2) && !MSGBUF_SYS_strcmp(argv[1], "--help"))
  {
    print_help(argc, argv);
    return 0;
  }

  MSGBUF_SYS_init ();

#ifdef  _NHT_RPC_TRACE_ON_
  rpc_ftrace_init (&nht_reportServerFTrace);
#endif

  nhtserver_cfgInit (&cfgData);
  status = nhtserver_cmdLineParser (argc, argv, &cfgData);

  if (!status)
  {
    /* */
    APP_MSGBUF_report_info_registerCBfct  (&_APP_MSGBUF_report_info_cbfct);
    APP_MSGBUF_report_error_registerCBfct (&_APP_MSGBUF_report_error_cbfct);

    APP_RPC_report_info_registerCBfct (&_APP_RPC_report_info_cbfct);
    APP_RPC_report_error_registerCBfct (&_APP_RPC_report_error_cbfct);
    APP_RPC_report_trace_registerCBfct (& _APP_RPC_report_trace_cbfct);

    status = rpc_start_server (
      cfgData.portNumber,
      20,
      SRV_STRAGETY_PROCESS_VERSUS,
      NULL /* &processInitResource */,
      &processTerminateResource,
      sizeof (gRpcServiceTable)/sizeof(TMsgBuf_serviceHandle*),
      gRpcServiceTable,
      cfgData.stdoutReportCbfct,
      cfgData.stderrReportCbfct );
  }


  nhtserver_cfgTerminate (&cfgData);

#ifdef  _NHT_RPC_TRACE_ON_
  rpc_ftrace_terminate ();
#endif

  MSGBUF_SYS_terminate ();

  return status;
}


/*----------------------------------------------------------
 * Static function definitions
 *---------------------------------------------------------*/

static void print_help
(
  int     xArgc,
  char ** pxArgv
)
{
  printf ("Application version : %s\n", nht_getCmServerVersion());
  printf ("NHT lib version     : %s\n\n", nht_getNhtServerComponentVersion());

  printf ("Usage: %s <arguments...>\n", pxArgv[0]);
  printf ("Where arguments are:\n");

  printf ("  [--no_redirect_stdout] : Do not redirect stdout into connected client env\n");
  printf ("  [--no_redirect_stderr] : Do not redirect stdout into connected client env\n");
  printf ("  [--enable_ftrace]      : Enable (by default) API/EAPI function tracing (see note #1,#2)\n");
  printf ("  <port-number>          : TCPI-IP port number (decimal expression)\n\n");
  printf ("To obtain this help, type: %s --help\n", pxArgv[0]);
  printf ("\n");
  printf ("  #1: A connected client is allowed to overwrite the default enable/disable\n");
  printf ("       tracing of the server associated to its client/server connection.\n");
  printf ("  #2: Option '--enable_ftrace' is only effective if the server was compiled\n");
  printf ("       with NHT_RPC_TRACE_ENABLED=1 defined macro.\n");
}


/* */
static void nhtserver_cfgInit
(
  TNhtTcpIpServerCfgData * pxCfgData
)
{
  pxCfgData->portNumber = 0;
  pxCfgData->stdoutReportCbfct = &stdout_report_cbfct,
  pxCfgData->stderrReportCbfct = &stderr_report_cbfct;
}


static void nhtserver_cfgTerminate
(
  TNhtTcpIpServerCfgData * pxCfgData
)
{
  nhtserver_cfgInit (pxCfgData);
}


/* */
static int nhtserver_cmdLineParser
(
  int                       xArgc,
  char                   ** pxArgv,
  TNhtTcpIpServerCfgData  * pxCfgData
)
{
  char isPortNumbParsed         = 0;
  char isNoStdoutRedirectParsed = 0;
  char isNoStderrRedirectParsed = 0;
  char isEnableFtraceParsed     = 0;
  int  argCounter = 1;
  int  status     = 0;

  while (!status && (argCounter < xArgc))
  {
    if (!MSGBUF_SYS_strcmp (pxArgv[argCounter], "--no_redirect_stdout"))
    {
      if (isNoStdoutRedirectParsed) {status = -1; break; }
      else
      {
        isNoStdoutRedirectParsed = 1;
        pxCfgData->stdoutReportCbfct = NULL;
        argCounter++;
        continue;
      }
    }

    if (!MSGBUF_SYS_strcmp (pxArgv[argCounter], "--no_redirect_stderr"))
    {
      if (isNoStderrRedirectParsed) {status = -1; break; }
      else
      {
        isNoStderrRedirectParsed = 1;
        pxCfgData->stderrReportCbfct = NULL;
        argCounter++;
        continue;
      }
    }

    if (!MSGBUF_SYS_strcmp (pxArgv[argCounter], "--enable_ftrace"))
    {
      if (isEnableFtraceParsed) {status = -1; break; }
      else
      {
        isEnableFtraceParsed = 1;

#ifdef _NHT_RPC_TRACE_ON_
        RPC_FTRACE_DEFAULT_ENABLE();
#endif
        argCounter++;
        continue;
      }
    }

    if (isPortNumbParsed) { status = -1; break; }
    isPortNumbParsed = 1;
    pxCfgData->portNumber = (uint16_t)atoi (pxArgv[argCounter]);
    if (pxCfgData->portNumber == 0) {status = -1; break;}
    argCounter++;
  }

  if (!isPortNumbParsed) status = -1;

  if (status)
  {
    fprintf (stderr, "ERROR: NHT server illegal cmd line\n");
    print_help (xArgc, pxArgv);
  }

  return status;
}


/* */
static void _APP_MSGBUF_report_info_cbfct
(
  const char * pxString
)
{
  NHT_REPORT_INFO ("MSGBUF", pxString);
}

/* */
static void _APP_MSGBUF_report_error_cbfct
(
  const char * pxString
)
{
  NHT_REPORT_FATAL ("MSGBUF", pxString);
}

/* */
static void _APP_RPC_report_info_cbfct
(
  const char * pxString
)
{
  NHT_REPORT_INFO ("RPC", pxString);
}

/* */
static void _APP_RPC_report_error_cbfct
(
  const char * pxString
)
{
  NHT_REPORT_FATAL ("RPC", pxString);
}

/* */
static void _APP_RPC_report_trace_cbfct
(
  const char * pxString
)
{
  NHT_REPORT_DEBUG ("RPC", pxString);
}

/* */
static int processTerminateResource(void)
{
  nhtCsdTerminate ();
  nhtCtdTerminate ();
  return 0;
}

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


/* */
#if 0
static int processInitResource(void)
{
  nhtCsdInitialize ();
  return 0;
}
#endif
