#include <stdio.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>

#include <math.h>

#define PI     3.14159265358979
#define TWOPI  6.28318530717958
#define PIDIV2 1.57079632679489

#include "skyDome.h"

int skyDome::random(int low, int high)
{
    int r = rand();
    int mapped = (((long)r * (high - low)) /RAND_MAX) + low;
    return mapped;
}

unsigned int skyDome::calcStarCoords(int size, int hollow)
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
				while( (fabs(x)<hollow)&&  // make hollow center
					(fabs(y)<hollow)&&
					(fabs(z)<hollow)) {
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

void skyDome::calcCloudDomeCoords(void)
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

			cloudDomeCoords[x][y].x = (float)((x - 4) * 100);
			cloudDomeCoords[x][y].y = (float)(sqrt(zSq));
			cloudDomeCoords[x][y].z = (float)((y - 4) * 100);

			//printf("cloud coord = %5.3f %5.3f %5.3f\n", cloudDomeCoords[x][y].x, cloudDomeCoords[x][y].y, cloudDomeCoords[x][y].z);
		}
	}
}

void skyDome::calcSkyDomeCoords(void)
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
			sphereCoords[i][j].x = (float)(tempRadius * cos(j * radiusStep));
			sphereCoords[i][j].y = (float)(tempRadius * sin(j * radiusStep));
			sphereCoords[i][j].z = (float)(tempZ);
		}
	}	
}

skyDome::skyDome(void)
{
	minute = 540;
	counter = 0;

	calcSkyDomeCoords();
	calcCloudDomeCoords();

	starfieldDisplayListA = calcStarCoords(1000, 800);
	starfieldDisplayListB = calcStarCoords(1000, 800);

	skyTexID = -1;
	cloudTexID = -1;

	lightRData[0] = 106.0f/255.0f;
	lightGData[0] = 90.0f/255.0f;
	lightBData[0] = 135.0f/255.0f;

	lightRData[1] = 182.0f/255.0f;
	lightGData[1] = 195.0f/255.0f;
	lightBData[1] = 210.0f/255.0f;

	lightRData[2] = 222.0f/255.0f;
	lightGData[2] = 249.0f/255.0f;
	lightBData[2] = 254.0f/255.0f;

	lightRData[3] = 224.0f/255.0f;
	lightGData[3] = 250.0f/255.0f;
	lightBData[3] = 255.0f/255.0f;

	lightRData[4] = 224.0f/255.0f;
	lightGData[4] = 250.0f/255.0f;
	lightBData[4] = 255.0f/255.0f;

	lightRData[5] = 224.0f/255.0f;
	lightGData[5] = 250.0f/255.0f;
	lightBData[5] = 255.0f/255.0f;

	lightRData[6] = 223.0f/255.0f;
	lightGData[6] = 249.0f/255.0f;
	lightBData[6] = 215.0f/255.0f;

	lightRData[7] = 255.0f/255.0f;
	lightGData[7] = 124.0f/255.0f;
	lightBData[7] = 38.0f/255.0f;

	lightRData[8] = 106.0f/255.0f;
	lightGData[8] = 90.0f/255.0f;
	lightBData[8] = 104.0f/255.0f;

	lightRData[9] = 51.0f/255.0f;
	lightGData[9] = 52.0f/255.0f;
	lightBData[9] = 84.0f/255.0f;

	lightRData[10] = 27.0f/255.0f;
	lightGData[10] = 44.0f/255.0f;
	lightBData[10] = 57.0f/255.0f;

	lightRData[11] = 27.0f/255.0f;
	lightGData[11] = 44.0f/255.0f;
	lightBData[11] = 57.0f/255.0f;

	lightRData[12] = 27.0f/255.0f;
	lightGData[12] = 44.0f/255.0f;
	lightBData[12] = 57.0f/255.0f;

	lightRData[13] = 27.0f/255.0f;
	lightGData[13] = 44.0f/255.0f;
	lightBData[13] = 57.0f/255.0f;

	lightRData[14] = 27.0f/255.0f;
	lightGData[14] = 44.0f/255.0f;
	lightBData[14] = 57.0f/255.0f;

	lightRData[15] = 27.0f/255.0f;
	lightGData[15] = 44.0f/255.0f;
	lightBData[15] = 57.0f/255.0f;

	lightRData[16] = 106.0f/255.0f;
	lightGData[16] = 90.0f/255.0f;
	lightBData[16] = 135.0f/255.0f;


	ambientRData[0] = 90.0f/255.0f;
	ambientGData[0] = 90.0f/255.0f;
	ambientBData[0] = 90.0f/255.0f;

	ambientRData[1] = 150.0f/255.0f;
	ambientGData[1] = 150.0f/255.0f;
	ambientBData[1] = 150.0f/255.0f;

	ambientRData[2] = 220.0f/255.0f;
	ambientGData[2] = 220.0f/255.0f;
	ambientBData[2] = 220.0f/255.0f;

	ambientRData[3] = 220.0f/255.0f;
	ambientGData[3] = 220.0f/255.0f;
	ambientBData[3] = 220.0f/255.0f;

	ambientRData[4] = 220.0f/255.0f;
	ambientGData[4] = 220.0f/255.0f;
	ambientBData[4] = 220.0f/255.0f;

	ambientRData[5] = 220.0f/255.0f;
	ambientGData[5] = 220.0f/255.0f;
	ambientBData[5] = 220.0f/255.0f;

	ambientRData[6] = 215.0f/255.0f;
	ambientGData[6] = 215.0f/255.0f;
	ambientBData[6] = 215.0f/255.0f;

	ambientRData[7] = 150.0f/255.0f;
	ambientGData[7] = 150.0f/255.0f;
	ambientBData[7] = 150.0f/255.0f;

	ambientRData[8] = 90.0f/255.0f;
	ambientGData[8] = 90.0f/255.0f;
	ambientBData[8] = 90.0f/255.0f;

	ambientRData[9] = 51.0f/255.0f;
	ambientGData[9] = 51.0f/255.0f;
	ambientBData[9] = 51.0f/255.0f;

	ambientRData[10] = 27.0f/255.0f;
	ambientGData[10] = 27.0f/255.0f;
	ambientBData[10] = 27.0f/255.0f;

	ambientRData[11] = 27.0f/255.0f;
	ambientGData[11] = 27.0f/255.0f;
	ambientBData[11] = 27.0f/255.0f;

	ambientRData[12] = 27.0f/255.0f;
	ambientGData[12] = 27.0f/255.0f;
	ambientBData[12] = 27.0f/255.0f;

	ambientRData[13] = 27.0f/255.0f;
	ambientGData[13] = 27.0f/255.0f;
	ambientBData[13] = 27.0f/255.0f;

	ambientRData[14] = 27.0f/255.0f;
	ambientGData[14] = 27.0f/255.0f;
	ambientBData[14] = 27.0f/255.0f;

	ambientRData[15] = 27.0f/255.0f;
	ambientGData[15] = 27.0f/255.0f;
	ambientBData[15] = 27.0f/255.0f;

	ambientRData[16] = 90.0f/255.0f;
	ambientGData[16] = 90.0f/255.0f;
	ambientBData[16] = 90.0f/255.0f;

}

void skyDome::setSkyTexture(unsigned int texID)
{
	skyTexID = texID;
}

void skyDome::setCloudTexture(unsigned int texID)
{
	cloudTexID = texID;
}

void skyDome::setTime(int minutes)
{
	if(minutes < 0)
		setTime(minutes + 1440);
	else if(minutes > 1440)
		setTime(minutes - 1440);
	else
		minute = minutes;
}

void skyDome::setTime(float hours)
{
	if(hours < 0)
		setTime(hours + 24.0f);
	else if(hours > 1440)
		setTime(hours - 24.0f);
	else
		minute = (int)(60.0f * hours);
}

void skyDome::getTime(int *minutes)
{
	*minutes = minute;
}

void skyDome::getTime(float *hours)
{
	*hours = minute / 60.0f;
}

void skyDome::drawSkyDome(void) const
{
	int heightSections = 16;
	int numSegments = 18;

	float zStep = (1.0f / (float)heightSections) * 0.9f;

	float alphaVals[17];

	//full daytime (full opacity) = 8 -> 16
	//full nighttime (little opacity) = 20 -> 6

	//calculate the alpha values of the sky
	if((minute / 60.0f) >= 8.0f && (minute / 60.0f) <= 16.0f)
	{
		//printf("drawing daytime\n");
		for(int i=0; i<17; i++)
			alphaVals[i] = 1.0f;
	}
	else if((minute / 60.0f) >= 20.0f || (minute / 60.0f) <= 6.0f)
	{
		//printf("drawing nighttime\n");
		alphaVals[0] = 0.99f;
		alphaVals[1] = 0.88f;
		alphaVals[2] = 0.59f;
		alphaVals[3] = 0.39f;

		for(int i=4; i<17; i++)
			alphaVals[i] = 0.19f;
	}
	else if((minute / 60.0f) > 16.0f && (minute / 60.0f) < 20.0f)
	{
		int stopVal = 17 - (((minute / 60) - 16) / 4) * 17;

		float tempA = 1.2f - (((minute / 60.0f) - 16) / 4.0f) * 0.8f;

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

		float tempA = 0.2f + (((minute / 60.0f) - 6) / 2.0f) * 0.8f;

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
	glBindTexture(GL_TEXTURE_2D, skyTexID);
	

	for(int i=1; i<=heightSections; i++)
	{
		for(int j=1; j<=numSegments; j++)
		{
						
			glBegin(GL_QUADS);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i-1]);

				glTexCoord2d(0.75f + (minute / 1440.0f), (i-1) * zStep);
				glVertex3d(sphereCoords[i-1][j-1].x, sphereCoords[i-1][j-1].y, sphereCoords[i-1][j-1].z);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i]);

				glTexCoord2d(0.75f + (minute / 1440.0f), (i) * zStep);
				glVertex3d(sphereCoords[i][j-1].x, sphereCoords[i][j-1].y, sphereCoords[i][j-1].z);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i]);

				glTexCoord2d(0.75f + (minute / 1440.0f), (i) * zStep);
				glVertex3d(sphereCoords[i][j].x, sphereCoords[i][j].y, sphereCoords[i][j].z);

				glColor4f(1.0f, 1.0f, 1.0f, alphaVals[i-1]);

				glTexCoord2d(0.75f + (minute / 1440.0f), (i-1) * zStep);
				glVertex3d(sphereCoords[i-1][j].x, sphereCoords[i-1][j].y, sphereCoords[i-1][j].z);
			glEnd();
		}
	}

	glDisable(GL_TEXTURE_2D);
	


	glPopMatrix();

}

void skyDome::drawStars(void) const
{
	glDisable(GL_TEXTURE_2D);					

	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	//draw starfields
	glPointSize(1);
	glCallList(starfieldDisplayListA);
	//glPushMatrix();
	//	glRotatef(180,0,1,0);// flip over and reuse stars at double size
		glPointSize(2);
		glCallList(starfieldDisplayListB);
	//glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void skyDome::drawClouds(void)
{
	int cloudHeight = 100;
	int cloudWidth = 500;
	int cloudWidthOuter = 750;
	int cloudHeightLower = -100;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	double r, g, b;

	getAmbientColor(&r, &g, &b);

	glBindTexture(GL_TEXTURE_2D, cloudTexID);

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
				glTexCoord2d(0.0f + (counter * 0.0005f), 0.0f + (counter * 0.001f));
				glVertex3f(cloudDomeCoords[x][y].x,     cloudDomeCoords[x][y].y,     cloudDomeCoords[x][y].z);

				glTexCoord2d(1.0f + (counter * 0.0005f), 0.0f + (counter * 0.001f));
				glVertex3f(cloudDomeCoords[x+1][y].x,   cloudDomeCoords[x+1][y].y,   cloudDomeCoords[x+1][y].z);

				glTexCoord2d(1.0f + (counter * 0.0005f), 1.0f + (counter * 0.001f));
				glVertex3f(cloudDomeCoords[x+1][y+1].x, cloudDomeCoords[x+1][y+1].y, cloudDomeCoords[x+1][y+1].z);

				glTexCoord2d(0.0f + (counter * 0.0005f), 1.0f + (counter * 0.001f));
				glVertex3f(cloudDomeCoords[x][y+1].x,   cloudDomeCoords[x][y+1].y,   cloudDomeCoords[x][y+1].z);
			glEnd();
		}
	}

	glPopMatrix();

	glDepthFunc(GL_LESS);
	
	glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);

}

void skyDome::draw(void)
{
	glEnable(GL_BLEND);
	drawStars();
	drawSkyDome();	
	drawClouds();
	glDisable(GL_BLEND);

	counter++;
	if(counter == 1000)
		counter = 0;

}

void skyDome::getLightOffset(int *intOffset, float *floatOffset)
{
	int iOff = (int)((minute / 1440.0f) * 16.0f);
	float fOff = ((minute / 1440.0f) * 16.0f) - iOff;

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

void skyDome::getAmbientColor(double *r, double *g, double *b)
{
	//recalculate ambient lighting
	int intOffset;
	float floatOffset;

	getLightOffset(&intOffset, &floatOffset);

	*r = (1.0f - floatOffset) * ambientRData[intOffset] + (floatOffset) * ambientRData[intOffset + 1];
	*g = (1.0f - floatOffset) * ambientGData[intOffset] + (floatOffset) * ambientGData[intOffset + 1];
	*b = (1.0f - floatOffset) * ambientBData[intOffset] + (floatOffset) * ambientBData[intOffset + 1];	
}

void skyDome::getLightColor(double *r, double *g, double *b)
{
	int intOffset;
	float floatOffset;

	getLightOffset(&intOffset, &floatOffset);

	*r = (1.0f - floatOffset) * lightRData[intOffset] + (floatOffset) * lightRData[intOffset + 1];
	*g = (1.0f - floatOffset) * lightGData[intOffset] + (floatOffset) * lightGData[intOffset + 1];
	*b = (1.0f - floatOffset) * lightBData[intOffset] + (floatOffset) * lightBData[intOffset + 1];	
}
