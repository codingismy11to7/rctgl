#include "rctgl-scenery.h"

using namespace RCTScenery;  //import path constants
using namespace RCTTextureManager;

//#define TEST_OPTIMIZATION

RCTGLScenerySystem::RCTGLScenerySystem()
{

}


bool RCTGLScenerySystem::loadOffset(uchar *data, uchar x, uchar z)
{	
	RCTGLSceneryElement tmpScenery;	

	//if item is in a quadrant, upper two bits of byte 0 are quad type
	//otherwise, upper two bits are upper two bits of color for geometric objects
	//mask with 11000000
	uchar tmp = (data[0] & 0xC0);
	tmpScenery.color = tmp;
	tmpScenery.baseQuad = (tmp >> 6);

	//lower 2 bits of byte 0 are direction item faces
	//mask with 00000011
	tmp = (data[0] & 0x03);
	tmpScenery.faceDirection = tmp;	
	
	//base height = byte 2
	tmpScenery.baseHeight = data[2] / 4;

	//item height = byte 3
	tmpScenery.clearance = data[3] / 4;

	//item id = byte 4
	tmpScenery.sceneryID = data[4];

	//item index = upper 6 bits of byte 5
	tmpScenery.index = (data[4] >> 2);	

	m_scenItems[x][z].push_back(tmpScenery);

	return true;
}

void RCTGLScenerySystem::compile()
{
	DebugLog::beginTask("RCTGLPathSystem::compile");

	uchar i, j, k;	

	unsigned int actualPolys = 0, renderedPolys = 0;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	for(i=0; i<128; i++)	
		for(j=0; j<128; j++)		
			for(k=0; k<m_scenItems[i][j].size(); k++)
				m_scenItems[i][j][k].compiled = false;

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			for(k=0; k<m_scenItems[i][j].size(); k++)
			{
				if(!m_scenItems[i][j][k].compiled)
				{
				}
			}
		}
	}

	stringstream x;
	x << "actualPolys: " << actualPolys;
	DebugLog::writeToLog(x.str());

	DebugLog::endTask();
}

void RCTGLScenerySystem::draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const
{
	/*
	uchar i, j, k;	

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);

#ifdef TEST_OPTIMIZATION
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

	//initialize all polygons
	for(i=minX; i<maxX; i++)	
		for(j=minZ; j<maxZ; j++)
			for(k=0; k<paths[i][j].size(); k++)
				paths[i][j][k].surface->wasDrawn = false;	
	


	for(i=minX; i<maxX; i++)
	{
		for(j=minZ; j<maxZ; j++)
		{
			for(k=0; k<paths[i][j].size(); k++)
			{
				if(paths[i][j][k].surface)
				{
					if(!paths[i][j][k].surface->wasDrawn)
					{
						paths[i][j][k].surface->draw();
						paths[i][j][k].surface->wasDrawn = true;
					}
				}
			}
		}
	}

#ifdef TEST_OPTIMIZATION
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

	glDisable(GL_ALPHA_TEST);
	*/
}

void RCTGLScenerySystem::clear()
{
	DebugLog::beginTask("RCTGLScenerySystem::clear");

	for(uchar i=0; i<128; i++)
		for(uchar j=0; j<128; j++)
			m_scenItems[i][j].clear();

	DebugLog::endTask();
}

void RCTGLScenerySystem::loadTreeTextures()
{
	RCTGLTextureManager texMan;

	DebugLog::beginTask("RCTGLScenerySystem::loadTreeTextures");

	m_treeTextures[0x00] = texMan.addTexture("\\trees\\00-1.tga", 0);
	m_treeTextures[0x01] = texMan.addTexture("\\trees\\01-1.tga", 0);
	m_treeTextures[0x02] = texMan.addTexture("\\trees\\02-1.tga", 0);
	m_treeTextures[0x03] = texMan.addTexture("\\trees\\03-1.tga", 0);
	m_treeTextures[0x04] = texMan.addTexture("\\trees\\04-1.tga", 0);
	m_treeTextures[0x05] = texMan.addTexture("\\trees\\05-1.tga", 0);
	m_treeTextures[0x06] = texMan.addTexture("\\trees\\06-1.tga", 0);
	m_treeTextures[0x07] = texMan.addTexture("\\trees\\07-1.tga", 0);

	m_treeTextures[0x0F] = texMan.addTexture("\\trees\\0F-1.tga", 0);

	m_treeTextures[0x11] = texMan.addTexture("\\trees\\11-1.tga", 0);
	m_treeTextures[0x12] = texMan.addTexture("\\trees\\12-1.tga", 0);
	m_treeTextures[0x13] = texMan.addTexture("\\trees\\13-1.tga", 0);
	m_treeTextures[0x14] = texMan.addTexture("\\trees\\14-1.tga", 0);

	m_treeTextures[0x18] = texMan.addTexture("\\trees\\18-1.tga", 0);
	m_treeTextures[0x19] = texMan.addTexture("\\trees\\19-1.tga", 0);
	m_treeTextures[0x1A] = texMan.addTexture("\\trees\\1A-1.tga", 0);
	m_treeTextures[0x1B] = texMan.addTexture("\\trees\\1B-1.tga", 0);

	m_treeTextures[0x1D] = texMan.addTexture("\\trees\\1D-1.tga", 0);
	m_treeTextures[0x1E] = texMan.addTexture("\\trees\\1E-1.tga", 0);
	m_treeTextures[0x1F] = texMan.addTexture("\\trees\\1F-1.tga", 0);
	m_treeTextures[0x20] = texMan.addTexture("\\trees\\20-1.tga", 0);
	m_treeTextures[0x21] = texMan.addTexture("\\trees\\21-1.tga", 0);
	m_treeTextures[0x22] = texMan.addTexture("\\trees\\22-1.tga", 0);

	m_treeTextures[0x24] = texMan.addTexture("\\trees\\24-1.tga", 0);
	m_treeTextures[0x25] = texMan.addTexture("\\trees\\25-1.tga", 0);
	m_treeTextures[0x26] = texMan.addTexture("\\trees\\26-1.tga", 0);
	m_treeTextures[0x27] = texMan.addTexture("\\trees\\27-1.tga", 0);
	m_treeTextures[0x28] = texMan.addTexture("\\trees\\28-1.tga", 0);
	m_treeTextures[0x29] = texMan.addTexture("\\trees\\29-1.tga", 0);
	m_treeTextures[0x2A] = texMan.addTexture("\\trees\\2A-1.tga", 0);

	m_treeTextures[0x34] = texMan.addTexture("\\trees\\34-1.tga", 0);

	m_treeTextures[0x36] = texMan.addTexture("\\trees\\36-1.tga", 0);
	m_treeTextures[0x37] = texMan.addTexture("\\trees\\37-1.tga", 0);

	m_treeTextures[0x66] = texMan.addTexture("\\trees\\66-1.tga", 0);

	m_treeTextures[0x77] = texMan.addTexture("\\trees\\77-1.tga", 0);

	m_treeTextures[0x80] = texMan.addTexture("\\trees\\80-1.tga", 0);
	m_treeTextures[0x81] = texMan.addTexture("\\trees\\81-1.tga", 0);
	m_treeTextures[0x82] = texMan.addTexture("\\trees\\82-1.tga", 0);
	m_treeTextures[0x83] = texMan.addTexture("\\trees\\83-1.tga", 0);
	m_treeTextures[0x84] = texMan.addTexture("\\trees\\84-1.tga", 0);

	DebugLog::endTask();
}

void RCTGLScenerySystem::loadFlowerTextures()
{
	RCTGLTextureManager texMan;

	DebugLog::beginTask("RCTGLScenerySystem::loadFlowerTextures");
	DebugLog::endTask();
}

void RCTGLScenerySystem::loadTextures()
{
	DebugLog::beginTask("RCTGLScenerySystem::loadTextures");

	loadTreeTextures();
	loadFlowerTextures();

	DebugLog::endTask();
}
