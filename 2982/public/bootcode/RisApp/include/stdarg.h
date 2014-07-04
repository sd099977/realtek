/*
 * Copyright (c) 1996-2003 MIPS Technologies, Inc.  All rights reserved.
 * 
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 * 
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies").  Any copying, reproducing, modifying or use of this
 * code (in whole or in part) that is not expressly permitted in writing
 * by MIPS Technologies or an authorized third party is strictly
 * prohibited.  At a minimum, this code is protected under unfair
 * competition and copyright laws.  Violations thereof may result in
 * criminal penalties and fines.
 * 
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise.  MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of
 * any error or omission in such code.  Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the
 * implied warranties of merchantability or fitness for a particular
 * purpose, are excluded.  Except as expressly provided in any written
 * license agreement from MIPS Technologies or an authorized third party,
 * the furnishing of this code does not give recipient any license to any
 * intellectual property rights, including any patent rights, that cover
 * this code.
 * 
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 * 
 * This code constitutes one or more of the following: commercial
 * computer software, commercial computer software documentation or other
 * commercial items.  If the user of this code, or any related
 * documentation of any kind, including related technical data or
 * manuals, is an agency, department, or other entity of the United
 * States government ("Government"), the use, duplication, reproduction,
 * release, modification, disclosure, or transfer of this code, or any
 * related documentation of any kind, is restricted in accordance with
 * Federal Acquisition Regulation 12.212 for civilian agencies and
 * Defense Federal Acquisition Regulation Supplement 227.7202 for
 * military agencies.  The use of this code by the Government is further
 * restricted in accordance with the terms of the license agreement(s)
 * and/or applicable contract terms and conditions covering this code
 * from MIPS Technologies or an authorized third party.
 */

/*
 * stdarg.h : ANSI stdarg definitions
 */


#ifndef __STDARG_H

#ifndef __need___va_list
#define __STDARG_H
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)

/* CPU-independent macros for GNU C 2.96 and above */

#ifndef __VA_LIST
#define __VA_LIST
/* A generally safe declaration for stdio.h, without loading
   everything else and polluting the namespace */
typedef __builtin_va_list __va_list;
#endif

/* Define the standard macros for the user,
   if this invocation was from the user program.  */
#ifndef __need___va_list

#ifdef  __VARARGS_H

/* These macros implement traditional (non-ANSI) varargs
   for GNU C.  */
#define va_alist  __builtin_va_alist

/* ??? We don't process attributes correctly in K&R argument context.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
typedef int __builtin_va_alist_t __attribute__((__mode__(__arg__)));
#elif __mips64 && ! #abi(32) && ! __mips_algabi
typedef long long __builtin_va_alist_t;
#else
typedef int __builtin_va_alist_t;
#endif

/* ??? It would be nice to get rid of the ellipsis here.  It causes
   current_function_varargs to be set in cc1.  */
#define va_dcl		__builtin_va_alist_t __builtin_va_alist; ...
#define va_start(v)	__builtin_varargs_start((v))

#else

/* These macros implement ANSI stdarg for GNU C.  */

/* Note that the type used in va_arg is supposed to match the
   actual type **after default promotions**.
   Thus, va_arg (..., short) is not valid.  */
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4))        /* add by alan */
#define va_start(v,l)   __builtin_va_start((v),l)                       /* add by alan */
#else                                                                   /* add by alan */
#define va_start(v,l)	__builtin_stdarg_start((v),l)
#endif                                                                  /* add by alan */

#endif

/* These macros are common.  */

#define va_end		__builtin_va_end
#define va_arg		__builtin_va_arg
#if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L
#define va_copy(d,s)	__builtin_va_copy((d),(s))
#endif
#define __va_copy(d,s)	__builtin_va_copy((d),(s))

/* Define va_list from __va_list */
typedef __va_list va_list;

#endif /* ! __need__va_list */

#else /* __GNUC__ < 2.96 */

#ifndef __VA_LIST
#define __VA_LIST
/* A generally safe declaration for stdio.h, without loading
   everything else and polluting the namespace */
typedef void *__va_list;
#endif

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
/* For GNU C library */
typedef char *__gnuc_va_list;
#endif

#if defined(__need___va_list)
/* dummy only for stdio.h */
#elif	defined(__spur__)
#include "spur/sa-spur.h"
#elif	defined(__MIPSEB__) || defined(__MIPSEL__)
#include "mips/stdarg.h"
#elif	defined(__i860__)
#include "i860/sa-i860.h"
#elif	defined(__pyr__)
#include "pyr/sa-pyr.h"
#elif 	defined(__NeXT__)
#include "NeXT/sa-NeXT.h"
#elif 	defined(__sparc__)
#include "sparc/stdarg.h"
#elif 	defined(__mc68000__) || defined(__i386__) || defined(__ns32000__)
/* standard basic */

typedef char *va_list;

/* Amount of space required in an argument list for an arg of type TYPE.
   TYPE may alternatively be an expression whose type is used.  */

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#ifdef __VARARGS_H
/* old-style, non-ANSI compatibility */
#define va_alist __builtin_va_alist;
#define va_dcl   int __builtin_va_alist; ...

#define va_start(AP) \
  AP = (char *)&__builtin_va_alist;
#else
/* new-style ANSI */
#define va_start(AP, LASTARG) 						\
 (AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#endif

void va_end (va_list);		/* Defined in gnulib ?? */
#define va_end(AP)

#define va_arg(AP, TYPE)						\
 (AP += __va_rounded_size (TYPE),					\
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

#else
#error "stdarg.h"
#endif

#endif /* __GNUC__ >= 2.96 */

#undef __need___va_list

#endif /* !defined __STDARG_H */
