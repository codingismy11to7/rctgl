/***************************************************************************/
/*                                                                         */
/*  cpw.h                                                                  */
/*                                                                         */
/*    The Cpw library main header file for applications.                   */
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

#ifndef __cpw_h__ /* __cpw_h__ */
#define __cpw_h__ /* __cpw_h__ */

#include "include/cpw_config.h"
#include "include/cpw_error.h"
#include CPW_OPENGL_H
#include CPW_GLU_H
#include CPW_GLAUX_H
#include CPW_INCLUDE_H

CPW_BEGIN_HEADER

/*************************************************************************/
/*                                                                       */
/*   Library State Management : see the cpw_state.h for more details.    */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwInitContext( pCpw * pcpw ); 
CPW_API bool  cpwFreeContext( pCpw * pcpw ); 

/*************************************************************************/
/*                                                                       */
/*   Global User State : see the cpw_state.h for more details.           */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwSetUserdata( pCpw cpw, pVoid userdata );
CPW_API pVoid cpwGetUserdata( pCpw cpw );

/*************************************************************************/
/*                                                                       */
/*   Error Manager : see cpw_error.h for more details                    */
/*                                                                       */
/*************************************************************************/

CPW_API int_32  cpwGetLastError( pCpw cpw );
CPW_API void    cpwSetLastError( pCpw cpw, int_32 errorCode );

/*************************************************************************/
/*                                                                       */
/*   Initialization : see cpw_init.h for more details                    */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwInitDisplayMode( pCpw cpw, uint_32 value );
CPW_API bool  cpwInitDisplayModeExact( pCpw cpw, uint_32 mode, uint_32 condition, int_32 value );
CPW_API bool  cpwInitWindowSize( pCpw cpw, uint_32 width, uint_32 height );
CPW_API bool  cpwInitWindowPosition( pCpw cpw, uint_32 xposition, uint_32 yposition );
CPW_API bool  cpwInitWindowProperty( pCpw cpw, uint_32 property, uint_32 paramone, uint_32 paramtwo );
CPW_API bool  cpwInitPrintHandler( pCpw cpw, CpwPrintHandler print );

/*************************************************************************/
/*                                                                       */
/*   Execution Manager : see cpw_main.h for more details                 */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwMainLoop( pCpw cpw );
CPW_API bool  cpwBreakMainLoop( pCpw cpw );
CPW_API bool  cpwMainLoopIsRunning( pCpw cpw );
CPW_API bool  cpwMainLoopUpdate( pCpw cpw, uint_32 ticks );
CPW_API bool  cpwIdleCallback( pCpw cpw, CpwIdleCallback idleCallback );
CPW_API bool  cpwMainLoopCallback( pCpw cpw, CpwMainLoopCallback mlCallback, uint_32 ticks );

/*************************************************************************/
/*                                                                       */
/*   Fullscreen Windows : see cpw_window.h for more details              */
/*                                                                       */
/*************************************************************************/

CPW_API uint_32 cpwCreateFullscreenWindow( pCpw cpw );

/*************************************************************************/
/*                                                                       */
/*   Normal Windows : see cpw_window.h for more details                  */
/*                                                                       */
/*************************************************************************/

CPW_API uint_32 cpwCreateWindow( pCpw cpw, pChar title );
CPW_API uint_32 cpwCreateWindowEx( pCpw cpw, pChar title, uint_32 x, uint_32 y, uint_32 width, uint_32 height );

/*************************************************************************/
/*                                                                       */
/*   Window Manager : see cpw_window.h for more details                  */
/*                                                                       */
/*************************************************************************/

CPW_API uint_32 cpwGetWindow( pCpw cpw );
CPW_API bool    cpwDestroyWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwSetWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwSetForegroundWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwSetWindowTitle( pCpw cpw, pChar string, uint_32 id );
CPW_API bool    cpwPositionWindow( pCpw cpw, uint_32 x, uint_32 y, uint_32 id );
CPW_API bool    cpwReshapeWindow( pCpw cpw, uint_32 width, uint_32 height, uint_32 id );
CPW_API bool    cpwFullscreenWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwStandardWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwPopWindow( pCpw cpw );
CPW_API bool    cpwPushWindow( pCpw cpw );
CPW_API bool    cpwIconifyWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwMaximizeWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwHideWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwRestoreWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwShowWindow( pCpw cpw, uint_32 id );
CPW_API bool    cpwPostRedisplay( pCpw cpw );
CPW_API bool    cpwPostWindowRedisplay( pCpw cpw, uint_32 id );
CPW_API bool    cpwSwapBuffers( pCpw cpw );
CPW_API bool    cpwSwapWindowBuffers( pCpw cpw, uint_32 id );
CPW_API bool    cpwListWindows( pCpw cpw, CpwWindowList * list );
CPW_API bool    cpwGetWindowInfo( pCpw cpw, CpwWindowInfo * info, uint_32 id );

/*************************************************************************/
/*                                                                       */
/*   Event Stack Manager : see cpw_event.h for more details              */
/*                                                                       */
/*************************************************************************/

CPW_API bool           cpwFilterEvent( pCpw cpw, CpwWindowEvent eventType, bool flag );
CPW_API CpwWindowEvent cpwNextEvent( pCpw cpw );
CPW_API CpwWindowEvent cpwNextWindowEvent( pCpw cpw, uint_32 id );
CPW_API bool           cpwClearEvent( pCpw cpw, CpwWindowEvent event ); 
CPW_API bool           cpwClearEvents( pCpw cpw );
CPW_API bool           cpwClearWindowEvent( pCpw cpw, CpwWindowEvent event, uint_32 id ); 
CPW_API bool           cpwClearWindowEvents( pCpw cpw, uint_32 id ); 
CPW_API bool           cpwPopEvent( pCpw cpw );
CPW_API int_32         cpwStackDepth( pCpw cpw );

/*************************************************************************/
/*                                                                       */
/*   User State Storage : see cpw_state.h, cpw_window.h for more details */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwSetUserdata( pCpw cpw, pVoid userdata );
CPW_API pVoid cpwGetUserdata( pCpw cpw );
CPW_API bool  cpwSetWindowUserdata( pCpw cpw, pVoid userdata, uint_32 id );
CPW_API pVoid cpwGetWindowUserdata( pCpw cpw, uint_32 id );

/*************************************************************************/
/*                                                                       */
/*   Window's Cursors : see cpw_window.h for more details                */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwSetCursor( pCpw cpw, CpwCursor cursor, uint_32 id );
CPW_API bool  cpwCenterCursor( pCpw cpw, uint_32 id );
CPW_API bool  cpwPositionCursor( pCpw cpw, uint_32 x, uint_32 y, uint_32 id );

/*************************************************************************/
/*                                                                       */
/*   Video Settings : see cpw_videosettings.h for more details           */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwChangeVideoMode( pCpw cpw, CpwVideoHints hints );
CPW_API bool  cpwResetVideoMode( pCpw cpw );
CPW_API bool  cpwListVideoModes( pCpw cpw, CpwVideoList * list );
CPW_API bool  cpwFreeVideoList( pCpw cpw, CpwVideoList * list );

/*************************************************************************/
/*                                                                       */
/*   Global Window Event Callbacks : see cpw_event.h for more details    */
/*                                                                       */
/*************************************************************************/

CPW_API bool cpwCreateCallback( pCpw cpw, CpwCreateCallback createCallback );
CPW_API bool cpwDisplayCallback( pCpw cpw, CpwDisplayCallback displayCallback );
CPW_API bool cpwReshapeCallback( pCpw cpw, CpwReshapeCallback reshapeCallback );
CPW_API bool cpwPositionCallback( pCpw cpw, CpwPositionCallback positionCallback );
CPW_API bool cpwKeyboardCallback( pCpw cpw, CpwKeyboardCallback keyCallback );
CPW_API bool cpwSystemKeyboardCallback( pCpw cpw, CpwSystemKeyboardCallback skeyCallback );
CPW_API bool cpwVisibilityCallback( pCpw cpw, CpwVisibilityCallback visibilityCallback );
CPW_API bool cpwMouseClickCallback( pCpw cpw, CpwMouseClickCallback mouseclickCallback );
CPW_API bool cpwMouseDragCallback( pCpw cpw, CpwMouseDragCallback mousedragCallback );
CPW_API bool cpwMouseMoveCallback( pCpw cpw, CpwMouseMoveCallback mousemoveCallback );
CPW_API bool cpwMouseEntryCallback( pCpw cpw, CpwMouseEntryCallback mouseentryCallback );

/*************************************************************************/
/*                                                                       */
/*   Specific Window Event Callbacks : see cpw_event.h for more details  */
/*                                                                       */
/*************************************************************************/

CPW_API bool cpwWindowCreateCallback( pCpw cpw, CpwCreateCallback createCallback, uint_32 id );
CPW_API bool cpwWindowDisplayCallback( pCpw cpw, CpwDisplayCallback displayCallback, uint_32 id );
CPW_API bool cpwWindowReshapeCallback( pCpw cpw, CpwReshapeCallback reshapeCallback, uint_32 id );
CPW_API bool cpwWindowPositionCallback( pCpw cpw, CpwPositionCallback positionCallback, uint_32 id );
CPW_API bool cpwWindowKeyboardCallback( pCpw cpw, CpwKeyboardCallback keyCallback, uint_32 id );
CPW_API bool cpwWindowSystemKeyboardCallback( pCpw cpw, CpwSystemKeyboardCallback skeyCallback, uint_32 id );
CPW_API bool cpwWindowVisibilityCallback( pCpw cpw, CpwVisibilityCallback visibilityCallback, uint_32 id );
CPW_API bool cpwWindowMouseClickCallback( pCpw cpw, CpwMouseClickCallback mouseclickCallback, uint_32 id );
CPW_API bool cpwWindowMouseDragCallback( pCpw cpw, CpwMouseDragCallback mousedragCallback, uint_32 id );
CPW_API bool cpwWindowMouseMoveCallback( pCpw cpw, CpwMouseMoveCallback mousemoveCallback, uint_32 id );
CPW_API bool cpwWindowMouseEntryCallback( pCpw cpw, CpwMouseEntryCallback mouseentryCallback, uint_32 id );

/*************************************************************************/
/*                                                                       */
/*   Keyboard & Mouse Info: see cpw_keymouse.h for more details          */
/*                                                                       */
/*************************************************************************/

CPW_API bool cpwMouseCapabilities( pCpw cpw, CpwMouseCapabilities * mcaps );
CPW_API bool cpwMouseState( pCpw cpw, CpwMouseInfo * info );
CPW_API bool cpwKeyState( pCpw cpw, CpwKeyConstant key );

/*************************************************************************/
/*                                                                       */
/*   Joysticks : see cpw_joystick.h for more details                     */
/*                                                                       */
/*************************************************************************/

CPW_API bool cpwInitJoysticks( pCpw cpw, CpwJoystickList * list );
CPW_API bool cpwJoystickPoll( pCpw cpw, CpwJoystickInfo * info );
CPW_API bool cpwJoystickCallback( pCpw cpw, CpwJoystickCallback joyCallback, uint_32 joyid, uint_32 delay );
CPW_API bool cpwJoystickPing( pCpw cpw, uint_32 joyid );

/*************************************************************************/
/*                                                                       */
/*   Timers : see cpw_timers.h for more details                          */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwTimerCallback( pCpw cpw, uint_32 milli, uint_32 id, bool recurring, CpwTimerCallback timerCallback );
CPW_API bool  cpwKillTimer( pCpw cpw, uint_32 id );

/*************************************************************************/
/*                                                                       */
/*   Images : see cpw_images.h for more details                          */
/*                                                                       */
/*************************************************************************/

CPW_API bool  cpwLoadImage( pCpw cpw, CpwImage * image, CpwImageType type, pChar filename, bool texturefit );
CPW_API bool  cpwSaveImage( pCpw cpw, CpwImage * image, pChar filename );
CPW_API bool  cpwFreeImage( pCpw cpw, CpwImage * image );
CPW_API bool  cpwScreenShot( pCpw cpw, CpwImage * image );
CPW_API bool  cpwResizeImage( pCpw cpw, CpwImage * image, uint_32 width, uint_32 height );
CPW_API bool  cpwTextureFit( pCpw cpw, CpwImage * image );

/*************************************************************************/
/*                                                                       */
/*   Font Rendering : see the cpw_font.h for more details.               */
/*                                                                       */
/*************************************************************************/

CPW_API int_32      cpwFontMode( pCpw cpw, int_32 mode, int_32 val );
CPW_API CpwFontFace cpwLoadFont( pCpw cpw, pChar fontname, uint_32 location, pChar fontpath, pChar cachelist );
CPW_API bool        cpwUnloadFont( pCpw cpw, CpwFontFace font );
CPW_API bool        cpwDrawFont( pCpw cpw, CpwFontFace font, pChar string, bool drawflag );
CPW_API bool        cpwDrawBufferedFont( pCpw cpw, CpwFontFace font, pChar string, CpwFontBuffer * buffer );
CPW_API bool        cpwFreeBufferedFont( pCpw cpw, CpwFontBuffer * buffer );
CPW_API bool        cpwGetFontBBox( pCpw cpw, CpwFontFace font, pChar string, CpwFontBBox * bbox );
CPW_API uint_32     cpwListFonts( pCpw cpw, CpwFontList * list, pChar searchtoken, uint_32 location );
CPW_API bool        cpwFreeFontList( pCpw cpw, CpwFontList* list );

/*************************************************************************/
/*                                                                       */
/*   Primitive Rendering : see cpw_primitive.h for more details.         */
/*                                                                       */
/*************************************************************************/

CPW_API bool cpwSetPrimitiveOpt( pCpw cpw, uint_32 option, float_32 value ); 
CPW_API bool cpwDrawPrimitive( pCpw cpw, uint_32 primitive ); 

/*************************************************************************/
/*                                                                       */
/*   GL Extension Support : see cpw_glextensions.h for more details.     */
/*                                                                       */
/*************************************************************************/

CPW_API pChar cpwIterateExtensions( pCpw cpw );
CPW_API bool  cpwIterateExtensionsReset( pCpw cpw );
CPW_API bool  cpwExtensionSupport( pCpw cpw, pChar string );

/*************************************************************************/
/*                                                                       */
/*   General State Information : see cpw_get.h for more details          */
/*                                                                       */
/*************************************************************************/

CPW_API int_64 cpwGet( pCpw cpw, uint_32 parameter );

/*************************************************************************/
/*                                                                       */
/*   Debug Performance Timing : see cpw_perfchecker.h for more details   */
/*                                                                       */
/*************************************************************************/

CPW_API uint_32 cpwAddMark( pCpw cpw, pChar name, bool average ); 
CPW_API bool    cpwEnterMark( pCpw cpw, uint_32 id );
CPW_API bool    cpwExitMark( pCpw cpw, uint_32 id );
CPW_API void    cpwDumpMarks( pCpw cpw );

/*************************************************************************/
/*                                                                       */
/*   Simple Frame Counter : see cpw_perfchecker.h for more details       */
/*                                                                       */
/*************************************************************************/

CPW_API void    cpwFpsInit( pCpw cpw );
CPW_API void    cpwFpsDraw( pCpw cpw, bool print );
CPW_API uint_32 cpwFpsGet( pCpw cpw );

/*************************************************************************/
/*                                                                       */
/*   Popup and Window Menus : see cpw_menus.h for more details           */
/*                                                                       */
/*************************************************************************/

CPW_API uint_32 cpwCreateMenu( pCpw cpw, CpwMenuCallback callback );
CPW_API uint_32 cpwCreateSubMenu( pCpw cpw );
CPW_API bool    cpwDestroyMenu( pCpw cpw, uint_32 menuid );

CPW_API bool    cpwAddMenuEntry( pCpw cpw, uint_32 menuid, pChar title, uint_32 entryid, bool checked );
CPW_API bool    cpwAddMenuSeperator( pCpw cpw, uint_32 menuid, uint_32 entryid );
CPW_API bool    cpwAddSubMenu( pCpw cpw, uint_32 menuid, pChar title, uint_32 submenuid, uint_32 entryid );
CPW_API bool    cpwEditMenuItem( pCpw cpw, uint_32 menu, uint_32 entryid, uint_32 newid, pChar newtitle, uint_32 newmenu );
CPW_API bool    cpwRemoveMenuItem( pCpw cpw, uint_32 menu, uint_32 entryid );

CPW_API bool    cpwAssignMenuToWindow( pCpw cpw, uint_32 menuid, uint_32 winid );
CPW_API bool    cpwUnassignMenu( pCpw cpw, uint_32 winid );
CPW_API bool    cpwAttachMenuToButton( pCpw cpw, uint_32 menuid, uint_32 button, uint_32 winid );
CPW_API bool    cpwDetachMenu( pCpw cpw, uint_32 button, uint_32 winid );

CPW_API bool    cpwCheckMenuEntry( pCpw cpw, uint_32 menuid, uint_32 entryid );
CPW_API bool    cpwUncheckMenuEntry( pCpw cpw, uint_32 menuid, uint_32 entryid );
CPW_API bool    cpwMenuEntryChecked( pCpw cpw, uint_32 menuid, uint_32 entryid );

CPW_END_HEADER

#endif

/*********************************************************************************
/*                                                                               *
/*  Cpw or "Cross-platform Windowing for OpenGL" is an adaptation of Mark        *
/*  Kilgard's GLUT library version 3.7. This library is true free software,      *
/*  use is granted with only minor restrictions. Please send any bug             *
/*  fixes, additional ports, and feedback to the cpw mailinglist address below.  *
/*  The GLUT 3.7 library was used as a framework in developing this code.        *
/*  Because of this I would like to graciously thank Mark Kilgard for his        *
/*  hard work on the GLUT library.                                               *
/*                                                                               *
/*  Other developers have had an important role in the development of this       *
/*  library. Please note the developer credits on the Cpw web site. If you       *
/*  use this library, please mention these developers on your web site or        *
/*  in your documentation.                                                       *
/*                                                                               *
/*  Cpw web site: (for now) http://www.mathies.com/cpw/                          *
/*  Cpw mailing list: (for now) cpw@mathies.com                                  *
/*  license: The "Lua License" (see below)                                       *
/*                                                                               *
/*  This Cpw Version: Beta 1.0                                                   *
/*                                                                               *
/*********************************************************************************/

/*********************************************************************************
/*                                                                               *
/* Cpw is Copyright 2001-2002 by                                                 *
/*   Jim Mathies,                                                                *
/*   All rights reserved.                                                        *
/*                                                                               *
/* Permission is hereby granted, without written agreement and without license   *
/* or royalty fees, to use, copy, modify, and distribute this software and it's  *
/* documentation for any purpose, including commercial applications, subject to  *
/* the following conditions:                                                     *
/*                                                                               *
/*  - The above copyright notice and this permission notice shall appear in all  *
/*    copies or substantial portions of the software's source code.              *
/*                                                                               *
/*  - The origin of this software must not be misrepresented; you must not       *
/*    claim that you wrote the original software. If you use this software in a  *
/*    product, an acknowledgment in the product documentation would be greatly   *
/*    appreciated (but it is not required).                                      *
/*                                                                               *
/*  - Altered source versions must be plainly marked as such, and must not be    *
/*    misrepresented as being the original software.                             *
/*                                                                               *
/* The authors specifically disclaim any warranties, including, but not limited  *
/* to, the implied warranties of merchantability and fitness for a particular    *
/* purpose.  The software provided hereunder is on an "as is" basis, and the     *
/* authors have no obligation to provide maintenance, support, updates,          *
/* enhancements, or modifications.  In no event shall the authors                *
/* be held liable to any party for direct, indirect, special, incidental, or     *
/* consequential damages arising out of the use of this software and its         *
/* documentation.                                                                *
/*                                                                               *
/*********************************************************************************/
