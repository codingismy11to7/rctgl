#ifndef RCTGL_H
#define RCTGL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>



#define CPWDLL_EXTERN
#define CPWDLL_LOC "depend//cpw//cpw.h"

#pragma comment(lib, "depend//corona//corona.lib")

#pragma warning(disable:4786)
#pragma warning(disable:4503)

#include "rctgl-displaymodes.h"
#include "rctgl-camera.h"
#include "rctgl-frustum.h"
#include "DebugLog.h"

typedef unsigned char uchar;

static const uchar RCT_NUM_COLORS = 32;

static const float UNITWIDTH	= 3.2f;
static const float UNITHEIGHT = 1.3f;

extern float RCTColorsR[RCT_NUM_COLORS];
extern float RCTColorsG[RCT_NUM_COLORS];
extern float RCTColorsB[RCT_NUM_COLORS];

extern float sinTable[360];
extern float cosTable[360];
extern float tanTable[360];

extern string RCTGL_Location;
extern string RCTGL_TempFile;
extern string RCTGL_InFile;

extern bool LoadedEdgeTex;
extern bool LoadedSurfaceTex;
extern bool LoadedTreeTex;
extern bool LoadedRideTex;
extern bool LoadedSkyTex;
extern bool LoadedPathTex;
extern bool LoadedWallTex;

extern bool UncompressedFile;
extern bool LoadedLandscape;
extern bool LoadedRides;
extern bool LoadedTrees;
extern bool LoadedPaths;
extern bool LoadedElements;
extern bool LoadedWalls;

extern displayModes displayMode;

enum NavModes { FreeMode, PeepMode };

extern NavModes navMode;

extern RCTGLCamera userView;

extern RCTGLFrustum theFrustum;

#endif
