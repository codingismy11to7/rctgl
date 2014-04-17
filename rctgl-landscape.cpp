#include "rctgl-landscape.h"
#include "rctgl-texman.h"


RCTGLLandscape::RCTGLLandscape(void)
{
	clear();
}

void RCTGLLandscape::loadTextures(void)
{
	RCTGLTextureManager texMan;

	RCTGLLog.beginTask("RCTGLLandscape::loadTextures");

	//non LL surfaces
	surfaceTextures[GRASS_TILE] = texMan.addTexture("\\surfaces\\grass4b.tga", 0);
	surfaceTextures[SAND_TILE] = texMan.addTexture("\\surfaces\\sand1.tga", 0);
	surfaceTextures[DIRT_TILE] = texMan.addTexture("\\surfaces\\dirt1.tga", 0);
	surfaceTextures[ROCK_TILE] = texMan.addTexture("\\surfaces\\gravel1.tga", 0);
	surfaceTextures[MARTIAN_TILE] = texMan.addTexture("\\surfaces\\mars1.tga", 0);
	surfaceTextures[CHECKER_TILE] = texMan.addTexture("\\surfaces\\checker1.tga", 0);
	surfaceTextures[JUNGLE_TILE] = texMan.addTexture("\\surfaces\\jungle1.tga", 0);
	surfaceTextures[ROOF_TILE] = texMan.addTexture("\\surfaces\\roofing1.tga", 0);	

	// LL surfaces
	surfaceTextures[8 + GREEN_GRID] = texMan.addTexture("\\surfaces\\green1.tga", 0);
	surfaceTextures[8 + PURPLE_GRID] = texMan.addTexture("\\surfaces\\purple1.tga", 0);
	surfaceTextures[8 + YELLOW_GRID] = texMan.addTexture("\\surfaces\\yellow1.tga", 0);
	surfaceTextures[8 + RED_GRID] = texMan.addTexture("\\surfaces\\red1.tga", 0);
	surfaceTextures[8 + GRAY_ROOF] = texMan.addTexture("\\surfaces\\grey1.tga", 0);
	surfaceTextures[8 + IRON_ROOF] = texMan.addTexture("\\surfaces\\iron1.tga", 0);
	surfaceTextures[8 + LOG_ROOF] = texMan.addTexture("\\surfaces\\log1.tga", 0);
	surfaceTextures[8 + ICE_TILE] = texMan.addTexture("\\surfaces\\icetop1.tga", 0);
	
	// non LL edges
	edgeTextures[WOOD_EDGE] = texMan.addTexture("\\edges\\wood1.tga", 0);
	edgeTextures[ROCK_EDGE] = texMan.addTexture("\\edges\\dirtwall.tga", 0);
	edgeTextures[BRICK_EDGE] = texMan.addTexture("\\edges\\bricks.tga", 0);
	edgeTextures[IRON_EDGE] = texMan.addTexture("\\edges\\rustwall.tga", 0);
	edgeTextures[BLACK_WALL] = texMan.addTexture("\\edges\\darkwall.tga", 0);
	edgeTextures[GRAY_WALL] = texMan.addTexture("\\edges\\greywall.tga", 0);
	edgeTextures[YELLOW_WALL] = texMan.addTexture("\\edges\\yelwall.tga", 0);
	edgeTextures[RED_WALL] = texMan.addTexture("\\edges\\redwall.tga", 0);

	//LL edges
	edgeTextures[8 + ICE_WALL] = texMan.addTexture("\\edges\\icewall.tga", 0);
	edgeTextures[8 + PURPLE_WALL] = texMan.addTexture("\\edges\\purwall.tga", 0);
	edgeTextures[8 + GREEN_WALL] = texMan.addTexture("\\edges\\grnwall.tga", 0);
	edgeTextures[8 + BROWN_STONE] = texMan.addTexture("\\edges\\brstwall.tga", 0);
	edgeTextures[8 + GRAY_STONE] = texMan.addTexture("\\edges\\grstwall.tga", 0);
	edgeTextures[8 + SKYSCRAPER_A] = texMan.addTexture("\\edges\\skyawall.tga", 0);
	edgeTextures[8 + SKYSCRAPER_B] = texMan.addTexture("\\edges\\skybwall.tga", 0);

	//water
	waterTexture = texMan.loadTex("\\surfaces\\water1.tga", 0);

	RCTGLLog.endTask();
}

void RCTGLLandscape::clear(void)
{
	RCTGLLog.beginTask("RCTGLLandscape::clear");

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
		}
	}

	RCTGLLog.endTask();
}

bool RCTGLLandscape::loadOffset(unsigned char *gameData, int x, int y)
{
	unsigned char buffer;

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
	buffer = gameData[3];
	land[x][y].edgeType = ((buffer & 0xE0) >> 5);

	//get the height of each corner by masking with 00011111
	buffer = gameData[3];
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
	buffer = gameData[3];
	land[x][y].waterLevel = (buffer & 0x1F);

	//precalcualte the optimizations
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

	return true;
}


void RCTGLLandscape::compile(void)
{
	for(int i=0; i<128; i++)
	{
		for(int j=0; j<128; j++)
		{
			//create the surface
			RCTGLPoly *surface = new RCTGLPoly;

			RCTGLVertex v;

			RCTGLRGB rgb;
			rgb.r = rgb.g = rgb.b = 1.0f;
			surface->setBaseRGB(rgb);

			//TL
			v.x = i * UNITWIDTH;
			v.y = land[i][j].TL * UNITHEIGHT;
			v.z = j * UNITWIDTH;
			surface->addVertex(v);

			//TR
			v.x = (i + 1) * UNITWIDTH;
			v.y = land[i][j].TR * UNITHEIGHT;
			v.z = j * UNITWIDTH;
			surface->addVertex(v);

			//BR
			v.x = (i + 1) * UNITWIDTH;
			v.y = land[i][j].BR * UNITHEIGHT;
			v.z = (j + 1) * UNITWIDTH;
			surface->addVertex(v);

			//BL
			v.x = i * UNITWIDTH;
			v.y = land[i][j].BL * UNITHEIGHT;
			v.z = (j + 1) * UNITWIDTH;
			surface->addVertex(v);
			
			
			if(land[i][j].surfaceLL)
				surface->setTextureID(surfaceTextures[8 + land[i][j].surfaceType]);
			else
				surface->setTextureID(surfaceTextures[land[i][j].surfaceType]);

			
			land[i][j].surface = surface;
		}
	}
}



bool RCTGLLandscape::draw(unsigned char x1, unsigned char z1, unsigned char x2, unsigned char z2)
{
	//glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);

	bool drawUnderwater = true;

	//this assumes that x1 < x2 and z1 < z2
	if((x1 > x2) || (z1 > z2))
		return false;
	
	unsigned char i, j, k;
	

	// draw the map
	for(i=x1; i<x2; i++)
	{
		for(j=z1; j<z2; j++)
		{
			land[i][j].surface->draw();

			/*
			for(k=0; k<4; k++)
			{
				land[i][j].edge[k]->draw();
			}
			*/			
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

