#include "vr3d.h" 

void DrawSingleRailRollerCoaster_00(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//main rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(0.0f,		0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
	glEnd();
}

void DrawSingleRailRollerCoaster_04(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//main rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(0.0f,		0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	1.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	1.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
	glEnd();
}

void DrawSingleRailRollerCoaster_06(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//main rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(0.0f,		0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.7f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.6f * UNITHEIGHT, 0.5f * UNITWIDTH);
	glEnd();
}

void DrawSingleRailRollerCoaster_0A(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//main rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		1.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(0.0f,		1.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
	glEnd();
}

void DrawSingleRailRollerCoaster_0C(int rideIndex, int colorIndex)
{
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	//main rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		0.6f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(0.0f,		0.7f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.2f * UNITHEIGHT, 0.5f * UNITWIDTH);
		glVertex3d(UNITWIDTH,	0.1f * UNITHEIGHT, 0.5f * UNITWIDTH);
	glEnd();
}

void DrawSingleRailRollerCoaster_10(int rideIndex, int colorIndex)
{
	double radius;
	double degrees[5];
	int i;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//main rail
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius * sin(degrees[i]),	0.1f * UNITHEIGHT, (-1.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i]),	0.2f * UNITHEIGHT, (-1.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i+1]),	0.2f * UNITHEIGHT, (-1.0f * UNITWIDTH + radius * cos(degrees[i+1])));
			glVertex3d(radius * sin(degrees[i+1]),	0.1f * UNITHEIGHT, (-1.0f * UNITWIDTH + radius * cos(degrees[i+1])));
		glEnd();
	}
}

void DrawSingleRailRollerCoaster_11(int rideIndex, int colorIndex)
{
	double radius;
	double degrees[5];
	int i;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//main rail
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius * sin(degrees[i]),	0.1f * UNITHEIGHT, -1 * (-2.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i]),	0.2f * UNITHEIGHT, -1 * (-2.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i+1]),	0.2f * UNITHEIGHT, -1 * (-2.0f * UNITWIDTH + radius * cos(degrees[i+1])));
			glVertex3d(radius * sin(degrees[i+1]),	0.1f * UNITHEIGHT, -1 * (-2.0f * UNITWIDTH + radius * cos(degrees[i+1])));
		glEnd();
	}
}


void DrawSingleRailRollerCoaster_2A(int rideIndex, int colorIndex)
{
	double radius;
	double degrees[5];
	int i;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius = 1.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//main rail
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius * sin(degrees[i]),	0.1f * UNITHEIGHT, (-0.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i]),	0.2f * UNITHEIGHT, (-0.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i+1]),	0.2f * UNITHEIGHT, (-0.0f * UNITWIDTH + radius * cos(degrees[i+1])));
			glVertex3d(radius * sin(degrees[i+1]),	0.1f * UNITHEIGHT, (-0.0f * UNITWIDTH + radius * cos(degrees[i+1])));
		glEnd();
	}
}

void DrawSingleRailRollerCoaster_2B(int rideIndex, int colorIndex)
{
	double radius;
	double degrees[5];
	int i;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius = 1.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//main rail
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius * sin(degrees[i]),	0.1f * UNITHEIGHT, -1 * (-1.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i]),	0.2f * UNITHEIGHT, -1 * (-1.0f * UNITWIDTH + radius * cos(degrees[i])));
			glVertex3d(radius * sin(degrees[i+1]),	0.2f * UNITHEIGHT, -1 * (-1.0f * UNITWIDTH + radius * cos(degrees[i+1])));
			glVertex3d(radius * sin(degrees[i+1]),	0.1f * UNITHEIGHT, -1 * (-1.0f * UNITWIDTH + radius * cos(degrees[i+1])));
		glEnd();
	}
}
