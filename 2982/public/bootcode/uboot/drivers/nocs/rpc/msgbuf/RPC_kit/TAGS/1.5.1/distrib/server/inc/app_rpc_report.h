/**
 * File: $Id:$
 *
 *  This header file defines the rpc standard report functions.
 *  User is free to implement the functions described here below
 *  in order to export rpc report notification to its application.
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

#ifndef _RPC_SYS_REPORT_H_
#define _RPC_SYS_REPORT_H_

#ifdef __cplusplus
extern "C" {
#endif


/* */
typedef void (*_TAppRpcReportFct) (
  const char * pxString );


/* */
void APP_RPC_report_info (
  const char * pxString );


/* */
void APP_RPC_report_error (
  const char * pxString );


/* */
void APP_RPC_report_trace (
  const char * pxString );


/* */
void APP_RPC_report_info_registerCBfct (
  _TAppRpcReportFct xReportFct );


/* */
void APP_RPC_report_error_registerCBfct (
  _TAppRpcReportFct xReportFct );


/* */
void APP_RPC_report_trace_registerCBfct (
  _TAppRpcReportFct xReportFct );


#ifdef __cplusplus
}
#endif

#endif /* _RPC_SYS_REPORT_H_ */
