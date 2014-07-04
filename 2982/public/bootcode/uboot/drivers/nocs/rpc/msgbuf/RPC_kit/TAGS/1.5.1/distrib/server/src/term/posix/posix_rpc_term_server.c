/**
 * File: $Id:$
 *
 *  This file implements the RPC posix client connection function.
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "inc/app_rpc_report.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/term/rpc_term_server.h"
#include "src/os/posix/posix_rpc_stdout_stderr_redirection.h"


TRpc_POSIX_outStreamsHandle gOutStreamsRedictionHandle;
static int fd = -1;


static void rpcTerm_stopClientService
(
  TMsgBuf_rpcHandler xRpcHandle
)
{
  close (fd);
}


static int posixRpcTerm_GetTermPosixSpeedAttr
(
  uint32_t  xSpeed,
  int      * pxPosixSpeedAttr
);

/* */
static int _portRead
(
  void    * pxFd,
  void    * pxBuffer,
  int       xSize
)
{
  int status;

  errno = 0;

#ifdef MSG_WAITALL
  status = recv ((int)pxFd, pxBuffer, xSize, MSG_WAITALL);
#else
  status = read ((int)pxFd, pxBuffer, xSize);
#endif

  if (status <= 0)
  {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
      status = 0;
    else status = -1;
  }

  return status;
}


/* */
static int _portWrite
(
  void          * pxFd,
  const void    * pxBuffer,
  int             xSize
)
{
  int status;

  rpc_posix_flush_redirected_outputStreams (&gOutStreamsRedictionHandle);

  errno = 0;

#ifdef MSG_WAITALL
  status = send ((int)pxFd, pxBuffer, xSize, MSG_WAITALL);
#else
  status = write ((int)pxFd, pxBuffer, xSize);
#endif

  if (status <= 0)
  {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
      status = 0;
    else status = -1;
  }

  return status;
}


/* */
int rpcTerm_startServer
(
  TProcessInitResourceFct        xProcessInitResFct,
  TProcessTerminateResourceFct   xProcessTerminateResFct,
  int                            xServiceNumber,
  const TMsgBuf_serviceHandle  * pxServiceSet[],
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct
)
{
  TMsgBuf_rpcHandler rpcHandler;
  int                status;
  struct termios     options;
  int                posixSpeedAttr;
  int                speed = 115200;
  const char         terminal[] = "/dev/ttyS0";


  status = posixRpcTerm_GetTermPosixSpeedAttr (speed, &posixSpeedAttr);

  if (status < 0)
  {
    char * pText = (char*)MSGBUF_SYS_malloc(1024);
    sprintf(pText,"Unsupported Terminal speed=%d for \'%s@%d\'", (int)speed, terminal);
    printf ("%s\n",pText);
    if (pText) MSGBUF_SYS_free(pText);
    return -1;
  }

  fd = open (terminal, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    char * pText = (char*)MSGBUF_SYS_malloc(1024);
    sprintf(pText,"fail to get terminal connection \'%s\'", terminal);
    printf ("%s\n", pText);
    if (pText) MSGBUF_SYS_free(pText);
    return -1;
  }
  else
  {
    APP_RPC_report_info ("Connection success");
  }

  fcntl (fd, F_SETFL, 0);
  tcgetattr (fd, &options);


  cfsetispeed (&options, posixSpeedAttr);
  cfsetospeed (&options, posixSpeedAttr);
  options.c_cflag |= (CLOCAL |CREAD);

  /* Use 8bits character (without parity) */
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  /* Disable RTS CTS controls */
  /* options.c_cflag &= ~CNEW_RTSCTS; */

  /* Use Input Raw mode */
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP| IXON);

  /* Set Output for raw data */
  options.c_oflag &= ~OPOST;

  options.c_cc[VMIN] = 0; options.c_cc[VTIME] = 50;
  tcsetattr (fd, TCSANOW | TCSAFLUSH, &options);

  rpcHandler = pPosixRpcService_createHandle ( (void*)fd, xServiceNumber, pxServiceSet, &_portWrite, &_portRead);
  if (rpcHandler == NULL)
  {
    APP_RPC_report_error ("Allocation failure");
    return -1;
  }

  rpc_redirect_outputStreams (
    &gOutStreamsRedictionHandle,
    xStdout_redirect_cbfct,
    xStderr_redirect_cbfct );

  posixRpcService_main ((void*)rpcHandler );

  rpc_restore_outputStreams (&gOutStreamsRedictionHandle);

  rpcTerm_stopClientService (rpcHandler);
  rpcHandler = NULL;

  return 0;
}



static int posixRpcTerm_GetTermPosixSpeedAttr
(
  uint32_t  xSpeed,
  int      * pxPosixSpeedAttr
)
{
  int status = 0;
  switch (xSpeed)
  {
    case 9600:   *pxPosixSpeedAttr = B9600;   break;
    case 19200:  *pxPosixSpeedAttr = B19200;  break;
    case 38400:  *pxPosixSpeedAttr = B38400;  break;
    case 57600:  *pxPosixSpeedAttr = B57600;  break;
    /* case 76800:  *pxPosixSpeedAttr = B76800;  break; */
    case 115200: *pxPosixSpeedAttr = B115200; break;
    default: status = -1; break;
  }

  return status;
}

int nhtBsdPort_open (void)
{
  return 0;
}
