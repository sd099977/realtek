/**
**  @file base_hndmng.h
**
** @brief
**    Base handler manager.
**
**  <hr>Copyright &copy; 2013 Nagravision. All rights reserved.\n
**  CH-1033 Cheseaux, Switzerland\n
**  Tel: +41 21 7320311  Fax: +41 21 7320100\n
**  http://www.nagra.com
**
**  All trademarks and registered trademarks are the property of their
**  respective owners.
**
**  This document is supplied with an understanding that the notice(s)
**  herein or any other contractual agreement(s) made that instigated the
**  delivery of a hard copy, electronic copy, facsimile or file transfer
**  of this document are strictly observed and maintained.
**
**  The information contained in this document is subject to change without
**  notice.
**
**  Any recipient of this document, without exception, is subject to a
**  Non-Disclosure Agreement (NDA) and access authorization.
**  $Id:$
**  $Change:$
*/

#ifndef _BASE_HNDMNG_H_
#define _BASE_HNDMNG_H_


#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include <stddef.h>
#include "inc/hndmng.h"


/***************************************************************************/
/*                                                                         */
/*                   Function declarations                                 */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup nht_sysBuffer
 *
 *  @brief
 *    Initialize the sysBuffer manager (singleton) if not already
 *    done.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @retval
 *    None
 *
 *  @remark
*/
void base_hndmng_init
(
  TAVLSet * pxSet
);


/**
 *  @ingroup nht_sysBuffer
 *
 *  @brief
 *    Create a local buffer associated to a remote sysBuffer.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]  xSysBufferRemoteHandle
 *    Remote system buffer address
 *
 *  @param[in]  xBufferSize
 *    buffer size
 *
 *  @retval
 *    Return an associated local buffer address
 *
 *  @remark
*/
int base_hndmng_register
(
  TAVLSet            * pxSet,
  void               * pxHandle,
  THndMng_closeCbFct   xCloseHandle_fct
);


/**
 *  @ingroup nht_sysBuffer
 *
 *  @brief
 *    Destroy a system buffer previously created using
 *    the sysbuf_client_create() function.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]  xLocalSysBuffer
 *    Address of the associate local buffer
 *
 *  @retval
 *    Return 0 if an existing system buffer was effectivelly
 *    destroyed.
 *
 *  @remark
 *
*/
int base_hndmng_unregister
(
  TAVLSet * pxSet,
  void    * pxHandle
);


/**
 *  @ingroup nht_sysBuffer
 *
 *  @brief
 *    Check if a local address belongs to a system buffer.
 *    If yes, provide the remote handle address value, as
 *    well as the remote mapped address handle.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]  pxLocalAdr
 *    Local address of a buffer
 *  @param[out]  pxRemoteHandle
 *    Remote address (handle) of the ssociated system remote buffer
 *  @param[out]  pxRemoteAdrHandle
 *    Remote address (handle) within the associate remote buffer
 *
 *  @retval
 *    Return 0 if an existing system buffer was effectivelly
 *    destroyed.
 *
 *  @remark
*/
int base_hndmng_isRegistered
(
  TAVLSet * pxSet,
  void    * pxHandle
);



/**
 *  @ingroup nht_sysBuffer
 *
 *  @brief
 *    Close all references to the system buffer that where
 *    previously created.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]  xCloseSysBuffer_fct
 *    Callback function for remotely deallocate the remote system buffer
 *  @retval
 *    None
 *
 *  @remark
*/
void base_hndmng_terminate
(
  TAVLSet * pxSet
);


#ifdef __cplusplus
}
#endif

#endif /* _BASE_HNDMNG_H_ */
