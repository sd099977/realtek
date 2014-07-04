/**
**  @file msgbuf_sys_mutex.h
**
** @brief
**    This header file describes the MSGBUF system mutex interface.
**
**  $Id:$
**  $Change:$
**
** REMARK:
**   Comments in this file use special tags to allow automatic API
**   documentation generation in HTML format, using the GNU-General
**   Public Licensed Doxygen tool. For more information about Doxygen,
**   please check www.doxygen.org
**
**   Depending on the platform, the CHM file may not open properly if it
**   is stored on a network drive. So either the file should be moved on
**   a local drive or add the following registry entry on Windows platform
**  (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/

#ifndef _MSGBUF_SYS_MUTEX_H_
#define _MSGBUF_SYS_MUTEX_H_


#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/


/**
 * @mainpage Overview
 *  - @subpage p_preface
 *
 *  <hr>Copyright &copy; 2012 Nagravision. All rights reserved.\n
 *  CH-1033 Cheseaux, Switzerland\n
 *  Tel: +41 21 7320311  Fax: +41 21 7320100\n
 *  http://www.nagra.com
 *
 *  All trademarks and registered trademarks are the property of their
 *  respective owners.
 *
 *  This document is supplied with an understanding that the notice(s)
 *  herein or any other contractual agreement(s) made that instigated the
 *  delivery of a hard copy, electronic copy, facsimile or file transfer
 *  of this document are strictly observed and maintained.
 *
 *  The information contained in this document is subject to change without
 *  notice.
 *
 *  <b>Security Policy of Nagravision Kudelski Group</b>\n
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 */

 /** @page p_preface Preface
 *
 *  <h2>Purpose</h2>
 *
 *  This document is intended to provide the API of Thread mutexes and
 *  semaphores
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for non OS-based application or for custom
 *  kernel or OS development.
 *
 *  <hr><h2>References</h2>
*/


 /** @defgroup mutex_group       Thread Mutexes */
 /** @defgroup sem_group         Thread Semaphores */


/***************************************************************************/
/*                                                                         */
/*              Types, structures and constants definitions                */
/*                                                                         */
/***************************************************************************/



/**
 *  @ingroup set
 *
 *  @brief
 *    MSGBUF thread mutex abstract handle type definition
*/
typedef void * TMsgbuf_thread_mutex;

/**
 *  @ingroup set
 *
 *  @brief
 *    MSGBUF thread semaphore abstract handle type definition
*/
typedef void * TMsgbuf_thread_sem;


/***************************************************************************/
/*                                                                         */
/*                   SET Structure initialization                          */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup mutex_group
 *
 *  @brief
 *    Create a new thread mutex instance and return its abstract handle
 *
 *  @retval
 *    Return the just created Mutex abstract handle or NULL if
 *    the operation fails
 *
*/
TMsgbuf_thread_mutex MSGBUF_SYS_createThreadMutex (void);


/**
 *  @ingroup mutex_group
 *
 *  @brief
 *    Delete a MSGBUF thread mutex created using the  MSGBUF_SYS_createThreadMutex()
 *    function.
 *
 *  @param[in]  xMutex
 *    Handle of the Mutex to be deleted.
 *
 *  @retval
 *    Return 0 in case of success.
 *    Return -1 in case of other errors.
*/
int MSGBUF_SYS_deleteThreadMutex
(
  TMsgbuf_thread_mutex xMutex
);


/**
 *  @ingroup mutex_group
 *
 *  @brief
 *    Acquire a MSGBUF thread mutex.
 *
 *  @param[in]  xMutex
 *    Handle of the Mutex to be deleted.
 *
 *  @retval
 *    Return 0 in case of success.
 *    Return -1 in case of other errors.
 *
 *   Acquiring access to a mutex decrease the access
 *   token by 1.
 *
 *   This function blocks when attempting to acquire a mutex
 *   that have its current token <= 0.
*/
int MSGBUF_SYS_acquireThreadMutex
(
  TMsgbuf_thread_mutex xMutex
);


/**
 *  @ingroup mutex_group
 *
 *  @brief
 *    Release a MSGBUF thread mutex.
 *
 *  @param[in]  xMutex
 *    Handle of the Mutex to be deleted.
 *
 *  @retval
 *    Return 0 in case of success.
 *    Return -1 in case of other errors.
 *
 *   Releasing access to a mutex increament the access
 *   token by 1.
 *
 *   This is a non-blocking function.
*/
int MSGBUF_SYS_releaseThreadMutex
(
  TMsgbuf_thread_mutex xMutex
);


/**
 *  @ingroup sem_group
 *
 *  @brief
 *    Create a new thread semaphore and return its abstract handle
 *
 *  @param[in]  xInitialToken
 *    Initial token value (normal case value is 1)
 *
 *  @retval
 *    The just created semaphore abstract handle or NULL if
 *    the operation fails
*/
TMsgbuf_thread_sem MSGBUF_SYS_createThreadSem
(
  int xInitialToken
);


/**
 *  @ingroup sem_group
 *
 *  @brief
 *    Delete a MSGBUF thread semaphore created using the  MSGBUF_SYS_createThreadSem().
 *    function.
 *
 *  @param[in]  xMutex
 *    Handle of the Semaphore to be deleted.
 *
 *  @retval
 *    Return 0 in case of success.
 *    Return -1 in case of other errors.
*/
int MSGBUF_SYS_deleteThreadSem
(
  TMsgbuf_thread_sem xSem
);


/**
 *  @ingroup sem_group
 *
 *  @brief
 *    Acquire a MSGBUF thread semaphore.
 *
 *  @param[in]  xMutex
 *    Handle of the Semaphore to be deleted.
 *
 *  @retval
 *    Return 0 in case of success.
 *    Return -1 in case of other errors.
 *
 *   Acquiring access to a mutex decrease the access
 *   token by 1.
 *
 *   This function blocks when attempting to acquire a mutex
 *   that have its current token <= 0.
*/
int MSGBUF_SYS_acquireThreadSem
(
  TMsgbuf_thread_sem xSem
);


/**
 *  @ingroup sem_group
 *
 *  @brief
 *    Release a MSGBUF thread semaphore.
 *
 *  @param[in]  xMutex
 *    Handle of the Semaphore to be deleted.
 *
 *  @retval
 *    Return 0 in case of success.
 *    Return -1 in case of other errors.
 *
 *   Releasing access to a mutex increament the access
 *   token by 1.
 *
 *   This is a non-blocking function.
*/
int MSGBUF_SYS_releaseThreadSem
(
  TMsgbuf_thread_sem xSem
);


#ifdef __cplusplus
}
#endif

#endif /* _MSGBUF_SYS_MUTEX_H_ */
