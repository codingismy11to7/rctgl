/***************************************************************************/
/*                                                                         */
/*  cpw_videosettings.h                                                    */
/*                                                                         */
/*    Setting video resolution of the desktop.                             */
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

#ifndef __cpw_videosettings_h__
#define __cpw_videosettings_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwVideoHints                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Video resolution hints structure used to describe a desktop        */
  /*    resolution and color depth.                                        */
  /*                                                                       */
  struct _CpwVideoHints 
  {
    uint_16 width;
    uint_16 height;
    uint_16 depth;
    bool    active;
  };
  typedef struct _CpwVideoHints CpwVideoHints;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwVideoList                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A list of CpwVideoHints describing the hosts's video capabilities. */
  /*                                                                       */
  #define MAX_VLIST 300
  struct _CpwVideoList 
  {
    CpwVideoHints * list[MAX_VLIST];
    uint_32         size;
  };
  typedef struct _CpwVideoList CpwVideoList;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwListVideoModes                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    List the various video modes this host's video adapter supports.   */
  /*    Pass in a pointer to a valid CpwVideoList.                         */
  /*                                                                       */
  CPW_API bool 
  cpwListVideoModes( pCpw cpw, 
                     CpwVideoList * list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwListVideoModes                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Frees resources stored within a video list.                        */
  /*                                                                       */
  CPW_API bool 
  cpwFreeVideoList( pCpw cpw, 
                    CpwVideoList * list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwChangeVideoMode                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Changes the current video settings based on a set of hints. To     */
  /*    insure the call is successful, call cpwListVideoModes first, which */
  /*    returns a list of video mode hints you can select from and use in  */
  /*    this call.                                                         */
  /*                                                                       */
  CPW_API bool 
  cpwChangeVideoMode( pCpw cpw, 
                      CpwVideoHints hints );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwResetVideoMode                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    If the video mode has been changed, reset it back to the default   */
  /*    (starting) mode. This call is automatically called when Cpw exits. */
  /*                                                                       */
  CPW_API bool 
  cpwResetVideoMode( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  bool cpw_videosettings_init( pCpw cpw );
  void cpw_videosettings_exit( pCpw cpw );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
