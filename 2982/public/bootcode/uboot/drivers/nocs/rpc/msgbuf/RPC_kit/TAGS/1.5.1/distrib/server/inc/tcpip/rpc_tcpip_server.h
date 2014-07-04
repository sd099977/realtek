/**
 * File: $Id:$
 *
 *  This header file implements the RPC basic server feature.
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

#ifndef _RPC_TCPIP_SERVER_H_
#define _RPC_TCPIP_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include "inc/xsd-c.h"

typedef enum
{
  SRV_STRAGETY_PROCESS_VERSUS,
  SRV_STRAGETY_THREAD_VERSUS_STRATEGY
} TServerStrategy;


typedef int (*TProcessInitResourceFct)(void);
typedef int (*TProcessTerminateResourceFct)(void);
typedef int (*TPosixOutStreamReportCbfct) (const char * pxText);


/* */
int rpc_start_server (
  uint16_t                      xPort,
  int                           xBackLog,
  TServerStrategy               xStrategy,
  TProcessInitResourceFct       xProcessInitResFct,
  TProcessTerminateResourceFct  xProcessTerminateResFct,
  int                           xServiceNumber,
  const TMsgBuf_serviceHandle * pxServiceSet[],
  TPosixOutStreamReportCbfct    xStdout_redirect_cbfct,
  TPosixOutStreamReportCbfct    xStderr_redirect_cbfct );


#ifdef __cplusplus
}
#endif

#endif /* _RPC_TCPIP_SERVER_H_ */
