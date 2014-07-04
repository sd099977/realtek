/**
 * File: $Id:$
 *
 *  This file implements the Nagra specific extended CSD API functions.
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

#include <stddef.h>
#include "inc/nv_nhtbsd.h"
#include "inc/msgbuf_sys_string.h"
#include "inc/os/none/serial_rpc_service.h"


/* */
TBsdStatus nhtGetNhtBsdApiVersion
(
  TUnsignedInt32*  pxNhtBsdApiVersion
)
{
  TBsdStatus bsdStatus = BSD_NO_ERROR;

  if (pxNhtBsdApiVersion)
  {
    *pxNhtBsdApiVersion = BSD_TOOL_VERSION_INT (
      NHTBSDAPI_VERSION_MAJOR,
      NHTBSDAPI_VERSION_MEDIUM,
      NHTBSDAPI_VERSION_MINOR);
  }
  else bsdStatus = BSD_ERROR_INVALID_PARAMETERS;

  return bsdStatus;
}


/* */
TBsdStatus nhtBsdGetBsdStatusOffsetValue
(
  TUnsignedInt32 * pxBsdOffsetValue
)
{
  TBsdStatus bsdStatus = BSD_NO_ERROR;

  if (pxBsdOffsetValue)
  {
    *pxBsdOffsetValue = (TUnsignedInt32)BSD_STATUS_OFFSET;
  }
  else bsdStatus = BSD_ERROR_INVALID_PARAMETERS;

  return bsdStatus;
}


/* */
TBsdStatus nhtbsd_r2r_monteCarlo_test_run
(
  const TNhtBsd_r2r_test_algoParams * pxInputParams,
  TUnsignedInt8                     * pxOutputData
)
{
  return nhtbsd_r2r_testAlgo_run (pxInputParams, pxOutputData);
}


/* */
TBsdStatus nhtBsdServerTerminate (void)
{
  serialRpcService_terminate (NULL);
  return BSD_NO_ERROR;
}