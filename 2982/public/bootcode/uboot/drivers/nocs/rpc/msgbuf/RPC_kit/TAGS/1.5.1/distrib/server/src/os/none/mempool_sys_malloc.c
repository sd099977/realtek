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
#include "src/os/none/memAlloc.h"

#ifndef NHT_MEMPOOL_BUFFER_SIZE
#define NHT_MEMPOOL_BUFFER_SIZE (1L<<20)
#endif

#define _NHT_MEMPOOL_VOIDP_BUFFER_SIZE (NHT_MEMPOOL_BUFFER_SIZE /sizeof(void*))


/* */
static void * _gMemPool_buffer[_NHT_MEMPOOL_VOIDP_BUFFER_SIZE];
static TMemPool gMemPool = NULL;


/* */
int MSGBUF_SYS_init (void)
{
  if (gMemPool) return 0;

  gMemPool = memPool_init (
    _gMemPool_buffer,
    sizeof(_gMemPool_buffer),
    NULL,
    NULL,
    NULL );
  if (gMemPool) return 0;
  else return -1;
}


/* */
void * MSGBUF_SYS_malloc
(
  size_t xSize
)
{
  if (gMemPool == NULL) return NULL;
  return memPool_malloc (gMemPool, (int)xSize);
}


/* */
void MSGBUF_SYS_free
(
  void * pxData
)
{
  if (gMemPool) memPool_free (gMemPool, pxData);
}


#if defined(_NHT_TRACE_DYN_ALLOCATOR_) && (_NHT_TRACE_DYN_ALLOCATOR_ != 0)
static int _printout
(
  const void     * pxBufferAddress,
  int              xBlockAllocatedSize,
  TMemAllocTrace   xBlockType
)
{
  int i;
  char * pBuffer = (char *)pxBufferAddress;

  printf ("block p=%p, size=%d\n", (void*)pxBufferAddress, (int)xBlockAllocatedSize);
  for (i=0; i<xBlockAllocatedSize; i++)
  {
    if (i%16 == 0) printf ("\n  ");
    printf ("%02X ", (int)pBuffer[i]);
  }
  pBuffer[xBlockAllocatedSize -1] = 0;
  printf ("%s\n", pBuffer);
  printf ("\n");
}
#endif


/* */
int MSGBUF_SYS_terminate (void)
{

#if defined(_NHT_TRACE_DYN_ALLOCATOR_) && (_NHT_TRACE_DYN_ALLOCATOR_ != 0)

  memPool_traceUsedBlock (
    gMemPool,
    MEMALLOC_TRACE_USED_BLOCKS,
    &_printout);
#endif

  return 0;
}
