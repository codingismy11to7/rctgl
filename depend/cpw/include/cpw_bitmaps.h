/***************************************************************************/
/*                                                                         */
/*  cpw_bitmaps.h                                                          */
/*                                                                         */
/*    Cpw interface to BMP file loading and saving.                        */
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

#ifndef __cpw_bitmaps_h__
#define __cpw_bitmaps_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_images.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

bool cpw_bitmap_load( pCpw cpw, char * filename, CpwImage * image );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
