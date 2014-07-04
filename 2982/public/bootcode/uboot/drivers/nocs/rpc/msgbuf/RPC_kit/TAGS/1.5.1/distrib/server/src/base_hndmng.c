/**
**  @file base_hndmng.c
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


/********************************************
 * INCLUDE Files                            *
 ********************************************/

#include <stddef.h>
#include "src/base_hndmng.h"
#include "inc/avlset.h"
#include "inc/msgbuf_sys_malloc.h"


/* */
typedef struct SHndMngHeader
{
  TAVLSet_iter         iter;
  void               * pHandle;
  THndMng_closeCbFct   closeHandle_fct;

} THndMngHeader;


/* */
static int localCompareFct
(
  TAVLSet_iter * pxIter1,
  TAVLSet_iter * pxIter2
)
{
  THndMngHeader * p1;
  THndMngHeader * p2;

  p1 = (THndMngHeader*)pxIter1;
  p2 = (THndMngHeader*)pxIter2;

  if (p1->pHandle > p2->pHandle) return 1;
  if (p1->pHandle < p2->pHandle) return -1;
  return 0;
}


/* */
void base_hndmng_init
(
  TAVLSet * pxSet
)
{
  AVLSet_init(pxSet, &localCompareFct, 0);
}


int base_hndmng_register
(
  TAVLSet            * pxSet,
  void               * pxHandle,
  THndMng_closeCbFct   xCloseHandle_fct
)
{
  THndMngHeader * pHeader;
  TAVLSet_iter  * pIter;
  THndMngHeader   sysHdr;

  sysHdr.pHandle = pxHandle;

  pIter = AVLSet_find (pxSet, &sysHdr.iter);
  if (pIter != AVLSet_end(pxSet))
  {
    /* TODO: There is a bug here in the remote board */
    return -1;
  }
  else
  {
    pHeader = (THndMngHeader*)MSGBUF_SYS_malloc(sizeof(THndMngHeader));
    if (pHeader == NULL) return -1;


    pHeader->pHandle = pxHandle;
    pHeader->closeHandle_fct = xCloseHandle_fct;
    pIter = AVLSet_insert (pxSet, &pHeader->iter);
    return 0;
  }
}


/* */
int base_hndmng_unregister
(
  TAVLSet * pxSet,
  void    * pxHandle
)
{
  THndMngHeader   sysHdr;
  TAVLSet_iter  * pIter;

  sysHdr.pHandle = pxHandle;

  pIter = AVLSet_find (pxSet, &sysHdr.iter);
  if (pIter != AVLSet_end (pxSet))
  {
    AVLSet_remove (pxSet, pIter);
    MSGBUF_SYS_free (pIter);
    return 0;
  }
  else return -1;
}


/* */
int base_hndmng_isRegistered
(
  TAVLSet * pxSet,
  void    * pxHandle
)
{
  THndMngHeader      sysHdr;
  TAVLSet_iter     * pIter;
  sysHdr.pHandle = pxHandle;

  pIter = AVLSet_find (pxSet, &sysHdr.iter);
  if (pIter == AVLSet_end (pxSet))
    return 0;
  else return 1;
}


/* */
void base_hndmng_terminate
(
  TAVLSet * pxSet
)
{
  TAVLSet_iter  * pIter;
  THndMngHeader * pHdr;

  pIter = AVLSet_next (AVLSet_begin(pxSet));
  while (pIter != AVLSet_end(pxSet))
  {
    pHdr = (THndMngHeader *)pIter;
    AVLSet_remove (pxSet, pIter);

    if (pHdr->closeHandle_fct) pHdr->closeHandle_fct (pHdr->pHandle);
    pIter = AVLSet_next (AVLSet_begin(pxSet))
  }
}
