#include "vr3d.h"
#define STEEL_ANGLEHEIGHT	1.5f

//level track
void DrawSteelRC_00(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );


	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 25 up
void DrawSteelRC_04(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 60 up
void DrawSteelRC_05(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	4.0f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	4.0f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	4.0f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	4.0f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// flat -> 25 up
void DrawSteelRC_06(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 25 up -> 60 up
void DrawSteelRC_07(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	2.0f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	2.0f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	2.0f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	2.0f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//25 down
void DrawSteelRC_0A(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//60 down
void DrawSteelRC_0B(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		4.0f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		4.0f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		4.0f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		4.0f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//flat -> 25 down
void DrawSteelRC_0C(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//25 down -> 60 down
void DrawSteelRC_0D(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		2.0f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		2.0f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		2.0f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		2.0f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//d5 left
void DrawSteelRC_10(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 2.0f * UNITWIDTH;
	radius2 = 3.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


//d5 right
void DrawSteelRC_11(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 3.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

//flat --> L bank
void DrawSteelRC_12(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);

		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT + 0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//flat - > R bank
void DrawSteelRC_13(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT + 0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//L bank -> flat
void DrawSteelRC_14(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);

		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//R bank -> flat
void DrawSteelRC_15(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT + 0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//d5 left banked
void DrawSteelRC_16(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 2.0f * UNITWIDTH;
	radius2 = 3.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


//d5 right banked
void DrawSteelRC_17(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 3.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


// L bank -> 25 up
void DrawSteelRC_18(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


// R bank -> 25 up
void DrawSteelRC_19(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 25 up -> L bank
void DrawSteelRC_1A(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f + STEEL_ANGLEHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


// 25 up -> R bank
void DrawSteelRC_1B(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//L bank -> 25 down
void DrawSteelRC_1C(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//R bank -> 25 down
void DrawSteelRC_1D(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + STEEL_ANGLEHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//25 down -> L bank
void DrawSteelRC_1E(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT ,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT + 0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//25 down -> R bank
void DrawSteelRC_1F(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT + 0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//L bank
void DrawSteelRC_20(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT + 0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT + 0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//R bank
void DrawSteelRC_21(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		STEEL_ANGLEHEIGHT + 0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	STEEL_ANGLEHEIGHT + 0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//left 1/4 D5 up 25
void DrawSteelRC_22(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;


	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glColor3f(1.0f, 1.0f, 1.0f);

	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (2.0f) * UNITWIDTH;

	heightCount = 0.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f ) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	heightCount = 0.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f ) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//right 1/4 D5 up 25
void DrawSteelRC_23(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//draw the beam
	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (2.0f) * UNITWIDTH;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, 1.0f * UNITWIDTH);
	

		glColor3f(1.0f, 1.0f, 1.0f);
	
	heightCount= 0.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	heightCount= 0.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glPopMatrix();

}

//left 1/4 D5 down 25
void DrawSteelRC_24(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;


	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glColor3f(1.0f, 1.0f, 1.0f);

	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (2.0f) * UNITWIDTH;

	heightCount = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, -0.0f * UNITWIDTH);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f ) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	heightCount = 1.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f ) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);



}


//right 1/4 D5 down 25
void DrawSteelRC_25(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//draw the beam
	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (2.0f) * UNITWIDTH;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, 0.0f * UNITWIDTH);
	

		glColor3f(1.0f, 1.0f, 1.0f);
	
	heightCount= 1.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}


	heightCount= 1.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	glPopMatrix();

}



//d3 left
void DrawSteelRC_2A(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 1.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	


	glPushMatrix();

		glTranslated(0.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//d3 right
void DrawSteelRC_2B(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 2.0f * UNITWIDTH;
	radius2 = 1.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//d3 left banked
void DrawSteelRC_2C(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 1.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	


	glPushMatrix();

		glTranslated(0.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//d3 right banked
void DrawSteelRC_2D(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	double degrees[5];
	int i;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//water
	radius1 = 2.0f * UNITWIDTH;
	radius2 = 1.0f * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}

//left 1/4 D3 up 25
void DrawSteelRC_2E(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;


	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glColor3f(1.0f, 1.0f, 1.0f);

	radius1 = (2.0f) * UNITWIDTH;
	radius2 = (1.0f) * UNITWIDTH;

	heightCount = 0.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, 0.0f * UNITWIDTH);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 0.5f) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 0.5f ) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	heightCount = 0.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 0.5f) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 0.5f ) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}

	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//right 1/4 D3 up 25
void DrawSteelRC_2F(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//draw the beam
	radius1 = (2.0f) * UNITWIDTH;
	radius2 = (1.0f) * UNITWIDTH;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, 0.0f * UNITWIDTH);
	

		glColor3f(1.0f, 1.0f, 1.0f);
	
	heightCount= 0.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}

	heightCount= 0.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}

	glPopMatrix();

}

//left 1/4 D3 down 25
void DrawSteelRC_30(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;


	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glColor3f(1.0f, 1.0f, 1.0f);

	radius1 = (2.0f) * UNITWIDTH;
	radius2 = (1.0f) * UNITWIDTH;

	heightCount = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, 1.0f * UNITWIDTH);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f ) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}

	heightCount = 1.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f ) * UNITHEIGHT + 0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}

	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);



}


//right 1/4 D3 down 25
void DrawSteelRC_31(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	float heightCount;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//draw the beam
	radius1 = (2.0f) * UNITWIDTH;
	radius2 = (1.0f) * UNITWIDTH;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);
	

		glColor3f(1.0f, 1.0f, 1.0f);
	
	heightCount= 1.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 0.5f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 0.5f) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}


	heightCount= 1.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 0.5f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 0.5f) * UNITHEIGHT + 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}

	glPopMatrix();

}

//left 1/8 turn OTD
void DrawSteelRC_85(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	glColor3f(1.0f, 1.0f, 1.0f);

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );


	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	glEnable(GL_TEXTURE_2D);
	

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	
		radius1 = (3.0f) * UNITWIDTH;
		radius2 = (4.0f) * UNITWIDTH;

		glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
		
		for(i=0; i<4; i++)
		{
		
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glEnd();
		}

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
		
		for(i=0; i<4; i++)
		{
		
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glEnd();
		}

		glPopMatrix();
}



//right 1/8 turn OTD
void DrawSteelRC_86(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	


	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	//draw the beam
	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (4.0f) * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



void DrawSteelRC_87(int rideIndex, int colorIndex)
{	
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	


	//draw the beam
	glColor3f(1.0f, 1.0f, 1.0f);

	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (4.0f) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



//right 1/8 turn DTO
void DrawSteelRC_88(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	int i;

	
	glColor3f(1.0f, 1.0f, 1.0f);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	//draw the beam
	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (4.0f) * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//left 1/8 turn OTD banked
void DrawSteelRC_89(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	glColor3f(1.0f, 1.0f, 1.0f);

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );


	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	glEnable(GL_TEXTURE_2D);
	

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	
		radius1 = (3.0f) * UNITWIDTH;
		radius2 = (4.0f) * UNITWIDTH;

		glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
		
		for(i=0; i<4; i++)
		{
		
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i]),  0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i+1]),0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glEnd();
		}

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
		
		for(i=0; i<4; i++)
		{
		
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i]),  0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i+1]),0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glEnd();
		}

		glPopMatrix();
}



//right 1/8 turn OTD banked
void DrawSteelRC_8A(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	


	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	//draw the beam
	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (4.0f) * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



void DrawSteelRC_8B(int rideIndex, int colorIndex)
{	
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	


	//draw the beam
	glColor3f(1.0f, 1.0f, 1.0f);

	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (4.0f) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),0.0f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),0.05f + STEEL_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



//right 1/8 turn DTO banked
void DrawSteelRC_8C(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	int i;

	
	glColor3f(1.0f, 1.0f, 1.0f);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	//draw the beam
	radius1 = (3.0f) * UNITWIDTH;
	radius2 = (4.0f) * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_01] );
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.0f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0F_00] );
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.05f + STEEL_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


/*====================================
 *======= Diagonal Segments ==========
 *====================================
 */
void DrawSteelRC_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_04(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelRC_8F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_05(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_06(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_91(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_06(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelRC_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_95(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_0B(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_97(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_0D(rideIndex, colorIndex, true);

	glPopMatrix();
}



void DrawSteelRC_9E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_12(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_9F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_13(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A0(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_14(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A1(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_15(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A2(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_18(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A3(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_19(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A4(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_1A(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A5(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_1B(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A6(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_1C(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A7(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_1D(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A8(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_1E(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_A9(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_1F(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelRC_AA(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_20(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelRC_AB(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelRC_21(rideIndex, colorIndex, true);

	glPopMatrix();
}




