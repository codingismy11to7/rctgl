#ifndef SKYDOME_H
#define SKYDOME_H

#include "rctgl-vertex.h"

class skyDome
{
public:
	skyDome(void);
	void draw(void);
	void setTime(int minutes);
	void setTime(float hours);
	void getTime(int *minutes);
	void getTime(float *hours);
	void getAmbientColor(double *r, double *g, double *b);
	void getLightDirection(double *x, double *y, double *z);
	void getLightColor(double *r, double *g, double *b);
	void setSkyTexture(unsigned int texID);
	void setCloudTexture(unsigned int texID);

private:
	void calcSkyDomeCoords(void);
	void calcCloudDomeCoords(void);
	unsigned int calcStarCoords(int size, int hollow);
	void drawSkyDome(void) const;
	void drawStars(void) const;
	void drawClouds(void);
	int random(int low, int high);
	void getLightOffset(int *intOffset, float *floatOffset);

	int minute;

	float ambientRData[17], ambientGData[17], ambientBData[17];
	float lightRData[17], lightGData[17], lightBData[17];
	unsigned int starfieldDisplayListA;	//the small stars
	unsigned int starfieldDisplayListB;	//the bigger stars
	RCTGLVertex sphereCoords[17][19];
	RCTGLVertex cloudDomeCoords[9][9];

	unsigned int skyTexID;
	unsigned int cloudTexID;
	int counter;
};

#endif