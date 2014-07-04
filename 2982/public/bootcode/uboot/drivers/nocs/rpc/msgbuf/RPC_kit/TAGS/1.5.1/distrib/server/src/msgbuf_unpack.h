/**
 * File: $Id:$
 *
 *  This header file implements the MSGBUF base unpacking functions.
 *
 *  PS: Unpacking refers to the generation a MSGBUF message structure associated
 *  to a MSGBUF data buffer.
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

#ifndef _MSGUBG_UNPACK_H_
#define _MSGUBG_UNPACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "inc/xsd-c.h"

/* */
int msgbuf_unpack_message_content (
  const TMsgBuf_messageDescriptor * pxMsgDesc,
  TMsgBuf_message                 * pxMessage,
  const uint8_t                    * pxIn,
  const uint8_t                    * pxEnd );

#ifdef __cplusplus
}
#endif

#endif /* ifndef _MSGUBG_UNPACK_H_ */
