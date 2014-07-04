/**
 * File: $Id:$
 *
 *  This file implements the Nagra specific extended CTD API functions.
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

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/msgbuf_sys_string.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/TRACE_nhtctd.h"

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/


TCtdStatus nhtCtdGetApiVersion
(
  TCtdUnsignedInt32*  pxNhtCtdApiVersion
)
{
  TCtdStatus ctdStatus = CTD_NO_ERROR;

  if (pxNhtCtdApiVersion) *pxNhtCtdApiVersion = (TCtdUnsignedInt32)NHT_CTDAPI_VERSION_INT;
  else ctdStatus = CTD_ERROR;

  return ctdStatus;
}
