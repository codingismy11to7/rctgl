/*********************************************************************
**
** OpenSL - the open string library
**
** Goals:
** - provide basic functions for common high-level string operations
** - platform independent (pure ANSI C)
** - unicode compliance
** - small , simple, reliable
** - use OpenGL naming conventions
** - easy for scripting langauges to use
**
** Non-Goals:
** - extremely high performance
**
** ToDo:
** - test for NULLs as arguments
** - test for failed mallocs
** - add sl wrappers for standard string lib functions???
**
** Notes:
** - all platform dependent functions are labeled and located
**   at the top of the opensl.c file
** - all functions returning a char * are returning newly allocated
**   strings which the caller is responsible for freeing.
**
** Author:
** - Steve Dekorte (www.dekorte.com)
**
** Contrib:
** - Jim Mathies (www.mathies.com)
**
**********************************************************************/

#ifndef OpenSL
#define OpenSL

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <memory.h>
#define slmalloc( size ) ((char*)malloc( size ))
#define slfree( p ) free( p )

#ifndef NULL
#define NULL 0
#endif
#define CHARSIZE 1 /* 1 byte per character */

/****************************************************
** unicode or non-unicode str functions.
****************************************************/
#if defined(UNICODE) | defined(_UNICODE)
#define slstrlen wstrlen
#define sltoupper towupper
#define sltolower towlower
#else
#define slstrlen strlen
#define sltoupper toupper
#define sltolower tolower
#endif

/****************************************************
** platform dependent - replace implementations with
** platform specific unicode calls.
****************************************************/

int slLength(char *s);
void slFree(char *s);
void slClear(char *s);

/****************************************************
** string creation
****************************************************/

char *slStringFromBuffer(void* buf, int size);
char *slSizeTo(char *s, int inLen);
char *slCopy(char *s);
char *slStringOfSize(int size);

/****************************************************
** character operations
** unicode may mess with these...
****************************************************/

char slCharAt(char *s, int pos );
int slSetCharAt(char *s, int pos, char c );
void slDropLastChar(char *s);
void slDropCharAt(char *s, int pos );

/****************************************************
** string modification operations
** new string is returned that caller must free
****************************************************/

char *slAppend(char *s, char *s2);
char *slAppendAndFree(char *s, char *s2);
char *slPreppend(char *s, char *s2);
char *slSubString(char *s, int startpos, int endpos );
char *slInsert(char *s, char *s2, int pos );
char *slLower(char *s);
char *slUpper(char *s);
char *slReplace( char *s, char *s2, char *s3 );

/****************************************************
** string comparision operations
****************************************************/

int slEquals( char *s, char *s2 );
int slEqualsAnyCase( char *s, char *s2 );
int slContains( char *s, char *s2 );
int slContainsAnyCase( char *s, char *s2 );
int slFind( char *s, char *s2 );
int slFindAnyCase( char *s, char *s2 );
int slFindFrom( char *s, char *s2, int from );
int slRFindFrom( char *s, char *s2, int from);
int slFindAnyCaseFrom( char *s, char *s2, int from );
int slCount( char *s, char *s2 );

/****************************************************
** private utility functions
****************************************************/

int slWrapPos(char *s, int pos);

#ifdef __cplusplus
}
#endif

#endif
