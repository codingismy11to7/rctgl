/***************************************************************************/
/*                                                                         */
/*  cpw_perftracker.h                                                      */
/*                                                                         */
/*    Debug performance tracking.                                          */
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

#ifndef __cpw_perftracker_h__
#define __cpw_perftracker_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwAddMark                                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Cpw has a built in mechanism for performance timing of code         */
  /*   segments. To use it, start by initing some marks using cpwAddMark.  */
  /*   cpwAddMark takes a name for the mark, and a flag indicating         */
  /*   whether you want the time stats to be an accumulated total, or      */
  /*   averaged. If averaged, the performance tracker will average the     */
  /*   total time the thread spends in a particular segment of code.       */
  /*   If accumulated, the total time the thread spends in the segment     */
  /*   will be reported. Times are recorded and reported using double      */
  /*   precision. The accuracy of which depends on the high freqency       */
  /*   counter routines for your platform.                                 */
  /*                                                                       */
  /*   Returns the mark's id used in subsequent calls.                     */
  /*                                                                       */
  CPW_API uint_32 
  cpwAddMark( pCpw cpw, pChar name, bool average ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwEnterMark                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Call cpwEnterMark when entering a code segment associated with a   */
  /*    performance mark you have previously created. Entering a mark      */
  /*    saves a time of entry. Then call cpwExitMark to 'close' the        */
  /*    segment.                                                           */
  /*                                                                       */
  CPW_API bool
  cpwEnterMark( pCpw cpw, uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwExitMark                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Exits a previously entered mark.                                   */
  /*                                                                       */
  CPW_API bool
  cpwExitMark( pCpw cpw, uint_32 id );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDumpMarks                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Dumps the current performance mark statistics to the cpw print      */
  /*   handler. Does not clear the statistics.                             */
  /*                                                                       */
  CPW_API void
  cpwDumpMarks( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFpsInit                                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Intializes the simple frame counter.                                */
  /*                                                                       */
  CPW_API void    
  cpwFpsInit( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFpsDraw                                                         */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Increments the frame counter by one and checks to see if 1 second   */
  /*   has elapsed. If it has, prints the current frame rate to the cpw    */
  /*   print handler if 'print' is true. Also saves the frame rate for     */
  /*   retieval through cpwFpsGet.                                         */
  /*                                                                       */
  CPW_API void    
  cpwFpsDraw( pCpw cpw, bool print );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFpsGet                                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Returns the current frame rate.                                     */
  /*                                                                       */
  CPW_API uint_32 
  cpwFpsGet( pCpw cpw );
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
  /*    PerformanceMark                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Holds a single performance mark's state.                           */
  /*                                                                       */
  struct _PerformanceMark
  {
    pStr      name;
    bool      average;
    float_64  ticks;
    float_64  entered;
  };
  typedef struct _PerformanceMark  PerformanceMark;
  typedef struct _PerformanceMark* pCpwMark;
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool cpw_perftracker_init( pCpw cpw );
  void cpw_perftracker_exit( pCpw cpw );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
