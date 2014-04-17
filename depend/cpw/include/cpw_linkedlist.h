/***************************************************************************/
/*                                                                         */
/*  cpw_linkedlist.h                                                       */
/*                                                                         */
/*    Cpw's linked list. General purpose linked list routines.             */
/*                                                                         */
/*  Copyright 2001-2002 by                                                 */
/*  Jim Mathies,                                                           */
/*                                                                         */
/*  This file is part of the Cpw project, and may only be used,            */
/*  modified, and distributed under the terms of the Cpw project           */
/*  license.  By continuing to use, modify, or distribute this file        */
/*  you indicate that you have read the license and understand and         */
/*  accept it fully.                                                       */
/*                                                                         */
/*  File Platform: cross                                                   */
/*                                                                         */
/***************************************************************************/

#ifndef __cpw_linkedlist_h__
#define __cpw_linkedlist_h__

#include "cpw_config.h"
#include "cpw_linkedelement.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    LinkedListData                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    List context - contains the list info.                             */
  /*                                                                       */
  struct _LinkedListData 
  {
      uint_32             idcount;
      LinkedElement *     baseElement;
  };
  typedef struct _LinkedListData LinkedListData;
  /*                                                                       */
  /*************************************************************************/



/* init of list data structure */

extern CPW_INLINE void 
ll_initList( LinkedListData * lld );

/* deletes a list's contents. returns the number of objects collected */

extern CPW_INLINE uint_32
ll_deleteList( LinkedListData * lld );

/* create and init a list */

extern CPW_INLINE LinkedListData * 
ll_createList( void );

/* delete and free a list pointer */

extern CPW_INLINE void 
ll_freeList( LinkedListData ** lld );

/* returns id of element or 0 on error */

extern CPW_INLINE uint_32 
ll_addStr( LinkedListData * lld, pStr string );

/* returns id of element or 0 on error */

extern CPW_INLINE uint_32 
ll_addString( LinkedListData * lld, char* string );

/* returns id of element or 0 on error */

extern CPW_INLINE uint_32 
ll_addFloat64( LinkedListData * lld, float_64 number );

/* returns id of element or 0 on error */

extern CPW_INLINE uint_32 
ll_addInt32( LinkedListData * lld, int_32 number );

/* returns id of element or 0 on error */

extern CPW_INLINE uint_32 
ll_addVoid( LinkedListData * lld, void * p );

/* returns pStr or null if not found */

extern CPW_INLINE bool
ll_getString( LinkedListData * lld, pStr* string, uint_32 id );

/* returns void* pointer or null if not found */

extern CPW_INLINE bool
ll_getVoid( LinkedListData * lld, void** pdata, uint_32 id );

/* returns bool indicating success or failure, fills string with value if found */

extern CPW_INLINE bool
ll_popString( LinkedListData * lld, pStr * string );

extern CPW_INLINE bool
ll_popFloat64( LinkedListData * lld, float_64 * number );

extern CPW_INLINE bool
ll_popInt32( LinkedListData * lld, int_32 * number );

extern CPW_INLINE bool
ll_setVoid( LinkedListData * lld, uint_32 id, void* p );

extern CPW_INLINE bool
ll_deleteElement( LinkedListData * lld, uint_32 id );

extern CPW_INLINE int_32 
ll_getLength( LinkedListData * lld );

extern CPW_INLINE bool 
ll_initIterate( LinkedListData * lld );

extern CPW_INLINE LinkedElement *
ll_getNext( LinkedListData * lld );

extern CPW_INLINE LinkedElement *
ll_getElement( LinkedListData * lld, uint_32 id );

extern CPW_INLINE uint_32 
ll_linkUp( LinkedListData * lld, LinkedElement* le );

/* unlink an element. does not delete the element. */

extern CPW_INLINE bool
ll_unLink( LinkedListData * lld, uint_32 id ); 

/* flip the list over into a new list. lld must have been created 
   with ll_createList(). It is iterated, deleted, freed here and then replaced. */

extern CPW_INLINE bool
ll_flipList( LinkedListData ** lld ); 

CPW_END_HEADER

#endif
