/***************************************************************************/
/*                                                                         */
/*  cpw_primitives.h                                                       */
/*                                                                         */
/*    Primitives drawing interface.                                        */
/*                                                                         */
/*    A better primitives interface imho. since you always call the same   */
/*    function and people can add an endless number of primitives. step    */
/*    right up, who wants to add their favorite primitive!                 */
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

#ifndef __cpw_primitives_h__
#define __cpw_primitives_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include CPW_OPENGL_H
#include CPW_GLU_H
#include <math.h>

CPW_BEGIN_HEADER

  #ifndef M_PI
  #define M_PI (float)3.14159265358979323846
  #endif

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*    CpwPrimitives                                                      */
  /*                                                                       */
  enum CpwPrimitives 
  {
    CPW_PRIM_3D_WIRESPHERE,       /* wire sphere     radius, slices, stacks */
    CPW_PRIM_3D_SOLIDSPHERE,      /* solid sphere    radius, slices, stacks */
    CPW_PRIM_3D_WIRECONE,         /* wire cone       baseradius, topradius, slices, stacks */
    CPW_PRIM_3D_SOLIDCONE,        /* solid cone      baseradius, topradius, slices, stacks */
    CPW_PRIM_3D_WIRECUBE,         /* wire cube       size */
    CPW_PRIM_3D_SOLIDCUBE,        /* solid cube      size */
    CPW_PRIM_3D_WIRETORUS,        /* wire torus      innerradius, outerradius, slices, stacks */
    CPW_PRIM_3D_SOLIDTORUS,       /* solid torus     innerradius, outerradius, slices, stacks */
    CPW_PRIM_3D_WIREDOUGHNUT,     /* wire torus      innerradius, outerradius, slices, stacks */
    CPW_PRIM_3D_SOLIDDOUGHNUT,    /* solid torus     innerradius, outerradius, slices, stacks */
    CPW_PRIM_3D_WIREDISK,         /* wire torus      innerradius, outerradius, slices, stacks */
    CPW_PRIM_3D_SOLIDDISK,        /* solid torus     innerradius, outerradius, slices, stacks */
    CPW_PRIM_3D_WIRETEAPOT,       /* teapot          scale */
    CPW_PRIM_3D_SOLIDTEAPOT,      /* teapot          scale */
    CPW_PRIM_3D_TEAPOTAHEDRON,    /* history         scale */
    CPW_PRIM_2D_LINE,             /* line            width */
    CPW_PRIM_2D_SQUARE,           /* rectangle       scale */
    CPW_PRIM_2D_FILLEDSQUARE,     /* filledrect      scale */
    CPW_PRIM_2D_RECTANGLE,        /* rectangle       width, height */
    CPW_PRIM_2D_FILLEDRECTANGLE,  /* filledrect      width, height */
    CPW_PRIM_2D_TRIANGLE,         /* triangle        scale */
    CPW_PRIM_2D_FILLEDTIRANGLE,   /* filledtri       scale */
  };
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*    CpwPrimitiveOption                                                 */
  /*                                                                       */
  enum CpwPrimitiveOption 
  {
    CPW_PRIMOPT_RESET,          /* reset primitive drawing state */
    CPW_PRIMOPT_SIZE,
    CPW_PRIMOPT_RADIUS,
    CPW_PRIMOPT_INNERRADIUS,
    CPW_PRIMOPT_OUTERRADIUS,
    CPW_PRIMOPT_TOPRADIUS,
    CPW_PRIMOPT_BASERADIUS,
    CPW_PRIMOPT_WIDTH,
    CPW_PRIMOPT_HEIGHT,
    CPW_PRIMOPT_SLICES,
    CPW_PRIMOPT_STACKS,
    CPW_PRIMOPT_SCALE,
    CPW_PRIMOPT_TEXTURE,
  };
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwPrimitivesState                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Hold the current primitive drawing state.                          */
  /*                                                                       */
  struct _CpwPrimitivesState
  {
    float_32 size;
    float_32 radius;
    float_32 innerradius;
    float_32 outerradius;
    float_32 topradius;
    float_32 baseradius;
    float_32 width;
    float_32 height;
    float_32 scale;
    uint_32  slices;
    uint_32  stacks;
    bool     texture;
    GLUquadricObj * quadObj;
  };
  typedef struct _CpwPrimitivesState  CpwPrimitivesState;
  typedef struct _CpwPrimitivesState* pCpwPrim;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwSetPrimitiveOpt                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Sets a particular option for primitives drawing.                    */
  /*                                                                       */
  CPW_API bool 
  cpwSetPrimitiveOpt( pCpw cpw, uint_32 option, float_32 value ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDrawPrimitive                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Draw the specified primitive.                                       */
  /*                                                                       */
  CPW_API bool 
  cpwDrawPrimitive( pCpw cpw, uint_32 primitive ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  bool cpw_primitives_init( pCpw cpw );
  void cpw_primitives_exit( pCpw cpw ); 

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
