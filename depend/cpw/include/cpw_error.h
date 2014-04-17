/***************************************************************************/
/*                                                                         */
/*  cpw_error.h                                                            */
/*                                                                         */
/*    Querying for and setting last error values.                          */
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

#ifndef __cpw_error_h__
#define __cpw_error_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Cpw Error Codes                                                    */
  /*                                                                       */
  enum CpwErrorCodes {
    cpw_error_noerror                   = 0,  /* no error */
    cpw_error_unknown                   = 1,  /* unknown error (cpw_fonts) */
    cpw_error_outofmemory               = 2,  /* out of memory */
    cpw_error_invalidparameter          = 3,  /* invalid parameter */
    cpw_error_invalidfont               = 4,  /* invalid font file */
    cpw_error_initfailed                = 5,  /* initialization failed */
    cpw_error_createwindowfailed        = 6,  /* failed to create the window */
    cpw_error_visualformatunsupported   = 7,  /* draw surface format is not supported */
    cpw_error_visualformatinvalid       = 8,  /* failed to set draw surface visual format */
    cpw_error_createcontextfailed       = 9,  /* failed to create a gl rendering context */
    cpw_error_setcurrentcontextfailed   = 10, /* failed to set gl rendering context current */
    cpw_error_failedtosetvideo          = 11, /* video resolution format not supported */
    cpw_error_failedtogetvideo          = 12, /* could not enumerate video modes */
    cpw_error_novalidcontext            = 13, /* call occured before a valid window exists */
    cpw_error_invalidmenuid             = 14, /* invalid menu id specified */
    cpw_error_maxentriesreached         = 15, /* max menu entries reached */
    cpw_error_invalidwindowid           = 16, /* invalid window id specified */
    cpw_error_unabletoassignmenu        = 17, /* assign menu to window failed */
    cpw_error_menunotassigned           = 18, /* the menu was not assigned to the window */
    cpw_error_invalidentryid            = 19, /* invalid menu entry id */
    cpw_error_invalidjoystickid         = 20, /* invalid joystick id specified */
    cpw_error_failedtoload              = 21, /* failed to load the file */
    cpw_error_invalidformat             = 22, /* invalid image format */
  };
  #define cpw_success cpw_error_noerror       /* the call was successful */
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwGetLastError                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Returns the error code for the last Cpw error that occured.         */
  /*                                                                       */
  CPW_API int_32 
  cpwGetLastError( pCpw cpw ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwSetLastError                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Sets the last error code.                                           */
  /*                                                                       */
  CPW_API void   
  cpwSetLastError( pCpw cpw, int_32 errorcode ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  void cpw_error_set( pCpw cpw, int_32 errorcode ); 

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
