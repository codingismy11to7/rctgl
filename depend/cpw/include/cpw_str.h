/***************************************************************************/
/*                                                                         */
/*  cpw_str.h                                                              */
/*                                                                         */
/*    Null safe, Unicode safe string library for Cpw. Feel free to use     */
/*    independantly of Cpw. Relies on opensl.                              */
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

/***************************************************************************/
/*                                                                         */
/*  Example use:                                                           */
/*                                                                         */
/*    pStr s = null;                                                       */
/*    setString( &s, "Hello" );                                            */
/*    freeStr( &s );                                                       */
/*                                                                         */
/***************************************************************************/

#ifndef __cpw_str_h__
#define __cpw_str_h__

#include "cpw_config.h"
#include "cpw_opensl.h"

CPW_BEGIN_HEADER

#define STRBUF 1024 /* used in value conversions */

  /*************************************************************************/
  /*                                                                       */
  /* <Define>                                                              */
  /*    Memory allocation wrappers for this library.                       */
  /*                                                                       */
  #define strMalloc( size )       (char*)cpwmalloc( size )
  #define strRealloc( p, size )   (char*)cpwrealloc( p, size )
  #define strFree( p )            cpwfree( p )
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Define>                                                              */
  /*    String std lib functions safe for whatever string type you are     */
  /*    using.                                                             */
  /*                                                                       */
  #if defined(UNICODE) | defined(_UNICODE)
  #define altstrlen wstrlen
  #else
  #define altstrlen strlen
  #endif
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    StringContext                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A structure used in storing a string and it's length.              */
  /*                                                                       */
  struct _StringContext {
    char*      str;
    uint_32    len;
  };
  typedef struct _StringContext StringContext;
  typedef StringContext* pStr;
  /*                                                                       */
  /*************************************************************************/

/* internal : string context allocation function */

static pStr newString( void ); 

/* create a new string context */

static pStr 
crtStr( void ) 
{
    pStr sc;
    sc = newString();
    if ( sc == null ) return null;

    sc->len = 0;
    sc->str = 0;

    return sc;
}

/* create an empty string context of length len */

static pStr
crtStrLen( uint_32 len )
{
    pStr sc;
    sc = newString();
    if ( sc == null ) return null;

    sc->len = 0;
    sc->str = 0;

    if ( sc->len == 0 )
	    return sc;

    sc->len = len;
    sc->str = strMalloc(sc->len+1);
    memset( sc->str, 0, sc->len+1 );
    sc->str[sc->len+1] = '\0';

    return sc;
}

/* frees the string and destroys it's context */

static void
freeStr( pStr* psc ) 
{
    if ( psc == null ) return; /* not a valid pointer */
    if ( (*psc) == null ) return; /* no context to free */

    if ( (*psc)->str != null ) {
        strFree( (*psc)->str );
        (*psc)->str = 0;
    }

    strFree( *psc ); /* free the context */
    *psc = 0;
}

/* free's the string resources, but not the string context. */

static void
strClr( pStr sc ) 
{
    if ( sc == null ) return;
    strFree( sc->str );
    sc->len = 0;
    sc->str = 0;
}

/* creates a string context containing the contents of a pStr string passed in */

static pStr
strCpy( pStr str )
{
    pStr sc;

    sc = newString();
    if ( sc == null ) return null;

    sc->len = 0;
    sc->str = 0;

    if ( str == null )      return sc;
    if ( str->str == null ) return sc;
    if ( str->len == 0 )    return sc;

    sc->len = str->len;
    sc->str = strMalloc(str->len+1);
    memcpy(sc->str, str->str, str->len);
    sc->str[sc->len] = '\0';

    return sc;
}

/* creates a string context containing a copy of a char* string passed in */

static pStr
cpyString( char* b )
{
    pStr sc;
    int len;

    sc = newString();
    if ( sc == null ) return null;

    sc->len = 0;
    sc->str = 0;

    if ( b == null ) return sc;

    len = altstrlen( b );
    if ( len == 0 ) return sc;

    sc->len = len;
    sc->str = strMalloc(len+1);
    memcpy(sc->str, b, len);
    sc->str[sc->len] = '\0';

    return sc;
}

/* creates a string context and copies inlen chars of a char* string into it */

static pStr
cpyStrLen( pStr in, uint_32 inlen )
{
    pStr sc;

    sc = newString();
    if ( sc == null ) return null;

    sc->len = 0;
    sc->str = 0;

    if ( in == 0 )      return sc;
    if ( inlen == 0 )   return sc;
    if ( in->len == 0 ) return sc;

    if ( inlen > in->len ) 
        inlen = in->len;        

    sc->len = inlen;
    sc->str = strMalloc(sc->len+1);
    memcpy(sc->str, in->str, sc->len);
    sc->str[sc->len] = '\0';

    return sc;
}

/* creates a string context and copies inlen chars of a char* string into it */

static pStr
cpyStringLen( char* b, uint_32 inlen )
{
    pStr sc;

    sc = newString();
    if ( sc == null ) return null;

    sc->len = 0;
    sc->str = 0;
    /* what if strlen( b ) < inlen ? well, b might be a buffer, so it's up to them to check. */
    if ( inlen == 0 ) return sc;

    sc->len = inlen;
    sc->str = strMalloc(sc->len+1);
    memcpy(sc->str, b, sc->len);
    sc->str[sc->len] = '\0';

    return sc;
}

/* copies a pStr's contents to another pStr */

static void 
setStr( pStr* psc, pStr sc ) 
{
    if ( psc == null ) return;

    if ( *psc != null ) {
        freeStr( psc );
    }

    *psc = strCpy( sc );
}

/* copies a char* string to a pStr */

static void 
setString( pStr* psc, char * s ) 
{
    if ( psc == null ) return;

    if ( *psc != null ) {
        freeStr( psc );
    }

    *psc = cpyString( s );
}

/* increase a string context to size len. pass in a pointer to 
   a pStr so the original can be set. */

static uint_32
sizeStr( pStr* psc, int_32 len )
{
    /* create a context if needed */
    if ( *psc == null ) {
        (*psc) = newString();

        (*psc)->len = 0;
        (*psc)->str = 0;
    }

    if ( len <= 0 ) return 0;

    if ( (*psc)->len == 0 ) {
        (*psc)->len = len;
        (*psc)->str = strMalloc((*psc)->len+1);
        memset( (*psc)->str, 0, (*psc)->len+1 );
    } else {
        /* regardless of down sizing or upsizing (may change sc address) */
        (*psc)->len = len;
        (*psc)->str = strRealloc((*psc)->str, (*psc)->len+1);
        memset( (*psc)->str, 0, (*psc)->len+1 );
    }

    /* return the length */
    return (*psc)->len;
}

/* return the string for pStr */

static char* 
getString( pStr a ) 
{
    if ( a == null ) return null;
    return a->str;
}

/* return the string for pStr */

static char* 
str( pStr a ) 
{
    if ( a == null ) return null;
    return a->str;
}

/* return the length for pStr */

static uint_32
len( pStr a ) 
{
    if ( a == null ) return 0;
    return a->len;
}

/* return the string for pStr */

static uint_32
strLen( pStr a ) 
{
    if ( a == null ) return 0;
    return a->len;
}

/* return the char at index for pStr */

static char 
getChar( pStr sc, uint_32 pos ) 
{
    if ( sc->str == null ) return (char)0x00;

    if ( pos <= sc->len && pos >= 0 ) {
        return sc->str[pos];
    } else {
        return (char)0x00;
    }
}

/* set character at pos equal to c in pStr */ 

static bool 
setChar( pStr sc, uint_32 pos, char c ) 
{
    if ( sc == null ) return false;

    if ( pos <= sc->len && pos >= 0 ) {
        sc->str[pos] = c;
        return true;
    }

    return false;
}

/* delete character at index in pStr */

static bool 
delChar( pStr* psc, uint_32 index ) 
{
    pStr sc;
    uint_32 i;

    /* not a valid pointer to a string context pointer */
    if ( psc == null ) return false;

    sc = *psc;

    /* not a valid string context */
    if ( sc == null ) return false;

    /* index is longer than sc's length */
    if ( index > sc->len ) return false;

    /* shift down contents removing char at index */
    i = 0;
    for( i = index; i <= sc->len; i++ )
        *(sc->str+i) = (char)*(sc->str+i+1); 

    /* set the last char to null */
    *(sc->str + sc->len) = '\0';

    /* we do not deallocate the character's memory at the end, we simply decrease the length by one */
    sc->len--;

    return true;
}

/* drop the ending character off pStr */

static bool
dropChar( pStr* psc )
{
    pStr sc;
    pStr copy;

    if ( psc == null ) return false;

    /* use the original context */
    sc = *psc;

    /* nothing to drop */
    if ( sc->len <= 0 ) return true;

    /* create a copy of the string minus one char (creates a new string stored in copy) */
    copy = cpyStrLen( sc, sc->len-1 );

    /* delete the original context and string */
    freeStr( &sc );
    sc = 0;

    /* set the incoming context pointer to the new context */
    *psc = copy;

    return true;
}

/* returns a new context containing a copy of the sub-string starting 
   at startpos, ending at endpos */

static pStr 
subStr( pStr sc, uint_32 start, int_32 end ) 
{
    pStr sub = null;
    int_32 len;

    if ( sc == null ) return newString();

    if ( start > sc->len ) return newString();

    if ( end == -1 ) end = sc->len - start;

    if ( end > (int_32)sc->len ) end = sc->len - start;

    len = end-start;

    if ( len < 0 ) len = 0;

    sizeStr( &sub, len ); /* adds hidden char on the end! */

    memcpy( sub->str, sc->str+start, len ); 
    
    return sub;
}

/* returns a new context containing a copy of the sub-string 
   starting at start, ending at the end of pStr */

static pStr 
subStrShort( pStr sc, uint_32 start ) 
{
    pStr sub = null;
    int_32 len;

    if ( sc == null ) return newString();

    if ( start > sc->len ) return newString();

    len = sc->len - start;

    if ( len < 0 ) len = 0;

    sizeStr( &sub, len ); /* adds hidden char on the end! */

    memcpy( sub->str, sc->str+start, len ); 
    
    return sub;
}

/* returns a new context containing a copy of the sub-string 
   starting at start for length of len */

static pStr 
subStrLen( pStr sc, uint_32 start, uint_32 len ) 
{
    pStr sub = null;

    //start = 0, len = 10, sc->len = 5  : len = 10
    //start = 5, len = 10, sc->len = 10 : len = 5

    if ( sc == null ) return newString();

    if ( start > sc->len ) return newString();

    if ( (start + len) > sc->len  ) len = sc->len - start;

    sizeStr( &sub, len ); /* adds hidden char on the end! */

    memcpy( sub->str, sc->str+start, len ); 
    
    return sub;
}

static pStr 
strToken( pStr * string, char* key )
{
    int_32 index;
    pStr tmp;
    pStr token;

    if ( string == null ) return false;
    if ( *string == 0 ) return false;
    if ( (*string)->len == 0 ) return false;
    if ( key == null ) return false;

    /* get the last chunk which i assumed to not have a key on the end */

    if ( ( index = slFind( str( *string ), key ) ) <= 0 ) {
        tmp = strCpy( *string );
        freeStr( string );
        return tmp;
    }

    token = subStr( *string, 0, index );
    tmp = subStrShort( *string, index+1 );
    setStr( string, tmp );
    freeStr( &tmp );
    return token;
}

/* concatinate src onto the end of target */

static bool
concatStr( pStr* target, pStr src )
{
    uint_32 tlen;
    uint_32 slen;
    char * p;

    if ( target == null || src == null ) return false;

    if ( *target == null ) *target = newString();

    tlen = (*target)->len;
    slen = src->len;

    if ( slen <= 0 ) return true;

    if ( tlen == 0 ) {
        *target = strCpy( src );
    } else {
        p = slAppend( (*target)->str, src->str );
        freeStr( target );
        setString( target, p );
        slFree( p );  
    }

    return true;
}

/* concatinate src onto the end of target */

static bool
concatString( pStr* target, char * src )
{
    uint_32 tlen;
    uint_32 slen;
    char * p;

    if ( target == null || src == null ) return false;

    if ( *target == null ) *target = newString();

    tlen = (*target)->len;
    slen = slLength( src );

    if ( slen == 0 ) return true;

    if ( tlen == 0 ) {
        freeStr( target );
        *target = cpyString( src );
    } else {
        p = slAppend( (*target)->str, src ); /* creates a new string in p */
        freeStr( target );
        setString( target, p ); /* creates a new string in target */
        slFree( p );  
    }

    return true;
}

/* concatinate src(s) onto the end of target. You must
   have the last string = "\0" */

static bool
concatStrings( pStr* target, char * src, ... )
{
    va_list marker;
    uint_32 tlen;
    uint_32 slen;
    char * p;

    if ( target == null || src == null ) return false;

    if ( *target == null ) *target = newString();

    va_start( marker, src );     /* Initialize variable arguments. */
    while( src != null )
    {
        slen = slLength( src );
        tlen = (*target)->len;

        if ( slen == 0 ) break;

        if ( (*target)->len == 0 ) {
            freeStr( target );
            *target = cpyString( src );
        } else {
            //sizeStr( target, tlen+slen ); /* adds hidden char on the end. */
            //memcpy( (*target)->str + tlen, src, slen );
            p = slAppend( (*target)->str, src );
            freeStr( target );
            setString( target, p );
            slFree( p );  
        }
        src = va_arg( marker, char* );
    }
    va_end( marker );              /* Reset variable arguments.      */

    return true;
}

/* concatinate src onto the end of target for a total len */

static bool
concatStringLen( pStr* target, char * src, uint_32 len )
{
    uint_32 tlen;
    uint_32 slen;

    if ( target == null || src == null ) return false;

    if ( *target == null ) *target = newString();

    tlen = (*target)->len;
    slen = slLength( src );

    if ( slen <= 0 ) return true;

    sizeStr( target, tlen+slen ); /* adds hidden char on the end. */
    
    memcpy( (*target)->str + tlen, src, slen );

    return true;
}

/* concatinate a charcter onto the end of target */

static bool 
concatChar( pStr* target, char c )
{
    char buf[1];

    buf[0] = c;
    buf[1] = 0;

    return concatString( target, buf );
}

#define appendStr concatStr
#define appendString concatString

/* memcmp wrapper with a little bit o fudge - case sensitive */

static int_32 
compareStrCs( pStr a, pStr b )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b->str == null ) return 0;

    if ( a->str == null || b->str == null ) return -1;

    return memcmp( a->str, b->str, a->len );
}

/* strncmp wrapper - case sensitive */

static int_32 
compareStrLenCs( pStr a, pStr b, uint_32 len )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b->str == null ) return 0;

    if ( a->str == null || b->str == null ) return -1;

    return memcmp( a->str, b->str, len );
}

/* strncmp wrapper - case sensitive */

static int_32 
compareStringLenCs( pStr a, char* b, uint_32 len )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b == null ) return 0;

    if ( a->str == null || b == null ) return -1;

    return memcmp( a->str, b, len );
}

/* strcmp wrapper with a little bit o fudge - case sensitive */

static int_32 
compareStrNc( pStr a, pStr b )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b->str == null ) return 0;

    if ( a->str == null || b->str == null ) return -1;

    return _memicmp( a->str, b->str, a->len );
}

/* strncmp wrapper - case insensitive */

static int_32 
compareStringNc( pStr a, char* b )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b == null ) return 0;

    if ( a->str == null || b == null ) return -1;

    return _memicmp( a->str, b, a->len );
}

/* strncmp wrapper - case insensitive */

static int_32 
compareStrLenNc( pStr a, pStr b, uint_32 len )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b->str == null ) return 0;

    if ( a->str == null || b->str == null ) return -1;

    return _memicmp( a->str, b->str, len );
}

/* strncmp wrapper - case insensitive */

static int_32 
compareStringLenNc( pStr a, char* b, uint_32 len )
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return -1;

    if ( a->str == null && b == null ) return 0;

    if ( a->str == null || b == null ) return -1;

    return _memicmp( a->str, b, len );
}

/* replace all instances of token with replace in target */

static int_32 
replaceString( pStr* target, char* token, char* replace )
{
    char* newstr;
    
    if ( token == null || replace == null ) 
        return -1;

    if ( target == null || (*target)->len <= 0 ) 
        return 0;

    if ( memcmp( token, replace, (slLength(token) > slLength(replace) ? slLength(token):slLength(replace)) ) == 0 ) {
        return -1;
    } 

    newstr = slReplace( (*target)->str, token, replace ); 
    setString( target, newstr );
    strFree( newstr );

    return 1;
}

/* Simple, straight forward sub string search.  
   returns -1 if not found, 'starting character 
   position' for sub string is returned. */

static int_32
containsStr( pStr a, pStr b )		
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return 0;

    if ( a->str == null || b->str == null ) return 0;

    return slFind( str( a ), str( b ) );
}

/* Simple, straight forward sub string search.  
   returns -1 if not found, 'starting character 
   position' for sub string is returned. */

static int_32
containsString( pStr a, char* b )		
{
    if ( a == null && b == null ) return 0;

    if ( a == null || b == null ) return 0;

    if ( a->str == null ) return 0;

    return slFind( str( a ), b );
}

/* convert pStr to int32 value */

static int_32 
strToInt32( pStr a )		
{
    if ( a == null ) return 0;

    if ( a->str == null ) return 0;

    return atoi( str( a ) );
}

/* convert pStr to double value */

static float_64 
strToFloat64( pStr a )		
{
    if ( a == null ) return 0;

    if ( a->str == null ) return 0;

    return atof( str( a ) );
}

/* convert int32 value to pStr string */

static pStr 
int32ToStr( int_32 value )		
{
    pStr str;
    char buf[STRBUF];

    str = newString();
    sprintf( buf, "%i", value );

    setString( &str, buf ); 
    return str;
}

/* convert double value to pStr string */

static pStr 
float64ToStr( float_64 value )		
{
    pStr str;
    char buf[STRBUF];

    str = newString();
    sprintf( buf, "%i", value );

    setString( &str, buf ); 
    return str;
}

/* internal : string context allocation function */

static pStr 
newString( void )
{
    pStr p;
    p = (pStr)strMalloc( sizeof( StringContext ) );
    if ( p == null ) return null;
    return (pStr)memset( (void*)p, 0, sizeof( StringContext ) );
}

/* don't clutter or conflict with anything - string lib use only */
#undef strMalloc
#undef strRealloc
#undef strFree

CPW_END_HEADER
#endif
