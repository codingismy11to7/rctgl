#include "rctgl-element.h"

using namespace RCTElement;  //import path constants
using namespace RCTTextureManager;

//#define TEST_OPTIMIZATION

RCTGLElementSystem::RCTGLElementSystem()
{

}


bool RCTGLElementSystem::loadOffset(uchar *data, uchar x, uchar z)
{	
	RCTGLElementElement tmpElement;

	tmpElement.baseHeight = 0;
	tmpElement.itemHeight = 0;

	//if MSB of first bit is set, then item is lift chain
	tmpElement.isLift = (bool)(data[0] & 0x80); //10000000

	//base height = byte 3
	tmpElement.baseHeight = data[2] / 4;

	//item height = byte 4
	tmpElement.itemHeight = data[3] / 4;
	
	//sometimes this value is 0
	//anyone know why?
	if(tmpElement.itemHeight)
		tmpElement.itemHeight -= tmpElement.baseHeight;

	//item id = byte 5
	tmpElement.elementID = data[4];

	//item index = byte 6
	tmpElement.index = data[5];

	//item color code = byte 7
	tmpElement.colorCode = data[6];

	//ride index = byte 8
	tmpElement.rideIndex = data[7];

	m_elementItems[x][z].push_back(tmpElement);

	return true;
}

bool RCTGLElementSystem::isElementSame(RCTGLElementElement sourceElement)
{
	return true;	
}

void RCTGLElementSystem::buildSteelTwister(RCTGLRideSystem rides, RCTGLElementElement *e, uchar x, uchar y)
{
	switch(e->elementID)
	{

	case 0x04:
		if(e->isLift)
		{
			//build a lift for a steel standup/sitdown/floorless twister
			//left and right rails
			//center square beam
			//cross ties (2 per unit)
			//left and right stairs			
			RCTGLRGB rgb;
			RCTGLVertex vert, tx;
			RCTGLPoly poly;
			
			rgb.r = RCTColorsR[rides.m_rides[e->rideIndex].primaryColors[e->colorCode]];
			rgb.g = RCTColorsG[rides.m_rides[e->rideIndex].primaryColors[e->colorCode]];
			rgb.b = RCTColorsB[rides.m_rides[e->rideIndex].primaryColors[e->colorCode]];
			
			//rgb.r = rgb.g = rgb.b = 1.0f;	


			poly.setBaseRGB(rgb);
			poly.setTextureID(m_textures[BM_LIFT_STAIRS]);

			vert.x = (x * UNITWIDTH);
			vert.y = (e->baseHeight * UNITHEIGHT) + 0.1f;
			vert.z = (y * UNITWIDTH);

			tx.x = 1.0f;
			tx.y = 0.0f;
			poly.addVertex(vert, tx);	

			vert.x += UNITWIDTH;
			vert.y += UNITHEIGHT;
			tx.y = 1.0f;	
			poly.addVertex(vert, tx);

			vert.z += UNITWIDTH;	
			tx.x = 0.0f;
			poly.addVertex(vert, tx);

			vert.x -= UNITWIDTH;
			vert.y -= UNITHEIGHT;
			tx.y = 0.0f;	
			poly.addVertex(vert, tx);

			e->surfaces.push_back(poly);

			//left hand rails
			poly.clear();
			poly.setTextureID(m_textures[BM_HAND_RAIL]);
			vert.x = (x * UNITWIDTH);
			vert.y = (e->baseHeight * UNITHEIGHT) + 0.1f;
			vert.z = (y * UNITWIDTH);

			tx.x = 0.0f;
			tx.y = 0.0f;
			poly.addVertex(vert, tx);	

			vert.x += UNITWIDTH;
			vert.y += UNITHEIGHT;
			tx.x = 1.0f;	
			poly.addVertex(vert, tx);

			vert.y += BM_RAIL_HEIGHT;	
			tx.y = 1.0f;
			poly.addVertex(vert, tx);

			vert.x -= UNITWIDTH;
			vert.y -= UNITHEIGHT;
			tx.x = 0.0f;	
			poly.addVertex(vert, tx);

			e->surfaces.push_back(poly);

			//right hand rail
			poly.clear();
			poly.setTextureID(m_textures[BM_HAND_RAIL]);
			vert.x = (x * UNITWIDTH);
			vert.y = (e->baseHeight * UNITHEIGHT) + 0.1f;
			vert.z = ((y + 1)* UNITWIDTH);

			tx.x = 0.0f;
			tx.y = 0.0f;
			poly.addVertex(vert, tx);	

			vert.x += UNITWIDTH;
			vert.y += UNITHEIGHT;
			tx.x = 1.0f;	
			poly.addVertex(vert, tx);

			vert.y += BM_RAIL_HEIGHT;	
			tx.y = 1.0f;
			poly.addVertex(vert, tx);

			vert.x -= UNITWIDTH;
			vert.y -= UNITHEIGHT;
			tx.x = 0.0f;	
			poly.addVertex(vert, tx);

			e->surfaces.push_back(poly);

			//netting under the track

		}

		break;
	}

	//stringstream s;
	//s << "Adding element to (" << (long)x <<", " << (long)(e->baseHeight) << ", " << (long)y << ")";
	//DebugLog::writeToLog(s.str());
}

void RCTGLElementSystem::compile(RCTGLRideSystem rides)
{
	DebugLog::beginTask("RCTGLElementSystem::compile");

	uchar i, j, k;	

	unsigned int actualPolys = 0, renderedPolys = 0;

	RCTGLRGB rgb;
	rgb.r = rgb.g = rgb.b = 1.0f;

	//clear everything
	for(i=0; i<128; i++)	
		for(j=0; j<128; j++)		
			for(k=0; k<m_elementItems[i][j].size(); k++)
				m_elementItems[i][j][k].compiled = false;

	RCTGLElementElement theElement;

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			for(k=0; k<m_elementItems[i][j].size(); k++)
			{
				theElement = m_elementItems[i][j][k];

				if(!theElement.compiled && !theElement.index == 1)
				{
					if(rides.m_rides[theElement.rideIndex].rideType == 0x33)
					{
						buildSteelTwister(rides, &(m_elementItems[i][j][k]), i, j);
					}

					m_elementItems[i][j][k].compiled = true;					
				}
			}
		}
	}

	stringstream x;
	x << "actualPolys: " << actualPolys;
	DebugLog::writeToLog(x.str());

	DebugLog::endTask();
}

void RCTGLElementSystem::draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const
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
			for(k=0; k<m_elementItems[i][j].size(); k++)
				m_elementItems[i][j][k].wasDrawn = false;	
	*/	


	for(i=minX; i<maxX; i++)
	{
		for(j=minZ; j<maxZ; j++)
		{
			for(k=0; k<m_elementItems[i][j].size(); k++)
			{
				/*
				if(theFrustum.isCubeInFrustum((float)(i*UNITWIDTH),
					(float)(m_elementItems[i][j][k].baseHeight * UNITHEIGHT),
					(float)(j*UNITWIDTH),
					(float)(UNITWIDTH),
					(float)(m_elementItems[i][j][k].itemHeight) * UNITHEIGHT,
					(float)(UNITWIDTH)))	
				*/
				{
					for(l=0; l<m_elementItems[i][j][k].surfaces.size(); l++)
					{						
						m_elementItems[i][j][k].surfaces[l].draw();
					}
				}				
			}
		}
	}

	glEnable(GL_CULL_FACE);
	glDisable(GL_ALPHA_TEST);	
}

void RCTGLElementSystem::clear()
{
	DebugLog::beginTask("RCTGLElementSystem::clear");

	for(uchar i=0; i<128; i++)
	{
		for(uchar j=0; j<128; j++)
		{
			for(uchar k=0; k<m_elementItems[i][j].size(); k++)
			{
				/*
				for(uchar l=0; l<m_elementItems[i][j][k].surfaces.size(); l++)
				{
					delete m_elementItems[i][j][k].surfaces[l];
				}
				*/

				m_elementItems[i][j][k].surfaces.clear();
			}

			m_elementItems[i][j].clear();
		}
	}

	DebugLog::endTask();
}

void RCTGLElementSystem::loadTextures()
{
	RCTGLTextureManager texMan;

	DebugLog::beginTask("RCTGLElementSystem::loadTextures");

	m_textures[BM_LIFT_STAIRS] = texMan.addTexture("\\elements\\BM-LiftStairs.tga", 0);
	m_textures[BM_HAND_RAIL] = texMan.addTexture("\\elements\\BM-HandRail.tga", 0);

	DebugLog::endTask();
}
