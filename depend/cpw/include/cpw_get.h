/***************************************************************************/
/*                                                                         */
/*  cpw_get.h                                                              */
/*                                                                         */
/*    Querying for various application constants.                          */
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

#ifndef __cpw_get_h__
#define __cpw_get_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*    Cpw Platform Identifiers                                           */
  /*                                                                       */
  enum CpwPlatformIdentifier
  {
      CPW_PLATFORM_WIN   = 1,
      CPW_PLATFORM_X11   = 2,
      CPW_PLATFORM_OSX   = 3,
  };
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*    Cpw Get Codes                                                      */
  /*                                                                       */
  enum CpwGetConstants 
  {
      CPW_INIT_WINDOW_X         = 1,
      CPW_INIT_WINDOW_Y         = 2,
      CPW_INIT_WINDOW_WIDTH     = 3,
      CPW_INIT_WINDOW_HEIGHT    = 4,
      CPW_INIT_DISPLAY_MODE     = 5,
      CPW_SCREEN_WIDTH          = 6, 
      CPW_SCREEN_HEIGHT         = 7,
      CPW_SCREEN_WIDTH_MM       = 8, /* for compat, returns 0 */
      CPW_SCREEN_HEIGHT_MM      = 9, /* for compat, returns 0 */
      CPW_WINDOW_X              = 10,/* for compat, use cpwWindowInfo */
      CPW_WINDOW_Y              = 11,/* for compat, use cpwWindowInfo */
      CPW_WINDOW_WIDTH          = 12,/* for compat, use cpwWindowInfo */
      CPW_WINDOW_HEIGHT         = 13,/* for compat, use cpwWindowInfo */
      CPW_WINDOW_FOREGROUND     = 14,/* returns id of the foreground window */
      CPW_WINDOW_GLCURRENT      = 15,/* returns id of the gl current window */
      CPW_WINDOW_COUNT          = 16,/* total number of open windows */
      CPW_MOUSE_BUTTONS         = 18,/* returns the number of mouse buttons (up to CPW_MAX_BUTTONS) */
      CPW_ELAPSED_TIME          = 19,/* for compat, returns 0 */
      CPW_DRIVER_VENDOR         = 20,/* 0 or null terminated string pointer */
      CPW_DRIVER_RENDERER       = 21,/* 0 or null terminated string pointer */
      CPW_DRIVER_VERSION        = 22,/* 0 or null terminated string pointer */
      CPW_VERSION               = 23,/* integer value */
      CPW_PLATFORM              = 24,/* see platform define constants above */
  };
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwGet                                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Returns application constants based on a specified parameter.       */
  /*                                                                       */
  CPW_API int_64 
  cpwGet( pCpw cpw, uint_32 param ); 
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
