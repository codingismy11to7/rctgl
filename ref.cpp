FIX 1A for steel corkscrew and for inverted

						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelTwisterRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelTwisterRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelTwisterRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelTwisterRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelTwisterRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelTwisterRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelTwisterRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelTwisterRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelTwisterRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelTwisterRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelTwisterRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelTwisterRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);


void DrawSteelTwisterRollerCoaster_10(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_11(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_12(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_13(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_14(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_15(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_16(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_17(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_18(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_19(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_1A(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_1B(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_1C(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_1D(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_1E(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_1F(int rideIndex, int colorIndex);


//left 1/4 D5
void DrawSteelTwisterRollerCoaster_10(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f  + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (2.0f  + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


}

//right 1/4 D5
void DrawSteelTwisterRollerCoaster_11(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (2.0f + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
}




//flat -> L bank
void DrawSteelTwisterRollerCoaster_12(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	



	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//flat -> R bank
void DrawSteelTwisterRollerCoaster_13(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//L bank -> flat
void DrawSteelTwisterRollerCoaster_14(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	
	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}


//R bank -> flat
void DrawSteelTwisterRollerCoaster_15(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}


//left 1/4 D5 turn banked
void DrawSteelTwisterRollerCoaster_16(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f  + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (2.0f  + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


}

//right 1/4 D5 turn banked
void DrawSteelTwisterRollerCoaster_17(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (2.0f + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
}

//L bank -> 25 up
void DrawSteelTwisterRollerCoaster_18(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//R bank -> 25 up
void DrawSteelTwisterRollerCoaster_19(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 up -> L Bank
void DrawSteelTwisterRollerCoaster_1A(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 up -> R Bank
void DrawSteelTwisterRollerCoaster_1B(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

		//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}


//L bank -> 25 down
void DrawSteelTwisterRollerCoaster_1C(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//R bank -> 25 down
void DrawSteelTwisterRollerCoaster_1D(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 down -> L bank
void DrawSteelTwisterRollerCoaster_1E(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 down -> R bank
void DrawSteelTwisterRollerCoaster_1F(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}
//left 1/4 D5
void DrawSteelTwisterRollerCoaster_10(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f  + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (2.0f  + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


}

//right 1/4 D5
void DrawSteelTwisterRollerCoaster_11(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	int i;

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (2.0f + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
}




//flat -> L bank
void DrawSteelTwisterRollerCoaster_12(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	



	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//flat -> R bank
void DrawSteelTwisterRollerCoaster_13(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//L bank -> flat
void DrawSteelTwisterRollerCoaster_14(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	
	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}


//R bank -> flat
void DrawSteelTwisterRollerCoaster_15(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT),	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT * UNITHEIGHT), (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}


//left 1/4 D5 turn banked
void DrawSteelTwisterRollerCoaster_16(int rideIndex, int colorIndex)
{
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;


	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;
	

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]),	STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]),STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f  + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	radius1 = (2.0f  + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f  + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]),  (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]),(STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}


}

//right 1/4 D5 turn banked
void DrawSteelTwisterRollerCoaster_17(int rideIndex, int colorIndex)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2;
	double degrees[5];
	double angledHeight;
	int i;

	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 0.0f  * 3.14/180.0f;
	degrees[1] = 22.5f * 3.14/180.0f;
	degrees[2] = 45.0f * 3.14/180.0f;
	degrees[3] = 67.5f * 3.14/180.0f;
	degrees[4] = 90.0f * 3.14/180.0f;

	//rails
	radius1a = (2.0f  + STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH;
	radius1b = (2.0f  + STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH;
	radius2a = (2.0f  + STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH;
	radius2b = (2.0f  + STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1a * sin(degrees[i]),	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i]), 	 (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i])));
			glVertex3d(radius1b * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1b * cos(degrees[i+1])));
			glVertex3d(radius1a * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1a * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2a * sin(degrees[i]),	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i]),	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i])));
			glVertex3d(radius2b * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2b * cos(degrees[i+1])));
			glVertex3d(radius2a * sin(degrees[i+1]),angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2a * cos(degrees[i+1])));
		glEnd();
	}

	radius1 = (2.0f + STEELTWISTER_LEFTRAIL) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTRAIL) * UNITWIDTH;

	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();
	}


	//draw the beam
	radius1 = (2.0f + STEELTWISTER_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f + STEELTWISTER_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
	
	for(i=0; i<4; i++)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius2 * sin(degrees[i]),	 (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
		glEnd();

		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
			glVertex3d(radius1 * sin(degrees[i]),	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i]), 	 (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i])));
			glVertex3d(radius2 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cos(degrees[i+1])));
			glVertex3d(radius1 * sin(degrees[i+1]), (STEELTWISTER_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cos(degrees[i+1])));
		glEnd();
	}
}

//L bank -> 25 up
void DrawSteelTwisterRollerCoaster_18(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//R bank -> 25 up
void DrawSteelTwisterRollerCoaster_19(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 up -> L Bank
void DrawSteelTwisterRollerCoaster_1A(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_RAILHEIGHT * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 up -> R Bank
void DrawSteelTwisterRollerCoaster_1B(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

		//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	


	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}


//L bank -> 25 down
void DrawSteelTwisterRollerCoaster_1C(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//R bank -> 25 down
void DrawSteelTwisterRollerCoaster_1D(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		angledHeight + (0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 down -> L bank
void DrawSteelTwisterRollerCoaster_1E(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	//right rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	//left rail
	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}

//25 down -> R bank
void DrawSteelTwisterRollerCoaster_1F(int rideIndex, int colorIndex)
{
	double angledHeight;
	double divideFactor = 0.642f; //(cos 50 = precalced);

	angledHeight = ((STEELTWISTER_RIGHTRAIL - STEELTWISTER_LEFTRAIL)) / divideFactor;

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_LEFTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(STEELTWISTER_TOPBEAM + 0.5f) * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(0.0f,		(STEELTWISTER_BOTTOMBEAM + 0.5f) * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_BOTTOMBEAM * UNITHEIGHT, STEELTWISTER_RIGHTBEAM * UNITWIDTH);
		glVertex3d(UNITWIDTH,	STEELTWISTER_TOPBEAM * UNITHEIGHT,	STEELTWISTER_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float halfRailDiameter;

	halfRailDiameter = STEELTWISTER_RAILDIAMETER / 2.0f;

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_RIGHTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT,	STEELTWISTER_RIGHTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_RIGHTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	(STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_RIGHTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT - halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT + halfRailDiameter) * UNITHEIGHT, STEELTWISTER_LEFTRAIL * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
		glVertex3d(0.0f,		(0.5f + STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT, (STEELTWISTER_LEFTRAIL - halfRailDiameter) * UNITWIDTH);
		glVertex3d(UNITWIDTH,	angledHeight + (STEELTWISTER_RAILHEIGHT) * UNITHEIGHT,	(STEELTWISTER_LEFTRAIL + halfRailDiameter) * UNITWIDTH);
	glEnd();
}
