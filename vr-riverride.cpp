#include "vr3d.h"

#define BOTTOM_WIDTH	0.9
#define TOP_WIDTH		0.95
#define FLUME_HEIGHT	0.4
#define WATER_LEVEL		0.35

extern float WaterOffset;

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];

extern int itemRot;

//straight flat
void DrawRiverRide_00(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;

	glShadeModel(GL_SMOOTH);
	
	//draw the top support beam

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);


	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side 
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//water
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

	val1 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	glColor3f(r1, g1, b1);	


	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0 + xWaterOffset);	
		glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + xWaterOffset);
		glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 0.0 + xWaterOffset);
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + xWaterOffset);
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);

}

//medium-grade uphill
void DrawRiverRide_04(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;

	glShadeModel(GL_SMOOTH);

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//lift belt
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_LOGLIFT] );

	val1 = calcLightFactor(-UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	glColor3f(r1, g1, b1);	
	

	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0 + xWaterOffset);	
		glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + xWaterOffset);
		glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 0.0 + xWaterOffset);
		glVertex3d(UNITWIDTH,	(WATER_LEVEL + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + xWaterOffset);
		glVertex3d(UNITWIDTH,	(WATER_LEVEL + 1.0f)  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

//transition flat -> medium-grade uphill
void DrawRiverRide_06(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//main rail
	/*
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(0.0f,		0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.7f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.6f * UNITHEIGHT, 0.5f * UNITWIDTH);
	glEnd();
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	*/

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//lift belt
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_LOGLIFT] );

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0 + xWaterOffset);	
		glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + xWaterOffset);
		glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 0.0 + xWaterOffset);
		glVertex3d(UNITWIDTH,	(WATER_LEVEL + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + xWaterOffset);
		glVertex3d(UNITWIDTH,	(WATER_LEVEL + 0.5f)  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);


}

//25 down
void DrawRiverRide_0A(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 1.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//water
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

	val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	glColor3f(r1, g1, b1);	


	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0 + (4.0f * xWaterOffset));	
		glVertex3d(0.0f,		(WATER_LEVEL + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + (4.0f * xWaterOffset));
		glVertex3d(0.0f,		(WATER_LEVEL + 1.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 0.0 + (4.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + (4.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


//60 down
void DrawRiverRide_0B(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;


	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 4.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 4.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 4.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 4.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 4.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 4.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//lift belt
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

	val1 = calcLightFactor(4.0f * UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	glColor3f(r1, g1, b1);	


	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0 + (8.0f * xWaterOffset));	
		glVertex3d(0.0f,		(WATER_LEVEL + 4.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + (8.0f * xWaterOffset));
		glVertex3d(0.0f,		(WATER_LEVEL + 4.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 0.0 + (8.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + (8.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


//flat -> 25 down
void DrawRiverRide_0C(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;
	glShadeModel(GL_SMOOTH);

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//water
	val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	val2 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);	

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );	

	glBegin(GL_QUADS);
		glColor3f(r2, g2, b2);	
		glTexCoord2d(0.0, 1.0 + (2.0f * xWaterOffset));	
		glVertex3d(0.0f,		(WATER_LEVEL + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + (2.0f * xWaterOffset));
		glVertex3d(0.0f,		(WATER_LEVEL + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glColor3f(r1, g1, b1);	
		glTexCoord2d(1.0, 0.0 + (2.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + (2.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);

}


//25 down -> 60 down
void DrawRiverRide_0D(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;
	glShadeModel(GL_SMOOTH);

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//water
	val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	val2 = calcLightFactor(UNITHEIGHT * 4.0f, UNITWIDTH, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);	

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

	

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);

		glTexCoord2d(0.0, 1.0 + (8.0f * xWaterOffset));	
		glVertex3d(0.0f,		(WATER_LEVEL + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + (8.0f * xWaterOffset));
		glVertex3d(0.0f,		(WATER_LEVEL + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glColor3f(r2, g2, b2);

		glTexCoord2d(1.0, 0.0 + (8.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + (8.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

//60 down -> 25 down
void DrawRiverRide_0E(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;
	glShadeModel(GL_SMOOTH);

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 2.0f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//water
	val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	val2 = calcLightFactor(UNITHEIGHT * 4.0f, UNITWIDTH, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);	

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

	

	glBegin(GL_QUADS);
		glColor3f(r2, g2, b1);

		glTexCoord2d(0.0, 1.0 + (8.0f * xWaterOffset));	
		glVertex3d(0.0f,		(WATER_LEVEL + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + (8.0f * xWaterOffset));
		glVertex3d(0.0f,		(WATER_LEVEL + 2.0f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glColor3f(r1, g1, b1);

		glTexCoord2d(1.0, 0.0 + (8.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + (8.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


//25 down -> flat
void DrawRiverRide_0F(int rideIndex, int colorIndex)
{
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	float val1, val2;
	glShadeModel(GL_SMOOTH);

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//bottom floor
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//right side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//left side
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(0.0f,		(RIDEOFFSETHEIGHT + 0.5f) * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	//water
	val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);
	val2 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);	

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );	

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);	
		glTexCoord2d(0.0, 1.0 + (2.0f * xWaterOffset));	
		glVertex3d(0.0f,		(WATER_LEVEL + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(1.0, 1.0 + (2.0f * xWaterOffset));
		glVertex3d(0.0f,		(WATER_LEVEL + 0.5f) * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glColor3f(r2, g2, b2);	
		glTexCoord2d(1.0, 0.0 + (2.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

		glTexCoord2d(0.0, 0.0 + (2.0f * xWaterOffset));
		glVertex3d(UNITWIDTH,	WATER_LEVEL  * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);

}


void DrawRiverRide_10(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 22.5f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	
	//flume bottom
	radius1 = (2.5f  + (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  - (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;

	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glVertex3d(radius1 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	//rail #1
	radius1 = (2.5f  + (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  + (TOP_WIDTH / 2.0f)) * UNITWIDTH;
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glVertex3d(radius1 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)i],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	//rail #2
	radius1 = (2.5f  - (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  - (TOP_WIDTH / 2.0f)) * UNITWIDTH;
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glVertex3d(radius1 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)i],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	//water
	radius1 = (2.5f  + (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  - (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glTexCoord2d(0.0, 1.0 + (1.0f * xWaterOffset));
			glVertex3d(radius1 * sinTable[(int)i],	WATER_LEVEL * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0, 1.0 + (1.0f * xWaterOffset));
			glVertex3d(radius2 * sinTable[(int)i],	WATER_LEVEL * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0, 0.0 + (1.0f * xWaterOffset));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	WATER_LEVEL * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(0.0, 0.0 + (1.0f * xWaterOffset));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	WATER_LEVEL * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void DrawRiverRide_11(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 22.5f;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//flume bottom
	radius1 = (2.5f  + (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  - (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;

	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glVertex3d(radius1 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}
	

	//rail #1
	radius1 = (2.5f  + (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  + (TOP_WIDTH / 2.0f)) * UNITWIDTH;
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glVertex3d(radius1 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)i],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	//rail #2
	radius1 = (2.5f  - (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  - (TOP_WIDTH / 2.0f)) * UNITWIDTH;
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glVertex3d(radius1 * sinTable[(int)i],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)i],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	(RIDEOFFSETHEIGHT  + FLUME_HEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	RIDEOFFSETHEIGHT * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	//water
	radius1 = (2.5f  + (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;
	radius2 = (2.5f  - (BOTTOM_WIDTH / 2.0f)) * UNITWIDTH;

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glTexCoord2d(0.0, 1.0 + (1.0f * xWaterOffset));
			glVertex3d(radius1 * sinTable[(int)i],	WATER_LEVEL * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0, 1.0 + (1.0f * xWaterOffset));
			glVertex3d(radius2 * sinTable[(int)i],	WATER_LEVEL * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0, 0.0 + (1.0f * xWaterOffset));
			glVertex3d(radius2 * sinTable[(int)(i+step)],	WATER_LEVEL * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(0.0, 0.0 + (1.0f * xWaterOffset));
			glVertex3d(radius1 * sinTable[(int)(i+step)],	WATER_LEVEL * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);  

}

//left S-bend
void DrawRiverRide_26(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glPushMatrix();

		glTranslated(-1.0f * UNITWIDTH, 0.0f, 0.0f);

		//segment #1
		//bottom floor
		glBegin(GL_QUADS);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		//right side
		glBegin(GL_QUADS);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		//left side
		glBegin(GL_QUADS);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		//water
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0 + xWaterOffset);	
			glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0, 1.0 + xWaterOffset);
			glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0, 0.0 + xWaterOffset);
			glVertex3d(0.50f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(0.0, 0.0 + xWaterOffset);
			glVertex3d(0.75f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

		//segment #2		
		//bottom floor
		glBegin(GL_QUADS);
			glVertex3d(0.75f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();
		

		//right side		
		glBegin(GL_QUADS);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		
		//left side
		glBegin(GL_QUADS);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		
		//water
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 2.0f + xWaterOffset);	
			glVertex3d(0.75f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0f, 2.0f + xWaterOffset);
			glVertex3d(0.50f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0f, 0.0f + xWaterOffset);
			glVertex3d(2.25f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);

			glTexCoord2d(0.0f, 0.0f + xWaterOffset);
			glVertex3d(2.50f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);		


		//segment #3
		//bottom floor
		glBegin(GL_QUADS);
			glVertex3d(2.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		//right side
		glBegin(GL_QUADS);
			glVertex3d(2.25f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		//left side
		glBegin(GL_QUADS);
			glVertex3d(2.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		//water
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0 + xWaterOffset);	
			glVertex3d(2.50f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);

			glTexCoord2d(1.0, 1.0 + xWaterOffset);
			glVertex3d(2.25f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);

			glTexCoord2d(1.0, 0.0 + xWaterOffset);
			glVertex3d(3.0f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);

			glTexCoord2d(0.0, 0.0 + xWaterOffset);
			glVertex3d(3.0f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH - UNITWIDTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//right S-bend
void DrawRiverRide_27(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glPushMatrix();

		glTranslated(-1.0f * UNITWIDTH, 0.0f, 0.0f);

		//segment #1
		//bottom floor
		glBegin(GL_QUADS);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		//right side
		glBegin(GL_QUADS);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		//left side
		glBegin(GL_QUADS);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.0f,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		//water
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0 + xWaterOffset);	
			glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0, 1.0 + xWaterOffset);
			glVertex3d(0.0f,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0, 0.0 + xWaterOffset);
			glVertex3d(0.75f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(0.0, 0.0 + xWaterOffset);
			glVertex3d(0.50f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

		//segment #2		
		//bottom floor
		glBegin(GL_QUADS);
			glVertex3d(0.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();
		

		//right side		
		glBegin(GL_QUADS);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.75f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		
		//left side
		glBegin(GL_QUADS);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(0.50f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		
		//water
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 2.0f + xWaterOffset);	
			glVertex3d(0.50f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0f, 2.0f + xWaterOffset);
			glVertex3d(0.75f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH);

			glTexCoord2d(1.0f, 0.0f + xWaterOffset);
			glVertex3d(2.50f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);

			glTexCoord2d(0.0f, 0.0f + xWaterOffset);
			glVertex3d(2.25f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

		


		//segment #3
		//bottom floor
		glBegin(GL_QUADS);
			glVertex3d(2.25f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		//right side
		glBegin(GL_QUADS);
			glVertex3d(2.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(2.50f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) - (TOP_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		//left side
		glBegin(GL_QUADS);
			glVertex3d(2.25f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(2.25f * UNITWIDTH,		RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT + FLUME_HEIGHT * UNITHEIGHT,	(0.5f * UNITWIDTH) + (TOP_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
			glVertex3d(3.0f * UNITWIDTH,	RIDEOFFSETHEIGHT * UNITHEIGHT,								(0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		//water
		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0 + xWaterOffset);	
			glVertex3d(2.25f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);

			glTexCoord2d(1.0, 1.0 + xWaterOffset);
			glVertex3d(2.50f * UNITWIDTH,		WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);

			glTexCoord2d(1.0, 0.0 + xWaterOffset);
			glVertex3d(3.0f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) - (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);

			glTexCoord2d(0.0, 0.0 + xWaterOffset);
			glVertex3d(3.0f * UNITWIDTH,	WATER_LEVEL * UNITHEIGHT, (0.5f * UNITWIDTH) + (BOTTOM_WIDTH / 2.0f) * UNITWIDTH + UNITWIDTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
