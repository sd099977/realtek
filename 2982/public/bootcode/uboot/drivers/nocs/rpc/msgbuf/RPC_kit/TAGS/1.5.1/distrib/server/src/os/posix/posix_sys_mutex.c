/**
**  @file null_sys_mutex.c
**
** @brief
**    This header file implements the POSIX MSGBUF system mutex interface.
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

#include "inc/os/msgbuf_sys_mutex.h"
#include "inc/msgbuf_sys_malloc.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>


/* */
TMsgbuf_thread_mutex MSGBUF_SYS_createThreadMutex (void)
{
  pthread_mutex_t * pMutex;

  pMutex = (pthread_mutex_t*)MSGBUF_SYS_malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init (pMutex, NULL);

  return (TMsgbuf_thread_mutex)(void*)pMutex;
}


/* */
int MSGBUF_SYS_deleteThreadMutex
(
  TMsgbuf_thread_mutex xMutex
)
{
  pthread_mutex_t * pMutex;

  pMutex = (pthread_mutex_t*)xMutex;
  pthread_mutex_destroy (pMutex);

  MSGBUF_SYS_free (xMutex);
  return 0;
}


/* */
int MSGBUF_SYS_acquireThreadMutex
(
  TMsgbuf_thread_mutex xMutex
)
{
  pthread_mutex_t * pMutex;
  int               status;

  pMutex = (pthread_mutex_t*)xMutex;
  status = pthread_mutex_lock (pMutex);
  return status;
}


/* */
int MSGBUF_SYS_releaseThreadMutex
(
  TMsgbuf_thread_mutex xMutex
)
{
  pthread_mutex_t * pMutex;

  pMutex = (pthread_mutex_t*)xMutex;
  pthread_mutex_unlock (pMutex);
  return 0;
}


/* */
TMsgbuf_thread_sem MSGBUF_SYS_createThreadSem
(
  int xInitialToken
)
{
  sem_t * pSem;

  pSem = (sem_t*)MSGBUF_SYS_malloc(sizeof(sem_t));
  sem_init (pSem, xInitialToken, 0);
  return (TMsgbuf_thread_sem)pSem;
}


/* */
int MSGBUF_SYS_deleteThreadSem
(
  TMsgbuf_thread_sem xSem
)
{
  sem_t * pSem;

  pSem = (sem_t*)(void*)xSem;
  sem_destroy (pSem);
  MSGBUF_SYS_free (pSem);
  return 0;
}


/* */
int MSGBUF_SYS_acquireThreadSem
(
  TMsgbuf_thread_sem xSem
)
{
  sem_t * pSem;
  int     status;

  pSem = (sem_t*)(void*)xSem;
  status = sem_wait (pSem);

  return status;
}


/* */
int MSGBUF_SYS_releaseThreadSem
(
  TMsgbuf_thread_sem xSem
)
{
  sem_t * pSem;

  pSem = (sem_t*)(void*)xSem;
  sem_post (pSem);
  return 0;
}
