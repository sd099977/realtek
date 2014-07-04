/**
 * File: $Id:$
 *
 *  This header file implements the dynamic memory allocation abstraction
 *  layer as a wrapper to an existing undelying OS.
 *
 *  This abstraction layer is intended to improve the OS portability
 *  of the msgbuf services. It also permits to abstract his feature for
 *  application not running on an OS (e.g: memory pool allocation)
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
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>


static pthread_mutex_t gAllocMutex;

/* */
int MSGBUF_SYS_init (void)
{
  pthread_mutex_init (&gAllocMutex, NULL);
  return 0;
}


/* */
void * MSGBUF_SYS_malloc
(
  size_t xSize
)
{
  void * pData;

  pthread_mutex_lock (&gAllocMutex);
  pData = malloc (xSize);
  pthread_mutex_unlock (&gAllocMutex);
  return pData;
}

/* */
void MSGBUF_SYS_free
(
  void * pxData
)
{
  pthread_mutex_lock (&gAllocMutex);
  free (pxData);
  pthread_mutex_unlock (&gAllocMutex);
}

/* */
int MSGBUF_SYS_terminate (void)
{
  pthread_mutex_destroy (&gAllocMutex);
  return 0;
}
