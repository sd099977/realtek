/**
 * File: $Id:$
 *
 *  This file implements the Nagra specific extended REPORT API functions.
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

#include "inc/nv_nht_report.h"


/* CM server application version name */
#ifndef NHT_SERVER_APP_VERSION_STR
#define NHT_SERVER_APP_VERSION_STR "<not_specified>"
#endif

/* NHT server lib vervion name  */
#ifndef NHT_COMPONENT_VERSION_STR
#define NHT_COMPONENT_VERSION_STR "<not_specified>"
#endif


/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Get the CM-defined server version string
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
const char * nht_getCmServerVersion (void)
{
  return NHT_SERVER_APP_VERSION_STR;
}


/**
 *  @ingroup ll_report_func
 *
 *  @brief
 *    Get the NHT server lib version string
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
*/
const char * nht_getNhtServerComponentVersion (void)
{
  return NHT_COMPONENT_VERSION_STR;
}
