#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <math.h>

const double PI     = 3.14159265358979;
const double TWOPI  = 6.28318530717958;
const double PIDIV2 = 1.57079632679489;

#include "skyDome.h"

int skyDome::random(int low, int high) const
{
    int r = rand();
    int mapped = (((long)r * (high - low)) /RAND_MAX) + low;
    return mapped;
}

unsigned int skyDome::calcStarCoords(int size, int hollow) const
{
	int x,y,z;
	int i;
	int size2;
	GLuint gpoints;

	size2=size*2;
	gpoints=glGenLists(1);
	glNewList(gpoints,GL_COMPILE);
		glBegin(GL_POINTS);
			for(i=0; i<1000; i++) {
				x=0; y=0; z=0;
				while( (fabs((float)x)<hollow)&&  // make hollow center
					(fabs((float)y)<hollow)&&
					(fabs((float)z)<hollow)) {
					//&& x >= 0.0f) {
					x=random(0, size2) - size;
					y=random(0, size2) - size;
					z=random(0, size2) - size;					
				}

				
				if (random(0, 100)<10)
					//glColor4f(0.3f+(0.5f * random(0, 100)),0.3f+(0.5f * random(0, 100)),0.3f+(0.5f * random(0, 100)), 1.0f); // few colored
					glColor4f(0.3f+(0.5f * random(0, 100)),0.3f+(0.5f * random(0, 100)),0.3f+(0.5f * random(0, 100)), 1.0f); // few colored
				else
					//glColor4f(0.5f+(0.3f * random(0, 100)),0.5f+(0.3f * random(0, 100)),0.5f+(0.3f * random(0, 100)), 1.0f); // mostly whitish
					glColor4f(0.1f+(0.3f * random(0, 100)),0.1f+(0.3f * random(0, 100)),0.6f+(0.3f * random(0, 100)), 1.0f); // mostly bluish
					

				//glColor3f(1.0f, 1.0f, 1.0f);
				glVertex3d(x,y,z);
				
			}
		glEnd();
	glEndList();
	return gpoints;
}

void skyDome::calcCloudDomeCoords()
{
	//x^2 + y^2 + z^2 = r^2

	//z^2 = r^2 - x^2 - y^2
	int sphereRad = 1000;
	int gridWidth = 800;

	int radSq, xSq, ySq, zSq;

	radSq = sphereRad * sphereRad;

	for(int x=0; x<=8; x++)
	{
		xSq = ((x - 4) * 100) * ((x - 4) * 100);

		for(int y=0; y<=8; y++)
		{
			ySq = ((y - 4) * 100) * ((y - 4) * 100);

			zSq = radSq - xSq - ySq;

			m_cloudDomeCoords[x][y].x = (float)((x - 4) * 100);
			m_cloudDomeCoords[x][y].y = (float)(sqrt((float)zSq));
			m_cloudDomeCoords[x][y].z = (float)((y - 4) * 100);

			//printf("cloud coord = %5.3f %5.3f %5.3f\n", m_cloudDomeCoords[x][y].x, m_cloudDomeCoords[x][y].y, m_cloudDomeCoords[x][y].z);
		}
	}
}

void skyDome::calcSkyDomeCoords()
{
	int heightSections = 16;
	int numSegments = 18;

	double heightAngleStep = (PIDIV2) / (float)heightSections;
	double radiusStep = (TWOPI) / numSegments;

	int sphereRadius = 800;

	//printf("heightAngleStep: %f\n", heightAngleStep);

	//x^2 + y^2 + z^2 = rad^2

	for(int i=0; i<=heightSections; i++)
	{
		//calc the height for this ring
		double tempZ = sin(i * heightAngleStep) * sphereRadius;
		double tempRadius = cos(i * heightAngleStep) * sphereRadius;		

		//printf("tempZ: %f\n", tempZ);

		for(int j=0; j<=numSegments; j++)
		{
			m_sphereCoords[i][j].x = (float)(tempRadius * cos(j * radiusStep));
			m_sphereCoords[i][j].y = (float)(tempRadius * sin(j * radiusStep));
			m_sphereCoords[i][j].z = (float)(tempZ);
		}
	}	
}

skyDome::skyDome()
: m_minute(540), m_counter(0), m_skyTexID(-1), m_cloudTexID(-1)
{
	calcSkyDomeCoords();
	calcCloudDomeCoords();

	m_starfieldDisplayListA = calcStarCoords(1000, 800);
	m_starfieldDisplayListB = calcStarCoords(1000, 800);

	m_lightRData[0] = 106.0f/255.0f;
	m_lightGData[0] = 90.0f/255.0f;
	m_lightBData[0] = 135.0f/255.0f;

	m_lightRData[1] = 182.0f/255.0f;
	m_lightGData[1] = 195.0f/255.0f;
	m_lightBData[1] = 210.0f/255.0f;

	m_lightRData[2] = 222.0f/255.0f;
	m_lightGData[2] = 249.0f/255.0f;
	m_lightBData[2] = 254.0f/255.0f;

	m_lightRData[3] = 224.0f/255.0f;
	m_lightGData[3] = 250.0f/255.0f;
	m_lightBData[3] = 255.0f/255.0f;

	m_lightRData[4] = 224.0f/255.0f;
	m_lightGData[4] = 250.0f/255.0f;
	m_lightBData[4] = 255.0f/255.0f;

	m_lightRData[5] = 224.0f/255.0f;
	m_lightGData[5] = 250.0f/255.0f;
	m_lightBData[5] = 255.0f/255.0f;

	m_lightRData[6] = 223.0f/255.0f;
	m_lightGData[6] = 249.0f/255.0f;
	m_lightBData[6] = 215.0f/255.0f;

	m_lightRData[7] = 255.0f/255.0f;
	m_lightGData[7] = 124.0f/255.0f;
	m_lightBData[7] = 38.0f/255.0f;

	m_lightRData[8] = 106.0f/255.0f;
	m_lightGData[8] = 90.0f/255.0f;
	m_lightBData[8] = 104.0f/255.0f;

	m_lightRData[9] = 51.0f/255.0f;
	m_lightGData[9] = 52.0f/255.0f;
	m_lightBData[9] = 84.0f/255.0f;

	m_lightRData[10] = 27.0f/255.0f;
	m_lightGData[10] = 44.0f/255.0f;
	m_lightBData[10] = 57.0f/255.0f;

	m_lightRData[11] = 27.0f/255.0f;
	m_lightGData[11] = 44.0f/255.0f;
	m_lightBData[11] = 57.0f/255.0f;

	m_lightRData[12] = 27.0f/255.0f;
	m_lightGData[12] = 44.0f/255.0f;
	m_lightBData[12] = 57.0f/255.0f;

	m_lightRData[13] = 27.0f/255.0f;
	m_lightGData[13] = 44.0f/255.0f;
	m_lightBData[13] = 57.0f/255.0f;

	m_lightRData[14] = 27.0f/255.0f;
	m_lightGData[14] = 44.0f/255.0f;
	m_lightBData[14] = 57.0f/255.0f;

	m_lightRData[15] = 27.0f/255.0f;
	m_lightGData[15] = 44.0f/255.0f;
	m_lightBData[15] = 57.0f/255.0f;

	m_lightRData[16] = 106.0f/255.0f;
	m_lightGData[16] = 90.0f/255.0f;
	m_lightBData[16] = 135.0f/255.0f;


	m_ambientRData[0] = 90.0f/255.0f;
	m_ambientGData[0] = 90.0f/255.0f;
	m_ambientBData[0] = 90.0f/255.0f;

	m_ambientRData[1] = 150.0f/255.0f;
	m_ambientGData[1] = 150.0f/255.0f;
	m_ambientBData[1] = 150.0f/255.0f;

	m_ambientRData[2] = 220.0f/255.0f;
	m_ambientGData[2] = 220.0f/255.0f;
	m_ambientBData[2] = 220.0f/255.0f;

	m_ambientRData[3] = 220.0f/255.0f;
	m_ambientGData[3] = 220.0f/255.0f;
	m_ambientBData[3] = 220.0f/255.0f;

	m_ambientRData[4] = 220.0f/255.0f;
	m_ambientGData[4] = 220.0f/255.0f;
	m_ambientBData[4] = 220.0f/255.0f;

	m_ambientRData[5] = 220.0f/255.0f;
	m_ambientGData[5] = 220.0f/255.0f;
	m_ambientBData[5] = 220.0f/255.0f;

	m_ambientRData[6] = 215.0f/255.0f;
	m_ambientGData[6] = 215.0f/255.0f;
	m_ambientBData[6] = 215.0f/255.0f;

	m_ambientRData[7] = 150.0f/255.0f;
	m_ambientGData[7] = 150.0f/255.0f;
	m_ambientBData[7] = 150.0f/255.0f;

	m_ambientRData[8] = 90.0f/255.0f;
	m_ambientGData[8] = 90.0f/255.0f;
	m_ambientBData[8] = 90.0f/255.0f;

	m_ambientRData[9] = 51.0f/255.0f;
	m_ambientGData[9] = 51.0f/255.0f;
	m_ambientBData[9] = 51.0f/255.0f;

	m_ambientRData[10] = 27.0f/255.0f;
	m_ambientGData[10] = 27.0f/255.0f;
	m_ambientBData[10] = 27.0f/255.0f;

	m_ambientRData[11] = 27.0f/255.0f;
	m_ambientGData[11] = 27.0f/255.0f;
	m_ambientBData[11] = 27.0f/255.0f;

	m_ambientRData[12] = 27.0f/255.0f;
	m_ambientGData[12] = 27.0f/255.0f;
	m_ambientBData[12] = 27.0f/255.0f;

	m_ambientRData[13] = 27.0f/255.0f;
	m_ambientGData[13] = 27.0f/255.0f;
	m_ambientBData[13] = 27.0f/255.0f;

	m_ambientRData[14] = 27.0f/255.0f;
	m_ambientGData[14] = 27.0f/255.0f;
	m_ambientBData[14] = 27.0f/255.0f;

	m_ambientRData[15] = 27.0f/255.0f;
	m_ambientGData[15] = 27.0f/255.0f;
	m_ambientBData[15] = 27.0f/255.0f;

	m_ambientRData[16] = 90.0f/255.0f;
	m_ambientGData[16] = 90.0f/255.0f;
	m_ambientBData[16] = 90.0f/255.0f;

}

void skyDome::setSkyTexture(unsigned int texID)
{
	m_skyTexID = texID;
}

void skyDome::setCloudTexture(unsigned int texID)
{
	m_cloudTexID = texID;
}

void skyDome::setTime(int minutes)
{
	if(minutes < 0)
		setTime(minutes + 1440);
	else if(minutes > 1440)
		setTime(minutes - 1440);
	else
		m_minute = minutes;
}

void skyDome::setTime(float hours)
{
	if(hours < 0)
		setTime(hours + 24.0f);
	else if(hours > 1440)
		setTime(hours - 24.0f);
	else
		m_minute = (int)(60.0f * hours);
}

void skyDome::getTime(int *minutes) const
{
	*minutes = m_minute;
}

void skyDome::getTime(float *hours) const
{
	*hours = m_minute / 60.0f;
}

void skyDome::drawSkyDome() const
{
	int heightSections = 16;
	int numSegments = 18;

	float zStep = (1.0f / (float)heightSections) * 0.9f;

	float alphaVals[17];

	//full daytime (full opacity) = 8 -> 16
	//full nighttime (little opacity) = 20 -> 6

	//calculate the alpha values of the sky
	if((m_minute / 60.0f) >= 8.0f && (m_minute / 60.0f) <= 16.0f)
	{
		//printf("drawing daytime\n");
		for(int i=0; i<17; i++)
			alphaVals[i] = 1.0f;
	}
	else if((m_minute / 60.0f) >= 20.0f || (m_minute / 60.0f) <= 6.0f)
	{
		//printf("drawing nighttime\n");
		alphaVals[0] = 0.99f;
		alphaVals[1] = 0.88f;
		alphaVals[2] = 0.59f;
		alphaVals[3] = 0.39f;

		for(int i=4; i<17; i++)
			alphaVals[i] = 0.19f;
	}
	else if((m_minute / 60.0f) > 16.0f && (m_minute / 60.0f) < 20.0f)
	{
		int stopVal = 17 - (((m_minute / 60) - 16) / 4) * 17;

		float tempA = 1.2f - (((m_minute / 60.0f) - 16) / 4.0f) * 0.8f;

		//printf("drawing sunset (%d)\n", stopVal);

		if(tempA < 0.99f)
			alphaVals[0] =0.99f;
		else
			alphaVals[0] =tempA;

		if(tempA < 0.88f)
			alphaVals[1] =0.88f;
		else
			alphaVals[1] =tempA;

		if(tempA < 0.59f)
			alphaVals[2] =0.59f;
		else
			alphaVals[2] =tempA;

		if(tempA < 0.39f)
			alphaVals[3] =0.39f;
		else
			alphaVals[3] =tempA;


		for(int i=4; i<17; i++)
			alphaVals[i] = tempA;
		
		/*
		for(int i=0; i<stopVal; i++)
			alphaVals[i] = 0.99f;
		if(i < 16)
			alphaVals[i+1] = 0.88f;
		if(i<15)
			alphaVals[i+2] = 0.59f;
		if(i<14)
			alphaVals[i+3] = 0.39f;

		for(i = i+4;i<17; i++)
			alphaVals[i] = 0.19f;
			*/
	}
	else
	{
		//printf("drawing sunrise\n");

		float tempA = 0.2f + (((m_minute / 60.0f) - 6) / 2.0f) * 0.8f;

		if(tempA < 0.99f)
			alphaVals[0] =0.99f;
		else
			alphaVals[0] =tempA;

		if(tempA < 0.88f)
			alphaVals[1] =0.88f;
		else
			alphaVals[1] =tempA;

		if(tempA < 0.59f)
			alphaVals[2] =0.59f;
		else
			alphaVals[2] =tempA;

		if(tempA < 0.39f)
			alphaVals[3] =0.39f;
		else
			alphaVals[3] =tempA;


		for(int i=4; i<17; i++)
			alphaVals[i] = tempA;

	}


	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, -100.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, m_skyTexID);
	

	for(int i=1; i<=heightSections; i++)
	{
		for(int j=1; j<=numSegments; j++)
		{
						
			glBegin(GL_QUADS);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i-1]);

				glTexCoord2d(0.75f + (m_minute / 1440.0f), (i-1) * zStep);
				glVertex3d(m_sphereCoords[i-1][j-1].x, m_sphereCoords[i-1][j-1].y, m_sphereCoords[i-1][j-1].z);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i]);

				glTexCoord2d(0.75f + (m_minute / 1440.0f), (i) * zStep);
				glVertex3d(m_sphereCoords[i][j-1].x, m_sphereCoords[i][j-1].y, m_sphereCoords[i][j-1].z);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i]);

				glTexCoord2d(0.75f + (m_minute / 1440.0f), (i) * zStep);
				glVertex3d(m_sphereCoords[i][j].x, m_sphereCoords[i][j].y, m_sphereCoords[i][j].z);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i-1]);

				glTexCoord2d(0.75f + (m_minute / 1440.0f), (i-1) * zStep);
				glVertex3d(m_sphereCoords[i-1][j].x, m_sphereCoords[i-1][j].y, m_sphereCoords[i-1][j].z);
			glEnd();
		}
	}

	glDisable(GL_TEXTURE_2D);
	


	glPopMatrix();

}

void skyDome::drawStars() const
{
	glDisable(GL_TEXTURE_2D);					

	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	//draw starfields
	glPointSize(1);
	glCallList(m_starfieldDisplayListA);
	//glPushMatrix();
	//	glRotatef(180,0,1,0);// flip over and reuse stars at double size
		glPointSize(2);
		glCallList(m_starfieldDisplayListB);
	//glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void skyDome::drawClouds() const
{
	int cloudHeight = 100;
	int cloudWidth = 500;
	int cloudWidthOuter = 750;
	int cloudHeightLower = -100;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	double r, g, b;

	getAmbientColor(&r, &g, &b);

	glBindTexture(GL_TEXTURE_2D, m_cloudTexID);

	glDepthFunc(GL_ZERO);

	glColor3d(r, g, b);

	glPushMatrix();

	glTranslatef(0.0f, -950.0f, 0.0f);
	//glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	//glTranslatef(0.0f, 0.0f, -2500.0f);

	for (int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			glBegin(GL_QUADS);
				glTexCoord2d(0.0f + (m_counter * 0.0005f), 0.0f + (m_counter * 0.001f));
				glVertex3f(m_cloudDomeCoords[x][y].x,     m_cloudDomeCoords[x][y].y,     m_cloudDomeCoords[x][y].z);

				glTexCoord2d(1.0f + (m_counter * 0.0005f), 0.0f + (m_counter * 0.001f));
				glVertex3f(m_cloudDomeCoords[x+1][y].x,   m_cloudDomeCoords[x+1][y].y,   m_cloudDomeCoords[x+1][y].z);

				glTexCoord2d(1.0f + (m_counter * 0.0005f), 1.0f + (m_counter * 0.001f));
				glVertex3f(m_cloudDomeCoords[x+1][y+1].x, m_cloudDomeCoords[x+1][y+1].y, m_cloudDomeCoords[x+1][y+1].z);

				glTexCoord2d(0.0f + (m_counter * 0.0005f), 1.0f + (m_counter * 0.001f));
				glVertex3f(m_cloudDomeCoords[x][y+1].x,   m_cloudDomeCoords[x][y+1].y,   m_cloudDomeCoords[x][y+1].z);
			glEnd();
		}
	}

	glPopMatrix();

	glDepthFunc(GL_LESS);
	
	glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);

}

void skyDome::draw() const
{
	glEnable(GL_BLEND);
	drawStars();
	drawSkyDome();	
	drawClouds();
	glDisable(GL_BLEND);

	m_counter++;
	if(m_counter == 1000)
		m_counter = 0;

}

void skyDome::getLightOffset(int *intOffset, float *floatOffset) const
{
	int iOff = (int)((m_minute / 1440.0f) * 16.0f);
	float fOff = ((m_minute / 1440.0f) * 16.0f) - iOff;

	iOff -=4;
	fOff -= 0.5f;

	if(fOff < 0)
	{
		fOff += 1.0f;
		iOff -= 1;
	}

	if(iOff < 0)
		iOff += 16;

	*intOffset = iOff;
	*floatOffset = fOff;
}

void skyDome::getAmbientColor(double *r, double *g, double *b) const
{
	//recalculate ambient lighting
	int intOffset;
	float floatOffset;

	getLightOffset(&intOffset, &floatOffset);

	*r = (1.0f - floatOffset) * m_ambientRData[intOffset] + (floatOffset) * m_ambientRData[intOffset + 1];
	*g = (1.0f - floatOffset) * m_ambientGData[intOffset] + (floatOffset) * m_ambientGData[intOffset + 1];
	*b = (1.0f - floatOffset) * m_ambientBData[intOffset] + (floatOffset) * m_ambientBData[intOffset + 1];	
}

void skyDome::getLightColor(double *r, double *g, double *b) const
{
	int intOffset;
	float floatOffset;

	getLightOffset(&intOffset, &floatOffset);

	*r = (1.0f - floatOffset) * m_lightRData[intOffset] + (floatOffset) * m_lightRData[intOffset + 1];
	*g = (1.0f - floatOffset) * m_lightGData[intOffset] + (floatOffset) * m_lightGData[intOffset + 1];
	*b = (1.0f - floatOffset) * m_lightBData[intOffset] + (floatOffset) * m_lightBData[intOffset + 1];	
}
