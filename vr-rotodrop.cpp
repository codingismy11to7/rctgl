#include "vr3d.h" 

extern double ambientRValue, ambientGValue, ambientBValue;
extern double lightRValue, lightGValue, lightBValue;

extern double calcLightFactor(double n1, double n2, double n3);

extern int itemRot;

void DrawRotoDrop_42(int rideIndex, int colorIndex)
{
	float val1, val2;

	//printf("rotoDrop rot %d\n", itemRot);

	//N

	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.195f, 0.0f, 0.98f);
		val2 = calcLightFactor(0.195f, 0.0f, 0.98f);
		
		/*
		printf("RideColor (%2.5f, %2.5f, %2.5f)\n", RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
		printf("ambient (%2.5f, %2.5f, %2.5f)\n", ambientRValue, ambientGValue, ambientBValue);
		printf("light (%2.5f, %2.5f, %2.5f)\n", lightRValue, lightGValue, lightBValue);
		*/
		


		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		
		glVertex3d(0.65f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.80f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);


	

	//NE
	glBegin(GL_QUADS);
		val1 = calcLightFactor(0.195f, 0.0f, 0.98f);
		val2 = calcLightFactor(0.98f, 0.0f, 0.195f);

		//printf("vals (%2.5f, %2.5f)\n", val1, val2);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.80f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	

	//E
	glBegin(GL_QUADS);
		val1 = calcLightFactor(0.98f, 0.0f, 0.195f);
		val2 = calcLightFactor(0.98f, 0.0f, -0.195f);

		//printf("vals (%2.5f, %2.5f)\n", val1, val2);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.65f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//SE
	glBegin(GL_QUADS);	
		val1 = calcLightFactor(0.98f, 0.0f, -0.195f);
		val2 = calcLightFactor(0.195f, 0.0f, -0.98f);

		//printf("vals (%2.5f, %2.5f)\n", val1, val2);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	

	//S
	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.195f, 0.0f, -0.98f);
		val2 = calcLightFactor(0.195f, 0.0f, -0.98f);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//SW
	glBegin(GL_QUADS);

		val1 = calcLightFactor(-0.195f, 0.0f, -0.98f);
		val2 = calcLightFactor(-0.98f, 0.0f, -0.195f);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//W
	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.98f, 0.0f, -0.195f);
		val2 = calcLightFactor(-0.98f, 0.0f, 0.195f);

	
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.65f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
	glEnd();	

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);
	
	//NW
	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.195f, 0.0f, 0.98f);
		val2 = calcLightFactor(-0.98f, 0.0f, 0.195f);
		

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.80f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	set_material_color(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glShadeModel(GL_FLAT);

	//draw the side rails
	glColor3f(0.05f, 0.05f, 0.05f);

	glBegin(GL_QUADS);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.82f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.88f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.88f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.82f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.52f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
		glVertex3d(0.52f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.18f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.12f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.12f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.18f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.52f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
		glVertex3d(0.52f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
	glEnd();

	//draw the magnetic brakes
	set_material_color(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glNormal3d(0.0f, 0.0f, -1.0f);
		glVertex3d(0.44f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.36f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.36f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
		glVertex3d(0.44f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3d(0.0f, 0.0f, -1.0f);
		glVertex3d(0.53f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.63f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.63f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
		glVertex3d(0.53f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3d(0.0f, 0.0f, 1.0f);
		glVertex3d(0.44f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.36f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.36f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
		glVertex3d(0.44f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3d(0.0f, 0.0f, 1.0f);
		glVertex3d(0.53f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.63f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.63f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
		glVertex3d(0.53f * UNITWIDTH,	6.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
	glEnd();
	
}

void DrawRotoDrop_43(int rideIndex, int colorIndex)
{
	float val1, val2;

	//N

	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.195f, 0.0f, 0.98f);
		val2 = calcLightFactor(0.195f, 0.0f, 0.98f);
		
		/*
		printf("RideColor (%2.5f, %2.5f, %2.5f)\n", RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);
		printf("ambient (%2.5f, %2.5f, %2.5f)\n", ambientRValue, ambientGValue, ambientBValue);
		printf("light (%2.5f, %2.5f, %2.5f)\n", lightRValue, lightGValue, lightBValue);
		*/
		


		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		
		glVertex3d(0.65f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.80f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);


	

	//NE
	glBegin(GL_QUADS);
		val1 = calcLightFactor(0.195f, 0.0f, 0.98f);
		val2 = calcLightFactor(0.98f, 0.0f, 0.195f);

		//printf("vals (%2.5f, %2.5f)\n", val1, val2);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.80f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	

	//E
	glBegin(GL_QUADS);
		val1 = calcLightFactor(0.98f, 0.0f, 0.195f);
		val2 = calcLightFactor(0.98f, 0.0f, -0.195f);

		//printf("vals (%2.5f, %2.5f)\n", val1, val2);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.65f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//SE
	glBegin(GL_QUADS);	
		val1 = calcLightFactor(0.98f, 0.0f, -0.195f);
		val2 = calcLightFactor(0.195f, 0.0f, -0.98f);

		//printf("vals (%2.5f, %2.5f)\n", val1, val2);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
		
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.80f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	

	//S
	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.195f, 0.0f, -0.98f);
		val2 = calcLightFactor(0.195f, 0.0f, -0.98f);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.65f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//SW
	glBegin(GL_QUADS);

		val1 = calcLightFactor(-0.195f, 0.0f, -0.98f);
		val2 = calcLightFactor(-0.98f, 0.0f, -0.195f);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.20f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.20f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//W
	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.98f, 0.0f, -0.195f);
		val2 = calcLightFactor(-0.98f, 0.0f, 0.195f);

	
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.35f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.65f * UNITWIDTH);
		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.35f * UNITWIDTH);
	glEnd();	

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);
	
	//NW
	glBegin(GL_QUADS);
		val1 = calcLightFactor(-0.195f, 0.0f, 0.98f);
		val2 = calcLightFactor(-0.98f, 0.0f, 0.195f);
		

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	0.0f,				0.80f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	0.0f,				0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val2 * lightBValue);		
		glVertex3d(0.20f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.65f * UNITWIDTH);

		glColor3f(ambientRValue * RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightRValue,
			ambientGValue * RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightGValue,
			ambientBValue * RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]] + val1 * lightBValue);		
		glVertex3d(0.35f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.80f * UNITWIDTH);
	glEnd();

	//printf ("val1: %2.5f\nval2: %2.5f\n", val1, val2);

	//glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	set_material_color(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glShadeModel(GL_FLAT);
	

	//draw the side rails
	glColor3f(0.05f, 0.05f, 0.05f);

	glBegin(GL_QUADS);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.82f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.88f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.88f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.82f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.52f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	0.0f,				0.85f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
		glVertex3d(0.52f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.85f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.18f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	0.0f,				0.12f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.12f * UNITWIDTH);
		glVertex3d(0.50f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.18f * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0.52f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	0.0f,				0.15f * UNITWIDTH);
		glVertex3d(0.47f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
		glVertex3d(0.52f * UNITWIDTH,	2.0f * UNITHEIGHT,	0.15f * UNITWIDTH);
	glEnd();

}