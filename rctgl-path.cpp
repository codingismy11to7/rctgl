#include "rctgl-path.h"

using namespace RCTPath;  //import path constants
using namespace RCTTextureManager;

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

bool RCTGLPathSystem::isPathTwoPronged(uchar i, uchar j, uchar k)
{
	uchar numExt = 0;

	RCTGLPathElement thePath = paths[i][j][k];

	if(thePath.m_pathExtensions & PATH_EXTEND_N)
		numExt++;
	if(thePath.m_pathExtensions & PATH_EXTEND_S)
		numExt++;
	if(thePath.m_pathExtensions & PATH_EXTEND_E)
		numExt++;
	if(thePath.m_pathExtensions & PATH_EXTEND_W)
		numExt++;

	if(numExt != 2)
		return false;

	if(thePath.m_pathExtensions & PATH_EXTEND_NW ||
		thePath.m_pathExtensions & PATH_EXTEND_NE ||
		thePath.m_pathExtensions & PATH_EXTEND_SE ||
		thePath.m_pathExtensions & PATH_EXTEND_SW)
		return false;

	return true;
}

bool RCTGLPathSystem::isPathLinear(uchar i, uchar j, uchar k)
{
	RCTGLPathElement thePath;

	thePath = paths[i][j][k];

	return ((thePath.m_pathExtensions & PATH_EXTEND_N &&
			thePath.m_pathExtensions & PATH_EXTEND_S &&
			!(thePath.m_pathExtensions & PATH_EXTEND_NW ||
			thePath.m_pathExtensions & PATH_EXTEND_NE ||
			thePath.m_pathExtensions & PATH_EXTEND_SE ||
			thePath.m_pathExtensions & PATH_EXTEND_SW))
			||
			(paths[i][j][k].m_pathExtensions & PATH_EXTEND_E &&
			paths[i][j][k].m_pathExtensions & PATH_EXTEND_W &&
			!(thePath.m_pathExtensions & PATH_EXTEND_NW ||
			thePath.m_pathExtensions & PATH_EXTEND_NE ||
			thePath.m_pathExtensions & PATH_EXTEND_SE ||
			thePath.m_pathExtensions & PATH_EXTEND_SW)));
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
				rotateClock = false;
				flipVert = false;
				flipHoriz = false;

				RCTGLExtendedPoly *pathPoly = new RCTGLExtendedPoly;
				
				uchar topOffset = 0, bottomOffset = 0, leftOffset = 0, rightOffset = 0;
				uchar startX, startZ, xLen, zLen;

				startX = i;
				startZ = j;

				xLen = 1;
				zLen = 1;

				unsigned int texID = queueTextures[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][0];

				if(paths[i][j][k].m_pathModifier1 & PATH_STYLE_MASK == PATH_STYLE_QUEUE)
				{
					texID = queueTextures[YELLOW_QUEUE][0];

					//search for the linear path
					if(isPathLinear(i, j, k))
					{
						texID = queueTextures[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][1];

						if (paths[i][j][k].m_pathExtensions & PATH_EXTEND_E &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_W)
							rotateClock = true;						
					}
					else if(isPathTwoPronged(i, j, k))
					{
						//standard for N & W
						texID = queueTextures[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK][2];

						if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_N &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_W)
						{
							//do nothing
						}						
						else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_N && paths[i][j][k].m_pathExtensions & PATH_EXTEND_E)
							flipVert = true;
						else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_S && paths[i][j][k].m_pathExtensions & PATH_EXTEND_W)
							flipHoriz = true;
						else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_S && paths[i][j][k].m_pathExtensions & PATH_EXTEND_E)
						{
							flipHoriz = true;
							flipVert = true;
						}							
					}
				}
				else
				{
					texID = otherTextures
							[paths[i][j][k].m_pathModifier1 & PATH_STYLE_MASK]
							[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK]
							[0];

					if(i >= 34)
						texID = texID;

					//linear paths, no corners
					if(isPathLinear(i, j, k))
					{
						texID = otherTextures
							[paths[i][j][k].m_pathModifier1 & PATH_STYLE_MASK]
							[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK]
							[1];

						if (paths[i][j][k].m_pathExtensions & PATH_EXTEND_E &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_W)
							rotateClock = true;						
					}
					//two pronged paths, no corners
					else if(isPathTwoPronged(i, j, k))
					{
						//standard for N & W
						texID = otherTextures
							[paths[i][j][k].m_pathModifier1 & PATH_STYLE_MASK]
							[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK]
							[2];

						if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_N &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_W)
						{
							//do nothing
						}						
						else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_N &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_E)
							flipVert = true;
						else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_S &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_W)
							flipHoriz = true;
						else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_S &&paths[i][j][k].m_pathExtensions & PATH_EXTEND_E)
						{
							flipHoriz = true;
							flipVert = true;
						}							
					}
					//full pieces
					else if(paths[i][j][k].m_pathExtensions & PATH_EXTEND_N &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_S &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_E &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_W &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_NE &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_NW &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_SW &&
						paths[i][j][k].m_pathExtensions & PATH_EXTEND_SE)
						texID = otherTextures
							[paths[i][j][k].m_pathModifier1 & PATH_STYLE_MASK]
							[paths[i][j][k].m_pathModifier1 & PATH_SUBTYPE_MASK]
							[3];
				}				


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

				//figure out which direction the path slopes
				switch(paths[i][j][k].m_pathModifier2 & PATH_SLOPE_MASK)
				{				
				case PATH_SLOPE_NORTH:
					rightOffset++;
					break;
				case PATH_SLOPE_SOUTH:
					leftOffset++;
					break;				
				case PATH_SLOPE_EAST:
					bottomOffset++;
					break;
				case PATH_SLOPE_WEST:
					topOffset++;
					break;					
				}

				//TL
				v.x = startX * UNITWIDTH;
				v.y = (paths[i][j][k].m_baseHeight + topOffset + leftOffset) * UNITHEIGHT + 0.1f;
				v.z = startZ * UNITWIDTH;

				//originally 0,0
				tex.x = texCoord[3][0] * (float)xLen;
				tex.y = texCoord[3][1] * (float)zLen;
				tex.z = 0.0f;

				pathPoly->addVertex(v, tex);

				//TR
				v.x = (startX + xLen) * UNITWIDTH;
				v.y = (paths[i][j][k].m_baseHeight + topOffset + rightOffset) * UNITHEIGHT + 0.1f;
				v.z = startZ * UNITWIDTH;

				//orginally 1,0
				tex.x = texCoord[2][0] * (float)xLen;
				tex.y = texCoord[2][1] * (float)zLen;

				pathPoly->addVertex(v, tex);

				//BR
				v.x = (startX+ xLen) * UNITWIDTH;
				v.y = (paths[i][j][k].m_baseHeight + bottomOffset + rightOffset) * UNITHEIGHT + 0.1f;
				v.z = (startZ + zLen) * UNITWIDTH;

				//originally 1,1
				tex.x = texCoord[0][0] * (float)xLen;
				tex.y = texCoord[0][1] * (float)zLen;
				
				pathPoly->addVertex(v, tex);

				//BL
				v.x = startX * UNITWIDTH;
				v.y = (paths[i][j][k].m_baseHeight + bottomOffset + leftOffset) * UNITHEIGHT + 0.1f;
				v.z = (startZ + zLen) * UNITWIDTH;

				//originally 0,1
				tex.x = texCoord[1][0] * (float)xLen;
				tex.y = texCoord[1][1] * (float)zLen;

				pathPoly->addVertex(v, tex);

							
				
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
	queueTextures[BLUE_QUEUE][1] = texMan.addTexture("\\paths\\00-06.tga", 0);
	queueTextures[BLUE_QUEUE][2] = texMan.addTexture("\\paths\\00-10.tga", 0);

	queueTextures[RED_QUEUE][0] = texMan.addTexture("\\paths\\01-00.tga", 0);
	queueTextures[RED_QUEUE][1] = texMan.addTexture("\\paths\\01-06.tga", 0);
	queueTextures[RED_QUEUE][2] = texMan.addTexture("\\paths\\01-10.tga", 0);

	queueTextures[YELLOW_QUEUE][0] = texMan.addTexture("\\paths\\02-00.tga", 0);
	queueTextures[YELLOW_QUEUE][1] = texMan.addTexture("\\paths\\02-06.tga", 0);
	queueTextures[YELLOW_QUEUE][2] = texMan.addTexture("\\paths\\02-10.tga", 0);

	queueTextures[GREEN_QUEUE][0] = texMan.addTexture("\\paths\\03-00.tga", 0);
	queueTextures[GREEN_QUEUE][1] = texMan.addTexture("\\paths\\03-06.tga", 0);
	queueTextures[GREEN_QUEUE][2] = texMan.addTexture("\\paths\\03-10.tga", 0);

	//load road textures

	uchar masks[3];

	//all sides and corners empty
	//000
	//010
	//000
	masks[0] = PATH_NORTH | PATH_SOUTH | PATH_EAST | PATH_WEST | PATH_NW | PATH_NE | PATH_SE | PATH_SW;
	//path from E->W
	//000
	//111
	//000
	masks[1] = PATH_NORTH | PATH_SOUTH | PATH_NW | PATH_NE | PATH_SE | PATH_SW;
	//path from E->N
	//010
	//110
	//000
	masks[2] = PATH_SOUTH | PATH_WEST | PATH_NW | PATH_NE | PATH_SE | PATH_SW;
	//solid piece
	//111
	//111
	//111
	masks[3] = 0;

	//load other textures
	//[path style][path type][connection type]
	otherTextures[PATH_STYLE_TARMAC][GRAY_TARMAC][0] = texMan.addTexture("\\paths\\04-base.tga", masks[0]);
	otherTextures[PATH_STYLE_TARMAC][GRAY_TARMAC][1] = texMan.addTexture("\\paths\\04-base.tga", masks[1]);
	otherTextures[PATH_STYLE_TARMAC][GRAY_TARMAC][2] = texMan.addTexture("\\paths\\04-base.tga", masks[2]);
	otherTextures[PATH_STYLE_TARMAC][GRAY_TARMAC][3] = texMan.addTexture("\\paths\\04-base.tga", masks[2]);

	otherTextures[PATH_STYLE_TARMAC][RED_TARMAC][0] = texMan.addTexture("\\paths\\05-00.tga", masks[0]);
	otherTextures[PATH_STYLE_TARMAC][RED_TARMAC][1] = texMan.addTexture("\\paths\\05-00.tga", masks[1]);
	otherTextures[PATH_STYLE_TARMAC][RED_TARMAC][2] = texMan.addTexture("\\paths\\05-00.tga", masks[2]);
	otherTextures[PATH_STYLE_TARMAC][RED_TARMAC][3] = texMan.addTexture("\\paths\\05-00.tga", masks[3]);

	otherTextures[PATH_STYLE_TARMAC][BROWN_TARMAC][0] = texMan.addTexture("\\paths\\06-base.tga", masks[0]);
	otherTextures[PATH_STYLE_TARMAC][BROWN_TARMAC][1] = texMan.addTexture("\\paths\\06-base.tga", masks[1]);
	otherTextures[PATH_STYLE_TARMAC][BROWN_TARMAC][2] = texMan.addTexture("\\paths\\06-base.tga", masks[2]);
	otherTextures[PATH_STYLE_TARMAC][BROWN_TARMAC][3] = texMan.addTexture("\\paths\\06-base.tga", masks[3]);

	otherTextures[PATH_STYLE_TARMAC][GREEN_TARMAC][0] = texMan.addTexture("\\paths\\07-00.tga", masks[0]);
	otherTextures[PATH_STYLE_TARMAC][GREEN_TARMAC][1] = texMan.addTexture("\\paths\\07-00.tga", masks[1]);
	otherTextures[PATH_STYLE_TARMAC][GREEN_TARMAC][2] = texMan.addTexture("\\paths\\07-00.tga", masks[2]);
	otherTextures[PATH_STYLE_TARMAC][GREEN_TARMAC][3] = texMan.addTexture("\\paths\\07-00.tga", masks[3]);

	otherTextures[PATH_STYLE_DIRT][BROWN_DIRT][0] = texMan.addTexture("\\paths\\0D-base.tga", masks[0]);
	otherTextures[PATH_STYLE_DIRT][BROWN_DIRT][1] = texMan.addTexture("\\paths\\0D-base.tga", masks[1]);
	otherTextures[PATH_STYLE_DIRT][BROWN_DIRT][2] = texMan.addTexture("\\paths\\0D-base.tga", masks[2]);
	otherTextures[PATH_STYLE_DIRT][BROWN_DIRT][3] = texMan.addTexture("\\paths\\0D-base.tga", masks[3]);

	otherTextures[PATH_STYLE_DIRT][BLACK_DIRT][0] = texMan.addTexture("\\paths\\0E-base.tga", masks[0]);
	otherTextures[PATH_STYLE_DIRT][BLACK_DIRT][1] = texMan.addTexture("\\paths\\0E-base.tga", masks[1]);
	otherTextures[PATH_STYLE_DIRT][BLACK_DIRT][2] = texMan.addTexture("\\paths\\0E-base.tga", masks[2]);
	otherTextures[PATH_STYLE_DIRT][BLACK_DIRT][3] = texMan.addTexture("\\paths\\0E-base.tga", masks[3]);

	otherTextures[PATH_STYLE_CRAZY_TILE][CRAZY_TILE][0] = texMan.addTexture("\\paths\\0C-base.tga", masks[0]);
	otherTextures[PATH_STYLE_CRAZY_TILE][CRAZY_TILE][1] = texMan.addTexture("\\paths\\0C-base.tga", masks[1]);
	otherTextures[PATH_STYLE_CRAZY_TILE][CRAZY_TILE][2] = texMan.addTexture("\\paths\\0C-base.tga", masks[2]);
	otherTextures[PATH_STYLE_CRAZY_TILE][CRAZY_TILE][3] = texMan.addTexture("\\paths\\0C-base.tga", masks[3]);

	otherTextures[PATH_STYLE_TILE][PLAIN_TILE][0] = texMan.addTexture("\\paths\\08-base.tga", masks[0]);
	otherTextures[PATH_STYLE_TILE][PLAIN_TILE][1] = texMan.addTexture("\\paths\\08-base.tga", masks[1]);
	otherTextures[PATH_STYLE_TILE][PLAIN_TILE][2] = texMan.addTexture("\\paths\\08-base.tga", masks[2]);
	otherTextures[PATH_STYLE_TILE][PLAIN_TILE][3] = texMan.addTexture("\\paths\\08-base.tga", masks[3]);

	otherTextures[PATH_STYLE_TILE][GRAY_TILE][0] = texMan.addTexture("\\paths\\09-base.tga", masks[0]);
	otherTextures[PATH_STYLE_TILE][GRAY_TILE][1] = texMan.addTexture("\\paths\\09-base.tga", masks[1]);
	otherTextures[PATH_STYLE_TILE][GRAY_TILE][2] = texMan.addTexture("\\paths\\09-base.tga", masks[2]);
	otherTextures[PATH_STYLE_TILE][GRAY_TILE][3] = texMan.addTexture("\\paths\\09-base.tga", masks[2]);

	otherTextures[PATH_STYLE_TILE][RED_TILE][0] = texMan.addTexture("\\paths\\0A-base.tga", masks[0]);
	otherTextures[PATH_STYLE_TILE][RED_TILE][1] = texMan.addTexture("\\paths\\0A-base.tga", masks[1]);
	otherTextures[PATH_STYLE_TILE][RED_TILE][2] = texMan.addTexture("\\paths\\0A-base.tga", masks[2]);
	otherTextures[PATH_STYLE_TILE][RED_TILE][3] = texMan.addTexture("\\paths\\0A-base.tga", masks[3]);

	otherTextures[PATH_STYLE_TILE][GREEN_TILE][0] = texMan.addTexture("\\paths\\0B-base.tga", masks[0]);
	otherTextures[PATH_STYLE_TILE][GREEN_TILE][1] = texMan.addTexture("\\paths\\0B-base.tga", masks[1]);
	otherTextures[PATH_STYLE_TILE][GREEN_TILE][2] = texMan.addTexture("\\paths\\0B-base.tga", masks[2]);
	otherTextures[PATH_STYLE_TILE][GREEN_TILE][3] = texMan.addTexture("\\paths\\0B-base.tga", masks[3]);



	DebugLog::endTask();
}
