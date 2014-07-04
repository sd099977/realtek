/**
 * File: $Id:$
 *
 *  This header file implements the dynamic memory allocation abstraction layer.
 *
 *  This abstraction layer is intended to improve the OS portability
 *  of applications. Such abstraction permits to abstract this feature
 *  for application not running on an OS
 *  (e.g: memory pool allocation as dynamic memory allocation mechanism)
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


#ifndef _MSGBUF_SYS_MALLOC_H_
#define _MSGBUF_SYS_MALLOC_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief
 *    Init the memory allocation sub-system.
 *
 *  @retval 0
 *    If successfully intialized (or already initialized)
 *  @retval -1
 *    If memory allocation sub-system failed
 *
*/
int MSGBUF_SYS_init (void);


/**
 *  @brief
 *    Allocate a memory buffer from the memory allocation sub-system.
 *
 *  @pre
 *    Memory allocation sub-system shall have been successfully initialized
 *    before calling this function.
 *
 *  @param[in] xSize
 *             Memory size to allocate
 *
 *  @retval A pointer to the allocated memory (or NULL is none)
*/
void * MSGBUF_SYS_malloc (size_t xSize);


/**
 *  @brief
 *    Deallocate a memory buffer that was previously allocated by the memory
 *    allocation sub-system.
 *
 *  @pre
 *    Memory allocation sub-system shall have been successfully initialized
 *    before calling this function.
 *
 *  @param[in] pxData
 *             Data buffer to deallocate
 *
 *  @retval None
*/
void MSGBUF_SYS_free (void * pxData);


/**
 *  @brief
 *    Terminate the memory allocation sub-system.
 *
 *  @retval 0
 *    If successfully intialized (or already initialized)
 *  @retval -1
 *    If memory allocation sub-system failed
 *
*/
int MSGBUF_SYS_terminate (void);


#ifdef __cplusplus
}
#endif

#endif /* _MSGBUF_SYS_MALLOC_H_ */
