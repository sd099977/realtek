/**
 * File: $Id:$
 *
 *  This file implements string builder utilily functions.
 *
 *  Copyright (c) 2013 Nagravision. All rights reserved.
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


#ifndef _MSGBUF_STR_BUILDER_H_
#define _MSGBUF_STR_BUILDER_H_


#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/msgbuf_types.h"


/***************************************************************************/
/*                                                                         */
/*                         TYPE DEFINITIONS                                */
/*                                                                         */
/***************************************************************************/

/* */
typedef struct SMsgbufStrBuffer
{
  char * pBuffer;
  int    bufferSize;
  int    curSize;

} TMsgbufStrBuffer;


/***************************************************************************/
/*                                                                         */
/*                   Function declarations                                 */
/*                                                                         */
/***************************************************************************/

/* */
void msgbuf_strbuilder_buffer_init (
  TMsgbufStrBuffer * pxNhtStrBuffer );

/* */
void msgbuf_strbuilder_buffer_terminate (
  TMsgbufStrBuffer * pxNhtStrBuffer );

/* */
void msgbuf_strbuilder_buffer_empty (
  TMsgbufStrBuffer * pxNhtStrBuffer );

/* */
int msgbuf_strbuilder_buffer_extSize (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  int             xExtSize );


/* */
void msgbuf_strbuilder_add_string (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxString );

/* */
int msgbuf_strbuilder_add_hexchar_value (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  unsigned char      xByte );

/* */
void msgbuf_strbuilder_add_buffer_value (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const void       * pxLineHeaderStr,
  const void       * pxByteArray,
  int                xSize );

/* */
void msgbuf_strbuilder_add_uchar (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  unsigned char      xNumber );

/* */
void msgbuf_strbuilder_add_hex_value (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  size_t             xNumber,
  size_t             xNumberSize );

/* */
void msgbuf_strbuilder_add_dec_value (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  size_t             xNumber );

/* */
void msgbuf_strbuilder_add_pointer (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const void       * pxPointer );


/* */
void msgbuf_strbuilder_setparam_buffer (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  const void       * pxByteArray,
  int                xSize );

/* */
void msgbuf_strbuilder_setparam_string (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  const char       * pxString );

/* */
void msgbuf_strbuilder_setparam_uchar (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  unsigned char      xNumber );

/* */
void msgbuf_strbuilder_setparam_pointer (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  const void       * pxPointer );

/* */
void msgbuf_strbuilder_setparam_hex_value (
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  size_t             xNumber,
  size_t             xNumberSize );


#ifdef __cplusplus
}
#endif

#endif /* _MSGBUF_STR_BUILDER_H_ */
