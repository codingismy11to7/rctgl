#include "vr3d.h"
#include "vr-tracks.h"
#include "vr-inverted.h"



//flat piece
void DrawInvertedRollerCoaster_00(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_04(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_05(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_06(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_07(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_08(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_09(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_0A(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_0B(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_0C(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_0D(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_0E(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_0F(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_10(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_11(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_12(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_13(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_14(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_15(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_16(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_17(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_18(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_19(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_1A(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_1B(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_1C(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_1D(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_1E(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_1F(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_20(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_21(int rideIndex, int colorIndex, bool doDiag)
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
void DrawInvertedRollerCoaster_22(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_23(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_24(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_25(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_2A(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_2B(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_2C(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_2D(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_2E(int rideIndex, int colorIndex)
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
void DrawInvertedRollerCoaster_2F(int rideIndex, int colorIndex)
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

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
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
void DrawInvertedRollerCoaster_30(int rideIndex, int colorIndex)
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
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

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
void DrawInvertedRollerCoaster_31(int rideIndex, int colorIndex)
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



//left 1/4 D3 turn up
void DrawInvertedRollerCoaster_5F(int rideIndex, int colorIndex)
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
	radius1a = (LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 0.0f;
	

	glPushMatrix();

		glTranslated(0.0f, 0.0f, UNITWIDTH);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
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
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (LEFTBEAM) * UNITWIDTH;
	radius2 = (RIGHTBEAM) * UNITWIDTH;

	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glPopMatrix();


}

//right 1/4 D3 turn up
void DrawInvertedRollerCoaster_60(int rideIndex, int colorIndex)
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

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
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
void DrawInvertedRollerCoaster_61(int rideIndex, int colorIndex)
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
	radius1a = (LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 3.0f;

	glPushMatrix();

		glTranslated(0.0f, UNITHEIGHT, 1.0f * UNITWIDTH);
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	radius1 = (LEFTRAIL) * UNITWIDTH;
	radius2 = (RIGHTRAIL) * UNITWIDTH;

	heightCount = 3.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (LEFTBEAM) * UNITWIDTH;
	radius2 = (RIGHTBEAM) * UNITWIDTH;

	heightCount = 3.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	glPopMatrix();


}

//right 1/4 D3 turn down
void DrawInvertedRollerCoaster_62(int rideIndex, int colorIndex)
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
	radius1a = (LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 3.0f;

	glPushMatrix();

		glTranslated(0.0f, UNITHEIGHT, -UNITWIDTH);

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount - 1.0f + RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	radius1 = (LEFTRAIL) * UNITWIDTH;
	radius2 = (RIGHTRAIL) * UNITWIDTH;

	heightCount = 3.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(heightCount + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}


	//draw the beam
	radius1 = (LEFTBEAM) * UNITWIDTH;
	radius2 = (RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	heightCount = 3.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (heightCount + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	glPopMatrix();
}



//left 1/4 D5 turn banked helix up
void DrawInvertedRollerCoaster_66(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, UNITHEIGHT, -1.0f * UNITWIDTH);
		drawSquareTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5 turn banked helix up
void DrawInvertedRollerCoaster_67(int rideIndex, int colorIndex)
{	
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, UNITHEIGHT, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();	
}

//left 1/4 D5 turn banked helix down
void DrawInvertedRollerCoaster_68(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f;
	thisTrack.endHeight = -UNITHEIGHT;

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

//right 1/4 D5 turn banked helix down
void DrawInvertedRollerCoaster_69(int rideIndex, int colorIndex)
{
	
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = UNITHEIGHT;
	thisTrack.endHeight = 0.0f;

	glPushMatrix();
		glTranslatef(0.0f, -UNITHEIGHT, 2.0f * UNITWIDTH);
		drawSquareTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
	
}




//left 1/8 turn OTD
void DrawInvertedRollerCoaster_85(int rideIndex, int colorIndex)
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
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

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
void DrawInvertedRollerCoaster_86(int rideIndex, int colorIndex)
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

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
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


void DrawInvertedRollerCoaster_87(int rideIndex, int colorIndex)
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
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

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
void DrawInvertedRollerCoaster_88(int rideIndex, int colorIndex)
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

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
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
void DrawInvertedRollerCoaster_89(int rideIndex, int colorIndex)
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
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

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
void DrawInvertedRollerCoaster_8A(int rideIndex, int colorIndex)
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

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
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


void DrawInvertedRollerCoaster_8B(int rideIndex, int colorIndex)
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
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

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
void DrawInvertedRollerCoaster_8C(int rideIndex, int colorIndex)
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

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
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



void DrawInvertedRollerCoaster_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawInvertedRollerCoaster_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_04(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawInvertedRollerCoaster_8F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_05(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawInvertedRollerCoaster_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_06(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawInvertedRollerCoaster_91(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawInvertedRollerCoaster_92(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawInvertedRollerCoaster_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_09(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawInvertedRollerCoaster_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawInvertedRollerCoaster_95(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_0B(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawInvertedRollerCoaster_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawInvertedRollerCoaster_97(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_0D(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawInvertedRollerCoaster_9E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_12(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawInvertedRollerCoaster_9F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_13(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawInvertedRollerCoaster_A0(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_14(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawInvertedRollerCoaster_A1(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_15(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawInvertedRollerCoaster_A2(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		//glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));
		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_18(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawInvertedRollerCoaster_A3(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.00f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_19(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawInvertedRollerCoaster_A4(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_1A(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawInvertedRollerCoaster_A5(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_1B(rideIndex, colorIndex, true);

	glPopMatrix();
	

}


void DrawInvertedRollerCoaster_A6(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_1C(rideIndex, colorIndex, true);

	glPopMatrix();
	

}


void DrawInvertedRollerCoaster_A7(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_1D(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawInvertedRollerCoaster_A8(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_1E(rideIndex, colorIndex, true);

	glPopMatrix();

}

void DrawInvertedRollerCoaster_A9(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_1F(rideIndex, colorIndex, true);

	glPopMatrix();

}



void DrawInvertedRollerCoaster_AA(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_20(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawInvertedRollerCoaster_AB(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawInvertedRollerCoaster_21(rideIndex, colorIndex, true);

	glPopMatrix();

}

