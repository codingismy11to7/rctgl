/***************************************************************************/
/*                                                                         */
/*  cpw_main.h                                                             */
/*                                                                         */
/*    Cpw main render loop interface and control.                          */
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

#ifndef __cpw_main_h__
#define __cpw_main_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    CpwIdleCallback,CpwMainLoopCallback                                */
  /*                                                                       */
  typedef void (*CpwIdleCallback)     ( pCpw cpw );
  typedef void (*CpwMainLoopCallback) ( pCpw cpw, bool eventsPending );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwIdleCallback                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*   the cpwIdleCallback is called when cpwMainLoop would normally       */
  /*   call sleep due to having nothing else to do.  If this is not        */
  /*   cpwMainLoop will call sleep( 1 milli ) instead.                     */
  /*                                                                       */
  CPW_API bool 
  cpwIdleCallback( pCpw cpw, 
                   CpwIdleCallback idleCallback );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwMainLoop                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*   cpwMainLoop is the main window and events manager execution         */
  /*   loop. It executes as long as the base window (id=1) exists          */
  /*   on the screen or until the localhost os requests the application    */
  /*   to shut down. Returns a bool indicating if there was an error       */
  /*   during init, or during event processing.                            */
  /*                                                                       */
  CPW_API bool 
  cpwMainLoop( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwBreakMainLoop                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*   cpwBreakMainLoop breaks cpwMainLoop execution causing cpwMainLoop   */
  /*   to return. You may re-enter cpwMainLoop after breaking it. Note,    */
  /*   Window events will not be processed if cpwMainLoop is not running   */
  /*   or if cpwMainLoopUpdate is not being polled (see below).            */
  /*                                                                       */
  CPW_API bool 
  cpwBreakMainLoop( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwMainLoopIsRunning                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Returns a bool flag indicating if there is a thread executing       */
  /*   in cpwMainLoop.                                                     */   
  /*                                                                       */
  CPW_API bool 
  cpwMainLoopIsRunning( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/


  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwMainLoopUpdate                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Alternate form of cpwMainLoop which only executes mainloop          */
  /*   functionality for a number of ticks before returning.               */
  /*   The cpwMainLoopCallback and cpwIdleCallback are not called during   */
  /*   cpwMainLoopUpdate.                                                  */
  /*                                                                       */
  CPW_API bool  
  cpwMainLoopUpdate( pCpw cpw, uint_32 ticks );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwMainLoopCallback                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*   cpwMainLoopCallback sets the main loop callback. The callback       */
  /*   is called on every 'ticks' iteration of Cpw's main execution loop.  */
  /*   Use this for doing light tasks like polling of joysticks.           */
  /*   The eventsPending flag tells the application if cpwMainLoop has     */
  /*   events it needs to process on the next loop around. You should      */
  /*   'ease up' on processing in the callback if this flag is set true.   */
  /*   The callback is called at the bottom of cpwMainLoop.                */
  /*                                                                       */
  CPW_API bool 
  cpwMainLoopCallback( pCpw cpw, 
                       CpwMainLoopCallback mlCallback, 
                       uint_32 ticks );
  /*                                                                       */
  /*************************************************************************/

CPW_END_HEADER

#endif
