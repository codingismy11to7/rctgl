#include "rctgl-path.h"

using namespace RCTPath;  //import path constants
using namespace RCTTextureManager;

RCTGLPathSystem::RCTGLPathSystem()
{

}


bool RCTGLPathSystem::loadOffset(uchar *data, uchar x, uchar z)
{	
	RCTGLPathElement tmpPath;

	tmpPath.pathModifier1 = 0;
	tmpPath.pathModifier2 = 0;
	tmpPath.pathExtras = 0;
	tmpPath.baseHeight = 0;
	tmpPath.pathExtensions = 0;

	//lower 2 bits of byte 0 are path qualifier
	//mask with 00000011
	uchar tmp = (data[0] & 0x03);
	tmpPath.pathModifier1 = tmp;

	//middle 2 bits of upper nibble of bit 1 are support type
	//mask with 01100000 and shift right
	tmp = ((data[1] & 0x60) >> 5);
	tmpPath.pathModifier2 = tmp;

	//base height = byte 2
	tmpPath.baseHeight = data[2] / 4;

	//upper nibble of byte 4 is path type
	//mask with 11110000 and shift right
	tmpPath.pathModifier1 |= ((data[4] & 0xF0) >> 2);

	//lower nibble of byte 4 is path slope
	//mask with 00001111
	tmp = (data[4] & 0x0F);

	switch(tmp)
	{
	case 0x00:
		tmpPath.pathModifier2 |= PATH_SLOPE_NONE;
		break;
	case 0x04:
		tmpPath.pathModifier2 |= PATH_SLOPE_WEST;
		break;
	case 0x05:
		tmpPath.pathModifier2 |= PATH_SLOPE_NORTH;
		break;
	case 0x06:
		tmpPath.pathModifier2 |= PATH_SLOPE_EAST;
		break;
	case 0x07:
		tmpPath.pathModifier2 |= PATH_SLOPE_SOUTH;
		break;
	}

	//if bit 3 is set, then the path is a queue entry point
	if(tmp & 0x08)
		tmpPath.pathModifier2 |= PATH_QUEUE_ENTRY;

	//byte 5 has additions to the path
	tmpPath.pathExtras = data[5];

	//byte 6 has path extensions
	tmpPath.pathExtensions = data[6];

	//byte 7 has edge info (extras)
	tmp = data[7];

	//upper 2 bits are for S (11000000)
	if(tmp & 0xC0)
		tmpPath.pathExtras |= MOD_APPLY_SOUTH;
	//next 2 bits are for E (00110000)
	if(tmp & 0x30)
		tmpPath.pathExtras |= MOD_APPLY_EAST;
	//next 2 bits are for N (00001100)
	if(tmp & 0x0C)
		tmpPath.pathExtras |= MOD_APPLY_NORTH;
	//bottom 2 bits are for W (00000011)
	if(tmp & 0x03)
		tmpPath.pathExtras |= MOD_APPLY_WEST;

	paths[x][z].push_back(tmpPath);

	return true;
}

uchar RCTGLPathSystem::numCardinals(uchar i, uchar j, uchar k) const
{
	RCTGLPathElement thePath = paths[i][j][k];

	uchar numExt = 0;

	if(thePath.pathExtensions & PATH_EXTEND_N)
		numExt++;
	if(thePath.pathExtensions & PATH_EXTEND_S)
		numExt++;
	if(thePath.pathExtensions & PATH_EXTEND_E)
		numExt++;
	if(thePath.pathExtensions & PATH_EXTEND_W)
		numExt++;

	return numExt;
}

uchar RCTGLPathSystem::numDiagonals(uchar i, uchar j, uchar k) const
{
	RCTGLPathElement thePath = paths[i][j][k];

	uchar numExt = 0;

	if(thePath.pathExtensions & PATH_EXTEND_NE)
		numExt++;
	if(thePath.pathExtensions & PATH_EXTEND_NW)
		numExt++;
	if(thePath.pathExtensions & PATH_EXTEND_SE)
		numExt++;
	if(thePath.pathExtensions & PATH_EXTEND_SW)
		numExt++;

	return numExt;
}

bool RCTGLPathSystem::isPathTwoPronged(uchar i, uchar j, uchar k) const
{
	if(numCardinals(i, j, k) == 2 && numDiagonals(i, j, k) == 0)
		return true;
	else
		return false;
}

bool RCTGLPathSystem::isPathLinear(uchar i, uchar j, uchar k) const
{
	RCTGLPathElement thePath;

	thePath = paths[i][j][k];

	if(numCardinals(i, j, k) > 2 || numDiagonals(i, j, k) > 0)
		return false;

	return ((thePath.pathExtensions & PATH_EXTEND_N &&
			thePath.pathExtensions & PATH_EXTEND_S)
			||
			(thePath.pathExtensions & PATH_EXTEND_E &&
			thePath.pathExtensions & PATH_EXTEND_W));
}

bool RCTGLPathSystem::isPathSame(uchar x1, uchar z1, uchar idx1, uchar x2, uchar z2, uchar idx2) const
{
	switch((paths[x2][z2][idx2].pathModifier2 & PATH_SLOPE_MASK))
	{
	case PATH_SLOPE_NONE:
		return (paths[x1][z1][idx1].baseHeight								== paths[x2][z2][idx2].baseHeight) &&
			(paths[x1][z1][idx1].pathExtensions							== paths[x2][z2][idx2].pathExtensions) &&
			(paths[x1][z1][idx1].baseHeight								== paths[x2][z2][idx2].baseHeight) &&
			((paths[x1][z1][idx1].pathModifier1 & PATH_STYLE_MASK)		== (paths[x2][z2][idx2].pathModifier1 & PATH_STYLE_MASK)) &&
			((paths[x1][z1][idx1].pathModifier1 & PATH_SUBTYPE_MASK)	== (paths[x2][z2][idx2].pathModifier1 & PATH_SUBTYPE_MASK)) &&
			((paths[x1][z1][idx1].pathModifier2 & PATH_SLOPE_MASK)		== ((paths[x2][z2][idx2].pathModifier2 & PATH_SLOPE_MASK)));
	case PATH_SLOPE_NORTH:
	case PATH_SLOPE_SOUTH:
	case PATH_SLOPE_EAST:
	case PATH_SLOPE_WEST:
	default:
		return false;
	}
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
		for(j=0; j<128; j++)		
			for(k=0; k<paths[i][j].size(); k++)
				paths[i][j][k].compiled = false;

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			for(k=0; k<paths[i][j].size(); k++)
			{
				if(!paths[i][j][k].compiled)
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

					//find out what kind of path we have
					unsigned int texID = m_queueTextures[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK][0];
					//unsigned int texID = m_otherTextures[PATH_STYLE_TARMAC >> 2][GRAY_TARMAC][6];

					
					if((paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) == PATH_STYLE_QUEUE)
					{
						texID = m_queueTextures[YELLOW_QUEUE][0];

						//search for the linear path
						if(isPathLinear(i, j, k))
						{
							texID = m_queueTextures[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK][1];

							if (paths[i][j][k].pathExtensions & PATH_EXTEND_E &&paths[i][j][k].pathExtensions & PATH_EXTEND_W)
								rotateClock = true;						
						}
						else if(isPathTwoPronged(i, j, k))
						{
							//standard for N & W
							texID = m_queueTextures[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK][2];

							if(paths[i][j][k].pathExtensions & PATH_EXTEND_N &&paths[i][j][k].pathExtensions & PATH_EXTEND_W)
							{
								//do nothing
							}						
							else if(paths[i][j][k].pathExtensions & PATH_EXTEND_N && paths[i][j][k].pathExtensions & PATH_EXTEND_E)
								flipVert = true;
							else if(paths[i][j][k].pathExtensions & PATH_EXTEND_S && paths[i][j][k].pathExtensions & PATH_EXTEND_W)
								flipHoriz = true;
							else if(paths[i][j][k].pathExtensions & PATH_EXTEND_S && paths[i][j][k].pathExtensions & PATH_EXTEND_E)
							{
								flipHoriz = true;
								flipVert = true;
							}							
						}
					}
					else
					{
						texID = m_otherTextures
								[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
								[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
								[0];

						if(numDiagonals(i, j, k) == 0)
						{
							//linear paths, no corners
							if(isPathLinear(i, j, k))
							{
								texID = m_otherTextures
									[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
									[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
									[1];

								if (paths[i][j][k].pathExtensions & PATH_EXTEND_E &&paths[i][j][k].pathExtensions & PATH_EXTEND_W)
									rotateClock = true;						
							}
							//two pronged paths, no corners
							else if(numCardinals(i, j, k) == 2)
							{
								//standard for N & W
								texID = m_otherTextures
									[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
									[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
									[2];

								if(paths[i][j][k].pathExtensions & PATH_EXTEND_N &&paths[i][j][k].pathExtensions & PATH_EXTEND_W)
								{
									//do nothing
								}						
								else if(paths[i][j][k].pathExtensions & PATH_EXTEND_N &&paths[i][j][k].pathExtensions & PATH_EXTEND_E)
									flipVert = true;
								else if(paths[i][j][k].pathExtensions & PATH_EXTEND_S &&paths[i][j][k].pathExtensions & PATH_EXTEND_W)
									flipHoriz = true;
								else if(paths[i][j][k].pathExtensions & PATH_EXTEND_S &&paths[i][j][k].pathExtensions & PATH_EXTEND_E)
								{
									flipHoriz = true;
									flipVert = true;
								}							
							}
							else if(numCardinals(i, j, k) == 3)
							{
								texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[3];

								if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_S))
									rotateClock = true;
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_N))
								{
									rotateClock = true;
									flipVert = true;
								}
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
								
								}
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_W))
									flipVert = true;
							}
							else if(numCardinals(i, j, k) == 4)
							{
								texID = m_otherTextures
									[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
									[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
									[5];
							}
							else if(numCardinals(i, j, k) == 1)
							{
								texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[4];

								if((paths[i][j][k].pathExtensions & PATH_EXTEND_S))
									rotateClock = true;
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_N))
								{
									rotateClock = true;
									flipVert = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
								
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_W))
									flipVert = true;
							}
							//we should never get to this point

						}
						else
						{
							//full pieces
							if(numCardinals(i, j, k) == 4 &&
								numDiagonals(i, j, k) == 4)
								texID = m_otherTextures
									[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
									[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
									[6];
							//half of a path
							else if(numCardinals(i, j, k) == 3 &&
								numDiagonals(i, j, k) ==2)
							{
								if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_NE) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_NW))
								{
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[7];
									rotateClock = true;
								}
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_SE) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_SW))
								{
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[7];
									rotateClock = true;
									flipVert = true;
								}
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_SW) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_NW))
								{
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[7];
									//rotateClock = true;
									//flipVert = true;
								}
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_E) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_SE) &&
									!(paths[i][j][k].pathExtensions & PATH_EXTEND_NE))
								{
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[7];
									//rotateClock = true;
									flipVert = true;
								}							
							}
							//one corner notched out
							else if(numCardinals(i, j, k) == 4 &&
								numDiagonals(i, j, k) == 3)
							{
								texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[8];

								if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_NE))
								{
								}
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_SE))
									flipHoriz = true;
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_NW))
									flipVert = true;
								else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_SW))
								{
									flipHoriz = true;
									flipVert = true;
								}
							}
							//an extended corner (2, 1)
							else if(numCardinals(i, j, k) == 2 &&
								numDiagonals(i, j, k) == 1)
							{
								texID = m_otherTextures
									[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
									[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
									[9];

								if((paths[i][j][k].pathExtensions & PATH_EXTEND_E) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_SE))
									flipHoriz = true;

								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_SW))
								{
									flipHoriz = true;
									flipVert = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_NW))
									flipVert = true;
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_E) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_NE))
								{
								}
							}
							//opposite corners and big T pieces
							else if(numCardinals(i, j, k) == 4 &&
								numDiagonals(i, j, k) == 2)
							{
								
								if((paths[i][j][k].pathExtensions & PATH_EXTEND_NE) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_SW))
								{
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[11];
									//flipHoriz = true;

								}							
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_NW) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_SE))
								{
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[11];
									flipHoriz = true;
								}
								else
								{								
									texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[10];
										
									if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_NE) &&
										!(paths[i][j][k].pathExtensions & PATH_EXTEND_NW))
										rotateClock = true;
									else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_SE) &&
										!(paths[i][j][k].pathExtensions & PATH_EXTEND_SW))
									{
										rotateClock = true;
										flipVert = true;
									}
									else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_SE) &&
										!(paths[i][j][k].pathExtensions & PATH_EXTEND_NE))
										flipVert = true;
									else if(!(paths[i][j][k].pathExtensions & PATH_EXTEND_SW) &&
										!(paths[i][j][k].pathExtensions & PATH_EXTEND_NW))
									{
									}
								}
							}
							//T with a diagonal piece
							else if(numCardinals(i, j, k) == 3 &&
								numDiagonals(i, j, k) == 1)
							{
								texID = m_otherTextures
										[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
										[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
										[12];

								if((paths[i][j][k].pathExtensions & PATH_EXTEND_SW) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{								
									rotateClock = true;
									flipVert = true;
									flipHoriz = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_SE) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
									rotateClock = true;
									flipVert = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_NE) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
									rotateClock = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_NW) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_W) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
									rotateClock = true;
									flipHoriz = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_NE) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
									flipVert = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_SE) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_E))
								{
									flipHoriz = true;
									flipVert = true;
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_NW) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_W))
								{
								}
								else if((paths[i][j][k].pathExtensions & PATH_EXTEND_SW) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_N) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_S) &&
									(paths[i][j][k].pathExtensions & PATH_EXTEND_W))
								{
									flipHoriz = true;
								}
							}
							else if(numCardinals(i, j, k) == 4 &&
								numDiagonals(i, j, k) == 1)
							{
								texID = m_otherTextures
									[(paths[i][j][k].pathModifier1 & PATH_STYLE_MASK) >> 2]
									[paths[i][j][k].pathModifier1 & PATH_SUBTYPE_MASK]
									[13];

								if(paths[i][j][k].pathExtensions & PATH_EXTEND_NE)
									flipVert = true;
								else if(paths[i][j][k].pathExtensions & PATH_EXTEND_NW)
								{
								}
								else if(paths[i][j][k].pathExtensions & PATH_EXTEND_SW)
									flipHoriz = true;
								else if(paths[i][j][k].pathExtensions & PATH_EXTEND_SE)
								{
									flipVert = true;
									flipHoriz = true;
								}
							}
						}					
					}
					


					//see how far this piece stretches
					//currently, this will only support flat land and only go in one dimension
					bool canContinue = true;
					uchar saveOffset = 255;
					
					while(canContinue)
					{
						canContinue = false;

						//loop through all of the entries in the next section
						for(uchar l=0; l<paths[i][j + zLen].size(); l++)
						{
							if(isPathSame(i, j, k, i, j + zLen, l))
							{
								canContinue = true;
								saveOffset = l;
							}

							if(canContinue)
							{
								//assign the path to this pointer
								paths[i][j + zLen][saveOffset].surface = pathPoly;

								//mark the path as compiled
								paths[i][j + zLen][saveOffset].compiled = true;

								zLen++;
							}
						}
					}

					vector <uchar> offsets;

					//now expand in the other direction
					bool goodLoop = true;
					while(goodLoop)
					{
						goodLoop = true;
						offsets.clear();

						//loop through all entries in a row
						for(uchar off=0; off<zLen; off++)
						{
							canContinue = false;

							//loop through all of the entries in the next section
							for(uchar l=0; l<paths[i + xLen][j + off].size(); l++)
							{
								if(isPathSame(i, j, k, i + xLen, j + off, l))
								{
									canContinue = true;
									saveOffset = l;
								}

								if(canContinue)
									offsets.push_back(saveOffset);								
							}

							if(!canContinue)
								goodLoop = false;
						}

						if(goodLoop)
						{
							//if we're in here, then every entry in the next row
							//is the same as the original path
							for(off=0; off<zLen; off++)
							{
								//assign the path to this pointer
								paths[i + xLen][j + off][offsets[off]].surface = pathPoly;

								//mark the path as compiled
								paths[i + xLen][j + off][offsets[off]].compiled = true;
							}

							xLen++;
						}
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
					switch(paths[i][j][k].pathModifier2 & PATH_SLOPE_MASK)
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
					v.y = (paths[i][j][k].baseHeight + topOffset + leftOffset) * UNITHEIGHT + 0.1f;
					v.z = startZ * UNITWIDTH;

					//originally 0,0
					tex.x = texCoord[3][0] * (float)xLen;
					tex.y = texCoord[3][1] * (float)zLen;
					tex.z = 0.0f;

					pathPoly->addVertex(v, tex);

					//TR
					v.x = (startX + xLen) * UNITWIDTH;
					v.y = (paths[i][j][k].baseHeight + topOffset + rightOffset) * UNITHEIGHT + 0.1f;
					v.z = startZ * UNITWIDTH;

					//orginally 1,0
					tex.x = texCoord[2][0] * (float)xLen;
					tex.y = texCoord[2][1] * (float)zLen;

					pathPoly->addVertex(v, tex);

					//BR
					v.x = (startX+ xLen) * UNITWIDTH;
					v.y = (paths[i][j][k].baseHeight + bottomOffset + rightOffset) * UNITHEIGHT + 0.1f;
					v.z = (startZ + zLen) * UNITWIDTH;

					//originally 1,1
					tex.x = texCoord[0][0] * (float)xLen;
					tex.y = texCoord[0][1] * (float)zLen;
					
					pathPoly->addVertex(v, tex);

					//BL
					v.x = startX * UNITWIDTH;
					v.y = (paths[i][j][k].baseHeight + bottomOffset + leftOffset) * UNITHEIGHT + 0.1f;
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
					paths[i][j][k].compiled = true;

					actualPolys+=zLen;
					renderedPolys++;
				}
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

void RCTGLPathSystem::loadPathTextureGroup(uchar index1, uchar index2, char *baseFilename)
{
	RCTGLTextureManager texMan;
	uchar masks[NUM_MASKS];

	uchar DIAGONAL_MASK = PATH_NW | PATH_NE | PATH_SE | PATH_SW;

	//
	// NON-DIAGONAL PIECES
	//
	
	//all sides and corners empty
	//000
	//010
	//000
	masks[0] = PATH_NORTH | PATH_SOUTH | PATH_EAST | PATH_WEST | DIAGONAL_MASK;
	//path from E->W
	//000
	//111
	//000
	masks[1] = PATH_NORTH | PATH_SOUTH | DIAGONAL_MASK;
	//path from E->N
	//010
	//011
	//000
	masks[2] = PATH_SOUTH | PATH_WEST | DIAGONAL_MASK;
	//path from E->N & W
	//010
	//111
	//000
	masks[3] = PATH_SOUTH | DIAGONAL_MASK;
	//path from S
	//000
	//010
	//010
	masks[4] = PATH_NORTH | PATH_EAST | PATH_WEST | DIAGONAL_MASK;
	//paths from all directions
	//010
	//111
	//010
	masks[5] = DIAGONAL_MASK;

	//
	// DIAGONAL PIECES
	//
	
	//solid piece (4, 4)
	//111
	//111
	//111
	masks[6] = 0;
	//edge piece (3,2)
	//111
	//111
	//000
	masks[7] = PATH_NE | PATH_NORTH | PATH_NW;
	//one corner notched in (4, 3)
	//111
	//111
	//110
	masks[8] = PATH_SE;
	//extended corners (2, 1)
	//000
	//011
	//011
	masks[9] = PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH | PATH_NE;



	//half full - T (4, 2)
	//010
	//111
	//111
	masks[10] = PATH_NE | PATH_NW;
	//opposites (4, 2)
	//110
	//111
	//011
	masks[11] = PATH_NE | PATH_SW;
	//T with a corner (3, 1)
	//011
	//111
	//000
	masks[12] = PATH_NW | PATH_SW | PATH_SOUTH | PATH_SE;
	//full cross with a corner (4, 1)
	//011
	//111
	//010
	masks[13] = PATH_NW | PATH_SW | PATH_SE;
	

	for(int i=0; i<NUM_MASKS; i++)
		m_otherTextures[index1 >> 2][index2][i] = texMan.addTexture(baseFilename, masks[i]);	
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
	m_queueTextures[BLUE_QUEUE][0] = texMan.addTexture("\\paths\\00-00.tga", 0);
	m_queueTextures[BLUE_QUEUE][1] = texMan.addTexture("\\paths\\00-06.tga", 0);
	m_queueTextures[BLUE_QUEUE][2] = texMan.addTexture("\\paths\\00-10.tga", 0);

	m_queueTextures[RED_QUEUE][0] = texMan.addTexture("\\paths\\01-00.tga", 0);
	m_queueTextures[RED_QUEUE][1] = texMan.addTexture("\\paths\\01-06.tga", 0);
	m_queueTextures[RED_QUEUE][2] = texMan.addTexture("\\paths\\01-10.tga", 0);

	m_queueTextures[YELLOW_QUEUE][0] = texMan.addTexture("\\paths\\02-00.tga", 0);
	m_queueTextures[YELLOW_QUEUE][1] = texMan.addTexture("\\paths\\02-06.tga", 0);
	m_queueTextures[YELLOW_QUEUE][2] = texMan.addTexture("\\paths\\02-10.tga", 0);

	m_queueTextures[GREEN_QUEUE][0] = texMan.addTexture("\\paths\\03-00.tga", 0);
	m_queueTextures[GREEN_QUEUE][1] = texMan.addTexture("\\paths\\03-06.tga", 0);
	m_queueTextures[GREEN_QUEUE][2] = texMan.addTexture("\\paths\\03-10.tga", 0);

	//load road textures


	//load other textures
	//[path style][path type][connection type]
	loadPathTextureGroup(PATH_STYLE_TARMAC, GRAY_TARMAC, "\\paths\\04-base.tga");
	loadPathTextureGroup(PATH_STYLE_TARMAC, RED_TARMAC, "\\paths\\05-base.tga");
	loadPathTextureGroup(PATH_STYLE_TARMAC, BROWN_TARMAC, "\\paths\\06-base.tga");
	loadPathTextureGroup(PATH_STYLE_TARMAC, GREEN_TARMAC, "\\paths\\07-base.tga");
	
	loadPathTextureGroup(PATH_STYLE_DIRT, BROWN_DIRT, "\\paths\\0D-base.tga");
	loadPathTextureGroup(PATH_STYLE_DIRT, BLACK_DIRT, "\\paths\\0E-base.tga");

	loadPathTextureGroup(PATH_STYLE_CRAZY_TILE, CRAZY_TILE, "\\paths\\0C-base.tga");

	loadPathTextureGroup(PATH_STYLE_TILE, PLAIN_TILE, "\\paths\\08-base.tga");
	loadPathTextureGroup(PATH_STYLE_TILE, GRAY_TILE, "\\paths\\09-base.tga");
	loadPathTextureGroup(PATH_STYLE_TILE, RED_TILE, "\\paths\\0A-base.tga");
	loadPathTextureGroup(PATH_STYLE_TILE, GREEN_TILE, "\\paths\\0B-base.tga");	

	DebugLog::endTask();
}
