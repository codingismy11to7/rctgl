#include "rctgl-camera.h"

void RCTGLCamera::setPos(float xv, float yv, float zv)
{
	XV = xv;
	YV = yv;
	ZV = zv;
}

void RCTGLCamera::setPosOffset(float xvOff, float yvOff, float zvOff)
{
	XV += xvOff;
	YV += yvOff;
	ZV += zvOff;
}

void RCTGLCamera::getPos(float *xv, float *yv, float *zv)
{
	*xv = XV;
	*yv = YV;
	*zv = ZV;
}