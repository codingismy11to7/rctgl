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

void RCTGLLandscape::compileSurfaces(void)
{
	DebugLog::beginTask((string)"RCTGLLandscape::compileSurfaces()");

	uchar i, j, k;

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

			//check for optimizations
			if(land[i][j].TL == land[i][j].TR == land[i][j].BR == land[i][j].BL)
			{
				//find out how long the land segment lasts
				uchar base = j;
				uchar offset = 1;
				while(land[i][base].TL == land[i][base+offset].TL &&
					land[i][base].BL == land[i][base+offset].BL &&
					land[i][base].BR == land[i][base+offset].BR &&
					land[i][base].TR == land[i][base+offset].TR &&
					base + offset < 128 &&
					land[i][base].surfaceLL == land[i][base+offset].surfaceLL &&
					land[i][base].surfaceType == land[i][base+offset].surfaceType)
					offset++;

				//TL
				v.x = i * UNITWIDTH;
				v.y = land[i][j].BR * UNITHEIGHT;
				v.z = j * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 0.0f;
				tex.z = 0.0f;

				surface->addVertex(v, tex);

				//TR
				v.x = (i + 1 + offset) * UNITWIDTH;
				v.y = land[i][j].BL * UNITHEIGHT;
				v.z = j * UNITWIDTH;

				tex.x = (float)offset;
				tex.y = 0.0f;

				surface->addVertex(v, tex);

				//BR
				v.x = (i + 1 + offset) * UNITWIDTH;
				v.y = land[i][j].TL * UNITHEIGHT;
				v.z = (j + 1) * UNITWIDTH;

				tex.x = (float)offset;
				tex.y = 1.0f;
				
				surface->addVertex(v, tex);

				//BL
				v.x = i * UNITWIDTH;
				v.y = land[i][j].TR * UNITHEIGHT;
				v.z = (j + 1) * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 1.0f;

				surface->addVertex(v, tex);

				
				//assign the texture
				if(land[i][j].surfaceLL)
					surface->setTextureID(surfaceTextures[8 + land[i][j].surfaceType]);
				else
					surface->setTextureID(surfaceTextures[land[i][j].surfaceType]);

				//assign the pointer to all of the appropriate surfaces
				for(k=0; k<offset; k++)
					land[i][j+k].surface = surface;

				//move j
				j+= (offset - 1);

				numPolys++;
				totalPolys += offset;
			}
			else
			{
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

				land[i][j].surface = surface;

				numPolys++;
				totalPolys++;
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
	uchar i, j, k;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	DebugLog::beginTask((string)"RCTGLLandscape::compileWater()");

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			//add the water if necessary
			if(land[i][j].TR < land[i][j].waterLevel ||
				land[i][j].BR < land[i][j].waterLevel ||
				land[i][j].BL < land[i][j].waterLevel ||
				land[i][j].TL < land[i][j].waterLevel)
			{
				RCTGLLandscapePoly *waterSurface = new RCTGLLandscapePoly;

				RCTGLVertex v, tex;

				waterSurface->setBaseRGB(rgb);

				//TL
				v.x = i * UNITWIDTH;
				v.y = land[i][j].waterLevel * UNITHEIGHT;
				v.z = j * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 0.0f;
				tex.z = 0.0f;

				waterSurface->addVertex(v, tex);

				//TR
				v.x = (i + 1) * UNITWIDTH;				
				v.z = j * UNITWIDTH;

				tex.x = 1.0f;
				tex.y = 0.0f;

				waterSurface->addVertex(v, tex);

				//BR
				v.x = (i + 1) * UNITWIDTH;				
				v.z = (j + 1) * UNITWIDTH;

				tex.x = 1.0f;
				tex.y = 1.0f;
				
				waterSurface->addVertex(v, tex);

				//BL
				v.x = i * UNITWIDTH;				
				v.z = (j + 1) * UNITWIDTH;

				tex.x = 0.0f;
				tex.y = 1.0f;

				waterSurface->addVertex(v, tex);

				waterSurface->setTextureID(waterTexture);

				land[i][j].waterSurface = waterSurface;

				numPolys++;
				totalPolys++;

				/*
				if(land[i][j].TR < land[i][j].waterLevel &&
					land[i][j].BR < land[i][j].waterLevel &&
					land[i][j].BL < land[i][j].waterLevel &&
					land[i][j].TL < land[i][j].waterLevel)
				{
					land[i][j].surface = NULL;
					delete land[i][j].surface;
				}
				*/
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
			
			if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
					(float)((land[i][j].lowest * UNITHEIGHT) - 0.1f),
					(float)(j*UNITWIDTH),
					(float)UNITWIDTH,
					(float)((land[i][j].highest - land[i][j].lowest) * UNITHEIGHT + 0.2f),					
					(float)(UNITWIDTH)))
					
			{
				if(land[i][j].surface && !land[i][j].surface->wasDrawn)
				{
					land[i][j].surface->draw();
					land[i][j].surface->wasDrawn = true;
				}

				if(land[i][j].waterSurface && !land[i][j].waterSurface->wasDrawn)
				{
					land[i][j].waterSurface->draw();
					land[i][j].waterSurface->wasDrawn = true;
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

