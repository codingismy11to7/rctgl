/* 
 * Virginia Reel 3D
 * Simulates a ride on a Virginia Reel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <glut.h>

#define MULTIPLER 10	/* basic multiplier to make objects larger */

#define UNITWIDTH 3.2	/* each tile has 10 m^2 area */
#define UNITHEIGHT 1.3	/* each 'unit' is 1 1/3 meters */

#define CIRCLE_SEGMENTS 4
#define TRACK_WIDTH 0.5	/* percentage of one unit */

#define VPD_MIN     200
#define VPD_DEFAULT 256
#define VPD_MAX     400

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define VIRGINA_REEL_TRACK_WIDTH 1.6

/* the only pieces used in a Virgina Reel are as follows (hex):
	00 - flat
	01 - end station
	02 - begin station
	03 - middle station
	04 - 25 upward hill
	06 - transition from flat to 25 upward hill
	09 - 25 upward hill to flat
	0A - 25 downward hill
	0C - flat to 25 downward hill
	0F - 25 downward hill to flat
	2A - medium left turn
	2B - medium right turn
	32 - sharp left turn
	33 - sharp right turn
	*/

/*
acceleration tests on virginia reel ride
when starting from station @ 4kph-1 - 500meters - 3:36:05 -3:39:40 (3:35 diff)
when going uphill starting @ 41kph-1 - 2.5 sec til stop
when going downhill 8kph to 41kph - 2.25 sec
lift speed - 8kph-1
no extra friction when going around turns
*/


int FileFormat;		/* indicates whether data is in RCT format (0)
					   or CF/LL format (1) */

int StationColor[3] = {1,0,0};	/* make the station red */
int LiftColor[3] = {0,1,0};		/* make the lift green */
int TrackColor[3] = {0,0,1};	/* make the regular track blue */

GLint main(int argc, char *argv[])
{
	FILE *input;
	char buffer;
	short *shorttemp;
	long *longtemp;
	char *chartemp;
	

	if(argc < 2)
	{
		printf("syntax: vreel3d inputfile\n");
		exit(-1);
	}

	DecompressFile(argc[1]);

	/* initialize GLUT: register callbacks, etc */
	wid = init_glut(&argc, argv);

	/* any OpenGL state initialization we need to do */
	init_opengl();

	init_lightsource();

	/* CREATE THE DISPLAY LIST FOR THE SCENE */
	sceneID = create_scene();

	glutMainLoop();

	return 0;
}








GLuint create_scene ( )
{
	GLuint torusList = glGenLists (1);
	GLuint sceneList = glGenLists(1);
	GLfloat fAngle = 45;
	GLfloat fMultiplier;

	GLfloat FogColor[4] = {1.0, 1.0, 1.0, 0.5};

	fMultiplier = (1 / (TORUS_RADIUS + TORUS_THICKNESS));

  
	torusList = glGenLists (1);
	glNewList(torusList, GL_COMPILE);
	create_torus();
	glEndList();

	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	glNewList(sceneList,GL_COMPILE);

  
	set_material_color(0.0,0.0,1.0,1.0);

	glPushMatrix();
		glTranslatef(-1.0,0.0,0.0);
		glEnable(GL_BLEND);
		glScalef(fMultiplier,fMultiplier,fMultiplier);
		glCallList(torusList);
	glPopMatrix();
  
	set_material_color(1.0,0.0,0.0,0.75);

	glPushMatrix();
		glTranslatef(0.0,0.0,0.0);
		glScalef(fMultiplier,fMultiplier,fMultiplier);
		glRotated(fAngle,1.0f,0.0f,0.0f);
		glEnable(GL_BLEND);
		glCallList(torusList);
	glPopMatrix();
  
	set_material_color(0.0,1.0,0.0,0.5);
  
	glPushMatrix();
		glTranslatef(1.0,0.0,0.0);
		glScalef(fMultiplier,fMultiplier,fMultiplier);
		glRotated(-fAngle,1.0f,0.0f,0.0f);
		glEnable(GL_BLEND);
		glCallList(torusList);
	glPopMatrix();
  
	glEndList();

	return sceneList;
}


