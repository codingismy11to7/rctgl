#include "vr3d.h" 

void DrawSpaceShot_42(int rideIndex, int colorIndex)
{
	glPushMatrix();

		glTranslated(0.0f, 0.0f, UNITWIDTH);

		//draw inner thing
		float r, g, b;
		float baseColor[3] = {RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]};
		float val;

		val = calcLightFactor(0.0f, 0.0f, 1.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);
		glBegin(GL_QUADS);
			glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
			glVertex3d(0.40f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
		glEnd();

		val = calcLightFactor(0.0f, 0.0f, -1.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);
			glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
			glVertex3d(0.40f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
		glEnd();

		val = calcLightFactor(-1.0f, 0.0f, 0.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);
			glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
			glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
			glVertex3d(0.40f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
			glVertex3d(0.40f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
		glEnd();

		val = calcLightFactor(1.0f, 0.0f, 0.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);
			glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
			glVertex3d(0.60f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
		glEnd();


		//draw outer shell
		baseColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
		baseColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
		baseColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];

		glAlphaFunc ( GL_LESS, 0.4f );
		glEnable    ( GL_ALPHA_TEST   );

		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0C_00] );

		val = calcLightFactor(0.0f, 0.0f, 1.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
			glTexCoord2d(1.0f, 3.0f);
			glVertex3d(0.68f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
			glTexCoord2d(0.0f, 3.0f);
			glVertex3d(0.31f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
		glEnd();	

		val = calcLightFactor(0.0f, 0.0f, -1.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);	
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
			glTexCoord2d(1.0f, 3.0f);
			glVertex3d(0.68f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
			glTexCoord2d(0.0f, 3.0f);
			glVertex3d(0.31f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
		glEnd();	

		val = calcLightFactor(-1.0f, 0.0f, 0.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
			glTexCoord2d(1.0f, 3.0f);
			glVertex3d(0.31f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
			glTexCoord2d(0.0f, 3.0f);
			glVertex3d(0.31f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
		glEnd();

		val = calcLightFactor(1.0f, 0.0f, 0.0f);
		calcColor(baseColor, val, &r, &g, &b);
		glColor3f(r, g, b);

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
			glTexCoord2d(1.0f, 3.0f);
			glVertex3d(0.68f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
			glTexCoord2d(0.0f, 3.0f);
			glVertex3d(0.68f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
		glEnd();	

		
	glPopMatrix();

}

void DrawSpaceShot_43(int rideIndex, int colorIndex)
{
	//draw inner thing
	float r, g, b;
	float baseColor[3] = {RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]};
	float val;

	val = calcLightFactor(0.0f, 0.0f, 1.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
		glVertex3d(0.40f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
	glEnd();

	val = calcLightFactor(0.0f, 0.0f, -1.0f); 
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);
	
	glBegin(GL_QUADS);
		glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
		glVertex3d(0.40f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
	glEnd();

	val = calcLightFactor(-1.0f, 0.0f, 0.0f); //changed
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
		glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
		glVertex3d(0.40f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
		glVertex3d(0.40f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
		glVertex3d(0.40f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
	glEnd();

	val = calcLightFactor(1.0f, 0.0f, 0.0f); //changed
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
		glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.40f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	0.0f,				0.60f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.60f * UNITWIDTH);
		glVertex3d(0.60f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.40f * UNITWIDTH);
	glEnd();


	//draw outer shell
	baseColor[0] = RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]];
	baseColor[1] = RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]];
	baseColor[2] = RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]];
	
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_0C_00] );

	val = calcLightFactor(0.0f, 0.0f, 1.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.68f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.31f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
	glEnd();	

	val = calcLightFactor(0.0f, 0.0f, -1.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);	
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.68f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.31f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
	glEnd();	

	val = calcLightFactor(-1.0f, 0.0f, 0.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);
	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.31f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.31f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.31f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
	glEnd();
	
	val = calcLightFactor(1.0f, 0.0f, 0.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.31f * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.68f * UNITWIDTH,	0.0f,				0.68f * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.68f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.68f * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.68f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.31f * UNITWIDTH);
	glEnd();	

}