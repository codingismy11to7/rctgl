/**************************************
*                                     *
*   Jeff Molofee's Basecode Example   *
*          nehe.gamedev.net           *
*                2001                 *
*                                     *
**************************************/

#include "vr3d.h"

//#include <windows.h>											// Header File For Windows
//#include <math.h>
//#include <gl\gl.h>												// Header File For The OpenGL32 Library
//#include <gl\glu.h>												// Header File For The GLu32 Library
//#include <gl\glaux.h>											// Header File For The GLaux Library
#include "NeHeGL.h"												// Header File For NeHeGL
#include "GLFont.h"												// Header File For Font Module
#include "ResourceIO.h"											// Header File For Resource Class Module
#include "resource.h"
#include "bbVertex.h"
#include "skyDome.h"


//#include <dinput.h>

#include "tga1.h"
#include "tga2.h"

//#include "vr-font.h"

//#include "GLFont.h"



#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking
#pragma comment( lib, "glaux.lib" )								// Search For GLaux.lib While Linking

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

#define RCT3DLOGO	0
#define FONTTEX		1

#define WALK_SPEED		6
#define WALK_SPEED_FAST	14
#define FLY_SPEED		10
#define FLY_SPEED_FAST	25


//define existing key codes
#define VK_LEFTARROW	37 
#define VK_RIGHTARROW	39 
#define VK_UPARROW		38 
#define VK_DOWNARROW	40

#define VK_PAGE_UP		33 
#define VK_PAGE_DOWN	34


#define PEEPHEIGHT 1.3

#define PI     3.14159265358979
#define TWOPI  6.28318530717958
#define PIDIV2 1.57079632679489




GLuint texture_id[NUMTEXTURES];
GLenum texFormat;

unsigned int skyTexID;


char RCTGL_Location[256];
char RCTGL_TempFile[256];

extern RenderModes DisplayMode;
RenderModes oldDisplayMode;

extern int fogLevel;
int oldFogLevel;

extern GL_Window			window;

landscape_t parkLandscape[128][128];

extern float RCTColorsR[32];
extern float RCTColorsG[32];
extern float RCTColorsB[32];

extern bool lMousePressed, rMousePressed;

extern HMENU hMenu;

GLuint	base;				// Base Display List For The Font Set



GL_Window*	g_window;
Keys*		g_keys;

// User Defined Variables
float		 angle;												// Used To Rotate The Triangles
GLuint       texture[1];
AUX_RGBImageRec *Texs[1];
GLFont       fNehe;												// Font Class

int TextureLoadProgress;

bool LoadedEdgeTex;
bool LoadedSurfaceTex;
bool LoadedTreeTex;
bool LoadedRideTex;
bool LoadedSkyTex;
bool LoadedPathTex;
bool LoadedWallTex;

bool UncompressedFile;
bool LoadedLandscape;
bool LoadedRides;
bool LoadedTrees;
bool LoadedPaths;
bool LoadedElements;
bool LoadedWalls;

float	rtri;
float	rquad;

float frustum[6][4];		//6 planes - 4 vals per plane

ParkStructType thePark;



extern LPDIRECTINPUT8 lpdi;
extern LPDIRECTINPUTDEVICE8 m_keyboard;
extern LPDIRECTINPUTDEVICE8 g_pMouse;



#define MOUSEBUTTONDOWN(key) (key & 0x80)
#define MOUSEBUTTON_LEFT 0
#define MOUSEBUTTON_RIGHT 1
#define MOUSEBUTTON_MIDDLE 2

bool isMenuVisible = true;
bool escapeKeyDown = false;
bool modeKeyDown = false;
bool tabKeyDown = false;
bool plusKeyDown = false;
bool minusKeyDown = false;

enum NavModes { FreeMode, PeepMode };

struct CanMoveStruct {
	int curX, curZ, curIndex;
	int N, S, E, W;
	int NE, NW, SW, SE;
} CanMove;

NavModes NavMode;

int lastTileX, lastTileZ;

//unsigned char keystate[256];

#define    KeyDown(data, n)    ((data[n] & 0x80) ? true : false)
#define    KeyUp(data, n)    ((data[n] & 0x80) ? false : true)


extern float blendSettings[4];

extern FMUSIC_MODULE *mod;


UINT g_FontListID = 0;

// This will save our old font and select it back in at the end of our program.
// We need this because we use SelectObject() to select in the new font.
// We don't want any memory leaks :)
HFONT hOldFont;

// This define is for the amount of lists we want to create.  There will need to be 1
// for every character.  Since there are 256 ascii characters, we will use 256.
// If we only wanted certain characters used, like alpha numerics, we would give less.
#define MAX_CHARS	256									

// This defines how high we want our font to be
#define FONT_HEIGHT	24


float posVector[3];
float viewVector[3];
float upVector[3];


float g_FrameInterval = 0.0f;


int lastCDTrack;

extern int queueRide;
extern bool inQueue;


double sinTable[360];
double cosTable[360];
double tanTable[360];


AudioStructType AudioSpecifiers[256];
int AudioSpecifierCount;

float ambientRData[17], ambientGData[17], ambientBData[17];
float lightRData[17], lightGData[17], lightBData[17];
GLuint starfieldDisplayListA;	//the small stars
GLuint starfieldDisplayListB;	//the bigger stars
bbVertex sphereCoords[17][19];

int minuteOfDay = 540;
double ambientRValue, ambientGValue, ambientBValue;
double lightRValue, lightGValue, lightBValue;
double lightPos[4] = {1.0f, 0.0f, 0.0f, 0.0f};

bool drawStars = true;
bool drawSky = true;

extern float edgeLighting[4][4];
double calcLightFactor(double n1, double n2, double n3);
extern int itemRot;

skyDome *mySkyDome;

void calcColor(float baseColor[3], float factor, float *r, float *g, float *b)
{
	*r = ambientRValue * baseColor[0] + factor * lightRValue;
	*g = ambientGValue * baseColor[1] + factor * lightGValue;
	*b = ambientBValue * baseColor[2] + factor * lightBValue;
}

double calcLightFactor(double n1, double n2, double n3)
{
	double normalizedVector[3];
	double normalizedLight[3];


	double newLightPos[3];
	newLightPos[0] = cos(itemRot * 3.14f / 180.0f)*lightPos[0] - sin(itemRot * 3.14f / 180.0f)*lightPos[2]; 
	newLightPos[1] = lightPos[1];
	newLightPos[2] = sin(itemRot * 3.14f / 180.0f)*lightPos[0] + cos(itemRot * 3.14f / 180.0f)*lightPos[2]; 
	

	double l = sqrt(n1 * n1 + n2 * n2 + n3 * n3);
	normalizedVector[0] = n1 / l;
	normalizedVector[1] = n2 / l;
	normalizedVector[2] = n3 / l;

	l = sqrt(newLightPos[0] * newLightPos[0] + newLightPos[1] * newLightPos[1] + newLightPos[2] * newLightPos[2]);
	normalizedLight[0] = newLightPos[0] / l;
	normalizedLight[1] = newLightPos[1] / l;
	normalizedLight[2] = newLightPos[2] / l;


	//printf("normalizedVector = {%2.5f, %2.5f, %2.5f}\n", normalizedVector[0], normalizedVector[1], normalizedVector[2]);

	double ret = normalizedVector[0] * normalizedLight[0] +
		 normalizedVector[1] * normalizedLight[1] +
		 normalizedVector[2] * normalizedLight[2];

	if (ret < 0)
		ret = 0;

	return ret;
}



void printBinary(int val)
{
	if(val >= 128)
	{
		val -=128;
		printf("1");
	}
	else
		printf("0");

	if(val >= 64)
	{
		val -=64;
		printf("1");
	}
	else
		printf("0");

	if(val >= 32)
	{
		val -=32;
		printf("1");
	}
	else
		printf("0");

	if(val >= 16)
	{
		val -=16;
		printf("1");
	}
	else
		printf("0");

	if(val >= 8)
	{
		val -=8;
		printf("1");
	}
	else
		printf("0");

	if(val >= 4)
	{
		val -=4;
		printf("1");
	}
	else
		printf("0");

	if(val >= 2)
	{
		val -=2;
		printf("1");
	}
	else
		printf("0");

	if(val >= 1)
	{
		val -=1;
		printf("1");
	}
	else
		printf("0");
}


void LoadNames(char *filename)
{
	FILE *input;

	input = fopen(filename, "rb");

	if(input == NULL)
		perror("fopen\n");

	int i;

	//for(i=0; i<256; i++)
	//	printf("stringindex for ride %d = %d\n", i, thePark.rides[i].nameStringOffset);

	for(i=0; i<1024; i++)
	{
		fseek(input, (i * 32) + 0x19B89C, SEEK_SET);
		fread(&thePark.nameStrings[i][0], 1, 32, input);
	}
	
	for(i=0; i<1024; i++)
	{
		if(thePark.nameStrings[i][0] > ' ')
		{
			printf("string #%d: %s\n", i, &thePark.nameStrings[i]);
			int tmp = strlen(thePark.nameStrings[i]);
			printf("len = %d\n", tmp);
			thePark.nameStrings[i][tmp] = NULL;

			//for(int i=0; i<tmp; i++)
			//printf("%c(%d) ", thePark.nameStrings[RideList[i].nameStringOffset][i], thePark.nameStrings[RideList[i].nameStringOffset][i]);

			//printf("\n");
		}
	}
}

void CalculateFrameRate()
{
	static float framesPerSecond    = 0.0f;		// This will store our fps
    static float lastTime			= 0.0f;		// This will hold the time from the last frame
	static char strFrameRate[50] = {0};			// We will store the string here for the window title


	static float frameTime = 0.0f;				// This stores the last frame's time

	// Get the current time in seconds.  Notice that we use timeGetTime() instead
	// of GetTickCount().  This is because on some computers, depending on their
	// CPU, GetTickCount() does update as fast or correctly as clock().  You need
	// to include <mmsystem.h> to use this function.  You will also need to include 
	// winmm.lib and mmsystem.h in your code.
    float currentTime = timeGetTime() * 0.001f;				

	// Here we store the elapsed time between the current and last frame,
	// then keep the current frame in our static variable for the next frame.
 	g_FrameInterval = currentTime - frameTime;
	frameTime = currentTime;

	// Increase the frame counter
    ++framesPerSecond;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
    if( currentTime - lastTime > 1.0f )
    {
		// Here we set the lastTime to the currentTime
	    lastTime = currentTime;
		
		// Copy the frames per second into a string to display in the window title bar
		sprintf(strFrameRate, "Current Frames Per Second: %d", int(framesPerSecond));

		// Set the window title bar to our string
		SetWindowText(window.hWnd, strFrameRate);

		// Reset the frames per second
        framesPerSecond = 0;
    }
}



UINT CreateOpenGLFont(LPSTR strFontName, int height)	// Build Our Bitmap Font
{
	UINT	fontListID = 0;								// This will hold the base ID for our display list
	HFONT	hFont;										// This will store the handle to our font

	// Here we generate the lists for each character we want to use.
	// This function then returns the base pointer, which will be 1 because
	// we haven't created any other lists.  If we generated another list after
	// this, the base pointer would be at 257 since the last one used was 256 (which is MAX_CHARS)
	fontListID = glGenLists(MAX_CHARS);					// Generate the list for the font

	// Now we actually need to create the font.  We use a windows function called:
	// CreateFont() that returns a handle to a font (HFONT).  Our CreateOpenGLFont()
	// function allows us to pass in a name and height.  For simplistic reasons, I left
	// other options out, but feel free to add them to your function (like bold, italic, width..)

	hFont = CreateFont(	height,							// Our desired HEIGHT of the font
						0,								// The WIDTH (If we leave this zero it will pick the best width depending on the height)
						0,								// The angle of escapement
						0,								// The angle of orientation
						FW_BOLD,						// The font's weight (We want it bold)
						FALSE,							// Italic - We don't want italic
						FALSE,							// Underline - We don't want it underlined
						FALSE,							// Strikeout - We don't want it strikethrough
						ANSI_CHARSET,					// This is the type of character set
						OUT_TT_PRECIS,					// The Output Precision
						CLIP_DEFAULT_PRECIS,			// The Clipping Precision
						ANTIALIASED_QUALITY,			// The quality of the font - We want anitaliased fonts
						FF_DONTCARE|DEFAULT_PITCH,		// The family and pitch of the font.  We don't care.
						strFontName);					// The font name (Like "Arial", "Courier", etc...)

	// Now that we have created a new font, we need to select that font into our global HDC.
	// We store the old font so we can select it back in when we are done to avoid memory leaks.
	hOldFont = (HFONT)SelectObject(window.hDC, hFont);

	// This function does the magic.  It takes the current font selected in
	// the hdc and makes bitmaps out of each character.  These are called glyphs.
	// The first parameter is the HDC that holds the font to be used.
	// The second parameters is the ASCII value to start from, which is zero in our case.
	// The third parameters is the ASCII value to end on (255 is the last of the ASCII values so we minus 1 from MAX_CHARS)
	// The last parameter is the base pointer for the display lists being used.  This should be 1.

	wglUseFontBitmaps(window.hDC, 0, MAX_CHARS - 1, fontListID);	// Builds 255 bitmap characters

	return fontListID;									// Return the ID to the display list to use later
}

///////////////////////////////// POSITION TEXT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function sets the drawing position for the text
/////
///////////////////////////////// POSITION TEXT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void PositionText( int x, int y )
{
	// If you are to use this font code for your applications,
	// you must be aware that you cannot position the font in 3D,
	// which means you can't rotate and scale it.  That will be covered in
	// the next font tutorial.  BUT, though that might be a drag, this code
	// is useful because when you display the text, it will always be on top
	// of everything else.  This is good if the camera is moving around, and you
	// don't want the text to move.  If the text was positioned in 3D you would have
	// to come up with a tricky way of making it always render in front of the camera.
	// To do this, we need to set the Raster Position.  That is the position that OpenGL
	// starts drawing at.  Since it's in floating point, it's not very intuitive, so what
	// we do is create a new view port, and then always draw the text at (0, 0, 0) in that
	// view port.  The weird part is that the Y is flipped, so (0, 0) is the bottom left corner.
	// Below we do some simple math to flip it back to normal.

	// Before we create a new view port, we need to save the current one we have.
	// This saves our transform (matrix) information and our current viewport information.
	// At the end of this function we POP it back.
	glPushAttrib( GL_TRANSFORM_BIT | GL_VIEWPORT_BIT );

	// Here we use a new projection and modelview matrix to work with.
	glMatrixMode( GL_PROJECTION );						// Set our matrix to our projection matrix
	glPushMatrix();										// Push on a new matrix to work with
	glLoadIdentity();									// reset the matrix
	glMatrixMode( GL_MODELVIEW );						// Set our matrix to our model view matrix
	glPushMatrix();										// Push on a new matrix to work with
	glLoadIdentity();									// Reset that matrix

	// Because the Y is flipped, we want 0 to be at the top, not bottom.
	// If we subtract the font height from the screen height, that should display the
	// font at the top of the screen (if they passed in 0 for Y), but then we subtract
	// the Y from that to get the desired position.  Since the font's drawing point is
	// at the base line of the font, we needed to subtract the font height to make sure
	// if they passed in (0, 0) it wouldn't be off screen.  If you view this in window mode,
	// the top of the window will cut off part of the font, but in full screen it works fine.
	// You just need to add about 25 to the Y to fix that for window mode.

	y = 480 - FONT_HEIGHT - y;				// Calculate the weird screen position

	// Now we create another view port (that is why we saved the old one above).
	// Since glViewPort takes the lower LEFT corner, we needed to change the Y
	// to make it more intuitive when using PositionText().  We minus 1 from the X and Y
	// because 0 is taken into account with the position.  The next 2 parameters are set
	// to 0 for the width and height so it will always draw in the middle of that position.
	// glRasterPos4f() takes (0, 0, 0) as the middle of the viewport, so if we give it a small
	// width/height it will draw at the X and Y given.  Sounds strange, to test this, try
	// using glRasterPos4f(0, 0, 0, 1) instead of PositionText() and you will see, everything
	// will be drawn from the middle.

	glViewport( x - 1, y - 1, 0, 0 );					// Create a new viewport to draw into

	// This is the most important function in here.  This actually positions the text.
	// The parameters are (x, y, z, w).  w should always be 1 , it's a clip coordinate.
	// don't worry about that though.  Because we set the projection and modelview matrix
	// back to the beginning (through LoadIdentity()), the view port is looking at (0, 0, 0).
	// This is the middle, so if we set the drawing position to the middle, it will draw at our
	// X and Y because the width/height of the viewport is 0, starting at X and Y.
	// You can actually call this function (or glRasterPos2f(0, 0)) instead of PositionText(),
	// but it is in floating point and doesn't work as nicely.  You will see why if you try.

	glRasterPos4f( 0, 0, 0, 1 );						// Set the drawing position

	// Now that we positioned the raster position, any text we draw afterwards will start
	// from that position.  Now we just have to put everything else back to normal.

	glPopMatrix();										// Pop the current modelview matrix off the stack
	glMatrixMode( GL_PROJECTION );						// Go back into projection mode
	glPopMatrix();										// Pop the projection matrix off the stack

	glPopAttrib();										// This restores our TRANSFORM and VIEWPORT attributes
}


///////////////////////////////// GL DRAW TEXT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This draws 2D text onto the screen using OpenGL, given an X and Y position 
/////
///////////////////////////////// GL DRAW TEXT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void glDrawText(int x, int y, const char *strString, ...)
{
	char		strText[256];							// This will hold our text to display
	va_list		argumentPtr;							// This will hold the pointer to the argument list

	// If you have never used a va_list, listen up.  Remember printf()?
	// or sprintf()?  Well, you can add unlimited arguments into the text like:
	// printf("My name is %s and I am %d years old!", strName, age);
	// Well, that is what va_list's do.  

	// First we need to check if there was even a string given
	if (strString == NULL)								// Check if a string was given
		return;											// Don't render anything then

	// First we need to parse the string for arguments given
	// To do this we pass in a va_list variable that is a pointer to the list of arguments.
	// Then we pass in the string that holds all of those arguments.
	va_start(argumentPtr, strString);					// Parse the arguments out of the string

	// Then we use a special version of sprintf() that takes a pointer to the argument list.
	// This then does the normal sprintf() functionality.
	vsprintf(strText, strString, argumentPtr);			// Now add the arguments into the full string

	va_end(argumentPtr);								// This resets and frees the pointer to the argument list.

	// Before we draw the text, we need to position it with our own function.
	PositionText(x, y);									// Call our own function to position the text on screen

	// Now, before we set the list base, we need to save off the current one.
	glPushAttrib(GL_LIST_BIT);							// This saves the list base information

	// Then we want to set the list base to the font's list base, which should be 1 in our case.
	// That way when we call our display list it will start from the font's lists'.
	glListBase(g_FontListID);							// This sets the lists base

	// Now comes the actually rendering.  We pass in the length of the string,
	// then the data types (which are characters so its a UINT), then the actually char array.
	// This will then take the ASCII value of each character and associate it with a bitmap.
	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);

	glPopAttrib();										// Return the display list back to it's previous state
}


///////////////////////////////// DESTROY FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function frees our display lists
/////
///////////////////////////////// DESTROY FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void DestroyFont()										
{
	glDeleteLists(g_FontListID, MAX_CHARS);				// Free the display list
	SelectObject(window.hDC, hOldFont);						// Select the old font back in so we don't have memory leaks
}

void runReport()
{
	FILE * logfile;
	int i,j,k;
	
	logfile=fopen("f:\\log.out", "w");
	
	for(i=0;i<128;i++)
		for(j=0;j<128;j++)
			if(thePark.paths[i][j].size() > -1)
				fprintf(logfile, "pathCount[%d][%d] = %d\n", i, j, thePark.paths[i][j].size());

	for(i=0;i<128;i++)
		for(j=0;j<128;j++)
			if(thePark.trees[i][j].size() > -1)
				fprintf(logfile, "treeCount[%d][%d] = %d\n", i, j, thePark.trees[i][j].size());

	fprintf(logfile, "\n\nDuplicate path report\n");

	for(i=0;i<128;i++)
		for(j=0;j<128;j++)
			if(thePark.paths[i][j].size() > 0)
				for(k=0;k<thePark.paths[i][j].size(); k++)
					fprintf(logfile, "%3d %3d - base:%f ceiling:%f type:%d\n",
						i, j, 
						thePark.paths[i][j][k].base,
						thePark.paths[i][j][k].ceiling,
						thePark.paths[i][j][k]);
				
	fclose(logfile);
}

void initLights(void)
{
	/*
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	*/
}


//BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
BOOL Initialize (void)
{
	int doh;
	char *dum;

	char *tmp;
	char tempstr[256];

	tmp = (char *)malloc(256);

	//get the program storage location from the registry
	/*
	HKEY hKey;
	DWORD dwBufLen;

	RegOpenKeyEx( HKEY_LOCAL_MACHINE,
	   "SOFTWARE\\RCTGL",
	   0, KEY_QUERY_VALUE, &hKey );

	RegQueryValueEx( hKey, "AppPath", NULL, NULL,
	   (LPBYTE) &RCTGL_Location[0], &dwBufLen);
	*/

	DWORD temp;

	char EXELoc[256];

	// get current directory so we can restore later
	temp = GetModuleFileName(NULL, &EXELoc[0], 256);

	printf("program location: %s\n", &EXELoc[0]);

	int len = strlen(&EXELoc[0]);

	EXELoc[len - 10] = '\0';

	printf("program dir: %s\n", &EXELoc[0]);

	dum = strcpy(&RCTGL_Location[0], &EXELoc[0]);



	/*
	if((RegQueryValueEx( hKey, "TempFile", NULL, NULL,
	   (LPBYTE) &RCTGL_TempFile[0], &dwBufLen)) != 0)
	{
	*/
		// set the value manually if we can't read it from the registry
		tmp = strcpy(&RCTGL_TempFile[0], "uncomp.sv4");

		tmp = (char *)memcpy((char *)&RCTGL_TempFile[0], (char *)tmp, 256);
	/*
	}
	*/

	//RegCloseKey( hKey );

	initLights();

	

	//build the location of the temp file
	//tmp = strcat("\\", &RCTGL_TempFile[0]);

	//strcpy(&RCTGL_TempFile[0], tmp);

	
	printf("temp file 1 = %s\n", &RCTGL_TempFile[0]);
	printf("loc 1 = %s\n", &RCTGL_Location[0]);


	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero

    //Texs[0]=auxDIBImageLoad("Data/font1.bmp");					// Load Font Texture
	glGenTextures(NUMTEXTURES, &texture_id[0]);								// Create Font Texture
    //glBindTexture(GL_TEXTURE_2D, texture_id[FONTTEX]);

	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);


	tmp = strcpy(&tempstr[0], &RCTGL_Location[0]);
	//strcat(tempstr, "\\Data\\font1")	
	doh = loadTGA( strcat(tempstr, "\\Data\\font1.tga"), FONTTEX );

	

	/*
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Texs[0]->sizeX , Texs[0]->sizeY , 0, GL_RGB, GL_UNSIGNED_BYTE, Texs[0]->data);
    if(Texs[0]->data != NULL) free(Texs[0]->data);				// Free Data Allocated
	*/

	printf ( "GL_VENDOR    ='%s'\n", glGetString ( GL_VENDOR     ) ) ;
	printf ( "GL_RENDERER  ='%s'\n", glGetString ( GL_RENDERER   ) ) ;
	printf ( "GL_VERSION   ='%s'\n", glGetString ( GL_VERSION    ) ) ;
	printf ( "GL_EXTENSIONS='%s'\n", glGetString ( GL_EXTENSIONS ) ) ;

	
	char TempCopy[256];

	dum = strcpy(&TempCopy[0], &RCTGL_Location[0]);

	dum = strcat(dum, "\\");

	dum = strcat(dum, &RCTGL_TempFile[0]);

	dum = (char *)memcpy((char *)&RCTGL_TempFile[0], (char *)dum, 256);

	printf("RCTGL Lives at: %s\n", &RCTGL_Location[0]);
	printf("RCTGL Temp File at: %s\n", &RCTGL_TempFile[0]);

	//set the colors
	// populate RCTColors arrays
	RCTColorsR[0] = 0.16f;
	RCTColorsG[0] = 0.25f;
	RCTColorsB[0] = 0.26f;

	RCTColorsR[1] = 0.42f;
	RCTColorsG[1] = 0.51f;
	RCTColorsB[1] = 0.52f;

	RCTColorsR[2] = 0.71f;
	RCTColorsG[2] = 0.76f;
	RCTColorsB[2] = 0.76f;

	RCTColorsR[3] = 0.45f;
	RCTColorsG[3] = 0.49f;
	RCTColorsB[3] = 0.68f;

	RCTColorsR[4] = 0.52f;
	RCTColorsG[4] = 0.32f;
	RCTColorsB[4] = 0.74f;

	RCTColorsR[5] = 0.03f;
	RCTColorsG[5] = 0.25f;
	RCTColorsB[5] = 0.75f;

	RCTColorsR[6] = 0.26f;
	RCTColorsG[6] = 0.53f;
	RCTColorsB[6] = 0.91f;

	RCTColorsR[7] = 0.16f;
	RCTColorsG[7] = 0.57f;
	RCTColorsB[7] = 0.55f;

	RCTColorsR[8] = 0.09f;
	RCTColorsG[8] = 0.47f;
	RCTColorsB[8] = 0.00f;

	RCTColorsR[9] = 0.29f;
	RCTColorsG[9] = 0.53f;
	RCTColorsB[9] = 0.35f;

	RCTColorsR[10] = 0.39f;
	RCTColorsG[10] = 0.56f;
	RCTColorsB[10] = 0.22f;

	RCTColorsR[11] = 0.26f;
	RCTColorsG[11] = 0.68f;
	RCTColorsB[11] = 0.13f;

	RCTColorsR[12] = 0.52f;
	RCTColorsG[12] = 0.62f;
	RCTColorsB[12] = 0.35f;

	RCTColorsR[13] = 0.52f;
	RCTColorsG[13] = 0.54f;
	RCTColorsB[13] = 0.22f;

	RCTColorsR[14] = 0.84f;
	RCTColorsG[14] = 0.65f;
	RCTColorsB[14] = 0.06f;

	RCTColorsR[15] = 0.55f;
	RCTColorsG[15] = 0.32f;
	RCTColorsB[15] = 0.00f;

	RCTColorsR[16] = 1.00f;
	RCTColorsG[16] = 0.43f;
	RCTColorsB[16] = 0.06f;

	RCTColorsR[17] = 0.71f;
	RCTColorsG[17] = 0.27f;
	RCTColorsB[17] = 0.00f;

	RCTColorsR[18] = 0.71f;
	RCTColorsG[18] = 0.51f;
	RCTColorsB[18] = 0.26f;

	RCTColorsR[19] = 0.48f;
	RCTColorsG[19] = 0.33f;
	RCTColorsB[19] = 0.09f;

	RCTColorsR[20] = 0.48f;
	RCTColorsG[20] = 0.40f;
	RCTColorsB[20] = 0.29f;

	RCTColorsR[21] = 0.81f;
	RCTColorsG[21] = 0.51f;
	RCTColorsB[21] = 0.39f;

	RCTColorsR[22] = 0.65f;
	RCTColorsG[22] = 0.22f;
	RCTColorsB[22] = 0.22f;

	RCTColorsR[23] = 0.55f;
	RCTColorsG[23] = 0.00f;
	RCTColorsB[23] = 0.00f;

	RCTColorsR[24] = 0.91f;
	RCTColorsG[24] = 0.02f;
	RCTColorsB[24] = 0.00f;

	RCTColorsR[25] = 0.87f;
	RCTColorsG[25] = 0.22f;
	RCTColorsB[25] = 0.55f;

	RCTColorsR[26] = 0.94f;
	RCTColorsG[26] = 0.62f;
	RCTColorsB[26] = 0.62f;

	RCTColorsR[27] = 0.58f;
	RCTColorsG[27] = 0.02f;
	RCTColorsB[27] = 0.29f;

	RCTColorsR[28] = 0.22f;
	RCTColorsG[28] = 0.26f;
	RCTColorsB[28] = 0.45f;

	RCTColorsR[29] = 0.52f;
	RCTColorsG[29] = 0.81f;
	RCTColorsB[29] = 0.81f;

	RCTColorsR[30] = 1.00f;
	RCTColorsG[30] = 0.91f;
	RCTColorsB[30] = 0.16f;

	RCTColorsR[31] = 0.55f;
	RCTColorsG[31] = 0.83f;
	RCTColorsB[31] = 0.97f;

	
	//load the game's logo
	tmp = strcpy(&tempstr[0], RCTGL_Location);

	doh = loadTGA( strcat(tempstr, "\\logo2.tga"), RCT3DLOGO );

	//DisplayMode = None;
	DisplayMode = TextureProgress;


	detailLevel = M_HIGH_DETAIL;
	

	LoadedSkyTex = FALSE;
	LoadedEdgeTex = FALSE;
	LoadedSurfaceTex = FALSE;				
	LoadedPathTex = FALSE;
	LoadedRideTex = FALSE;
	LoadedTreeTex = FALSE;
	LoadedWallTex = FALSE;

	

	XV = -2.0f;
	YV = -2.0f;
	ZV = -2.0f;

	XR = 0.0f;
	YR = 180.0f;
	ZR = 0.0f;

	//InitSkyTextures();


	//glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);							// Enable Blending
	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
	glEnable(GL_BLEND);											// Enable Blending



	gluPerspective(80.0, 1.0, 1.0, 5000.0);

	
	GLfloat fogColor[4]= {0.65f, 0.65f, 0.60f, 1.0f};

	//glClearColor(0.5f,0.5f,0.5f,1.0f);			// We'll Clear To The Color Of The Fog ( Modified )

	glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.25f);				// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
	glFogf(GL_FOG_END, 5000.0f);				// Fog End Depth
	glEnable(GL_FOG);					// Enables GL_FOG


	//initialize the thePark structure
//	int i,j;

	//InitDInput();

	//InitFMod();

	g_FontListID = CreateOpenGLFont("Arial", FONT_HEIGHT);

	int i;

	for(i=0; i<360; i++)
	{
		sinTable[i] = sin(i * (3.14f / 180.0f));
		cosTable[i] = cos(i * (3.14f / 180.0f));
		tanTable[i] = tan(i * (3.14f / 180.0f));

		//printf("%1.4f %1.4f %1.4f\n", sinTable[i], cosTable[i], tanTable[i]);
	}

	mySkyDome = new skyDome();

	mySkyDome->getAmbientColor(&ambientRValue, &ambientGValue, &ambientBValue);
	mySkyDome->getLightColor(&lightRValue, &lightGValue, &lightBValue);

	double val = calcLightFactor(0.0f, 0.0f, 1.0f);
	float white[3] = {1.0f, 1.0f, 1.0f};
	float r, g, b;
	calcColor(white, val, &edgeLighting[0][0], &edgeLighting[0][1], &edgeLighting[0][2]);
		
		
	val = calcLightFactor(1.0f, 0.0f, 0.0f);
	calcColor(white, val, &edgeLighting[1][0], &edgeLighting[1][1], &edgeLighting[1][2]);

	//changed
	val = calcLightFactor(0.0f, 0.0f, -1.0f);
	calcColor(white, val, &edgeLighting[2][0], &edgeLighting[2][1], &edgeLighting[2][2]);

	val = calcLightFactor(-1.0f, 0.0f, 0.0f);
	calcColor(white, val, &edgeLighting[3][0], &edgeLighting[3][1], &edgeLighting[3][2]);


	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
}

void calcCanMove(int xTile, int zTile, int savePlace)
{
	int i;

	CanMove.curX = xTile;
	CanMove.curZ = zTile;
	CanMove.curIndex = savePlace;

	//ZV = thePark.paths[xTile][zTile][savePlace].base + PEEPHEIGHT;

	//check the north side
	CanMove.N = -1;
	for(i=0; i<thePark.paths[xTile][zTile+1].size(); i++)
	{
		if(thePark.paths[xTile][zTile][savePlace].connectE > 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][savePlace].pathSlope == 0)
			{
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 0)
					CanMove.N = i;
				else if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 6)
					CanMove.N = i;
				else if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 4)
					CanMove.N = i;
			}
			//if we start going uphill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 6)
			{
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 0)
					CanMove.N = i;
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 4)
					CanMove.N = i;
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 6)
					CanMove.N = i;
			}
			//if we start going downhill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 4)
			{
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 0)
					CanMove.N = i;
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 4)
					CanMove.N = i;
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 6)
					CanMove.N = i;
			}
		}
		
	}


	//check the south side
	CanMove.S = -1;
	for(i=0; i<thePark.paths[xTile][zTile-1].size(); i++)
	{
		if(thePark.paths[xTile][zTile][savePlace].connectW > 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][savePlace].pathSlope == 0)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 0)			
					CanMove.S = i;
				// piece is continuing up-hill
				else if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 4)			
					CanMove.S = i;
				// piece is continuing downhill
				else if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 6)
					CanMove.S = i;
			}
			// if we start uphill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 4)
			{
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 0)			
					CanMove.S = i;
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 4)			
					CanMove.S = i;
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 6)			
					CanMove.S = i;
			}
			//if we start downhill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 6)
			{
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 0)			
					CanMove.S = i;
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 4)			
					CanMove.S = i;
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 6)			
					CanMove.S = i;
			}
		}
	}


	//check the east side
	CanMove.E = -1;
	for(i=0; i<thePark.paths[xTile+1][zTile].size(); i++)
	{
		if(thePark.paths[xTile][zTile][savePlace].connectN > 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][savePlace].pathSlope == 0)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 0)			
					CanMove.E = i;
				// piece goes up-hill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 5)			
					CanMove.E = i;
				// piece goes downhill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 7)
					CanMove.E = i;
			}
			
			// if we start uphill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 5)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 0)			
					CanMove.E = i;
				// piece goes up-hill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 5)			
					CanMove.E = i;
				// piece goes downhill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 7)
					CanMove.E = i;
			}		
			//if we start downhill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 7)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 0)			
					CanMove.E = i;
				// piece goes up-hill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 5)			
					CanMove.E = i;
				// piece goes downhill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 7)
					CanMove.E = i;
			}
		}
		
	}

	//check the west side
	CanMove.W = -1;
	for(i=0; i<thePark.paths[xTile-1][zTile].size(); i++)
	{
		if(thePark.paths[xTile][zTile][savePlace].connectS > 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][savePlace].pathSlope == 0)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)			
					CanMove.W = i;
				// piece goes up-hill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 5)			
					CanMove.W = i;
				// piece goes downhill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 7)
					CanMove.W = i;
			}
			
			// if we start uphill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 5)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)			
					CanMove.W = i;
				// piece goes up-hill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base - 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 5)			
					CanMove.W = i;
				// piece goes downhill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 7)
					CanMove.W = i;
			}		
			//if we start downhill
			else if(thePark.paths[xTile][zTile][savePlace].pathSlope == 7)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)			
					CanMove.W = i;
				// piece goes up-hill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 5)			
					CanMove.W = i;
				// piece goes downhill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base + 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 7)
					CanMove.W = i;
			}
		}
	}
		
	/*
	if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][savePlace].base
			&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)
			CanMove.W = i;
	printf("CanMove.W = %d\n", CanMove.W);
	*/

	CanMove.NW = -1;
	CanMove.NE = -1;
	CanMove.SE = -1;
	CanMove.SW = -1;
}

void recalcAmbientLighting(void)
{
	mySkyDome->getAmbientColor(&ambientRValue, &ambientGValue, &ambientBValue);
	
	//double ambient[4] = {ambientRValue, ambientGValue, ambientBValue, 1.0f};
	//float ones[3] = {10.f, 10.f, 1.0f};

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	mySkyDome->getLightColor(&lightRValue, &lightGValue, &lightBValue);

	//float lightPos[4] = {-1.0f, 1.0f, 0.5f, 0.0f};
	//double lightColor[4] = {lightRValue, lightGValue, lightBValue, 1.0f};		
}



void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
//	HRESULT hr;
	char keystate[256];
	DIMOUSESTATE mouse_state;
	int xTile, zTile;

	float moveStep;

	xTile = (int)(XV / UNITWIDTH);
	zTile = (int)(ZV / UNITWIDTH);
	
	//handle the keyboard input
	if(FAILED(m_keyboard->GetDeviceState(sizeof(keystate), (LPVOID)&keystate)))
	{
		printf("keyboard->GetDeviceState failed\naborting\n");
		exit(0);
	}

	if (KeyDown(keystate, DIK_ESCAPE) && escapeKeyDown == false)
	{
		escapeKeyDown = true;

		if(isMenuVisible)
		{
			SetMenu(window.hWnd, NULL);
			isMenuVisible = false;
			if(DisplayMode == PausedInGame)
				DisplayMode = InGame;
		}
		else
		{
			SetMenu(window.hWnd, hMenu);
			isMenuVisible = true;
			if(DisplayMode == InGame)
				DisplayMode = PausedInGame;
		}
	}


	if (!KeyDown(keystate, DIK_ESCAPE))
		escapeKeyDown = false;

	if(KeyDown(keystate, DIK_F1))
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode

	if(KeyDown(keystate, DIK_F2))
	{
		int theIndex;
		int newStandard;
		int i;

		// find the highest path under the user
		for(i=0; i<thePark.paths[xTile][zTile].size(); i++)
		{
			if((thePark.paths[xTile][zTile][i].base * UNITHEIGHT) <= YV &&
				thePark.paths[xTile][zTile][i].base > newStandard)
			{
				theIndex = i;
				newStandard = thePark.paths[xTile][zTile][i].base;
			}
		}

		if(theIndex >= 0 )
		{
			printf("start calcQueueRide()\n");
			int returned = calcQueueRide(xTile, zTile, theIndex, -1);
			printf("calcQueueRide = %d\n", returned);
			if(returned > -1)
			{
				int stringIndex = RideList[returned].nameStringOffset;
				printf("returned %d %s\n", stringIndex, &thePark.nameStrings[stringIndex][0]);
			}
		}				
	}

	bool timeModified = false;

	if(KeyDown(keystate, DIK_ADD) && plusKeyDown == false)
	{
		int tod;
		mySkyDome->getTime(&tod);
		mySkyDome->setTime(tod + 15);
		
		plusKeyDown = true;
		
		timeModified = true;
	}

	if(KeyDown(keystate, DIK_SUBTRACT) && minusKeyDown == false)
	{
		int tod;
		mySkyDome->getTime(&tod);
		mySkyDome->setTime(tod - 15);

		minusKeyDown = true;		
		timeModified = true;
	}

	if(timeModified)
	{
		/*
		if(minuteOfDay >= 1440)
			minuteOfDay = 0;
		else if(minuteOfDay <= 0)
			minuteOfDay = 1425;
			*/

		recalcAmbientLighting();

		double val = calcLightFactor(0.0f, 0.0f, 1.0f);
		float white[3] = {1.0f, 1.0f, 1.0f};
		float r, g, b;
		calcColor(white, val, &edgeLighting[0][0], &edgeLighting[0][1], &edgeLighting[0][2]);
		
		
		val = calcLightFactor(1.0f, 0.0f, 0.0f);
		calcColor(white, val, &edgeLighting[1][0], &edgeLighting[1][1], &edgeLighting[1][2]);

		//changed
		val = calcLightFactor(0.0f, 0.0f, -1.0f);
		calcColor(white, val, &edgeLighting[2][0], &edgeLighting[2][1], &edgeLighting[2][2]);

		val = calcLightFactor(-1.0f, 0.0f, 0.0f);
		calcColor(white, val, &edgeLighting[3][0], &edgeLighting[3][1], &edgeLighting[3][2]);
	}
	
	

	if(KeyDown(keystate, DIK_LSHIFT) || KeyDown(keystate, DIK_RSHIFT))
		if(NavMode == PeepMode)
			moveStep = WALK_SPEED_FAST * g_FrameInterval;
		else
			moveStep = FLY_SPEED_FAST * g_FrameInterval;
	else
		if(NavMode == PeepMode)
			moveStep = WALK_SPEED * g_FrameInterval;
		else
			moveStep = FLY_SPEED * g_FrameInterval;

	/*
	if(DisplayMode != TextureProgress && KeyDown(keystate, DIK_O) &&
		(KeyDown(keystate, DIK_LCONTROL) || KeyDown(keystate, DIK_RCONTROL)))
		processFileOpenRequest();
		*/

	if(KeyDown(keystate, DIK_TAB) && tabKeyDown == false && 
		(DisplayMode == InGame || DisplayMode == PausedInGame || DisplayMode == MapMode))
	{
		tabKeyDown = true;

		if(DisplayMode == MapMode)
		{
			DisplayMode = oldDisplayMode;

			if(fogLevel != M_FOG_NONE)
				glEnable(GL_FOG);
		}
		else
		{
			oldDisplayMode = DisplayMode;
			DisplayMode = MapMode;
			glDisable(GL_FOG);
		}
	}

	if(!KeyDown(keystate, DIK_TAB))
	{
		tabKeyDown = false;
	}

	if(!KeyDown(keystate, DIK_ADD))
		plusKeyDown = false;
	if(!KeyDown(keystate, DIK_SUBTRACT))
		minusKeyDown = false;

	if(DisplayMode == InGame)
	{
		if (KeyDown(keystate, DIK_LEFT) || KeyDown(keystate, DIK_A))						// Is F1 Being Pressed?
		{
			//printf("got left arrow (%f %f %f)\n", XV, YV, ZV);
			ZV+=(float)(-moveStep * cos((XR - 90.0f) * M_PI / 180.0f));
			XV-=(float)(-moveStep * sin((XR - 90.0f) * M_PI / 180.0f));
		}

		if (KeyDown(keystate, DIK_RIGHT) || KeyDown(keystate, DIK_D))						// Is F1 Being Pressed?
		{
			//printf("got right arrow (%f %f %f)\n", XV, YV, ZV);
			ZV+=(float)(-moveStep * cos((XR + 90.0f) * M_PI / 180.0f));
			XV-=(float)(-moveStep * sin((XR + 90.0f) * M_PI / 180.0f));
		}

		if (KeyDown(keystate, DIK_UP) || KeyDown(keystate, DIK_W))						// Is F1 Being Pressed?
		{
			//printf("got up arrow (%f %f %f)\n", XV, YV, ZV);
			ZV+=(float)(-moveStep * cos(XR * M_PI / 180.0f));
			XV-=(float)(-moveStep * sin(XR * M_PI / 180.0f));
		}

		if (KeyDown(keystate, DIK_DOWN) || KeyDown(keystate, DIK_S))
		{
			//printf("got down arrow (%f %f %f)\n", XV, YV, ZV);
			ZV-=(float)(-moveStep * cos(XR * M_PI / 180.0f));
			XV+=(float)(-moveStep * sin(XR * M_PI / 180.0f));
		}

		if (KeyDown(keystate, DIK_PRIOR) && NavMode == FreeMode)
		{
			//printf("got page up (%f %f %f)\n", XV, YV, ZV);
			YV+=moveStep;
		}

		if (KeyDown(keystate, DIK_NEXT) && NavMode == FreeMode)
		{
			//printf("got page down (%f %f %f)\n", XV, YV, ZV);
			YV-=moveStep;
		}


		if (KeyDown(keystate, DIK_M) && modeKeyDown == false)
		{
			modeKeyDown = true;

			if(NavMode == PeepMode)
			{
				printf("changing to FreeMode\n");
				NavMode = FreeMode;
			}
			else
			{
				int i, theIndex, newStandard;

				theIndex = -1;
				newStandard = -1;

				// find the highest path under the user
				for(i=0; i<thePark.paths[xTile][zTile].size(); i++)
				{
					if((thePark.paths[xTile][zTile][i].base * UNITHEIGHT) <= YV &&
						thePark.paths[xTile][zTile][i].base > newStandard)
					{
						theIndex = i;
						newStandard = thePark.paths[xTile][zTile][i].base;
					}
				}

				if(theIndex >= 0)
				{
					YV = (newStandard + PEEPHEIGHT) * UNITHEIGHT;
					printf("changing to PeepMode NAR\n");
					NavMode = PeepMode;
					printf("calling calcCanMove\n");
					calcCanMove(xTile, zTile, theIndex);
				}				
			}
		}

		if(!KeyDown(keystate, DIK_M))
			modeKeyDown = false;
	}

	// track the mouse
	if(FAILED(g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state)))
	{
		//printf("reacquiring mouse tracking\n");
		g_pMouse->Acquire();			
	}
	else
	{
		if(DisplayMode == InGame) // || DisplayMode == MapMode)
		{
			XR += 0.5f * mouse_state.lX;
			YR += 0.5f * mouse_state.lY;
		}

		if(XR < 0.0f)
			XR += 360.0f;
		else if(XR > 360.0f)
			XR -= 360.0f;

		if(YR < 0.0f)
			YR += 360.0f;
		else if(XR > 360.0f)
			YR -= 360.0f;
	}

	if(NavMode == PeepMode)
	{
		float edgeSpacingOut = 1.25f;
		float edgeSpacingIn = UNITWIDTH - edgeSpacingOut;

		if(inQueue == false)
		{
			if(thePark.paths[xTile][zTile][CanMove.curIndex].pathType == 0)
			{
				inQueue = true;
				queueRide = calcQueueRide(xTile, zTile, CanMove.curIndex, -1);
			}
			else
				inQueue = false;
		}
		else
		{
			if(thePark.paths[xTile][zTile][CanMove.curIndex].pathType != 0)
				inQueue = false;
		}

		

		
		if(XV >= ((CanMove.curX + 1) * UNITWIDTH) - edgeSpacingOut && CanMove.E== -1)
		//if(xTile >= (CanMove.curX - edgeSpacingIn) && CanMove.E == -1)
		{

			XV = (CanMove.curX + 1) * UNITWIDTH - edgeSpacingOut;
			//xTile = CanMove.curX;
		}
		else if(xTile > CanMove.curX && CanMove.E >= 0)
		{

			calcCanMove(xTile, CanMove.curZ, CanMove.E);
		}		
		else if(XV <= (CanMove.curX * UNITWIDTH) + edgeSpacingOut && CanMove.W== -1)
		//else if(xTile <= (CanMove.curX + edgeSpacingOut) && CanMove.W == -1)
		{

			XV = (CanMove.curX) * UNITWIDTH + edgeSpacingOut;
			//xTile = CanMove.curX;
		}
		else if(xTile < CanMove.curX && CanMove.W >= 0)
		{

			calcCanMove(xTile, CanMove.curZ, CanMove.W);
		}		
		
		//if(zTile >= CanMove.curZ && CanMove.N == -1)
		if(ZV >= ((CanMove.curZ + 1) * UNITWIDTH) - edgeSpacingOut && CanMove.N== -1)
		{

			ZV = (CanMove.curZ + 1) * UNITWIDTH - edgeSpacingOut;
			//zTile = CanMove.curZ;
		}
		else if(zTile > CanMove.curZ && CanMove.N >= 0)
		{

			calcCanMove(CanMove.curX, zTile, CanMove.N);
		}
		//else if(zTile <= CanMove.curZ && CanMove.S == -1)
		else if(ZV <= (CanMove.curZ * UNITWIDTH) + edgeSpacingOut && CanMove.S== -1)
		{

			ZV = (CanMove.curZ) * UNITWIDTH + edgeSpacingOut;
			//zTile = CanMove.curZ;
		}
		else if(zTile < CanMove.curZ && CanMove.S >= 0)
		{

			calcCanMove(CanMove.curX, zTile, CanMove.S);
		}


		//adjust the peep's height if they are on a sloped surface
		if(thePark.paths[xTile][zTile][CanMove.curIndex].pathSlope == 4)
		{
			float percentage;

			percentage = 1.0f - (ZV - (zTile * UNITWIDTH)) / UNITWIDTH;



			YV = (thePark.paths[xTile][zTile][CanMove.curIndex].base + percentage + PEEPHEIGHT) * UNITHEIGHT;
		}

		if(thePark.paths[xTile][zTile][CanMove.curIndex].pathSlope == 6)
		{
			float percentage;

			percentage = (ZV - (zTile * UNITWIDTH)) / UNITWIDTH;



			YV = (thePark.paths[xTile][zTile][CanMove.curIndex].base + percentage + PEEPHEIGHT) * UNITHEIGHT;
		}


		if(thePark.paths[xTile][zTile][CanMove.curIndex].pathSlope == 5)
		{
			float percentage;

			percentage = (XV - (xTile * UNITWIDTH)) / UNITWIDTH;



			YV = (thePark.paths[xTile][zTile][CanMove.curIndex].base + percentage + PEEPHEIGHT) * UNITHEIGHT;
		}

		if(thePark.paths[xTile][zTile][CanMove.curIndex].pathSlope == 7)
		{
			float percentage;

			percentage = 1.0f - (XV - (xTile * UNITWIDTH)) / UNITWIDTH;



			YV = (thePark.paths[xTile][zTile][CanMove.curIndex].base + percentage + PEEPHEIGHT) * UNITHEIGHT;
		}			
	}

	posVector[0] = XV;
	posVector[1] = YV;
	posVector[2] = ZV;

	//viewVector[0] = XV + cos((float)(XR - 90.0f)* 3.14f / 180.0f);
	//viewVector[1] = YV;
	//viewVector[2] = ZV + sin((float)(XR - 90.0f) * 3.14f / 180.0f);

	viewVector[0] = XV + sin((float)(YR - 90.0f)* 3.14f / 180.0f) * cos((float)(XR - 90.0f)* 3.14f / 180.0f);
	viewVector[1] = YV + cos((float)(YR - 90.0f) * 3.14f / 180.0f);
	viewVector[2] = ZV + sin((float)(YR - 90.0f) * 3.14f / 180.0f) * sin((float)(XR - 90.0f)* 3.14f / 180.0f);
	


	angle += (float)(milliseconds) / 5.0f;						// Update angle Based On The Clock
}

void Draw (void)
{//87 83 65 68
	int i,j,k;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	

	//DrawSkyBox();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	if (DisplayMode == None || DisplayMode == TextureProgress || DisplayMode == SV4Progress)
	{
		//glEnable(GL_TEXTURE_2D);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
		glLoadIdentity();											// Reset The View	
		//glColor3f(0.0f,0.3f,1.0f);
		fNehe.SetBase(32);											// Adjust Base Start Pos (First Set of Fonts)

		/*
		if (window.init.isFullScreen == TRUE)
		{
			fNehe.20,30,"RCTGL - Milestone3");			// Print GL Text To The Screen
			glColor3f(1.0f,1.0f,0.0f);
			fNehe.SetBase(32 - 128);									// Adjust Base Start Pos (Second Set of Fonts)
			fNehe.Print(20,50,"Milestone 3");			// Print GL Text To The Screen
		}
		else
		*/
		{
			fNehe.Print(20,50,"RCTGL - Milestone 5");			// Print GL Text To The Screen
			//glColor3f(1.0f,1.0f,0.0f);
			//fNehe.SetBase(32 - 128);									// Adjust Base Start Pos (Second Set of Fonts)
			//fNehe.Print(20,70,"Milestone 3");			// Print GL Text To The Screen
		}
		
		glTranslatef(0.5f, 0.0f, -2.0f);
			
		//draw the rotating logo
		glPushMatrix();
		
			
			//glRotatef(sin(angle / 500.0f) * 30.0f, 1.0f, 0.0f, 0.0f);

			//glRotatef(sin(angle / 300.0f) * 40.0f, 0.0f, 1.0f, 0.0f);

			//glTranslatef(0.0f, 0.5f, 0.0f);
		
			glEnable(GL_TEXTURE_2D);

			glBindTexture (GL_TEXTURE_2D, texture_id[RCT3DLOGO] );

			glAlphaFunc ( GL_GREATER, 0.95f );
			glEnable    ( GL_ALPHA_TEST   );

		

			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);	
				glVertex3f(-0.45f, -1.0f, 0.0f);

				glTexCoord2f(1.0, 0.0);
				glVertex3f(0.65f, -1.0f, 0.0f);

				glTexCoord2f(1.0, 1.0);
				glVertex3f(0.65f, 1.0f, 0.0f);

				glTexCoord2f(0.0, 1.0);
				glVertex3f(-0.45f, 1.0f, 0.0f);
			glEnd();

			glDisable    ( GL_ALPHA_TEST   );

			glAlphaFunc ( GL_NONE, 0.95f );

			//glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}


	/*
	if(DisplayMode == None)
		MessageBox(NULL, "displaymode = none", "TITTIE", MB_OK);
	else if(DisplayMode == TextureProgress)
		MessageBox(NULL, "displaymode = textureprogress", "TITTIE", MB_OK);
	else if(DisplayMode == SV4Progress)
		MessageBox(NULL, "displaymode = sv4progress", "TITTIE", MB_OK);
	else if(DisplayMode == InGame)
		MessageBox(NULL, "displaymode = ingame", "TITTIE", MB_OK);
	else
		MessageBox(NULL, "displaymode = undefined", "TITTIE", MB_OK);
		*/


	if (DisplayMode == TextureProgress)
	{
		//glEnable(GL_TEXTURE_2D);
		//fNehe.SetBase(32 - 128);

		//print loading info
		

		fNehe.SetBase(32);									// Adjust Base Start Pos (Second Set of Fonts)
		fNehe.Print(20,90,"Loading Textures...");			// Print GL Text To The Screen

		//print all the categories

		fNehe.Print(40,110,"Edges");			// Print GL Text To The Screen

		fNehe.Print(40,130,"Surfaces");			// Print GL Text To The Screen
		
		fNehe.Print(40,150,"Paths");			// Print GL Text To The Screen
		
		fNehe.Print(40,170,"Trees");			// Print GL Text To The Screen
		
		fNehe.Print(40,190,"Rides");			// Print GL Text To The Screen
		
		fNehe.Print(40,210,"Sky");			// Print GL Text To The Screen

		fNehe.Print(40,230,"Walls");			// Print GL Text To The Screen

		fNehe.SetBase(32 - 128);									// Adjust Base Start Pos (Second Set of Fonts)
		
		//go through the categories (boolean)
		if(LoadedEdgeTex == TRUE)
			fNehe.Print(150,110,"Done");
		if(LoadedSurfaceTex == TRUE)
			fNehe.Print(150,130,"Done");
		if(LoadedPathTex == TRUE)
			fNehe.Print(150,150,"Done");
		if(LoadedTreeTex == TRUE)
			fNehe.Print(150,170,"Done");
		if(LoadedRideTex == TRUE)
			fNehe.Print(150,190,"Done");
		if(LoadedSkyTex == TRUE)
			fNehe.Print(150,210,"Done");
		if(LoadedWallTex == TRUE)
			fNehe.Print(150,230,"Done");
		
		
		//process the categories as needed
		if(LoadedEdgeTex == FALSE)
		{
			InitEdgeTextures();
			LoadedEdgeTex = TRUE;
		}
		else if(LoadedSurfaceTex == FALSE)
		{
			InitSurfaceTextures();
			LoadedSurfaceTex = TRUE;
		}
		else if(LoadedPathTex == FALSE)
		{
			InitPathTextures();
			LoadedPathTex = TRUE;
		}
		else if(LoadedTreeTex == FALSE)
		{
			InitTreeTextures();
			LoadedTreeTex = TRUE;
		}
		else if(LoadedRideTex == FALSE)
		{
			InitRideTextures();
			LoadedRideTex = TRUE;
		}
		else if(LoadedSkyTex == FALSE)
		{
			InitSkyTextures();
			LoadedSkyTex = TRUE;
		}
		else if(LoadedWallTex == FALSE)
		{
			InitWallTextures();
			LoadedWallTex = TRUE;
		}
		else
		{
			initAtmosphere(MENU_ENV_ORIGINAL);

			//enable the menu option to open a file
			EnableMenuItem(hMenu, MENU_FILE_OPEN, MF_ENABLED);
			EnableMenuItem(hMenu, MENU_LOAD_EXTENDED, MF_ENABLED);

			//change the display mode
			DisplayMode = None;			
		}
	}
	
	else if (DisplayMode == SV4Progress)
	{
		//set up the time
		minuteOfDay = 540;
		drawStars = false;
		drawSky = true;

		//use the first font
		fNehe.SetBase(32);

		fNehe.Print(20,90,"Loading Park...");
		
		fNehe.Print(40,110,"Uncompressing");	
		fNehe.Print(40,130,"Landscape");	
		fNehe.Print(40,150,"Rides");	
		fNehe.Print(40,170,"Trees");	
		fNehe.Print(40,190,"Paths");	
		fNehe.Print(40,210,"Elements");	
		fNehe.Print(40,230,"Walls");

		//use the second font
		fNehe.SetBase(32-128);

		if(UncompressedFile == TRUE)
			fNehe.Print(200,110,"Done");
		if(LoadedLandscape == TRUE)
			fNehe.Print(200,130,"Done");
		if(LoadedRides == TRUE)
			fNehe.Print(200,150,"Done");
		if(LoadedTrees == TRUE)
			fNehe.Print(200,170,"Done");
		if(LoadedPaths == TRUE)
			fNehe.Print(200,190,"Done");
		if(LoadedElements == TRUE)
			fNehe.Print(200,210,"Done");
		if(LoadedWalls == TRUE)
			fNehe.Print(200,230,"Done");

		if(UncompressedFile == FALSE)
		{
			DecompressFile(&RCTGL_InFile[0], &RCTGL_TempFile[0]);

			UncompressedFile = TRUE;

			thePark.parkEntranceX = -1;
			thePark.parkEntranceY = -1;
			thePark.parkEntranceZ = -1;

			for(i=0; i<128; i++)
			{
				for(j=0; j<128;j++)
				{
					thePark.trees[i][j].clear();
					thePark.tracks[i][j].clear();
					thePark.elements[i][j].clear();					
					thePark.paths[i][j].clear();
					thePark.walls[i][j].clear();
					thePark.entrances[i][j].clear();					
				}
			}

		}
		else if(LoadedLandscape == FALSE)
		{
			LoadLandscape(&RCTGL_TempFile[0]);
			LoadedLandscape = TRUE;
		}
		else if(LoadedRides == FALSE)
		{
			LoadRides(&RCTGL_TempFile[0]);
			LoadedRides = TRUE;
		}
		else if(LoadedTrees == FALSE)
		{
			LoadTrees1(&RCTGL_TempFile[0]);
			LoadBigScenery(&RCTGL_TempFile[0]);
			LoadedTrees = TRUE;
		}
		else if(LoadedPaths == FALSE)
		{
			LoadPaths(&RCTGL_TempFile[0]);
			LoadEntrances(&RCTGL_TempFile[0]);
			LoadedPaths = TRUE;
		}
		else if(LoadedElements == FALSE)
		{
			LoadElements(&RCTGL_TempFile[0]);
			LoadedElements = TRUE;
		}
		else if(LoadedWalls == FALSE)
		{
			LoadWalls(&RCTGL_TempFile[0]);
			LoadedWalls = TRUE;	
			
			LoadNames(&RCTGL_TempFile[0]);
		}
		else
		{
			posVector[0] = 100.0f;
			posVector[1] = 20.0f;
			posVector[2] = 0.0f;

			viewVector[0] = 100.0f;
			viewVector[1] = 20.0f;
			viewVector[2] = 10.0f;

			upVector[0] = 0.0f;
			upVector[1] = 1.0f;
			upVector[2] = 0.0f;

			

			if(thePark.parkEntranceX == -1)
			{
				XV = 100.0f;
				YV = 20.0f;
				ZV = 0.0f;

				XR = 180.0f;
				YR = 0.0f;
				ZR = 0.0f;
			}
			else
			{
				if(thePark.parkEntranceX > 64 && thePark.parkEntranceZ < 64)
				{
					XV = 128 * UNITWIDTH;
					YV = thePark.parkEntranceY * UNITHEIGHT + PEEPHEIGHT;
					ZV = (thePark.parkEntranceZ - 0.5f) * UNITWIDTH;

					XR = 270.0f;
					YR = 0.0f;
					ZR = 0.0f;
				}
				else if(thePark.parkEntranceX > 64 && thePark.parkEntranceZ >= 64)
				{
					XV = 128 * UNITWIDTH;
					YV = thePark.parkEntranceY * UNITHEIGHT + PEEPHEIGHT;
					ZV = (thePark.parkEntranceZ - 0.5f) * UNITWIDTH;

					XR = 270.0f;
					YR = 0.0f;
					ZR = 0.0f;
				}
				else if(thePark.parkEntranceX < 64 && thePark.parkEntranceZ < 64)
				{
					XV = 0.0f;
					YV = thePark.parkEntranceY * UNITHEIGHT + PEEPHEIGHT;
					ZV = (thePark.parkEntranceZ - 0.5f) * UNITWIDTH;

					XR = 90.0f;
					YR = 0.0f;
					ZR = 0.0f;
				}
				else
				{
					XV = 0.0f;
					YV = 0.0f;
					ZV = 0.0f;

					XR = 0.0f;
					YR = 0.0f;
					ZR = 0.0f;
				}

				
			}

			XV = 0.0f;
			YV = 35.0f;
			ZV = 0.0f;

			XR = 135.0f;
			YR = 0.0f;
			ZR = 0.0f;

			lMousePressed = FALSE;
			rMousePressed = FALSE;

			DisplayMode = InGame;

			SetMenu(window.hWnd, NULL);
			isMenuVisible = false;

			NavMode = FreeMode;

			modeKeyDown = false;

			lastCDTrack = -1;

			//glViewport(0, 120, 640, 240);

			//runReport();
		}
	}
	else if(DisplayMode == InGame || DisplayMode == PausedInGame || DisplayMode == MapMode)
	{		
		/*
		char buf[80];
		char YRstr[10];
		char Detstr[20];
		*/

		if(lMousePressed == TRUE && NavMode == FreeMode && DisplayMode == InGame)
		{

			//printf("%f %f %f\n", XV, YV, ZV);
			//was the shift key pressed?
			if(g_keys->keyDown [16] == FALSE)
			{
				ZV+=(float)(-0.5f * cos(XR * M_PI / 180.0f));
				XV-=(float)(-0.5f * sin(XR * M_PI / 180.0f));
				YV+=(float)(-0.5f * sin(YR * M_PI / 180.0f));
			}
			else
			{
				ZV+=(float)(-2.5f * cos(XR * M_PI / 180.0f));
				XV-=(float)(-2.5f * sin(XR * M_PI / 180.0f));
				YV+=(float)(-2.5f * sin(YR * M_PI / 180.0f));
			}
		}

		if(rMousePressed == TRUE && NavMode == FreeMode && DisplayMode == InGame)
		{
			//was the shift key pressed?
			if(g_keys->keyDown [16] == FALSE)
			{
				ZV+=(float)(0.5f * cos(XR * M_PI / 180.0f));
				XV-=(float)(0.5f * sin(XR * M_PI / 180.0f));
				YV+=(float)(0.5f * sin(YR * M_PI / 180.0f));
			}
			else
			{
				ZV+=(float)(2.5f * cos(XR * M_PI / 180.0f));
				XV-=(float)(2.5f * sin(XR * M_PI / 180.0f));
				YV+=(float)(2.5f * sin(YR * M_PI / 180.0f));
			}
		}

		float objHeight;


		
		
		//GLfloat specular [] = { 1.0, 1.0, 1.0, 1.0 };
		
		//GLfloat shininess [] = { 1000.0 };
		//GLfloat position [] = { -372.0, -134.0, -1000.0, 0.0 };
		//GLfloat position [] = { 371.0f, 294.0f, 1000.0f, 0.0f };
		//GLfloat position [] = {
		//	1000.0f * sin((float)(YR)* 3.14f / 180.0f) * cos((float)(XR)* 3.14f / 180.0f),
		//	1000.0f * cos((float)(YR) * 3.14f / 180.0f),
		//	1000.0f * sin((float)(YR) * 3.14f / 180.0f) * sin((float)(XR)* 3.14f / 180.0f) };

		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		
		///glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
//
		//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		//glEnable(GL_COLOR_MATERIAL);

		//glLightfv(GL_LIGHT0, GL_POSITION, position);		
		
		

		glDisable (GL_BLEND);
		glEnable(GL_NORMALIZE);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		//glClearDepth(1.0f);
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glPushMatrix();


			if(DisplayMode == MapMode)
			{
				gluLookAt(XV, 200, ZV,
					XV, 0, ZV,
					cos((XR - 90.0f) * 3.14f / 180.0f), 0, sin((XR - 90.0f) * 3.14f / 180.0f));
				/*
				glRotated(XR,0.0f,0.0f,1.0f);				// Rotate The Triangle On The Y axis
				glRotated(90.0f,1.0f,0.0f,0.0f);
				glTranslated(-XV,-200,-ZV);						// Move Left 1.5 Units And Into The Screen 6.0	
				*/
			}
			else
			{
				/*
				gluLookAt(posVector[0], posVector[1], posVector[2],
					viewVector[0], viewVector[1], viewVector[2],
					upVector[0], upVector[1], upVector[2]);
					*/

				
				glRotated(YR,1.0f,0.0f,0.0f);				// Rotate The Triangle On The Y axis
				glRotated(XR,0.0f,1.0f,0.0f);
				glTranslated(-XV,-YV,-ZV);						// Move Left 1.5 Units And Into The Screen 6.0	
				
			}
			//glRotatef(rtri,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis

			objHeight = 32.0f;


//			int glError;
//			char errorstring[256];


			/*
			GLfloat position [] = { -371.0f, -250.0f, -1000.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glShadeModel(GL_SMOOTH);
			GLfloat ambient [] = { 0.75, 0.75, 0.75, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			*/
			
			
			ExtractFrustum();

			glEnable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);			

			if(DisplayMode != MapMode)
			{
				if(fogLevel != M_FOG_NONE)
					glDisable(GL_FOG);

				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//if(drawStars)
				{
					glDisable(GL_TEXTURE_2D);					

					glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
					//draw starfields
					glPointSize(1);
					glCallList(starfieldDisplayListA);
					//glPushMatrix();
					//	glRotatef(180,0,1,0);// flip over and reuse stars at double size
						glPointSize(2);
						glCallList(starfieldDisplayListB);
					//glPopMatrix();

					glEnable(GL_TEXTURE_2D);
				}
				
				//if(drawSky)
				{
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glShadeModel(GL_SMOOTH);
					glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
					//draw horizon gradient
					glBindTexture(GL_TEXTURE_2D,texture_id[TEXTURE_SKYDOME]);
					//myDrawSphere();
					//printf("drawing sky\n");
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_BLEND);
					//glShadeModel(GL_SMOOTH);
				}
	
				glDepthMask(GL_TRUE);

				//DrawSkyBox();

				if(fogLevel != M_FOG_NONE)
					glEnable(GL_FOG);
			}

			int a, b;

			int Mdetailsize = 20;
			int Hdetailsize = 50;
			int mapsize = 128;
			double gridX, gridZ;
			double startX, endX;
			double startZ, endZ;

			gridX = XV / UNITWIDTH;
			gridZ = ZV / UNITWIDTH;

			if(detailLevel == M_LOW_DETAIL || detailLevel == M_MEDIUM_DETAIL)
			{	
				//find the grid location of the viewpoint
				gridX = XV / UNITWIDTH;
				gridZ = ZV / UNITWIDTH;

				//printf("gridX:%d   gridZ:%d\n", gridX, gridZ);

				//precalculate the detailed regions to draw
				if (gridX - Mdetailsize < 0)
					startX = 0;
				else
					startX = gridX - Mdetailsize;

				if (gridX + Mdetailsize > mapsize)
					endX = mapsize;
				else
					endX = gridX + Mdetailsize;

				if (gridZ - Mdetailsize < 0)
					startZ = 0;
				else
					startZ = gridZ - Mdetailsize;

				if (gridZ + Mdetailsize > mapsize)
					endZ = mapsize;
				else
					endZ = gridZ + Mdetailsize;
			}
			else if(detailLevel == M_HIGH_DETAIL)
			{
				//find the grid location of the viewpoint
				gridX = XV / UNITWIDTH;
				gridZ = ZV / UNITWIDTH;

				//printf("gridX:%d   gridZ:%d\n", gridX, gridZ);

				//precalculate the detailed regions to draw
				if (gridX - Hdetailsize < 0)
					startX = 0;
				else
					startX = gridX - Hdetailsize;

				if (gridX + Hdetailsize > mapsize)
					endX = mapsize;
				else
					endX = gridX + Hdetailsize;

				if (gridZ - Hdetailsize < 0)
					startZ = 0;
				else
					startZ = gridZ - Hdetailsize;

				if (gridZ + Hdetailsize > mapsize)
					endZ = mapsize;
				else
					endZ = gridZ + Hdetailsize;
			}
			else
			{
				startX = 0;
				endX = mapsize;
				startZ = 0;
				endZ = mapsize;
			}			
			

			glCullFace(GL_BACK);

			glEnable(GL_CULL_FACE);

			DrawLandscape();

			glDisable(GL_CULL_FACE);			

			for(a=(int)startX; a<(int)endX; a++)
			{
				for(b=(int)startZ; b<(int)endZ; b++)
				{
					//float ones[3] = {1.0f, 1.0f, 1.0f};

					//glMaterialfv(GL_FRONT, GL_AMBIENT, ones);					
					
					DrawWalls(a, b);								
					
					DrawTrees1(a, b);				

					DrawElements(a, b);
					
					itemRot = 0;
					
					//glColor3f(1.0f, 1.0f, 1.0f);
					
					DrawPaths(a, b);
					
					DrawEntrances(a, b);					

					DrawBigScenery(a, b);

					itemRot = 0;
				}
			}
			

			

			
		glPopMatrix();

		int xTile, zTile;

		xTile = (int)(XV / UNITWIDTH);
		zTile = (int)(ZV / UNITWIDTH);

		int rideIndex, stringIndex;

		
		/*
		for(i=0; i<=thePark.elementCount[xTile][zTile]; i++)
		{
			rideIndex = thePark.elements[xTile][zTile][i].rideIndex;

			stringIndex = RideList[rideIndex].nameStringOffset;

			if(stringIndex > -1)
				printf("ride name (%d) (%d) (%d): %s\n", rideIndex, thePark.elements[xTile][zTile][i].identity, stringIndex, &thePark.nameStrings[stringIndex][0]);
		}
		*/
		

		if(blendSettings[3] > 0.0f)
		{
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(blendSettings[0], blendSettings[1],
				blendSettings[2], blendSettings[3]);
			glRectf(-1.0f, -1.0f, 1.0f, 1.0f);
			glDisable(GL_BLEND);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}

		

		glColor3f(0.8f, 0.8f, 0.8f);
		fNehe.SetBase(32);

		
		
		glDisable(GL_DEPTH_TEST);

		char buf[256];

		/*
		switch(thePark.cdTrack[(int)(XV / UNITWIDTH)][(int)(ZV / UNITWIDTH)])
		{
		case 1:
			sprintf(&buf[0], "Main Theme");
			break;
		case 2:
			sprintf(&buf[0], "Confisco");
			break;
		case 3:
			sprintf(&buf[0], "Ocean Trader");
			break;
		case 4:
			sprintf(&buf[0], "Welcome Seuss");
			break;
		case 5:
			sprintf(&buf[0], "Cat In The Hat");
			break;
		case 6:
			sprintf(&buf[0], "Circus McGurkus");
			break;
		case 7:
			sprintf(&buf[0], "Lost City");
			break;
		case 8:
			sprintf(&buf[0], "Arabian Street");
			break;
		case 9:
			sprintf(&buf[0], "Merlinwood");
			break;
		case 10:
			sprintf(&buf[0], "Jurassic Calypso");
			break;
		case 11:
			sprintf(&buf[0], "Camp Jurassic");
			break;
		case 12:
			sprintf(&buf[0], "Thunder Falls");
			break;
		case 13:
			sprintf(&buf[0], "Toon Walk");
			break;
		case 14:
			sprintf(&buf[0], "Jay Ward");
			break;
		case 15:
			sprintf(&buf[0], "Sweethaven");
			break;
		case 16:
			sprintf(&buf[0], "Funny Business");
			break;
		case 17:
			sprintf(&buf[0], "MSHI Street");
			break;
		case 18:
			sprintf(&buf[0], "Dr Doom");
			break;
		case 19:
			sprintf(&buf[0], "Baner Science Park");
			break;
		case 20:
			sprintf(&buf[0], "A Call...");
			break;
		default:
			sprintf(&buf[0], "No Music");
			break;
		}

		glDrawText(20,420,&buf[0]);

  */
		if(NavMode == PeepMode && inQueue == true)
		{
			thePark.nameStrings[RideList[queueRide].nameStringOffset][30] = '\x0';
			
			sprintf(&buf[0], "Queueing for: %s\n", thePark.nameStrings[RideList[queueRide].nameStringOffset]);
			//get rid of the funky char at the end of all the ride names
			buf[strlen(buf) - 1] = NULL;
			glDrawText(20,400,&buf[0]);

			int cnt;			

			switch(RideList[queueRide].rideType)
			{
			case 0x00:
				sprintf(&buf[0], "Wooden Roller Coaster");
				break;
			case 0x01:
				sprintf(&buf[0], "Stand-Up Roller Coaster");
				break;
			case 0x02:
				sprintf(&buf[0], "Suspended Roller Coaster");
				break;
			case 0x03:
				sprintf(&buf[0], "Inverted Roller Coaster");
				break;
			case 0x04:
				sprintf(&buf[0], "Steel Mini Roller Coaster");
				break;
			case 0x05:
				sprintf(&buf[0], "Miniature Railroad");
				break;
			case 0x06:
				sprintf(&buf[0], "Monorail");
				break;
			case 0x07:
				sprintf(&buf[0], "Suspended Single-Rail Coaster");
				break;
			case 0x08:
				sprintf(&buf[0], "Boat Hire");
				break;
			case 0x09:
				sprintf(&buf[0], "Wooden Wild Mouse Coaster");
				break;
			case 0x0A:
				sprintf(&buf[0], "Single-Rail Roller Coaster");
				break;
			case 0x0B:
				sprintf(&buf[0], "Car Ride");
				break;
			case 0x0C:
				sprintf(&buf[0], "Woah Belly");
				break;
			case 0x0D:
				sprintf(&buf[0], "Bobsled Roller Coaster");
				break;
			case 0x0E:
				sprintf(&buf[0], "Observation Tower");
				break;
			case 0x0F:
				sprintf(&buf[0], "Steel Roller Coaster");
				break;
			case 0x10:
				sprintf(&buf[0], "Water Slide");
				break;
			case 0x11:
				sprintf(&buf[0], "Mine Train Roller Coaster");
				break;
			case 0x12:
				sprintf(&buf[0], "Chairlift");
				break;
			case 0x13:
				sprintf(&buf[0], "Steel Corkscrew Roller Coaster");
				break;
			case 0x14:
				sprintf(&buf[0], "Hedge Maze");
				break;
			case 0x15:
				sprintf(&buf[0], "Spiral Slide");
				break;
			case 0x16:
				sprintf(&buf[0], "Go Karts");
				break;
			case 0x17:
				sprintf(&buf[0], "Log Flume");
				break;
			case 0x18:
				sprintf(&buf[0], "River Rapids");
				break;
			case 0x19:
				sprintf(&buf[0], "Bumper Cars");
				break;
			case 0x1A:
				sprintf(&buf[0], "Swinging Ship");
				break;
			case 0x1B:
				sprintf(&buf[0], "Swinging Inverter Ship");
				break;
			case 0x21:
				sprintf(&buf[0], "Merry-Go-Round");
				break;
			case 0x25:
				sprintf(&buf[0], "Ferris Wheel");
				break;
			case 0x26:
				sprintf(&buf[0], "Motion Simulator");
				break;
			case 0x27:
				sprintf(&buf[0], "3D Cinema");
				break;
			case 0x28:
				sprintf(&buf[0], "Gravitron");
				break;
			case 0x29:
				sprintf(&buf[0], "Space Rings");
				break;
			case 0x2A:
				sprintf(&buf[0], "Reverse Woah Belly Roller Coaster");
				break;
			case 0x2C:
				sprintf(&buf[0], "Vertical Roller Coaster");
				break;
			case 0x2E:
				sprintf(&buf[0], "Scrambled Eggs");
				break;
			case 0x2F:
				sprintf(&buf[0], "Haunted House");
				break;
			case 0x31:
				sprintf(&buf[0], "Circus Show");
				break;
			case 0x32:
				sprintf(&buf[0], "Ghost Train");
				break;
			case 0x33:
				sprintf(&buf[0], "Steel Twister Roller Coaster");
				break;
			case 0x34:
				sprintf(&buf[0], "Wooden Twister Roller Coaster");
				break;
			case 0x35:
				sprintf(&buf[0], "Wooden Side-Friction Roller Coaster");
				break;
			case 0x36:
				sprintf(&buf[0], "Steel Wild Mouse Roller Coaster");
				break;
			case 0x3B:
				sprintf(&buf[0], "Virginia Reel");
				break;
			case 0x3C:
				sprintf(&buf[0], "River Ride");
				break;
			case 0x3D:
				sprintf(&buf[0], "Cycle Monorail");
				break;
			case 0x3E:
				sprintf(&buf[0], "Flying Roller Coaster");
				break;
			case 0x3F:
				sprintf(&buf[0], "Suspended Monorail");
				break;
			case 0x41:
				sprintf(&buf[0], "Wooden Reverser Roller Coaster");
				break;
			case 0x42:
				sprintf(&buf[0], "Heartline Twister Roller Coaster");
				break;
			case 0x43:
				sprintf(&buf[0], "Miniature Golf");
				break;
			case 0x45:
				sprintf(&buf[0], "Roto Drop");
				break;
			case 0x46:
				sprintf(&buf[0], "Flying Saucers");
				break;
			case 0x47:
				sprintf(&buf[0], "Crooked House");
				break;
			case 0x48:
				sprintf(&buf[0], "Cycle Railway");
				break;
			case 0x49:
				sprintf(&buf[0], "Suspended Looping Coaster");
				break;
			case 0x4A:
				sprintf(&buf[0], "Water Coaster");
				break;
			case 0x4B:
				sprintf(&buf[0], "Air-Powerd Vertical Coaster");
				break;
			case 0x4C:
				sprintf(&buf[0], "Inverted Wild Mouse Coaster");
				break;
			case 0x4D:
				sprintf(&buf[0], "Jet Skis");
				break;
			case 0x4F:
				sprintf(&buf[0], "Raft Ride");
				break;
			case 0x51:
				sprintf(&buf[0], "Enterprise");
				break;
			default:
				sprintf(&buf[0], "(no ride found)");
				break;
			}

			glDrawText(20,430,&buf[0]);
		}
		
		/*
		if((int)(XV / UNITWIDTH) >= 0 && (int)(XV / UNITWIDTH) < 128)
		{
			if((int)(YV / UNITWIDTH) >= 0 && (int)(YV / UNITWIDTH) < 128)
			{
				if(lastCDTrack != thePark.cdTrack[(int)(XV / UNITWIDTH)][(int)(ZV / UNITWIDTH)])
				{
					lastCDTrack = thePark.cdTrack[(int)(XV / UNITWIDTH)][(int)(ZV / UNITWIDTH)];
					
					if(NavMode == PeepMode)
					{			
						if(lastCDTrack == -1)
							FSOUND_CD_SetPaused(0, TRUE);
						else
						{
							if(FSOUND_CD_GetPaused(0))
								FSOUND_CD_SetPaused(0, FALSE);

							FSOUND_CD_Play(0, lastCDTrack);
						}		
					}
				}
			}
			else
				FSOUND_CD_SetPaused(0, TRUE);
		}
		else
			FSOUND_CD_SetPaused(0, TRUE);
			*/



		//sprintf(&buf[0], "%5.2f, %5.2f, %5.2f", XV / UNITWIDTH, YV / UNITHEIGHT, ZV / UNITWIDTH);

		//glDrawText(300,380,&buf[0]);

		//sprintf(&buf[0], "%5.2f, %5.2f, %5.2f", XR, YR, ZR);

		//glDrawText(300,400,&buf[0]);
		
		if(DisplayMode == PausedInGame)
			glDrawText(500,420,"Paused");
		else if(DisplayMode == MapMode)
			glDrawText(500,420,"Overhead Map");
		else
			if(NavMode == FreeMode)
				glDrawText(500,420,"Free Mode");
			else if(NavMode == PeepMode)
				glDrawText(500,420,"Peep Mode");

		glEnable(GL_DEPTH_TEST);

		CalculateFrameRate();
		
	}

	glFlush ();													// Flush The GL Rendering Pipeline
}

void DrawSkyBox(void)
{
	float BoxSize = 2000.0f;
	float HalfBox = BoxSize / 2.0f;
	float OffsetBox = 400.0f;

	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();

		glTranslatef(-HalfBox, 0.0f, -HalfBox);
		//glTranslatef(-5.0f, -5.0f, -5.0f);

		glEnable(GL_TEXTURE_2D);
		glDisable( GL_ALPHA_TEST   );

		//glColor3f(0.0f, 0.0f, 1.0f);
		
		if(CubeInFrustum(-HalfBox, -OffsetBox, BoxSize - HalfBox,
						BoxSize, 2.0f * OffsetBox, 0.1f))
		{
			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYFRONT] );

			glBegin(GL_TRIANGLE_STRIP);			
						
				glTexCoord2f(0.995f, 0.995f);
				glVertex3f(BoxSize,  OffsetBox, BoxSize);
				glTexCoord2f(0.005f, 0.995f);
				glVertex3f(   0.0f,  OffsetBox, BoxSize);
				glTexCoord2f(0.995f, 0.005f);
				glVertex3f(BoxSize, -OffsetBox, BoxSize);
				glTexCoord2f(0.005f, 0.005f);
				glVertex3f(   0.0f, -OffsetBox, BoxSize);

			glEnd();			
		}
		
		

		if(CubeInFrustum(-HalfBox, -OffsetBox, -HalfBox,
						0.1f, 2.0f * OffsetBox, BoxSize))
		{
			

			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYLEFT] );

			glBegin(GL_TRIANGLE_STRIP);			
						
				glTexCoord2f(0.995f, 0.995f);
				glVertex3f(0.0f, OffsetBox, BoxSize);
				glTexCoord2f(0.005f, 0.995f);
				glVertex3f(0.0f, OffsetBox, 0.0f);
				glTexCoord2f(0.995f, 0.005f);
				glVertex3f(0.0f, -OffsetBox, BoxSize);
				glTexCoord2f(0.005f, 0.005f);
				glVertex3f(0.0f, -OffsetBox, 0.0f);

			glEnd();
		}	


		if(CubeInFrustum(-HalfBox, -OffsetBox, -HalfBox,
						BoxSize, 2.0f * OffsetBox, 0.1f))
		{
			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYBACK] );

			

			glBegin(GL_TRIANGLE_STRIP);			
						
				glTexCoord2f(0.995f, 0.995f);
				glVertex3f(   0.0f,  OffsetBox, 0.0f);
				glTexCoord2f(0.005f, 0.995f);
				glVertex3f(BoxSize,  OffsetBox, 0.0f);
				glTexCoord2f(0.995f, 0.005f);
				glVertex3f(   0.0f, -OffsetBox, 0.0f);
				glTexCoord2f(0.005f, 0.005f);
				glVertex3f(BoxSize, -OffsetBox, 0.0f);

			glEnd();
		}

		
		if(CubeInFrustum(BoxSize-HalfBox, -OffsetBox, -HalfBox,
						0.1f, 2.0f * OffsetBox, BoxSize))
		{
			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYRIGHT] );
			

			glBegin(GL_TRIANGLE_STRIP);			
						
				glTexCoord2f(0.995f, 0.995f);
				glVertex3f(BoxSize, OffsetBox, 0.0f);
				glTexCoord2f(0.005f, 0.995f);
				glVertex3f(BoxSize, OffsetBox, BoxSize);
				glTexCoord2f(0.995f, 0.005f);
				glVertex3f(BoxSize, -OffsetBox, 0.0f);
				glTexCoord2f(0.005f, 0.005f);
				glVertex3f(BoxSize, -OffsetBox, BoxSize);

			glEnd();	
		}	


		if(CubeInFrustum(-HalfBox, OffsetBox, -HalfBox,
						BoxSize, 0.1f, BoxSize))
		{
			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYUP] );

			glBegin(GL_TRIANGLE_STRIP);			
						
				glTexCoord2f(0.995f, 0.995f);
				glVertex3f(BoxSize, OffsetBox, 0.0f);
				glTexCoord2f(0.005f, 0.995f);
				glVertex3f(   0.0f, OffsetBox, 0.0f);
				glTexCoord2f(0.995f, 0.005f);
				glVertex3f(BoxSize, OffsetBox, BoxSize);
				glTexCoord2f(0.005f, 0.005f);
				glVertex3f(   0.0f, OffsetBox, BoxSize);

			glEnd();
		}

		if(CubeInFrustum(-HalfBox, -OffsetBox, -HalfBox,
						BoxSize, 0.1f, BoxSize))
		{
			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYDOWN] );

			glBegin(GL_TRIANGLE_STRIP);			
						
				glTexCoord2f(0.995f, 0.995f);
				glVertex3f(BoxSize, -OffsetBox, 0.0f);
				glTexCoord2f(0.005f, 0.995f);
				glVertex3f(   0.0f, -OffsetBox, 0.0f);
				glTexCoord2f(0.995f, 0.005f);
				glVertex3f(BoxSize, -OffsetBox, BoxSize);
				glTexCoord2f(0.005f, 0.005f);
				glVertex3f(   0.0f, -OffsetBox, BoxSize);

			glEnd();
		}
			
		
	glPopMatrix();


}


void ExtractFrustum(void)
{
	float   proj[16];
	float   modl[16];
	float   clip[16];
	float   t;

	/* Get the current PROJECTION matrix from OpenGL */
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	/* Combine the two matrices (multiply projection by modelview) */
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

	/* Extract the numbers for the RIGHT plane */
	frustum[0][0] = clip[ 3] - clip[ 0];
	frustum[0][1] = clip[ 7] - clip[ 4];
	frustum[0][2] = clip[11] - clip[ 8];
	frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = (float) sqrt(frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	frustum[1][0] = clip[ 3] + clip[ 0];
	frustum[1][1] = clip[ 7] + clip[ 4];
	frustum[1][2] = clip[11] + clip[ 8];
	frustum[1][3] = clip[15] + clip[12];

	/* Normalize the result */
	t = (float) sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	frustum[2][0] = clip[ 3] + clip[ 1];
	frustum[2][1] = clip[ 7] + clip[ 5];
	frustum[2][2] = clip[11] + clip[ 9];
	frustum[2][3] = clip[15] + clip[13];

	/* Normalize the result */
	t = (float) sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;

	/* Extract the TOP plane */
	frustum[3][0] = clip[ 3] - clip[ 1];
	frustum[3][1] = clip[ 7] - clip[ 5];
	frustum[3][2] = clip[11] - clip[ 9];
	frustum[3][3] = clip[15] - clip[13];

	/* Normalize the result */
	t = (float) sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;

	/* Extract the FAR plane */
	frustum[4][0] = clip[ 3] - clip[ 2];
	frustum[4][1] = clip[ 7] - clip[ 6];
	frustum[4][2] = clip[11] - clip[10];
	frustum[4][3] = clip[15] - clip[14];

	/* Normalize the result */
	t = (float) sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;

	/* Extract the NEAR plane */
	frustum[5][0] = clip[ 3] + clip[ 2];
	frustum[5][1] = clip[ 7] + clip[ 6];
	frustum[5][2] = clip[11] + clip[10];
	frustum[5][3] = clip[15] + clip[14];

	/* Normalize the result */
	t = (float) sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;
}


int CubeInFrustum( float x, float y, float z, float dx, float dy, float dz )
{
	int p;

	//return FALSE;

	for( p = 0; p < 6; p++ )
	{
		if( frustum[p][0] * x + frustum[p][1]        * y + frustum[p][2]        * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * y + frustum[p][2]        * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1]        * (y + dy) + frustum[p][2] * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * (y + dy) + frustum[p][2] * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1]        * y + frustum[p][2]        * (z + dz) + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * y + frustum[p][2]        * (z + dz) + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1]        * (y + dy) + frustum[p][2] * (z + dz) + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * (y + dy) + frustum[p][2] * (z + dz) + frustum[p][3] > 0 )
			continue;
		return FALSE;
	}

	return TRUE;
}


int CubeInFrustum2( float x, float y, float z, float width, float height, float depth )
{
	int p;	

	//return FALSE;

	for( p = 0; p < 6; p++ )
	{
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y - height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y - height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y + height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y + height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y - height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y - height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y + height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y + height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	return FALSE;
	}
	return TRUE;
}

int CalcDetail(float x, float y, float z)
{
	if ((fabs(XV - x) < MEDIUM_DETAIL_DISTANCE) && 
		(fabs(-YV - y) < MEDIUM_DETAIL_DISTANCE) &&
		(fabs(ZV - z) < MEDIUM_DETAIL_DISTANCE))
	{
		//glColor3f(1.0f, 0.0f, 0.0f);
		return 3;
	}
	else if ((fabs(XV - x) < LOW_DETAIL_DISTANCE) &&
		(fabs(-YV - y) < LOW_DETAIL_DISTANCE) &&
		(fabs(ZV - z) < LOW_DETAIL_DISTANCE))
	{
		//glColor3f(0.0f, 1.0f, 0.0f);
		return 2;
	}
	else
	{
		//glColor3f(0.0f, 0.0f, 1.0f);
		return 1;
	}
}

void set_material_color (float r, float g, float b)
{

	GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient_and_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[1] = { 50.0 };

	GLfloat LightConstant = 0.25;

	if (r<LightConstant)
		mat_specular[0] = mat_ambient_and_diffuse[0] = LightConstant;
	else
		mat_specular[0] = mat_ambient_and_diffuse[0] = r;

	if (g<LightConstant)
		mat_specular[1] = mat_ambient_and_diffuse[1] = LightConstant;
	else
		mat_specular[1] = mat_ambient_and_diffuse[1] = g;

	if (b<LightConstant)
		mat_specular[2] = mat_ambient_and_diffuse[2] = LightConstant;
	else
		mat_specular[2] = mat_ambient_and_diffuse[2] = b;


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
  
	glColor3f(r, g, b);
	
 
}
