/***************************************************************************/
/*                                                                         */
/*  cpw_timers.h                                                           */
/*                                                                         */
/*    Cpw timers interface.                                                */
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

#ifndef __cpw_timers_h__
#define __cpw_timers_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    CpwTimerCallback                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Timer callback function prototype.                                 */
  /*                                                                       */
  typedef void (*CpwTimerCallback) ( pCpw cpw, uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwTimerCallback                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new timer. 'milli' is the timer's timeout value          */
  /*    in milliseconds. 'timerid' is a user definable id value            */
  /*    handed back to the timer callback function. 'recurring'            */
  /*    is a boolean flag indicating whether the timer is a recurring      */
  /*    timer or one-shot.                                                 */
  /*                                                                       */
  CPW_API bool 
  cpwTimerCallback( pCpw cpw, 
                    uint_32 milli, 
                    uint_32 id, 
                    bool recuring, 
                    CpwTimerCallback timerCallback );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwKillTimer                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Stops a recurring timer.                                           */
  /*                                                                       */
  CPW_API bool 
  cpwKillTimer( pCpw cpw, 
                uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  /* tick called by main */

  extern CPW_INLINE bool cpw_timers_tick( pCpw cpw );

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwTimer                                                           */
  /*                                                                       */
  /* <Description>                                                         */
  /*    struct that holds a timer's data.                                  */
  /*                                                                       */
  struct _CpwTimer 
  {
    CpwTimerCallback timerCallback;
    float_64         hpcount;
    float_64         hpdiff;
    uint_32          listid;
    uint_32          timerid;
    bool             redo;
    bool             internal;
    uint_32          int_type;
  };
  typedef struct _CpwTimer CpwTimer;
  typedef struct _CpwTimer* pCpwTimer;
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool cpw_timers_init( pCpw cpw );
  void cpw_timers_exit( pCpw cpw );

  /* running through the list */

  CPW_INLINE pCpwTimer cpw_timers_iteratestart( pCpw cpw );
  CPW_INLINE pCpwTimer cpw_timers_iteratenext( pCpw cpw );

  /* internal timer types */

  enum {
    CPW_TIMER_INTERNAL_JOYSTICK = 1,
  };

  /* internal timers */

  bool cpw_timers_createinternal( pCpw cpw, uint_32 type, bool redo, uint_32 delay, uint_32 id );
  void cpw_timers_internaltimeout( pCpw cpw, pCpwTimer timer );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
