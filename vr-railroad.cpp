#include "vr3d.h"

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];


extern double ambientRValue, ambientGValue, ambientBValue;
extern double lightRValue, lightGValue, lightBValue;

//level track
void DrawRailroad_00(int rideIndex, int colorIndex, bool isDiag)
{
	double segWid;

	if(isDiag)
		segWid = 0.71f;
	else
		segWid = 1.0f;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);	

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 25 up
void DrawRailroad_04(int rideIndex, int colorIndex, bool isDiag)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	double val = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	UNITHEIGHT,	UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	UNITHEIGHT,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// flat -> 25 up
void DrawRailroad_06(int rideIndex, int colorIndex, bool isDiag)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	double val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	double val2 = calcLightFactor(0.0f, 1.0f, 0.0f);
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);	
	
	/*
	glColor3d(ambientRValue * 1.0f + val2 * lightRValue,
		ambientGValue * 1.0f + val2 * lightGValue,
		ambientBValue * 1.0f + val2 * lightBValue);
		*/

	glBegin(GL_QUADS);
		glColor3d(r2, g2, b2);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		UNITWIDTH);

		glColor3d(r1, g1, b1);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);
}


// 25 up -> flat
void DrawRailroad_09(int rideIndex, int colorIndex, bool isDiag)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	double val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);	
	double val2 = calcLightFactor(0.0f, 1.0f, 0.0f);
	float r1, g1, b1;
	float r2, g2, b2;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);	
	

	glBegin(GL_QUADS);
		glColor3d(r1, g1, b1);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		UNITWIDTH);

		glColor3d(r2, g2, b2);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);
}

//25 down
void DrawRailroad_0A(int rideIndex, int colorIndex, bool isDiag)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );



	double val = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);


	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		UNITHEIGHT,		UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//flat -> 25 down
void DrawRailroad_0C(int rideIndex, int colorIndex, bool isDiag)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	double val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	double val2 = calcLightFactor(0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
		glColor3d(ambientRValue * 1.0f + val2 * lightRValue,
			ambientGValue * 1.0f + val2 * lightGValue,
			ambientBValue * 1.0f + val2 * lightBValue);		
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		UNITWIDTH);

		glColor3d(ambientRValue * 1.0f + val1 * lightRValue,
			ambientGValue * 1.0f + val1 * lightGValue,
			ambientBValue * 1.0f + val1 * lightBValue);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);
}


//25 down -> flat
void DrawRailroad_0F(int rideIndex, int colorIndex, bool isDiag)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	double val1 = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
	double val2 = calcLightFactor(0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
		glColor3d(ambientRValue * 1.0f + val1 * lightRValue,
			ambientGValue * 1.0f + val1 * lightGValue,
			ambientBValue * 1.0f + val1 * lightBValue);		
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		UNITWIDTH);

		glColor3d(ambientRValue * 1.0f + val2 * lightRValue,
			ambientGValue * 1.0f + val2 * lightGValue,
			ambientBValue * 1.0f + val2 * lightBValue);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);
}



//d5 left
void DrawRailroad_10(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 2.0f * UNITWIDTH;
	radius2 = 3.0f * UNITWIDTH;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	step = 22.5f;

	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sinTable[(int)i],	0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sinTable[(int)i],	0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


//d5 right
void DrawRailroad_11(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 3.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	step = 22.5f;

	for(i=0.0f; i<90.0f; i+=step)
	{
		glBegin(GL_QUADS);
			//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
			glTexCoord2d(0.0, 0.0);
			glVertex3d(radius1 * sinTable[(int)i],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
			glTexCoord2d(0.0, 1.0);
			glVertex3d(radius2 * sinTable[(int)i],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
			glTexCoord2d(1.0, 1.0);
			glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
			glTexCoord2d(1.0, 0.0);
			glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}



//d3 left
void DrawRailroad_2A(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 1.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	step = 22.5f;


	glPushMatrix();

		glTranslated(0.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		for(i=0.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
				glTexCoord2d(0.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)i],	0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)i],	0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//d3 right
void DrawRailroad_2B(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 2.0f * UNITWIDTH;
	radius2 = 1.0f * UNITWIDTH;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	step = 22.5f;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);

		for(i=0.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
				glTexCoord2d(0.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)i],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)i],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//left 1/8 turn OTD
void DrawRailroad_85(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	step = 9.0f;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -2.0f * UNITWIDTH);
	
		radius1 = (3.0f) * UNITWIDTH;
		radius2 = (4.0f) * UNITWIDTH;


		for(i=0.0f; i<45.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)i],  0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)i],  0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)(i+step)],0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)(i+step)],0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();
}



//right 1/8 turn OTD
void DrawRailroad_86(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	step = 9.0f;

	glPushMatrix();

		glTranslated(0.0f, 0.0f, 2.0f * UNITWIDTH);

		radius1 = (3.0f) * UNITWIDTH;
		radius2 = (4.0f) * UNITWIDTH;		
		
		for(i=0.0f; i<45.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)i],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)i], 	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)(i+step)], 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)(i+step)], 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();
}



void DrawRailroad_87(int rideIndex, int colorIndex)
{	
	double radius1, radius2;
	float i, step;

	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);


	glPushMatrix();

		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, -2.0f * UNITWIDTH);	

		glAlphaFunc ( GL_LESS, 0.4f );
		glEnable    ( GL_ALPHA_TEST   );

		glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

		step = 9.0f;
		

		radius1 = (3.0f) * UNITWIDTH;
		radius2 = (4.0f) * UNITWIDTH;

		for(i=45.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)i],  0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)i],  0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)(i+step)],0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)(i+step)],0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();
}



//right 1/8 turn DTO
void DrawRailroad_88(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;
	
	double val = calcLightFactor(0.0f, 1.0f, 0.0f);

	float r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};
	calcColor(baseColor, val, &r, &g, &b);
	glColor3f(r, g, b);

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_05_00] );

	glPushMatrix();

		glRotated(0.0f, 0.0f, 1.0f, 0.0f);

		glTranslated(-2.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		radius1 = (3.0f) * UNITWIDTH;
		radius2 = (4.0f) * UNITWIDTH;
		

		step = 9.0f;
		
		for(i=45.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cosTable[(int)i]
				glTexCoord2d(0.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)i],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)i], 	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0f, 1.0f);
				glVertex3d(radius2 * sinTable[(int)(i+step)], 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0f, 0.0f);
				glVertex3d(radius1 * sinTable[(int)(i+step)], 0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();
}



/*====================================
 *======= Diagonal Segments ==========
 *====================================
 */
void DrawRailroad_8D(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawRailroad_00(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawRailroad_8E(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawRailroad_04(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawRailroad_90(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawRailroad_06(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawRailroad_93(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawRailroad_06(rideIndex, colorIndex, true);

	glPopMatrix();
}


void DrawRailroad_94(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawRailroad_0A(rideIndex, colorIndex, true);

	glPopMatrix();
}

void DrawRailroad_96(int rideIndex, int colorIndex)
{	
	glPushMatrix();

		glScalef(1.41f, 1.0f, 1.41f);

		glTranslated(((0.5f + 0.1f) * UNITWIDTH), 0.0f, ((-0.75f + 0.1f) * UNITWIDTH));

		glRotated(-45.0f, 0.0f, 1.0f, 0.0f);

		DrawRailroad_0C(rideIndex, colorIndex, true);

	glPopMatrix();
}


