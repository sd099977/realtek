/**
**  @file avltree.c
**
** @brief
**    Memory pool allocator
**
**    This file implements an AVL-tree based memory allocator operating on
**    on a statically pre-allocator buffer (called memory pool).
**
**    Allocations, deallocations are granted to operate in in 0-ln(n) manner.
**
**    This memory pool is intended to provide the same feature as a on-heap memory
**    allocation for SW programs that do not run on an OS.
**
**
**  <hr>Copyright &copy; 2012 Nagravision. All rights reserved.\n
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

#define AVL_SET_DEBUG 1

#define AVL_SET_IMPL_VERSION_MAJOR     1
#define AVL_SET_IMPL_VERSION_MEDIUM    0
#define AVL_SET_IMPL_VERSION_MINOR     0


/********************************************
 * INCLUDE Files                            *
 ********************************************/

#include <stddef.h>
#include "inc/avlset.h"

/***********************************************
 * Private Function Declarations
 ***********************************************/

/*
 * Insert a node in an AVL tree identified by its current
 * root node
 *
 * Return the new AVL tree root node if the tree
 * does not contain any nodes.
 */
static void _AVLSet_insert (
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter );


/* */
static void _AVLSet_insertAfter (
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter,
  TAVLSet_iter * pxAfterIter );

/*
 * Rebalance tree starting from a leaf
 */
static void pBalance (
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter );

/*
 * Rotate right a subtree identified by its root node.
 * Return the new root node of this sub-tree.
 *
 * PS: Left child node of the root node is assumed not being
 * NULL.
 */
static TAVLSet_iter * pRotateRight (
  TAVLSet_iter * pxIter );

/*
 * Rotate left a subtree identified by its root node.
 * Return the new root node of this sub-tree.
 *
 * PS: Right child node of the root node is assumed not being
 * NULL.
 */
static TAVLSet_iter * pRotateLeft (
  TAVLSet_iter * pxIter );

/*
 * Get Balance factor of a node
 * Balance factor of a node is defined as the different of height
 * of left and right child height values
 */
static TAVLSet_height getBalance (
  TAVLSet_iter * pxIter );

/*
 * Get the height of a node.
 * Height is assumed to be 0, if node is NULL.
 * A leaf node should is represented with an height
 * equal to 0.
 */
static TAVLSet_height getHeight (
  TAVLSet_iter * pxIter );

/*
 * Get the maximum height value (from 2 height values)
 */
static TAVLSet_height maxValue (
  TAVLSet_height x1,
  TAVLSet_height x2 );


/***********************************************
 * Public Functions Implementation
 ***********************************************/

/* */
void AVLSet_init
(
  TAVLSet         * pxSet,
  TAVLSet_compare   xCompare,
  int               xIsMSet
)
{
  pxSet->size      = 0;
  pxSet->compare   = xCompare;
  pxSet->isMSet    = xIsMSet;
  pxSet->pRootIter = &pxSet->beginIter;

  pxSet->beginIter.pParent = NULL;
  pxSet->beginIter.pChild[AVLSET_LEFT] = NULL;
  pxSet->beginIter.pChild[AVLSET_RIGHT] = &pxSet->endIter;
  pxSet->beginIter.height = 2;
  pxSet->beginIter.pNeighbor[AVLSET_LEFT] = &pxSet->beginIter;
  pxSet->beginIter.pNeighbor[AVLSET_RIGHT] = &pxSet->endIter;

  pxSet->endIter.pParent = &pxSet->beginIter;
  pxSet->endIter.pChild[AVLSET_LEFT] = NULL;
  pxSet->endIter.pChild[AVLSET_RIGHT] = NULL;
  pxSet->endIter.height = 1;
  pxSet->endIter.pNeighbor[AVLSET_LEFT] = &pxSet->beginIter;
  pxSet->endIter.pNeighbor[AVLSET_RIGHT] = &pxSet->endIter;
}

/* */
void AVLSet_iterInit
(
  TAVLSet_iter * pxIter
)
{
  pxIter->pChild[AVLSET_LEFT] = NULL;
  pxIter->pChild[AVLSET_RIGHT] = NULL;
  pxIter->pNeighbor[AVLSET_LEFT] = pxIter;
  pxIter->pNeighbor[AVLSET_RIGHT] = pxIter;
  pxIter->pParent = NULL;
  pxIter->height = 1;
}


/* */
TAVLSet_iter * AVLSet_insert
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_iter * pIter;

  if (!pxSet->isMSet) pIter = AVLSet_find (pxSet, pxIter);
  else pIter = &pxSet->endIter;

  if (pIter == &pxSet->endIter)
  {
    _AVLSet_insert (pxSet, pxIter);
    pIter = pxIter;
  }
  else pIter = &pxSet->endIter;

  return pIter;
}


/* */
TAVLSet_iter * AVLSet_insertAfter
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter,
  TAVLSet_iter * pxAfterIter
)
{
  TAVLSet_iter * pIter = pxAfterIter;

  if (!pxSet->isMSet)
  {
    pIter = AVLSet_find (pxSet, pxIter);
    if (pIter == &pxSet->endIter) pIter = AVLSet_lowerBound(pxSet, pxIter);
  }

  if (pIter == pxAfterIter)
  {
    _AVLSet_insertAfter (pxSet, pxIter, pxAfterIter);
    pIter = pxIter;
  }
  else pIter = &pxSet->endIter;

  return pIter;
}


/* */
void AVLSet_remove
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_iter * pSwapIter;
  TAVLSet_iter * pIter;
  TAVLSet_iter * pTmpIter;

  pxSet->size--;

  /* Extract this node out of the neighborhood */
  pxIter->pNeighbor[AVLSET_LEFT]->pNeighbor[AVLSET_RIGHT] = pxIter->pNeighbor[AVLSET_RIGHT];
  pxIter->pNeighbor[AVLSET_RIGHT]->pNeighbor[AVLSET_LEFT] = pxIter->pNeighbor[AVLSET_LEFT];

  pIter = pxIter->pParent;
  if (!pxIter->pChild[AVLSET_RIGHT])
  {
    pTmpIter = pxIter->pChild[AVLSET_LEFT];
    if (pTmpIter) pTmpIter->pParent = pIter;

    if (!pIter)
    {
      pxSet->pRootIter = pTmpIter;
      return;
    }
    else
    {
      if (pIter->pChild[AVLSET_LEFT] == pxIter)
        pIter->pChild[AVLSET_LEFT] = pTmpIter;
      else pIter->pChild[AVLSET_RIGHT] = pTmpIter;
    }
  }
  else if (!pxIter->pChild[AVLSET_LEFT])
  {
    pTmpIter = pxIter->pChild[AVLSET_RIGHT];
    pTmpIter->pParent = pIter;

    if (!pIter)
    {
      pxSet->pRootIter = pTmpIter;
      return;
    }
    else
    {
      if (pIter->pChild[AVLSET_LEFT] == pxIter)
        pIter->pChild[AVLSET_LEFT] = pTmpIter;
      else pIter->pChild[AVLSET_RIGHT] = pTmpIter;
    }
  }
  else
  {
    pSwapIter = pxIter->pNeighbor[AVLSET_LEFT];
    if (pSwapIter->pChild[AVLSET_LEFT]) pRotateRight(pSwapIter);

    if (pIter)
    {
      if (pIter->pChild[AVLSET_LEFT] == pxIter) pIter->pChild[AVLSET_LEFT] = pSwapIter;
      else pIter->pChild[AVLSET_RIGHT] = pSwapIter;
    }
    else pxSet->pRootIter = pSwapIter;

    pSwapIter->height = pxIter->height;
    pTmpIter = pxIter->pChild[AVLSET_RIGHT];
    pSwapIter->pChild[AVLSET_RIGHT] = pTmpIter;
    pTmpIter->pParent = pSwapIter;

    pTmpIter = pIter;
    pIter = pSwapIter->pParent;
    pSwapIter->pParent = pTmpIter;

    if (pIter == pxIter) { pSwapIter->pChild[AVLSET_LEFT] = NULL; pIter = pSwapIter;}
    else
    {
      pIter->pChild[AVLSET_RIGHT] = NULL;
      pTmpIter = pxIter->pChild[AVLSET_LEFT];
      pSwapIter->pChild[AVLSET_LEFT] = pTmpIter;
      pTmpIter->pParent = pSwapIter;
    }
  }

  pBalance (pxSet, pIter);
}


/* */
TAVLSet_iter * AVLSet_find
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_iter * pRootIter = pxSet->pRootIter;
  TAVLSet_iter * pRefIter  = NULL;
  int            diff;

  while (pRootIter)
  {
    if (pRootIter == &pxSet->beginIter) diff = -1;
    else if (pRootIter == &pxSet->endIter) diff = 1;
    else diff = pxSet->compare(pRootIter, pxIter);

    if (diff >= 0)
    {
      if (diff == 0) pRefIter = pRootIter;
      pRootIter = pRootIter->pChild[AVLSET_LEFT];
    }
    else pRootIter = pRootIter->pChild[AVLSET_RIGHT];
  }

  if (pRefIter) return pRefIter;
  else return &pxSet->endIter;
}


/* */
TAVLSet_iter * AVLSet_lowerBound
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_iter * pRootIter = pxSet->pRootIter;
  TAVLSet_iter * pRefIter  = NULL;
  TAVLSet_iter * pTmpIter  = NULL;
  int            diff;

  while (pRootIter)
  {
    pTmpIter = pRootIter;

    if (pRootIter == &pxSet->beginIter) diff = -1;
    else if (pRootIter == &pxSet->endIter) diff = 1;
    else diff = pxSet->compare (pRootIter, pxIter);

    if (diff <= 0) pRefIter = pRootIter;
    if (diff >= 0)
      pRootIter = pRootIter->pChild[AVLSET_LEFT];
    else
    pRootIter = pRootIter->pChild[AVLSET_RIGHT];
  }

  return pRefIter;
}


/* */
TAVLSet_iter * AVLSet_upperBound
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_iter * pRootIter = pxSet->pRootIter;
  TAVLSet_iter * pRefIter  = &pxSet->endIter;
  int            diff;

  while (pRootIter)
  {
    if (pRootIter == &pxSet->beginIter) diff = -1;
    else if (pRootIter == &pxSet->endIter) diff = 1;
    else diff = pxSet->compare (pRootIter, pxIter);

    if (diff > 0)
    {
      pRefIter = pRootIter;
      pRootIter = pRootIter->pChild[AVLSET_LEFT];
    }
    else pRootIter = pRootIter->pChild[AVLSET_RIGHT];
  }

  return pRefIter;
}

/***********************************************
 * Private Functions Implementation
 ***********************************************/

/* */
static void _AVLSet_insert
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_side   childSide, adjChildSide;
  TAVLSet_iter * pIter = NULL;
  TAVLSet_iter * pTmpIter;
  int            diff = 0;

  /* Initialize the inserted node structure */
  pxIter->pChild[AVLSET_LEFT] = pxIter->pChild[AVLSET_RIGHT] = pxIter->pParent = NULL;
  pxIter->height = 1;

  /* Find the leaf where to insert the node */
  pTmpIter = pxSet->pRootIter;
  while (pTmpIter)
  {
    pIter = pTmpIter;
    if (pTmpIter == &pxSet->beginIter) diff = -1;
    else if (pTmpIter == &pxSet->endIter) diff = 1;
    else diff = pxSet->compare (pTmpIter, pxIter);

    if (diff <= 0)
      pTmpIter = pTmpIter->pChild[AVLSET_RIGHT];
    else pTmpIter = pTmpIter->pChild[AVLSET_LEFT];
  }

  /* Link the Node (as a leaf) into the AVL tree */
  pxIter->pParent = pIter;
  childSide = ((diff <= 0) ? AVLSET_RIGHT : AVLSET_LEFT);
  pIter->pChild[childSide] = pxIter;

  /* Update the ref nodes neighbors link */
  adjChildSide = childSide ^ 1;
  pxIter->pNeighbor[adjChildSide] = pIter;
  pxIter->pNeighbor[childSide] = pIter->pNeighbor[childSide];
  pIter->pNeighbor[childSide] = pxIter;
  pxIter->pNeighbor[childSide]->pNeighbor[adjChildSide] = pxIter;

  pxSet->size++;
  pBalance (pxSet, pIter);
}


/* */
static void _AVLSet_insertAfter
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter,
  TAVLSet_iter * pxAfterIter
)
{
  TAVLSet_iter * pIter = NULL;

  /* Initialize the inserted node structure */
  pxIter->pChild[AVLSET_LEFT] = pxIter->pChild[AVLSET_RIGHT] = pxIter->pParent = NULL;
  pxIter->height = 1;

  /* Update neighborhood */
  pxIter->pNeighbor[AVLSET_LEFT] = pxAfterIter;
  pxIter->pNeighbor[AVLSET_RIGHT] = pxAfterIter->pNeighbor[AVLSET_RIGHT];
  pxIter->pNeighbor[AVLSET_RIGHT]->pNeighbor[AVLSET_LEFT] = pxIter;
  pxIter->pNeighbor[AVLSET_LEFT]->pNeighbor[AVLSET_RIGHT] = pxIter;

  if (pxAfterIter->pChild[AVLSET_RIGHT] == NULL)
  {
    pxAfterIter->pChild[AVLSET_RIGHT] = pxIter;
    pxIter->pParent = pxAfterIter;
    pIter = pxAfterIter;
  }
  else
  {
    pIter = pxIter->pNeighbor[AVLSET_RIGHT];
    pIter->pChild[AVLSET_LEFT] = pxIter;
    pxIter->pParent = pIter;
  }

  pxSet->size++;
  pBalance (pxSet, pIter);
}


/* */
static void pBalance
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
)
{
  TAVLSet_iter   * pIter;
  TAVLSet_iter   * pTmpIter;
  TAVLSet_height   balance, childBalance;
  TAVLSet_height   prevHeight;

  pIter = pTmpIter = pxIter;

  /* Rebalance the AVL tree according to the Node insertion */
  while (pIter)
  {
    prevHeight = pIter->height;
    balance = getBalance (pIter);

    /* Left Left Case */
    if (balance > 1)
    {
      childBalance = getBalance (pIter->pChild[AVLSET_LEFT]);
      if (childBalance < 0) pRotateLeft (pIter->pChild[AVLSET_LEFT]);
      pIter = pRotateRight(pIter);
    }

    else if (balance < -1)
    {
      childBalance = getBalance (pIter->pChild[AVLSET_RIGHT]);
      if (childBalance > 0) pRotateRight (pIter->pChild[AVLSET_RIGHT]);
      pIter = pRotateLeft (pIter);
    }
    else pIter->height = maxValue (getHeight(pIter->pChild[AVLSET_LEFT]), getHeight(pIter->pChild[AVLSET_RIGHT])) + 1;

    pTmpIter = pIter;
    pIter = pIter->pParent;

    if (!pIter) pxSet->pRootIter = pTmpIter;
    if (pTmpIter->height == prevHeight) return;
  }
}


/* */
static TAVLSet_iter * pRotateRight
(
  TAVLSet_iter * pxIter
)
{
  /* Note: assuming that pxIter left child is never NULL when calling this
   * function */
  TAVLSet_iter * pNewRootNode = pxIter->pChild[AVLSET_LEFT];
  TAVLSet_iter * pTmpNode = pxIter->pParent;

  pNewRootNode->pParent = pTmpNode;
  if (pTmpNode)
  {
    if (pTmpNode->pChild[AVLSET_LEFT] == pxIter)
      pTmpNode->pChild[AVLSET_LEFT] = pNewRootNode;
    else pTmpNode->pChild[AVLSET_RIGHT] = pNewRootNode;
  }

  pTmpNode = pNewRootNode->pChild[AVLSET_RIGHT];
  pxIter->pChild[AVLSET_LEFT] = pTmpNode;
  if (pTmpNode != NULL) pTmpNode->pParent = pxIter;

  pNewRootNode->pChild[AVLSET_RIGHT] = pxIter;
  pxIter->pParent = pNewRootNode;

  pxIter->height = maxValue (getHeight(pxIter->pChild[AVLSET_LEFT]), getHeight(pxIter->pChild[AVLSET_RIGHT])) + 1;
  pNewRootNode->height = maxValue (getHeight (pNewRootNode->pChild[AVLSET_LEFT]), getHeight (pNewRootNode->pChild[AVLSET_RIGHT])) + 1;

  return pNewRootNode;
}


/* */
static TAVLSet_iter * pRotateLeft
(
  TAVLSet_iter * pxIter
)
{
  /* Note: assuming that pxIter right child is never NULL when calling this
   * function */
  TAVLSet_iter * pNewRootNode = pxIter->pChild[AVLSET_RIGHT];
  TAVLSet_iter * pTmpNode = pxIter->pParent;

  pNewRootNode->pParent = pTmpNode;
  if (pTmpNode)
  {
    if (pTmpNode->pChild[AVLSET_LEFT] == pxIter)
      pTmpNode->pChild[AVLSET_LEFT] = pNewRootNode;
    else pTmpNode->pChild[AVLSET_RIGHT] = pNewRootNode;
  }

  pTmpNode = pNewRootNode->pChild[AVLSET_LEFT];
  pxIter->pChild[AVLSET_RIGHT] = pTmpNode;
  if (pTmpNode != NULL) pTmpNode->pParent = pxIter;

  pNewRootNode->pChild[AVLSET_LEFT] = pxIter;
  pxIter->pParent = pNewRootNode;

  pxIter->height = maxValue (getHeight(pxIter->pChild[AVLSET_LEFT]), getHeight(pxIter->pChild[AVLSET_RIGHT])) + 1;
  pNewRootNode->height = maxValue (getHeight (pNewRootNode->pChild[AVLSET_LEFT]), getHeight (pNewRootNode->pChild[AVLSET_RIGHT])) + 1;

  return pNewRootNode;
}


/* */
static TAVLSet_height getHeight
(
  TAVLSet_iter * pxIter
)
{
  if (pxIter == NULL) return 0;
  else return pxIter->height;
}


/* */
static TAVLSet_height maxValue
(
  TAVLSet_height x1,
  TAVLSet_height x2
)
{
  return ((x1 > x2) ? x1 : x2);
}


/* Get Balance factor of node N */
static TAVLSet_height getBalance
(
  TAVLSet_iter * pxIter
)
{
  return ((pxIter == NULL) ? 0 : getHeight(pxIter->pChild[AVLSET_LEFT]) - getHeight(pxIter->pChild[AVLSET_RIGHT]));
}
