/***************************************************************************/
/*                                                                         */
/*  cpw_dragdrop.h                                                         */
/*                                                                         */
/*    Cpw drag and drop interface.                                         */
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

#ifndef __cpw_dragdrop_h__
#define __cpw_dragdrop_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwDDObject                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwDDObject
  {
    pChar mimetype;
    pChar filename;
    pVoid data;
  };
  typedef struct _CpwDDObject CpwDDObject;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwDDList                                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwDDList
  {
    CpwDDObject* objs;
    uint_32      size;
  };
  typedef struct _CpwDDList CpwDDList;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    CpwDropCallback                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Drop callback function prototype.                                  */
  /*                                                                       */
  typedef void (*CpwDropCallback) ( pCpw cpw, CpwDDList * list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    CpwDragCallback                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Drag callback function prototype.                                  */
  /*                                                                       */
  typedef CpwDDList* (*CpwDragCallback) ( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDropCallback                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool 
  cpwDropCallback( pCpw cpw, 
                   CpwDropCallback dropcb );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDragCallback                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool 
  cpwDragCallback( pCpw cpw, 
                   CpwDragCallback dragcb );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
