#include "vr3d.h"


int wd,hd;
float	rtri;
float	rquad;

float frustum[6][4];		//6 planes - 4 vals per plane

/* -- set_material_color() --
 * sets the color of a material
 */
void set_material_color (float r, float g, float b)
{
	GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient_and_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[1] = { 50.0 };

	GLfloat LightConstant = 0.25;

	if (r<LightConstant)
		mat_specular[0] = mat_ambient_and_diffuse[0] = LightConstant;
	else
		mat_specular[0] = mat_ambient_and_diffuse[0] = r;

	if (g<LightConstant)
		mat_specular[1] = mat_ambient_and_diffuse[1] = LightConstant;
	else
		mat_specular[1] = mat_ambient_and_diffuse[1] = g;

	if (b<LightConstant)
		mat_specular[2] = mat_ambient_and_diffuse[2] = LightConstant;
	else
		mat_specular[2] = mat_ambient_and_diffuse[2] = b;


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
  
	glColor3f(r, g, b);
 
}




GLvoid reshape(GLint w, GLint h)
{
	glViewport     ( 0, 0, w, h );
	glMatrixMode   ( GL_PROJECTION );  // Select The Projection Matrix
	glLoadIdentity ( );                // Reset The Projection Matrix
	if ( h==0 )  // Calculate The Aspect Ratio Of The Window
		gluPerspective ( 80, ( float ) w, 1.0, 5000.0 );
	else
		gluPerspective ( 80, ( float ) w / ( float ) h, 1.0, 5000.0 );
	glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
	glLoadIdentity ( );    // Reset The Model View Matrix

	wd = w;
	hd = h;
}




void display ( void )   // Create The Display Function
{
	//cstring buf;
	char buf[80];
	char YRstr[10];
	char Detstr[20];

	float objHeight;

	//buf.resize(80);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	//glClearDepth(1.0f);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glPushMatrix();
	glRotatef(YR,1.0f,0.0f,0.0f);				// Rotate The Triangle On The Y axis
	glRotatef(XR,0.0f,1.0f,0.0f);
	glTranslatef(-XV,YV,-ZV);						// Move Left 1.5 Units And Into The Screen 6.0	
	//glRotatef(rtri,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis

	objHeight = 32.0f;


	//glCallList(LANDSCAPE_LIST);
	ExtractFrustum();

	/*
	DrawSkyBox();
	DrawLandscape();
	DrawTrees1();
	DrawPaths();
	DrawElements();
	*/

	/*
	glAlphaFunc ( GL_LESS, 0.4 );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_84_1] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.0, 0.0);
		glVertex3f(   0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(UNITWIDTH, 0.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(UNITWIDTH,  (objHeight / 4.0f) * UNITHEIGHT, 0.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(   0.0f,  (objHeight / 4.0f) * UNITHEIGHT, 0.0f);

	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_84_2] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.0, 0.0);
		glVertex3f((UNITWIDTH / 2.0f), 0.0f, -(UNITWIDTH / 2.0f));
		glTexCoord2f(1.0, 0.0);
		glVertex3f((UNITWIDTH / 2.0f), 0.0f, (UNITWIDTH / 2.0f));
		glTexCoord2f(1.0, 1.0);
		glVertex3f((UNITWIDTH / 2.0f),  (objHeight / 4.0f) * UNITHEIGHT, (UNITWIDTH / 2.0f));
		glTexCoord2f(0.0, 1.0);
		glVertex3f((UNITWIDTH / 2.0f),  (objHeight / 4.0f) * UNITHEIGHT, -(UNITWIDTH / 2.0f));

	glEnd();
	*/


		
	//DrawTrack();
	//DrawLandscape();

	
	glPopMatrix();
	rtri+=0.2f;						// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.15f;						// Decrease The Rotation Variable For The Quad     ( NEW )


	ourDoFPS(&buf[0]);

	sprintf(&YRstr[0], "XR:%5.1f", XR);
	
	switch (detailLevel)
	{
	case M_LOW_DETAIL:
		sprintf(Detstr, "Detail: Low");
		break;
	case M_MEDIUM_DETAIL:
		sprintf(Detstr, "Detail: Medium");
		break;
	case M_HIGH_DETAIL:
		sprintf(Detstr, "Detail: High");
		break;
	}

	glColor3f(0.0f,1.0f,1.0f);
	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection();
	/*
	renderBitmapString2f(30,40,GLUT_BITMAP_8_BY_13,buf);
	renderBitmapString2f(30,70,GLUT_BITMAP_8_BY_13,YRstr);
	renderBitmapString2f(30,100,GLUT_BITMAP_8_BY_13,Detstr);
	*/
	glPopMatrix();
	resetPerspectiveProjection();
	
	glFlush();

	/*
	glutSwapBuffers ( );
	*/
	// Swap The Buffers To Not Be Left With A Clear Screen
}


void old_display ( void )   // Create The Display Function
{
	char buf[80];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	//glClearDepth(1.0f);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glPushMatrix();
	glRotatef(YR,1.0f,0.0f,0.0f);				// Rotate The Triangle On The Y axis
	glRotatef(XR,0.0f,1.0f,0.0f);
	glTranslatef(XV,YV,ZV);						// Move Left 1.5 Units And Into The Screen 6.0	
	//glRotatef(rtri,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis


	/*
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRASS1] );
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(50.0f * UNITWIDTH, -0.25f, 50.0f * UNITWIDTH);
		glTexCoord2f(0.0, 50.0); 
		glVertex3f(50.0f * UNITWIDTH, -0.25f, -50.0f * UNITWIDTH);
		glTexCoord2f(50.0, 50.0); 
		glVertex3f(-50.0f * UNITWIDTH, -0.25f, -50.0f * UNITWIDTH);
		glTexCoord2f(50.0, 0.0); 
		glVertex3f(-50.0f * UNITWIDTH, -0.25f, 50.0f * UNITWIDTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	*/


		
	//DrawTrack();
	DrawLandscape();

	
	glPopMatrix();
	rtri+=0.2f;						// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.15f;						// Decrease The Rotation Variable For The Quad     ( NEW )


	ourDoFPS(&buf[0]);

	glColor3f(0.0f,1.0f,1.0f);
	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection();
	/*
	renderBitmapString2f(30,35,GLUT_BITMAP_8_BY_13,buf);
	*/
	glPopMatrix();
	resetPerspectiveProjection();



	/*
	glutSwapBuffers ( );
	*/
	// Swap The Buffers To Not Be Left With A Clear Screen
}


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

void DrawTrack(void)
{
}


void DoRotate(int step)
{
	TOrientation += step;

	if(TOrientation < 0)
	{
		TOrientation += 8;
	}
	else if (TOrientation > 7)
	{
		TOrientation -= 8;
	}
}


void ourDoFPS(char *string) 
{
   static clock_t last=0;
   clock_t now;
   float delta;

   if (++FrameCount >= FRAME_RATE_SAMPLES) {
      now  = clock();
      delta= (now - last) / (float) CLOCKS_PER_SEC;
      last = now;

      FrameRate = FRAME_RATE_SAMPLES / delta;
      FrameCount = 0;	  
   }

   sprintf(string,"FPS:%4.2f", FrameRate);
}


void setOrthographicProjection()
{

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, wd, 0, hd);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -hd, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection()
{
	// set the current matrix to GL_PROJECTION
	glMatrixMode(GL_PROJECTION);
	// restore previous settings
	glPopMatrix();
	// get back to GL_MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}


int CalcDetail(float x, float y, float z)
{
	if ((fabs(XV - x) < MEDIUM_DETAIL_DISTANCE) && 
		(fabs(-YV - y) < MEDIUM_DETAIL_DISTANCE) &&
		(fabs(ZV - z) < MEDIUM_DETAIL_DISTANCE))
	{
		//glColor3f(1.0f, 0.0f, 0.0f);
		return 3;
	}
	else if ((fabs(XV - x) < LOW_DETAIL_DISTANCE) &&
		(fabs(-YV - y) < LOW_DETAIL_DISTANCE) &&
		(fabs(ZV - z) < LOW_DETAIL_DISTANCE))
	{
		//glColor3f(0.0f, 1.0f, 0.0f);
		return 2;
	}
	else
	{
		//glColor3f(0.0f, 0.0f, 1.0f);
		return 1;
	}
}


void DrawSkyBox(void)
{
	float BoxSize = 2000.0f;
	float HalfBox = BoxSize / 2.0f;
	float OffsetBox = 400.0f;

	glPushMatrix();
	glTranslatef(-HalfBox, 0.0f, -HalfBox);

	glEnable(GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYTOP] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.015, 0.015);
		glVertex3f(   0.0f, -OffsetBox, BoxSize);
		glTexCoord2f(0.995, 0.015);
		glVertex3f(BoxSize, -OffsetBox, BoxSize);
		glTexCoord2f(0.995, 0.995);
		glVertex3f(BoxSize,  OffsetBox, BoxSize);
		glTexCoord2f(0.015, 0.995);
		glVertex3f(   0.0f,  OffsetBox, BoxSize);

	glEnd();

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYLEFT] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.995, 0.015);
		glVertex3f(0.0f, -OffsetBox, BoxSize);
		glTexCoord2f(0.015, 0.015);
		glVertex3f(0.0f, -OffsetBox, 0.0f);
		glTexCoord2f(0.015, 0.995);
		glVertex3f(0.0f, OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.995);
		glVertex3f(0.0f, OffsetBox, BoxSize);

	glEnd();



	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYBOTTOM] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.995, 0.015);
		glVertex3f(   0.0f, -OffsetBox, 0.0f);
		glTexCoord2f(0.015, 0.015);
		glVertex3f(BoxSize, -OffsetBox, 0.0f);
		glTexCoord2f(0.015, 0.995);
		glVertex3f(BoxSize,  OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.995);
		glVertex3f(   0.0f,  OffsetBox, 0.0f);

	glEnd();


	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYRIGHT] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.015, 0.015);
		glVertex3f(BoxSize, -OffsetBox, BoxSize);
		glTexCoord2f(0.995, 0.015);
		glVertex3f(BoxSize, -OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.995);
		glVertex3f(BoxSize, OffsetBox, 0.0f);
		glTexCoord2f(0.015, 0.995);
		glVertex3f(BoxSize, OffsetBox, BoxSize);

	glEnd();


	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYUP] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.015, 0.995);
		glVertex3f(   0.0f, OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.995);
		glVertex3f(BoxSize, OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.015);
		glVertex3f(BoxSize, OffsetBox, BoxSize);
		glTexCoord2f(0.015, 0.015);
		glVertex3f(   0.0f, OffsetBox, BoxSize);

	glEnd();


	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYDOWN] );

	glBegin(GL_QUADS);
				
		glTexCoord2f(0.015, 0.995);
		glVertex3f(   0.0f, -OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.995);
		glVertex3f(BoxSize, -OffsetBox, 0.0f);
		glTexCoord2f(0.995, 0.015);
		glVertex3f(BoxSize, -OffsetBox, BoxSize);
		glTexCoord2f(0.015, 0.015);
		glVertex3f(   0.0f, -OffsetBox, BoxSize);

	glEnd();


	glPopMatrix();


}

void ExtractFrustum(void)
{
	float   proj[16];
	float   modl[16];
	float   clip[16];
	float   t;

	/* Get the current PROJECTION matrix from OpenGL */
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	/* Combine the two matrices (multiply projection by modelview) */
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

	/* Extract the numbers for the RIGHT plane */
	frustum[0][0] = clip[ 3] - clip[ 0];
	frustum[0][1] = clip[ 7] - clip[ 4];
	frustum[0][2] = clip[11] - clip[ 8];
	frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	frustum[1][0] = clip[ 3] + clip[ 0];
	frustum[1][1] = clip[ 7] + clip[ 4];
	frustum[1][2] = clip[11] + clip[ 8];
	frustum[1][3] = clip[15] + clip[12];

	/* Normalize the result */
	t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	frustum[2][0] = clip[ 3] + clip[ 1];
	frustum[2][1] = clip[ 7] + clip[ 5];
	frustum[2][2] = clip[11] + clip[ 9];
	frustum[2][3] = clip[15] + clip[13];

	/* Normalize the result */
	t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;

	/* Extract the TOP plane */
	frustum[3][0] = clip[ 3] - clip[ 1];
	frustum[3][1] = clip[ 7] - clip[ 5];
	frustum[3][2] = clip[11] - clip[ 9];
	frustum[3][3] = clip[15] - clip[13];

	/* Normalize the result */
	t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;

	/* Extract the FAR plane */
	frustum[4][0] = clip[ 3] - clip[ 2];
	frustum[4][1] = clip[ 7] - clip[ 6];
	frustum[4][2] = clip[11] - clip[10];
	frustum[4][3] = clip[15] - clip[14];

	/* Normalize the result */
	t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;

	/* Extract the NEAR plane */
	frustum[5][0] = clip[ 3] + clip[ 2];
	frustum[5][1] = clip[ 7] + clip[ 6];
	frustum[5][2] = clip[11] + clip[10];
	frustum[5][3] = clip[15] + clip[14];

	/* Normalize the result */
	t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;
}


int CubeInFrustum( float x, float y, float z, float dx, float dy, float dz )
{
	int p;

	for( p = 0; p < 6; p++ )
	{
		if( frustum[p][0] * x + frustum[p][1]        * y + frustum[p][2]        * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * y + frustum[p][2]        * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1]        * (y + dy) + frustum[p][2] * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * (y + dy) + frustum[p][2] * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1]        * y + frustum[p][2]        * (z + dz) + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * y + frustum[p][2]        * (z + dz) + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1]        * (y + dy) + frustum[p][2] * (z + dz) + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * (x + dx) + frustum[p][1] * (y + dy) + frustum[p][2] * (z + dz) + frustum[p][3] > 0 )
			continue;
		return FALSE;
	}

	return TRUE;
}


int CubeInFrustum2( float x, float y, float z, float width, float height, float depth )
{
	int p;

	for( p = 0; p < 6; p++ )
	{
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y - height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y - height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y + height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y + height) + frustum[p][2] * (z - depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y - height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y - height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x - width) + frustum[p][1] * (y + height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	if( frustum[p][0] * (x + width) + frustum[p][1] * (y + height) + frustum[p][2] * (z + depth) + frustum[p][3] > 0 )
		continue;
	return FALSE;
	}
	return TRUE;
}