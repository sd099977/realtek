/**
 * File: $Id:$
 *
 *  This file implements string manipulation basics functions
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


#include "inc/msgbuf_sys_string.h"


/* */
char MSGBUF_SYS_toupper
(
  char c
)
{
  if ((c >= 'a') && (c <= 'z')) c -= 32;
  return c;
}


/* */
size_t MSGBUF_SYS_strlen
(
  const char * pxStr
)
{
  size_t cnt = 0;

  while (*pxStr)
  {
    pxStr++;
    cnt++;
  }

  return cnt;
}


/* */
char * MSGBUF_SYS_strcpy
(
  char       * pxDest,
  const char * pxSrc
)
{
  char * pPtr = pxDest;

  while (*pxSrc) *pPtr++ = *pxSrc++;
  *pPtr = '\0';

  return pxDest;
}


/* */
char * MSGBUF_SYS_strncpy
(
  char       * pxDest,
  const char * pxSrc,
  size_t       xCnt
)
{
  char * pPtr = pxDest;

  while (*pxSrc && (xCnt > 0))
  {
    *pPtr++ = *pxSrc++;
    xCnt--;
  }
  if (xCnt > 0) *pPtr = '\0';

  return pxDest;
}


/* */
size_t MSGBUF_SYS_xstrncpy
(
  char       * pxDest,
  const char * pxSrc,
  size_t       xCnt
)
{
  char   * pPtr = pxDest;
  size_t   copied = 0;

  while (*pxSrc && (xCnt > 1))
  {
    *pPtr++ = *pxSrc++;
    xCnt--;
    copied++;
  }
  *pPtr = '\0';

  return copied;
}


/* */
int MSGBUF_SYS_strcmp
(
  const char * pxDest,
  const char * pxSrc
)
{
  while (*pxSrc && *pxDest)
  {
    if (*pxDest < *pxSrc) return -1;
    if (*pxDest > *pxSrc) return 1;
    pxDest++;
    pxSrc++;
  }

  if (*pxDest && !*pxSrc) return 1;
  if (!*pxDest && *pxSrc) return -1;
  return 0;
}


/* */
int MSGBUF_SYS_strncmp
(
  const char * pxDest,
  const char * pxSrc,
  size_t       xCnt
)
{
  size_t i = 0;

  while ((*pxSrc && *pxDest) && (i < (xCnt - 1) ))
  {
    if (*pxDest < *pxSrc) return -1;
    if (*pxDest > *pxSrc) return 1;
    pxDest++;
    pxSrc++;
    i++;
  }

  if (*pxDest == *pxSrc)
    return 0;
  else if (*pxDest > *pxSrc)
    return 1;
  else
    return -1;
}


/* */
int MSGBUF_SYS_strcmpi
(
  const char * pxDest,
  const char * pxSrc
)
{
  char dc,sc;

  while (*pxSrc && *pxDest)
  {
    dc = MSGBUF_SYS_toupper(*pxDest);
    sc = MSGBUF_SYS_toupper(*pxSrc);
    if (dc < sc) return -1;
    if (dc > sc) return 1;
    pxDest++;
    pxSrc++;
  }

  if (*pxDest && !*pxSrc) return 1;
  if (!*pxDest && *pxSrc) return -1;
  return 0;
}


/* */
char * MSGBUF_SYS_strchr
(
  const char * pxDest,
  int          c
)
{
  while (*pxDest)
  {
    if (*pxDest == c) return (char *) pxDest;
    pxDest++;
  }
  return NULL;
}


/* */
char * MSGBUF_SYS_strstr
(
  const char * pxDest,
  char       * pxFind
)
{
  size_t   len;
  char   * s = (char *) pxDest;

  len = MSGBUF_SYS_strlen (pxFind);

  while (*s != 0)
  {
    if (!MSGBUF_SYS_strncmp (s, pxFind, len) != 0) return s;
    s++;
  }
  return NULL;
}


/* */
char * MSGBUF_SYS_strnchr
(
  const char * pxDest,
  int          c,
  size_t       xCnt
)
{
  while (*pxDest && (xCnt > 0))
  {
    if (*pxDest == c) return (char *) pxDest;
    pxDest++;
    xCnt--;
  }
  return NULL;
}


/* */
char * MSGBUF_SYS_strrchr
(
  const char * pxDest,
  int          c
)
{
  char * pRet = NULL;

  while (*pxDest)
  {
    if (*pxDest == c) pRet = (char *) pxDest;
     pxDest++;
  }

  return pRet;
}


/* */
int MSGBUF_SYS_memcmp
(
  const void * pxDest,
  const void * pxSrc,
  size_t       xCnt
)
{
  const unsigned char * d;
  const unsigned char * s;

  d = (const unsigned char *) pxDest;
  s = (const unsigned char *) pxSrc;

  while (xCnt)
  {
    if (*d < *s) return -1;
    if (*d > *s) return 1;
    d++; s++; xCnt--;
  }

  return 0;
}


/* */
void * MSGBUF_SYS_memcpy
(
  void       * pxDest,
  const void * pxSrc,
  size_t       xCnt
)
{
  unsigned char       * d;
  const unsigned char * s;

  d = (unsigned char *) pxDest;
  s = (const unsigned char *) pxSrc;

  while (xCnt)
  {
    *d++ = *s++;
    xCnt--;
  }

  return pxDest;
}


/* */
void * MSGBUF_SYS_memset
(
  void   * pxDest,
  int      c,
  size_t   xCnt
)
{
  unsigned char * d;

  d = (unsigned char*)pxDest;

  while (xCnt)
  {
    *d++ = (unsigned char) c;
    xCnt--;
  }

  return d;
}



/* */
void MSGBUF_SYS_strupr
(
  char * pxStr
)
{
  while (*pxStr)
  {
    *pxStr = MSGBUF_SYS_toupper (*pxStr);
    pxStr++;
  }
}


/* */
char * MSGBUF_SYS_strcat
(
  char       * pxDest,
  const char * pxSrc
)
{
  char * pPtr = pxDest;

  while (*pPtr) pPtr++;
  while (*pxSrc) *pPtr++ = *pxSrc++;
  *pPtr = '\0';

  return pxDest;
}


/* */
#define MSGBUF_SYS_isspace(x) (((x) == ' ') || ((x) == '\t'))


/* */
char * MSGBUF_SYS_gettoken
(
  char ** pPtr
)
{
  char * p = *pPtr;
  char * pRet;

  /* skip white space */

  while (*p && MSGBUF_SYS_isspace(*p)) p++;
  pRet = p;

  /* check for end of string */

  if (!*p)
  {
    *pPtr = p;
    return NULL;
  }

  /* skip non-whitespace */

  while (*p)
  {
    if (MSGBUF_SYS_isspace(*p)) break;

    /* do quoted strings */

    if (*p == '"')
    {
      p++;
      pRet = p;
      while (*p && (*p != '"')) p++;
      if (*p == '"') *p = '\0';
    }
    p++;
  }

  if (*p) *p++ = '\0';
  *pPtr = p;

  return pRet;
}


/* */
int MSGBUF_SYS_atoi
(
  const char * pxDest
)
{
  int x = 0;
  int digit;

  if ((*pxDest == '0') && (*(pxDest+1) == 'x'))
  {
    return MSGBUF_SYS_xtoi(pxDest+2);
  }

  while (*pxDest)
  {
    if ((*pxDest >= '0') && (*pxDest <= '9'))
    {
      digit = * pxDest - '0';
    }
    else break;

    x *= 10;
    x += digit;
    pxDest++;
  }

  return x;
}


/* */
int MSGBUF_SYS_xtoi
(
  const char * pxDest
)
{
  int x = 0;
  int digit;

  if ((*pxDest == '0') && (*(pxDest+1) == 'x')) pxDest += 2;

  while (*pxDest)
  {
    if ((*pxDest >= '0') && (*pxDest <= '9'))
      digit = *pxDest - '0';
    else if ((*pxDest >= 'A') && (*pxDest <= 'F'))
      digit = 10 + *pxDest - 'A';
    else if ((*pxDest >= 'a') && (*pxDest <= 'f'))
      digit = 10 + *pxDest - 'a';
    else break;

    x *= 16;
    x += digit;
    pxDest++;
  }

  return x;
}


#if 0
/* */
uint64_t MSGBUF_SYS_xtoq
(
  const char * pxDest
)
{
  uint64_t x = 0;
  unsigned int digit;

  if ((*pxDest == '0') && (*(pxDest+1) == 'x')) pxDest += 2;

  while (*pxDest)
  {
    if ((*pxDest >= '0') && (*pxDest <= '9'))
      digit = *pxDest - '0';
    else if ((*pxDest >= 'A') && (* pxDest <= 'F'))
      digit = 10 + *pxDest - 'A';
    else if ((*pxDest >= 'a') && (*pxDest <= 'f'))
      digit = 10 + *pxDest - 'a';
    else break;

    x *= 16;
    x += digit;
    pxDest++;
  }

  return x;
}
#endif

