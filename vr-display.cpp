#define CPWDLL_EXTERN
#include "basictemplate/cpw.h"
#include "vr3d.h"
#include "NeheGL.h"
#include "vr-displaymodes.h"
#include "skyDome.h"

#define PEEPHEIGHT 1.3

bool LoadedEdgeTex;
bool LoadedSurfaceTex;
bool LoadedTreeTex;
bool LoadedRideTex;
bool LoadedSkyTex;
bool LoadedPathTex;
bool LoadedWallTex;

extern bool UncompressedFile;
extern bool LoadedLandscape;
extern bool LoadedRides;
extern bool LoadedTrees;
extern bool LoadedPaths;
extern bool LoadedElements;
extern bool LoadedWalls;


extern displayModes displayMode;
extern CpwFontFace menuFont;


extern int minuteOfDay;
extern bool drawStars = true;
extern bool drawSky = true;

void LoadNames(char *filename);

extern float posVector[3];
extern float viewVector[3];
extern float upVector[3];

bool lMousePressed, rMousePressed;

enum NavModes { FreeMode, PeepMode };
extern NavModes NavMode;

extern int lastCDTrack;

extern GLuint starfieldDisplayListA;	//the small stars
extern GLuint starfieldDisplayListB;	//the bigger stars

void myDrawSphere(void);

extern int itemRot;
extern float blendSettings[4];

extern int queueRide;
bool inQueue;

extern skyDome *mySkyDome;

void drawRCTGLLogo(pCpw cpw)
{
	glRasterPos2d( 20, 480 - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
    cpwDrawFont( cpw, menuFont, "RctGL", 1 );

	glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
	glRasterPos2d( 250, 480 - 50);
	cpwDrawFont( cpw, menuFont, "Initializing", 1 );
}


void displayInit(pCpw cpw)
{
	glDisable(GL_TEXTURE_2D);

	drawRCTGLLogo(cpw);

	glRasterPos2d( 20, 480 - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
	cpwDrawFont( cpw, menuFont, "RctGL", 1 );

	glColor3f(0.75f, 0.75f, 0.75f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 25 );
	glRasterPos2d( 20, 480 - 90);
	cpwDrawFont( cpw, menuFont, "Loading Textures", 1 );		

	//print all the categories
	glRasterPos2d( 20, 480 - 110);
	cpwDrawFont( cpw, menuFont, "Edges", 1 );

	glRasterPos2d( 20, 480 - 140);
	cpwDrawFont( cpw, menuFont, "Surfaces", 1 );

	glRasterPos2d( 20, 480 - 170);
	cpwDrawFont( cpw, menuFont, "Paths", 1 );

	glRasterPos2d( 20, 480 - 200);
	cpwDrawFont( cpw, menuFont, "Trees", 1 );

	glRasterPos2d( 20, 480 - 230);
	cpwDrawFont( cpw, menuFont, "Rides", 1 );

	glRasterPos2d( 20, 480 - 260);
	cpwDrawFont( cpw, menuFont, "Sky", 1 );

	glRasterPos2d( 20, 480 - 290);
	cpwDrawFont( cpw, menuFont, "Walls", 1 );

	
	//go through the categories (boolean)
	if(LoadedEdgeTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 110);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}			
	if(LoadedSurfaceTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 140);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedPathTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 170);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedTreeTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 200);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedRideTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 230);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedSkyTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 260);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedWallTex == TRUE)
	{
		glRasterPos2d( 250, 480 - 290);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}	
	
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
		//change the display mode
		displayMode = MENU;			
	}
}


void displayParkLoad(pCpw cpw)
{
	int i, j, k;

	printf("in displayParkLoad()\n");

	glDisable(GL_TEXTURE_2D);

	//set up the time
	minuteOfDay = 540;
	drawStars = false;
	drawSky = true;
	drawRCTGLLogo(cpw);

	glRasterPos2d( 20, 480 - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
	cpwDrawFont( cpw, menuFont, "RctGL", 1 );

	glColor3f(0.75f, 0.75f, 0.75f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 25 );
	glRasterPos2d( 20, 480 - 90);
	cpwDrawFont( cpw, menuFont, "Loading Park", 1 );
	
	glRasterPos2d( 20, 480 - 110);
	cpwDrawFont( cpw, menuFont, "Decompressing", 1 );
	glRasterPos2d( 20, 480 - 140);
	cpwDrawFont( cpw, menuFont, "Landscape", 1 );
	glRasterPos2d( 20, 480 - 170);
	cpwDrawFont( cpw, menuFont, "Rides", 1 );
	glRasterPos2d( 20, 480 - 200);
	cpwDrawFont( cpw, menuFont, "Trees", 1 );
	glRasterPos2d( 20, 480 - 230);
	cpwDrawFont( cpw, menuFont, "Paths", 1 );
	glRasterPos2d( 20, 480 - 260);
	cpwDrawFont( cpw, menuFont, "Elements", 1 );
	glRasterPos2d( 20, 480 - 290);
	cpwDrawFont( cpw, menuFont, "Walls", 1 );
	
	
	if(UncompressedFile == TRUE)
	{
		glRasterPos2d( 250, 480 - 110);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedLandscape == TRUE)
	{
		glRasterPos2d( 250, 480 - 140);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedRides == TRUE)
	{
		glRasterPos2d( 250, 480 - 170);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedTrees == TRUE)
	{
		glRasterPos2d( 250, 480 - 200);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedPaths == TRUE)
	{
		glRasterPos2d( 250, 480 - 230);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedElements == TRUE)
	{
		glRasterPos2d( 250, 480 - 260);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}
	if(LoadedWalls == TRUE)
	{
		glRasterPos2d( 250, 480 - 290);
		cpwDrawFont( cpw, menuFont, "Done", 1 );
	}


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

		displayMode = GAME;

		//SetMenu(window.hWnd, NULL);
		//isMenuVisible = false;

		NavMode = FreeMode;

		//modeKeyDown = false;

		lastCDTrack = -1;
	}
}

void calcViewArea(double *startX, double *endX, double *startZ, double *endZ)
{
	int Mdetailsize = 20;
	int Hdetailsize = 50;
	int mapsize = 128;
	double gridX, gridZ;

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
			*startX = 0;
		else
			*startX = gridX - Mdetailsize;

		if (gridX + Mdetailsize > mapsize)
			*endX = mapsize;
		else
			*endX = gridX + Mdetailsize;

		if (gridZ - Mdetailsize < 0)
			*startZ = 0;
		else
			*startZ = gridZ - Mdetailsize;

		if (gridZ + Mdetailsize > mapsize)
			*endZ = mapsize;
		else
			*endZ = gridZ + Mdetailsize;
	}
	else if(detailLevel == M_HIGH_DETAIL)
	{
		//find the grid location of the viewpoint
		gridX = XV / UNITWIDTH;
		gridZ = ZV / UNITWIDTH;

		//printf("gridX:%d   gridZ:%d\n", gridX, gridZ);

		//precalculate the detailed regions to draw
		if (gridX - Hdetailsize < 0)
			*startX = 0;
		else
			*startX = gridX - Hdetailsize;

		if (gridX + Hdetailsize > mapsize)
			*endX = mapsize;
		else
			*endX = gridX + Hdetailsize;

		if (gridZ - Hdetailsize < 0)
			*startZ = 0;
		else
			*startZ = gridZ - Hdetailsize;

		if (gridZ + Hdetailsize > mapsize)
			*endZ = mapsize;
		else
			*endZ = gridZ + Hdetailsize;
	}
	else
	{
		*startX = 0;
		*endX = mapsize;
		*startZ = 0;
		*endZ = mapsize;
	}			

}


void displayGame(pCpw cpw)
{
	/*
	char buf[80];
	char YRstr[10];
	char Detstr[20];
	*/

	//printf("displaying park\n");

	if(lMousePressed == TRUE && NavMode == FreeMode && displayMode == GAME)
	{

		//printf("%f %f %f\n", XV, YV, ZV);
		//was the shift key pressed?
		//if(g_keys->keyDown [16] == FALSE)
		{
			ZV+=(float)(-0.5f * cos(XR * M_PI / 180.0f));
			XV-=(float)(-0.5f * sin(XR * M_PI / 180.0f));
			YV+=(float)(-0.5f * sin(YR * M_PI / 180.0f));
		}
		/*
		else
		{
			ZV+=(float)(-2.5f * cos(XR * M_PI / 180.0f));
			XV-=(float)(-2.5f * sin(XR * M_PI / 180.0f));
			YV+=(float)(-2.5f * sin(YR * M_PI / 180.0f));
		}
		*/
	}

	if(rMousePressed == TRUE && NavMode == FreeMode && displayMode == GAME)
	{
		//was the shift key pressed?
		//if(g_keys->keyDown [16] == FALSE)
		{
			ZV+=(float)(0.5f * cos(XR * M_PI / 180.0f));
			XV-=(float)(0.5f * sin(XR * M_PI / 180.0f));
			YV+=(float)(0.5f * sin(YR * M_PI / 180.0f));
		}
		/*
		else
		{
			ZV+=(float)(2.5f * cos(XR * M_PI / 180.0f));
			XV-=(float)(2.5f * sin(XR * M_PI / 180.0f));
			YV+=(float)(2.5f * sin(YR * M_PI / 180.0f));
		}
		*/
	}

	float objHeight;

	detailLevel = M_HIGH_DETAIL;


	
	
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


		if(displayMode == MAP)
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

		double startX, endX;
		double startZ, endZ;

		calcViewArea(&startX, &endX, &startZ, &endZ);
		
		
		ExtractFrustum();

		glEnable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);			

		if(displayMode != MAP)
		{
			if(fogLevel != M_FOG_NONE)
				glDisable(GL_FOG);

			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPushMatrix();
				glTranslatef(XV, YV, ZV);
				mySkyDome->draw();			
			glPopMatrix();

			glDepthMask(GL_TRUE);

			//DrawSkyBox();

			if(fogLevel != M_FOG_NONE)
				glEnable(GL_FOG);
		}

		int a, b;

		

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
				
				//printf("drawing walls\n");
				
				DrawWalls(a, b);		
				
				//printf("drawing trees\n");
				
				DrawTrees1(a, b);	
				
				//printf("drawing elements\n");

				DrawElements(a, b);
				
				itemRot = 0;
				
				//glColor3f(1.0f, 1.0f, 1.0f);

				//printf("drawing paths\n");
				
				DrawPaths(a, b);

				//printf("drawing entrances\n");
				
				DrawEntrances(a, b);	
				
				//printf("drawing big scenery\n");

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
	//fNehe.SetBase(32);

	
	
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
		//glDrawText(20,400,&buf[0]);

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

		//glDrawText(20,430,&buf[0]);
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
	
	/*
	if(displayMode == PAUSED)
		glDrawText(500,420,"Paused");
	else if(displayMode == MAP)
		glDrawText(500,420,"Overhead Map");
	else
		if(NavMode == FreeMode)
			glDrawText(500,420,"Free Mode");
		else if(NavMode == PeepMode)
			glDrawText(500,420,"Peep Mode");
			*/

	glEnable(GL_DEPTH_TEST);

	//CalculateFrameRate();
}