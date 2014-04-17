/***************************************************************************/
/*                                                                         */
/*  cpw_callbacks.h                                                        */
/*                                                                         */
/*    Contains window event callback prototype definitions and the         */
/*    default event callbacks for Cpw.                                     */
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

#ifndef __cpw_callbacks_h__
#define __cpw_callbacks_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Global event callback function prototypes                          */
  /*                                                                       */
  typedef void (*CpwCreateCallback)         ( pCpw cpw, uint_32 id, bool flag ); 
  typedef void (*CpwDisplayCallback)        ( pCpw cpw, uint_32 id ); 
  typedef void (*CpwPositionCallback)       ( pCpw cpw, uint_32 id, uint_32 x, uint_32 y ); 
  typedef void (*CpwReshapeCallback)        ( pCpw cpw, uint_32 id, uint_32 w, uint_32 h ); 
  typedef void (*CpwKeyboardCallback)       ( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y );
  typedef void (*CpwSystemKeyboardCallback) ( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y );
  typedef void (*CpwMouseClickCallback)     ( pCpw cpw, uint_32 id, uint_32 button, uint_32 state, uint_32 x, uint_32 y );
  typedef void (*CpwMouseDragCallback)      ( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y );
  typedef void (*CpwMouseMoveCallback)      ( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
  typedef void (*CpwMouseEntryCallback)     ( pCpw cpw, uint_32 id, uint_32 state ); 
  typedef void (*CpwVisibilityCallback)     ( pCpw cpw, uint_32 id, uint_32 state ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    Default Callbacks                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    These functions take the place of global event callback if         */
  /*    a particular callback isn't set. They are all nop's except         */
  /*    on a window destroy event which closes the open window.            */
  /*                                                                       */
  void defaultCreateCallback( pCpw cpw, uint_32 id, bool flag );
  void defaultDisplayCallback( pCpw cpw, uint_32 id );
  void defaultReshapeCallback( pCpw cpw, uint_32 id, uint_32 w, uint_32 h );
  void defaultVisibilityCallback( pCpw cpw, uint_32 id, uint_32 state );
  void defaultPositionCallback( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
  void defaultMouseClickCallback( pCpw cpw, uint_32 id, uint_32 state, uint_32 button, uint_32 x, uint_32 y );
  void defaultMouseMoveCallback( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
  void defaultMouseDragCallback( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y );
  void defaultKeyboardCallback( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y );
  void defaultSystemKeyboardCallback( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y );
  void defaultMouseEntryCallback( pCpw cpw, uint_32 id, uint_32 state );
  /*                                                                       */
  /*************************************************************************/

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
