/**
 * File: $Id:$
 *
 *  This file implements the posix RPC stdout/stderr redirection
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


#ifndef _POSIX_RPC_STDOUT_STDERR_REDIRECTION_H_
#define _POSIX_RPC_STDOUT_STDERR_REDIRECTION_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include "inc/tcpip/rpc_tcpip_server.h"
#include <pthread.h>
#include <semaphore.h>


/* */
#define NHT_RPC_POSIX_STDERR_ID               0
#define NHT_RPC_POSIX_STDOUT_ID               1
#define _NHT_RPC_POSIX_MAX_STD_STREAMS        2

/* */
#define _NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID    0
#define _NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID    1
#define _NHT_RPC_POSIX_STDEO_PIPE_MAX_ID      2


/* */
typedef struct SRpc_POSIX_outStreamHandle
{
  /* Inputs */
  TPosixOutStreamReportCbfct   report_cbfct;

  int                          fd_backup;
  int                          fd_original;
  FILE                       * pFile;
  char const                 * pFileName;
  int                          pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_MAX_ID];
  pthread_t                    child_thread;
  sem_t                        syncSem;

} TRpc_POSIX_outStreamHandle;


/* */
typedef struct SRpc_POSIX_outStreamsHandle
{
  TRpc_POSIX_outStreamHandle stream[_NHT_RPC_POSIX_MAX_STD_STREAMS];

} TRpc_POSIX_outStreamsHandle;



/* */
int rpc_redirect_outputStreams (
  TRpc_POSIX_outStreamsHandle * pxOutStreamHandles,
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct );


/* */
int rpc_restore_outputStreams (
  TRpc_POSIX_outStreamsHandle * pxOutStreamHandles );


/* */
int rpc_posix_flush_redirected_outputStreams (
  TRpc_POSIX_outStreamsHandle * pxOutStreamHandles );


#ifdef __cplusplus
}
#endif

#endif /* _POSIX_RPC_STDOUT_STDERR_REDIRECTION_H_ */
