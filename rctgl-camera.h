#ifndef RCTGL_CAMERA_H
#define RCTGL_CAMERA_H

class RCTGLCamera
{
public:
	void setPos(float xv, float yv, float zv);
	void setRot(float xr, float yr, float zr);	

	void setPosOffset(float xvOff, float yvOff, float zvOff);
	void setRotOffset(float xrOff, float yrOff, float zrOff);

	void getPos(float *xv, float *yv, float *zv) const;
	void getRot(float *xr, float *yr, float *zr) const;

	float XR, YR, ZR;
	float XV, YV, ZV;

private:
	void fixRot(bool xChanged, bool yChanged, bool zChanged);
	void fixAngle(float *angle);
};

#endif