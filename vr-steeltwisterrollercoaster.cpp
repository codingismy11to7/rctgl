#include "vr3d.h" 
#include "vr-steeltwister.h"

#define LEFTBEAM		0.45f
#define RIGHTBEAM	0.55f
#define TOPBEAM		0.2f
#define BOTTOMBEAM	0.4f
#define RAILHEIGHT	0.5f
#define LEFTRAIL		0.25f
#define RIGHTRAIL	0.75f
#define RAILDIAMETER	0.1f




extern int itemRot;

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];


//flat piece
void DrawSteelTwisterRollerCoaster_00(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

// 25 degree up hill
void DrawSteelTwisterRollerCoaster_04(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 degree up hill
void DrawSteelTwisterRollerCoaster_05(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 60;
	thisTrack.endAngle = 60;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 4.0f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//flat to 25 up
void DrawSteelTwisterRollerCoaster_06(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//25 -> 60 up
void DrawSteelTwisterRollerCoaster_07(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 60;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 2.0f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 -> 25 up
void DrawSteelTwisterRollerCoaster_08(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 60;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 2.0f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//25 up -> flat
void DrawSteelTwisterRollerCoaster_09(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//25 degree drop
void DrawSteelTwisterRollerCoaster_0A(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 degree drop
void DrawSteelTwisterRollerCoaster_0B(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -60;
	thisTrack.endAngle = -60;
	thisTrack.startHeight = 4.0f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//flat to 25 down
void DrawSteelTwisterRollerCoaster_0C(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);

}


//25 -> 60 down
void DrawSteelTwisterRollerCoaster_0D(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = -60;
	thisTrack.startHeight = 2.0f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//60 -> 25 down
void DrawSteelTwisterRollerCoaster_0E(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -60;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = 2.0f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//25 down to flat
void DrawSteelTwisterRollerCoaster_0F(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}



//left 1/4 D5
void DrawSteelTwisterRollerCoaster_10(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5
void DrawSteelTwisterRollerCoaster_11(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}




//flat -> L bank
void DrawSteelTwisterRollerCoaster_12(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//flat -> R bank
void DrawSteelTwisterRollerCoaster_13(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//L bank -> flat
void DrawSteelTwisterRollerCoaster_14(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);	
}


//R bank -> flat
void DrawSteelTwisterRollerCoaster_15(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}


//left 1/4 D5 turn banked
void DrawSteelTwisterRollerCoaster_16(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D5 turn banked
void DrawSteelTwisterRollerCoaster_17(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//L bank -> 25 up
void DrawSteelTwisterRollerCoaster_18(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//R bank -> 25 up
void DrawSteelTwisterRollerCoaster_19(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//25 up -> L Bank
void DrawSteelTwisterRollerCoaster_1A(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);

	thisTrack.endHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//25 up -> R Bank
void DrawSteelTwisterRollerCoaster_1B(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.5f * UNITHEIGHT;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);

	thisTrack.endHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}


//L bank -> 25 down
void DrawSteelTwisterRollerCoaster_1C(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);

	thisTrack.startHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//R bank -> 25 down
void DrawSteelTwisterRollerCoaster_1D(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);

	thisTrack.startHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//25 down -> L bank
void DrawSteelTwisterRollerCoaster_1E(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//25 down -> R bank
void DrawSteelTwisterRollerCoaster_1F(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.5f * UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//L bank
void DrawSteelTwisterRollerCoaster_20(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//R bank
void DrawSteelTwisterRollerCoaster_21(int rideIndex, int colorIndex, bool doDiag)
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

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];

	//draw center
	drawSquareTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}


//left 1/4 D5 up 25
void DrawSteelTwisterRollerCoaster_22(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 1.0f * UNITHEIGHT;
	thisTrack.endHeight = 5.0f * UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, 2.0f * UNITHEIGHT, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D5 up 25
void DrawSteelTwisterRollerCoaster_23(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 1.0f * UNITHEIGHT; //0.0f;
	thisTrack.endHeight = 5.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 2.0f * UNITHEIGHT, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/4 D5 down 25
void DrawSteelTwisterRollerCoaster_24(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = -2.0f * UNITHEIGHT;
	thisTrack.endHeight = -6.0f * UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, -1.0f * UNITHEIGHT, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D5 down 25
void DrawSteelTwisterRollerCoaster_25(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = -2.0f * UNITHEIGHT; //0.0f;
	thisTrack.endHeight = -6.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, -UNITHEIGHT, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/4 D3 turn
void DrawSteelTwisterRollerCoaster_2A(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D3 turn
void DrawSteelTwisterRollerCoaster_2B(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/4 D3 turn banked
void DrawSteelTwisterRollerCoaster_2C(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D3 turn banked
void DrawSteelTwisterRollerCoaster_2D(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//left 1/4 D3 turn up
void DrawSteelTwisterRollerCoaster_2E(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 25;
	thisTrack.endAngle = 25;
	thisTrack.startHeight = 0.0f; //UNITHEIGHT; //0.0f;
	thisTrack.endHeight = 2.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 2.0f * UNITHEIGHT, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D3 turn up
void DrawSteelTwisterRollerCoaster_2F(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (1.0f  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (1.0f  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (1.0f  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (1.0f  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (heightCount + 0.5f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (heightCount + 0.5f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount + 0.5f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount + 0.5f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}

	radius1 = (1.0f + LEFTRAIL) * UNITWIDTH;
	radius2 = (1.0f + RIGHTRAIL) * UNITWIDTH;

	heightCount = 0.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}


	//draw the beam
	radius1 = (1.0f + LEFTBEAM) * UNITWIDTH;
	radius2 = (1.0f + RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}
}

//left 1/4 D3 turn down
void DrawSteelTwisterRollerCoaster_30(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (1.0f  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (1.0f  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (1.0f  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (1.0f  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 1.0f;
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}

	radius1 = (1.0f  + LEFTRAIL) * UNITWIDTH;
	radius2 = (1.0f  + RIGHTRAIL) * UNITWIDTH;

	heightCount = 1.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (1.0f  + LEFTBEAM) * UNITWIDTH;
	radius2 = (1.0f  + RIGHTBEAM) * UNITWIDTH;

	heightCount = 1.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}


}

//right 1/4 D3 turn down
void DrawSteelTwisterRollerCoaster_31(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -25;
	thisTrack.endAngle = -25;
	thisTrack.startHeight = 0.0f; //UNITHEIGHT; //0.0f;
	thisTrack.endHeight = -2.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, -UNITHEIGHT, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}



//left 1/4 D1 turn up
void DrawSteelTwisterRollerCoaster_5F(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -60;
	thisTrack.endAngle = -60;
	thisTrack.startHeight = 0.0f * UNITHEIGHT;
	thisTrack.endHeight = 4.0f * UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, 4.0f * UNITHEIGHT, 0.0f);
		drawSquareTubeCurveLeft(0.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(0.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(0.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D1 turn up
void DrawSteelTwisterRollerCoaster_60(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	//glColor3f(1.0f, 0.0f, 0.0f);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 0.0f;

	glPushMatrix();
	
		glTranslated(0.0f, 0.0f, -UNITWIDTH);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	radius1 = (LEFTRAIL) * UNITWIDTH;
	radius2 = (RIGHTRAIL) * UNITWIDTH;

	heightCount = 0.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}


	//draw the beam
	radius1 = (LEFTBEAM) * UNITWIDTH;
	radius2 = (RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glPopMatrix();
}

//left 1/4 D1 turn down
void DrawSteelTwisterRollerCoaster_61(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -60;
	thisTrack.endAngle = -60;
	thisTrack.startHeight = 0.0f * UNITHEIGHT;
	thisTrack.endHeight = -4.0f * UNITHEIGHT;

	glPushMatrix();
		//glTranslatef(0.0f, 0.0f, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(0.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(0.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(0.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D1 turn down
void DrawSteelTwisterRollerCoaster_62(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = -60;
	thisTrack.endAngle = -60;
	thisTrack.startHeight = 0.0f * UNITHEIGHT;
	thisTrack.endHeight = -4.0f * UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f * UNITWIDTH);
		drawSquareTubeCurveRight(0.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(0.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(0.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();	
}


//left 1/8 turn OTD
void DrawSteelTwisterRollerCoaster_85(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (rad  + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn OTD
void DrawSteelTwisterRollerCoaster_86(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_87(int rideIndex, int colorIndex)
{	
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (rad  + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn DTO
void DrawSteelTwisterRollerCoaster_88(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}

//left 1/8 turn OTD banked
void DrawSteelTwisterRollerCoaster_89(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (rad  + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn OTD banked
void DrawSteelTwisterRollerCoaster_8A(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_8B(int rideIndex, int colorIndex)
{	
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius1 = (rad  + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn DTO banked
void DrawSteelTwisterRollerCoaster_8C(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((RIGHTRAIL - LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + (RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



void DrawSteelTwisterRollerCoaster_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelTwisterRollerCoaster_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_04(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_8F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_05(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelTwisterRollerCoaster_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_06(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelTwisterRollerCoaster_91(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelTwisterRollerCoaster_92(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSteelTwisterRollerCoaster_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_09(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_95(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_0B(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_97(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_0D(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSteelTwisterRollerCoaster_9E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_12(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSteelTwisterRollerCoaster_9F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_13(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSteelTwisterRollerCoaster_A0(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_14(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSteelTwisterRollerCoaster_A1(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_15(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSteelTwisterRollerCoaster_A2(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		//glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));
		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_18(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawSteelTwisterRollerCoaster_A3(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.00f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_19(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawSteelTwisterRollerCoaster_A4(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_1A(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawSteelTwisterRollerCoaster_A5(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_1B(rideIndex, colorIndex, true);

	glPopMatrix();
	

}


void DrawSteelTwisterRollerCoaster_A6(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_1C(rideIndex, colorIndex, true);

	glPopMatrix();
	

}


void DrawSteelTwisterRollerCoaster_A7(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_1D(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSteelTwisterRollerCoaster_A8(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_1E(rideIndex, colorIndex, true);

	glPopMatrix();

}

void DrawSteelTwisterRollerCoaster_A9(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_1F(rideIndex, colorIndex, true);

	glPopMatrix();

}



void DrawSteelTwisterRollerCoaster_AA(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_20(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSteelTwisterRollerCoaster_AB(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSteelTwisterRollerCoaster_21(rideIndex, colorIndex, true);

	glPopMatrix();

}


void drawLargeHalfLoop(int rideIndex, int colorIndex, char leanDirection)
{
	int startAngle = 22;

	int angleInc = 17;

	float rad = 3.0f * UNITWIDTH;
	float step = 0.5f * UNITWIDTH / 6.0f;

	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r4, g4, b4;
	float baseColor[3] = {RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]};
	float val1, val2, val3, val4;

	glShadeModel(GL_SMOOTH);
	
	//draw the top support beam
	val1 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	glColor3f(r1, g1, b1);	


	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(5.0f * UNITWIDTH, (16.0f * UNITHEIGHT - 3.0f * UNITWIDTH), -0.5f * UNITWIDTH);

		
	glEnd();

	float tmpHeight = 16.0f * UNITHEIGHT - 3.0f * UNITWIDTH;

	//inside beam
	for(int i=0; i<6; i++)
	{
		val1 = calcLightFactor(-cosTable[i * 15], -sinTable[i * 15], 0.0f);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(-cosTable[(i+1) * 15], -sinTable[i * 15], 0.0f);
		calcColor(baseColor, val2, &r2, &g2, &b2);
		

		glBegin(GL_QUADS);

		if(leanDirection == 'L')
		{
			glColor3f(r1, g1, b1);
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, -0.5f *UNITWIDTH - i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, -0.5f *UNITWIDTH - i * step + (RIGHTBEAM * UNITWIDTH));
			glColor3f(r2, g2, b2);
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, -0.5f *UNITWIDTH - (i+1) * step + (LEFTBEAM * UNITWIDTH));
		}
		else
		{
			glColor3f(r1, g1, b1);
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, 0.5f *UNITWIDTH + i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, 0.5f *UNITWIDTH + i * step + (RIGHTBEAM * UNITWIDTH));
			glColor3f(r2, g2, b2);
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, 0.5f *UNITWIDTH + (i+1) * step + (LEFTBEAM * UNITWIDTH));
		}

		glEnd();
	}

	rad = 12.08f;
	float offset = 10.32; //7.0f * UNITWIDTH - 11.2f;
	float totalSize = 0.0f; //7.0f * UNITWIDTH;

	for(i=-1; i<4; i++)
	{
		val1 = calcLightFactor(-cosTable[i * 17 + 22], -sinTable[i * 17 + 22], 0.0f);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(-cosTable[(i+1) * 17 + 22], -sinTable[i * 17 + 22], 0.0f);
		calcColor(baseColor, val2, &r2, &g2, &b2);
		
		
		glBegin(GL_QUADS);
			glColor3f(r1, g1, b1);
			glVertex3f(2.0f * UNITWIDTH + (cosTable[i*17 + 22] * rad), tmpHeight - sinTable[i*17 + 22] * rad, -0.5f *UNITWIDTH - (4 - i) * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + (cosTable[i*17 + 22] * rad), tmpHeight - sinTable[i*17 + 22] * rad, -0.5f *UNITWIDTH - (4 - i) * step + (RIGHTBEAM * UNITWIDTH));
			glColor3f(r2, g2, b2);
			glVertex3f(2.0f * UNITWIDTH + (cosTable[(i+1)*17 + 22] * rad), tmpHeight - sinTable[(i+1)*17 + 22] * rad, -0.5f *UNITWIDTH - ((4 - i)-1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + (cosTable[(i+1)*17 + 22] * rad), tmpHeight - sinTable[(i+1)*17 + 22] * rad, -0.5f *UNITWIDTH - ((4 - i)-1) * step + (LEFTBEAM * UNITWIDTH));
		glEnd();
	}

	//outside beam
	rad = (3.0f + (BOTTOMBEAM - TOPBEAM)) * UNITWIDTH;
	for(i=0; i<6; i++)
	{
		val1 = calcLightFactor(cosTable[i * 15], sinTable[i * 15], 0.0f);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(cosTable[(i+1) * 15], sinTable[i * 15], 0.0f);
		calcColor(baseColor, val2, &r2, &g2, &b2);

		glBegin(GL_QUADS);
		
		if(leanDirection == 'L')
		{		
			glColor3f(r1, g1, b1);
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, -0.5f *UNITWIDTH - i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, -0.5f *UNITWIDTH - i * step + (RIGHTBEAM * UNITWIDTH));
			glColor3f(r2, g2, b2);
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, -0.5f *UNITWIDTH - (i+1) * step + (LEFTBEAM * UNITWIDTH));
		}
		else
		{
			glColor3f(r1, g1, b1);
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, 0.5f *UNITWIDTH + i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * rad, tmpHeight + sinTable[i*15] * rad, 0.5f *UNITWIDTH + i * step + (RIGHTBEAM * UNITWIDTH));
			glColor3f(r2, g2, b2);
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * rad, tmpHeight + sinTable[(i+1)*15] * rad, 0.5f *UNITWIDTH + (i+1) * step + (LEFTBEAM * UNITWIDTH));
		}
		glEnd();
	}

	//left edge
	float radA = 3.0f * UNITWIDTH;
	float radB = rad;
	for(i=0; i<6; i++)
	{
		val1 = calcLightFactor(0.0f, 0.0f, -1.0f);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		glColor3f(r1, g1, b1);

		glBegin(GL_QUADS);
		
		if(leanDirection == 'L')
		{		
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radA, tmpHeight + sinTable[i*15] * radA, -0.5f *UNITWIDTH - i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radB, tmpHeight + sinTable[i*15] * radB, -0.5f *UNITWIDTH - i * step + (LEFTBEAM * UNITWIDTH));		
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radB, tmpHeight + sinTable[(i+1)*15] * radB, -0.5f *UNITWIDTH - (i+1) * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radA, tmpHeight + sinTable[(i+1)*15] * radA, -0.5f *UNITWIDTH - (i+1) * step + (LEFTBEAM * UNITWIDTH));
		}
		else
		{
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radA, tmpHeight + sinTable[i*15] * radA, 0.5f *UNITWIDTH + i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radB, tmpHeight + sinTable[i*15] * radB, 0.5f *UNITWIDTH + i * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radB, tmpHeight + sinTable[(i+1)*15] * radB, 0.5f *UNITWIDTH + (i+1) * step + (LEFTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radA, tmpHeight + sinTable[(i+1)*15] * radA, 0.5f *UNITWIDTH + (i+1) * step + (LEFTBEAM * UNITWIDTH));
		}
		glEnd();
	}

	//right edge
	for(i=0; i<6; i++)
	{
		val1 = calcLightFactor(0.0f, 0.0f, 1.0f);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		glColor3f(r1, g1, b1);

		glBegin(GL_QUADS);
		
		if(leanDirection == 'L')
		{		
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radA, tmpHeight + sinTable[i*15] * radA, -0.5f *UNITWIDTH - i * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radB, tmpHeight + sinTable[i*15] * radB, -0.5f *UNITWIDTH - i * step + (RIGHTBEAM * UNITWIDTH));		
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radB, tmpHeight + sinTable[(i+1)*15] * radB, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radA, tmpHeight + sinTable[(i+1)*15] * radA, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTBEAM * UNITWIDTH));
		}
		else
		{
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radA, tmpHeight + sinTable[i*15] * radA, 0.5f *UNITWIDTH + i * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radB, tmpHeight + sinTable[i*15] * radB, 0.5f *UNITWIDTH + i * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radB, tmpHeight + sinTable[(i+1)*15] * radB, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTBEAM * UNITWIDTH));
			glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radA, tmpHeight + sinTable[(i+1)*15] * radA, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTBEAM * UNITWIDTH));
		}
		glEnd();
	}

	//right rail
	float halfRailDiameter;

	halfRailDiameter = RAILDIAMETER / 2.0f;
	//val1 = towards inside
	//val2 = towards outside
	//val3 = towards right
	//val4 = towards left

	radA = 3.0f * UNITWIDTH - (RAILHEIGHT + halfRailDiameter) * UNITHEIGHT;
	radA = 3.0f * UNITWIDTH - (RAILHEIGHT - halfRailDiameter) * UNITHEIGHT;
	float radC = (3.0f - RAILHEIGHT) * UNITWIDTH;

	for(i=0; i<6; i++)
	{
		//calc inside and inside for next segment
		val1 = calcLightFactor(-cosTable[i * 15], -sinTable[i * 15], 0.0f);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(-cosTable[(i+1) * 15], -sinTable[i * 15], 0.0f);
		calcColor(baseColor, val2, &r2, &g2, &b2);
		
		//calc right and left edges
		val3 = calcLightFactor(0.0f, 0.0f, 1.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);
		val4 = calcLightFactor(0.0f, 0.0f, -1.0f);
		calcColor(baseColor, val4, &r4, &g4, &b4);		

		
		
		if(leanDirection == 'L')
		{		
			glBegin(GL_QUADS);
				glColor3f(r1, g1, b1);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radA, tmpHeight + sinTable[i*15] * radA, -0.5f *UNITWIDTH - i * step + (RIGHTRAIL) * UNITWIDTH);
				glColor3f(r3, g3, b3);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radC, tmpHeight + sinTable[i*15] * radC, -0.5f *UNITWIDTH - i * step + (RIGHTRAIL + halfRailDiameter) * UNITWIDTH);		
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radC, tmpHeight + sinTable[(i+1)*15] * radC, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
				glColor3f(r2, g2, b2);
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radA, tmpHeight + sinTable[(i+1)*15] * radA, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTRAIL) * UNITWIDTH);
			glEnd();

			glBegin(GL_QUADS);
				glColor3f(r1, g1, b1);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radB, tmpHeight + sinTable[i*15] * radA, -0.5f *UNITWIDTH - i * step + (RIGHTRAIL) * UNITWIDTH);
				glColor3f(r4, g4, b4);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radC, tmpHeight + sinTable[i*15] * radC, -0.5f *UNITWIDTH - i * step + (RIGHTRAIL - halfRailDiameter) * UNITWIDTH);		
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radC, tmpHeight + sinTable[(i+1)*15] * radC, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
				glColor3f(r2, g2, b2);
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radB, tmpHeight + sinTable[(i+1)*15] * radA, -0.5f *UNITWIDTH - (i+1) * step + (RIGHTRAIL) * UNITWIDTH);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radA, tmpHeight + sinTable[i*15] * radB, 0.5f *UNITWIDTH + i * step + (RIGHTRAIL) * UNITWIDTH);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radC, tmpHeight + sinTable[i*15] * radC, 0.5f *UNITWIDTH + i * step + (RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radC, tmpHeight + sinTable[(i+1)*15] * radC, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radA, tmpHeight + sinTable[(i+1)*15] * radB, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTRAIL) * UNITWIDTH);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radB, tmpHeight + sinTable[i*15] * radB, 0.5f *UNITWIDTH + i * step + (RIGHTRAIL) * UNITWIDTH);
				glVertex3f(2.0f * UNITWIDTH + cosTable[i*15] * radC, tmpHeight + sinTable[i*15] * radC, 0.5f *UNITWIDTH + i * step + (RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radC, tmpHeight + sinTable[(i+1)*15] * radC, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
				glVertex3f(2.0f * UNITWIDTH + cosTable[(i+1)*15] * radB, tmpHeight + sinTable[(i+1)*15] * radB, 0.5f *UNITWIDTH + (i+1) * step + (RIGHTRAIL) * UNITWIDTH);
			glEnd();
		}
		
	}











}


//large half loop up left
void DrawSteelTwisterRollerCoaster_B7(int rideIndex, int colorIndex)
{
	drawLargeHalfLoop(rideIndex, colorIndex, 'L');
}

//large half loop up right
void DrawSteelTwisterRollerCoaster_B8(int rideIndex, int colorIndex)
{
	//glPushMatrix();
		//glTranslatef(0.0f, 0.0f, 0.0f);

		drawLargeHalfLoop(rideIndex, colorIndex, 'R');
	//glPopMatrix();
}

//large half loop down left
void DrawSteelTwisterRollerCoaster_B9(int rideIndex, int colorIndex)
{
	glPushMatrix();
		glTranslatef(-2.0f * UNITWIDTH, -15.5f * UNITHEIGHT, -UNITWIDTH);
		drawLargeHalfLoop(rideIndex, colorIndex, 'R');
	glPopMatrix();
}

//large half loop down right
void DrawSteelTwisterRollerCoaster_BA(int rideIndex, int colorIndex)
{
	glPushMatrix();
		glTranslatef(-2.0f * UNITWIDTH, -15.5f * UNITHEIGHT, UNITWIDTH);
		drawLargeHalfLoop(rideIndex, colorIndex, 'L');
	glPopMatrix();
}

