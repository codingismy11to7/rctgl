#include "rctgl-scenery.h"

using namespace RCTScenery;  //import path constants
using namespace RCTTextureManager;

//#define TEST_OPTIMIZATION

RCTGLScenerySystem::RCTGLScenerySystem()
{

}


bool RCTGLScenerySystem::loadOffset(uchar *data, uchar x, uchar z, uchar tileType)
{	
	RCTGLSceneryElement tmpScenery;

	tmpScenery.baseHeight = 0;
	tmpScenery.itemHeight = 0;
	tmpScenery.descriptor = 0;

	tmpScenery.descriptor |= tileType;

	//if item is in a quadrant, upper two bits of byte 0 are quad type
	//otherwise, upper two bits are upper two bits of color for geometric objects
	//mask with 11000000
	uchar tmp = (data[0] & 0xC0);
	tmpScenery.color = tmp;

	switch(tmp >> 6)
	{
	case 0x00:
		tmpScenery.descriptor |= SW_QUAD;
		break;
	case 0x01:
		tmpScenery.descriptor |= NW_QUAD;
		break;
	case 0x02:
		tmpScenery.descriptor |= NE_QUAD;
		break;
	case 0x03:
		tmpScenery.descriptor |= SE_QUAD;
		break;
	}	

	//lower 2 bits of byte 0 are direction item faces
	//mask with 00000011
	tmp = (data[0] & 0x03);

	switch(tmp)
	{
	case 0x00:
		tmpScenery.descriptor |= FACES_WEST;
		break;
	case 0x01:
		tmpScenery.descriptor |= FACES_NORTH;
		break;
	case 0x02:
		tmpScenery.descriptor |= FACES_EAST;
		break;
	case 0x03:
		tmpScenery.descriptor |= FACES_SOUTH;
		break;
	}
	
	
	//base height = byte 2
	tmpScenery.baseHeight = data[2] / 4;

	//item height = byte 3
	tmpScenery.itemHeight = data[3] / 4;
	
	//sometimes this value is 0
	//anyone know why?
	if(tmpScenery.itemHeight)
		tmpScenery.itemHeight -= tmpScenery.baseHeight;

	//item id = byte 4
	tmpScenery.sceneryID = data[4];

	//item index = upper 6 bits of byte 5
	tmpScenery.index = (data[4] >> 2);	

	if(isItemTree(tmpScenery.sceneryID) && ((tmpScenery.descriptor & TILE_TYPE_MASK) == SINGLE_TILE))
		tmpScenery.sceneryType = SCENERY_TREE;
	else
		tmpScenery.sceneryType = SCENERY_MODEL;

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

	//clear everything
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
					switch(m_scenItems[i][j][k].sceneryType)
					{
					case SCENERY_TREE:
					{
						//build a tree
						RCTGLExtendedPoly tmp;
						RCTGLVertex v, tex;					

						tmp.setBaseRGB(rgb);
						tmp.setTextureID(m_treeTextures[m_scenItems[i][j][k].sceneryID]);

						//draw the first surface
						//this one goes along the z plane

						
						//vert1
						v.x = UNITWIDTH * i;
						//v.y = (m_scenItems[i][j][k].baseHeight + m_scenItems[i][j][k].clearance) * UNITHEIGHT);
						v.y = (m_scenItems[i][j][k].baseHeight + m_scenItems[i][j][k].itemHeight) * UNITHEIGHT;
						v.z = UNITWIDTH * (j + 0.5f);

						tex.x = 0.0f;
						tex.y = 1.0f;

						tmp.addVertex(v, tex);

						//vert2
						v.x = UNITWIDTH * (i + 1);	

						tex.x = 1.0f;
						tex.y = 1.0f;

						tmp.addVertex(v, tex);

						//vert3						
						v.y = (m_scenItems[i][j][k].baseHeight * UNITHEIGHT);

						tex.x = 1.0f;
						tex.y = 0.0f;

						tmp.addVertex(v, tex);

						//vert4
						v.x = UNITWIDTH * i;						

						tex.x = 0.0f;
						tex.y = 0.0f;

						tmp.addVertex(v, tex);						
						
						m_scenItems[i][j][k].surfaces.push_back(tmp);
						
						//the next surface goes along the x plane
						tmp.clear();
						

						//vert1
						v.x = UNITWIDTH * (i + 0.5f);
						//v.y = (m_scenItems[i][j][k].baseHeight + m_scenItems[i][j][k].clearance) * UNITHEIGHT;
						v.y = (m_scenItems[i][j][k].baseHeight + m_scenItems[i][j][k].itemHeight) * UNITHEIGHT;
						v.z = UNITWIDTH * j;

						tex.x = 0.0f;
						tex.y = 1.0f;

						tmp.addVertex(v, tex);

						//vert2
						v.z = UNITWIDTH * (j + 1);	

						tex.x = 1.0f;
						tex.y = 1.0f;

						tmp.addVertex(v, tex);

						//vert3						
						v.y = (m_scenItems[i][j][k].baseHeight * UNITHEIGHT);

						tex.x = 1.0f;
						tex.y = 0.0f;

						tmp.addVertex(v, tex);

						//vert4
						v.z = UNITWIDTH * j;						

						tex.x = 0.0f;
						tex.y = 0.0f;

						tmp.addVertex(v, tex);
						
						m_scenItems[i][j][k].surfaces.push_back(tmp);
					}

						break;
					default:
						break;
					}

					m_scenItems[i][j][k].compiled = true;					
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
	uchar i, j, k, l;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);

	//initialize all polygons
	/*
	for(i=minX; i<maxX; i++)	
		for(j=minZ; j<maxZ; j++)
			for(k=0; k<m_scenItems[i][j].size(); k++)
				m_scenItems[i][j][k].wasDrawn = false;	
	*/	


	for(i=minX; i<maxX; i++)
	{
		for(j=minZ; j<maxZ; j++)
		{
			for(k=0; k<m_scenItems[i][j].size(); k++)
			{
				switch(m_scenItems[i][j][k].sceneryType)
				{
				case SCENERY_TREE:
					if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
						(float)(m_scenItems[i][j][k].baseHeight * UNITHEIGHT),
						(float)(j*UNITWIDTH),
						(float)(UNITWIDTH),
						(float)(m_scenItems[i][j][k].itemHeight) * UNITHEIGHT,
						(float)(UNITWIDTH)))	
					{
						for(l=0; l<m_scenItems[i][j][k].surfaces.size(); l++)
						{	
							m_scenItems[i][j][k].surfaces[l].draw();
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}

	glEnable(GL_CULL_FACE);

	glDisable(GL_ALPHA_TEST);
	
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

	m_treeTextures[0x0F] = texMan.addTexture("\\trees\\redux\\0F-1.tga", 0);

	m_treeTextures[0x11] = texMan.addTexture("\\trees\\redux\\11-1.tga", 0);
	m_treeTextures[0x12] = texMan.addTexture("\\trees\\12-1.tga", 0);
	m_treeTextures[0x13] = texMan.addTexture("\\trees\\redux\\13-1.tga", 0);
	m_treeTextures[0x14] = texMan.addTexture("\\trees\\redux\\14-1.tga", 0);

	m_treeTextures[0x16] = texMan.addTexture("\\trees\\redux\\16-1.tga", 0);

	m_treeTextures[0x18] = texMan.addTexture("\\trees\\18-1.tga", 0);
	m_treeTextures[0x19] = texMan.addTexture("\\trees\\19-1.tga", 0);
	m_treeTextures[0x1A] = texMan.addTexture("\\trees\\redux\\1A-1.tga", 0);
	m_treeTextures[0x1B] = texMan.addTexture("\\trees\\1B-1.tga", 0);

	m_treeTextures[0x1D] = texMan.addTexture("\\trees\\1D-1.tga", 0);
	m_treeTextures[0x1E] = texMan.addTexture("\\trees\\1E-1.tga", 0);
	m_treeTextures[0x1F] = texMan.addTexture("\\trees\\1F-1.tga", 0);
	m_treeTextures[0x20] = texMan.addTexture("\\trees\\20-1.tga", 0);
	m_treeTextures[0x21] = texMan.addTexture("\\trees\\21-1.tga", 0);
	m_treeTextures[0x22] = texMan.addTexture("\\trees\\22-1.tga", 0);

	m_treeTextures[0x24] = texMan.addTexture("\\trees\\24-1.tga", 0);
	m_treeTextures[0x25] = texMan.addTexture("\\trees\\redux\\25-1.tga", 0);
	m_treeTextures[0x26] = texMan.addTexture("\\trees\\redux\\26-1.tga", 0);
	m_treeTextures[0x27] = texMan.addTexture("\\trees\\redux\\27-1.tga", 0);
	m_treeTextures[0x28] = texMan.addTexture("\\trees\\redux\\28-1.tga", 0);
	m_treeTextures[0x29] = texMan.addTexture("\\trees\\redux\\29-1.tga", 0);
	m_treeTextures[0x2A] = texMan.addTexture("\\trees\\redux\\2A-1.tga", 0);

	m_treeTextures[0x34] = texMan.addTexture("\\trees\\34-1.tga", 0);

	m_treeTextures[0x36] = texMan.addTexture("\\trees\\redux\\36-1.tga", 0);
	m_treeTextures[0x37] = texMan.addTexture("\\trees\\redux\\37-1.tga", 0);

	m_treeTextures[0x66] = texMan.addTexture("\\trees\\redux\\66-1.tga", 0);

	m_treeTextures[0x77] = texMan.addTexture("\\trees\\77-1.tga", 0);

	m_treeTextures[0x80] = texMan.addTexture("\\trees\\redux\\80-1.tga", 0);
	m_treeTextures[0x81] = texMan.addTexture("\\trees\\redux\\81-1.tga", 0);
	m_treeTextures[0x82] = texMan.addTexture("\\trees\\redux\\82-1.tga", 0);
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

bool RCTGLScenerySystem::isItemTree(uchar type)
{
	for(uchar i=0; i<numTreeObjects; i++)
		if(type == treeList[i])
			return true;

	return false;
}
