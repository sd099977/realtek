/**
 * File: $Id:$
 *
 *  This header file defines the MSGBUF main types.
 *
 *  Copyright (c) 2012 Nagravision. All rights reserved.
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

#ifndef _MSGBUF_SYS_STRING_H_
#define _MSGBUF_SYS_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>


/* */
char MSGBUF_SYS_toupper (
  char c );


/* */
size_t MSGBUF_SYS_strlen (
  const char * pxStr );


/* */
char * MSGBUF_SYS_strcpy (
  char       * pxDest,
  const char * pxSrc );


/* */
char * MSGBUF_SYS_strncpy (
  char       * pxDest,
  const char * pxSrc,
  size_t       xCnt );


/* */
size_t MSGBUF_SYS_xstrncpy (
  char       * pxDest,
  const char * pxSrc,
  size_t       xCnt );


/* */
int MSGBUF_SYS_strcmp (
  const char * pxDest,
  const char * pxSrc );


/* */
int MSGBUF_SYS_strncmp (
  const char * pxDest,
  const char * pxSrc,
  size_t       xCnt );


/* */
int MSGBUF_SYS_strcmpi (
  const char * pxDest,
  const char * pxSrc );


/* */
char * MSGBUF_SYS_strchr (
  const char * pxDest,
  int          c );


/* */
char * MSGBUF_SYS_strstr (
  const char * pxDest,
  char       * pxFind );


/* */
char * MSGBUF_SYS_strnchr (
  const char * pxDest,
  int          c,
  size_t       xCnt );


/* */
char * MSGBUF_SYS_strrchr (
  const char * pxDest,
  int          c );


/* */
int MSGBUF_SYS_memcmp (
  const void * pxDest,
  const void * pxSrc,
  size_t       xCnt );


/* */
void * MSGBUF_SYS_memcpy (
  void       * pxDest,
  const void * pxSrc,
  size_t       xCnt );

/* */
void * MSGBUF_SYS_memset (
  void   * pxDest,
  int      c,
  size_t   xCnt );


/* */
void MSGBUF_SYS_strupr (
  char * pxStr );


/* */
char * MSGBUF_SYS_strcat (
  char       * pxDest,
  const char * pxSrc );


/* */
char * MSGBUF_SYS_gettoken (
  char ** pPtr );


/* */
int MSGBUF_SYS_atoi (
  const char * pxDest );


/* */
int MSGBUF_SYS_xtoi (
  const char * pxDest );

#if 0
/* */
uint64_t MSGBUF_SYS_xtoq (
  const char * pxDest );
#endif

#ifdef __cplusplus
}
#endif

#endif /* define _MSGBUF_SYS_STRING_H_ */


