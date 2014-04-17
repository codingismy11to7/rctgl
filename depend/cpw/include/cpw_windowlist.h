/***************************************************************************/
/*                                                                         */
/*  cpw_windowlist.h                                                       */
/*                                                                         */
/*    The Cpw library windowlist manager.                                  */
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

#ifndef __cpw_windowlist_h__
#define __cpw_windowlist_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_window.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  bool    cpw_windowlist_init( pCpw cpw );
  void    cpw_windowlist_exit( pCpw cpw );
  void    cpw_windowlist_free( pCpw cpw );
  uint_32 cpw_windowlist_insert( pCpw cpw, pCpwWin window );
  uint_32 cpw_windowlist_length( pCpw cpw );
  bool    cpw_windowlist_replace( pCpw cpw, pCpwWin window, uint_32 id );
  pCpwWin cpw_windowlist_remove( pCpw cpw, uint_32 id );
  pCpwWin cpw_windowlist_lookup( pCpw cpw, uint_32 id );
  pCpwWin cpw_windowlist_iteratestart( pCpw cpw );
  pCpwWin cpw_windowlist_iteratenext( pCpw cpw );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
