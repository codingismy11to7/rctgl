/***************************************************************************/
/*                                                                         */
/*  cpw_config.h                                                           */
/*                                                                         */
/*    Build macros for the Cpw library. This is the primary platform and   */
/*    host configuration file for Cpw.                                     */
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
/*  File Platform: mixed (the only one)                                    */
/*                                                                         */
/***************************************************************************/

#ifndef __cpw_config_h__
#define __cpw_config_h__

  /*************************************************************************/
  /*                                                                       */
  /* <Macro>                                                               */
  /*    CPW_BEGIN_HEADER                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    This macro is used in association with @CPW_END_HEADER in header   */
  /*    files to ensure that the declarations within are properly          */
  /*    encapsulated in an `extern "C" { .. }' block when included from a  */
  /*    C++ compiler.                                                      */
  /*                                                                       */
  /*************************************************************************/

#ifdef __cplusplus
#define CPW_BEGIN_HEADER  extern "C" {
#else
#define CPW_BEGIN_HEADER  /* nothing */
#endif

  /*************************************************************************/
  /*                                                                       */
  /* <Macro>                                                               */
  /*    CPW_END_HEADER                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    This macro is used in association with @CPW_BEGIN_HEADER in header */
  /*    files to ensure that the declarations within are properly          */
  /*    encapsulated in an `extern "C" { .. }' block when included from a  */
  /*    C++ compiler.                                                      */
  /*                                                                       */
  /*************************************************************************/

#ifdef __cplusplus
#define CPW_END_HEADER  }
#else
#define CPW_END_HEADER  /* nothing */
#endif

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Include Macro>                                                       */
  /*    CPW_INCLUDE_H                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Flips between Cpw internal library build includes and external     */
  /*    application build includes.                                        */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN
#define CPW_INCLUDE_H 
#else
#define CPW_INCLUDE_H "include/cpw_extern.h"
#endif

  /*************************************************************************/
  /*                                                                       */
  /* <Define>                                                              */
  /*    CpwVersion                                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The version of this library.                                       */
  /*                                                                       */
  /*************************************************************************/

  #define CpwVersion 1.0

  /*************************************************************************/
  /*                                                                       */
  /* <Compile Switch>                                                      */
  /*    CPW_COMPILEOPT_SINGLESTATE                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Cpw is a multi-state library. This means you can create any number */
  /*    of Cpw contexts which get passed into each API call. For           */
  /*    non-embedded applications, this may be overkill. The single and    */
  /*    multistate compile options switch between the multi-state api      */
  /*    and a simple single-state api which does not require the passing   */
  /*    of a pCpw context into api calls. For a replacement, a single Cpw  */
  /*    global context is statically defined in cpw_state.h and is used    */
  /*    internally. Use this option if you are compiling a stand-alone     */
  /*    application which only requires a single state, or if you are      */
  /*    porting an existing GLUT application to Cpw.                       */
  /*                                                                       */
  /*    Currently NOT implemented.                                         */
  /*                                                                       */
  /*************************************************************************/

  /* #define CPW_COMPILEOPT_SINGLESTATE */

  #ifdef CPW_COMPILEOPT_SINGLESTATE
    #define pCpwCtx
    #define pCpwCtxc
    #define ppCpwCtx
  #else
    #define pCpwCtx  pCpw cpw
    #define pCpwCtxc pCpw cpw,
    #define ppCpwCtx pCpw * cpw
  #endif 

  /*************************************************************************/
  /*                                                                       */
  /* <Compile Switch>                                                      */
  /*    CPW_COMPILEOPT_WINDOWSPECIFICEVENTS                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Cpw supports both GLUT-like global window event handlers and       */
  /*    window specific event handlers which override their global         */
  /*    counterparts. Window specific event processing requires an         */
  /*    additional window id lookup when processing an event. If your      */
  /*    porting a GLUT application to Cpw or if your application does      */
  /*    not make use of any window specific events, comment out this       */
  /*    compile option which removes the additional id lookup and window   */
  /*    specific event code. (which increases event processing             */
  /*    performance.)                                                      */
  /*                                                                       */
  /*    Define CPW_COMPILEOPT_WINDOWSPECIFICEVENTS to enable window        */
  /*    specific events.                                                   */
  /*                                                                       */
  /*************************************************************************/

#define CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

  /*************************************************************************/
  /*                                                                       */
  /* <Compile Switch>                                                      */
  /*    CPW_COMPILEOPT_CURRENTCONTEXTCACHING                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Are you a total speed freak? If so, and if your only using a       */
  /*    single Cpw state in your application, define this compile option   */
  /*    to turn on current rendering context id caching.                   */
  /*                                                                       */
  /*    Defining this option causes Cpw to cache the last window id that   */
  /*    was set current, and shunts repeated calls to the localhost        */
  /*    adapter's setcurrentcontext if the context is already current.     */
  /*    In single window games or applications which do not use multiple   */
  /*    Cpw states, this can result in increased rendering performance.    */
  /*                                                                       */
  /*    In single threaded applications which use multiple states, you     */
  /*    can't use current context id caching because one Cpw state does    */
  /*    not know about the other state's actions on the current rendering  */
  /*    context. Context caching will work for applications which have     */     
  /*    a unique state per multiple threads.                               */
  /*                                                                       */
  /*    Define CPW_COMPILEOPT_CURRENTCONTEXTCACHING to enable current      */
  /*    context id caching.                                                */
  /*                                                                       */
  /*************************************************************************/

#define CPW_COMPILEOPT_CURRENTCONTEXTCACHING

  /*************************************************************************/
  /*                                                                       */
  /* <Compile Switch>                                                      */
  /*    CPW_COMPILEOPT_SHUTDOWNONFIRSTWINDOW                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    This compile options when defined causes Cpw to shutdown (calls    */
  /*    cpwBreakMainLoop internally) automatically when the first window   */
  /*    that gets created (window id=1) is closed. Without this option     */
  /*    defined Cpw's cpwMainLoop will run when there are no windows       */
  /*    created and also after the first window created is closed.         */ 
  /*                                                                       */
  /*    Define CPW_COMPILEOPT_SHUTDOWNONFIRSTWINDOW to enable shutdown     */
  /*    when the first window closes.                                      */
  /*                                                                       */
  /*************************************************************************/

#define CPW_COMPILEOPT_SHUTDOWNONFIRSTWINDOW

  /*************************************************************************/
  /*                                                                       */
  /* <Limits Define>                                                       */
  /*    CPW_MENUS_MAXENTRIES                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The maximum number of entries per menu. The number of menu's is    */
  /*    not capped but entries are for simplicity.                         */
  /*                                                                       */
  /*************************************************************************/

#define CPW_MENUS_MAXENTRIES 300

  /*************************************************************************/
  /*                                                                       */
  /* <Section>                                                             */
  /*    Platform specifc definitions                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    This section defines macros and standardized types for the Cpw     */
  /*    library. Each platform this library is ported to must have an      */
  /*    entry in this section.                                             */
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   Win32 specific configurations.                                      */
  /*                                                                       */
  /*************************************************************************/

#ifdef WIN32

    /****************************************************/
    /*  this platform identifier                        */
    /****************************************************/

    #define CPW_THIS_PLATFORM   CPW_PLATFORM_WIN

    /****************************************************/
    /*  standard include(s) for this platform           */
    /****************************************************/

    #include <windows.h>
    #include <stdio.h>

    /****************************************************/
    /*  platform specific adapter include file          */
    /****************************************************/

    #define CPW_LOCALHOST_H  "../win32/cpw_win32.h"

    /****************************************************/
    /*  platform's OpenGL header includes               */
    /****************************************************/

    #define CPW_OPENGL_H  <gl/gl.h>

    #define CPW_GLAUX_H  <gl/glaux.h>

    /****************************************************/
    /*  platform's GLU header includes                  */
    /****************************************************/

    #define CPW_GLU_H  <gl/glu.h>

    /****************************************************/
    /*  auto link WIN32's OpenGL library's. change this */
    /*  if your using an alternate library.             */
    /****************************************************/

    #pragma comment (lib, "opengl32.lib")
    #pragma comment (lib, "glu32.lib")

    /****************************************************/
    /*  auto link to freetype                           */
    /****************************************************/

    #if defined(CPWDLL_EXPORTS)
      #if defined(_DEBUG)
      #pragma comment (lib, "freetype206MT_D.lib" )
      #else
      #pragma comment (lib, "freetype206MT.lib" )
      #endif
    #endif

    #if defined(CPW_EXTERN) 
      #pragma comment (lib, "CpwLib.lib" )
      #pragma comment (lib, "freetype206MT.lib" )
    #endif

    #if defined(CPWDLL_EXTERN) 
      #pragma comment (lib, "CpwDLL.lib" )
    #endif

    #if defined(CPWDLLDBG_EXTERN) 
      #pragma comment (lib, "CpwDLL_dbg.lib" )
    #endif

    #if defined(CPWEXTDLL_EXTERN) 
      #pragma comment (lib, "CpwExtDLL.lib" )
    #endif

    /****************************************************/
    /*  external API exporting macro                    */
    /****************************************************/
    
    #ifdef _LIB
    #define CPW_API  extern /* building the static lib */
    #elif CPWDLL_EXPORTS    /* building the dll */
    #define CPW_API __declspec(dllexport)
    #else
    #define CPW_API /* nothing */
    #endif

    /****************************************************/
    /*  platform's inline function declaration          */
    /****************************************************/
       
    #define CPW_INLINE  __inline

    /****************************************************/
    /*  platform's type definitions                     */
    /****************************************************/

    #ifndef bool
    #define bool      BOOL
    #endif

    #ifndef false
    #define false     FALSE
    #endif

    #ifndef true
    #define true      TRUE
    #endif

    #ifndef null
    #define null      NULL
    #endif

    #define pVoid     void*
    #define pChar     char*
    #define uint_8    unsigned __int8
    #define uint_16   unsigned __int16
    #define uint_32   unsigned __int32
    #define int_16    __int16
    #define int_32    __int32
    #define int_64    __int64
    #define float_32  float
    #define float_64  double
    #define long_32   LONG32

    /****************************************************/
    /*  memory allocators - override to suit you needs  */
    /****************************************************/

    #define cpwmalloc         malloc
    #define cpwrealloc        realloc
    #define cpwfree           free

    /*************************************************************************/
    /*                                                                       */
    /* <Include Macro>                                                       */
    /*    FreeType Font Library include header location.                     */
    /*                                                                       */
    /* <Description>                                                         */
    /*    Points to your local FreeType include headers directory.           */
    /*                                                                       */
    /*    Chances are you need to change this to compile Cpw on your box.    */
    /*    The Win32 VC 6.0 projects have an include search path in them that */
    /*    is specific to my box: '../../../freetype-2.0.6/include' which     */
    /*    assumes the FreeType project sits in the same root as the Cpw      */
    /*    project directory and is FreeType version 2.0.6.                   */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_FREETYPE_H "freetype/freetype.h"

    /*************************************************************************/
    /*                                                                       */
    /* <Limits Define>                                                       */
    /*    CPW_MAX_BUTTONS                                                    */
    /*                                                                       */
    /* <Description>                                                         */
    /*    The maximum number of buttons on a mouse.                          */
    /*    For Win32, we have 2 standard plus the wheel/middle button.        */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_MAX_BUTTONS 3

    /*************************************************************************/
    /*                                                                       */
    /* <Define>                                                              */
    /*    CPW_LOCALHOST_DIRDIV                                               */
    /*                                                                       */
    /* <Description>                                                         */
    /*    The directory dividing character. Used in cpw_fonts.c              */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_LOCALHOST_DIRDIV  "\\"

    /*************************************************************************/
    /*                                                                       */
    /* <Compile Switch>                                                      */
    /*    CPW_DIRECTINPUT_JOYSTICKACCESS                                     */
    /*                                                                       */
    /* <Description>                                                         */
    /*    Direct input joystick or windows base services joystick access.    */
    /*    Comment this out if you always want to use winbase access. Note    */
    /*    Cpw will fall through to winbase joystick access if the required   */
    /*    di interfaces are not available on the host running the Cpw app.   */
    /*    See the win32 adapter for more information. Only comment this out  */
    /*    if you specifically want winbase or if you don't have the di sdk   */
    /*    installed on your development machine.                             */
    /*                                                                       */
    /*    Commenting this out removes di joystick code, saving space.        */
    /*                                                                       */
    /*************************************************************************/

    /* #define CPW_DIRECTINPUT_JOYSTICKACCESS */

    /*************************************************************************/
    /*                                                                       */
    /* <Compile Switch>                                                      */
    /*    CPW_DIRECTINPUT_MOUSEACCESS                                        */
    /*                                                                       */
    /* <Description>                                                         */
    /*    Direct input mouse access. This is primarily for game programmers. */
    /*    Mouse input with directinput has no mouse cursors! So don't use    */
    /*    this unless your writing a full screen game or app that doesn't    */
    /*    need the mouse cursor to display. (you could draw your own cursor  */
    /*    if you wanted to I suppose) Also note, di mouse access must be     */
    /*    associated with a window. The di interface is initialized the      */
    /*    first time cpwMouseState is called. (Event callbacks are not       */
    /*    supported - it is assumed your going for speed and as such,        */
    /*    would not use a callback mechanism for mouse input.) Make sure     */
    /*    your window is created and in the foreground before calling        */
    /*    cpwMouseState for the first time.                                  */
    /*                                                                       */
    /*    For mouse access you must compile with and your clients must       */
    /*    have DirectInput 3 or greater.                                     */
    /*                                                                       */
    /*    Commenting this out removes di mouse code, saving space.           */
    /*                                                                       */
    /*************************************************************************/

    /* #define CPW_DIRECTINPUT_MOUSEACCESS */

    /*************************************************************************/
    /*                                                                       */
    /* <Compile Switch>                                                      */
    /*    CPW_DIRECTINPUT_KEYBOARDACCESS                                     */
    /*                                                                       */
    /* <Description>                                                         */
    /*    Direct input keyboard access. Is there a need? I've found Cpw's    */
    /*    keyboard event callbacks more than adequate, even for game         */
    /*    programming. There just isn't that much data / cpu time associated */
    /*    with a key presses. They are 'low bandwidth'.                      */
    /*                                                                       */
    /*    * Currently NOT implemented *                                      */
    /*                                                                       */
    /*    Commenting this out removes di keyboard code, saving space.        */
    /*                                                                       */
    /*************************************************************************/

    /* #define CPW_DIRECTINPUT_KEYBOARDACCESS */

    /*************************************************************************/
    /*                                                                       */
    /* <MS Compile Switch>                                                   */
    /*    DIRECTINPUT_VERSION                                                */
    /*                                                                       */
    /* <Description>                                                         */
    /*    Direct input version to use. If you are using winbase for input    */
    /*    this value has no signifigance. DirectInput must have this defined */
    /*    or it will default to the current version of the sdk you have      */
    /*    installed. You should use to the lowest possible version so users  */
    /*    Don't have to install the latest runtime to run your game. To get  */
    /*    the latest runtime on your client's machine you can optionally     */
    /*    include the di runtime installer that comes with the disdk.        */
    /*                                                                       */
    /*    For joystick access you must compile with and your clients must    */
    /*    have DirectInput 5 or greater.                                     */
    /*                                                                       */
    /*************************************************************************/

    #define DIRECTINPUT_VERSION 0x0500
    /* #define DIRECTINPUT_VERSION 0x0700 */
    /* #define DIRECTINPUT_VERSION 0x0800 */

    /*************************************************************************/
    /*                                                                       */
    /* <Compile Switch>                                                      */
    /*    CPW_PLATFORMINFO_LITTLEENDIAN                                      */
    /*                                                                       */
    /* <Description>                                                         */
    /*    This platform is little endian. Do not define this if your         */
    /*    compiling on a big endian (MAC hardware for example) machine.      */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_PLATFORMINFO_LITTLEENDIAN

#endif

  /*************************************************************************/
  /*                                                                       */
  /*   SunOS specific configurations.                                      */
  /*                                                                       */
  /*************************************************************************/

#ifdef __SunOS__
#endif

  /*************************************************************************/
  /*                                                                       */
  /*   CygWin specific configurations.                                     */
  /*                                                                       */
  /*************************************************************************/

#ifdef CygWin

    /****************************************************/
    /*  this platform identifier                        */
    /****************************************************/

    #define CPW_THIS_PLATFORM   CPW_PLATFORM_WIN

    /****************************************************/
    /*  standard include(s) for this platform           */
    /****************************************************/

    #include <windows.h>
    #include <winuser.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include <float.h>
    #include <stdio.h>

    /****************************************************/
    /*  platform specific adapter include file          */
    /****************************************************/

    #define CPW_LOCALHOST_H  "../win32/cpw_win32.h"

    /****************************************************/
    /*  platform's OpenGL header includes               */
    /****************************************************/

    #define CPW_OPENGL_H  <GL/gl.h>

    /****************************************************/
    /*  platform's GLU header includes                  */
    /****************************************************/

    #define CPW_GLU_H  <GL/glu.h>

    /****************************************************/
    /*  auto link WIN32's OpenGL library's. change this */
    /*  if your using an alternate library.             */
    /****************************************************/

    /****************************************************/
    /*  auto link Cpw and freetype                      */
    /****************************************************/

    /****************************************************/
    /*  external API exporting macro                    */
    /****************************************************/
    
    #define CPW_API  extern /* building the static lib */

    /****************************************************/
    /*  platform's inline function declaration          */
    /****************************************************/
       
    #define CPW_INLINE  inline

    /****************************************************/
    /*  platform's type definitions                     */
    /****************************************************/

    #ifndef bool
    #define bool      BOOL
    #endif

    #ifndef false
    #define false     FALSE
    #endif

    #ifndef true
    #define true      TRUE
    #endif

    #ifndef null
    #define null      NULL
    #endif

    #define pVoid     void*
    #define pChar     char*
    #define uint_8    unsigned char
    #define uint_16   unsigned short
    #define uint_32   unsigned int
    #define int_16    short
    #define int_32    int
    #define int_64    int
    #define float_32  float
    #define float_64  double
    #define long_32   long

    /****************************************************/
    /*  memory allocators - override to suit you needs  */
    /****************************************************/

    #define cpwmalloc         malloc
    #define cpwrealloc        realloc
    #define cpwfree           free

    /*************************************************************************/
    /*                                                                       */
    /* <Limits Define>                                                       */
    /*    CPW_MAX_BUTTONS                                                    */
    /*                                                                       */
    /* <Description>                                                         */
    /*    The maximum number of buttons on a mouse.                          */
    /*    For Win32, we have 2 standard plus the wheel/middle button.        */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_MAX_BUTTONS 3

    /*************************************************************************/
    /*                                                                       */
    /* <Define>                                                              */
    /*    CPW_LOCALHOST_DIRDIV                                               */
    /*                                                                       */
    /* <Description>                                                         */
    /*    The directory dividing character. Used in cpw_fonts.c              */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_LOCALHOST_DIRDIV  "\\"

    /*************************************************************************/
    /*                                                                       */
    /* <Include Macro>                                                       */
    /*    Freetype Font rendering library include header location.           */
    /*                                                                       */
    /* <Description>                                                         */
    /*    Points to your local freetype include header.                      */
    /*    Chances are you need to edit this.                                 */
    /*                                                                       */
    /*************************************************************************/

    #define CPW_FREETYPE_H "/cygdrive/f/Projects/freetype-2.0.6/include/freetype/freetype.h"
    /*#define CPW_FREETYPE_H "/d/freetype-2.0.6/include/freetype/freetype.h"*/

#endif

  /*************************************************************************/
  /*                                                                       */
  /*   OSX specific configurations.                                        */
  /*                                                                       */
  /*************************************************************************/

#ifdef OSX
#endif

  /*************************************************************************/
  /*                                                                       */
  /*   Linux specific configurations.                                      */
  /*                                                                       */
  /*************************************************************************/

#ifdef X11
#endif

  /*************************************************************************/
  /*                                                                       */
  /* <Section>                                                             */
  /*    Configuration cross checks.                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Confirm configuration has been set correctly.                      */
  /*                                                                       */
  /*************************************************************************/

#if defined(CPW_INTERN)
#elif defined(CPW_EXTERN)
#elif defined(CPWDLL_EXTERN)
#elif defined(CPWEXTDLL_EXTERN)
#elif defined(CPWDLLDBG_EXTERN)
#else
#error your compile isnt configured correctly. (CPW_EXTERN, CPWDLL_EXTERN or CPW_INTERN)
#endif

#if !defined(CPW_OPENGL_H) | !defined(CPW_GLU_H)
#error cpw_config.h isnt configured correctly. (gl headers)
#endif

#if !defined(CPW_API) | !defined(CPW_INLINE)
#error cpw_config.h isnt configured correctly. (inline or api)
#endif

#if !defined(CPW_LOCALHOST_H)
#error cpw_config.h isnt configured correctly. (localhost)
#endif

#if !defined(CPW_FREETYPE_H)
#error cpw_config.h isnt configured correctly. (freetype)
#endif

#if !defined(bool) | !defined(true) | !defined(false) | !defined(null) | !defined(pVoid) | !defined(pChar) | !defined(uint_8) | !defined(uint_16) | !defined(uint_32) | !defined(int_32) | !defined(int_64) | !defined(float_32) | !defined(float_64) | !defined(long_32)
#error cpw_config.h isnt configured correctly. (types)
#endif

#if !defined(cpwmalloc) | !defined(cpwrealloc) | !defined(cpwfree)
#error cpw_config.h isnt configured correctly. (memory allocation handlers)
#endif

#if !defined(CPW_MENUS_MAXENTRIES)
#error cpw_config.h isnt configured correctly. (menuentries max)
#endif

#if !defined(CPW_MAX_BUTTONS)
#error cpw_config.h isnt configured correctly. (mouse buttons max)
#endif

#if !defined(CPW_LOCALHOST_DIRDIV)
#error cpw_config.h isnt configured correctly. (directory divider)
#endif

CPW_END_HEADER
#endif
