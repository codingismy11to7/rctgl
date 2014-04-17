/***************************************************************************/
/*                                                                         */
/*  cpw_glextensions.h                                                     */
/*                                                                         */
/*    Utility functions for querying support of and iterating each of      */
/*    the localhost's OpenGL extensions.                                   */
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

#ifndef __cpw_glextensions_h__
#define __cpw_glextensions_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwIterateExtensions                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Iterates each extension supported, returning a null terminated     */
  /*    string or null when the end of the list is reached.                */
  /*                                                                       */
  CPW_API pChar 
  cpwIterateExtensions( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwExtensionSupport                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Tests to see if a particluar extension is supported using a        */
  /*    string search across the entire extension string list.             */
  /*                                                                       */
  CPW_API bool  
  cpwExtensionSupport( pCpw cpw, 
                       pChar string );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwIterateExtensionsReset                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Resets the iteration index for cpwIterateExtensions.               */
  /*                                                                       */
  CPW_API bool  
  cpwIterateExtensionsReset( pCpw cpw );
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
  /* <Struct>                                                              */
  /*    CpwExtensionList                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Hold a list of opengl extensions this localhost supports.          */
  /*                                                                       */
  struct _CpwExtensionList
  {
    pChar   list;
    uint_32 size;
    uint_32 index;
    bool    init;
  };
  typedef struct _CpwExtensionList CpwExtensionList;
  /*                                                                       */
  /*************************************************************************/


  bool cpw_glextensions_init( pCpw cpw );
  void cpw_glextensions_exit( pCpw cpw );
  bool cpw_glextensions_initlist( pCpw cpw );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
