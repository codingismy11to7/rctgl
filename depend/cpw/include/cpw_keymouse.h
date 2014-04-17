/***************************************************************************/
/*                                                                         */
/*  cpw_keymouse.h                                                         */
/*                                                                         */
/*    Querying realtime keyboard and mouse state. Also contains            */
/*    keyboard and mouse constants.                                        */
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

#ifndef __cpw_keymouse_h__
#define __cpw_keymouse_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /*   key state constants                                                 */
  /*                                                                       */
  /*************************************************************************/

  /* These constants are returned in 'state' by the key and system key 
     events callbacks. */

  #define CPW_KEYMOD_DOWN        1
  #define CPW_KEYMOD_UP          2

  /*************************************************************************/
  /*                                                                       */
  /*   system key constants                                                */
  /*                                                                       */
  /*************************************************************************/

  /* These constants are returned by the system keyboard event callback 
     and are used in the cpwKeyState call. */

  /* function keys */

  #define CPW_KEY_F1              1
  #define CPW_KEY_F2              2
  #define CPW_KEY_F3              3
  #define CPW_KEY_F4              4
  #define CPW_KEY_F5              5
  #define CPW_KEY_F6              6
  #define CPW_KEY_F7              7
  #define CPW_KEY_F8              8
  #define CPW_KEY_F9              9
  #define CPW_KEY_F10             10
  #define CPW_KEY_F11             11
  #define CPW_KEY_F12             12

  /* arrow keys */

  #define CPW_KEY_LEFT            13
  #define CPW_KEY_UP              14
  #define CPW_KEY_RIGHT           15
  #define CPW_KEY_DOWN            16

  /* cursor control keys */

  #define CPW_KEY_PAGEUP          17
  #define CPW_KEY_PAGEDOWN        18
  #define CPW_KEY_HOME            19
  #define CPW_KEY_END             20
  #define CPW_KEY_INSERT          21
  #define CPW_KEY_DELETE          22

  /* system keys */

  #define CPW_KEY_CAPSLOCK        23
  #define CPW_KEY_SHIFT           24
  #define CPW_KEY_CONTROL         25
  #define CPW_KEY_ALT             26
  #define CPW_KEY_ESCAPE          27
  #define CPW_KEY_TAB             28
  #define CPW_KEY_BACKSPACE       29
  #define CPW_KEY_ENTER           30

  /* number pad keys */

  #define CPW_KEY_MULTIPLY        31
  #define CPW_KEY_ADD             32
  #define CPW_KEY_SEPERATOR       33
  #define CPW_KEY_SUBTRACT        34
  #define CPW_KEY_DECIMAL         35
  #define CPW_KEY_DIVIDE          36
  #define CPW_KEY_NUMLOCK         37

  /* sys request key */

  #define CPW_KEY_PRINT           38
  #define CPW_KEY_SCROLLLOCK      39
  #define CPW_KEY_PAUSE           40

  /*************************************************************************/
  /*                                                                       */
  /*   key constants                                                       */
  /*                                                                       */
  /*************************************************************************/

  /* These constants are specific to cpwKetState calls. The key event callback 
     returns the ansi or unicode character constant in 'key'. It does _not_ 
     return these constant values. */

  /* numbers */

  #define CPW_KEY_1               41
  #define CPW_KEY_2               42
  #define CPW_KEY_3               43
  #define CPW_KEY_4               44
  #define CPW_KEY_5               45
  #define CPW_KEY_6               46
  #define CPW_KEY_7               47
  #define CPW_KEY_8               48
  #define CPW_KEY_9               49
  #define CPW_KEY_0               50

  /* specific system keys */

  #define CPW_KEY_LCONTROL        51
  #define CPW_KEY_RCONTROL        52
  #define CPW_KEY_LSHIFT          53
  #define CPW_KEY_RSHIFT          54
  #define CPW_KEY_LALT            55
  #define CPW_KEY_RALT            56

  /* symbol keys */

  #define CPW_KEY_MINUS           57
  #define CPW_KEY_EQUALS          58
  #define CPW_KEY_LBRACKET        59
  #define CPW_KEY_RBRACKET        60
  #define CPW_KEY_SEMICOLON       61
  #define CPW_KEY_APOSTROPHE      62
  #define CPW_KEY_QUOTE           63
  #define CPW_KEY_COMMA           64
  #define CPW_KEY_PERIOD          65
  #define CPW_KEY_SLASH           66
  #define CPW_KEY_BACKSLASH       67
  #define CPW_KEY_SPACE           68

  /* ansi keys */

  #define CPW_KEY_A               69
  #define CPW_KEY_B               70
  #define CPW_KEY_C               71
  #define CPW_KEY_D               72
  #define CPW_KEY_E               73
  #define CPW_KEY_F               74
  #define CPW_KEY_G               75
  #define CPW_KEY_H               76
  #define CPW_KEY_I               77
  #define CPW_KEY_J               78
  #define CPW_KEY_K               79
  #define CPW_KEY_L               80
  #define CPW_KEY_M               81
  #define CPW_KEY_N               82
  #define CPW_KEY_O               83
  #define CPW_KEY_P               84
  #define CPW_KEY_Q               85
  #define CPW_KEY_R               86
  #define CPW_KEY_S               87
  #define CPW_KEY_T               88
  #define CPW_KEY_U               89
  #define CPW_KEY_V               90
  #define CPW_KEY_W               91
  #define CPW_KEY_X               92
  #define CPW_KEY_Y               93
  #define CPW_KEY_Z               94

  typedef uint_32 CpwKeyConstant;

  /*************************************************************************/
  /*                                                                       */
  /*   mouse constants                                                     */
  /*                                                                       */
  /*************************************************************************/

  /* Mouse button identifiers for the CpwMouseClickCallback and 
     CpwMouseDragCallback mouse button event callbacks. */

  #define CPW_BUTTON_LEFT         0
  #define CPW_BUTTON_MIDDLE       1
  #define CPW_BUTTON_RIGHT        2

  /* Mouse button state constants for the CpwMouseClickCallback and 
     CpwMouseDragCallback mouse button event callbacks. */

  #define CPW_BUTTON_DOWN          0
  #define CPW_BUTTON_UP            1
  #define CPW_BUTTON_ROLL          2  /* wheel roll events on win32 */

  /* mouse enter/leave a window constants for the CpwMouseEntryCallback 
     event callback. */

  #define CPW_MOUSE_ENTER         0
  #define CPW_MOUSE_LEAVE         1

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwMouseInfo                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Contains information about the current position and the mouse       */
  /*   button states. x, y, and z values are relative to the last call     */
  /*   to cpwMouseState.                                                   */
  /*                                                                       */
  /*                                                                       */
  struct _CpwMouseInfo
  {
    int_32 x;
    int_32 y;
    int_32 z;
    bool   buttons[CPW_MAX_BUTTONS];
  };
  typedef struct _CpwMouseInfo CpwMouseInfo;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwMouseCapabilities                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Structure used in describing the mouse connected to this host. Use  */
  /*   cpwMouseCapabilities to fill the structure.                         */
  /*                                                                       */
  struct _CpwMouseCapabilities
  {
    bool xy;
    bool z;
    uint_32 buttons;
  };
  typedef struct _CpwMouseCapabilities CpwMouseCapabilities;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwMouseCapabilities                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Returns a CpwMouseCapabilities describing the mouse connected to    */
  /*   to the host.                                                        */
  /*                                                                       */
  CPW_API bool 
  cpwMouseCapabilities( pCpw cpw, 
                        CpwMouseCapabilities * mcaps );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwMouseState                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Fills and CpwMouseInfo structure with the current state of the      */
  /*   mouse.                                                              */
  /*                                                                       */
  CPW_API bool 
  cpwMouseState( pCpw cpw, 
                 CpwMouseInfo * info );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwKeyState                                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Returns the state of a particular key on the keyboard. Returns true */
  /*   if the key is down, false if it is up.                              */
  /*                                                                       */
  CPW_API bool 
  cpwKeyState( pCpw cpw, 
               CpwKeyConstant key );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions                                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

uint_32 cpw_keymouse_translatekeyconstant( uint_32 keycode, bool shift );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif


