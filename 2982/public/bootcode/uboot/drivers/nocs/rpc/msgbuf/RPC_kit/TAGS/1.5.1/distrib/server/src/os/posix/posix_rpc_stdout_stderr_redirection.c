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


#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"
#include "src/os/posix/posix_rpc_stdout_stderr_redirection.h"
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>


/* */
static void * posix_outStreamReport_main (
  void * pxArg );


/* */
int rpc_redirect_outputStreams
(
  TRpc_POSIX_outStreamsHandle * pxOutStreamsHandle,
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct
)
{
  struct sigaction sa;
  int              flags;
  int              addedFlags = 0;
  int              i;

  /* INFO: In POSIX, redirecting stdout and stderr in anonymous pipe may cause subsequent
   * fflush of on stdout and stderr to fail sending SIGPIPE signal to the application.
   * .
   * As a conclusion, the default action of the SIGPIPE signal shall be desabled,
   * in order to ensure a proper run of the applications (including when integrating
   * code that might be using the fflush() function.
   *
   * This is done by setting the default SIG_IGN handle to the SIGPIE signal.
   */

  sa.sa_handler = SIG_IGN;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction (SIGPIPE, &sa, 0);


  /* Setup additional flags for making the pipe itself unbuffered (direct) */
  /* Note that, this will only be effective on Linux starting with v2.6 of Linux */

#ifdef O_DIRECT
  addedFlags |= O_DIRECT;
#endif

#ifdef O_ASYNC
  addedFlags |= O_ASYNC;
#else
#ifdef FSYNC
  addedFlags |= FSYNC;
#endif
#endif

  /* Initialize the structure */
  pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].report_cbfct = xStderr_redirect_cbfct;
  pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].report_cbfct = xStdout_redirect_cbfct;

  pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].pFile = stderr;
  pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].pFile = stdout;

  pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].pFileName = "stderr";
  pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].pFileName = "stdout";

  /* Ensure that stdout/sterr original pipe are flush and make them
   * unbuffered (for more accurated reporting) */
  for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
  {
    TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

    sem_init (&pHandle->syncSem, 0, 0);

    /* Make the output stream nonbuffered (for more efficient reporting) */
    pHandle->fd_original = fileno(pHandle->pFile);
    pHandle->fd_backup   = dup (pHandle->fd_original);
    fflush (pHandle->pFile);
    setbuf (pHandle->pFile, NULL);
  }

  /* If stderr and stdout callback function are the same, redirect stdout/stderr into the
   * same pipe (a single pipe indeed) */
  if ((xStderr_redirect_cbfct == xStdout_redirect_cbfct) &&
      (xStdout_redirect_cbfct != NULL))
  {
    TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID];

    printf ("[NHT server PID=%d] '%s/%s' (merged) redirected to its client application environment.\n",
      (int)getpid(),
      (char*)pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].pFileName,
      (char*)pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].pFileName );

    fflush (stdout);

    /* Create a unique pipe for capturing stdout and stderr streams */
    /* By default will put it in stderr */
    pipe (pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].pipe_fd);

    flags = fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], F_GETFD);
    flags |= addedFlags;
    fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], F_SETFD, flags);

    flags = fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID], F_GETFD);
    flags |= addedFlags;
    fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID], F_SETFD, flags);

    /* Redirect the output stream into the pipe */
    dup2 (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].fd_original);
    dup2 (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].fd_original);

    /* Close the write pipe file descriptor */
    close (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID]);

    if (!pthread_create (&pHandle->child_thread, NULL, &posix_outStreamReport_main, pHandle))
    {
      int                policy;
      int                priority_max;
      struct sched_param param;

      pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].child_thread = pHandle->child_thread;
      pthread_getschedparam (pHandle->child_thread, &policy, &param);
      priority_max = sched_get_priority_max (policy);
      param.sched_priority = priority_max;
      pthread_setschedparam (pHandle->child_thread, policy, &param);
    }
  }
  else
  {
    for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
    {
      TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

      if (pHandle->report_cbfct != NULL)
      {
        printf ("[NHT server PID=%d] '%s' redirected to its client application environment.\n",
          (int)getpid(),
          (char*)pHandle->pFileName );
      }
    }

    for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
    {
      TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

      if (pHandle->report_cbfct != NULL)
      {
        /* Create a pipe for capturing the dedicated streams */
        pipe (pHandle->pipe_fd);

        flags = fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], F_GETFD);
        flags |= addedFlags;
        fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], F_SETFD, flags);

        flags = fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID], F_GETFD);
        flags |= addedFlags;
        fcntl (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID], F_SETFD, flags);

        /* Redirect the output stream into the pipe */
        dup2 (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID], pHandle->fd_original);
      }
    }

    for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
    {
      TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

      if (pHandle->report_cbfct != NULL)
      {
        /* Close the write pipe file descriptor */
        /* close (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_WR_ID]); */

        if (!pthread_create (&pHandle->child_thread, NULL, &posix_outStreamReport_main, pHandle))
        {
          int                policy;
          int                priority_max;
          struct sched_param param;

          pthread_getschedparam (pHandle->child_thread, &policy, &param);
          priority_max = sched_get_priority_max (policy);
          param.sched_priority = priority_max;
          pthread_setschedparam (pHandle->child_thread, policy, &param);
        }
      }
    }
  }

  return 0;
}


/* */
int rpc_restore_outputStreams
(
  TRpc_POSIX_outStreamsHandle * pxOutStreamsHandle
)
{
  void * rett;
  int    i;

  if ((pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].report_cbfct == pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].report_cbfct) &&
      (pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].report_cbfct != NULL))
  {
    TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID];

    fprintf (pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].pFile, "\007");
    fflush (pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].pFile);
    sem_wait (&pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].syncSem);

    dup2 (pHandle->fd_backup, pHandle->fd_original);
    dup2 (pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].fd_backup, pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].fd_original);
    close (pHandle->fd_original);
    close (pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].fd_original);

    close (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID]);

    pthread_join (pHandle->child_thread, &rett);

    pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDERR_ID].report_cbfct = NULL;
    pxOutStreamsHandle->stream[NHT_RPC_POSIX_STDOUT_ID].report_cbfct = NULL;
  }
  else
  {
    for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
    {
      TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

      if (pHandle->report_cbfct)
      {
        fprintf (pHandle->pFile, "\004");
        fflush (pHandle->pFile);
        sem_wait (&pHandle->syncSem);
        dup2 (pHandle->fd_backup, pHandle->fd_original);
        close (pHandle->fd_backup);
        close (pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID]);
      }
    }

    for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
    {
      TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

      if (pHandle->report_cbfct)
      {
        pthread_join (pHandle->child_thread, &rett);
        pHandle->report_cbfct = NULL;
      }
    }
  }

  for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
  {
    TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

    sem_destroy (&pHandle->syncSem);
  }

  /* printf ("[NHT server PID=%d] 'stdout/stderr' redirection restored.\n", (int)getpid()); */
  return 0;
}


/* */
int rpc_posix_flush_redirected_outputStreams
(
  TRpc_POSIX_outStreamsHandle * pxOutStreamsHandle
)
{
  int i;

  for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
  {
    TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

    if ((pHandle->report_cbfct != NULL) && (pHandle->child_thread == pthread_self())) return 0;
  }

  for (i=0; i < _NHT_RPC_POSIX_MAX_STD_STREAMS; i++)
  {
    TRpc_POSIX_outStreamHandle * pHandle = &pxOutStreamsHandle->stream[i];

    if ((pHandle->report_cbfct != NULL) && (pHandle->child_thread != pthread_self()))
    {
      fprintf (pHandle->pFile, "\006");
      fflush (pHandle->pFile);
      sem_wait (&pHandle->syncSem);
    }
  }

  return 0;
}


/* */
static void * posix_outStreamReport_main
(
  void * pxArg
)
{
  TRpc_POSIX_outStreamHandle * pHandle;
  char                       * pBuffer = NULL;
  char                       * pCurPtr = NULL;
  int                          read_fd;
  int                          mallocSize;
  int                          usedSize;
  ssize_t                      readSize;
  int                          syncEnable = 0;
  int                          quitEnable = 0;

  /* TODO: Get */
  pHandle = (TRpc_POSIX_outStreamHandle*)pxArg;
  read_fd = pHandle->pipe_fd[_NHT_RPC_POSIX_STDEO_PIPE_FD_RD_ID];


  /* Initialized the temporary line print buffer with it default size */
  mallocSize = 1024;
  pBuffer    = (char*)MSGBUF_SYS_malloc (mallocSize);
  usedSize   = 0;
  pCurPtr    = pBuffer;

  for (;;)
  {
    errno = 0;
    readSize = read (read_fd, pCurPtr, 1);

    if (readSize < 0) continue;

#if 0
    if (readSize < 0)
    {
      if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) continue;
      pCurPtr[0] = 0;
      pHandle->report_cbfct (pBuffer);
      break;
    }
#endif
    if (readSize > 0)
    {
      if ((pCurPtr[0] == '\006') || (pCurPtr[0] == '\004'))
      {
        if (pCurPtr != pBuffer)
        {
          pCurPtr[0] = 0x0A;
          syncEnable = 1;
          if (pCurPtr[0] == '\004') quitEnable = 1;
        }
        else
        {
          sem_post (&pHandle->syncSem);
          if (pCurPtr[0] == '\004') break;
          continue;
        }

        if (pCurPtr[0] == '\004') quitEnable = 1;
      }

      if ((pCurPtr[0] == 0x0D) && (usedSize == 0)) continue;

      if (pCurPtr[0] == 0x0A)
      {
        pCurPtr[0] = 0;
        pHandle->report_cbfct (pBuffer);
        pCurPtr = pBuffer;
        usedSize = 0;

        if (syncEnable)
        {
          syncEnable = 0;
          sem_post (&pHandle->syncSem);
        }

        if (quitEnable) break;
      }
      else
      {
        usedSize++;
        pCurPtr++;
        if (usedSize == mallocSize)
        {
          char * pTmpBuffer = pBuffer;
          mallocSize += 1024;
          pBuffer = (char*)MSGBUF_SYS_malloc (mallocSize);
          MSGBUF_SYS_memcpy (pBuffer, pTmpBuffer, usedSize);
          MSGBUF_SYS_free (pTmpBuffer);
          pCurPtr = &pBuffer[usedSize];
        }
      }
    }
  }

  return NULL;
}
