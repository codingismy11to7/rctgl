#include "rctgl-poly.h"

using namespace RCTPoly;

#define DRAW_WATER
//#define DRAW_WATER_TWO_PLANED

RCTGLPoly::RCTGLPoly(void)
{
	//clear out the lists
	m_vertexList.clear();
	m_texCoordList.clear();

	m_vertexCount = 0;
	m_texID = 0;

	m_polyType = POLY_NORMAL;

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
	

	if(m_texID > 0)
	{
		if(m_vertexCount == 4)
		{
#ifdef DRAW_WATER
			if(m_polyType == POLY_WATER)
			{				
				glBegin(GL_QUADS);	

				//draw bottom quad
				for(uchar i=0; i<m_vertexCount; i++)
				{
					glTexCoord2f(m_texCoordList[i].x + xWaterOffset2, m_texCoordList[i].y + zWaterOffset2);
					glVertex3f(m_vertexList[i].x, m_vertexList[i].y, m_vertexList[i].z);
				}

				glEnd();

	#ifdef DRAW_WATER_TWO_PLANED

				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST);
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);				
				

				glColor4f(m_baseRGB.r, m_baseRGB.g, m_baseRGB.b, 0.65f); //used to be 0.50f
				glBegin(GL_QUADS);
				//draw top quad
				for(i=0; i<m_vertexCount; i++)
				{
					glTexCoord2f(2.0f * (m_texCoordList[i].x + xWaterOffset1), 2.0f * (m_texCoordList[i].y + zWaterOffset1));
					glVertex3f(m_vertexList[i].x, m_vertexList[i].y, m_vertexList[i].z);
				}

				glEnd();

				glDisable(GL_BLEND);
				glBlendFunc (GL_ONE, GL_ONE);
				glEnable(GL_DEPTH_TEST);

				
				
	#endif //#ifdef DRAW_WATER_TWO_PLANED


			}
			else
	#endif //#ifdef DRAW_WATER
			{
				uchar seqList[4] = {2, 3, 1, 0};

				glBegin(GL_TRIANGLE_STRIP);

				for(int i=0; i<4; i++)
				{
					glTexCoord2f(m_texCoordList[seqList[i]].x, m_texCoordList[seqList[i]].y);
					glVertex3f(m_vertexList[seqList[i]].x, m_vertexList[seqList[i]].y, m_vertexList[seqList[i]].z);
				}		

				glEnd();
				
			}
		}
		else
		{		
			//not 4 verticies. do this the old fashioned way

			glBegin(GL_QUADS);	

			//draw bottom quad
			for(uchar i=0; i<m_vertexCount; i++)
			{
				glTexCoord2f(m_texCoordList[i].x, m_texCoordList[i].y);
				glVertex3f(m_vertexList[i].x, m_vertexList[i].y, m_vertexList[i].z);
			}

			glEnd();			
		}
	}
	else
	{
		for(int i=0; i<m_vertexCount; i++)
			glVertex3f(m_vertexList[i].x, m_vertexList[i].y, m_vertexList[i].z);

		glEnd();
	}

}

void RCTGLPoly::setTextureID(unsigned int texID)
{
	m_texID = texID;
}

void RCTGLPoly::clear()
{
	m_RGBList.clear();
	m_vertexList.clear();
	m_texCoordList.clear();

	m_vertexCount = 0;
}

RCTGLPoly::~RCTGLPoly()
{			
	m_RGBList.clear();
	m_vertexList.clear();
	m_texCoordList.clear();
}
