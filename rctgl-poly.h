#ifndef RCTGL_POLY_H
#define RCTGL_POLY_H

#include "rctgl.h"

#include <vector>
#include "rctgl-vertex.h"
#include "rctgl-rgb.h"

using namespace std;

namespace RCTPoly
{
	const uchar POLY_NORMAL = 0;
	const uchar POLY_WATER  = 1;	
}

extern float xWaterOffset1, zWaterOffset1, xWaterOffset2, zWaterOffset2;

class RCTGLPoly
{
public:
	uchar m_polyType;

	RCTGLPoly(void);
	~RCTGLPoly();
	void addVertex(const RCTGLVertex &inVertex);
	void addVertex(const RCTGLVertex &inVertex, const RCTGLRGB &inColor);
	void addVertex(const RCTGLVertex &inVertex, const RCTGLVertex &inTexVertex);
	void addVertex(const RCTGLVertex &inVertex, const RCTGLRGB &inColor, const RCTGLVertex &inTexVert);

	void setBaseRGB(const RCTGLRGB &baseRGB);

	void draw() const;

	void setTextureID(unsigned int texID);

private:
	vector<RCTGLRGB> m_RGBList;
	vector<RCTGLVertex> m_vertexList;
	vector<RCTGLVertex> m_texCoordList;
	uchar m_vertexCount;
	unsigned int m_texID;

	RCTGLRGB m_baseRGB;
};

class RCTGLExtendedPoly : public RCTGLPoly
{
public:
	bool wasDrawn;
	uchar length, width;
};

#endif
