#include <stdio.h>
#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glaux.h>											// Header File For The GLaux Library

int checkSize (int x);
unsigned char* getRGBA (FILE *s, int size);
unsigned char* getRGB (FILE *s, int size);
unsigned char* getGray (FILE *s, int size);
unsigned char* getData (FILE *s, int sz, int iBits);
int LoadTGAFromFile(char *fname, int texID);
