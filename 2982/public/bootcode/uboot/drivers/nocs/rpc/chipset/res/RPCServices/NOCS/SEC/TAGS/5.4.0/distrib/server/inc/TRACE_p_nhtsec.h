/**
 * File: $Id:$
 *
 *  This file implements the server specific SEC API/EAPI function traces.
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


#ifndef _TRACE_NV_NHTSEC_H_
#define _TRACE_NV_NHTSEC_H_

/**
 * File: $Id:$
 *
 *  This file implements the server SEC API/EAPI function traces.
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


#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "ca_sec.h"
#include "ca_nhtsec.h"
#include "inc/nv_nhtsec.h"
#include "inc/rpc_ftrace.h"


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

#ifdef _NHT_RPC_TRACE_ON_
#define TRACE_nhtsec_r2r_monteCarlo_test_run  nhtsec_r2r_testAlgo_run
#else
#define nhtsec_r2r_monteCarlo_test_run nhtsec_r2r_testAlgo_run
#endif /*  _NHT_RPC_TRACE_ON_ */

#ifdef __cplusplus
}
#endif

#endif /* _TRACE_NV_NHTSEC_H_ */
