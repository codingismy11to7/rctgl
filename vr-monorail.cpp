#include "vr3d.h" 

#define MONORAIL_LEFTBEAM		0.45f
#define MONORAIL_RIGHTBEAM	0.55f
#define MONORAIL_TOPBEAM		0.2f
#define MONORAIL_BOTTOMBEAM	0.65f
#define MONORAIL_RAILHEIGHT	0.5f
#define MONORAIL_LEFTRAIL		0.25f
#define MONORAIL_RIGHTRAIL	0.75f
#define MONORAIL_RAILDIAMETER	0.1f

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];

extern double ambientRValue, ambientGValue, ambientBValue;
extern double lightRValue, lightGValue, lightBValue;

extern double calcLightFactor(double n1, double n2, double n3);

//flat piece
void DrawMonorail_00(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	float r, g, b;
	float baseColor[3] = {RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]};
	float val;

	glShadeModel(GL_SMOOTH);

	val = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);


	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

	//draw the top support beam
	//glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	val = calcLightFactor(0.0f, -1.0f, 0.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	val = calcLightFactor(0.0f, 0.0f, -1.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	val = calcLightFactor(0.0f, 0.0f, 1.0f);
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);

}

// 25 degree up hill
void DrawMonorail_04(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );


	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

}


//flat to 25 up
void DrawMonorail_06(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

}



//25 up -> flat
void DrawMonorail_09(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );


	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

}


//25 degree drop
void DrawMonorail_0A(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,  segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,  segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,  segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 1.0f) * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 1.0f) * UNITHEIGHT,  segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

}



//flat to 25 down
void DrawMonorail_0C(int rideIndex, int colorIndex, bool doDiag)
{
	double segWid;

	if(doDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT,		segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		(MONORAIL_TOPBEAM + 0.5f) * UNITHEIGHT,		segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		(MONORAIL_BOTTOMBEAM + 0.5f) * UNITHEIGHT,	segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT,			segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT,				segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

}




//left 1/4 D5
void DrawMonorail_10(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 22.5f;

	float halfRailDiameter;

	halfRailDiameter = MONORAIL_RAILDIAMETER / 2.0f;

	glEnable(GL_TEXTURE_2D);

	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;

	float baseColor[3] = {RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]};
	float val1, val2, val3;

	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);


	radius1 = (2.0f  + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f  + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glShadeModel(GL_SMOOTH);

	for(i=0.0f; i<90.0f; i+=step)
	{
		val1 = calcLightFactor(sinTable[(int)(i + 180)], 0.0f, cosTable[(int)(i + 180)]);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(sinTable[(int)(i + step + 180)], 0.0f, cosTable[(int)(i + step + 180)]);
		calcColor(baseColor, val2, &r2, &g2, &b2);		

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glColor3f(r1, g1, b1);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glColor3f(r2, g2, b2);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		val3 = calcLightFactor(0.0f, 1.0f, 0.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);		

		glColor3f(r3, g3, b3);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		val1 = calcLightFactor(sinTable[(int)(i)], 0.0f, cosTable[(int)(i)]);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(sinTable[(int)(i + step)], 0.0f, cosTable[(int)(i + step)]);
		calcColor(baseColor, val2, &r2, &g2, &b2);		

		glBegin(GL_QUADS);			
			glColor3f(r1, g1, b1);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glColor3f(r2, g2, b2);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		val3 = calcLightFactor(0.0f, -1.0f, 0.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);		

		glColor3f(r3, g3, b3);

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glShadeModel(GL_FLAT);

	glDisable(GL_TEXTURE_2D);

}

//right 1/4 D5
void DrawMonorail_11(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 22.5f;

	float halfRailDiameter;

	halfRailDiameter = MONORAIL_RAILDIAMETER / 2.0f;

	//draw the beam
	radius1 = (2.0f + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (2.0f + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glEnable(GL_TEXTURE_2D);

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0.0f; i<90.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}


//flat piece
void DrawMonorail_26(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, -UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();


	glDisable(GL_TEXTURE_2D);

}


//flat piece
void DrawMonorail_27(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_LEFTBEAM * UNITWIDTH);
	glEnd();

	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.0f,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(0.25f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(3.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3d(2.75f * UNITWIDTH,		MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_BOTTOMBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(3.0f * UNITWIDTH,	MONORAIL_TOPBEAM * UNITHEIGHT, UNITWIDTH + segWid * MONORAIL_RIGHTBEAM * UNITWIDTH);
	glEnd();


	glDisable(GL_TEXTURE_2D);

}



//left 1/4 D3 turn
void DrawMonorail_2A(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 22.5f;

	float halfRailDiameter;

	halfRailDiameter = MONORAIL_RAILDIAMETER / 2.0f;

	glEnable(GL_TEXTURE_2D);

	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;

	float baseColor[3] = {RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]};
	float val1, val2, val3;

	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);


	radius1 = (1.0f  + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (1.0f  + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glShadeModel(GL_SMOOTH);

	for(i=0.0f; i<90.0f; i+=step)
	{
		val1 = calcLightFactor(sinTable[(int)(i + 180)], 0.0f, cosTable[(int)(i + 180)]);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(sinTable[(int)(i + step + 180)], 0.0f, cosTable[(int)(i + step + 180)]);
		calcColor(baseColor, val2, &r2, &g2, &b2);		

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glColor3f(r1, g1, b1);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glColor3f(r2, g2, b2);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		val3 = calcLightFactor(0.0f, 1.0f, 0.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);		

		glColor3f(r3, g3, b3);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		val1 = calcLightFactor(sinTable[(int)(i)], 0.0f, cosTable[(int)(i)]);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(sinTable[(int)(i + step)], 0.0f, cosTable[(int)(i + step)]);
		calcColor(baseColor, val2, &r2, &g2, &b2);		

		glBegin(GL_QUADS);			
			glColor3f(r1, g1, b1);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glColor3f(r2, g2, b2);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		val3 = calcLightFactor(0.0f, -1.0f, 0.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);		

		glColor3f(r3, g3, b3);

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glShadeModel(GL_FLAT);

	glDisable(GL_TEXTURE_2D);


}

//right 1/4 D3 turn
void DrawMonorail_2B(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 22.5f;

	//draw the beam
	radius1 = (1.0f + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (1.0f + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glEnable(GL_TEXTURE_2D);
	
	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	glPushMatrix();

		//glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);

	for(i=0.0f; i<90.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}




//left 1/8 turn OTD
void DrawMonorail_85(int rideIndex, int colorIndex)
{
		double radius1, radius2;
	float i, step;

	step = 9.0f;

	float halfRailDiameter;

	halfRailDiameter = MONORAIL_RAILDIAMETER / 2.0f;

	glEnable(GL_TEXTURE_2D);

	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;

	float baseColor[3] = {RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]};
	float val1, val2, val3;

	//draw the beam
	//glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);


	radius1 = (3.0f  + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (3.0f  + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glShadeModel(GL_SMOOTH);

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);

	for(i=0.0f; i<45.0f; i+=step)
	{
		val1 = calcLightFactor(sinTable[(int)(i + 180)], 0.0f, cosTable[(int)(i + 180)]);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(sinTable[(int)(i + step + 180)], 0.0f, cosTable[(int)(i + step + 180)]);
		calcColor(baseColor, val2, &r2, &g2, &b2);		

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glColor3f(r1, g1, b1);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glColor3f(r2, g2, b2);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		val3 = calcLightFactor(0.0f, 1.0f, 0.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);		

		glColor3f(r3, g3, b3);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		val1 = calcLightFactor(sinTable[(int)(i)], 0.0f, cosTable[(int)(i)]);
		calcColor(baseColor, val1, &r1, &g1, &b1);
		val2 = calcLightFactor(sinTable[(int)(i + step)], 0.0f, cosTable[(int)(i + step)]);
		calcColor(baseColor, val2, &r2, &g2, &b2);		

		glBegin(GL_QUADS);			
			glColor3f(r1, g1, b1);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glColor3f(r2, g2, b2);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		val3 = calcLightFactor(0.0f, -1.0f, 0.0f);
		calcColor(baseColor, val3, &r3, &g3, &b3);		

		glColor3f(r3, g3, b3);

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glPopMatrix();

	glShadeModel(GL_FLAT);

	glDisable(GL_TEXTURE_2D);

	/*
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

	radius1 = (rad  + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	for(i=0.0f; i<45.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);			
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );
		
		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );
		
		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	*/
}


//right 1/8 turn OTD
void DrawMonorail_86(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	step = 9.0f;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	float rad = 3.0f;


	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);


	//draw the beam
	radius1 = (rad + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glEnable(GL_TEXTURE_2D);
	

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);
	
	for(i=0.0f; i<45.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );
		
		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


//left 1/8 turn DTO
void DrawMonorail_87(int rideIndex, int colorIndex)
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

	radius1 = (rad  + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad  + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	for(i=45.0f; i<90.0f; i+=step)
	{
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_TOPBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i],  (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)],(MONORAIL_BOTTOMBEAM) * UNITHEIGHT, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


//right 1/8 turn DTO
void DrawMonorail_88(int rideIndex, int colorIndex)
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
	radius1 = (rad + MONORAIL_LEFTBEAM) * UNITWIDTH;
	radius2 = (rad + MONORAIL_RIGHTBEAM) * UNITWIDTH;

	glColor3f(RCTColorsR[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].PrimaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].PrimaryColor[colorIndex]]);

	glEnable(GL_TEXTURE_2D);
	
	for(i=45.0f; i<90.0f; i+=step)
	{		
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_02] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_01] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)i],	 (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_TOPBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
		glEnd();

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_06_00] );

		glBegin(GL_QUADS);			
			glTexCoord2d(0.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)i],	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)i], 	 (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0f, 1.0f);
			glVertex3d(radius2 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0f, 0.0f);
			glVertex3d(radius1 * sinTable[(int)(i+step)], (MONORAIL_BOTTOMBEAM) * UNITHEIGHT, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void DrawMonorail_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawMonorail_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawMonorail_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawMonorail_04(rideIndex, colorIndex, true);

	glPopMatrix();
}



void DrawMonorail_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawMonorail_06(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawMonorail_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawMonorail_09(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawMonorail_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawMonorail_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}



void DrawMonorail_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawMonorail_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}


