#include "rctgl-poly.h"

RCTGLPoly::RCTGLPoly(void)
{
	//clear out the lists
	m_vertexList.clear();
	m_texCoordList.clear();

	m_vertexCount = 0;
	m_texID = 0;

	m_baseRGB.r = m_baseRGB.g = m_baseRGB.b = -1;
}

void RCTGLPoly::setBaseRGB(const RCTGLRGB &baseRGB)
{
	m_baseRGB.r = baseRGB.r;
	m_baseRGB.g = baseRGB.g;
	m_baseRGB.b = baseRGB.b;
}

void RCTGLPoly::addVertex(const RCTGLVertex &inVertex)
{
	RCTGLVertex vert; // = new RCTGLVertex;
	vert.copy(inVertex);
	m_vertexList.push_back(vert);

	m_vertexCount++;
}

void RCTGLPoly::addVertex(const RCTGLVertex &inVertex, const RCTGLRGB &inColor)
{
	RCTGLVertex vert; // = new RCTGLVertex;
	vert.copy(inVertex);
	m_vertexList.push_back(vert);

	RCTGLRGB newRGB; // = new RCTGLRGB;

	newRGB.r = inColor.r;
	newRGB.g = inColor.g;
	newRGB.b = inColor.b;

	m_RGBList.push_back(newRGB);

	m_vertexCount++;
}

void RCTGLPoly::addVertex(const RCTGLVertex &inVertex, const RCTGLVertex &inTexVertex)
{
	RCTGLVertex vert; // = new RCTGLVertex;
	vert.copy(inVertex);
	m_vertexList.push_back(vert);

	RCTGLVertex newTexVert; // = new RCTGLRGB;
	newTexVert.copy(inTexVertex);	

	m_texCoordList.push_back(newTexVert);

	m_vertexCount++;
}

void RCTGLPoly::addVertex(const RCTGLVertex &inVertex, const RCTGLRGB &inColor, const RCTGLVertex &inTexVert)
{
	addVertex(inVertex, inColor);

	RCTGLVertex vert; // = new RCTGLVertex;

	vert.x = inTexVert.x;
	vert.y = inTexVert.y;
	vert.z = 0.0f;

	m_texCoordList.push_back(vert);
}

void RCTGLPoly::draw() const
{
	if(m_texID > 0)
		glBindTexture(GL_TEXTURE_2D, m_texID);

	glColor3f(m_baseRGB.r, m_baseRGB.g, m_baseRGB.b);

	glBegin(GL_QUADS);	

	if(m_texID > 0)
	{
		for(int i=0; i<m_vertexCount; i++)
		{
			glTexCoord2f(m_texCoordList[i].x, m_texCoordList[i].y);
			glVertex3f(m_vertexList[i].x, m_vertexList[i].y, m_vertexList[i].z);
		}
	}
	else
		for(int i=0; i<m_vertexCount; i++)
			glVertex3f(m_vertexList[i].x, m_vertexList[i].y, m_vertexList[i].z);
	
	glEnd();

}

void RCTGLPoly::setTextureID(unsigned int texID)
{
	m_texID = texID;
}

RCTGLPoly::~RCTGLPoly()
{			
	m_RGBList.clear();
	m_vertexList.clear();
	m_texCoordList.clear();
}
