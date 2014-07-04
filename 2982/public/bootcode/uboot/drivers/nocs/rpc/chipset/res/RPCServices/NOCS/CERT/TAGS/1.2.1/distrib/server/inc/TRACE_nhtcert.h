/**
 * File: $Id:$
 *
 *  This file implements the server/client common CERT API/EAPI function traces.
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


#ifndef _TRACE_NHTCERT_H_
#define _TRACE_NHTCERT_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "inc/rpc_ftrace.h"
#include "inc/nv_nhtcert.h"
#include "ca_cert.h"


#ifdef _NHT_RPC_TRACE_ON_

/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

/* */
TCertFunctionTable * _CRPC(certGetFunctionTable) (void);

#endif /* _NHT_RPC_TRACE_ON_ */

#ifdef __cplusplus
}
#endif

#endif /* _TRACE_NHTCERT_H_ */