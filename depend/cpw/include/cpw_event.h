/***************************************************************************/
/*                                                                         */
/*  cpw_event.h                                                            */
/*                                                                         */
/*    The Cpw library event stack interface and management.                */
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

#ifndef __cpw_event_h__
#define __cpw_event_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_keymouse.h"
#include "cpw_callbacks.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*    CpwWindowEvent                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Every Cpw window receives events based on various things that      */ 
  /*    happen to the window, or a user's interaction with a window.       */
  /*    These are the event constants.                                     */
  /*                                                                       */
  enum _CpwWindowEvent 
  {
    CPW_NO_EVENT           = 0,
    CPW_MOUSECLICK_EVENT   = 1,
    CPW_MOUSEMOTION_EVENT  = 2,
    CPW_MOUSEDRAG_EVENT    = 3,
    CPW_MOUSEENTRY_EVENT   = 4,
    CPW_KEYBOARD_EVENT     = 5,
    CPW_SYSKEYBOARD_EVENT  = 6,
    CPW_CREATE_EVENT       = 7,
    CPW_DESTROY_EVENT      = 8,
    CPW_POSITION_EVENT     = 9,
    CPW_DISPLAY_EVENT      = 10,
    CPW_VISIBILITY_EVENT   = 11,
    CPW_RESHAPE_EVENT      = 12,
    CPW_MENUSELECT_EVENT   = 13,
  };
  typedef enum _CpwWindowEvent CpwWindowEvent;
  #define CPW_EVENTCOUNT    CPW_MENUSELECT_EVENT + 1 
  #define CPW_MAXEVENTVALUE CPW_MENUSELECT_EVENT
  /*                                                                       */
  /*************************************************************************/

  /***********************************/
  /* window visibility changes       */
  /***********************************/

  #define CPW_HIDE                0   /* if visible, now hidden */
  #define CPW_SHOW                1   /* if hidden, now shown */
  #define CPW_GAINEDFOCUS         2   /* now the foreground window */
  #define CPW_LOSTFOCUS           3   /* lost foreground status */
  #define CPW_ICONIC              4   /* was iconified */
  #define CPW_RESTORED            5   /* was restored */

  /*************************************************************************/
  /*                                                                       */
  /*   global event handler setter api.                                    */
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
  /*   window specifc event handler setter api.                            */
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
  /*   event stack manipulation api functions                              */
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFilterEvent                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Turns event filtering for a specific event on or off. Returns      */
  /*    the previous filter value for the particular event.                */
  /*                                                                       */
  CPW_API bool           
  cpwFilterEvent( pCpw cpw, 
                  CpwWindowEvent eventType, 
                  bool flag );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwNextEvent                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Returns a CpwWindowEvent constant indicating the next event        */
  /*    to be delivered.                                                   */
  /*                                                                       */
  CPW_API CpwWindowEvent 
  cpwNextEvent( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwNextWindowEvent                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Returns a CpwWindowEvent constant indicating the next event        */
  /*    to be delivered for the specified window.                          */
  /*                                                                       */
  CPW_API CpwWindowEvent 
  cpwNextWindowEvent( pCpw cpw, 
                      uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwClearEvents                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Clears all events from the event stack.                            */
  /*                                                                       */
  CPW_API bool           
  cpwClearEvents( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwClearEvent                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Clears all events of the type specified from the event stack.      */
  /*                                                                       */
  CPW_API bool           
  cpwClearEvent( pCpw cpw, 
                 CpwWindowEvent event ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwClearWindowEvents                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Clears all events in the event stack for the specified window.     */
  /*                                                                       */
  CPW_API bool           
  cpwClearWindowEvents( pCpw cpw, 
                        uint_32 id ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwClearWindowEvent                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Clears all of the events of the type specified in the event stack  */
  /*    for the specified window.                                          */
  /*                                                                       */
  CPW_API bool           
  cpwClearWindowEvent( pCpw cpw, 
                       CpwWindowEvent event, 
                       uint_32 id ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwPopEvent                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Discards the top event off the event stack.                        */
  /*                                                                       */
  CPW_API bool           
  cpwPopEvent( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwStackDepth                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Returns the current number of events pending.                      */
  /*                                                                       */
  CPW_API int_32         
  cpwStackDepth( pCpw cpw );
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
  /*   localhost event interface - see localhost adapter for information.  */
  /*                                                                       */
  /*************************************************************************/

  /* inserting events into the event stack */

  void cpw_hostevent_setfocus( pCpw cpw, uint_32 id ); 
  void cpw_hostevent_lostfocus( pCpw cpw, uint_32 id ); 
  void cpw_hostevent_cursorenter( pCpw cpw, uint_32 id );
  void cpw_hostevent_cursorleft( pCpw cpw, uint_32 id );
  void cpw_hostevent_draw( pCpw cpw, uint_32 id );
  void cpw_hostevent_reshape( pCpw cpw, uint_32 id, uint_32 width, uint_32 height );
  void cpw_hostevent_destroy( pCpw cpw, uint_32 id );
  void cpw_hostevent_position( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
  void cpw_hostevent_visibility( pCpw cpw, uint_32 id, uint_32 state );
  void cpw_hostevent_mouseclick( pCpw cpw, uint_32 id, uint_32 state, uint_32 button, uint_32 x, uint_32 y );
  void cpw_hostevent_mousedrag( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y );
  void cpw_hostevent_mousemove( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
  void cpw_hostevent_keyboard( pCpw cpw, uint_32 id, uint_32 key, bool shift, uint_32 state, uint_32 x, uint_32 y );
  void cpw_hostevent_systemkeyboard( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y );
  void cpw_hostevent_menuselect( pCpw cpw, uint_32 id, uint_32 menuid, uint_32 entryid );

  /* quick check to see if an event is filtered */

  bool cpw_event_filtered( pCpw cpw, CpwWindowEvent event );

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwEventFilter                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A structure used in storing the current event filters.             */
  /*                                                                       */
  struct _CpwEventFilter 
  {
    bool flag[CPW_EVENTCOUNT];
  };
  typedef struct _CpwEventFilter CpwEventFilter;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwEvent                                                           */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Events received by the localhost adapter are stored in an event    */
  /*    stack. This sturcture encompasses a single event in the event      */
  /*    stack.                                                             */
  /*                                                                       */
  struct _CpwEvent 
  {
    bool            used;   /* 1: holds a valid event, 0 : at top of stack */
    bool            filt;   /* 1: this event was purged, skip to next */
    uint_32         winid;  /* id of the window this event is destined for */
    CpwWindowEvent  event;  /* event constant */
    uint_32         p1;     /* p1-p5 are the event's parameters. */
    uint_32         p2;
    uint_32         p3;
    uint_32         p4;
    uint_32         p5;
  };
  typedef struct _CpwEvent CpwEvent;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwEventStack                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The Cpw event stack structure.                                     */
  /*                                                                       */
  /* <Notes>                                                               */
  /*                                                                       */
  /*    The event stack is currently statically defined and holds 256      */
  /*    events. You can bump the size of this structure up to 65535 but    */
  /*    expect it to suck alot of memory. I'd like to convert this to a    */
  /*    dynamic stack, but there are a number of performance issues with   */
  /*    this i'm not in the mood to deal with right now. 256 events        */
  /*    is actually fairly respectable, i've rarely seen the stack fill    */
  /*    completely even on slow machines with crappy video cards.          */
  /*                                                                       */
  /*    When the stack fills up incoming events are discarded.             */
  /*                                                                       */
  #define CPW_EVENTSTACK_DEPTH 256 /* 255+1:uint_8 */
  struct _CpwEventStack 
  {
    uint_8         nxtindex;  /* next event location index */
    uint_8         insindex;  /* insert location index */
    CpwEvent       stack[CPW_EVENTSTACK_DEPTH];
    CpwEventFilter filter;    /* list of event filter flags */
  };
  typedef struct _CpwEventStack CpwEventStack;
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool cpw_event_init( pCpw cpw );
  void cpw_event_exit( pCpw cpw );

  /* insert standard event - returns false if event is filtered */

  bool cpw_event_insert( pCpw cpw, uint_32 id, CpwWindowEvent event, 
                         uint_32 p1, uint_32 p2, uint_32 p3, uint_32 p4, uint_32 p5 );

  /* insert high priority event */

  bool cpw_event_insertnext( pCpw cpw, uint_32 id, CpwWindowEvent event,
                         uint_32 p1, uint_32 p2, uint_32 p3, uint_32 p4, uint_32 p5 );

  /* processing events in the event stack, used by main */

  bool cpw_event_sendevent( pCpw cpw );
  bool cpw_event_sendevents( pCpw cpw, uint_32 num );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
