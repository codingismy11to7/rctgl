#include "rctgl-path.h"

using namespace RCTPath;  //import path constants

RCTGLPathSystem::RCTGLPathSystem(void)
{

}


bool RCTGLPathSystem::loadOffset(uchar *data, uchar x, uchar z)
{	
	RCTGLPathElement tmpPath;

	tmpPath.m_pathModifier1 = 0;
	tmpPath.m_pathModifier2 = 0;
	tmpPath.m_pathExtras = 0;
	tmpPath.m_baseHeight = 0;
	tmpPath.m_pathExtensions = 0;

	//lower 2 bits of byte 0 are path qualifier
	//mask with 00000011
	uchar tmp = (data[0] & 0x03);
	tmpPath.m_pathModifier1 = tmp;

	//middle 2 bits of upper nibble of bit 1 are support type
	//mask with 01100000 and shift right
	tmp = ((data[1] & 0x60) >> 5);
	tmpPath.m_pathModifier2 = tmp;

	//base height = byte 2
	tmpPath.m_baseHeight = data[2] / 4;

	//upper nibble of byte 4 is path type
	//mask with 11110000 and shift right
	tmpPath.m_pathModifier1 |= ((data[4] & 0xF0) >> 2);

	//lower nibble of byte 4 is path slope
	//mask with 00001111
	tmp = (data[4] & 0x0F);

	switch(tmp)
	{
	case 0x00:
		tmpPath.m_pathModifier2 |= PATH_SLOPE_NONE;
		break;
	case 0x04:
		tmpPath.m_pathModifier2 |= PATH_SLOPE_WEST;
		break;
	case 0x05:
		tmpPath.m_pathModifier2 |= PATH_SLOPE_NORTH;
		break;
	case 0x06:
		tmpPath.m_pathModifier2 |= PATH_SLOPE_EAST;
		break;
	case 0x07:
		tmpPath.m_pathModifier2 |= PATH_SLOPE_SOUTH;
		break;
	}

	//if bit 3 is set, then the path is a queue entry point
	if(tmp & 0x08)
		tmpPath.m_pathModifier2 |= PATH_QUEUE_ENTRY;

	//byte 5 has additions to the path
	tmpPath.m_pathExtras = data[5];

	//byte 6 has path extensions
	tmpPath.m_pathExtensions = data[6];

	//byte 7 has edge info (extras)
	tmp = data[7];

	//upper 2 bits are for S (11000000)
	if(tmp & 0xC0)
		tmpPath.m_pathExtras |= MOD_APPLY_SOUTH;
	//next 2 bits are for E (00110000)
	if(tmp & 0x30)
		tmpPath.m_pathExtras |= MOD_APPLY_EAST;
	//next 2 bits are for N (00001100)
	if(tmp & 0x0C)
		tmpPath.m_pathExtras |= MOD_APPLY_NORTH;
	//bottom 2 bits are for W (00000011)
	if(tmp & 0x03)
		tmpPath.m_pathExtras |= MOD_APPLY_WEST;

	paths[x][z].push_back(tmpPath);

	return true;
}

void RCTGLPathSystem::compile()
{
	DebugLog::beginTask("RCTGLPathSystem::compile");

	uchar i, j, k;

	bool rotateClock, flipVert, flipHoriz;

	unsigned int actualPolys = 0, renderedPolys = 0;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			for(k=0; k<paths[i][j].size(); k++)
			{
				paths[i][j][k].surface = NULL;

				RCTGLExtendedPoly *pathPoly = new RCTGLExtendedPoly;
				
				uchar topOffset = 0, bottomOffset = 0, leftOffset = 0, rightOffset = 0;
				uchar startX, startZ, xLen, zLen;

				startX = i;
				startZ = j;

				xLen = 1;
				zLen = 1;

				float texCoord[4][2];

				texCoord[0][0] = 1.0f;
				texCoord[0][1] = 1.0f;

				texCoord[1][0] = 0.0f;
				texCoord[1][1] = 1.0f;

				texCoord[2][0] = 1.0f;
				texCoord[2][1] = 0.0f;

				texCoord[3][0] = 0.0f;
				texCoord[3][1] = 0.0f;

				if(rotateClock)
				{
					texCoord[0][0] = 1.0f;
					texCoord[0][1] = 0.0f;

					texCoord[1][0] = 1.0f;
					texCoord[1][1] = 1.0f;

					texCoord[2][0] = 0.0f;
					texCoord[2][1] = 0.0f;

					texCoord[3][0] = 0.0f;
					texCoord[3][1] = 1.0f;
				}

				if(flipVert)
				{
					if(texCoord[0][1] == 1.0f)
						texCoord[0][1] = 0.0f;
					else
						texCoord[0][1] = 1.0f;

					if(texCoord[1][1] == 1.0f)
						texCoord[1][1] = 0.0f;
					else
						texCoord[1][1] = 1.0f;

					if(texCoord[2][1] == 1.0f)
						texCoord[2][1] = 0.0f;
					else
						texCoord[2][1] = 1.0f;

					if(texCoord[3][1] == 1.0f)
						texCoord[3][1] = 0.0f;
					else
						texCoord[3][1] = 1.0f;

				}

				if(flipHoriz)
				{
					if(texCoord[0][0] == 1.0f)
						texCoord[0][0] = 0.0f;
					else
						texCoord[0][0] = 1.0f;

					if(texCoord[1][0] == 1.0f)
						texCoord[1][0] = 0.0f;
					else
						texCoord[1][0] = 1.0f;

					if(texCoord[2][0] == 1.0f)
						texCoord[2][0] = 0.0f;
					else
						texCoord[2][0] = 1.0f;

					if(texCoord[3][0] == 1.0f)
						texCoord[3][0] = 0.0f;
					else
						texCoord[3][0] = 1.0f;
				}

				RCTGLVertex v, tex;

				//TL
				v.x = startX * UNITWIDTH;
				v.y = paths[i][j][k].m_baseHeight * UNITHEIGHT + 0.1f;
				v.z = startZ * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 0.0f;
				tex.z = 0.0f;

				pathPoly->addVertex(v, tex);

				//TR
				v.x = (startX + xLen) * UNITWIDTH;
				//v.y = land[startX+(xLen-1)][startZ].BL * UNITHEIGHT;
				v.z = startZ * UNITWIDTH;

				tex.x = (float)xLen;
				tex.y = 0.0f;

				pathPoly->addVertex(v, tex);

				//BR
				v.x = (startX+ xLen) * UNITWIDTH;
				//v.y = land[startX+(xLen-1)][startZ+(zLen-1)].TL * UNITHEIGHT;
				v.z = (startZ + zLen) * UNITWIDTH;

				tex.x = (float)xLen;
				tex.y = (float)zLen;
				
				pathPoly->addVertex(v, tex);

				//BL
				v.x = startX * UNITWIDTH;
				//v.y = land[startX][startZ+(zLen-1)].TR * UNITHEIGHT;
				v.z = (startZ + zLen) * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = (float)zLen;

				pathPoly->addVertex(v, tex);

				unsigned int texID = 0;

				switch(paths[i][j][k].m_pathModifier1 & PATH_STYLE_MASK)
				{
				case PATH_STYLE_QUEUE:
					texID = queueTextures[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][0];
					break;
				case PATH_STYLE_TARMAC:
					texID = otherTextures[PATH_STYLE_TARMAC][paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][0];					
					break;
				case PATH_STYLE_DIRT:
					texID = otherTextures[PATH_STYLE_DIRT][paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][0];					
					break;
				case PATH_STYLE_CRAZY_TILE:
					texID = otherTextures[PATH_STYLE_CRAZY_TILE][paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][0];					
					break;
				case PATH_STYLE_ROAD:
					break;
				case PATH_STYLE_TILE:
					texID = otherTextures[PATH_STYLE_TILE][paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][0];					
					break;
				}				
				
				pathPoly->setTextureID(texID);
				
				pathPoly->length = 1;
				pathPoly->width = 1;

				pathPoly->setBaseRGB(rgb);

				paths[i][j][k].surface = pathPoly;

				actualPolys++;
				renderedPolys++;
			}
		}
	}

	stringstream x;
	x << "Optimized from " << actualPolys << " to " << renderedPolys << " polygons";
	DebugLog::writeToLog(x.str());

	DebugLog::endTask();
}

void RCTGLPathSystem::draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const
{
	uchar i, j, k;	

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);

	for(i=minX; i<maxX; i++)
	{
		for(j=minZ; j<maxZ; j++)
		{
			for(k=0; k<paths[i][j].size(); k++)
			{
				if(paths[i][j][k].surface)
					paths[i][j][k].surface->draw();
			}
		}
	}

	glDisable(GL_ALPHA_TEST);
}

void RCTGLPathSystem::clear()
{
	DebugLog::beginTask("RCTGLPathSystem::clear");

	for(uchar i=0; i<128; i++)
		for(uchar j=0; j<128; j++)
			paths[i][j].clear();

	DebugLog::endTask();
}

void RCTGLPathSystem::loadTextures()
{
	DebugLog::beginTask("RCTGLPathSystem::loadTextures");

	RCTGLTextureManager texMan;

	//load queue textures
	//[queue color][connection type]
	//slot 0 = no connections
	//slot 1 = N/S connection
	//slot 2 = N/E connection
	queueTextures[BLUE_QUEUE][0] = texMan.addTexture("\\paths\\00-00.tga", 0);
	queueTextures[BLUE_QUEUE][1] = texMan.addTexture("\\paths\\00-10.tga", 0);
	queueTextures[BLUE_QUEUE][2] = texMan.addTexture("\\paths\\00-06.tga", 0);

	queueTextures[RED_QUEUE][0] = texMan.addTexture("\\paths\\01-00.tga", 0);
	queueTextures[RED_QUEUE][1] = texMan.addTexture("\\paths\\01-10.tga", 0);
	queueTextures[RED_QUEUE][2] = texMan.addTexture("\\paths\\01-06.tga", 0);

	queueTextures[YELLOW_QUEUE][0] = texMan.addTexture("\\paths\\02-00.tga", 0);
	queueTextures[YELLOW_QUEUE][1] = texMan.addTexture("\\paths\\02-10.tga", 0);
	queueTextures[YELLOW_QUEUE][2] = texMan.addTexture("\\paths\\02-06.tga", 0);

	queueTextures[GREEN_QUEUE][0] = texMan.addTexture("\\paths\\03-00.tga", 0);
	queueTextures[GREEN_QUEUE][1] = texMan.addTexture("\\paths\\03-10.tga", 0);
	queueTextures[GREEN_QUEUE][2] = texMan.addTexture("\\paths\\03-06.tga", 0);

	//load road textures

	//load other textures
	//[path style][path type][connection type]
	otherTextures[PATH_STYLE_TARMAC][GRAY_TARMAC][0] = texMan.addTexture("\\paths\\04-base.tga", 0);
	otherTextures[PATH_STYLE_TARMAC][RED_TARMAC][0] = texMan.addTexture("\\paths\\05-00.tga", 0);
	otherTextures[PATH_STYLE_TARMAC][BROWN_TARMAC][0] = texMan.addTexture("\\paths\\06-base.tga", 0);
	otherTextures[PATH_STYLE_TARMAC][GREEN_TARMAC][0] = texMan.addTexture("\\paths\\07-00.tga", 0);

	otherTextures[PATH_STYLE_DIRT][BROWN_DIRT][0] = texMan.addTexture("\\paths\\0D-base.tga", 0);
	otherTextures[PATH_STYLE_DIRT][BLACK_DIRT][0] = texMan.addTexture("\\paths\\0E-base.tga", 0);

	otherTextures[PATH_STYLE_CRAZY_TILE][CRAZY_TILE][0] = texMan.addTexture("\\paths\\0C-base.tga", 0);

	otherTextures[PATH_STYLE_TILE][PLAIN_TILE][0] = texMan.addTexture("\\paths\\08-base.tga", 0);
	otherTextures[PATH_STYLE_TILE][GRAY_TILE][0] = texMan.addTexture("\\paths\\09-base.tga", 0);
	otherTextures[PATH_STYLE_TILE][RED_TILE][0] = texMan.addTexture("\\paths\\0A-base.tga", 0);
	otherTextures[PATH_STYLE_TILE][GREEN_TILE][0] = texMan.addTexture("\\paths\\0B-base.tga", 0);



	DebugLog::endTask();
}
