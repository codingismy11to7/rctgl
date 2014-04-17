/***************************************************************************/
/*                                                                         */
/*  cpw_macros.h                                                           */
/*                                                                         */
/*    Some useful macros for setting and accessing information in Cpw.     */
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

#ifndef __cpw_macros_h__
#define __cpw_macros_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_joystick.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Helper Macros>                                                       */
  /*    Some useful macros for setting and accessing information in Cpw.   */
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   joysticks                                                           */
  /*                                                                       */
  /*************************************************************************/

  /****************************************************/
  /*                                                  */
  /*  Setting data in the CpwJoystickList structure   */
  /*         ( used in cpwInitJoysticks )             */
  /*                                                  */
  /****************************************************/

  /* setting the number of joysticks requested */

  #define MCpwJoysticksRequested( list, count )   \
          list.joysticks = count

  /* setting the custom axis range in CpwJoystickList structure */

  #define MCpwJoystickAxisRange( list, min, max ) \
          list.ranges.axis = true;                \
          list.ranges.axismin = min;              \
          list.ranges.axismax = max

  /* setting the custom rotation range in CpwJoystickList structure */

  #define MCpwJoystickRotRange( list, min, max )  \
          list.ranges.rotation = true;            \
          list.ranges.rotmin = min;               \
          list.ranges.rotmax = max

  /* setting the custom velocity range in CpwJoystickList structure */

  #define MCpwJoystickVelRange( list, min, max )  \
          list.ranges.velocity = true;            \
          list.ranges.velmin = min;               \
          list.ranges.velmax = max

  /* setting the custom acceleration range in CpwJoystickList structure */

  #define MCpwJoystickAccelRange( list, min, max )\
          list.ranges.accel = true;               \
          list.ranges.accelmin = min;             \
          list.ranges.accelmax = max

  /********************************************************/
  /*                                                      */
  /*  Retrieving data from the CpwJoystickList structure  */
  /*       ( after calling cpwInitJoysticks )             */
  /*                                                      */
  /********************************************************/

  /* the number of joysticks found ( 0 -> CPW_MAX_JOYSTICKS ) */

  #define MCpwJoysticksFound( list )              \
          list.joysticks

  /* the id of the first joystick found */

  #define MCpwJoystick1Id( list )                 \
          list.caps[0].id

  /* the id of the second joystick found */

  #define MCpwJoystick2Id( list )                 \
          list.caps[1].id

  /* joystick supports a pov */

  #define MCpwJoystickPov( list, id )             \
          list.caps[id-1].pov[0]

  /* the axis range minimum */

  #define MCpwJoystickAxisRangeMin( list )        \
          list.ranges.axismin

  /* the axis range maximum */

  #define MCpwJoystickAxisRangeMax( list )        \
          list.ranges.axismax

  /* the rot range minimum */

  #define MCpwJoystickRotRangeMin( list )         \
          list.ranges.rotmin

  /* the rot range maximum */

  #define MCpwJoystickRotRangeMax( list )         \
          list.ranges.rotmax

  /********************************************************/
  /*                                                      */
  /*  Retrieving data from the CpwJoystickInfo structure  */
  /*  ( after calling cpwJoystickPoll or in a callback )  */
  /*                                                      */
  /********************************************************/

  /* access the x-axis value */

  #define MCpwJoystickXAxis( info )               \
          info.axis[0]

  /* access the y-axis value */

  #define MCpwJoystickYAxis( info )               \
          info.axis[1]

  /* access the z-axis value */

  #define MCpwJoystickZAxis( info )               \
          info.axis[2]

  /* access the u-axis value */

  #define MCpwJoystickUAxis( info )               \
          info.axis[3]

  /* access the v-axis value */

  #define MCpwJoystickVAxis( info )               \
          info.axis[4]

  /* access the number of buttons */

  #define MCpwJoystick1ButtonCount( list )        \
          list.caps[0].numbuttons

  /* access a button state */

  #define MCpwJoystick1Button( info, b )          \
          info.buttons[b-1]

  /* access the x-rotation value */

  #define MCpwJoystickXRot( info )                \
          info.rot[0]

  /* access the y-rotation value */

  #define MCpwJoystickYRot( info )                \
          info.rot[1]

  /* access the z-rotation value */

  #define MCpwJoystickZRot( info )                \
          info.rot[2]

  /* access the pov1 position */

  #define MCpwJoystickPov1( info )                \
          info.pov[0]

  /* access the pov2 position */

  #define MCpwJoystickPov2( info )                \
          info.pov[1]

  /* access the pov3 position */

  #define MCpwJoystickPov3( info )                \
          info.pov[2]

CPW_END_HEADER

#endif
