#ifndef RCTGL_FRUSTUM_H
#define RCTGL_FRUSTUM_H

#include <windows.h>
#include <math.h>

#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>

class RCTGLFrustum
{
public:
	void extractFrustum(void);
	bool isCubeInFrustum(float x, float y, float z, float dx, float dy, float dz) const;

private:
	float m_frustum[6][4];
};

#endif