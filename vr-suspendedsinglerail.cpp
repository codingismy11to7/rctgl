#include "vr3d.h" 
#include "vr-tracks.h"
#include "vr-suspendedsinglerail.h"

#define SUSPENDEDSINGLERAIL_LEFTBEAM		0.45f
#define SUSPENDEDSINGLERAIL_RIGHTBEAM	0.55f
#define SUSPENDEDSINGLERAIL_TOPBEAM		0.2f
#define SUSPENDEDSINGLERAIL_BOTTOMBEAM	0.4f
#define SUSPENDEDSINGLERAIL_RAILHEIGHT	0.5f
#define SUSPENDEDSINGLERAIL_LEFTRAIL		0.25f
#define SUSPENDEDSINGLERAIL_RIGHTRAIL	0.75f
#define SUSPENDEDSINGLERAIL_RAILDIAMETER	0.1f

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];

//flat piece
void DrawSuspendedSingleRail_00(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	trackInfo thisTrack;
	thisTrack.startAngle = 0.0f;
	thisTrack.endAngle = 0.0f;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);	
}

// 25 degree up hill
void DrawSuspendedSingleRail_04(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = UNITHEIGHT;

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);
}


//flat to 25 up
void DrawSuspendedSingleRail_06(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);


}



//25 up -> flat
void DrawSuspendedSingleRail_09(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

}


//25 degree drop
void DrawSuspendedSingleRail_0A(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);


}



//flat to 25 down
void DrawSuspendedSingleRail_0C(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);


}

//25 down to flat
void DrawSuspendedSingleRail_0F(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);
}


//left 1/4 D5
void DrawSuspendedSingleRail_10(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D5
void DrawSuspendedSingleRail_11(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.0f * UNITWIDTH);
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}


//flat piece
void DrawSuspendedSingleRail_26(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();


	glDisable(GL_TEXTURE_2D);

}


//flat piece
void DrawSuspendedSingleRail_27(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	SUSPENDEDSINGLERAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * SUSPENDEDSINGLERAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();


	glDisable(GL_TEXTURE_2D);

}



//left 1/4 D3 turn
void DrawSuspendedSingleRail_2A(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawRoundTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D3 turn
void DrawSuspendedSingleRail_2B(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.0f * UNITWIDTH);
		drawRoundTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}




//left 1/8 turn OTD
void DrawSuspendedSingleRail_85(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;
	float rad = 3.0f;

	step = 9.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);

	glEnable(GL_TEXTURE_2D);
	

	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (rad  + SUSPENDEDSINGLERAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + SUSPENDEDSINGLERAIL_RIGHTBEAM) * UNITWIDTH;

	for(i=0.0f; i<45.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);			
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		
		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		
		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


//right 1/8 turn OTD
void DrawSuspendedSingleRail_86(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 9.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float rad = 3.0f;


	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);


	//draw the beam
	radius1 = (rad + SUSPENDEDSINGLERAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + SUSPENDEDSINGLERAIL_RIGHTBEAM) * UNITWIDTH;

	glEnable(GL_TEXTURE_2D);
	

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0.0f; i<45.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );
		
		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


//left 1/8 turn DTO
void DrawSuspendedSingleRail_87(int rideIndex, int colorIndex)
{	
	double radius1, radius2;
	float i, step;

	step = 9.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float rad = 3.0f;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	
	glEnable(GL_TEXTURE_2D);

	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (rad  + SUSPENDEDSINGLERAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + SUSPENDEDSINGLERAIL_RIGHTBEAM) * UNITWIDTH;

	for(i=45.0f; i<90.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


//right 1/8 turn DTO
void DrawSuspendedSingleRail_88(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 9.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float rad = 3.0f;

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);


	//draw the beam
	radius1 = (rad + SUSPENDEDSINGLERAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + SUSPENDEDSINGLERAIL_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glEnable(GL_TEXTURE_2D);
	
	for(i=45.0f; i<90.0f; i+=step)
	{		
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();


		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (SUSPENDEDSINGLERAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void DrawSuspendedSingleRail_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSuspendedSingleRail_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSuspendedSingleRail_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSuspendedSingleRail_04(rideIndex, colorIndex, true);

	glPopMatrix();
}



void DrawSuspendedSingleRail_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSuspendedSingleRail_06(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSuspendedSingleRail_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSuspendedSingleRail_09(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSuspendedSingleRail_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSuspendedSingleRail_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}



void DrawSuspendedSingleRail_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSuspendedSingleRail_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}


