
#include <stddef.h>
#include "inc/hndmng.h"
#include "src/base_hndmng.h"
#include "inc/avlset.h"
#include <pthread.h>
#include <semaphore.h>


static pthread_mutex_t   _gMutex;
static TAVLSet           gHandleSet;
static TAVLSet         * pgHandleSet   = NULL;

static int hndmng_init (void)
{
  if (pgHandleSet == NULL)
  {
    pgHandleSet  = &gHandleSet;
    pthread_mutex_init (&_gMutex, NULL);
    base_hndmng_init (pgHandleSet);
  }

  return 0;
}


/* */
int hndmng_register
(
  void               * pxHandle,
  THndMng_closeCbFct   xCloseHandle_fct
)
{
  int status = 0;

  hndmng_init ();
  pthread_mutex_lock (&_gMutex);
  status = base_hndmng_register(pgHandleSet, pxHandle, xCloseHandle_fct);
  pthread_mutex_unlock (&_gMutex);
  return status;
}


/* */
int hndmng_unregister
(
  void * pxHandle
)
{
  int status = 0;

  hndmng_init ();
  pthread_mutex_lock (&_gMutex);
  status = base_hndmng_unregister(pgHandleSet, pxHandle);
  pthread_mutex_unlock (&_gMutex);
  return status;
}


/* */
int hndmng_isRegistered
(
  void * pxHandle
)
{
  int status = 0;

  hndmng_init ();
  pthread_mutex_lock (&_gMutex);
  status = base_hndmng_isRegistered (pgHandleSet, pxHandle);
  pthread_mutex_unlock (&_gMutex);
  return status;
}


/* */
void hndmng_terminate (void)
{
  hndmng_init ();

  pthread_mutex_lock (&_gMutex);
  base_hndmng_terminate (pgHandleSet);
  pthread_mutex_unlock (&_gMutex);
}
