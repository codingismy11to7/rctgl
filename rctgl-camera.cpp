#include "rctgl-camera.h"

void RCTGLCamera::setPos(float xv, float yv, float zv)
{
	XV = xv;
	YV = yv;
	ZV = zv;
}

void RCTGLCamera::setRot(float xr, float yr, float zr)
{
	XR = xr;
	YR = yr;
	ZR = zr;
}

void RCTGLCamera::setPosOffset(float xvOff, float yvOff, float zvOff)
{
	XV += xvOff;
	YV += yvOff;
	ZV += zvOff;
}

void RCTGLCamera::setRotOffset(float xrOff, float yrOff, float zrOff)
{
	bool xCh = false, yCh = false, zCh = false;

	XR += xrOff;
	YR += yrOff;
	ZR += zrOff;

	if(xrOff != 0.0f)
		xCh = true;
	if(yrOff != 0.0f)
		yCh = true;
	if(zrOff != 0.0f)
		zCh = true;

	fixRot(xCh, yCh, zCh);
}

void RCTGLCamera::fixAngle(float *angle)
{
	while(*angle < 0.0f)
		*angle += 360.0f;
	while(*angle >= 360.0f)
		*angle -= 360.0f;
}

void RCTGLCamera::fixRot(bool xChanged, bool yChanged, bool zChanged)
{
	if(xChanged)
		fixAngle(&XR);
	
	if(yChanged)
		fixAngle(&YR);
	
	if(zChanged)
		fixAngle(&ZR);	
}

void RCTGLCamera::getPos(float *xv, float *yv, float *zv)
{
	*xv = XV;
	*yv = YV;
	*zv = ZV;
}

void RCTGLCamera::getRot(float *xr, float *yr, float *zr)
{
	*xr = XR;
	*yr = YR;
	*zr = ZR;
}