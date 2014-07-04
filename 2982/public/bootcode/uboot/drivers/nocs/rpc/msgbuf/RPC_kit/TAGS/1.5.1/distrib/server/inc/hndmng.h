
#ifndef _HNDMNG_H_
#define _HNDMNG_H_


#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include <stddef.h>
#include "inc/avlset.h"



/***************************************************************************/
/*                                                                         */
/*                   Function declarations                                 */
/*                                                                         */
/***************************************************************************/


/* */
typedef int (*THndMng_closeCbFct)
(
  void *  pxHandleAdr
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
int hndmng_register
(
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
int hndmng_unregister
(
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
int hndmng_isRegistered
(
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
void hndmng_terminate (void);


#ifdef __cplusplus
}
#endif

#endif /* _HNDMNG_H_ */
