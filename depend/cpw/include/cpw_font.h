/***************************************************************************/
/*                                                                         */
/*  cpw_font.h                                                             */
/*                                                                         */
/*    The Cpw library interface to FreeType 2.0. This is fairly            */
/*    stand-alone and could probably be pulled out of Cpw without much     */
/*    effort.                                                              */
/*                                                                         */
/*  Copyright 2001-2002 by                                                 */
/*    Jim Mathies,                                                         */
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

#ifndef __cpw_font_h__
#define __cpw_font_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include CPW_OPENGL_H

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwFontList                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A structure used in loading lists of locally available fonts.      */
  /*                                                                       */
  /* <Fields>                                                              */
  /*    size   - size of the internal list of fonts. 0 for none            */
  /*                   found or if the list was never generated.           */
  /*                                                                       */
  /*    list   - pointer to char* list[size]                               */
  /*                                                                       */
  #define CPW_MAX_FONTS 500
  struct _CpwFontList
  {
    int_32   size;
    pChar    list[CPW_MAX_FONTS];
  };
  typedef struct _CpwFontList CpwFontList;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwListLocalFonts                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    List's localhost's available (and supported) font files.           */
  /*                                                                       */
  CPW_API uint_32 
  cpwListFonts( pCpw cpw, 
                CpwFontList* list, 
                pChar hints,
                uint_32 location );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFreeFontList                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Frees a font list.                                                 */
  /*                                                                       */
  CPW_API bool 
  cpwFreeFontList( pCpw cpw, 
                   CpwFontList* list );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFontMode                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Sets various font rendering parameters. (listed above )            */
  /*                                                                       */
  CPW_API int_32  
  cpwFontMode( pCpw cpw, 
               int_32 mode, 
               int_32 val );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*    Font modes constants                                               */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Font rendering options (set by cpwFontMode above) which are used   */
  /*    by cpwDrawFont and cpwDrawBufferedFont.                            */
  /*                                                                       */
  /* Rendering Modes:                                                      */
  /*                                                                       */
  /*    CPW_FONTOPT_PIXELMAP          - Render using pixelmap mode. Pixel  */
  /*                                    map fonts are drawn directly to    */
  /*                                    the framebuffer using glDrawPixels */
  /*                                    at the current raster position.    */
  /*                                    Pixel width is dependant on the    */
  /*                                    glformat option set below. If a    */
  /*                                    format that uses color is specified*/
  /*                                    the current gl color will be used. */
  /*                                                                       */
  /*                                    (Specific to cpwDrawFont.)         */
  /*                                                                       */
  /*                                    val = ignored                      */
  /*                                    this is the default mode           */
  /*                                                                       */
  /* Rendering Options:                                                    */
  /*                                                                       */
  /*    CPW_FONTOPT_PIXELMAP_GLFORMAT - the pixel format for calls to      */
  /*                                    glDrawPixels when rendering pixel  */
  /*                                    mapped fonts with cpDrawFont.      */
  /*                                                                       */
  /*                                    val = gl pixel format constant     */
  /*                                    default = GL_LUMINANCE             */
  /*                                                                       */
  /*    CPW_FONTOPT_LAYOUTDEBUG       - Draws rectangles around each       */
  /*                                    character and the entire buffer    */
  /*                                    in cpwDrawBufferedFont buffers.    */
  /*                                                                       */
  /*                                    (Specific to cpwDrawBufferedFont.) */
  /*                                                                       */
  /*                                    val = 1/0                          */
  /*                                    default = off                      */
  /*                                                                       */
  /* Layout Options:                                                       */
  /*                                                                       */
  /*    CPW_FONTOPT_SIZE              - sets the size in points of the     */
  /*                                    font face.                         */
  /*                                                                       */
  /*                                    val = positive int value >= 1      */
  /*                                    default = 16                       */
  /*                                                                       */
  /*    CPW_FONTOPT_FTSIZE            - sets the size of the font face to  */
  /*                                    Freetype 26.6 pixels. 1 point =    */
  /*                                    64 Freetype pixels.                */
  /*                                                                       */
  /*                                    val = positive int value >= 1      */
  /*                                                                       */
  /*    CPW_FONTOPT_SPACING           - the character spacing multiplier.  */
  /*                                                                       */
  /*                                    val = 0.0 and up                   */
  /*                                    default = 1                        */
  /*                                                                       */
  /*    CPW_FONTOPT_KERN              - sets kerning advance on or off.    */
  /*                                    Note: kerning is not supported if  */
  /*                                    the font file does not support it. */
  /*                                                                       */
  /*                                    val = true/false                   */
  /*                                    default = false                    */
  /*                                                                       */
  /*    CPW_FONTOPT_SCREENWIDTH       - the current display screen's       */
  /*                                    width in dpi.                      */
  /*                                                                       */
  /*                                    val = int width                    */
  /*                                    default = 72                       */
  /*                                                                       */
  /*    CPW_FONTOPT_SCREENHEIGHT      - the current display screen's       */
  /*                                    height in dpi.                     */
  /*                                                                       */
  /*                                    val = int height                   */
  /*                                    default = 72                       */
  /*                                                                       */
  /* Alignment Options:                                                    */
  /*                                    Currently only left alinged text   */
  /*                                    is supported.                      */
  /*                                                                       */
  /*   CPW_FONTOPT_ALIGNRIGHT         - Align text right.                  */
  /*                                                                       */
  /*   CPW_FONTOPT_ALIGNLEFT          - Align text left (default).         */
  /*                                                                       */
  /*   CPW_FONTOPT_ALIGNUP            - Align text up.                     */
  /*                                                                       */
  /*   CPW_FONTOPT_ALIGNDOWN          - Align text down.                   */
  /*                                                                       */
  /*   CPW_FONTOPT_ALIGNCENTER        - Align text center.                 */
  /*                                                                       */
  enum _FontRenderMode 
  {
    CPW_FONTOPT_PIXELMAP    = 1, /* pixelmap drawing mode */
  };
  typedef enum _FontRenderMode FontRenderMode;

  enum _FontOption 
  {
    CPW_FONTOPT_SIZE                = 20, /* font size in points */
    CPW_FONTOPT_PICASIZE            = 21, /* font size in 1/64 points */
    CPW_FONTOPT_KERN                = 22, /* kerning on/off */
    CPW_FONTOPT_SPACING             = 23, /* character spacing multiplier 0.0 and up */
    CPW_FONTOPT_SCREENWIDTH         = 24, /* display screen width (300) */
    CPW_FONTOPT_SCREENHEIGHT        = 25, /* display screen height (300) */
    CPW_FONTOPT_PIXELMAP_GLFORMAT   = 26, /* glDrawPixels format for pixelmaps */
    CPW_FONTOPT_LAYOUTDEBUG         = 27, /* bufferedfont character layout debug lines */
  };
  typedef enum _FontOption FontOption;

  enum _FontAlignMode
  {
    CPW_FONTOPT_ALIGNRIGHT  = 10, /* align text right */
    CPW_FONTOPT_ALIGNLEFT   = 11, /* align text left (default) */
    CPW_FONTOPT_ALIGNUP     = 12, /* align text up */
    CPW_FONTOPT_ALIGNDOWN   = 13, /* align text down */
    CPW_FONTOPT_ALIGNCENTER = 14  /* align text center */
  };
  typedef enum _FontAlignMode FontAlignMode;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Type>                                                                */
  /*    CpwFontFace                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A font face handle. Holds a pointer to the Freetype FT_Face        */
  /*                                                                       */
  typedef pVoid CpwFontFace;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Enum>                                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*     Font file location constants. Used by cpwLoadFont to locate a     */
  /*     font file.                                                        */
  /*                                                                       */
  enum 
  {
    CPW_FONTLOC_HOST                = 1, /* use localhost fonts for search */
    CPW_FONTLOC_RELATIVE            = 2, /* custom path to font directory */
  };
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwLoadFont                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Load a font face into memory. 'fontname' is the file name          */
  /*    of the True Type font. 'location' is either CPW_FONTLOC_HOST       */
  /*    or CPW_FONTLOC_RELATIVE. If CPW_FONTLOC_RELATIVE is specified,     */
  /*    'fontpath' should contains a valid application relative            */
  /*    directory name where the font file is located. If CPW_FONTLOC_HOST */
  /*    is specified, Cpw looks for the font in the localhost's default    */
  /*    font directory if one exists. 'cachelist' should be null.          */
  /*                                                                       */
  CPW_API CpwFontFace    
  cpwLoadFont( pCpw cpw, 
               pChar fontname, 
               uint_32 location, 
               pChar fontpath, 
               pChar cachelist );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwUnloadFont                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Unloads a font face from memory.                                   */
  /*                                                                       */
  CPW_API bool
  cpwUnloadFont( pCpw cpw, CpwFontFace font );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDrawFont                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Draws a font string and advances the raster position.              */
  /*    'string' should be a null terminated string. if 'drawflag'         */
  /*    is true, drawing will occur. If it is false, drawing will          */
  /*    not occur but the raster position will be advanced accordingly.    */
  /*                                                                       */
  /*    Use cpwFontMode to set the FontRenderMode, FontAlignMode and       */
  /*    any FontOption's that apply. CPW_FONTOPT_PIXELMAP is currently     */
  /*    the only render mode supported. You must set the                   */
  /*    CPW_FONTOPT_PIXELMAP_GLFORMAT for rendering pixel map fonts.       */
  /*    CPW_FONTOPT_PIXELMAP_GLFORMAT can be set to any of the valid       */
  /*    OpenGL formats available in the glDrawPixels call.                 */
  /*                                                                       */
  /*    Future support will be available for outline and mesh font render  */
  /*    modes. Use cpwDrawBufferedFont to generate textures for texture    */
  /*    mapped font drawing.                                               */
  /*                                                                       */
  /*    Anyone care to add outline or mesh support? :)                     */
  /*                                                                       */
  CPW_API bool    
  cpwDrawFont( pCpw cpw, 
               CpwFontFace font, 
               pChar string, 
               bool drawflag );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwFontBBox                                                        */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A structure used to hold a font string's bounding box, i.e., the   */
  /*    width and maximum height of the string in pixels. 'offset' is the  */
  /*    space from the lower left of the box to the baseline of the        */
  /*    of the string. The baseline is the 'virtual' line drawn through    */
  /*    the text which all characters in the string rest on.               */
  /*                                                                       */
  struct  _CpwFontBBox
  {
    int_32 width;
    int_32 height;
    int_32 offsetx;
    int_32 offsety;
  };
  typedef struct _CpwFontBBox CpwFontBBox;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwGetFontBBox                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Fills a CpwFontBBox with the specified string's dimensions based   */
  /*    on the current font options and alignment.                         */
  /*                                                                       */
  CPW_API bool    
  cpwGetFontBBox( pCpw cpw, 
                  CpwFontFace font, 
                  pChar string,
                  CpwFontBBox * bbox );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwFontBuffer                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Used by cpwDrawBufferedFont. Holds a font buffer's information     */
  /*    and buffer data.                                                   */
  /*                                                                       */
  struct _CpwFontBuffer 
  {
    char*   data;     /* buffer */
    uint_32 w;        /* width of buffer based on glformat */
    uint_32 h;        /* height of buffer based on glformat */
    int_32  glformat; /* the glformat of the buffer data */
  };
  typedef struct _CpwFontBuffer CpwFontBuffer;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDrawBufferedFont                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new buffer suitable for holding an image of the string,  */
  /*    and renders the string into the buffer. 'glformat' is a valid      */
  /*    OpenGL format used in glDrawPixels. Pass a vilid pointer to a      */
  /*    CpwFontBuffer structure.                                           */
  /*                                                                       */
  /*    Note! You must free a buffer returned by cpwDrawBufferedFont with  */
  /*    cpwFreeBufferedFont.                                               */
  /*                                                                       */
  CPW_API bool    
  cpwDrawBufferedFont( pCpw cpw, 
                       CpwFontFace font, 
                       pChar string,
                       CpwFontBuffer * buffer );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwFreeBufferedFont                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Frees the data contained within a CpwFontBuffer by calling cpwfree */
  /*    on the buffer's 'data' member.                                     */
  /*                                                                       */
  CPW_API bool    
  cpwFreeBufferedFont( pCpw cpw, 
                       CpwFontBuffer * buffer );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions and definitions                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN
#include CPW_FREETYPE_H /* freetype main include header */
/* #include FT_GLYPH_H  needed for bounding box calculations */

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwFontState                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwFontState 
  {
    FT_Library      library;
    FontRenderMode  renderMode;
    uint_32         fontSize;
    FontAlignMode   alignMode;
    bool            kerning;
    bool            layoutdebug;
    int_32          spacingMulti;
    GLenum          pixmap_format;
    int_32          screenWidth;
    int_32          screenHeight;
    char*           pixelbuffer;
    uint_32         pixelbuffersize;
  };
  typedef struct _CpwFontState CpwFontState;
  /*                                                                       */
  /*************************************************************************/

  bool cpw_font_init( pCpw cpw );
  void cpw_font_exit( pCpw cpw );
  void cpw_font_pixelmap_convertfree( CpwFontState * cfs );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif


