/***************************************************************************/
/*                                                                         */
/*  cpw_state.h                                                            */
/*                                                                         */
/*    The Cpw library state context & library init and exit.               */
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

#ifndef __cpw_state_h__
#define __cpw_state_h__

#include "cpw_config.h"
#include "cpw_linkedlist.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    CpwPrintHandler                                                    */
  /*                                                                       */
  typedef void (*CpwPrintHandler) ( char * string );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwContext                                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The primary Cpw state structure.                                   */
  /*                                                                       */
  /*                                                                       */
  struct _CpwContext {
   
  /* general cpw environment values                                        */

  char*   cpw_programname;
  uint_32 cpw_displaymode;
  uint_32 cpw_screenheight;
  uint_32 cpw_screenwidth;
  bool    cpw_initsuccess;
  bool    cpw_running;

  /* cpwGet driver info string                                             */

  pStr cpw_driverinfo;

  /* print output handler                                                  */

  CpwPrintHandler cpw_print;

  /* cpw window init values                                                */

  uint_32 win_initwidth;    /* width */
  uint_32 win_initheight;   /* height */
  uint_32 win_initx;        /* desktop x position */
  uint_32 win_inity;        /* desktop y position */
  uint_32 win_currentid;    /* window with current context */
  uint_32 win_foregroundid; /* the current forground window id */
  uint_32 win_properties;   /* window style property flags */
  bool    win_expectmenu;   /* window is expected to hold a titlebar menu */

  /* keystate                                                              */

  bool keyboard_state[256];

  /* lists                                                                 */

  LinkedListData list_win;    /* window list */
  LinkedListData list_timers; /* timer list */
  LinkedListData list_perf;   /* performace mark list */
  LinkedListData list_menus;  /* master menu list */

  /* timers set?                                                           */

  bool timers;

  /* cpwMainLoop info                                                      */

  bool    mainloop_break;
  uint_32 mainloop_callbackticks;
  pVoid   mainloopCallback;

  /* system's idle callback                                                */

  pVoid  idleCallback;

  /* global window event callbacks                                         */

  pVoid  createCallback;
  pVoid  displayCallback;
  pVoid  reshapeCallback;
  pVoid  keyCallback;
  pVoid  skeyCallback;
  pVoid  mouseclickCallback;
  pVoid  mousedragCallback;
  pVoid  mousemoveCallback;
  pVoid  mouseentryCallback;
  pVoid  visibilityCallback;
  pVoid  positionCallback;

  /* cpw error state variables                                             */

  int_32 err_code;

  /* fps counter                                                           */

  float_64 fps_hpcount;
  float_64 fps_hpfreq;
  uint_32  fps_ticks;
  uint_32  fps_fps;

  /* listing extensions                                                    */

  pVoid extensions;

  /* event stack                                                           */

  pVoid stack;

  /* localhost context                                                     */

  pVoid ctx_localhost;

  /* font context                                                          */

  pVoid ctx_font; 

  /* primitives state                                                      */   

  pVoid ctx_primitives;

  /* joystick context                                                      */

  pVoid  ctx_joystick;

  /* global userdata                                                       */
  
  pVoid ctx_user;

  /* Add-on contexts                                                       */

  pVoid   ctx_ao_openal;  /* optional openal audio library extension */
  pVoid   ctx_ao_images;  /* optional image library extension */

  };
  typedef struct _CpwContext  CpwContext;
  typedef struct _CpwContext  Cpw;
  typedef struct _CpwContext* pCpw;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitContext                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*   cpwInitContext initializes the library and any add-ons you've       */
  /*   compiled into it. It must always be called before any other Cpw     */
  /*   call is made. pCpw * cpw is a pointer to a 'pCpw' context (which    */
  /*   is a pointer also). Init context allocates memory for the state,    */
  /*   so all you have to do is hand in a valid pointer to a pCpw which    */
  /*   will be used to store it.                                           */
  /*                                                                       */
  /*   Example use:                                                        */
  /*                                                                       */
  /*     pCpw cpw;                                                         */
  /*     cpwInitContext( &cpw );                                           */
  /*     ..                                                                */
  /*                                                                       */
  /*     (pCpw is a typecast to a CpwContext*)                             */
  /*                                                                       */
  /*     You can have multiple states if you want. All states must be      */
  /*     init'd and free'd by the user.                                    */
  /*                                                                       */
  /*     pCpw cpw1;                                                        */
  /*     pCpw cpw2;                                                        */
  /*                                                                       */
  /*     cpwInitContext( &cpw1 );                                          */
  /*     cpwInitContext( &cpw2 );                                          */
  /*                                                                       */
  /*     cpwDisplayCallback( cpw1, app1_displayCallback );                 */
  /*     cpwDisplayCallback( cpw2, app2_displayCallback );                 */
  /*                                                                       */
  /*     cpwCreateWindowEx( cpw1, "App1 Win1", 100, 100, 300, 300 );       */
  /*     cpwCreateWindowEx( cpw1, "App1 Win2", 120, 120, 300, 300 );       */
  /*     cpwCreateWindowEx( cpw2, "App2 Win1", 200, 200, 300, 300 );       */
  /*     cpwCreateWindowEx( cpw2, "App2 Win2", 220, 220, 300, 300 );       */
  /*                                                                       */
  CPW_API bool 
  cpwInitContext( pCpw * cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFreeContext                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*   cpwFreeContext shuts down the library for the context. Open         */
  /*   windows associated with the state will first receive a close        */
  /*   event and then will be destroyed. It is acceptable practive         */
  /*   to call cpwDestroyWindow on a window's close event. Any             */
  /*   resources associated with the window should be destroyed            */
  /*   before returning from a destroy event.                              */
  /*                                                                       */
  /*   After windows are destroyed, the rest of the library will be        */
  /*   shutdown, and all internal resources will be freed, include         */
  /*   the state memory itself. (pCpw will return as 0x000000 after        */
  /*   a call to cpwFreeContext.)                                          */
  /*                                                                       */
  /*   Example use:                                                        */
  /*                                                                       */
  /*     pCpw cpw;                                                         */
  /*     cpwInitContext( &cpw );                                           */
  /*     ..                                                                */
  /*     ..                                                                */
  /*     cpwFreeContext( &cpw );                                           */
  /*     exit();                                                           */
  /*                                                                       */
  CPW_API bool 
  cpwFreeContext( pCpw * cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetUserdata                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Sets the global user definable context.                            */
  /*                                                                       */
  CPW_API bool  
  cpwSetUserdata( pCpw cpw, 
                  pVoid userdata );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwGetUserdata                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Retrieves the global user definable context.                       */
  /*                                                                       */
  CPW_API pVoid 
  cpwGetUserdata( pCpw cpw );
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
