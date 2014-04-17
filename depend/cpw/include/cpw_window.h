/***************************************************************************/
/*                                                                         */
/*  cpw_window.h                                                           */
/*                                                                         */
/*    Window management and adapter event interface.                       */
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

#ifndef __cpw_window_h__
#define __cpw_window_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_callbacks.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwCursor                                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The default Cpw cursor identifiers. Custom is not supported yet.   */
  /*                                                                       */
  enum _CpwCursor
  {
    CursorArrow     = 1,
    CursorHand      = 2,
    CursorNo        = 3,
    CursorQuestion  = 4,
    CursorBeam      = 5,
    CursorWait      = 6,
    CursorCrosshair = 7,
    CursorNone      = 8,
    CursorSizeNSEW  = 9,
    CursorSizeNS    = 10,
    CursorSizeNeSw  = 11,
    CursorSizeEW    = 12,
    CursorSizeSeNw  = 13,
    CursorCustom    = 14 
  };
  typedef enum _CpwCursor CpwCursor;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwWindowInfo                                                      */
  /*                                                                       */
  struct _CpwWindowInfo
  {
    uint_32 id;
    uint_32 x;
    uint_32 y;
    uint_32 width;
    uint_32 height;
    bool    foreground;
    bool    fullscreen;
  };
  typedef struct _CpwWindowInfo  CpwWindowInfo;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwWindowList                                                      */
  /*                                                                       */
  #define CPW_MAX_WINLIST 30
  struct _CpwWindowList 
  {
    CpwWindowInfo list[CPW_MAX_WINLIST]; /* todo: make dynamic */
    uint_32 size;
  };
  typedef struct _CpwWindowList  CpwWindowList;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCreateWindow                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new window using the properties specified in the last    */
  /*    call to cpwInitWindowPosition and cpwInitWindowSize. Returns the   */
  /*    window's id used in subsequent calls.                              */
  /*                                                                       */
  /*    Window id's start at 1. By default, when the user closes the       */
  /*    window with this id value, cpwMainLoop returns. A window id of     */
  /*    0 can be passed to window management calls indicating the action   */
  /*    should effect the current foreground window, regardless of it's    */
  /*    id value.                                                          */
  /*                                                                       */
  CPW_API uint_32 
  cpwCreateWindow( pCpw cpw, 
                   char * title );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCreateWindowEx                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new window with the specified properties. Returns the    */
  /*    window's id used in subsequent calls.                              */
  /*                                                                       */
  CPW_API uint_32 
  cpwCreateWindowEx( pCpw cpw, 
                     char * title, 
                     uint_32 x, 
                     uint_32 y, 
                     uint_32 width, 
                     uint_32 height );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCreateFullscreenWindow                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new fullscreen window suitable for a game. Fullscreen    */
  /*    windows are just like any other Cpw window and receive all of the  */
  /*    same events.                                                       */
  /*                                                                       */
  /*    You can create as many fullscreen windows as you like. A           */
  /*    fullscreen window is simply a Cpw window a few minor changes       */
  /*    in the way it is created.                                          */
  /*                                                                       */
  /*       - Fullscreen windows will minimize automatically if they        */
  /*         loose focus.                                                  */
  /*                                                                       */
  /*       - Fullscreen windows have CursorNone as their default cursor.   */
  /*                                                                       */
  CPW_API uint_32 
  cpwCreateFullscreenWindow( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFullscreenWindow                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Converts an existing window to a fullscreen window. To create a    */
  /*    new fullscreen window use cpwCreateFullscreenWindow.               */
  /*                                                                       */
  /*       - Fullscreen windows will minimize automatically if they        */
  /*         loose focus.                                                  */
  /*                                                                       */
  CPW_API bool    
  cpwFullscreenWindow( pCpw cpw, 
                       uint_32 id );
  /*                                                                       */
  /*************************************************************************/

CPW_API bool cpwMaximizeWindow( pCpw cpw, uint_32 id );
CPW_API bool cpwStandardWindow( pCpw cpw, uint_32 id );

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDestroyWindow                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Destroy's an existing window and all of it's resources. This call  */
  /*    does not generate a destroy window event for the user's window     */
  /*    callback. It is excepted practive to call this function for a      */
  /*    when the destroy window event is received.                         */
  /*                                                                       */
  CPW_API bool
  cpwDestroyWindow( pCpw cpw, 
                    uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetWindowTitle                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Changes the title text of the window specified.                    */
  /*                                                                       */
  CPW_API bool    
  cpwSetWindowTitle( pCpw cpw, 
                     pChar title, 
                     uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPositionWindow                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Positions the window frame on the desktop. Origin is upper left.   */
  /*                                                                       */
  CPW_API bool    
  cpwPositionWindow( pCpw cpw, 
                     uint_32 x, 
                     uint_32 y, 
                     uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwReshapeWindow                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Reshapes (or resizes) the window specified. Parameters indicate    */
  /*    the window's client area.                                          */
  /*                                                                       */
  CPW_API bool    
  cpwReshapeWindow( pCpw cpw, 
                    uint_32 width, 
                    uint_32 height, 
                    uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwGetWindow                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Returns the id of the current foreground window.                   */
  /*                                                                       */
  CPW_API uint_32 
  cpwGetWindow( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetWindow                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Sets the gl rendering context for the specified window             */
  /*    current.                                                           */
  /*                                                                       */
  CPW_API bool    
  cpwSetWindow( pCpw cpw, 
                uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetForegroundWindow                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Moves the specified window to the foreground.                      */
  /*                                                                       */
  CPW_API bool    
  cpwSetForegroundWindow( pCpw cpw, 
                          uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPopWindow                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Places the current foreground window at the bottom of the window   */
  /*    z-order window stack.                                              */
  /*                                                                       */
  CPW_API bool    
  cpwPopWindow( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPushWindow                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Pushes the foreground window down one in the window z-order stack, */
  /*    replacing it with the window below.                                */
  /*                                                                       */
  CPW_API bool    
  cpwPushWindow( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwIconifyWindow                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Iconify the window.                                                */
  /*                                                                       */
  CPW_API bool    
  cpwIconifyWindow( pCpw cpw, 
                    uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwRestoreWindow                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Restores a hidden or iconified window to it's original position on */
  /*    the desktop.                                                       */
  /*                                                                       */
  CPW_API bool    
  cpwRestoreWindow( pCpw cpw, 
                    uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwHideWindow                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Completely hides a window.                                         */
  /*                                                                       */
  CPW_API bool    
  cpwHideWindow( pCpw cpw, 
                 uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwShowWindow                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Shows a currently hidden window.                                   */
  /*                                                                       */
  CPW_API bool    
  cpwShowWindow( pCpw cpw, 
                 uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPostRedisplay                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Iterates all windows, starting at window id 1, posting a redisplay */
  /*    message to each.                                                   */
  /*                                                                       */
  CPW_API bool    
  cpwPostRedisplay( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPostWindowRedisplay                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Posts a redisplay message to a single window.                      */
  /*                                                                       */
  CPW_API bool    
  cpwPostWindowRedisplay( pCpw cpw, 
                          uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSwapBuffers                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Iterates all windows, starting at window id 1, swapping any double */
  /*    buffered ones.                                                     */
  /*                                                                       */
  CPW_API bool    
  cpwSwapBuffers( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSwapWindowBuffers                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Swaps the buffers on a double buffered window.                     */
  /*                                                                       */
  CPW_API bool    
  cpwSwapWindowBuffers( pCpw cpw, 
                        uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetCursor                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Sets the cursor for a window which will be displayed any time the  */
  /*    the cursor is located within that window's client area.            */
  /*                                                                       */
  CPW_API bool    
  cpwSetCursor( pCpw cpw, 
                CpwCursor cursor, 
                uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPositionCursor                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Positions the cursor at the point specified within the window's    */
  /*    client area. This call will only take effect if the window is in   */
  /*    the foreground z-order position.                                   */
  /*                                                                       */
  CPW_API bool    
  cpwPositionCursor( pCpw cpw, 
                     uint_32 x, 
                     uint_32 y, 
                     uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCenterCursor                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Centers the cursor at the center point of the window's client      */
  /*    area. This call will only take effect if the window is in the      */
  /*    foreground z-order position.                                       */
  /*                                                                       */
  CPW_API bool    
  cpwCenterCursor( pCpw cpw, 
                   uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwListWindows                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Generates a list of CpwWindowInfo structures for all the current   */
  /*    windows. CpwWindowList contains a CpwWindowInfo structured list    */
  /*    and a size indicating the size of that list.                       */
  /*                                                                       */
  CPW_API bool    
  cpwListWindows( pCpw cpw, 
                  CpwWindowList * list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFreeWindowList                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Frees a previously allocated CpwWindowList structurte.             */
  /*                                                                       */
  CPW_API bool    
  cpwFreeWindowList( pCpw cpw, 
                     CpwWindowList * list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwGetWindowInfo                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Retrieves the properties for the window specified and places the   */
  /*    information in a user defined cpwGetWindowInfo strucuture.         */
  /*                                                                       */
  CPW_API bool    
  cpwGetWindowInfo( pCpw cpw, 
                    CpwWindowInfo * info, 
                    uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetWindowUserdata                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Sets a user definable context for the specified window.            */
  /*                                                                       */
  CPW_API bool  
  cpwSetWindowUserdata( pCpw cpw, 
                        pVoid userdata, 
                        uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwGetWindowUserdata                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Retrieves the user definable context for a window.                 */
  /*                                                                       */
  CPW_API pVoid 
  cpwGetWindowUserdata( pCpw cpw, 
                        uint_32 id );
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
  /*    CpwWindowStruct                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Hold all the information related to a Cpw window.                  */
  /*                                                                       */
  struct _CpwWindowStruct 
  {
    /* window user id */

    uint_32 id;

    /* window title */

    pStr title;

    /* current dimensions */

    uint_32 x;              /* window width in pixels */
    uint_32 y;              /* window height in pixels */
    uint_32 width;          /* window width in pixels */
    uint_32 height;         /* window height in pixels */

    /* backup dimensions */

    uint_32 bx;             /* window width in pixels */
    uint_32 by;             /* window height in pixels */
    uint_32 bwidth;         /* window width in pixels */
    uint_32 bheight;        /* window height in pixels */

    /* cursor type */
    
    CpwCursor cursor;
    bool      cursorpresent;

    /* fullscreen flag */

    bool fullscreen;

    /* menus */

    uint_32 menuid;
    uint_32 buttonmenuid[CPW_MAX_BUTTONS];

    /* localhost window context pointer */

    pVoid plhwc;

    /* window specific callbacks */

    CpwCreateCallback         createCallback;
    CpwDisplayCallback        displayCallback;
    CpwPositionCallback       positionCallback;
    CpwReshapeCallback        reshapeCallback;
    CpwKeyboardCallback       keyCallback;
    CpwSystemKeyboardCallback skeyCallback;
    CpwMouseClickCallback     mouseclickCallback;
    CpwMouseDragCallback      mousedragCallback;
    CpwMouseMoveCallback      mousemoveCallback;
    CpwMouseEntryCallback     mouseentryCallback;
    CpwVisibilityCallback     visibilityCallback;

    /* userdata context pointer */

    pVoid userdata;

  };
  typedef struct _CpwWindowStruct  CpwWindowStruct;
  typedef struct _CpwWindowStruct* pCpwWin;
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool    cpw_window_init( pCpw cpw );
  void    cpw_window_exit( pCpw cpw );

  void    cpw_window_close( pCpw cpw );
  uint_32 cpw_window_create( pCpw cpw, char* title, uint_32 x, uint_32 y, uint_32 width, uint_32 height );
  uint_32 cpw_window_createfullscreen( pCpw cpw );
  bool    cpw_window_fullscreen( pCpw cpw, uint_32 id );
  bool    cpw_window_closeall( pCpw cpw );
  bool    cpw_window_destroyall( pCpw cpw );
  bool    cpw_window_destroy( pCpw cpw, pCpwWin window );
  bool    cpw_window_makecurrent( pCpw cpw, uint_32 id );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
