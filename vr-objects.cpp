#include "vr3d.h"

/* -- createStraight() --
 * draws a straight piece of track
 */
GLvoid createStraight(int detail)
{
	/* if we're in low detail mode, don't use textures */
	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}
	

	/* start a new strip */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 1.0);	
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();

	glDisable(GL_TEXTURE_2D);	
}

/* -- createStation() --
 * draws a piece of station track
 */
GLvoid createStationMiddle(int detail)
{
	/* if we're in low detail mode, don't use textures */
	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}
	
	/* draw the track */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 1.0);	
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();

	if(detail==1)
		glColor3f(0.8f, 0.68f, 0.49f);
	else
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICK2] );

	/* draw both sides of the station */
	/* top side */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);

	glEnd();


	/* top side - side walls */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      UNITWIDTH);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      UNITWIDTH);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);

	glEnd();


    /* bottom side */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);

	glEnd();

	/* bottom side - walls */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      0.0f);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      0.0f);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);

	glEnd();



	glDisable(GL_TEXTURE_2D);
}

GLvoid createStationStart(int detail)
{
	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}
	
	/* draw the track */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 1.0);	
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();

	if(detail==1)
		glColor3f(0.8f, 0.68f, 0.49f);
	else
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICK2] );

	/* draw both sides of the station */
	/* top side */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);

	glEnd();

	/* top side - side walls */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      UNITWIDTH);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      UNITWIDTH);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);

	glEnd();

	/* top - end edge */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f, 0.0f                      , (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(0.0f, VIRGINIA_REEL_RAIL_HEIGHT , (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(0.0f, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f, 0.0f                     , UNITWIDTH);

	glEnd();


    /* bottom side */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);

	glEnd();

	/* bottom side - walls */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      0.0f);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      0.0f);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);

	glEnd();

	/* top - end edge */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f, 0.0f                      , (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(0.0f, VIRGINIA_REEL_RAIL_HEIGHT , (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(0.0f, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f, 0.0f                     , 0.0f);

	glEnd();





	glDisable(GL_TEXTURE_2D);
}

GLvoid createStationEnd(int detail)
{
	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}
	
	/* draw the track */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 1.0);	
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(1.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,       0.0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();


	if(detail==1)
		glColor3f(0.8f, 0.68f, 0.49f);
	else
		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICK2] );


	/* draw both sides of the station */
	/* top side */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);

	glEnd();

	/* top side - side walls */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      UNITWIDTH);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      UNITWIDTH);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);

	glEnd();

	/* top - end edge */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(UNITWIDTH, 0.0f                      , (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT , (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, UNITWIDTH);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0f                     , UNITWIDTH);

	glEnd();


    /* bottom side */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);

	glEnd();

	/* bottom side - walls */
	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(0.0f,      0.0f,                      0.0f);
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, 0.0f,                      0.0f);
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f,      VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);

	glEnd();

	/* top - end edge */
    glBegin(GL_QUADS);
	
		glNormal3d(0,1,0);
		glTexCoord2f(0.0, 4.0);	
		glVertex3f(UNITWIDTH, 0.0f                      , (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 4.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT , (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glTexCoord2f(4.0, 0.0);
		glVertex3f(UNITWIDTH, VIRGINIA_REEL_RAIL_HEIGHT, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0f                     , 0.0f);

	glEnd();


	glDisable(GL_TEXTURE_2D);
}


/* -- createSmallTurn() --
 * draws a small turn
 */
GLvoid createSmallTurn(int detail)
{
	float angle;
	float angles[HIGH_CIRCLE_SEGMENTS+1];
	float distance1, distance2;
	int i;
	int segments;

	switch(detail)
	{
	case 1:
		segments = LOW_CIRCLE_SEGMENTS;
		break;
	case 2:
		segments = MEDIUM_CIRCLE_SEGMENTS;
		break;
	case 3:
		segments = HIGH_CIRCLE_SEGMENTS;
		break;
	}

	distance1 = (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH);
	distance2 = (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH);

	angle=(3.14f * 1.5f);

	for(i=0; i<=segments; i++)
	{
		angles[i] = angle;
		angle+=(float)(1.57/segments);
	}

	angles[segments] = 0.0f;


	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}



	for(i=1; i<=segments; i++)
	{
		glBegin(GL_QUADS);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(cos(angles[i-1]) * distance1, 0.0f, sin(angles[i-1]) * distance1 * -1.0f);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(cos(angles[i]) * distance1, 0.0f, sin(angles[i]) * distance1 * -1.0f);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(cos(angles[i]) * distance2, 0.0f, sin(angles[i]) * distance2 * -1.0f);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(cos(angles[i-1]) * distance2, 0.0f, sin(angles[i-1]) * distance2 * -1.0f);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

}

/* -- createMediumTurn() --
 * draws a medium turn (the largest one available
 * for a Virginia Reel)
 */
GLvoid createMediumTurn(int detail)
{
	float angle;
	float angles[HIGH_CIRCLE_SEGMENTS+1];
	float distance1, distance2;
	int i;
	int segments;

	switch(detail)
	{
	case 1:
		segments = LOW_CIRCLE_SEGMENTS;
		break;
	case 2:
		segments = MEDIUM_CIRCLE_SEGMENTS;
		break;
	case 3:
		segments = HIGH_CIRCLE_SEGMENTS;
		break;
	}


	distance1 = (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH) + UNITWIDTH;
	distance2 = (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH) + UNITWIDTH;

	angle=(3.14f * 1.5f);

	for(i=0; i<=segments; i++)
	{
		angles[i] = angle;
		angle+=(float)(1.57/segments);
	}

	angles[segments] = 0.0f;


	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}


	for(i=1; i<=segments; i++)
	{
		glBegin(GL_QUADS);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(cos(angles[i-1]) * distance1, 0.0f, sin(angles[i-1]) * distance1 * -1.0f - UNITWIDTH);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(cos(angles[i]) * distance1, 0.0f, sin(angles[i]) * distance1 * -1.0f - UNITWIDTH);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(cos(angles[i]) * distance2, 0.0f, sin(angles[i]) * distance2 * -1.0f - UNITWIDTH);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(cos(angles[i-1]) * distance2, 0.0f, sin(angles[i-1]) * distance2 * -1.0f - UNITWIDTH);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}

/* -- createFlatHill() --
 * draws a transition from flat track to a hill
 */
GLvoid createFlatHill(int detail)
{
	/*int angle;*/

	/* start a new strip */
    glBegin(GL_QUADS);

		/* calculate the surface normal */
		glNormal3d(0,1,0);

		/* draw the flat section */
		glVertex3f(0.0f, 0.0f, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glVertex3f(0.0f, 0.0f, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glVertex3f(0.5f * UNITWIDTH, 0.0f, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glVertex3f(0.5f * UNITWIDTH, 0.0f, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);

		glNormal3d(tanh(UNITHEIGHT/UNITWIDTH), M_PI - tanh(UNITHEIGHT/UNITWIDTH), 0);

		glVertex3f(0.5 * UNITWIDTH, 0, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glVertex3f(0.5 * UNITWIDTH, 0, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glVertex3f(UNITWIDTH, 0.5 * UNITHEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glVertex3f(UNITWIDTH, 0.5 * UNITHEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();
}

/* -- createHillFlat() --
 * draws a transition from a hill to flat track
 */
GLvoid createHillFlat(int detail)
{
	/* int angle; */

	/* start a new strip */
    glBegin(GL_QUADS);

		/* calculate the surface normal */
		glNormal3d(0,1,0);

		/* draw the flat section */
		glVertex3f(UNITWIDTH, UNITHEIGHT,  (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glVertex3f(UNITWIDTH, UNITHEIGHT,  (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glVertex3f(0.5f * UNITWIDTH, UNITHEIGHT,  (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glVertex3f(0.5f * UNITWIDTH, UNITHEIGHT,  (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));

	glEnd();

	glBegin(GL_QUADS);

		/* calculate the next normal */
		glNormal3d(tanh(UNITHEIGHT/UNITWIDTH), M_PI - tanh(UNITHEIGHT/UNITWIDTH), 0);

		/* draw the sloped section */
		glVertex3f(0.5f * UNITWIDTH, UNITHEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));
		glVertex3f(0.5f * UNITWIDTH, UNITHEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));

		glVertex3f(0.0f, 0.5 * UNITHEIGHT, (0.5 * UNITWIDTH) + (0.5 * TRACK_WIDTH));
		glVertex3f(0.0f, 0.5 * UNITHEIGHT, (0.5 * UNITWIDTH) - (0.5 * TRACK_WIDTH));

	glEnd();
}

/* createHill() --
 * draws a hill
 */
GLvoid createHill(int detail)
{
	if (detail==1)
	{
		glColor3f(0.45f, 0.42f, 0.38f);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOOD1] );
	}

	/* start a new strip */
    glBegin(GL_QUADS);

		/* calculate the surface normal */
		glNormal3d(0,1,0);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0f, 0.5f * UNITHEIGHT, (0.5f * UNITWIDTH) - (0.5f * TRACK_WIDTH));
		glTexCoord2f(1.0, 0.0);
		glVertex3f(UNITWIDTH, -0.5f * UNITHEIGHT, (0.5f * UNITWIDTH) - (0.5f * TRACK_WIDTH));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(UNITWIDTH, -0.5f * UNITHEIGHT, (0.5f * UNITWIDTH) + (0.5f * TRACK_WIDTH));
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0f, 0.5f * UNITHEIGHT, (0.5f * UNITWIDTH) + (0.5f * TRACK_WIDTH));

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
