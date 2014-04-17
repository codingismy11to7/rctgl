#include "rctgl.h"

#include <vector>
#include "rctgl-vertex.h"
#include "rctgl-rgb.h"

using namespace std;

class RCTGLPoly
{
public:

	RCTGLPoly(void);
	void addVertex(RCTGLVertex inVertex);
	void addVertex(RCTGLVertex inVertex, RCTGLRGB inColor);
	void addVertex(RCTGLVertex inVertex, RCTGLRGB inColor, RCTGLVertex inTexVert);

	void setBaseRGB(RCTGLRGB baseRGB);

	void draw(void);

	void setTextureID(unsigned int texID);

private:
	vector<RCTGLRGB> RGBList;
	vector<RCTGLVertex> vertexList;
	vector<RCTGLVertex> texCoordList;
	unsigned char vertexCount;
	unsigned int texID;

	RCTGLRGB baseRGB;
};