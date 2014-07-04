/**
**  @file memAlloc.c
**
** @brief
**    Memory pool allocator
**
**    This file implements an AVL-tree based memory allocator operating on
**    on a statically pre-allocator buffer (called memory pool).
**
**    Allocations, deallocations are granted to operate in in 0-ln(n) manner.
**    According to AVL algorithm, the depth H(N) of a tree follows the following
**    rule:
**
**    As an brief summary to AVL algorithm, let introduce 'H' the deapest
**    possible path in a tree having N nodes. We have (without demonstration):
**
**    A H depth tree cannot contain more than N <= 2^(H) - 1
**    A H depth tree contains at least N = phi^(H+3) / 5^(0.5). Where phi = (1 + 5^(1/2))/2
**
**    As a result: H(N) satisfies the following relationship .
**
**      (roundup(ln(N+1)/ln(2)) <= H <= roundup(1.44 * ln(N+2)/ln(2) - 1.328)
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

#define MEM_ALLOC_DEBUG                  0

#define MEM_ALLOC_IMPL_VERSION_MAJOR     1
#define MEM_ALLOC_IMPL_VERSION_MEDIUM    0
#define MEM_ALLOC_IMPL_VERSION_MINOR     0


/********************************************
 * INCLUDE Files                            *
 ********************************************/

#include <stddef.h>
#include "src/os/none/memAlloc.h"


/* AVL SIDE identifier */
#define LEFT     0
#define RIGHT    1
#define SIDE_NUM 2

/* */
#define MEM_BLOCK_USED 0x1
#define MEM_BLOCK_FREE 0x02


/***********************************************
 * Type definition
 ***********************************************/

typedef unsigned char  _TAVLNodeSide;
typedef short int      _TAVLNodeHeight;

typedef struct _SAVLNode   _TAVLNode;
typedef struct _SMemBlkHdr _TMemBlkHdr;
typedef struct _SMemPool   _TMemPool;


/***********************************************
 * Private Structure Definition
 ***********************************************/

/* AVL node structure definition */
struct _SAVLNode
{
  _TAVLNode       * pChild[SIDE_NUM];
  _TAVLNode       * pParent;
  _TAVLNodeHeight   height;
};


/* Memory block header structure definition */
struct _SMemBlkHdr
{
  int rightOffset;
  int leftOffset;
  int status;
};


/* Memory pool header structure definition */
struct _SMemPool
{
  int                         magicNumber;
  _TMemBlkHdr               * pBeginBlock;
  _TMemBlkHdr               * pEndBlock;
  _TAVLNode                 * pRootNode;
  TMemPool_mutexHandle        mutex;
  TMemPool_mutexAcquire_fct   acquireFct;
  TMemPool_mutexRelease_fct   releaseFct;
  int                         poolSize;
  int                         poolUserMemSize;
  int                         usedMemSize;
  int                         freeBlkNum;
  int                         allocBlkNum;
};


/***********************************************
 * Private Function Declarations
 ***********************************************/


/*
 * Get the height of a node.
 * Height is assumed to be 0, if node is NULL.
 * A leaf node should is represented with an height
 * equal to 0.
 */
static _TAVLNodeHeight getHeight (
  _TAVLNode * pxNode );


/*
 * Get the maximum height value (from 2 height values)
 */
static _TAVLNodeHeight maxValue (
  _TAVLNodeHeight x1,
  _TAVLNodeHeight x2 );


/*
 * Get Balance factor of a node
 * Balance factor of a node is defined as the different of height
 * of left and right child height values
 */
static _TAVLNodeHeight getBalance (
  _TAVLNode * pxNode );


/*
 * Rotate right a subtree identified by its root node.
 * Return the new root node of this sub-tree.
 *
 * PS: Left child node of the root node is assumed not being
 * NULL.
 */
static _TAVLNode * pRotateRight (
  _TAVLNode     * pxNode );


/*
 * Rotate left a subtree identified by its root node.
 * Return the new root node of this sub-tree.
 *
 * PS: Right child node of the root node is assumed not being
 * NULL.
 */
static _TAVLNode * pRotateLeft (
  _TAVLNode     * pxNode );


/*
 * Insert a node in an AVL tree identified by its current
 * root node
 *
 * Return the new AVL tree root node if the tree
 * does not contain any nodes.
 */
_TAVLNode * pInsertNode (
  _TAVLNode * pxRefNode,
  _TAVLNode * pxRootNode );


/*
 * Delete a node from an AVL tree identified by its current root
 * node.
 *
 * Node to be deleted is assumed to belong to this tree
 * Return the the new AVL tree root node (or NULL is the
 * new AVL-tree does not contain no more nodes
 */
static _TAVLNode * pDeleteNode (
  _TAVLNode * pxNode,
  _TAVLNode * pxRootNode );


/*
 * Find the the best memory block node able to hold a given memory
 * size from a pool specified by its root node.
 *
 * Return the node that has the smaller memory size fitting the request
 * (or NULL if none are found)
 */
static _TAVLNode * pMemPool_findBestNode (
  _TAVLNode * pxRootNode,
  int         xSize );


/*
 * Get the bigger free memory block as possible in a pool specified
 * by its root node.
 */
static int pMemPool_findBiggestFreeMemBlock (
  _TAVLNode * pxRootNode );



/***********************************************
 * Public Function definition
 ***********************************************/


#define MIN_POOL_SIZE (sizeof(_TMemPool) + 3 * sizeof(_TMemBlkHdr) + sizeof(_TAVLNode))
#define MEM_BLOCK_MODULO_SIZE (sizeof(_TMemBlkHdr) + sizeof(_TAVLNode))

#define MEM_POOL_MAGIC_NUMBER  0xA9F7632D


/*----------------------------------------------
 * Memory pool configuration function(s)
 *---------------------------------------------*/

/* */
TMemPool memPool_init
(
  void                      * pxMemPoolBuffer[],
  int                         xMemPoolBufferByteSize,
  TMemPool_mutexAcquire_fct   xAcquireFct,
  TMemPool_mutexRelease_fct   xReleaseFct,
  TMemPool_mutexHandle        xMutexHandle
)
{
  _TMemPool   * pMemPool;
  int           poolSize;
  int           memPoolSize;
  _TMemBlkHdr * pBeginBlock;
  _TMemBlkHdr * pEndBlock;
  _TMemBlkHdr * pEmptyBlock;
  _TAVLNode   * pRootNode;

  pMemPool = (_TMemPool*)&pxMemPoolBuffer[0];
  poolSize = (xMemPoolBufferByteSize / sizeof(void*)) * sizeof(void*);

  /* If the memory size pool is too small */
  if (poolSize < MIN_POOL_SIZE) return NULL;
  pMemPool->poolSize = poolSize;

  /* Setup the thread safe mutex info */
  pMemPool->mutex      = xMutexHandle;
  pMemPool->acquireFct = xAcquireFct;
  pMemPool->releaseFct = xReleaseFct;

  /* Setup the operational pool size */
  memPoolSize = poolSize - sizeof(_TMemPool) - 2 * sizeof(_TMemBlkHdr);
  memPoolSize = (memPoolSize / MEM_BLOCK_MODULO_SIZE) * MEM_BLOCK_MODULO_SIZE;
  pMemPool->poolUserMemSize = memPoolSize;

  pMemPool->usedMemSize  = 0;
  pMemPool->allocBlkNum  = 0;
  pMemPool->freeBlkNum   = 1;
  pMemPool->magicNumber  = MEM_POOL_MAGIC_NUMBER;

  pBeginBlock = (_TMemBlkHdr*)&pMemPool[1];
  pEmptyBlock = &pBeginBlock[1];
  pEndBlock = (_TMemBlkHdr*)((char*)pEmptyBlock + memPoolSize);
  pMemPool->pEndBlock = pEndBlock;
  pMemPool->pBeginBlock = pBeginBlock;
  pMemPool->pRootNode = pRootNode = (_TAVLNode*)&pBeginBlock[2];

  pBeginBlock->status = MEM_BLOCK_USED;
  pBeginBlock->rightOffset = sizeof(_TMemBlkHdr);
  pBeginBlock->leftOffset = 1;

  pEmptyBlock->status = MEM_BLOCK_FREE;
  pEmptyBlock->leftOffset = sizeof(_TMemBlkHdr);
  pEmptyBlock->rightOffset = memPoolSize;

  pEndBlock->status = MEM_BLOCK_USED;
  pEndBlock->leftOffset = memPoolSize;
  pEndBlock->rightOffset = 1;

  pRootNode->height = 1;
  pRootNode->pChild[LEFT] =
    pRootNode->pChild[RIGHT] = NULL;
  pRootNode->pParent = NULL;

  return pMemPool;
}


/*------------------------------------------------
 * Memory pool allocation/deallocation function(s)
 *-----------------------------------------------*/

/* */
void * memPool_malloc
(
  TMemPool xMemPool,
  int      xMemSize
)
{
  _TMemPool   * pMemPool = (_TMemPool*)xMemPool;
  _TAVLNode   * pCurNode = NULL;
  _TMemBlkHdr * pCurMemBlk;
  int           remainingSize;
  int           size = xMemSize + sizeof(_TMemBlkHdr);
  int           status;

  if (pMemPool->magicNumber != MEM_POOL_MAGIC_NUMBER) return NULL;

  size = ((size + sizeof(_TMemBlkHdr) + MEM_BLOCK_MODULO_SIZE -1) / MEM_BLOCK_MODULO_SIZE) * MEM_BLOCK_MODULO_SIZE;

  if (pMemPool->acquireFct) status = (pMemPool->acquireFct)(pMemPool->mutex);
  else status = 0;

  if (status == 0)
  {
    pCurNode = pMemPool_findBestNode (pMemPool->pRootNode, size);
    if (pCurNode)
    {
      pMemPool->allocBlkNum++;
      pMemPool->pRootNode = pDeleteNode (pCurNode, pMemPool->pRootNode);
      pCurMemBlk = &((_TMemBlkHdr*)pCurNode)[-1];
      pCurMemBlk->status = MEM_BLOCK_USED;

      pMemPool->usedMemSize += (size - sizeof(_TMemBlkHdr));
      remainingSize = pCurMemBlk->rightOffset - size;
      if (remainingSize > 0)
      {
        _TAVLNode   * pNewNode;

        pCurMemBlk->rightOffset = size;
        pCurMemBlk = (_TMemBlkHdr*)(((char*)pCurMemBlk) + size);
        pCurMemBlk->leftOffset = size;
        pCurMemBlk->rightOffset = remainingSize;
        pCurMemBlk->status = MEM_BLOCK_FREE;
        pNewNode = (_TAVLNode*)&pCurMemBlk[1];
        pCurMemBlk = (_TMemBlkHdr*)(((char*)pCurMemBlk) + remainingSize);
        pCurMemBlk->leftOffset = remainingSize;
        pMemPool->pRootNode = pInsertNode (pNewNode, pMemPool->pRootNode);
      }
    else pMemPool->freeBlkNum--;
    }

    if (pMemPool->releaseFct) (pMemPool->releaseFct)(pMemPool->mutex);
  }

  return pCurNode;
}


/* */
void * memPool_realloc
(
  TMemPool   xMemPool,
  void     * pxBuffer,
  int        xNewSize
)
{
  _TMemPool   * pMemPool = (_TMemPool*)xMemPool;
  _TMemBlkHdr * pMemBlk = &((_TMemBlkHdr*)pxBuffer)[-1];
  int         * pNewBuffer = NULL;
  int         * pPrevBuffer = (int*)pxBuffer;

  if (pMemPool->magicNumber != MEM_POOL_MAGIC_NUMBER) return NULL;

  if (pMemBlk->status == MEM_BLOCK_USED)
  {
    int size = pMemBlk->rightOffset - sizeof (_TMemBlkHdr);
    if (xNewSize < size) size = ((xNewSize + sizeof(void*) + 1)/sizeof(void*)) * sizeof(void*);

    pNewBuffer = (int*)memPool_malloc (xMemPool, xNewSize);
    if (pNewBuffer)
    {
      int intSize = size/sizeof(int);
      int i;

      for (i=0; i < intSize; i++) *pNewBuffer++ = *pPrevBuffer++;
      memPool_free (xMemPool, pxBuffer);
    }
  }

  return pNewBuffer;
}


/* */
void memPool_free
(
  TMemPool   xMemPool,
  void     * pxData
)
{
  _TMemPool   * pMemPool = (_TMemPool*)xMemPool;
  _TMemBlkHdr * pMemBlk = &((_TMemBlkHdr*)pxData)[-1];
  _TMemBlkHdr * pLeftMemBlk;
  _TMemBlkHdr * pRightMemBlk;
  int           status;

  if (pMemPool->magicNumber != MEM_POOL_MAGIC_NUMBER) return;

  if (pMemPool->acquireFct) status = (pMemPool->acquireFct)(pMemPool->mutex);
  else status = 0;

  if (status == 0)
  {
    if (pMemBlk->status == MEM_BLOCK_USED)
    {
      pMemPool->allocBlkNum--;
      pMemPool->usedMemSize -= (pMemBlk->rightOffset - sizeof(_TMemBlkHdr));

      pLeftMemBlk =  (_TMemBlkHdr*)(((char*)pMemBlk) - pMemBlk->leftOffset);
      pRightMemBlk = (_TMemBlkHdr*)(((char*)pMemBlk) + pMemBlk->rightOffset);

      if (pLeftMemBlk->status == MEM_BLOCK_FREE)
      {
        pMemPool->pRootNode = pDeleteNode ((_TAVLNode*)&pLeftMemBlk[1], pMemPool->pRootNode);
        pMemPool->freeBlkNum--;
        pLeftMemBlk->rightOffset += pMemBlk->rightOffset;
        pRightMemBlk->leftOffset += pMemBlk->leftOffset;
        pMemBlk = pLeftMemBlk;
      }

      if (pRightMemBlk->status == MEM_BLOCK_FREE)
      {
        pMemPool->pRootNode = pDeleteNode ((_TAVLNode*)&pRightMemBlk[1], pMemPool->pRootNode);
        pMemBlk->rightOffset += pRightMemBlk->rightOffset;
        pMemPool->freeBlkNum--;
        pLeftMemBlk = (_TMemBlkHdr*)(((char*)pRightMemBlk) + pRightMemBlk->rightOffset);
        pLeftMemBlk->leftOffset += pRightMemBlk->leftOffset;
      }

      pMemBlk->status = MEM_BLOCK_FREE;
      pMemPool->freeBlkNum++;
      pMemPool->pRootNode = pInsertNode ((_TAVLNode*)&pMemBlk[1], pMemPool->pRootNode);
    }

    if (pMemPool->releaseFct) (pMemPool->releaseFct)(pMemPool->mutex);
  }
}


/*------------------------------------------------
 * Memory pool info function(s)
 *-----------------------------------------------*/

/* */
int memPool_getInfo
(
  const TMemPool   xMemPool,
  TMemPoolInfo   * pxMemPoolInfo
)
{
  _TMemPool const * pMemPool = (_TMemPool const *)xMemPool;
  int               status;

  if (pxMemPoolInfo == NULL) return -1;
  if (pMemPool->magicNumber != MEM_POOL_MAGIC_NUMBER) return -1;

  if (pMemPool->acquireFct) status = (pMemPool->acquireFct)(pMemPool->mutex);
  else status = 0;

  if (status == 0)
  {
    pxMemPoolInfo->implementation.version_majorDigit  = MEM_ALLOC_IMPL_VERSION_MAJOR;
    pxMemPoolInfo->implementation.version_mediumDigit = MEM_ALLOC_IMPL_VERSION_MEDIUM;
    pxMemPoolInfo->implementation.version_minorDigit  = MEM_ALLOC_IMPL_VERSION_MINOR;

    pxMemPoolInfo->config.userMemoryPoolSize = pMemPool->poolUserMemSize;

    if (pMemPool->releaseFct) (pMemPool->releaseFct)(pMemPool->mutex);
  }

  return status;
}


/* */
int memPool_getUsageInfo
(
  const TMemPool      xMemPool,
  TMemPoolUsageInfo * pxMemPoolUsageInfo
)
{
  _TMemPool const * pMemPool = (_TMemPool const *)xMemPool;
  int               status;

  if (pxMemPoolUsageInfo == NULL) return -1;
  if (pMemPool->magicNumber != MEM_POOL_MAGIC_NUMBER) return -1;

  if (pMemPool->acquireFct) status = (pMemPool->acquireFct)(pMemPool->mutex);
  else status = 0;

  if (status == 0)
  {
    pxMemPoolUsageInfo->currentUsedMemorySize       = pMemPool->usedMemSize;
    pxMemPoolUsageInfo->currentAllocatedBlockNumber = pMemPool->allocBlkNum;
    pxMemPoolUsageInfo->currentFragBlockNumber      = pMemPool->freeBlkNum;

    pxMemPoolUsageInfo->currentFreeMemorySize =
      pMemPool->poolUserMemSize - pMemPool->usedMemSize - (pMemPool->allocBlkNum + pMemPool->freeBlkNum) * sizeof(_TMemBlkHdr);

    pxMemPoolUsageInfo->currentMaxFreeMemoryBlockSize = pMemPool_findBiggestFreeMemBlock(pMemPool->pRootNode);

  pxMemPoolUsageInfo->lostUserMemorySize = (pMemPool->allocBlkNum + pMemPool->freeBlkNum) * sizeof(_TMemBlkHdr);
    if (pMemPool->releaseFct) (pMemPool->releaseFct)(pMemPool->mutex);
  }

  return status;
}


/*------------------------------------------------
 * Memory pool debug function(s)
 *-----------------------------------------------*/

/* */
int memPool_traceUsedBlock
(
  const TMemPool             xMemPool,
  TMemAllocTrace             xBlockType,
  TMemPoolUsedBlockReportFct xReportFct
)
{
  _TMemPool const * pMemPool     = (_TMemPool const *)xMemPool;
  _TMemBlkHdr     * pCurBlock    = pMemPool->pBeginBlock;
  int               lastRightOfs;
  int               status;

  if (pMemPool->magicNumber != MEM_POOL_MAGIC_NUMBER) return -1;

  lastRightOfs = pCurBlock->rightOffset;
  pCurBlock = (_TMemBlkHdr*)(((char*)pCurBlock) + pCurBlock->rightOffset);
  while (pCurBlock < pMemPool->pEndBlock)
  {
    if (pCurBlock->leftOffset != lastRightOfs)
    {
      /* printf ("corrupted mem ofs\n"); */
      return -1;
    }

    switch (pCurBlock->status)
    {
      case MEM_BLOCK_USED:
        if (xBlockType & MEMALLOC_TRACE_USED_BLOCK_FLAG)
          if (xReportFct)
          {
            status = xReportFct (
              (void*)&pCurBlock[1],
              pCurBlock->rightOffset - sizeof(_TMemBlkHdr),
              MEMALLOC_TRACE_USED_BLOCK_FLAG);
            if (status) return 0;
          }
        break;

      case MEM_BLOCK_FREE:
        if (xBlockType & MEMALLOC_TRACE_FREE_BLOCK_FLAG)
          if (xReportFct)
          {
            status = xReportFct (
              (void*)&pCurBlock[1],
              pCurBlock->rightOffset - sizeof(_TMemBlkHdr),
              MEMALLOC_TRACE_FREE_BLOCK_FLAG);
            if (status) return 0;
          }
        break;

      default:
        /* printf ("[xxxx] "); */
        return -1;
    }

    lastRightOfs = pCurBlock->rightOffset;
    pCurBlock = (_TMemBlkHdr*)(((char*)pCurBlock) + pCurBlock->rightOffset);
  }

  return 0;
}


/***********************************************
 * Private Functions Implementation
 ***********************************************/

/* */
static _TAVLNodeHeight getHeight
(
  _TAVLNode * pxNode
)
{
  if (pxNode == NULL) return 0;
  else return pxNode->height;
}


/* */
static _TAVLNodeHeight maxValue
(
  _TAVLNodeHeight x1,
  _TAVLNodeHeight x2
)
{
  return ((x1 > x2) ? x1 : x2);
}


/* Get Balance factor of node N */
static _TAVLNodeHeight getBalance
(
  _TAVLNode * pxNode
)
{
  return ((pxNode == NULL) ? 0 : getHeight(pxNode->pChild[LEFT]) - getHeight(pxNode->pChild[RIGHT]));
}


/* */
static _TAVLNode * pRotateRight
(
  _TAVLNode     * pxNode
)
{
  /* Note: assuming that pxNode left child is never NULL when calling this
   * function */
  _TAVLNode     * pNewRootNode = pxNode->pChild[LEFT];
  _TAVLNode     * pTmpNode = pxNode->pParent;

  pNewRootNode->pParent = pTmpNode;
  if (pTmpNode)
  {
    if (pTmpNode->pChild[LEFT] == pxNode)
      pTmpNode->pChild[LEFT] = pNewRootNode;
    else pTmpNode->pChild[RIGHT] = pNewRootNode;
  }

  pTmpNode = pNewRootNode->pChild[RIGHT];
  pxNode->pChild[LEFT] = pTmpNode;
  if (pTmpNode != NULL) pTmpNode->pParent = pxNode;

  pNewRootNode->pChild[RIGHT] = pxNode;
  pxNode->pParent = pNewRootNode;

  pxNode->height = maxValue (getHeight(pxNode->pChild[LEFT]), getHeight(pxNode->pChild[RIGHT])) + 1;
  pNewRootNode->height = maxValue (getHeight (pNewRootNode->pChild[LEFT]), getHeight (pNewRootNode->pChild[RIGHT])) + 1;

  return pNewRootNode;
}


/* */
static _TAVLNode * pRotateLeft
(
  _TAVLNode     * pxNode
)
{
  /* Note: assuming that pxNode right child is never NULL when calling this
   * function */
  _TAVLNode     * pNewRootNode = pxNode->pChild[RIGHT];
  _TAVLNode     * pTmpNode = pxNode->pParent;

  pNewRootNode->pParent = pTmpNode;
  if (pTmpNode)
  {
    if (pTmpNode->pChild[LEFT] == pxNode)
      pTmpNode->pChild[LEFT] = pNewRootNode;
    else pTmpNode->pChild[RIGHT] = pNewRootNode;
  }

  pTmpNode = pNewRootNode->pChild[LEFT];
  pxNode->pChild[RIGHT] = pTmpNode;
  if (pTmpNode != NULL) pTmpNode->pParent = pxNode;

  pNewRootNode->pChild[LEFT] = pxNode;
  pxNode->pParent = pNewRootNode;

  pxNode->height = maxValue (getHeight(pxNode->pChild[LEFT]), getHeight(pxNode->pChild[RIGHT])) + 1;
  pNewRootNode->height = maxValue (getHeight (pNewRootNode->pChild[LEFT]), getHeight (pNewRootNode->pChild[RIGHT])) + 1;

  return pNewRootNode;
}


/* */
_TAVLNode * pInsertNode
(
  _TAVLNode * pxRefNode,
  _TAVLNode * pxRootNode
)
{
  _TAVLNodeSide     childSide;
  _TAVLNodeHeight   prevHeight;
  _TAVLNode       * pNode = NULL;
  _TAVLNode       * pTmpNode;
  int               refBlockSize = ((_TMemBlkHdr*)pxRefNode)[-1].rightOffset;
  int               diffBlockSize = -1;
  _TAVLNodeHeight   balance, childBalance;

  /* Initialize the inserted node structure */
  pxRefNode->pChild[LEFT] = pxRefNode->pChild[RIGHT] = pxRefNode->pParent = NULL;
  pxRefNode->height = 1;

  /* Find the leaf where to insert the node */
  pTmpNode = pxRootNode;
  while (pTmpNode)
  {
    pNode = pTmpNode;
    diffBlockSize = refBlockSize - ((_TMemBlkHdr*)pTmpNode)[-1].rightOffset;
    if (diffBlockSize >= 0)
      pTmpNode = pTmpNode->pChild[RIGHT];
    else pTmpNode = pTmpNode->pChild[LEFT];
  }

  /* Link the Node (as a leaf) into the AVL tree */
  pxRefNode->pParent = pNode;
  childSide = ((diffBlockSize >= 0) ? RIGHT : LEFT);
  if (pNode) pNode->pChild[childSide] = pxRefNode;

  /* Rebalance the AVL tree according to the Node insertion */
  while (pNode)
  {
    prevHeight = pNode->height;
    balance = getBalance (pNode);

    /* Left Left Case */
    if (balance > 1)
    {
      childBalance = getBalance (pNode->pChild[LEFT]);
      if (childBalance < 0) pRotateLeft (pNode->pChild[LEFT]);
      pNode = pRotateRight(pNode);
    }

    else if (balance < -1)
    {
      childBalance = getBalance (pNode->pChild[RIGHT]);
      if (childBalance > 0) pRotateRight (pNode->pChild[RIGHT]);
      pNode = pRotateLeft (pNode);
    }
    else pNode->height = maxValue (getHeight(pNode->pChild[LEFT]), getHeight(pNode->pChild[RIGHT])) + 1;

    pxRefNode = pNode;
    pNode = pNode->pParent;

    if (pxRefNode->height == prevHeight)
    {
      if (pNode) return pxRootNode;
      else break;
    }
  };

  return pxRefNode;
}


/* */
static _TAVLNode * pDeleteNode
(
  _TAVLNode * pxNode,
  _TAVLNode * pxRootNode
)
{
  _TAVLNode       * pSwapNode;
  _TAVLNode       * pNode;
  _TAVLNode       * pTmpNode;
  _TAVLNodeHeight   oldHeight;
  _TAVLNodeHeight   balance;

  pNode = pxNode->pParent;
  if (!pxNode->pChild[RIGHT])
  {
    pTmpNode = pxNode->pChild[LEFT];
    if (pTmpNode) pTmpNode->pParent = pNode;

    if (!pNode) return pTmpNode;
    else
    {
      if (pNode->pChild[LEFT] == pxNode)
        pNode->pChild[LEFT] = pTmpNode;
      else pNode->pChild[RIGHT] = pTmpNode;
    }
  }
  else if (!pxNode->pChild[LEFT])
  {
    pTmpNode = pxNode->pChild[RIGHT];
    pTmpNode->pParent = pNode;

    if (!pNode) return pTmpNode;
    else
    {
      if (pNode->pChild[LEFT] == pxNode)
        pNode->pChild[LEFT] = pTmpNode;
      else pNode->pChild[RIGHT] = pTmpNode;
    }
  }
  else
  {
    pTmpNode = pxNode->pChild[LEFT];
    do
    {
      pSwapNode = pTmpNode; pTmpNode = pTmpNode->pChild[RIGHT];
    } while (pTmpNode);

    if (pSwapNode->pChild[LEFT]) pRotateRight(pSwapNode);

    if (pNode)
    {
      if (pNode->pChild[LEFT] == pxNode) pNode->pChild[LEFT] = pSwapNode;
      else pNode->pChild[RIGHT] = pSwapNode;
    }
    else pxRootNode = pSwapNode;

    pSwapNode->height = pxNode->height;
    pTmpNode = pxNode->pChild[RIGHT];
    pSwapNode->pChild[RIGHT] = pTmpNode;
    pTmpNode->pParent = pSwapNode;

    pTmpNode = pNode;
    pNode = pSwapNode->pParent;
    pSwapNode->pParent = pTmpNode;

    if (pNode == pxNode) { pSwapNode->pChild[LEFT] = NULL; pNode = pSwapNode;}
    else
    {
      pNode->pChild[RIGHT] = NULL;
      pTmpNode = pxNode->pChild[LEFT];
      pSwapNode->pChild[LEFT] = pTmpNode;
      pTmpNode->pParent = pSwapNode;
    }
  }

  pTmpNode = pNode;
  do
  {
    oldHeight = pTmpNode->height;
    balance = getBalance (pTmpNode);

    if (balance > 1)
    {
      pSwapNode = pTmpNode->pChild[LEFT];
      if (getBalance(pSwapNode) < 0) pRotateLeft (pSwapNode);
      pTmpNode = pRotateRight(pTmpNode);
    }
    else if (balance < 0)
    {
      pSwapNode = pTmpNode->pChild[RIGHT];
      if (getBalance(pSwapNode) > 0) pRotateRight (pSwapNode);
      pTmpNode = pRotateLeft(pTmpNode);
    }
    else pTmpNode->height = maxValue (getHeight(pTmpNode->pChild[LEFT]), getHeight(pTmpNode->pChild[RIGHT])) + 1;

    pNode = pTmpNode;
    pTmpNode = pTmpNode->pParent;

    if (oldHeight == pNode->height)
    {
      if (pTmpNode) return pxRootNode;
      else break;
    }

  } while (pTmpNode);

  return pNode;
}


/* */
static _TAVLNode * pMemPool_findBestNode
(
  _TAVLNode * pxRootNode,
  int         xSize
)
{
  _TAVLNode * pRefNode = NULL;
  int         diffSize;

  while (pxRootNode)
  {
    diffSize = ((_TMemBlkHdr*)pxRootNode)[-1].rightOffset - xSize;

    if (diffSize >= 0)
    {
      pRefNode = pxRootNode;
      pxRootNode = pxRootNode->pChild[LEFT];
    }
    else pxRootNode = pxRootNode->pChild[RIGHT];
  }

  return pRefNode;
}


/* */
static int pMemPool_findBiggestFreeMemBlock
(
  _TAVLNode * pxRootNode
)
{
  _TAVLNode * pTmpNode = NULL;

  while (pxRootNode)
  {
    pTmpNode = pxRootNode;
    pxRootNode = pxRootNode->pChild[RIGHT];
  }

  if (pTmpNode) return ((_TMemBlkHdr*)pTmpNode)[-1].rightOffset - sizeof(_TMemBlkHdr);
  else return -1;
}
