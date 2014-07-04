
#ifndef RTK_BSD_H
#define RTK_BSD_H


/**
 * Defines the version number of the BSD API. Note also that this version number
 * does not correspond to the version number of the software version.
 * @warning Do not update these values
*/
#define RTK_BSDAPI_VERSION_MAJOR  0001
#define RTK_BSDAPI_VERSION_MEDIUM 0000
#define RTK_BSDAPI_VERSION_MINOR  0000

#include "nocs_bsd.h"

/******************************************************************************/
/*                                                                            */
/*                               INCLUDE FILES                                */
/*                                                                            */
/******************************************************************************/



/******************************************************************************/
/*                                                                            */
/*                             OVERALL DOCUMENTATION                          */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*                              VERSION TOOL                                  */
/*                                                                            */
/******************************************************************************/
#define RTKAPI_VERSION_INTER BSD_TOOL_VERSION(RTK_BSDAPI_VERSION_MAJOR, \
              RTK_BSDAPI_VERSION_MEDIUM, \
              RTK_BSDAPI_VERSION_MINOR)

#define RTK_BSD_SOFTWARE_VERSION  BSD_TOOL_STRINGIFY(RTKAPI_VERSION_INTER)

//#define RTK_BSD_SOFTWARE_VERSION "0001.0000.0000"

//#define cr_writel(value,addr)   	rtd_outl(addr,value)
//#define cr_readl(addr)          	rtd_inl(addr)



#endif /* RTK_BSD_H */

/* rtk_bsd.h */
