/**
 * File: $Id:$
 *
 *  This header file implements the MSGBUF low-level allocation functions.
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

#ifndef _MSGUBG_ALLOC_H_
#define _MSGUBG_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "inc/xsd-c.h"


/* Init a preallocated message content with its default value */
void msgbuf_init_generic_message (
  const TMsgBuf_messageDescriptor * pxMsgDesc,
  TMsgBuf_message                 * pxMessage );


TMsgBuf_message * protobuf_c_allocate_init_message (
  const TMsgBuf_messageDescriptor * pxMsgDesc );


void protobuf_c_deallocate_message (
  TMsgBuf_message * pxMessage );


#ifdef __cplusplus
}
#endif

#endif /* ifndef _MSGUBG_ALLOC_H_ */
