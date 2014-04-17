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

#include "rctgl-displaymodes.h"
#include "debuglog.h"

#define RCT_NUM_COLORS 32

#define UNITWIDTH	3.2
#define UNITHEIGHT	1.3

extern float RCTColorsR[RCT_NUM_COLORS];
extern float RCTColorsG[RCT_NUM_COLORS];
extern float RCTColorsB[RCT_NUM_COLORS];

extern float sinTable[360];
extern float cosTable[360];
extern float tanTable[360];

extern char RCTGL_Location[256];
extern char RCTGL_TempFile[256];
extern char RCTGL_InFile[256];

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

extern debugLog RCTGLLog;

#endif