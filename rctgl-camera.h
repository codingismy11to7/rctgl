class RCTGLCamera
{
public:
	void setPos(float xv, float yv, float zv);
	void setRot(float xr, float yr, float zr);	

	void setPosOffset(float xvOff, float yvOff, float zvOff);
	void setRotOffset(float xrOff, float yrOff, float zrOff);

	void getPos(float *xv, float *yv, float *zv);
	void getRot(float *xr, float *yr, float *zr);
private:
	float XR, YR, ZR;
	float XV, YV, ZV;
};