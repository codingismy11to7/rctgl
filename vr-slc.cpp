#include "vr3d.h"
#include "vr-tracks.h"
#include "vr-slc.h"

//flat piece
void DrawSLCRollerCoaster_00(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);

}

// 25 degree up hill
void DrawSLCRollerCoaster_04(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 degree up hill
void DrawSLCRollerCoaster_05(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//flat to 25 up
void DrawSLCRollerCoaster_06(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//25 -> 60 up
void DrawSLCRollerCoaster_07(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 -> 25 up
void DrawSLCRollerCoaster_08(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);


}



//25 up -> flat
void DrawSLCRollerCoaster_09(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//25 degree drop
void DrawSLCRollerCoaster_0A(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 degree drop
void DrawSLCRollerCoaster_0B(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//flat to 25 down
void DrawSLCRollerCoaster_0C(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}


//25 -> 60 down
void DrawSLCRollerCoaster_0D(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//60 -> 25 down
void DrawSLCRollerCoaster_0E(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//25 down to flat
void DrawSLCRollerCoaster_0F(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}





//left 1/4 D5
void DrawSLCRollerCoaster_10(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D5
void DrawSLCRollerCoaster_11(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}




//flat -> L bank
void DrawSLCRollerCoaster_12(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//flat -> R bank
void DrawSLCRollerCoaster_13(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//L bank -> flat
void DrawSLCRollerCoaster_14(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);	
}


//R bank -> flat
void DrawSLCRollerCoaster_15(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}


//left 1/4 D5 turn banked
void DrawSLCRollerCoaster_16(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5 turn banked
void DrawSLCRollerCoaster_17(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//L bank -> 25 up
void DrawSLCRollerCoaster_18(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//R bank -> 25 up
void DrawSLCRollerCoaster_19(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.startHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//25 up -> L Bank
void DrawSLCRollerCoaster_1A(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);

	thisTrack.endHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//25 up -> R Bank
void DrawSLCRollerCoaster_1B(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);

	thisTrack.endHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}


//L bank -> 25 down
void DrawSLCRollerCoaster_1C(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);

	thisTrack.startHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//R bank -> 25 down
void DrawSLCRollerCoaster_1D(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);

	thisTrack.startHeight = 0.5f * UNITHEIGHT + (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);

	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//25 down -> L bank
void DrawSLCRollerCoaster_1E(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//25 down -> R bank
void DrawSLCRollerCoaster_1F(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = (RAIL_HEIGHT_TILTED - RAIL_HEIGHT);
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}

//L bank
void DrawSLCRollerCoaster_20(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
}

//R bank
void DrawSLCRollerCoaster_21(int rideIndex, int colorIndex, bool doDiag)
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
	drawRoundTube(CENTER_RADIUS, CENTER_HEIGHT, 0.5f * UNITWIDTH, colorArr, thisTrack);

	colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

	//draw rails
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, RIGHT_RAIL, colorArr, thisTrack);
	thisTrack.endHeight = thisTrack.startHeight = RAIL_HEIGHT_TILTED - RAIL_HEIGHT;
	drawRoundTube(RAIL_RADIUS, RAIL_HEIGHT, LEFT_RAIL, colorArr, thisTrack);
}


//left 1/4 D5 up 25
void DrawSLCRollerCoaster_22(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 1.0f * UNITHEIGHT;
	thisTrack.endHeight = 5.0f * UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, 2.0f * UNITHEIGHT, -1.0f * UNITWIDTH);
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5 up 25
void DrawSLCRollerCoaster_23(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 1.0f * UNITHEIGHT; //0.0f;
	thisTrack.endHeight = 5.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 2.0f * UNITHEIGHT, 2.0f * UNITWIDTH);
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/4 D5 down 25
void DrawSLCRollerCoaster_24(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = -2.0f * UNITHEIGHT;
	thisTrack.endHeight = -6.0f * UNITHEIGHT;

	glPushMatrix();
		glTranslatef(0.0f, -1.0f * UNITHEIGHT, -1.0f * UNITWIDTH);
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5 down 25
void DrawSLCRollerCoaster_25(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = -2.0f * UNITHEIGHT; //0.0f;
	thisTrack.endHeight = -6.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, -UNITHEIGHT, 2.0f * UNITWIDTH);
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/4 D3 turn
void DrawSLCRollerCoaster_2A(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D3 turn
void DrawSLCRollerCoaster_2B(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/4 D3 turn banked
void DrawSLCRollerCoaster_2C(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D3 turn banked
void DrawSLCRollerCoaster_2D(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//left 1/4 D3 turn up
void DrawSLCRollerCoaster_2E(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f; //UNITHEIGHT; //0.0f;
	thisTrack.endHeight = 2.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, 2.0f * UNITHEIGHT, -1.0f * UNITWIDTH);
		drawRoundTubeCurveLeft(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}

//right 1/4 D3 turn up
void DrawSLCRollerCoaster_2F(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (1.0f  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (1.0f  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (1.0f  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (1.0f  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (heightCount + 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (heightCount + 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount + 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount + 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}

	radius1 = (1.0f + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (1.0f + SLC_RIGHTRAIL) * UNITWIDTH;

	heightCount = 0.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}


	//draw the beam
	radius1 = (1.0f + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (1.0f + SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 0.5f;
	}
}

//left 1/4 D3 turn down
void DrawSLCRollerCoaster_30(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (1.0f  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (1.0f  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (1.0f  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (1.0f  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 1.0f;
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}

	radius1 = (1.0f  + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (1.0f  + SLC_RIGHTRAIL) * UNITWIDTH;

	heightCount = 1.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (1.0f  + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (1.0f  + SLC_RIGHTBEAM) * UNITWIDTH;

	heightCount = 1.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 0.5f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 0.5f;
	}


}

//right 1/4 D3 turn down
void DrawSLCRollerCoaster_31(int rideIndex, int colorIndex)
{
	float colorArr[3];

	colorArr[0] = RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[1] = RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]];
	colorArr[2] = RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]];
	
	trackInfo thisTrack;
	thisTrack.startAngle = 0;
	thisTrack.endAngle = 0;
	thisTrack.startHeight = 0.0f; //UNITHEIGHT; //0.0f;
	thisTrack.endHeight = -2.0f * UNITHEIGHT; //0.0f;

	glPushMatrix();
		glTranslatef(0.0f, -UNITHEIGHT, 2.0f * UNITWIDTH);
		drawRoundTubeCurveRight(1.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(1.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(1.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}



//left 1/4 D3 turn up
void DrawSLCRollerCoaster_5F(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 0.0f;
	

	glPushMatrix();

		glTranslated(0.0f, 0.0f, UNITWIDTH);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	radius1 = (SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (SLC_RIGHTRAIL) * UNITWIDTH;

	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (SLC_RIGHTBEAM) * UNITWIDTH;

	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glPopMatrix();


}

//right 1/4 D3 turn up
void DrawSLCRollerCoaster_60(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 0.0f;

	glPushMatrix();
	
		glTranslated(0.0f, 0.0f, -UNITWIDTH);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount + 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	radius1 = (SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (SLC_RIGHTRAIL) * UNITWIDTH;

	heightCount = 0.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}


	//draw the beam
	radius1 = (SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	heightCount = 0.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount + 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount += 1.0f;
	}

	glPopMatrix();
}

//left 1/4 D1 turn down
void DrawSLCRollerCoaster_61(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 3.0f;

	glPushMatrix();

		glTranslated(0.0f, UNITHEIGHT, 1.0f * UNITWIDTH);
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	radius1 = (SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (SLC_RIGHTRAIL) * UNITWIDTH;

	heightCount = 3.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (SLC_RIGHTBEAM) * UNITWIDTH;

	heightCount = 3.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	glPopMatrix();


}

//right 1/4 D3 turn down
void DrawSLCRollerCoaster_62(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	float heightCount;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	heightCount = 3.0f;

	glPushMatrix();

		glTranslated(0.0f, UNITHEIGHT, -UNITWIDTH);

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(heightCount - 1.0f + SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	radius1 = (SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (SLC_RIGHTRAIL) * UNITWIDTH;

	heightCount = 3.0f;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(heightCount + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(heightCount + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}


	//draw the beam
	radius1 = (SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	heightCount = 3.0f;
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (heightCount + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (heightCount + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (heightCount - 1.0f + SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		heightCount -= 1.0f;
	}

	glPopMatrix();
}


//left 1/4 D5 turn banked helix up
void DrawSLCRollerCoaster_66(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5 turn banked helix up
void DrawSLCRollerCoaster_67(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();	
}

//left 1/4 D5 turn banked helix down
void DrawSLCRollerCoaster_68(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();


}

//right 1/4 D5 turn banked helix down
void DrawSLCRollerCoaster_69(int rideIndex, int colorIndex)
{
	/*
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
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT_TILTED, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
	*/
}


//left 1/4 D5 turn helix up
void DrawSLCRollerCoaster_6A(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();

}

//right 1/4 D5 turn helix up
void DrawSLCRollerCoaster_6B(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();	
}

//left 1/4 D5 turn helix down
void DrawSLCRollerCoaster_6C(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveLeft(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveLeft(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();


}

//right 1/4 D5 turn helix down
void DrawSLCRollerCoaster_6D(int rideIndex, int colorIndex)
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
		drawRoundTubeCurveRight(2.5f * UNITWIDTH, CENTER_RADIUS, CENTER_HEIGHT, colorArr, thisTrack);

		colorArr[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		colorArr[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		drawRoundTubeCurveRight(2.0f * UNITWIDTH + RIGHT_RAIL, RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
		drawRoundTubeCurveRight(2.0f * UNITWIDTH + LEFT_RAIL,  RAIL_RADIUS, RAIL_HEIGHT, colorArr, thisTrack);
	glPopMatrix();
}


//left 1/8 turn OTD
void DrawSLCRollerCoaster_85(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (rad  + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn OTD
void DrawSLCRollerCoaster_86(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


void DrawSLCRollerCoaster_87(int rideIndex, int colorIndex)
{	
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (rad  + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn DTO
void DrawSLCRollerCoaster_88(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

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
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}

//left 1/8 turn OTD banked
void DrawSLCRollerCoaster_89(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (rad  + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn OTD banked
void DrawSLCRollerCoaster_8A(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 18.0f * 3.14/180.0f;
	degrees[2] = 27.0f * 3.14/180.0f;
	degrees[3] = 36.0f * 3.14/180.0f;
	degrees[4] = 45.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


void DrawSLCRollerCoaster_8B(int rideIndex, int colorIndex)
{	
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 45.0f  * 3.14/180.0f;
	degrees[1] = 54.0f * 3.14/180.0f;
	degrees[2] = 63.0f * 3.14/180.0f;
	degrees[3] = 72.0f * 3.14/180.0f;
	degrees[4] = 81.0f * 3.14/180.0f;
	degrees[5] = 90.0f * 3.14/180.0f;

	float rad = 3.0f;

	//rails
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);
	

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + SLC_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad  + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (rad  + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + SLC_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(SLC_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}


//right 1/8 turn DTO banked
void DrawSLCRollerCoaster_8C(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[6];
	int i;

	double angledHeight;
	
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((SLC_RIGHTRAIL - SLC_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = SLC_RAILDIAMETER / 2.0f;

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
	radius1a = (rad  + SLC_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (rad  + SLC_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (rad  + SLC_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (rad  + SLC_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		//glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + (SLC_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (rad + SLC_LEFTRAIL) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (SLC_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (SLC_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (rad + SLC_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + SLC_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<5; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (SLC_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}

	glPopMatrix();
}



void DrawSLCRollerCoaster_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSLCRollerCoaster_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_04(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSLCRollerCoaster_8F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_05(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSLCRollerCoaster_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_06(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSLCRollerCoaster_91(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSLCRollerCoaster_92(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_07(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawSLCRollerCoaster_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_09(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSLCRollerCoaster_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSLCRollerCoaster_95(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_0B(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSLCRollerCoaster_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSLCRollerCoaster_97(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_0D(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawSLCRollerCoaster_9E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_12(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSLCRollerCoaster_9F(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_13(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSLCRollerCoaster_A0(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_14(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSLCRollerCoaster_A1(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_15(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSLCRollerCoaster_A2(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		//glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));
		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_18(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawSLCRollerCoaster_A3(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.00f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_19(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawSLCRollerCoaster_A4(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_1A(rideIndex, colorIndex, true);

	glPopMatrix();
	

}

void DrawSLCRollerCoaster_A5(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_1B(rideIndex, colorIndex, true);

	glPopMatrix();
	

}


void DrawSLCRollerCoaster_A6(int rideIndex, int colorIndex)
{
	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_1C(rideIndex, colorIndex, true);

	glPopMatrix();
	

}


void DrawSLCRollerCoaster_A7(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_1D(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSLCRollerCoaster_A8(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_1E(rideIndex, colorIndex, true);

	glPopMatrix();

}

void DrawSLCRollerCoaster_A9(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_1F(rideIndex, colorIndex, true);

	glPopMatrix();

}



void DrawSLCRollerCoaster_AA(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_20(rideIndex, colorIndex, true);

	glPopMatrix();

}


void DrawSLCRollerCoaster_AB(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.42f, 1.0f, 1.42f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((0.0f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawSLCRollerCoaster_21(rideIndex, colorIndex, true);

	glPopMatrix();

}

