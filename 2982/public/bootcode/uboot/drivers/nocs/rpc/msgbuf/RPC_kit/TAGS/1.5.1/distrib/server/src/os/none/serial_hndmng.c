
#include <stddef.h>
#include "inc/hndmng.h"
#include "src/base_hndmng.h"
#include "inc/avlset.h"


static TAVLSet   gHandleSet;
static TAVLSet * pgHandleSet   = NULL;

static int hndmng_init (void)
{
  if (pgHandleSet == NULL)
  {
    pgHandleSet  = &gHandleSet;
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
  status = base_hndmng_register(pgHandleSet, pxHandle, xCloseHandle_fct);
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
  status = base_hndmng_unregister(pgHandleSet, pxHandle);
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
  status = base_hndmng_isRegistered (pgHandleSet, pxHandle);
  return status;
}


/* */
void hndmng_terminate (void)
{
  hndmng_init ();
  base_hndmng_terminate (pgHandleSet);
}
