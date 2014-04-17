/***************************************************************************/
/*                                                                         */
/*  LibTarga                                                               */
/*                                                                         */ 
/*  Adapted from:                                                          */
/*                                                                         */
/*  http://www.cs.wisc.edu/graphics/Gallery/LibTarga/                      */
/*                                                                         */
/*  Truecolor images supported:                                            */
/*                                                                         */
/*    bits            breakdown   components                               */
/*    --------------------------------------                               */
/*    32              8-8-8-8     RGBA                                     */
/*    24              8-8-8       RGB                                      */
/*    16              5-6-5       RGB                                      */
/*    15              5-5-5-1     RGB (ignore extra bit)                   */
/*                                                                         */
/*    Paletted images supported:                                           */
/*                                                                         */
/*    index size      palette entry   breakdown   components               */
/*    ------------------------------------------------------               */
/*    8               <any of above>  <same as above> ..                   */
/*    16              <any of above>  <same as above> ..                   */
/*    24              <any of above>  <same as above> ..                   */
/*                                                                         */
/*    Targa files are read in and converted to                             */
/*    any of these three for you -- you choose which you want.             */
/*                                                                         */
/*    This is the 'format' argument to tga_create/load/write.              */
/*                                                                         */
/*    For create and load, format is what you want the data                */
/*    converted to.                                                        */
/*                                                                         */
/*    For write, format is what format the data you're writing             */
/*    is in. (NOT the format you want written)                             */
/*                                                                         */
/*    Only TGA_TRUECOLOR_32 supports an alpha channel.                     */
/*                                                                         */
/*    Image data will start in the low-left corner                         */
/*    of the image.                                                        */
/*                                                                         */
/*  File Platform: cross                                                   */
/*                                                                         */
/***************************************************************************/

#ifndef _libtarga_h_
#define _libtarga_h_

#include "cpw_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* some libtarga -> Cpw type conversions */

#ifndef uint32
#define uint32 uint_32
#endif
#ifndef int32
#define int32 int_32
#endif
#ifndef int16
#define int16 int_16
#endif
#ifndef uint16
#define uint16 uint_16
#endif
#ifndef ubyte
#define ubyte unsigned char
#endif
#ifndef uchar
#define uchar char
#endif

/* endianess */

#ifdef CPW_PLATFORMINFO_LITTLEENDIAN
#else
#define WORDS_BIGENDIAN
#endif

/* malloc alloc and free are piped through cpw's handlers */

#define ltgamalloc    cpwmalloc
#define ltgarealloc   cpwrealloc
#define ltgafree      cpwfree

/* targa format types (color depth) */

#define TGA_TRUECOLOR_32      (4)
#define TGA_TRUECOLOR_24      (3)

/* targa image information descriptor */

struct _TargaInfo 
{
    uint32 height;
    uint32 width;
    uint32 format;
    uint32 TargaError;
    bool error;
};
typedef struct _TargaInfo TargaInfo;

/* #define multipliedalpha see the .c for implications */

/* error description string */

const char* tga_error_string( uint32 TargaError );

/* creating and loading images */

void* tga_create( TargaInfo * ti );
void* tga_load( TargaInfo * ti, const char * filename );
void  tga_info( TargaInfo * ti, const char * filename );

/* writing images to a file  --  a return of 1 indicates success, 0 indicates error */

int tga_write_raw( const char * file, 
                   int width, 
                   int height, 
                   unsigned char * dat, 
                   unsigned int format );

int tga_write_rle( const char * file, 
                   int width, 
                   int height, 
                   unsigned char * dat, 
                   unsigned int format );

#ifdef __cplusplus
}
#endif

#endif /* _libtarga_h_ */

