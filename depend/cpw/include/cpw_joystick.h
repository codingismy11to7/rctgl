/***************************************************************************/
/*                                                                         */
/*  cpw_joystick.h                                                         */
/*                                                                         */
/*    Joystick polling interface.                                          */
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

#ifndef __cpw_joystick_h__
#define __cpw_joystick_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Limits Define>                                                       */
  /*    CPW_MAX_JOYSTICKS                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The maximum number of joyticks the library supports.               */
  /*                                                                       */
  #define CPW_MAX_JOYSTICKS 2
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Limits Define>                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    CPW_JOY_AXES    - maximum number of axes a joystick can support    */
  /*                                                                       */
  /*    CPW_JOY_POVS    - maximum number of hats a joystick can support    */
  /*                                                                       */
  /*    CPW_JOY_BUTTONS - maximum number of buttons a joystick can support */
  /*                                                                       */
  #define CPW_JOY_AXES     5
  #define CPW_JOY_POVS     4
  #define CPW_JOY_BUTTONS  32
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Define>                                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Default joystick normalization ranges.                             */
  /*                                                                       */
  #define CPW_JOY_AXISMIN       -1000
  #define CPW_JOY_AXISMAX        1000
  #define CPW_JOY_ROTATIONMIN    0
  #define CPW_JOY_ROTATIONMAX    3590
  #define CPW_JOY_VELOCITYMIN    0
  #define CPW_JOY_VELOCITYMAX    1000
  #define CPW_JOY_ACCELMIN       0
  #define CPW_JOY_ACCELMAX       1000
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Define>                                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*    POV (point of view) hat positions for POV's that support discrete  */
  /*    positional information.                                            */
  /*                                                                       */
  #define CPW_POV_CENTERED     -1
  #define CPW_POV_UP           0
  #define CPW_POV_UPRIGHT      4500
  #define CPW_POV_RIGHT        9000
  #define CPW_POV_DOWNRIGHT    13500
  #define CPW_POV_DOWN         18000
  #define CPW_POV_DOWNLEFT     22500
  #define CPW_POV_LEFT         27000
  #define CPW_POV_UPLEFT       31500
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwJoystickCapabilities                                            */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwJoystickCapabilities
  {
    uint_32 id;                     /* the joystick id value */

    bool    axis[CPW_JOY_AXES];     /* x, y, z, u, v axis */
    bool    rot[CPW_JOY_AXES];      /* axis rotation */
    bool    variablepov;            /* point-of-view hats are variable */
    bool    pov[CPW_JOY_POVS];      /* point-of-view hats */
    bool    vel[CPW_JOY_AXES];      /* axis velocity */
    bool    accel[CPW_JOY_AXES];    /* axis acceleration */
    bool    force[CPW_JOY_AXES];    /* axis force applied */
    bool    forcefeedback;          /* supports force feedback */
    uint_32 numbuttons;             /* number of buttons supported */
  };
  typedef struct _CpwJoystickCapabilities CpwJoystickCapabilities;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwJoystickRanges                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Contained within CpwJoystickList. Allows application to set        */
  /*    custom ranges on certain joystick properties.                      */
  /*                                                                       */
  /* <Fields>                                                              */
  /*    axis        - use custom ranges or return device defaults          */
  /*                                                                       */
  /*    rotation    - use custom ranges or return device defaults          */
  /*                                                                       */
  /*    velocity    - use custom ranges or return device defaults          */
  /*                                                                       */
  /*    accel       - use custom ranges or return device defaults          */
  /*                                                                       */
  /*    axismin     - defines the minimum value an axis                    */
  /*                  positional value is normailized to.                  */
  /*                                                                       */
  /*    axismax     - defines the maximum value an axis                    */
  /*                  positional value is normailized to.                  */
  /*                                                                       */
  /*    rotmin      - defines the minimum value an axes rotational         */
  /*                  value is normailized to.                             */
  /*                                                                       */
  /*    rotmax      - defines the maximum value an axes rotational         */
  /*                  value is normailized to.                             */
  /*                                                                       */
  /*    velmin      - defines the minimum value an axes velocity of        */
  /*                  movement value is normailized to.                    */
  /*                                                                       */
  /*    velmax      - defines the maximum value an axes velocity of        */
  /*                  movement value is normailized to.                    */
  /*                                                                       */
  /*    accelmin    - defines the minimum value an axes acceleration of    */
  /*                  movement value is normailized to.                    */
  /*                                                                       */
  /*    accelmax    - defines the maximum value an axes acceleration of    */
  /*                  movement value is normailized to.                    */
  /*                                                                       */
  struct _CpwJoystickRanges
  {
    bool   axis;     /* use custom axis range values */
    int_16 axismin;  /* user definable minimum axis normalization value */
    int_16 axismax;  /* user definable maximum axis normalization value */
    bool   rotation; /* use custom rotation range values */
    int_16 rotmin;   /* user definable minimum rotation normalization value. */
    int_16 rotmax;   /* user definable maximum rotation normalization value. */
    bool   velocity; /* use custom velocity range values */
    int_16 velmin;   /* user definable minimum velocity normalization value */
    int_16 velmax;   /* user definable maximum velocity normalization value */
    bool   accel;    /* use custom accel range values */
    int_16 accelmin; /* user definable minimum acceleration normalization value. */
    int_16 accelmax; /* user definable maximum acceleration normalization value. */
  };
  typedef struct _CpwJoystickRanges CpwJoystickRanges;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwJoystickList                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The primary data structure for cpwInitJoysticks.                   */
  /*                                                                       */
  /* <Fields>                                                              */
  /*                                                                       */
  struct _CpwJoystickList
  {
    uint_32                 joysticks;
    CpwJoystickRanges       ranges;
    CpwJoystickCapabilities caps[CPW_MAX_JOYSTICKS];
  };
  typedef struct _CpwJoystickList CpwJoystickList;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwJoystickInfo                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  /*    Inputs:                                                            */
  /*                                                                       */
  /*    id          - the id of the joystick to read                       */
  /*                                                                       */
  /*    Outputs:                                                           */
  /*                                                                       */
  /*    axis[]      - returns the value of the axis position.              */
  /*                  default values : -1000/1000                          */
  /*                                                                       */
  /*    rot[]       - returns the value of the axis rotation.              */
  /*                  default values : 0/3590                              */
  /*                                                                       */
  /*    vel[]       - returns the value of the axis velocity of            */
  /*                  motion.                                              */
  /*                  default values : 0/1000                              */
  /*                                                                       */
  /*    accel[]     - returns the value of the axis acceleration           */
  /*                  of motion.                                           */
  /*                  default values : 0/1000                              */
  /*                                                                       */
  /*    pov[]       - returns the value of the pov (point-of-view) hat.    */
  /*                  pov positions can either be discrete, meaning they   */
  /*                  adhere to a set of Cpw directional states, or they   */
  /*                  are variable, meaning they have continuous position  */
  /*                  values like an axis.                                 */
  /*                  variable values : 0/35900, 36000 centered            */
  /*                  discrete values : POV position constants             */
  /*                                                                       */
  struct _CpwJoystickInfo
  {
    uint_32 id;                      /* the joystick id to access */

    int_32 axis[CPW_JOY_AXES];       /* x, y, z, u, v axis */
    int_32 rot[CPW_JOY_AXES];        /* axis rotation */
    int_32 pov[CPW_JOY_POVS];        /* point-of-view hats, variable or discrete */
    int_32 vel[CPW_JOY_AXES];        /* axis velocity */
    int_32 accel[CPW_JOY_AXES];      /* axis acceleration */
    bool   buttons[CPW_JOY_BUTTONS]; /* button states */
  };
  typedef struct _CpwJoystickInfo CpwJoystickInfo;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    Global joystick event callback                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  typedef void (*CpwJoystickCallback) ( pCpw cpw, CpwJoystickInfo * info ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitJoysticks                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Lists any active, plugged in joystick available. Returns a list of */
  /*    CpwJoystickCapabilities containing information about each          */
  /*    joystick.                                                          */
  /*                                                                       */
  CPW_API bool 
  cpwInitJoysticks( pCpw cpw, 
                    CpwJoystickList * list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwJoystickCallback                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Sets a global joystick callback which will be called               */
  /*    every msecs 'delay'.                                               */
  /*                                                                       */
  CPW_API bool 
  cpwJoystickCallback( pCpw cpw, 
                       CpwJoystickCallback joyCallback, 
                       uint_32 joyid, 
                       uint_32 delay );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwJoystickPing                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Forces the generation of a callback to cpwJoystickCallback's       */
  /*    callback function.                                                 */
  /*                                                                       */
  CPW_API bool 
  cpwJoystickPing( pCpw cpw, uint_32 joyid ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwJoystickPoll                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Returns real-time information on the state of a joystick.          */
  /*                                                                       */
  CPW_API bool 
  cpwJoystickPoll( pCpw cpw, 
                   CpwJoystickInfo * info );
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
  /*    CpwJoystickList                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwJoystickContext 
  {
    CpwJoystickCallback joyCallback[CPW_MAX_JOYSTICKS];
    uint_32             timerid[CPW_MAX_JOYSTICKS];
  }; 
  typedef struct _CpwJoystickContext  CpwJoystickContext;
  typedef struct _CpwJoystickContext* pCpwJoystickContext;
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool cpw_joystick_init( pCpw cpw );
  void cpw_joystick_exit( pCpw cpw );

  /* cpw_timer callback */

  void cpw_joystick_timout( pCpw cpw, uint_32 id );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
