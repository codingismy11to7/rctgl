class RCTGLFrustum
{
public:
	void extractFrustum(void);
	bool isCubeInFrustum(float x, float y, float z, float dx, float dy, float dz);

private:
	float frustum[6][4];
};