/**
**  @file avlset.h
**
** @brief
**    Set /Multi-set AVL tree based implementation
**
**    This header file describes the API of a C++ like set/multiset.
**    As a main difference with the C++ standard set multiset implementation,
**    this implement does not allocate any data at insertion time and do not
**    dynamically deallocate any data at deletion time.
**
**    It only reference/unreference node in a set.
**
**    The set or multiset option is defined at Set handle intialization making
**    the interface identifical for both: set and multi-set like feature.
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

#ifndef _AVL_SET_H_
#define _AVL_SET_H_


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the version number of the Memory pool API.
 * Note also that this version number
 * does not correspond to the version number of the software version.
 */
#define AVL_SET_VERSION_MAJOR   1
#define AVL_SET_VERSION_MEDIUM  0
#define AVL_SET_VERSION_MINOR   0


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
 *  This document is intended to provide the API of a set/multi set
 *  caracterized by a 0-ln(n) search, insert and remove algorithm
 *  (AVL tree based).
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
/*              Types, structures and constants definitions                */
/*                                                                         */
/***************************************************************************/

/* AVL SIDE identifier */
#define AVLSET_LEFT     0
#define AVLSET_RIGHT    1
#define AVLSET_SIDE_NUM 2

typedef unsigned char    TAVLSet_side;

/**
 *  @ingroup set
 *
 *  @brief
 *    Set/Multiset handle type definition
*/
typedef struct SAVLSet TAVLSet;

/**
 *  @ingroup set
 *
 *  @brief
 *    Set/Multiset iter handle type definition
*/
typedef struct SAVLSet_iter TAVLSet_iter;

/**
 *  @ingroup set
 *
 *  @brief
 *    Set/Multiset iter AVL height
*/
typedef short int        TAVLSet_height;


/**
 *  @ingroup set
 *
 *  @brief
 *    Set/Multiset compare call back function type definition
*/
typedef int    (*TAVLSet_compare)(TAVLSet_iter * pxIter1,TAVLSet_iter * pxIter2);


/**
 *  @ingroup set
 *
 *  @brief
 *    AVL Set/Multiset iter structure definition
*/
struct SAVLSet_iter
{
  TAVLSet_iter   * pChild[2];
  TAVLSet_iter   * pNeighbor[2];
  TAVLSet_iter   * pParent;
  TAVLSet_height   height;
};

/**
 *  @ingroup set
 *
 *  @brief
 *    AVL Set/Multiset handle structure definition
*/
struct SAVLSet
{
  TAVLSet_iter    * pRootIter;
  TAVLSet_iter      beginIter;
  TAVLSet_iter      endIter;
  TAVLSet_compare   compare;
  int               isMSet;
  int               size;
};


/***************************************************************************/
/*                                                                         */
/*                   SET Structure initialization                          */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup set_init
 *
 *  @brief
 *    Initialize a set/multiset handle
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle to be initialized
 *  @param[in]  xCompare
 *    set/multiset compare function (cannot be passed as NULL)
 *  @param[in]  xIsMSet
 *    is multiset indicator
 *
 *  @retval
 *    None
*/
void AVLSet_init
(
  TAVLSet          * pxSet,
  TAVLSet_compare    xCompare,
  int                xIsMSet
);

/**
 *  @ingroup set_init
 *
 *  @brief
 *    Initialize a set/multiset iterator handle
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxIter
 *    Set/Multiset iterator handle to be initialized
 *
 *  @retval None
*/
void AVLSet_iterInit
(
  TAVLSet_iter * pxIter
);


/***************************************************************************/
/*                                                                         */
/*                   Set/Multiset manipulation functions                   */
/*                                                                         */
/***************************************************************************/


/**
 *  @ingroup set_operator
 *
 *  @brief
 *    Insert an iterator into a set/multiset
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle in which one the iterator should be inserted.
 *  @param[in]  pxIter
 *    Iterator to be inserted
 *
 *  @retval   The reference of the iterator that was inserted or
 *            the end iterator of the set/multiset if insertion
 *            failed.
*/

/* */
TAVLSet_iter * AVLSet_insert
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
);


/**
 *  @ingroup set_operator
 *
 *  @brief
 *    Insert an iterator into a set/multiset after another iterator
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle in which one the iterator should be inserted.
 *  @param[in]  pxIter
 *    Iterator to be inserted
 *  @param[in]  pxAfterIter
 *    Iterator of the set/multi set after which one to insert the
 *    'pxIter' iterator.
 *
 *  @retval   The reference of the iterator that was inserted or
 *            the end iterator of the set/multiset if insertion
 *            failed.
*/
TAVLSet_iter * AVLSet_insertAfter
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter,
  TAVLSet_iter * pxAfterIter
);


/**
 *  @ingroup set_operator
 *
 *  @brief
 *    Remove an iterator from a set/multiset after another iterator
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle in which one the iterator should be removed from.
 *  @param[in]  pxIter
 *    Iterator to be removed
 *
 *  @retval
 *    None
 *
 *  @remark
*/
void AVLSet_remove
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
);


/***************************************************************************/
/*                                                                         */
/*                   Set/Multiset lookup functions                         */
/*                                                                         */
/***************************************************************************/

/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    Find an iterator in a set/multi set.
 *    Return end() iterator is not found.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle in which the iterator should be found.
 *  @param[in]  pxIter
 *    Iterator reference value
 *
 *  @retval
 *    None
 *
 *  @remark
*/
TAVLSet_iter * AVLSet_find
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
);

/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    Find the lower bound iterator in a set/multi set.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle in which the iterator should be found.
 *  @param[in]  pxIter
 *    Iterator reference value
 *
 *  @retval
 *    None
 *
 *  @remark
*/
TAVLSet_iter * AVLSet_lowerBound
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
);

/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    Find the upper bound iterator in a set/multi set.
 *
 *  @pre
 *    None.
 *
 *  @post
 *    None.
 *
 *  @param[in,out]  pxSet
 *    Set/Multiset handle in which the iterator should be found.
 *  @param[in]  pxIter
 *    Iterator reference value
 *
 *  @retval
 *    None
 *
 *  @remark
*/
TAVLSet_iter * AVLSet_upperBound
(
  TAVLSet      * pxSet,
  TAVLSet_iter * pxIter
);


/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    get the end() iterator of a set/multiset
*/
#define AVLSet_end(_pxSet) (&(_pxSet)->endIter)


/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    get the begin() iterator of a set/multiset
*/
#define AVLSet_begin(_pxSet) (&(_pxSet)->beginIter)


/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    get the next() iterator of a set/multiset
*/
#define AVLSet_next(_pxIter) ((_pxIter)->pNeighbor[AVLSET_RIGHT]);


/**
 *  @ingroup set_lookup
 *
 *  @brief
 *    get the prev() iterator of a set/multiset
*/
#define AVLSet_prev(_pxIter) ((_pxIter)->pNeighbor[AVLSET_LEFT]);


#ifdef __cplusplus
}
#endif

#endif /* _AVL_SET_H_ */
