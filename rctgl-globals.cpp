#include "rctgl.h"
#include "rctgl-displaymodes.h"


float RCTColorsR[RCT_NUM_COLORS];
float RCTColorsG[RCT_NUM_COLORS];
float RCTColorsB[RCT_NUM_COLORS];

float sinTable[360];
float cosTable[360];
float tanTable[360];

char RCTGL_Location[256];
char RCTGL_TempFile[256];
char RCTGL_InFile[256];

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

displayModes displayMode;

NavModes navMode;



