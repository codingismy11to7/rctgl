#ifndef SKYDOME_H
#define SKYDOME_H

#include "rctgl-vertex.h"

class skyDome
{
public:
	skyDome();
	void draw() const;
	void setTime(int minutes);
	void setTime(float hours);
	void getTime(int *minutes) const;
	void getTime(float *hours) const;
	void getAmbientColor(double *r, double *g, double *b) const;
	void getLightDirection(double *x, double *y, double *z) const;
	void getLightColor(double *r, double *g, double *b) const;
	void setSkyTexture(unsigned int texID);
	void setCloudTexture(unsigned int texID);

private:
	void calcSkyDomeCoords();
	void calcCloudDomeCoords();
	unsigned int calcStarCoords(int size, int hollow) const;
	void drawSkyDome() const;
	void drawStars() const;
	void drawClouds() const;
	int random(int low, int high) const;
	void getLightOffset(int *intOffset, float *floatOffset) const;

	int m_minute;

	float m_ambientRData[17], m_ambientGData[17], m_ambientBData[17];
	float m_lightRData[17], m_lightGData[17], m_lightBData[17];
	unsigned int m_starfieldDisplayListA;	//the small stars
	unsigned int m_starfieldDisplayListB;	//the bigger stars
	RCTGLVertex m_sphereCoords[17][19];
	RCTGLVertex m_cloudDomeCoords[9][9];

	unsigned int m_skyTexID;
	unsigned int m_cloudTexID;
	mutable int m_counter;
};

#endif