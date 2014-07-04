/**
**  @file memAlloc.h
**
** @brief
**    Memory pool allocator
**
**    This header file describes the API of dynamic memory allocator operating on
**    on a statically pre-allocator buffer (called memory pool).
**
**    This memory pool is intended to provide the same feature as a on-heap memory
**    allocation for SW programs that do not run on an OS.
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

#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the version number of the Memory pool API.
 * Note also that this version number
 * does not correspond to the version number of the software version.
 */
#define MEM_POOL_VERSION_MAJOR   1
#define MEM_POOL_VERSION_MEDIUM  0
#define MEM_POOL_VERSION_MINOR   0


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
 *  This document is intended to provide the API of a memory pool allocator.
 *
 *  A memory pool allocator is intended to provide dynamic allocation
 *  mechanism for applications that do not run on an OS.
 *
 *  The only difference between an OS memory allocator is that memory is
 *  not allocated on a heap. It is allocated in a statically pre-allocated
 *  buffer inside the application.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for non OS-based application or for custom
 *  kernel or OS development.
 *
 *  <hr><h2>References</h2>
*/


 /** @defgroup memory_pool       Memory pool configuration */
 /** @defgroup memory_pool_alloc Memory Allocation */
 /** @defgroup memory_pool_info  Memory pool Info */
 /** @defgroup memory_pool_debug Memory pool Debug */



/***************************************************************************/
/*                                                                         */
/*                             FUNCTION PROTOTYPES                         */
/*                                                                         */
/***************************************************************************/

/**
 *  @ingroup memory_pool
 *
 *  @brief
 *
 *    Memory pool abstract handle
*/
typedef void * TMemPool;


/**
 *  @ingroup memory_pool
 *
 *  @brief
 *
 *    Memory pool abstract mutex handle
*/
typedef void * TMemPool_mutexHandle;


/**
 *  @ingroup memory_pool
 *
 *  @brief
 *    Memory pool mutual access acquire callback function
 *
 *  @param[in,out]  xMutex
 *                memory pool abstract mutex
 *
 *  @retval   0 if Mutex successfully acquired (otherwize, return -1)
*/
typedef int (*TMemPool_mutexAcquire_fct) (TMemPool_mutexHandle xMutex);


/**
 *  @ingroup memory_pool
 *
 *  @brief
 *    Memory pool mutual access release callback function
 *
 *  @param[in,out]  xMutex
 *                memory pool abstract mutex
 *
 *  @retval   0 if Mutex successfully released (otherwize, return -1)
*/
typedef int (*TMemPool_mutexRelease_fct) (TMemPool_mutexHandle xMutex);


/**
 *  @ingroup memory_pool
 *
 *  @brief
 *    Initialize a memory pool operating on a pre-allocated RAM buffer.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in]  pxMemPoolBuffer
 *               Address of the memory buffer intended to serve as a memory
 *               pool
 *  @param[in]  xMemPoolBufferByteSize
 *               Size memory buffer intended to serve as a memory
 *               pool.
 *  @param[in]  xAcquireFct
 *               Pool mutex acquire callback function (or NULL is no Mutex)
 *  @param[in]  xReleaseFct
 *               Pool mutex release callback function (or NULL is no Mutex)
 *  @param[in,out]  xMutexHandle
 *               Abstract Mutex handle (or NULL is not provided)
 *
 *  @retval
 *    An abstract memory pool pointer (or NULL if intialization failed)
 *
 *  The input pre-allocated RAM buffer can be (or condition)\n
 *  - A application static pool buffer (static allocation)\n
 *  - A OS dynamically allocated buffer (if OS memory allocation resource
 *    is available)\n
 *  - A memory buffer itself obtained from a memory pool (nested memory pools)\n\n
 *
 *  Memory pool requires that pre-allocated buffer is at least "pointer-aligned".
 *  This is the reason why it is expressed as an array of (void*) instead of as
 *  a void*. This is however a pure artifact intended to ensure that this
 *  pre-requisite is well implemented.
 *
 *  If thread safe is not mandatory for application, xAcquireFct,
 *  xReleaseFct and xMutexHandle can be passed as NULL. If not, both
 *  xAcquireFct and xReleaseFct should be provided as non-NULL function
 *  address.
 *
 *  xMutexHandle is not directly used by the implementation but simply passed
 *  to the xAcquireFct and xReleaseFct functions.
 *
 * @remark
 *  Assumption is done that the mutex provided as an input parameter was
 *  successfully initialilized to 0 before calling this function.
*/

TMemPool memPool_init
(
  void                      * pxMemPoolBuffer[],
  int                         xMemPoolBufferByteSize,
  TMemPool_mutexAcquire_fct   xAcquireFct,
  TMemPool_mutexRelease_fct   xReleaseFct,
  TMemPool_mutexHandle        xMutexHandle
);


/***************************************************************************/
/*                                                                         */
/*                   Memory allocation/deallocation                        */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup memory_pool_alloc
 *
 *  @brief
 *    Allocate a buffer from a memory pool.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  xMemPool
 *               memory pool handle (in which allocation should be done)
 *
 *  @param[in]  xMemSize
 *               Size of the memory to allocate
 *
 *
 *  @retval   The address of the allocated buffer (or NULL if intialization failed)
 *
*/

void * memPool_malloc
(
  TMemPool xMemPool,
  int      xMemSize
);


/**
 *  @ingroup memory_pool_alloc
 *
 *  @brief
 *    Allocate a buffer from a memory pool.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  xMemPool
 *               memory pool handle (in which allocation should be done)
 *  @param[in]  pxBuffer
 *               In-pool initialy allocated buffer
 *  @param[in]  xNewSize
 *               new block size
 *
 *
 *  @retval   The address of the reallocated buffer (or NULL if intialization failed)
*/

void * memPool_realloc
(
  TMemPool   xMemPool,
  void     * pxBuffer,
  int        xNewSize
);


/**
 *  @ingroup memory_pool_alloc
 *
 *  @brief
 *    Deallocate a buffer previously allocated from a memory pool.
 *
 *  @pre
 *    Buffer to be deallocated in a pool shall have been allocated from
 *    the same pool.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  xMemPool
 *               memory pool handle (in which allocation should be done)
 *
 *  @param[in]  pxBuffer
 *               In-pool previously allocated buffer
 *
 *
 *  @retval   None
 *
*/

void memPool_free
(
  TMemPool   xMemPool,
  void     * pxBuffer
);


/***************************************************************************/
/*                                                                         */
/*                             Memory pool Info                            */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup memory_pool_info
 *
 *  @brief
 *    Memory pool info structure definition
 */
typedef struct SMemPoolInfo TMemPoolInfo;


/**
 *  @ingroup memory_pool_info
 *
 *  @brief
 *    Memory pool usage info structure definition
 */
typedef struct SMemPoolUsageInfo TMemPoolUsageInfo;


/**
 *  @ingroup memory_pool_info
 *
 *  @brief
 *    Memory pool info structure definition
 */
struct SMemPoolInfo
{
  struct
  {
    int      version_majorDigit;
    /**< Memory pool implementation major version digit */

    int      version_mediumDigit;
    /**< Memory pool implementation medium version digit */

    int      version_minorDigit;
    /**< Memory pool implementation minor version digit */

  } implementation;
  /**< Memory pool implementation info */

  struct
  {
    int       userMemoryPoolSize;
    /**< User memory size associated to the pool */

  } config;
  /**< Memory pool configuration info */

};


/**
 *  @ingroup memory_pool_info
 *
 *  @brief
 *    Memory pool usage info structure definition
 */
struct SMemPoolUsageInfo
{
  int       currentFreeMemorySize;
  /**< Current free memory sizein the pool */

  int       currentUsedMemorySize;
  /**< Current used memory size in the pool */

  int       currentAllocatedBlockNumber;
  /**< Current used memory block number in the pool */

  int       currentFragBlockNumber;
  /**< Current fragmentation block number in the pool */

  int       lostUserMemorySize;
  /**< Current lost user memory size in the pool */

  int       currentMaxFreeMemoryBlockSize;
  /**< Current MAX memory block size */
};


/**
 *  @ingroup memory_pool_info
 *
 *  @brief
 *    Report buffers currently pre-allocated in a memory pool.
 *
 *  @pre
 *    None
 *
 *  @post
 *    None.
 *
 *  @param[in]   xMemPool
 *               memory pool handle (in which allocation should be done)
 *  @param[out]  pxMemPoolInfo
 *               Reference to the memory pool info structure to be filled up
 *  @retval
 *      Return 0 if no error (-1 otherwize)
*/
int memPool_getInfo
(
  const TMemPool   xMemPool,
  TMemPoolInfo   * pxMemPoolInfo
);


/**
 *  @ingroup memory_pool_info
 *
 *  @brief
 *    Report buffers currently pre-allocated in a memory pool.
 *
 *  @pre
 *    None
 *
 *  @post
 *    None.
 *
 *  @param[in]   xMemPool
 *               memory pool handle (in which allocation should be done)
 *  @param[out]  pxMemPoolUsageInfo
 *               Reference to the memory pool usage info structure to be filled up
 *  @retval
 *      Return 0 if no error (-1 otherwize)
*/
int memPool_getUsageInfo
(
  const TMemPool      xMemPool,
  TMemPoolUsageInfo * pxMemPoolUsageInfo
);

/***************************************************************************/
/*                                                                         */
/*                       Memory Pool Debug                                 */
/*                                                                         */
/***************************************************************************/


#define MEMALLOC_TRACE_USED_BLOCK_FLAG  (1 << 0)
#define MEMALLOC_TRACE_FREE_BLOCK_FLAG  (1 << 1)

/**
 *  @ingroup memory_pool_debug
 *
 *  @brief
 *    Memory pool trace block types
*/
typedef enum
{
  MEMALLOC_TRACE_USED_BLOCKS = MEMALLOC_TRACE_USED_BLOCK_FLAG,
    /**< Trace in memory pool used blocks type */

  MEMALLOC_TRACE_FREE_BLOCKS = MEMALLOC_TRACE_FREE_BLOCK_FLAG,
    /**< Trace in memory pool free blocks type */

  MEMALLOC_TRACE_ALL_BLOCKS = (MEMALLOC_TRACE_FREE_BLOCK_FLAG | MEMALLOC_TRACE_USED_BLOCK_FLAG)
    /**< Trace in memory pool free blocks type */

} TMemAllocTrace;


/**
 *  @ingroup memory_pool_debug
 *
 *  @brief
 *    Memory pool report callback function type definition
 *
 *  @param[out]  pxBufferAddress
 *               Address of used block
 *  @param[out]  xBlockAllocatedSize
 *               Size of the used block
 *  @retval 0
 *     If memory pool scanning shall continue
 *  @retval 1
 *     If memory pool scanning shall stop
*/
typedef int (*TMemPoolUsedBlockReportFct) (
  const void     * pxBufferAddress,
  int              xBlockAllocatedSize,
  TMemAllocTrace   xBlockType );


/**
 *  @ingroup memory_pool_debug
 *
 *  @brief
 *    Report buffers currently pre-allocated in a memory pool.
 *
 *  @pre
 *    None
 *
 *  @post
 *    None.
 *
 *  @param[in]  xMemPool
 *               memory pool handle (in which allocation should be done)
 *
 *  @param[in]  xBlockType
 *               Block types to be traced
 *
 *  @param[in]  xReportFct
 *               Used block report call back function
 *
 *
 *  @retval
 *    Return  0 if successfully setup.
 *    Return -1 if memory pool is corrupted
 *
 *  This function is provided as a pure debug function (e.g: for
 *  tracing memory leak in an application)
 *
*/
int memPool_traceUsedBlock
(
  const TMemPool             xMemPool,
  TMemAllocTrace             xBlockType,
  TMemPoolUsedBlockReportFct xReportFct
);



#ifdef __cplusplus
}
#endif

#endif /* _MEMORY_POOL_H_ */
