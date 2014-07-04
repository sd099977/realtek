/**
 * File: $Id:$
 *
 *  This file implements the posix RPC-service server
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

#include "inc/tcpip/rpc_tcpip_server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "inc/msgbuf_sys_string.h"
#include <pthread.h>
#include "inc/msgbuf_sys_malloc.h"
#include "inc/app_rpc_report.h"
#include "src/os/posix/posix_rpc_service.h"
#include <string.h>
#include <strings.h>
#include "src/os/posix/posix_rpc_stdout_stderr_redirection.h"
#include <netinet/tcp.h>


#if defined(RPC_USE_UNIX_SOCKET) && (RPC_USE_UNIX_SOCKET != 0)
#include <sys/un.h>
#endif


/* */
typedef struct SFdHandle
{
  pthread_mutex_t _writeMutex;
  int             connfd;
} TFdHandle;


TRpc_POSIX_outStreamsHandle gOutStreamsRedictionHandle;


/* */
static int _socketRead
(
  void * pxFd,
  void * pxBuffer,
  int    xSize
)
{
  int         status;
  TFdHandle * pFdHandle = (TFdHandle*)pxFd;

  errno = 0;

#ifdef MSG_WAITALL
  status = recv (pFdHandle->connfd, pxBuffer, xSize, MSG_WAITALL);
#else
  status = read (pFdHandle->connfd, pxBuffer, xSize);
#endif

  if (status < 0)
  {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK) || (errno == 0))
      status = 0;
    else status = -1;
  }
  else if (status == 0) status = -1;

  return status;
}


/* */
static int _socketWrite
(
  void       * pxFd,
  const void * pxBuffer,
  int          xSize
)
{
  int status;
  TFdHandle * pFdHandle = (TFdHandle*)pxFd;

  rpc_posix_flush_redirected_outputStreams (&gOutStreamsRedictionHandle);


  pthread_mutex_lock (&pFdHandle->_writeMutex);

  errno = 0;

#ifdef MSG_WAITALL
  status = send (pFdHandle->connfd, pxBuffer, xSize, MSG_WAITALL);
#else
  status = write (pFdHandle->connfd, pxBuffer, xSize);
#endif

  if (status < 0)
  {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
      status = 0;
    else status = -1;
  }
  else if (status == 0) status = -1;

  pthread_mutex_unlock (&pFdHandle->_writeMutex);

  return status;
}


/*
 * main_thrSocketHandler
 */
static void * main_thrSocketHandler (void *xArg)
{
  TMsgBuf_rpcHandler rpcHandler;

  rpcHandler = (TMsgBuf_rpcHandler)xArg;

  posixRpcService_main (rpcHandler);

  MSGBUF_SYS_free (xArg);
  pthread_exit ((void *)0);
  return NULL;
}


/* */
static int start_thr_strategy_server
(
  uint16_t                      xPort,
  int                           xBackLog,
  TProcessInitResourceFct       xProcessInitResFct,
  TProcessTerminateResourceFct  xProcessTerminateResFct,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceHandleSet[],
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct
)
{
  int         status;
  int         listenfd;   /* listen socked fd */
  int         connfd;     /* current socket fd for client opened connection */
  int         yes = 1;
  TMsgBuf_rpcHandler rpcHandler;


#if defined(RPC_USE_UNIX_SOCKET) && (RPC_USE_UNIX_SOCKET != 0)
  struct sockaddr_un  unix_cliaddr;
  struct sockaddr_un  unix_servaddr;
  int                 servlen;
#else /* RPC_USE_UNIX_SOCKET */
  struct sockaddr_in  servaddr;
  struct sockaddr_in  cliaddr;
#endif /* RPC_USE_UNIX_SOCKET */

  socklen_t      clilen;
  pthread_t      chld_thr;

  if (xProcessInitResFct != NULL)
  {
    status = xProcessInitResFct();
    if (status < 0)
    {
      perror ("[RPC server] Fails to initialize process resources\n");
      return status;
    }
  }

#if defined(RPC_USE_UNIX_SOCKET) && (RPC_USE_UNIX_SOCKET != 0)

  /* Get a listener socket file descriptor */
  status = socket (AF_UNIX,SOCK_STREAM,0, &listenfd);

  memset (&unix_servaddr, 0, sizeof(unix_servaddr));
  unix_servaddr.sun_family = AF_UNIX;
  MSGBUF_SYS_strcpy(unix_servaddr.sun_path, "./rpc_pipe");
  servlen = MSGBUF_SYS_strlen (unix_servaddr.sun_path) +
    sizeof(unix_servaddr.sun_family);

  status = bind (
    listenfd,
    (struct sockaddr *)
    &unix_servaddr,
    servlen);

#else /* RPC_USE_UNIX_SOCKET */

  /* Get a listener socket file descriptor */
  listenfd = socket (AF_INET,SOCK_STREAM,0);

  /* So we can restart our server quickly */
  status = setsockopt (
    listenfd,
    SOL_SOCKET,
    SO_REUSEADDR,
    &yes,
    sizeof(int));

  if (status == -1)
  {
    perror("[RPC server] setsockopt error\n");
    exit(1);
  }

  memset (&servaddr, 0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port=htons (32000);

  status =bind (listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

#endif /* RPC_USE_UNIX_SOCKET */

  if (status == -1)
  {
    close (listenfd);
    perror("[RPC server] bind error\n");
    exit (1);
  }

  status = listen (listenfd, xBackLog);
  if (status == -1)
  {
    perror("[RPC server] listen error\n");
    exit(1);
  }

  for(;;)
  {
    TFdHandle * pFdHandle = NULL;


#if defined (RPC_USE_UNIX_SOCKET) && (RPC_USE_UNIX_SOCKET != 0)
    clilen = sizeof(unix_cliaddr);
    connfd = accept (listenfd,(struct sockaddr *)&unix_cliaddr, &clilen);
#else /* RPC_USE_UNIX_SOCKET */
    clilen = sizeof(cliaddr);
    connfd = accept (listenfd,(struct sockaddr *)&cliaddr, &clilen);
#endif /*RPC_USE_UNIX_SOCKET */

    if(connfd == -1)
    {
      perror ("[RPC server] accept error\n");
      exit(0);
    }

    printf ("[NHT server PID=%d] New client connection opened.\n", (int)getpid());

    pFdHandle = (TFdHandle*)MSGBUF_SYS_malloc(sizeof(TFdHandle));
    pFdHandle->connfd = connfd;
    pthread_mutex_init (&pFdHandle->_writeMutex, NULL);

    rpcHandler = pPosixRpcService_createHandle ((void*)pFdHandle, xServiceNumber, pxServiceHandleSet, &_socketWrite, &_socketRead);

    /* create a new thread to process the incomming request */
    status = pthread_create (
      &chld_thr,
      NULL,
      main_thrSocketHandler,
      (void*) rpcHandler );

    if (status)
    {
      close (connfd);
      perror ("[RPC server] Fail to create thread\n");
      exit (0);
    }
    /* the server is now free to accept another socket request */
  }
}


/* */
static int start_process_strategy_server
(
  uint16_t                      xPort,
  int                           xBackLog,
  TProcessInitResourceFct       xProcessInitResFct,
  TProcessTerminateResourceFct  xProcessTerminateResFct,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceHandleSet[],
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct
)
{
  TMsgBuf_rpcHandler rpcHandle;
  int                listenfd;   /* listen socked fd */
  int                connfd;     /* current socket fd for client opened connection */
  int                yes = 1;

  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  socklen_t          clilen;
  int                status;
  pid_t              childpid;

#if defined(RPC_TRACE_CALL_ENABLE) && (RPC_TRACE_CALL_ENABLE != 0)
  printf ("[RPC server]: server process-strategy started\n");
#endif

  /* Get a listener socket file descriptor */
  listenfd = socket (AF_INET,SOCK_STREAM,0);

  /* So we can restart our server quickly */
  status = setsockopt (
    listenfd,
    SOL_SOCKET,
    SO_REUSEADDR,
    &yes,
    sizeof(int));

  if (listenfd == -1)
  {
    perror("[RPC server] setsockopt error\n");
    exit(1);
  }

  memset (&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons (xPort);

  status = bind (
    listenfd,
    (struct sockaddr *)&servaddr,
    sizeof(servaddr));

  if (status == -1)
  {
    close(listenfd);
    perror("[RPC server] bind error\n");
    exit (1);
  }

  status = listen (listenfd, xBackLog);
  if (status == -1)
  {
    perror("[RPC server] listen error\n");
    exit(1);
  }

  for (;;)
  {
    clilen = sizeof(cliaddr);
    connfd = accept (
      listenfd,
      (struct sockaddr *)&cliaddr,
      &clilen);

    if(connfd == -1)
    {
      perror ("[RPC server] accept error\n");
      exit(0);
    }

    if ((childpid = fork()) != 0)
    {
      TFdHandle * pFdHandle = NULL;
      int         flags     = 1;

      pFdHandle = (TFdHandle*)MSGBUF_SYS_malloc(sizeof(TFdHandle));
      pFdHandle->connfd = connfd;
      pthread_mutex_init (&pFdHandle->_writeMutex, NULL);

      close (listenfd);

      setsockopt (connfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(int));

      rpcHandle = pPosixRpcService_createHandle ((void*)pFdHandle, xServiceNumber, pxServiceHandleSet, &_socketWrite, &_socketRead);
      if (rpcHandle == NULL)
      {
        close (connfd);
        perror ("[RPC server] RPC connection service mismatch error\n");
        exit (1);
      }

      printf ("[NHT server PID=%d] New client connection opened.\n", (int)getpid());

      if (xProcessInitResFct != NULL)
      {
        status = xProcessInitResFct();
        if (status < 0)
        {
          perror ("[RPC server] Fails to initialize process resources\n");
        }
      }
      else status = 0;

      if (status >= 0)
      {
        rpc_redirect_outputStreams (
          &gOutStreamsRedictionHandle,
          xStdout_redirect_cbfct,
          xStderr_redirect_cbfct );

        posixRpcService_main (rpcHandle);

        if (xProcessTerminateResFct != NULL)
        {
          status = xProcessTerminateResFct();
        }

        rpc_restore_outputStreams (&gOutStreamsRedictionHandle);
        printf ("[NHT server PID=%d] Client connection closed.\n", (int)getpid());

        close (connfd);
        posixRpcService_closeHandle (rpcHandle);

      }
      else close (connfd);

      if (pFdHandle)
      {
        pthread_mutex_destroy (&pFdHandle->_writeMutex);
        MSGBUF_SYS_free (pFdHandle);
      }

      return status;
    }
    else close (connfd);
  }

  return 0;
}


/* */
int rpc_start_server
(
  uint16_t                      xPort,
  int                           xBackLog,
  TServerStrategy               xStrategy,
  TProcessInitResourceFct       xProcessInitResFct,
  TProcessTerminateResourceFct  xProcessTerminateResFct,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceHandleSet[],
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct
)
{
  if (xStrategy == SRV_STRAGETY_THREAD_VERSUS_STRATEGY)
    return start_thr_strategy_server (
      xPort,
      xBackLog,
      xProcessInitResFct,
      xProcessTerminateResFct,
      xServiceNumber,
      pxServiceHandleSet,
      xStdout_redirect_cbfct,
      xStderr_redirect_cbfct );

  else
  {
    return start_process_strategy_server (
      xPort,
      xBackLog,
      xProcessInitResFct,
      xProcessTerminateResFct,
      xServiceNumber,
      pxServiceHandleSet,
      xStdout_redirect_cbfct,
      xStderr_redirect_cbfct );
  }
}
