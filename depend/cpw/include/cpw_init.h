/***************************************************************************/
/*                                                                         */
/*  cpw_init.h                                                             */
/*                                                                         */
/*    The Cpw library init interface and developer log.                    */
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

#ifndef __cpw_init_h__
#define __cpw_init_h__

#include "cpw_config.h"
#include "cpw_state.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitDisplayMode                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool  
  cpwInitDisplayMode( pCpw cpw, 
                      uint_32 modes );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Defines>                                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Bit flag constants for cpwInitDisplayMode.                         */
  /*                                                                       */
  #define    CPW_SURFACE_RGBA     0x0000000000000001 /* (default) */
  #define    CPW_SURFACE_RGB      0x0000000000000001 
  #define    CPW_SURFACE_INDEX    0x0000000000000002 /* not supported */
  #define    CPW_SURFACE_SINGLE   0x0000000000000004
  #define    CPW_SURFACE_DOUBLE   0x0000000000000008 /* (default) */
  /* accumulation buffer requested */
  #define    CPW_SURFACE_ACCUM    0x0000000000000010
  /* depth buffer requested */
  #define    CPW_SURFACE_DEPTH    0x0000000000000020 /* (default) */
  /* stencil buffer requested */
  #define    CPW_SURFACE_STENCIL  0x0000000000000040
  /* stereo buffers requested */
  #define    CPW_SURFACE_STEREO   0x0000000000000080
  /* overall color component depth requests */
  #define    CPW_SURFACE_COLOR8   0x0000000000000100
  #define    CPW_SURFACE_COLOR16  0x0000000000000200 /* (default) */
  #define    CPW_SURFACE_COLOR32  0x0000000000000400
  #define    CPW_SURFACE_COLOR64  0x0000000000000800
  /* color buffer component specific bit depth requests */
  #define    CPW_SURFACE_RED2     0x0000000000001000
  #define    CPW_SURFACE_RED4     0x0000000000002000
  #define    CPW_SURFACE_RED8     0x0000000000004000
  #define    CPW_SURFACE_RED16    0x0000000000008000
  #define    CPW_SURFACE_GREEN2   0x0000000000010000
  #define    CPW_SURFACE_GREEN4   0x0000000000020000
  #define    CPW_SURFACE_GREEN8   0x0000000000040000
  #define    CPW_SURFACE_GREEN16  0x0000000000080000
  #define    CPW_SURFACE_BLUE2    0x0000000000100000
  #define    CPW_SURFACE_BLUE4    0x0000000000200000
  #define    CPW_SURFACE_BLUE8    0x0000000000400000
  #define    CPW_SURFACE_BLUE16   0x0000000000800000
  #define    CPW_SURFACE_ALPHA2   0x0000000001000000
  #define    CPW_SURFACE_ALPHA4   0x0000000002000000
  #define    CPW_SURFACE_ALPHA8   0x0000000004000000
  #define    CPW_SURFACE_ALPHA16  0x0000000008000000
  /* z buffer depth requests */
  #define    CPW_SURFACE_DEPTH2   0x0000000010000000
  #define    CPW_SURFACE_DEPTH4   0x0000000020000000
  #define    CPW_SURFACE_DEPTH8   0x0000000040000000 /* (default) */
  #define    CPW_SURFACE_DEPTH16  0x0000000080000000
  #define    CPW_SURFACE_DEPTH32  0x0000000100000000
  #define    CPW_SURFACE_DEPTH64  0x0000000200000000
  /* accumulation buffer's color component depth requests */
  #define    CPW_SURFACE_ACOLOR8  0x0004000000000000
  #define    CPW_SURFACE_ACOLOR16 0x0008000000000000
  #define    CPW_SURFACE_ACOLOR32 0x0010000000000000
  #define    CPW_SURFACE_ACOLOR64 0x0020000000000000
  /* accumulation buffer color component specific depth requests */
  #define    CPW_SURFACE_ARED2    0x0000000400000000
  #define    CPW_SURFACE_ARED4    0x0000000800000000
  #define    CPW_SURFACE_ARED8    0x0000001000000000
  #define    CPW_SURFACE_ARED16   0x0000002000000000
  #define    CPW_SURFACE_AGREEN2  0x0000004000000000
  #define    CPW_SURFACE_AGREEN4  0x0000008000000000
  #define    CPW_SURFACE_AGREEN8  0x0000010000000000
  #define    CPW_SURFACE_AGREEN16 0x0000020000000000
  #define    CPW_SURFACE_ABLUE2   0x0000040000000000
  #define    CPW_SURFACE_ABLUE4   0x0000080000000000
  #define    CPW_SURFACE_ABLUE8   0x0000100000000000
  #define    CPW_SURFACE_ABLUE16  0x0000200000000000
  #define    CPW_SURFACE_AALPHA2  0x0000400000000000
  #define    CPW_SURFACE_AALPHA4  0x0000800000000000
  #define    CPW_SURFACE_AALPHA8  0x0001000000000000
  #define    CPW_SURFACE_AALPHA16 0x0002000000000000
  /* accumulation buffer's z buffer depth requests */
  #define    CPW_SURFACE_ADEPTH2  0x0040000000000000
  #define    CPW_SURFACE_ADEPTH4  0x0080000000000000
  #define    CPW_SURFACE_ADEPTH8  0x0100000000000000
  #define    CPW_SURFACE_ADEPTH16 0x0200000000000000
  #define    CPW_SURFACE_ADEPTH32 0x0400000000000000
  #define    CPW_SURFACE_ADEPTH64 0x0800000000000000
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitWindowSize                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool  
  cpwInitWindowSize( pCpw cpw, 
                     uint_32 width, 
                     uint_32 height );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitWindowPosition                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool  
  cpwInitWindowPosition( pCpw cpw, 
                         uint_32 xposition, 
                         uint_32 yposition );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitWindowProperty                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */

  /* window style flags */

  #define CPW_WINDOWPROP_STANDARD       0x00000001
  #define CPW_WINDOWPROP_POPUP          0x00000002
  #define CPW_WINDOWPROP_NODRESSING     0x00000004
  #define CPW_WINDOWPROP_STYLECLRMASK   0xFFFFFF00

  /* window border style flags */

  #define CPW_WINDOWPROP_NOBORDER       0x00000100
  #define CPW_WINDOWPROP_THINBORDER     0x00000200
  #define CPW_WINDOWPROP_THICKBORDER    0x00000400
  #define CPW_WINDOWPROP_BORDERCLRMASK  0xFFFFF0FF

  /* setting numerical options */

  #define CPW_WINDOWPROP_POSITION       0x80000000
  #define CPW_WINDOWPROP_SIZE           0x40000000
  #define CPW_WINDOWPROP_DESKTOP        0x20000000
  #define CPW_WINDOWPROP_EXPECTMENU     0x10000000

  CPW_API bool
  cpwInitWindowProperty( pCpw cpw, 
                         uint_32 property, 
                         uint_32 paramone,
                         uint_32 paramtwo );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitPrintHandler                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool  
  cpwInitPrintHandler( pCpw cpw, 
                       CpwPrintHandler print );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwInitDisplayModeExact                                            */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool  
  cpwInitDisplayModeExact( pCpw cpw, 
                           uint_32 mode, 
                           uint_32 condition, 
                           int_32  value );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Defines>                                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Comparitor constants for cpwInitDisplayModeExact.                  */
  /*                                                                       */
  #define  CPW_NONE                             0x0000
  #define  CPW_EQUAL                            0x0001
  #define  CPW_NOT_EQUAL                        0x0002
  #define  CPW_LESS                             0x0003
  #define  CPW_MORE                             0x0004
  #define  CPW_LESS_OR_EQUAL                    0x0005
  #define  CPW_MORE_OR_EQUAL                    0x0006
  #define  CPW_CLOSEST                          0x0007
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Defines>                                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Settings flag constants for cpwInitDisplayModeExact.               */
  /*                                                                       */
  #define    CPW_SURFACEX_ALPHA                 1
  #define    CPW_SURFACEX_ACCUM                 2
  #define    CPW_SURFACEX_RED                   3
  #define    CPW_SURFACEX_GREEN                 4
  #define    CPW_SURFACEX_BLUE                  5
  #define    CPW_SURFACEX_INDEXCOLORBUFFER      6
  #define    CPW_SURFACEX_CONFORMANT            7
  #define    CPW_SURFACEX_DEPTH                 8
  #define    CPW_SURFACEX_DOUBLE                9
  #define    CPW_SURFACEX_INDEX                 10
  #define    CPW_SURFACEX_NUM                   11
  #define    CPW_SURFACEX_RGBA                  12
  #define    CPW_SURFACEX_RGB                   13
  #define    CPW_SURFACEX_LUMINANCE             14
  #define    CPW_SURFACEX_STENCIL               15
  #define    CPW_SURFACEX_SINGLE                16
  #define    CPW_SURFACEX_STEREO                17
  #define    CPW_SURFACEX_SAMPLES               18
  #define    CPW_SURFACEX_SLOW                  19
  #define    CPW_SURFACEX_WIN32PDF              20
  #define    CPW_SURFACEX_XVISUAL               21
  #define    CPW_SURFACEX_XSTATICGRAY           22
  #define    CPW_SURFACEX_XGRAYSCALE            23
  #define    CPW_SURFACEX_XSTATICCOLOR          24
  #define    CPW_SURFACEX_XPSEUDOCOLOR          25
  #define    CPW_SURFACEX_XTRUECOLOR            26
  #define    CPW_SURFACEX_XDIRECTCOLOR          27
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

  bool cpw_init_init( pCpw cpw );
  void cpw_init_exit( pCpw cpw );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif

/* 
    Developer Logs

    Date        Name                    Notes
    ------------------------------------------------------------------------
    12/09/2001  Jim Mathies             Started Cpw Project
    01/01/2002  Jim Mathies             First public release of 1.0 Beta
    02/01/2002  Jim Mathies             Final 1.0 release

    "Programming is an art. 
    
    One important quality of a true masterpeice is how you mix and 
    apply the paint to the canvas.

    Another is the paint you choose."

*/
