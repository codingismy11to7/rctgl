#include "vr3d.h"

//here's the actual definition of our global variables
TreeStructType TreeList[15876]; //make a 126x126 array



int TreeListSize;


PathStructType PathList[15876]; //make a 126x126 array
int PathListSize;

ElementStructType ElementList[15876]; //make a 126x126 array
int ElementListSize;

RideStructType RideList[256]; 
int RideListSize;

//GLint wid;
unsigned int sceneID;

int FileFormat;		/* indicates whether data is in RCT format (0)
					   or CF/LL format (1) */

int StationColor[3];	/* make the station red */
int LiftColor[3];		/* make the lift green */
int TrackColor[3];	/* make the regular track blue */

//GLuint sceneID;

//GLint wid;

//char *tempfile;

GLint wid, /* GLUT window id               */
      vpd; /* (square) viewport dimensions */





/* Globals */
float	rtri;
float	rquad;

int TrackOrientationsDeg[8];
float TrackOrientationsRad[8];

int TOrientation;		// track orientation. used when drawing the track
int TOrientationOrig;	// track orientation. used when drawing the track

int TrackLength;
int TrackLayout[500];
TrackStructType TrackSetup[500];

float XV, YV, ZV;
float XR, YR, ZR;

float xWaterOffset;
float zWaterOffset;

int FrameCount;
float FrameRate;

int wd,hd;

/* display lists */
GLuint LANDSCAPE_LIST;


int detailLevel;


int framecount;

Texture textures[NUMTEXTURES];

GLuint texture_id[NUMTEXTURES];

int lastmousex, lastmousey;

int InclineDegrees;

long NumPolys;


landscape_t parkLandscape[128][128];


//frustum information
float frustum[6][4];		//6 planes - 4 vals per plane

float RCTColorsR[32];
float RCTColorsG[32];
float RCTColorsB[32];
