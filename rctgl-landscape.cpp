#include "rctgl-landscape.h"
#include "rctgl-texman.h"

//#define DETAILED_LOG
#define OPTIMIZE_LANDSCAPE


RCTGLLandscape::RCTGLLandscape(void)
{
	for(int i=0; i<128; i++)
	{
		for(int j=0; j<128; j++)
		{
			land[i][j].edgeType = -1;
			land[i][j].edgeLL = false;

			land[i][j].surfaceType = -1;
			land[i][j].surfaceLL = false;

			land[i][j].TR = land[i][j].TL = land[i][j].BR = land[i][j].BL = 0;
			land[i][j].waterLevel = -1;
			land[i][j].lowest = land[i][j].highest = -1;

			land[i][j].drawWater = false;
			land[i][j].allLandUnderwater = false;			

			land[i][j].surface = NULL;
			land[i][j].waterSurface = NULL;

			land[i][j].edges[EDGE_NORTH] = NULL;
			land[i][j].edges[EDGE_EAST] = NULL;
		}
	}
}

void RCTGLLandscape::loadTextures(void)
{
	RCTGLTextureManager texMan;

	DebugLog::beginTask("RCTGLLandscape::loadTextures");

	//non LL surfaces
	surfaceTextures[GRASS_TILE]		= texMan.addTexture("\\surfaces\\grass4b.tga", 0);
	surfaceTextures[SAND_TILE]		= texMan.addTexture("\\surfaces\\sand1.tga", 0);
	surfaceTextures[DIRT_TILE]		= texMan.addTexture("\\surfaces\\dirt1.tga", 0);
	surfaceTextures[ROCK_TILE]		= texMan.addTexture("\\surfaces\\gravel1.tga", 0);
	surfaceTextures[MARTIAN_TILE]	= texMan.addTexture("\\surfaces\\mars1.tga", 0);
	surfaceTextures[CHECKER_TILE]	= texMan.addTexture("\\surfaces\\checker1.tga", 0);
	surfaceTextures[JUNGLE_TILE]	= texMan.addTexture("\\surfaces\\jungle1.tga", 0);
	surfaceTextures[ROOF_TILE]		= texMan.addTexture("\\surfaces\\roofing1.tga", 0);	

	// LL surfaces
	surfaceTextures[8 + GREEN_GRID]	 = texMan.addTexture("\\surfaces\\green1.tga", 0);
	surfaceTextures[8 + PURPLE_GRID] = texMan.addTexture("\\surfaces\\purple1.tga", 0);
	surfaceTextures[8 + YELLOW_GRID] = texMan.addTexture("\\surfaces\\yellow1.tga", 0);
	surfaceTextures[8 + RED_GRID]	 = texMan.addTexture("\\surfaces\\red1.tga", 0);
	surfaceTextures[8 + GRAY_ROOF]	 = texMan.addTexture("\\surfaces\\grey1.tga", 0);
	surfaceTextures[8 + IRON_ROOF]	 = texMan.addTexture("\\surfaces\\iron1.tga", 0);
	surfaceTextures[8 + LOG_ROOF]	 = texMan.addTexture("\\surfaces\\log1.tga", 0);
	surfaceTextures[8 + ICE_TILE]	 = texMan.addTexture("\\surfaces\\icetop1.tga", 0);
	
	// non LL edges
	edgeTextures[WOOD_EDGE]		= texMan.addTexture("\\edges\\wood1.tga", 0);
	edgeTextures[ROCK_EDGE]		= texMan.addTexture("\\edges\\dirtwall.tga", 0);
	edgeTextures[BRICK_EDGE]	= texMan.addTexture("\\edges\\bricks.tga", 0);
	edgeTextures[IRON_EDGE]		= texMan.addTexture("\\edges\\rustwall.tga", 0);
	edgeTextures[BLACK_WALL]	= texMan.addTexture("\\edges\\darkwall.tga", 0);
	edgeTextures[GRAY_WALL]		= texMan.addTexture("\\edges\\greywall.tga", 0);
	edgeTextures[YELLOW_WALL]	= texMan.addTexture("\\edges\\yelwall.tga", 0);
	edgeTextures[RED_WALL]		= texMan.addTexture("\\edges\\redwall.tga", 0);

	//LL edges
	edgeTextures[8 + ICE_WALL]		= texMan.addTexture("\\edges\\icewall.tga", 0);
	edgeTextures[8 + PURPLE_WALL]	= texMan.addTexture("\\edges\\purwall.tga", 0);
	edgeTextures[8 + GREEN_WALL]	= texMan.addTexture("\\edges\\grnwall.tga", 0);
	edgeTextures[8 + BROWN_STONE]	= texMan.addTexture("\\edges\\brstwall.tga", 0);
	edgeTextures[8 + GRAY_STONE]	= texMan.addTexture("\\edges\\grstwall.tga", 0);
	edgeTextures[8 + SKYSCRAPER_A]	= texMan.addTexture("\\edges\\skyawall.tga", 0);
	edgeTextures[8 + SKYSCRAPER_B]	= texMan.addTexture("\\edges\\skybwall.tga", 0);

	//water
	waterTexture = texMan.addTexture("\\surfaces\\water1.tga", 0);

	DebugLog::endTask();
}

void RCTGLLandscape::clear(void)
{
	DebugLog::beginTask("RCTGLLandscape::clear");

	uchar i, j, x, y;

	//clean up the surfaces
	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			if(land[i][j].surface)
			{
				uchar wid, len;

				wid = land[i][j].surface->width;
				len = land[i][j].surface->length;

				delete land[i][j].surface;

				for(x=0; x<wid; x++)
					for(y=0; y<len; y++)
						if(land[i+x][j+y].surface)
							land[i+x][j+y].surface = NULL;
			}
		}
	}

	//clean up the water
	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			if(land[i][j].waterSurface)
			{
				uchar wid, len;

				wid = land[i][j].waterSurface->width;
				len = land[i][j].waterSurface->length;

				delete land[i][j].waterSurface;

				for(x=0; x<wid; x++)
					for(y=0; y<len; y++)
						land[i+x][j+y].waterSurface = NULL;
			}
		}
	}
	//clean up everything else
	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			land[i][j].edgeType = -1;
			land[i][j].edgeLL = false;

			land[i][j].surfaceType = -1;
			land[i][j].surfaceLL = false;

			land[i][j].TR = land[i][j].TL = land[i][j].BR = land[i][j].BL = 0;
			land[i][j].waterLevel = -1;
			land[i][j].lowest = land[i][j].highest = -1;

			land[i][j].drawWater = false;
			land[i][j].allLandUnderwater = false;
			
			if(land[i][j].edges[EDGE_NORTH])
				delete land[i][j].edges[EDGE_NORTH];
			if(land[i][j].edges[EDGE_EAST])
				delete land[i][j].edges[EDGE_EAST];

			land[i][j].edges[EDGE_NORTH] = NULL;
			land[i][j].edges[EDGE_EAST] = NULL;
		}
	}

	DebugLog::endTask();
}

bool RCTGLLandscape::loadOffset(uchar *gameData, int x, int y)
{
	uchar buffer;

	buffer = gameData[0];

	//MSB determines edge. LSB determines surface
	if(buffer & 0x01)
		land[x][y].surfaceLL = true;
	if(buffer & 0x80)
		land[x][y].edgeLL = true;

	//get the base height
	buffer = gameData[2];
	if(buffer)
		land[x][y].TR = land[x][y].TL = land[x][y].BR = land[x][y].BL = buffer / 4;

	//get the edge type by masking with 11100000
	buffer = gameData[4];
	land[x][y].edgeType = ((buffer & 0xE0) >> 5);

	//get the height of each corner by masking with 00011111
	buffer = gameData[4];
	buffer = (buffer & 0x1F);

	//handle 4 bit operation
	if(buffer < 16)
	{
		if(buffer & 0x01)
			land[x][y].TL++;
		if(buffer & 0x02)
			land[x][y].TR++;
		if(buffer & 0x04)
			land[x][y].BR++;
		if(buffer & 0x08)
			land[x][y].BL++;
	}
	//handle the special 5-bit cases
	else
	{
		switch(buffer)
		{
		case 23:
			land[x][y].TL++;
			land[x][y].TR+=2;
			land[x][y].BR++;
			break;
		case 27:
			land[x][y].TL+=2;
			land[x][y].TR++;
			land[x][y].BL++;
			break;
		case 30:
			land[x][y].TR++;
			land[x][y].BR+=2;
			land[x][y].BL++;
			break;
		case 29:
			land[x][y].TL++;
			land[x][y].BR++;
			land[x][y].BL+=2;
			break;
		}
	}

	//get the surface by masking with 11100000 and shifting
	buffer = gameData[5];
	land[x][y].surfaceType = ((buffer & 0xE0) >> 5);

	//get the water level by masking with 00011111
	buffer = gameData[5];
	land[x][y].waterLevel = (buffer & 0x1F);

	//precalculate the optimizations
	if((land[x][y].waterLevel > land[x][y].TL) ||
		(land[x][y].waterLevel > land[x][y].TR) ||
		(land[x][y].waterLevel > land[x][y].BR) ||
		(land[x][y].waterLevel > land[x][y].BL))
		land[x][y].drawWater = true;

	if((land[x][y].waterLevel > land[x][y].TL) &&
		(land[x][y].waterLevel > land[x][y].TR) &&
		(land[x][y].waterLevel > land[x][y].BR) &&
		(land[x][y].waterLevel > land[x][y].BL))
		land[x][y].allLandUnderwater = true;
	
	//calc lowest point
	land[x][y].lowest = land[x][y].BR;
	if(land[x][y].BL < land[x][y].lowest)
		land[x][y].lowest = land[x][y].BL;
	if(land[x][y].TL < land[x][y].lowest)
		land[x][y].lowest = land[x][y].TL;
	if(land[x][y].TR < land[x][y].lowest)
		land[x][y].lowest = land[x][y].TR;

	//calc highest point
	land[x][y].highest = land[x][y].BR;
	if(land[x][y].BL > land[x][y].highest)
		land[x][y].highest = land[x][y].BL;
	if(land[x][y].TL > land[x][y].highest)
		land[x][y].highest = land[x][y].TL;
	if(land[x][y].TR > land[x][y].highest)
		land[x][y].highest = land[x][y].TR;
	if(land[x][y].waterLevel > land[x][y].highest)
		land[x][y].highest = land[x][y].waterLevel;

	return true;
}

bool RCTGLLandscape::isFlatLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif

	return (land[x1][z1].TL			== land[x2][z2].TL &&
		land[x1][z1].BL				== land[x2][z2].BL &&
		land[x1][z1].BR				== land[x2][z2].BR &&
		land[x1][z1].TR				== land[x2][z2].TR &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);
}

bool RCTGLLandscape::isFlatRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	/*
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isFlatLandSame(startX, startZ, row, z))
			return false;	
	*/
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isFlatLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isLeftRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL + (z2 - z1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL + (z2 - z1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR + (z2 - z1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR + (z2 - z1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}
	


bool RCTGLLandscape::isLeftRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isLeftRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}


bool RCTGLLandscape::isRightRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL - (z2 - z1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL - (z2 - z1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR - (z2 - z1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR - (z2 - z1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isRightRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isRightRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}


bool RCTGLLandscape::isLowerRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL + (x2 - x1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL + (x2 - x1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR + (x2 - x1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR + (x2 - x1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isLowerRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isLowerRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isUpperRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL - (x2 - x1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL - (x2 - x1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR - (x2 - x1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR - (x2 - x1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isUpperRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isUpperRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isUpperRightRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL - (x2 - x1) - (z2 - z1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL - (x2 - x1) - (z2 - z1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR - (x2 - x1) - (z2 - z1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR - (x2 - x1) - (z2 - z1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isUpperRightRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isUpperRightRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isLowerLeftRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL + (x2 - x1) + (z2 - z1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL + (x2 - x1) + (z2 - z1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR + (x2 - x1) + (z2 - z1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR + (x2 - x1) + (z2 - z1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isLowerLeftRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isLowerLeftRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isUpperLeftRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL - (x2 - x1) + (z2 - z1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL - (x2 - x1) + (z2 - z1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR - (x2 - x1) + (z2 - z1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR - (x2 - x1) + (z2 - z1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isUpperLeftRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isUpperLeftRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isLowerRightRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
#ifdef DETAILED_LOG

	stringstream x;
	x << "Comparing " << (unsigned int)x1 << ", " << (unsigned int)z1;
	x << " to " << (unsigned int)x2 << ", " << (unsigned int)z2;
	DebugLog::writeToLog(x.str());

#endif	
	
	return (land[x1][z1].TL			== (land[x2][z2].TL + (x2 - x1) - (z2 - z1)) &&
		land[x1][z1].BL				== (land[x2][z2].BL + (x2 - x1) - (z2 - z1)) &&
		land[x1][z1].BR				== (land[x2][z2].BR + (x2 - x1) - (z2 - z1)) &&
		land[x1][z1].TR				== (land[x2][z2].TR + (x2 - x1) - (z2 - z1)) &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType &&
		!land[x2][z2].surface);	
}

bool RCTGLLandscape::isLowerRightRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isLowerRightRaisedLandSame(startX, startZ, row, z))
			return false;	


	return true;
}

bool RCTGLLandscape::isWaterSame(uchar x1, uchar z1, uchar x2, uchar z2)
{
	return (land[x1][z1].drawWater	== land[x2][z2].drawWater &&
		land[x1][z1].waterLevel		== land[x2][z2].waterLevel);
}

bool RCTGLLandscape::isWaterRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isWaterSame(startX, startZ, row, z))
			return false;	

	return true;
}


void RCTGLLandscape::assignSurfaceToLand(uchar startX, uchar xLen, uchar startZ, uchar zLen, RCTGLExtendedPoly *surface)
{
	//assign the pointer to all of the appropriate surfaces
	uchar zStep, xStep;
	for(zStep=0; zStep<zLen; zStep++)
	{
		for(xStep=0; xStep<xLen; xStep++)
		{
#ifdef DETAILED_LOG
			stringstream x;
			x << "Setting land at " << (unsigned int)(startX + xStep);
			x << ", " << (unsigned int)(startZ + zStep);
			x << " to value at " << (unsigned int)startX << ", " << (unsigned int)startZ;
			DebugLog::writeToLog(x.str());
#endif

			if(land[startX + xStep][startZ + zStep].surface)
			{
				stringstream x;
				x << "Error: Polygon at " << (unsigned int)(startX + xStep) << ", " << (unsigned int)(startZ + zStep) << " was reassigned";
				DebugLog::writeToLog(x.str());
			}
			else
				land[startX + xStep][startZ + zStep].surface= surface;
		}
	}
}

void RCTGLLandscape::assignWaterSurfaceToLand(uchar startX, uchar xLen, uchar startZ, uchar zLen, RCTGLExtendedPoly *surface)
{
	//assign the pointer to all of the appropriate surfaces
	uchar zStep, xStep;
	for(zStep=0; zStep<zLen; zStep++)
	{
		for(xStep=0; xStep<xLen; xStep++)
		{
#ifdef DETAILED_LOG
			stringstream x;
			x << "Setting land at " << (unsigned int)(startX + xStep);
			x << ", " << (unsigned int)(startZ + zStep);
			x << " to value at " << (unsigned int)startX << ", " << (unsigned int)startZ;
			DebugLog::writeToLog(x.str());
#endif

			if(land[startX + xStep][startZ + zStep].waterSurface)
			{
				stringstream x;
				x << "Error: Polygon at " << (unsigned int)(startX + xStep) << ", " << (unsigned int)(startZ + zStep) << " was reassigned";
				DebugLog::writeToLog(x.str());
			}
			else
				land[startX + xStep][startZ + zStep].waterSurface= surface;
		}
	}
}

void RCTGLLandscape::addVerticiesToSurface(uchar startX, uchar xLen, uchar startZ, uchar zLen, RCTGLExtendedPoly *surface, bool isWater)
{
	RCTGLVertex v, tex;

	//TL
	v.x = startX * UNITWIDTH;
	if(isWater)
		v.y = land[startX][startZ].waterLevel * UNITHEIGHT - 0.05f;
	else
		v.y = land[startX][startZ].BR * UNITHEIGHT;
	v.z = startZ * UNITWIDTH;

	tex.x = 0.0f;
	tex.y = 0.0f;
	tex.z = 0.0f;

	surface->addVertex(v, tex);

	//TR
	v.x = (startX + xLen) * UNITWIDTH;
	if(!isWater)
		v.y = land[startX+(xLen-1)][startZ].BL * UNITHEIGHT;
	v.z = startZ * UNITWIDTH;

	tex.x = (float)xLen;
	tex.y = 0.0f;

	surface->addVertex(v, tex);

	//BR
	v.x = (startX+ xLen) * UNITWIDTH;
	if(!isWater)
		v.y = land[startX+(xLen-1)][startZ+(zLen-1)].TL * UNITHEIGHT;
	v.z = (startZ + zLen) * UNITWIDTH;

	tex.x = (float)xLen;
	tex.y = (float)zLen;
	
	surface->addVertex(v, tex);

	//BL
	v.x = startX * UNITWIDTH;
	if(!isWater)
		v.y = land[startX][startZ+(zLen-1)].TR * UNITHEIGHT;
	v.z = (startZ + zLen) * UNITWIDTH;

	tex.x = 0.0f;
	tex.y = (float)zLen;

	surface->addVertex(v, tex);
	
	//assign the texture
	if(!isWater)
	{
		if(land[startX][startZ].surfaceLL)
			surface->setTextureID(surfaceTextures[8 + land[startX][startZ].surfaceType]);
		else
			surface->setTextureID(surfaceTextures[land[startX][startZ].surfaceType]);
	}

	surface->length = zLen;
	surface->width = xLen;
}

void RCTGLLandscape::compileSurfaces()
{
	DebugLog::beginTask((string)"RCTGLLandscape::compileSurfaces()");

	uchar i, j; //, k, l;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;
	RCTGLRGB testRGB;
	testRGB.r = testRGB.g = testRGB.b = 0.5f;

	//build the surfaces
	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			if(!land[i][j].surface)
			{
				//create the surface
				RCTGLExtendedPoly *surface = new RCTGLExtendedPoly;			
				
				surface->setBaseRGB(rgb);
				
				uchar baseZ = j, baseX = i;
				uchar offsetZ = 1, offsetX = 1;
				
#ifdef DETAILED_LOG
				stringstream coords;
				coords << " === Processing " << (unsigned int)i << ", " << (unsigned int)j << " ===";
				DebugLog::writeToLog(coords.str());
#endif
				
#ifdef OPTIMIZE_LANDSCAPE
				//check for optimizations
				//handle flat pieces
				// 0 0
				// 0 0
				if(land[i][j].TL == land[i][j].TR &&
					land[i][j].TL == land[i][j].BR &&
					land[i][j].TL == land[i][j].BL)			
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"Optimizing flat land");
#endif
					//find out how long the land segment lasts
					while(isFlatLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isFlatRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)
						offsetX++;
					
#ifdef DETAILED_LOG
					if(offsetX > 1 && offsetZ > 1)
					{
						stringstream x;
						x << "Expanding flat land at " << (unsigned int)i << ", " << (unsigned int)j;
						x << " to " << (unsigned int)(i + offsetX - 1) << ", " << (unsigned int)(j + offsetZ - 1);
						DebugLog::writeToLog(x.str());
					}
#endif
				}
				//handle left-raised land
				// 1 0
				// 1 0
				else if(land[i][j].BL == land[i][j].BR &&
					land[i][j].TL == land[i][j].TR &&
					land[i][j].BL == land[i][j].TL + 1 &&
					land[i][j].BR == land[i][j].TR + 1)
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"Optimizing left-raised land");
#endif
					//find out how long the land segment lasts
					while(isLeftRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isLeftRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;				
				}
				//handle right-raised land
				// 0 1
				// 0 1
				else if(land[i][j].BL == land[i][j].BR &&
					land[i][j].TL == land[i][j].TR &&
					land[i][j].BL == land[i][j].TL - 1 &&
					land[i][j].BR == land[i][j].TR - 1)
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"Optimizing right-raised land");
#endif
					//find out how long the land segment lasts
					while(isRightRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isRightRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;				
				}
				//lower raised land
				// 0 0
				// 1 1
				else if(land[i][j].BL == land[i][j].TL &&
					land[i][j].BR == land[i][j].TR &&
					land[i][j].BL == land[i][j].BR - 1 &&
					land[i][j].TL == land[i][j].TR - 1)
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"Optimizing right-raised land");
#endif
					//find out how long the land segment lasts
					while(isLowerRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isLowerRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;				
				}
				//upper raised land
				// 1 1
				// 0 0
				else if(land[i][j].BL == land[i][j].TL &&
					land[i][j].BR == land[i][j].TR &&
					land[i][j].BL == land[i][j].BR + 1 &&
					land[i][j].TL == land[i][j].TR + 1)
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"Optimizing right-raised land");
#endif
					//find out how long the land segment lasts
					while(isUpperRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isUpperRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;				
				}
				//upper right raised land
				// 1 2
				// 0 1
				else if(land[i][j].BL == land[i][j].TR &&
					land[i][j].BL == land[i][j].TL - 1 &&
					land[i][j].BL == land[i][j].BR + 1)
				{
					//find out how long the land segment lasts
					while(isUpperRightRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isUpperRightRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;
				}
				//bottom left raised land
				// 1 0
				// 2 1
				else if(land[i][j].BL == land[i][j].TR &&
					land[i][j].BL == land[i][j].TL + 1 &&
					land[i][j].BL == land[i][j].BR - 1)
				{
					//find out how long the land segment lasts
					while(isLowerLeftRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isLowerLeftRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;
				}
				//upper left raised land
				// 2 1
				// 1 0
				else if(land[i][j].BR == land[i][j].TL &&
					land[i][j].BR == land[i][j].TR + 1 &&
					land[i][j].BR == land[i][j].BL - 1) 
				{
					//find out how long the land segment lasts
					while(isUpperLeftRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isUpperLeftRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;
				}
				//lower right raised land
				// 0 1
				// 1 2
				else if(land[i][j].BR == land[i][j].TL &&
					land[i][j].BR == land[i][j].TR - 1 &&
					land[i][j].BR == land[i][j].BL + 1) 
				{
					//find out how long the land segment lasts
					while(isLowerRightRaisedLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
						baseZ + offsetZ < 128)
						offsetZ++;				
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isLowerRightRaisedRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)					
						offsetX++;
				}
				else if(land[i][j].surface)
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"Surface already assigned");
#endif
					continue;
				}
				else if(!land[i][j].surface)
#endif //#ifdef OPTIMIZE_LANDSCAPE
				{
#ifdef DETAILED_LOG
					DebugLog::writeToLog((string)"NOT optimizing land");
					stringstream y;		
					y << "(" << land[i][j].BL << ", " << land[i][j].TL << ", " << land[i][j].TR << ", " << land[i][j].BR << ")";
					DebugLog::writeToLog(y.str());
#endif
				}
				
				addVerticiesToSurface(baseX, offsetX, baseZ, offsetZ, surface, false);
				assignSurfaceToLand(baseX, offsetX, baseZ, offsetZ, surface);
				
				//move j
				j+=(offsetZ-1);
				
				numPolys++;
				totalPolys += (offsetZ * offsetX);
			}
		}
	}

	DebugLog::endTask();
}

void RCTGLLandscape::compileEdges()
{
	uchar i, j; //, k;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	DebugLog::beginTask((string)"RCTGLLandscape::compileEdges()");

	/*
	BR (0, 0)	BL (1, 0)
	TR (0, 1)	TL (1, 1)
	 */

	//now build the edges
	for(i=0;i<128;i++)		//x
	{
		for(j=0;j<128;j++)	//z
		{
			land[i][j].edges[EDGE_NORTH] = NULL;
			land[i][j].edges[EDGE_SOUTH] = NULL;
			land[i][j].edges[EDGE_EAST] = NULL;
			land[i][j].edges[EDGE_WEST] = NULL;

			//check N edge
			if(j < 127)
			{
				//heights are different. make a polygon				
				if((land[i][j+1].BR != land[i][j].TR) || (land[i][j+1].BL != land[i][j].TL))
				{
					RCTGLExtendedPoly *tmp = new RCTGLExtendedPoly;
					RCTGLVertex v, tex;					

					tmp->setBaseRGB(rgb);

					//vert1
					v.x = UNITWIDTH * i;
					v.y = land[i][j+1].BR * UNITHEIGHT;
					v.z = UNITWIDTH * (j + 1);

					tex.x = 1.0f;
					tex.y = land[i][j+1].BR / 2.0f;//0.0f;

					tmp->addVertex(v, tex);

					//vert2
					v.x = UNITWIDTH * i;
					v.y = land[i][j].TR * UNITHEIGHT;
					v.z = UNITWIDTH * (j + 1);

					tex.x = 1.0f;
					tex.y = land[i][j].TR / 2.0f; //1.0f;

					tmp->addVertex(v, tex);

					//vert3
					v.x = UNITWIDTH * (i + 1);
					v.y = land[i][j].TL * UNITHEIGHT;
					v.z = UNITWIDTH * (j + 1);

					tex.x = 0.0f;
					tex.y = land[i][j].TL / 2.0f; //1.0f;

					tmp->addVertex(v, tex);

					//vert4
					v.x = UNITWIDTH * (i + 1);
					v.y = land[i][j+1].BL * UNITHEIGHT;
					v.z = UNITWIDTH * (j + 1);

					tex.x = 0.0f;
					tex.y = land[i][j+1].BL / 2.0f; //0.0f;

					tmp->addVertex(v, tex);

					if((land[i][j+1].BR >= land[i][j].TR) && (land[i][j+1].BL >= land[i][j].TL))
					{
						if(land[i][j+1].edgeLL)
							tmp->setTextureID(edgeTextures[8 + land[i][j+1].edgeType]);
						else
							tmp->setTextureID(edgeTextures[land[i][j+1].edgeType]);
					}
					else
					{
						if(land[i][j].edgeLL)
							tmp->setTextureID(edgeTextures[8 + land[i][j].edgeType]);
						else
							tmp->setTextureID(edgeTextures[land[i][j].edgeType]);

					}

					land[i][j].edges[EDGE_NORTH] = tmp;

					numPolys++;
					totalPolys++;
				}
			}			

			//check E edge
			if(i < 127)
			{
				//heights are different. make a polygon
				if((land[i+1][j].BR != land[i][j].BL) || (land[i+1][j].TR != land[i][j].TL))
				{
					RCTGLExtendedPoly *tmp = new RCTGLExtendedPoly;
					RCTGLVertex v, tex;					

					tmp->setBaseRGB(rgb);

					//vert1
					v.x = UNITWIDTH * (i + 1);
					v.y = land[i+1][j].BR * UNITHEIGHT;
					v.z = UNITWIDTH * j;

					tex.x = 0.0f;
					tex.y = land[i+1][j].BR / 2.0f;//0.0f;

					tmp->addVertex(v, tex);

					//vert2
					v.x = UNITWIDTH * (i + 1);
					v.y = land[i+1][j].TR * UNITHEIGHT;
					v.z = UNITWIDTH * (j + 1);

					tex.x = 1.0f;
					tex.y = land[i+1][j].TR / 2.0f; //1.0f;

					tmp->addVertex(v, tex);

					//vert3
					v.x = UNITWIDTH * (i + 1);
					v.y = land[i][j].TL * UNITHEIGHT;
					v.z = UNITWIDTH * (j + 1);

					tex.x = 1.0f;
					tex.y = land[i][j].TL / 2.0f; //1.0f;

					tmp->addVertex(v, tex);

					//vert4
					v.x = UNITWIDTH * (i + 1);
					v.y = land[i][j].BL * UNITHEIGHT;
					v.z = UNITWIDTH * j;

					tex.x = 0.0f;
					tex.y = land[i][j].BL / 2.0f; //0.0f;

					tmp->addVertex(v, tex);
					
					if((land[i+1][j].BR >= land[i][j].BL) || (land[i+1][j].TR >= land[i][j].TL))
					{
						if(land[i+1][j].edgeLL)
							tmp->setTextureID(edgeTextures[8 + land[i+1][j].edgeType]);
						else
							tmp->setTextureID(edgeTextures[land[i+1][j].edgeType]);
					}
					else
					{
						if(land[i][j].edgeLL)
							tmp->setTextureID(edgeTextures[8 + land[i][j].edgeType]);
						else
							tmp->setTextureID(edgeTextures[land[i][j].edgeType]);

					}
					

					land[i][j].edges[EDGE_EAST] = tmp;

					numPolys++;
					totalPolys++;
				}
			}
		}
	}

	DebugLog::endTask();
}


void RCTGLLandscape::compileWater()
{
	uchar i, j;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	DebugLog::beginTask((string)"RCTGLLandscape::compileWater()");

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			if(!land[i][j].waterSurface)
			{
				//create the surface
				RCTGLExtendedPoly *surface = new RCTGLExtendedPoly;
				
				surface->setBaseRGB(rgb);
				
				//check for optimizations
				if(land[i][j].drawWater && !land[i][j].waterSurface)
				{
					//find out how long the land segment lasts
					uchar baseZ = j, baseX = i;
					uchar offsetZ = 1, offsetX = 1;
#ifdef OPTIMIZE_LANDSCAPE
					while(isWaterSame(i, baseZ, i, baseZ+offsetZ) && 
						baseZ + offsetZ < 128)
						offsetZ++;
					
					//now that we have the maximum Z for this segment, let's
					//find how far it extends in the X direction
					while(isWaterRowSame(baseX, baseZ, baseX+offsetX, offsetZ) &&
						baseX + offsetX < 128)
						offsetX++;
#endif //#ifdef OPTIMIZE_LANDSCAPE
					
					addVerticiesToSurface(baseX, offsetX, baseZ, offsetZ, surface, true);
					
					surface->setTextureID(waterTexture);
					
					assignWaterSurfaceToLand(baseX, offsetX, baseZ, offsetZ, surface);
					
					//move j
					j+=(offsetZ-1);
					
					numPolys++;
					totalPolys += (offsetZ * offsetX);
				}
			}		
		}
	}


	DebugLog::endTask();
}


void RCTGLLandscape::compile()
{
	DebugLog::beginTask((string)"RCTGLLandscape::compile()");

	numPolys = totalPolys = 0;

	compileSurfaces();
	compileWater();
	compileEdges();

	stringstream x;

	x << "Landscape optimized from " << (long)totalPolys << " to " << (long)numPolys << " polygons";
	DebugLog::writeToLog(x.str());

	DebugLog::endTask();
}



bool RCTGLLandscape::draw(uchar x1, uchar z1, uchar x2, uchar z2) const
{
	//glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);

	bool drawUnderwater = true;

	//this assumes that x1 < x2 and z1 < z2
	if((x1 > x2) || (z1 > z2))
		return false;
	
	uchar i, j; //, k;

	//initialize all polygons
	for(i=x1; i<x2; i++)
	{
		for(j=z1; j<z2; j++)
		{
			if(land[i][j].surface)
				land[i][j].surface->wasDrawn = false;
			
			if(land[i][j].waterSurface)
				land[i][j].waterSurface->wasDrawn = false;
			
		}
	}

	//as an optimization, we're going to draw the surface, edge, and water separately
	//this is to attempt to reduce the amount of texture switching we're doing

	//draw surface
	for(i=x1; i<x2; i++)
	{
		for(j=z1; j<z2; j++)
		{
			if(land[i][j].surface)
			{
				if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
					(float)((land[i][j].lowest * UNITHEIGHT) - 0.1f),
					(float)(j*UNITWIDTH),
					(float)(land[i][j].surface->width * UNITWIDTH),
					(float)((land[i][j].highest - land[i][j].lowest) * UNITHEIGHT + 0.2f),					
					(float)(land[i][j].surface->length * UNITWIDTH)))					
				{
					if(!land[i][j].surface->wasDrawn)
					{
						/*						
						if(land[i][j].BR == land[i][j].TL &&
							land[i][j].BR == land[i][j].TR - 1 &&
							land[i][j].BR == land[i][j].BL + 1)
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						*/
  
						land[i][j].surface->draw();
						land[i][j].surface->wasDrawn = true;

						//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					}
				}
			}
		}
	}

	//draw water
	for(i=x1; i<x2; i++)
	{
		for(j=z1; j<z2; j++)
		{
			if(land[i][j].waterSurface)
			{
				if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
					(float)((land[i][j].waterLevel * UNITHEIGHT) - 0.1f),
					(float)(j*UNITWIDTH),
					(float)(land[i][j].waterSurface->width * UNITWIDTH),
					(float)((land[i][j].waterLevel) * UNITHEIGHT + 0.1f),
					(float)(land[i][j].waterSurface->length * UNITWIDTH)))					
				{
					if(land[i][j].waterSurface && !land[i][j].waterSurface->wasDrawn)
					{
						land[i][j].waterSurface->draw();
						land[i][j].waterSurface->wasDrawn = true;
					}
				}
			}
		}
	}

	//draw edges
	for(i=x1; i<x2; i++)
	{
		for(j=z1; j<z2; j++)
		{
			//now we only care about elements 0 and 2			
			if(land[i][j].edges[EDGE_NORTH])
			{
				if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
					(float)(land[i][j].lowest * UNITHEIGHT),
					(float)(((j + 1)*UNITWIDTH) - 0.1f),
					(float)UNITWIDTH,
					(float)((land[i][j+1].highest - land[i][j].lowest) * UNITHEIGHT),					
					(float)0.2f))
					land[i][j].edges[EDGE_NORTH]->draw();

			}

			if(land[i][j].edges[EDGE_EAST])
			{
				if(theFrustum.isCubeInFrustum((float)((i+1)*UNITWIDTH),
					(float)(land[i][j].lowest * UNITHEIGHT),
					(float)((j*UNITWIDTH) - 0.1f),
					(float)0.2f,
					(float)((land[i+1][j].highest - land[i][j].lowest) * UNITHEIGHT),					
					(float)UNITWIDTH))					
					land[i][j].edges[EDGE_EAST]->draw();
			}
		}
	}		

	return true;
}



float RCTGLLandscape::getLowestPoint(int i, int j)
{
	float lowest;

	lowest = (float)land[i][j].TR;

	if (land[i][j].TL < lowest)
		lowest = (float)land[i][j].TL;
	if (land[i][j].BL < lowest)
		lowest = (float)land[i][j].BL;
	if (land[i][j].BR < lowest)
		lowest = (float)land[i][j].BR;

	return lowest;
}

float RCTGLLandscape::getHighestPoint(int i, int j)
{
	float highest;

	highest = (float)land[i][j].TR;

	if (land[i][j].TL > highest)
		highest = (float)land[i][j].TL;
	if (land[i][j].BL > highest)
		highest = (float)land[i][j].BL;
	if (land[i][j].BR > highest)
		highest = (float)land[i][j].BR;

	return highest;
}

