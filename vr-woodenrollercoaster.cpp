#include "vr3d.h"
#include "vr-wooden.h"


void drawStraightTexturedTrack(float color[3], unsigned int texID, trackInfo thePiece, int frontBank, int backBank, bool doDiag)
{
	double segWid;

	if(thePiece.startAngle < 0)
		thePiece.startAngle += 360;
	if(thePiece.endAngle < 0)
		thePiece.endAngle += 360;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	double startVal, endVal;
	float r1, g1, b1;
	float r2, g2, b2;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glShadeModel(GL_SMOOTH);
		
	glBindTexture (GL_TEXTURE_2D, texID );
	
	//draw the bottom side
	startVal = calcLightFactor(-sinTable[thePiece.startAngle], -cosTable[thePiece.startAngle], 0.0f);
	endVal = calcLightFactor(-sinTable[thePiece.endAngle], -cosTable[thePiece.endAngle], 0.0f);

	calcColor(color, startVal, &r1, &g1, &b1);
	calcColor(color, endVal, &r2, &g2, &b2);	

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		thePiece.startHeight, 0.0f);		
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		thePiece.startHeight, segWid * UNITWIDTH);
		glColor3f(r2, g2, b2);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	thePiece.endHeight, segWid * UNITWIDTH);		
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	thePiece.endHeight, 0.0f);
	glEnd();


	//draw the other side
	startVal = calcLightFactor(sinTable[thePiece.startAngle], cosTable[thePiece.startAngle], 0.0f);
	endVal = calcLightFactor(sinTable[thePiece.endAngle], cosTable[thePiece.endAngle], 0.0f);

	calcColor(color, startVal, &r1, &g1, &b1);
	calcColor(color, endVal, &r2, &g2, &b2);	

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		thePiece.startHeight, 0.0f);
		glColor3f(r2, g2, b2);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	thePiece.endHeight, 0.0f);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	thePiece.endHeight, segWid * UNITWIDTH);
		glColor3f(r1, g1, b1);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		thePiece.startHeight, segWid * UNITWIDTH);		
	glEnd();


	glShadeModel(GL_FLAT);


	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
}

//level track
void DrawWoodenRC_00(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 0;
	trIn.startHeight = 0;
	trIn.endAngle = 0;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight = 0.05;
	trIn.endHeight = 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}

// 25 up
void DrawWoodenRC_04(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 25;
	trIn.startHeight = 0;
	trIn.endAngle = 25;
	trIn.endHeight = UNITHEIGHT;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}

// 60 up
void DrawWoodenRC_05(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 60;
	trIn.startHeight = 0;
	trIn.endAngle = 60;
	trIn.endHeight = 4.0f * UNITHEIGHT;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}

// flat -> 25 up
void DrawWoodenRC_06(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 0;
	trIn.startHeight = 0;
	trIn.endAngle = 25;
	trIn.endHeight = 0.5f * UNITHEIGHT;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}

// 25 up -> 60 up
void DrawWoodenRC_07(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 25;
	trIn.startHeight = 0;
	trIn.endAngle = 60;
	trIn.endHeight = 2.0f * UNITHEIGHT;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


// 60 up -> 25 up
void DrawWoodenRC_08(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 60;
	trIn.startHeight = 0;
	trIn.endAngle = 25;
	trIn.endHeight = 2.0f * UNITHEIGHT;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


// 25 up ->flat
void DrawWoodenRC_09(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 25;
	trIn.startHeight = 0;
	trIn.endAngle = 0;
	trIn.endHeight = 0.5f * UNITHEIGHT;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


//25 down
void DrawWoodenRC_0A(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = -25;
	trIn.startHeight = UNITHEIGHT;
	trIn.endAngle = -25;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


//60 down
void DrawWoodenRC_0B(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = -60;
	trIn.startHeight = 4.0f * UNITHEIGHT;
	trIn.endAngle = -60;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


//flat -> 25 down
void DrawWoodenRC_0C(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = 0;
	trIn.startHeight = 0.5f * UNITHEIGHT;
	trIn.endAngle = -25;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


//25 down -> 60 down
void DrawWoodenRC_0D(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = -25;
	trIn.startHeight = 2.0f * UNITHEIGHT;
	trIn.endAngle = -60;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


//60 down -> 25 down
void DrawWoodenRC_0E(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = -60;
	trIn.startHeight = 2.0f * UNITHEIGHT;
	trIn.endAngle = -25;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}


//25 down -> flat
void DrawWoodenRC_0F(int rideIndex, int colorIndex, bool isDiag)
{
	trackInfo trIn;

	trIn.startAngle = -25;
	trIn.startHeight = 0.5f * UNITHEIGHT;
	trIn.endAngle = 0;
	trIn.endHeight = 0;

	float itemColor[3]; 

	itemColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_01], 
		trIn, 0, 0, isDiag);

	trIn.startHeight += 0.05;
	trIn.endHeight += 0.05;

	itemColor[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	itemColor[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];


	drawStraightTexturedTrack(itemColor, texture_id[TEXTURE_RIDE_00_00], 
		trIn, 0, 0, isDiag);
}



//d5 left
void DrawWoodenRC_10(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
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
void DrawWoodenRC_11(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
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
void DrawWoodenRC_12(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);

		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT + 0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//flat - > R bank
void DrawWoodenRC_13(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT + 0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//L bank -> flat
void DrawWoodenRC_14(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);

		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);

		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//R bank -> flat
void DrawWoodenRC_15(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT, 0.0f);
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT + 0.05f, 0.0f);
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
void DrawWoodenRC_16(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


//d5 right banked
void DrawWoodenRC_17(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


// L bank -> 25 up
void DrawWoodenRC_18(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


// R bank -> 25 up
void DrawWoodenRC_19(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT,		0.0f);
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT + 0.05f,		0.0f);
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
void DrawWoodenRC_1A(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f + WOODEN_ANGLEHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


// 25 up -> R bank
void DrawWoodenRC_1B(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT,	0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + 0.05f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT + 0.05f,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//L bank -> 25 down
void DrawWoodenRC_1C(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//R bank -> 25 down
void DrawWoodenRC_1D(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT,		0.0f);
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + WOODEN_ANGLEHEIGHT + 0.05f,		0.0f);
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
void DrawWoodenRC_1E(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT ,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT + 0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//25 down -> R bank
void DrawWoodenRC_1F(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT,			0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT + 0.05f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT + 0.05f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//L bank
void DrawWoodenRC_20(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT + 0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT + 0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//R bank
void DrawWoodenRC_21(int rideIndex, int colorIndex, bool isDiag)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT, 0.0f);
	glEnd();

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		WOODEN_ANGLEHEIGHT + 0.05f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.05f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	WOODEN_ANGLEHEIGHT + 0.05f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//left 1/4 D5 up 25
void DrawWoodenRC_22(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
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
void DrawWoodenRC_23(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

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
void DrawWoodenRC_24(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	
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
void DrawWoodenRC_25(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

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
void DrawWoodenRC_2A(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

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
void DrawWoodenRC_2B(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
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
void DrawWoodenRC_2C(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//d3 right banked
void DrawWoodenRC_2D(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sin(degrees[i+1]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sin(degrees[i+1]),	0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}

//left 1/4 D3 up 25
void DrawWoodenRC_2E(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
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
void DrawWoodenRC_2F(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

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
void DrawWoodenRC_30(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	
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
void DrawWoodenRC_31(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

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
void DrawWoodenRC_85(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
		
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
		
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
void DrawWoodenRC_86(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	
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



void DrawWoodenRC_87(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

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
void DrawWoodenRC_88(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	
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
void DrawWoodenRC_89(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
		
		for(i=0; i<4; i++)
		{
		
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i]),  0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i+1]),0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glEnd();
		}

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
		
		for(i=0; i<4; i++)
		{
		
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i]),  0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sin(degrees[i+1]),0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glEnd();
		}

		glPopMatrix();
}



//right 1/8 turn OTD banked
void DrawWoodenRC_8A(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



void DrawWoodenRC_8B(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),0.0f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),0.0f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),  0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]),  0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]),0.05f + WOODEN_ANGLEHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]),0.05f, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



//right 1/8 turn DTO banked
void DrawWoodenRC_8C(int rideIndex, int colorIndex)
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
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_01] );
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.0f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i+1]), 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]],
		RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_00_00] );
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sin(degrees[i]),	0.05f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i]), 	0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sin(degrees[i+1]), 0.05f + WOODEN_ANGLEHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
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
void DrawWoodenRC_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_04(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawWoodenRC_8F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_05(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_06(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_91(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_06(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawWoodenRC_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_95(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_0B(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_97(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_0D(rideIndex, colorIndex, true);

	glPopMatrix();
}



void DrawWoodenRC_9E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_12(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_9F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_13(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A0(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_14(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A1(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_15(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A2(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_18(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A3(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_19(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A4(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_1A(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A5(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_1B(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A6(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_1C(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A7(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_1D(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A8(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_1E(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_A9(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_1F(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawWoodenRC_AA(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_20(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawWoodenRC_AB(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawWoodenRC_21(rideIndex, colorIndex, true);

	glPopMatrix();
}




