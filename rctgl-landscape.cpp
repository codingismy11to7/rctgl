#include "rctgl-landscape.h"
#include "rctgl-texman.h"


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

			if(land[i][j].surface)
				delete land[i][j].surface;
			if(land[i][j].waterSurface)
				delete land[i][j].waterSurface;

			land[i][j].surface = NULL;
			land[i][j].waterSurface = NULL;

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
	return (land[x1][z1].TL			== land[x2][z2].TL &&
		land[x1][z1].BL				== land[x2][z2].BL &&
		land[x1][z1].BR				== land[x2][z2].BR &&
		land[x1][z1].TR				== land[x2][z2].TR &&	
		land[x1][z1].surfaceLL		== land[x2][z2].surfaceLL &&
		land[x1][z1].surfaceType	== land[x2][z2].surfaceType);
}

bool RCTGLLandscape::isFlatRowSame(uchar startX, uchar startZ, uchar row, uchar width)
{
	for(uchar z=startZ; z<(startZ + width); z++)	
		if(!isFlatLandSame(startX, startZ, row, z))
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

void RCTGLLandscape::compileSurfaces(void)
{
	DebugLog::beginTask((string)"RCTGLLandscape::compileSurfaces()");

	uchar i, j, k, l;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	//build the surfaces
	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			//create the surface
			RCTGLLandscapePoly *surface = new RCTGLLandscapePoly;

			RCTGLVertex v, tex;

			surface->setBaseRGB(rgb);

#ifdef DETAILED_LOG
			stringstream coords;
			coords << "Processing " << (unsigned int)i << ", " << (unsigned int)j;
			DebugLog::writeToLog(coords.str());
#endif

			//check for optimizations
			if(land[i][j].TL == land[i][j].TR &&
				land[i][j].TL == land[i][j].BR &&
				land[i][j].TL == land[i][j].BL &&
				land[i][j].surface == NULL)			
			{
				//find out how long the land segment lasts
				uchar baseZ = j, baseX = i;
				uchar offsetZ = 1, offsetX = 1;

#ifdef DETAILED_LOG
				DebugLog::writeToLog((string)"Optimizing flat land");
#endif


				while(isFlatLandSame(baseX, baseZ, baseX, baseZ+offsetZ) &&
					baseZ + offsetZ < 128)
					offsetZ++;				

				//now that we have the maximum Z for this segment, let's
				//find how far it extends in the X direction
				while(isFlatRowSame(baseX, baseZ, offsetX, offsetZ) &&
					baseX + offsetX < 128)
					offsetX++;

				//TL
				v.x = baseX * UNITWIDTH;
				v.y = land[baseX][baseZ].BR * UNITHEIGHT;
				v.z = baseZ * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 0.0f;
				tex.z = 0.0f;

				surface->addVertex(v, tex);

				//TR
				v.x = (baseX + offsetX) * UNITWIDTH;
				v.y = land[baseX][baseZ].BL * UNITHEIGHT;
				v.z = baseZ * UNITWIDTH;

				tex.x = (float)offsetX;
				tex.y = 0.0f;

				surface->addVertex(v, tex);

				//BR
				v.x = (baseX+ offsetX) * UNITWIDTH;
				v.y = land[baseX][baseZ].TL * UNITHEIGHT;
				v.z = (baseZ + offsetZ) * UNITWIDTH;

				tex.x = (float)offsetX;
				tex.y = (float)offsetZ;
				
				surface->addVertex(v, tex);

				//BL
				v.x = baseX * UNITWIDTH;
				v.y = land[baseX][baseZ].TR * UNITHEIGHT;
				v.z = (baseZ + offsetZ) * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = (float)offsetZ;

				surface->addVertex(v, tex);
				
				//assign the texture
				if(land[i][j].surfaceLL)
					surface->setTextureID(surfaceTextures[8 + land[i][j].surfaceType]);
				else
					surface->setTextureID(surfaceTextures[land[i][j].surfaceType]);

				surface->length = offsetZ;
				surface->width = offsetX;

#ifdef DETAILED_LOG
				if(offsetX > 1 && offsetZ > 1)
				{
					stringstream x;
					x << "Expanding flat land at " << (unsigned int)i << ", " << (unsigned int)j;
					x << " to " << (unsigned int)(i + offsetX - 1) << ", " << (unsigned int)(j + offsetZ - 1);
					DebugLog::writeToLog(x.str());
				}
#endif

				//assign the pointer to all of the appropriate surfaces
				for(k=0; k<offsetZ; k++)
				{
					for(l=0; l<offsetX; l++)
					{
#ifdef DETAILED_LOG
						stringstream x;
						x << "Setting land at " << (unsigned int)(baseX + l);
						x << ", " << (unsigned int)(baseZ + k);
						x << " to value at " << (unsigned int)baseX << ", " << (unsigned int)baseZ;
						DebugLog::writeToLog(x.str());
#endif

						land[baseX + l][baseZ + k].surface = surface;
					}
				}

				//move j
				j+=(offsetZ-1);

				numPolys++;
				totalPolys += (offsetZ * offsetX);
			}
			else if(land[i][j].surface == NULL)
			{
#ifdef DETAILED_LOG
				DebugLog::writeToLog((string)"NOT optimizing land");
				stringstream y;		
				y << "(" << land[i][j].BL << ", " << land[i][j].TL << ", " << land[i][j].TR << ", " << land[i][j].BR << ")";
				DebugLog::writeToLog(y.str());
#endif
				//TL
				v.x = i * UNITWIDTH;
				v.y = land[i][j].BR * UNITHEIGHT;
				v.z = j * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 0.0f;
				tex.z = 0.0f;

				surface->addVertex(v, tex);

				//TR
				v.x = (i + 1) * UNITWIDTH;
				v.y = land[i][j].BL * UNITHEIGHT;
				v.z = j * UNITWIDTH;

				tex.x = 1.0f;
				tex.y = 0.0f;

				surface->addVertex(v, tex);

				//BR
				v.x = (i + 1) * UNITWIDTH;
				v.y = land[i][j].TL * UNITHEIGHT;
				v.z = (j + 1) * UNITWIDTH;

				tex.x = 1.0f;
				tex.y = 1.0f;
				
				surface->addVertex(v, tex);

				//BL
				v.x = i * UNITWIDTH;
				v.y = land[i][j].TR * UNITHEIGHT;
				v.z = (j + 1) * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 1.0f;

				surface->addVertex(v, tex);

				if(land[i][j].surfaceLL)
					surface->setTextureID(surfaceTextures[8 + land[i][j].surfaceType]);
				else
					surface->setTextureID(surfaceTextures[land[i][j].surfaceType]);

				surface->length = 1;

				land[i][j].surface = surface;

				numPolys++;
				totalPolys++;				
			}
			else if(!land[i][j].surface)
			{
#ifdef DETAILED_LOG
				DebugLog::writeToLog((string)"NULL surface");
#endif
			}
			else
			{
#ifdef DETAILED_LOG
				DebugLog::writeToLog((string)"Unhandled surface");
#endif
			}
		}
	}

	DebugLog::endTask();
}

void RCTGLLandscape::compileEdges(void)
{
	uchar i, j, k;

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
			if(j < 128)
			{
				//heights are different. make a polygon
				if((land[i][j+1].BR != land[i][j].TR) || (land[i][j+1].BL != land[i][j].TL))
				{
					RCTGLLandscapePoly *tmp = new RCTGLLandscapePoly;
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
			if(i < 128)
			{
				//heights are different. make a polygon
				if((land[i+1][j].BR != land[i][j].BL) || (land[i+1][j].TR != land[i][j].TL))
				{
					RCTGLLandscapePoly *tmp = new RCTGLLandscapePoly;
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


void RCTGLLandscape::compileWater(void)
{
	uchar i, j, k, l;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	DebugLog::beginTask((string)"RCTGLLandscape::compileWater()");

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			//create the surface
			RCTGLLandscapePoly *surface = new RCTGLLandscapePoly;

			RCTGLVertex v, tex;

			surface->setBaseRGB(rgb);

			//check for optimizations
			if(land[i][j].drawWater && !land[i][j].waterSurface)
			{
				//find out how long the land segment lasts
				uchar baseZ = j, baseX = i;
				uchar offsetZ = 1, offsetX = 1;
				while(isWaterSame(i, baseZ, i, baseZ+offsetZ) && 
					baseZ + offsetZ < 128)
					offsetZ++;

				//now that we have the maximum Z for this segment, let's
				//find how far it extends in the X direction
				while(isWaterRowSame(baseX, baseZ, offsetX, offsetZ) &&
					baseX + offsetX < 128)
					offsetX++;

				//TL
				v.x = baseX * UNITWIDTH;
				v.y = land[baseX][baseZ].waterLevel * UNITHEIGHT;
				v.z = baseZ * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 0.0f;
				tex.z = 0.0f;

				surface->addVertex(v, tex);

				//TR
				v.x = (baseX + offsetX) * UNITWIDTH;				
				v.z = baseZ * UNITWIDTH;

				tex.x = (float)offsetX;
				tex.y = 0.0f;

				surface->addVertex(v, tex);

				//BR
				v.x = (baseX+ offsetX) * UNITWIDTH;				
				v.z = (baseZ + offsetZ) * UNITWIDTH;

				tex.x = (float)offsetX;
				tex.y = (float)offsetZ;
				
				surface->addVertex(v, tex);

				//BL
				v.x = baseX * UNITWIDTH;				
				v.z = (baseZ + offsetZ) * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = (float)offsetZ;

				surface->addVertex(v, tex);
				
				//assign the texture
				surface->setTextureID(waterTexture);

				surface->length = offsetZ;
				surface->width = offsetX;

#ifdef DETAILED_LOG
				if(offsetX > 1 && offsetZ > 1)
				{
					stringstream x;
					x << "Expanding water at " << (unsigned int)i << ", " << (unsigned int)j;
					x << " to " << (unsigned int)(i + offsetX - 1) << ", " << (unsigned int)(j + offsetZ - 1);
					DebugLog::writeToLog(x.str());
				}
#endif

				//assign the pointer to all of the appropriate surfaces
				for(k=0; k<offsetZ; k++)
				{
					for(l=0; l<offsetX; l++)
					{
#ifdef DETAILED_LOG
						stringstream x;
						x << "Setting water at " << (unsigned int)(baseX + l);
						x << ", " << (unsigned int)(baseZ + k);
						x << " to value at " << (unsigned int)baseX << ", " << (unsigned int)baseZ;
						DebugLog::writeToLog(x.str());
#endif

						land[baseX + l][baseZ + k].waterSurface = surface;
					}
				}

				//move j
				j+=(offsetZ-1);

				numPolys++;
				totalPolys += (offsetZ * offsetX);
			}		
		}
	}


	DebugLog::endTask();
}


void RCTGLLandscape::compile(void)
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



bool RCTGLLandscape::draw(uchar x1, uchar z1, uchar x2, uchar z2)
{
	//glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);

	bool drawUnderwater = true;

	//this assumes that x1 < x2 and z1 < z2
	if((x1 > x2) || (z1 > z2))
		return false;
	
	uchar i, j, k;

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
	

	// draw the map
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
						land[i][j].surface->draw();
						land[i][j].surface->wasDrawn = true;
					}
				}
			}

			
			if(land[i][j].waterSurface)
			{
				if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
					(float)((land[i][j].lowest * UNITHEIGHT) - 0.1f),
					(float)(j*UNITWIDTH),
					(float)(land[i][j].surface->width * UNITWIDTH),
					(float)((land[i][j].highest - land[i][j].lowest) * UNITHEIGHT + 0.2f),					
					(float)(land[i][j].surface->length * UNITWIDTH)))					
				{
					if(land[i][j].waterSurface && !land[i][j].waterSurface->wasDrawn)
					{
						land[i][j].waterSurface->draw();
						land[i][j].waterSurface->wasDrawn = true;
					}
				}
			}
			

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

