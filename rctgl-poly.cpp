#include "rctgl-poly.h"

RCTGLPoly::RCTGLPoly(void)
{
	//clear out the lists
	vertexList.clear();
	texCoordList.clear();

	vertexCount = 0;
	texID = 0;

	baseRGB.r = baseRGB.g = baseRGB.b = -1;
}

void RCTGLPoly::setBaseRGB(RCTGLRGB baseRGB)
{
	this->baseRGB.r = baseRGB.r;
	this->baseRGB.g = baseRGB.g;
	this->baseRGB.b = baseRGB.b;
}

void RCTGLPoly::addVertex(RCTGLVertex inVertex)
{
	RCTGLVertex vert; // = new RCTGLVertex;
	vert.copy(inVertex);
	vertexList.push_back(vert);

	vertexCount++;
}

void RCTGLPoly::addVertex(RCTGLVertex inVertex, RCTGLRGB inColor)
{
	RCTGLVertex vert; // = new RCTGLVertex;
	vert.copy(inVertex);
	vertexList.push_back(vert);

	RCTGLRGB newRGB; // = new RCTGLRGB;

	newRGB.r = inColor.r;
	newRGB.g = inColor.g;
	newRGB.b = inColor.b;

	RGBList.push_back(newRGB);

	vertexCount++;
}

void RCTGLPoly::addVertex(RCTGLVertex inVertex, RCTGLVertex inTexVertex)
{
	RCTGLVertex vert; // = new RCTGLVertex;
	vert.copy(inVertex);
	vertexList.push_back(vert);

	RCTGLVertex newTexVert; // = new RCTGLRGB;
	newTexVert.copy(inTexVertex);	

	texCoordList.push_back(newTexVert);

	vertexCount++;
}

void RCTGLPoly::addVertex(RCTGLVertex inVertex, RCTGLRGB inColor, RCTGLVertex inTexVert)
{
	addVertex(inVertex, inColor);

	RCTGLVertex vert; // = new RCTGLVertex;

	vert.x = inTexVert.x;
	vert.y = inTexVert.y;
	vert.z = 0.0f;

	texCoordList.push_back(vert);
}

void RCTGLPoly::draw(void)
{
	if(texID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, texID);
		stringstream x;
		x << "TexID=" << (long)texID;

		//DebugLog::writeToLog(x.str());
	}
	//else	
		//DebugLog::writeToLog((string)"No Texture ID");

	glColor3f(baseRGB.r, baseRGB.g, baseRGB.b);

	glBegin(GL_QUADS);

	if(texID > 0)
	{
		for(int i=0; i<vertexCount; i++)
		{
			glTexCoord2f(texCoordList[i].x, texCoordList[i].y);
			glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z);
		}
	}
	else
		for(int i=0; i<vertexCount; i++)
			glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z);
	

	glEnd();

}

void RCTGLPoly::setTextureID(unsigned int texID)
{
	this->texID = texID;
}
