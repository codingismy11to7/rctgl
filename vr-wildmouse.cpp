#include "vr3d.h"

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];


//level track
void DrawWildMouse_00(int rideIndex, int colorIndex)
{	
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glColor3f(0.5f, 0.5f, 0.5f);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f, UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f, UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f, 0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 25 up
void DrawWildMouse_04(int rideIndex, int colorIndex)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glColor3f(0.5f, 0.5f, 0.5f);

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

// 60 up
void DrawWildMouse_05(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	4.0f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	4.0f * UNITHEIGHT,	0.0f);
	glEnd();
	

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


// flat -> 25 up
void DrawWildMouse_06(int rideIndex, int colorIndex)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glColor3f(0.5f, 0.5f, 0.5f);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.5f * UNITHEIGHT,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

// 25 up -> 60 up
void DrawWildMouse_07(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	2.0f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	2.0f * UNITHEIGHT,	0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


//25 down
void DrawWildMouse_0A(int rideIndex, int colorIndex)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glColor3f(0.5f, 0.5f, 0.5f);
	
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

//60 down
void DrawWildMouse_0B(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		4.0f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		4.0f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();


	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}



//flat -> 25 down
void DrawWildMouse_0C(int rideIndex, int colorIndex)
{
	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glColor3f(0.5f, 0.5f, 0.5f);
	
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.5f * UNITHEIGHT,		UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//25 down -> 60 down
void DrawWildMouse_0D(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		2.0f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		2.0f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,			segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,			0.0f);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}




//d3 left
void DrawWildMouse_2A(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 1.0f * UNITWIDTH;
	radius2 = 2.0f * UNITWIDTH;

	glColor3f(0.5f, 0.5f, 0.5f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );


	glPushMatrix();

		glTranslated(0.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		step = 22.5f;

		for(i=0.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);			
				glTexCoord2d(0.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)i],			0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)i],			0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
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
void DrawWildMouse_2B(int rideIndex, int colorIndex)
{
	double radius1, radius2;

	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 2.0f * UNITWIDTH;
	radius2 = 1.0f * UNITWIDTH;

	glColor3f(0.5f, 0.5f, 0.5f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);

		step = 22.5f;

		for(i=0.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)i],			0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)i],			0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
}


//d1 left
void DrawWildMouse_32(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );


	//water
	radius1 = 0.0f * UNITWIDTH;
	radius2 = 1.0f * UNITWIDTH;

	glColor3f(0.5f, 0.5f, 0.5f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );


	glPushMatrix();

		glTranslated(0.0f * UNITWIDTH, 0.0f, 1.0f * UNITWIDTH);

		step = 22.5f;

		for(i=0.0f; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)i],			0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)i],			0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, (-1.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, (-1.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}


//d1 right
void DrawWildMouse_33(int rideIndex, int colorIndex)
{
	double radius1, radius2;
	float i, step;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	radius1 = 1.0f * UNITWIDTH;
	radius2 = 0.0f * UNITWIDTH;

	glColor3f(0.5f, 0.5f, 0.5f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glPushMatrix();

		glTranslated(0.0f, 0.0f, -1.0f * UNITWIDTH);

		step = 22.5f;

		for(i=0; i<90.0f; i+=step)
		{
			glBegin(GL_QUADS);
				//-UNITWIDTH + radius * UNITWIDTH * cos(degrees[i])
				glTexCoord2d(0.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)i],			0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)i]));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)i],			0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)i]));
				glTexCoord2d(1.0, 1.0);
				glVertex3d(radius2 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius2 * cosTable[(int)(i+step)]));
				glTexCoord2d(1.0, 0.0);
				glVertex3d(radius1 * sinTable[(int)(i+step)],	0.0f, -1.0f * (-2.0f * UNITWIDTH + radius1 * cosTable[(int)(i+step)]));
			glEnd();
		}

	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}


// flat -> 60 up
void DrawWildMouse_3E(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		0.0f,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		0.0f,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	1.5f * UNITHEIGHT,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	1.5f * UNITHEIGHT,	0.0f);
	glEnd();
	

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


// flat -> 60 down
void DrawWildMouse_40(int rideIndex, int colorIndex)
{
	double segWid;

	segWid = 1.0f;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_09_00] );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3d(0.0f,		1.5f * UNITHEIGHT,		0.0f);
		glTexCoord2d(0.0f, 1.0f);				
		glVertex3d(0.0f,		1.5f * UNITHEIGHT,		segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 1.0f);	  
		glVertex3d(UNITWIDTH,	0.0f,	segWid * UNITWIDTH);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3d(UNITWIDTH,	0.0f,	0.0f);
	glEnd();
	

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}


