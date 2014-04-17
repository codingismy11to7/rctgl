/***************************************************************************/
/*                                                                         */
/*  cpw_linkedelement.h                                                    */
/*                                                                         */
/*    LinkedElement, used by LinkedList.                                   */
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

#ifndef __cpw_linkedelement_h__
#define __cpw_linkedelement_h__

#include "cpw_config.h"
#include "cpw_str.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    LinkedElementType                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  enum _LinkedElementType 
  {
      Element_Empty      = 0,
      Element_Float64    = 1,
      Element_Int32      = 2,
      Element_pStr       = 3,
      Element_Void       = 4
  };
  typedef enum _LinkedElementType LinkedElementType;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    LinkedElement                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _LinkedElement 
  {
      union 
      { 
          int_32          e_int_32;
          float_64        e_float_32;
          void *          e_pvoid;
          pStr            e_pstr;
      } e;
      LinkedElementType   etype;
      uint_32             id;
      bool                iterate;
      void *              childtomyright;
  };
  typedef struct _LinkedElement LinkedElement;
  /*                                                                       */
  /*************************************************************************/


/* default construction */

extern CPW_INLINE LinkedElement*
le_createElement( void );

/* init a pStr element */

extern CPW_INLINE LinkedElement*
le_initStr( pStr string, uint_32 id );

/* init a string element */

extern CPW_INLINE LinkedElement*
le_initString( char* string, uint_32 id );

/* init a 64 bit float element */

extern CPW_INLINE LinkedElement*
le_initFloat64( float_64 number, uint_32 id );

/* init a 32 bit int element */

extern CPW_INLINE LinkedElement*
le_initInt32( int_32 number, uint_32 id );

/* init a void* pointer element */

extern CPW_INLINE LinkedElement*
le_initVoid( void * userp, uint_32 id );

/* default destruction */

extern CPW_INLINE void
le_freeElement( LinkedElement** le );

/* getters */

extern CPW_INLINE LinkedElementType 
le_getType( LinkedElement* le );

extern CPW_INLINE pStr
le_getString( LinkedElement* le );

extern CPW_INLINE void*
le_getVoid( LinkedElement* le );

extern CPW_INLINE float_64
le_getFloat64( LinkedElement* le );

extern CPW_INLINE int_32
le_getInt32( LinkedElement* le );

extern CPW_INLINE uint_32  
le_getId( LinkedElement* le ); 

/* setters */

extern CPW_INLINE void 
le_setId( LinkedElement* le, uint_32 id );

extern CPW_INLINE void
le_setVoid( LinkedElement* le, void* p );

/* purge the list of elements */

extern CPW_INLINE void
le_cleanUp( LinkedElement* le, uint_32 * pkillcount ); 

/* add an element */

extern CPW_INLINE void 
le_linkUp(  LinkedElement* le, LinkedElement* sibling ); 

/* remove an element */

extern CPW_INLINE LinkedElement*
le_unLink( LinkedElement* me, LinkedElement * myParent, uint_32 id ); 

/* find an element */

extern CPW_INLINE LinkedElement* 
le_seek( LinkedElement* le, uint_32 id ); 

/* count elements */

extern CPW_INLINE void 
le_countUp( LinkedElement* le, uint_32 * pcount ); 

/* iterate all elements - init */

extern CPW_INLINE void 
le_initIterate( LinkedElement* le ); 

/* iterate all elements - next */

extern CPW_INLINE LinkedElement*
le_getNext( LinkedElement* le ); 

/* get the last element */

extern CPW_INLINE LinkedElement*
le_lastOne( LinkedElement* le ); 

CPW_END_HEADER

#endif
