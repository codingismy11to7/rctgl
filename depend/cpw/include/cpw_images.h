/***************************************************************************/
/*                                                                         */
/*  cpw_images.h                                                           */
/*                                                                         */
/*    Support for loading and saving a few image formats commonly used     */
/*    in game programming. Also supports a few image manipulation          */
/*    routines. Simple, no-nonsence, and built to stay that way.           */
/*                                                                         */
/*    Currently supports: TGA, BMP                                         */
/*                                                                         */
/*    This part of the library relies on libtarga, a small, public domain  */
/*    TGA file loading and saving library by Mark Pingel. See the source   */
/*    of libtarga for more details.                                        */ 
/*                                                                         */
/*    For a useful, small, and portable image manipulation lib check out   */
/*    Steve Dekorte's image library which supports a BSD style license.    */
/*    Visit www.dekorte.com for more information.                          */
/*                                                                         */
/*    For advanced image manipulation and support for multiple image       */
/*    formats take a look at devIL, previously known as OpenIL.            */
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

#ifndef __cpw_images_h__
#define __cpw_images_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include CPW_OPENGL_H

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*   CpwImage                                                            */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwImage
  {
    uint_32 width;
    uint_32 height;
    uint_32 depth;      /* 1 (gray scale), 3 (rgb), 4 (rgba) */
    pChar   data;
  };
  typedef struct _CpwImage CpwImage;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*   CpwImageType                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*   Currently supported image types.                                    */
  /*                                                                       */
  enum _CpwImageType
  {
      CPW_IMAGEFORMAT_TGA = 1,
      CPW_IMAGEFORMAT_BMP = 2,
  };
  typedef enum _CpwImageType CpwImageType;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwLoadImage                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Load an image into memory. Type can be one of the CpwExtImageType  */
  /*    constants. texturefit indicates the image should be scaled to fit  */
  /*    the closest acceptable width and height of an OpenGL texture.      */
  /*                                                                       */
  CPW_API bool   
  cpwLoadImage( pCpw cpw, 
                CpwImage * image, 
                CpwImageType type,
                pChar filename,
                bool texturefit );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwTextureFit                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Fits an image to a width and height suitable for OpenGL texturing. */ 
  /*                                                                       */
  CPW_API bool 
  cpwTextureFit( pCpw cpw, 
                 CpwImage * image );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwFreeImage                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Frees a loaded image's resources.                                  */ 
  /*                                                                       */
  CPW_API bool   
  cpwFreeImage( pCpw cpw, 
                CpwImage * image );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwScreenShot                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Copies pixel data from the current frame buffer using glReadPixels */ 
  /*    into 'image' of format RGBA.                                       */
  /*                                                                       */
  CPW_API bool   
  cpwScreenShot( pCpw cpw, 
                 CpwImage * image );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwSaveImage                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Saves an image to disk. Currently, only supports the TGA file      */ 
  /*    format.                                                            */
  /*                                                                       */
  CPW_API bool   
  cpwSaveImage( pCpw cpw, 
                CpwImage * image,
                pChar filename );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwResizeImage                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Resizes an image.                                                  */ 
  /*                                                                       */
  CPW_API bool   
  cpwResizeImage( pCpw cpw, 
                  CpwImage * image, 
                  uint_32 new_width, 
                  uint_32 new_height );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions                                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  bool cpw_images_bestfit( uint_32 * width, uint_32 * height );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
