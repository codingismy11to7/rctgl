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

	//lower 2 bits indicate element rotation
	tmpElement.rotation = (data[0] & 0x03);		//00000011

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

void RCTGLElementSystem::addBMNormalCrosstie(RCTGLElementElement *e, RCTGLRGB color, float xOffset, float top, float bottom, float left, float right)
{
	RCTGLVertex vert, tx;
	RCTGLPoly poly;

	poly.clear();
	poly.setBaseRGB(color);

	poly.setTextureID(m_textures[BM_NORMAL_CROSSTIE]);

	poly.needsAlpha = true;

	//go in z direction
	vert.x = xOffset;
	vert.y = bottom;
	vert.z = right;

	tx.x = 0.0f;
	tx.y = 0.0f;
	poly.addVertex(vert, tx);	

	vert.z += (left - right);
	//vert.y += UNITHEIGHT;
	tx.x = 1.0f;	
	poly.addVertex(vert, tx);

	vert.y += (top - bottom);	
	tx.y = 1.0f;
	poly.addVertex(vert, tx);

	vert.z -= (left - right);
	//vert.y -= UNITHEIGHT;
	tx.x = 0.0f;	
	poly.addVertex(vert, tx);

	e->obj.addPoly(poly);
}

void RCTGLElementSystem::addBMLiftCrosstie(RCTGLElementElement *e, RCTGLRGB color, float xOffset, float top, float bottom, float left, float right)
{
	RCTGLVertex vert, tx;
	RCTGLPoly poly;

	poly.clear();
	poly.setBaseRGB(color);

	poly.setTextureID(m_textures[BM_LIFT_CROSSTIE]);

	poly.needsAlpha = true;

	//go in z direction
	vert.x = xOffset;
	vert.y = bottom;
	vert.z = right;

	tx.x = 0.0f;
	tx.y = 0.0f;
	poly.addVertex(vert, tx);	

	vert.z += (left - right);
	//vert.y += UNITHEIGHT;
	tx.x = 1.0f;	
	poly.addVertex(vert, tx);

	vert.y += (top - bottom);	
	tx.y = 1.0f;
	poly.addVertex(vert, tx);

	vert.z -= (left - right);
	//vert.y -= UNITHEIGHT;
	tx.x = 0.0f;	
	poly.addVertex(vert, tx);

	e->obj.addPoly(poly);
}

void RCTGLElementSystem::addStraightRail(RCTGLElementElement *e, RCTGLRGB color, float height, float length, float radius, float z)
{
	RCTGLPoly poly;
	RCTGLVertex vert;

	poly.setBaseRGB(color);

	//go in positive x direction

	//top right corner
	//start at top center of rail
	vert.x = 0.0f;
	vert.y = 0.0f + height + 2.0f * radius;
	vert.z = 0.0f + z;
	poly.addVertex(vert);

	vert.y -= radius;
	vert.z -= radius;
	poly.addVertex(vert);

	vert.x += length;
	poly.addVertex(vert);

	vert.y += radius;
	vert.z += radius;
	poly.addVertex(vert);

	e->obj.addPoly(poly);
	

	//top left corner	
	poly.clear();
	vert.x = 0.0f;
	vert.y = 0.0f + height + 2.0f * radius;
	vert.z = 0.0f + z;
	poly.addVertex(vert);

	vert.y -= radius;
	vert.z += radius;
	poly.addVertex(vert);

	vert.x += length;
	poly.addVertex(vert);

	vert.y += radius;
	vert.z -= radius;
	poly.addVertex(vert);

	e->obj.addPoly(poly);
}

void RCTGLElementSystem::addBMHandrail(RCTGLElementElement *e, RCTGLRGB rgb, float z, float length, float baseHeight)
{	
	RCTGLVertex vert, tx;
	RCTGLPoly poly;

	poly.clear();
	poly.setBaseRGB(rgb);

	poly.setTextureID(m_textures[BM_HAND_RAIL]);

	poly.needsAlpha = true;

	vert.x = 0.0f;
	vert.y = baseHeight;
	vert.z = z;

	tx.x = 0.0f;
	tx.y = 0.0f;
	poly.addVertex(vert, tx);	

	vert.x += length;
	//vert.y += UNITHEIGHT;
	tx.x = 1.0f;	
	poly.addVertex(vert, tx);

	vert.y += BM_RAIL_HEIGHT;	
	tx.y = 1.0f;
	poly.addVertex(vert, tx);

	vert.x -= length;
	//vert.y -= UNITHEIGHT;
	tx.x = 0.0f;	
	poly.addVertex(vert, tx);

	e->obj.addPoly(poly);
}

void RCTGLElementSystem::addBMLiftBeam(RCTGLElementElement *e, RCTGLRGB rgb, float z1, float z2, float length, float baseHeight)
{
	RCTGLVertex vert, tx;
	RCTGLPoly poly;

	poly.setBaseRGB(rgb);
	poly.setTextureID(m_textures[BM_LIFT_BEAM]);
	poly.needsAlpha = true;

	vert.x = 0.0f;
	vert.y = baseHeight;
	vert.z = z1;

	tx.x = 1.0f;
	tx.y = 0.0f;
	poly.addVertex(vert, tx);	

	vert.x += length;
	//vert.y += UNITHEIGHT;
	tx.y = 1.0f;	
	poly.addVertex(vert, tx);

	vert.z = z2;	
	tx.x = 0.0f;
	poly.addVertex(vert, tx);

	vert.x -= length;
	//vert.y -= UNITHEIGHT;
	tx.y = 0.0f;	
	poly.addVertex(vert, tx);

	e->obj.addPoly(poly);
}


void RCTGLElementSystem::addBMStairs(RCTGLElementElement *e, RCTGLRGB rgb, float z1, float z2, float length, float baseHeight)
{
	RCTGLVertex vert, tx;
	RCTGLPoly poly;

	poly.setBaseRGB(rgb);
	poly.setTextureID(m_textures[BM_LIFT_STAIRS]);
	poly.needsAlpha = true;

	vert.x = 0.0f;
	vert.y = baseHeight;
	vert.z = z1;

	tx.x = 1.0f;
	tx.y = 0.0f;
	poly.addVertex(vert, tx);	

	vert.x += length;
	//vert.y += UNITHEIGHT;
	tx.y = 1.0f;	
	poly.addVertex(vert, tx);

	vert.z = z2;	
	tx.x = 0.0f;
	poly.addVertex(vert, tx);

	vert.x -= length;
	//vert.y -= UNITHEIGHT;
	tx.y = 0.0f;	
	poly.addVertex(vert, tx);

	e->obj.addPoly(poly);
}

void RCTGLElementSystem::buildSteelTwister(RCTGLRideSystem *rides, RCTGLElementElement *e, uchar x, uchar y)
{
	const float leftRail = 0.70f * UNITWIDTH;
	const float rightRail = 0.30f * UNITWIDTH;
	const float leftBeam = 0.55f * UNITWIDTH;
	const float rightBeam = 0.45f * UNITWIDTH;
	const float railRadius = 0.025f * UNITWIDTH;
	const float railHeight = 0.9f;

	const float singleAngle = tan(UNITHEIGHT / UNITWIDTH) * (360.0f / (2.0f * M_PI)) - 2.75f;
	//const float singleAngle = 25.0f;
	const float singleAngleLen = sqrt(UNITWIDTH*UNITWIDTH + UNITHEIGHT*UNITHEIGHT);

	const float doubleAngle = tan(4.0f * UNITHEIGHT / UNITWIDTH) * (360.0f / (2.0f * M_PI)) - 2.75f;	
	const float doubleAngleLen = sqrt(UNITWIDTH*UNITWIDTH + 4.0f*UNITHEIGHT*4.0f*UNITHEIGHT);

	RCTGLRGB primaryRGB, secondaryRGB;
	primaryRGB.r = RCTColorsR[rides->m_rides[e->rideIndex].primaryColors[e->colorCode]];
	primaryRGB.g = RCTColorsG[rides->m_rides[e->rideIndex].primaryColors[e->colorCode]];
	primaryRGB.b = RCTColorsB[rides->m_rides[e->rideIndex].primaryColors[e->colorCode]];

	secondaryRGB.r = RCTColorsR[rides->m_rides[e->rideIndex].secondaryColors[e->colorCode]];
	secondaryRGB.g = RCTColorsG[rides->m_rides[e->rideIndex].secondaryColors[e->colorCode]];
	secondaryRGB.b = RCTColorsB[rides->m_rides[e->rideIndex].secondaryColors[e->colorCode]];

	switch(e->elementID)
	{
	//straight piece
	case 0x00:
	//brake
	case 0x63:
	case 0x44:
	case 0x64:
	case 0x65:
	//station pieces
	case 0x01:
	case 0x02:
	case 0x03:
	{	
		float trackLen = UNITWIDTH;

		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);

		addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
		addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);

		e->obj.translate(RCTGLVertex(x * UNITWIDTH, e->baseHeight * UNITHEIGHT, y * UNITWIDTH));

		//e->obj.rotateAboutCenter(90.0f, false, true, false);

		break;
	}
	//25 degree incline
	case 0x04:
	{		
		float trackLen = singleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);
			
			addBMLiftBeam(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight - 0.5f);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(singleAngle, false, false, true);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}

	//60 degree incline
	case 0x05:
	{		
		float trackLen = doubleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(doubleAngle, false, false, true);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}


	//25 degree decline
	case 0x0A:
	{		
		float trackLen = singleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(-singleAngle, false, false, true);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}

	//60 degree decline
	case 0x0B:
	{		
		float trackLen = doubleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(doubleAngle, false, false, true);
		e->obj.rotateAboutCenter(180.0f, false, true, false);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}
	
	} //end switch

	switch(e->rotation)
	{
	case 0x00:
		e->obj.rotateAboutCenter(90.0f, false, true, false);
		break;
	//this is the base case
	case 0x01:
		break;
	case 0x02:
		e->obj.rotateAboutCenter(270.0f, false, true, false);
		break;
	case 0x03:
		e->obj.rotateAboutCenter(180.0f, false, true, false);
		break;
	}

	//stringstream s;
	//s << "Adding element to (" << (long)x <<", " << (long)(e->baseHeight) << ", " << (long)y << ")";
	//DebugLog::writeToLog(s.str());
}

void RCTGLElementSystem::buildInverted(RCTGLRideSystem *rides, RCTGLElementElement *e, uchar x, uchar y)
{
	const float leftRail = 0.70f * UNITWIDTH;
	const float rightRail = 0.30f * UNITWIDTH;
	const float leftBeam = 0.55f * UNITWIDTH;
	const float rightBeam = 0.45f * UNITWIDTH;
	const float railRadius = 0.025f * UNITWIDTH;
	const float railHeight = 0.9f;

	const float singleAngle = tan(UNITHEIGHT / UNITWIDTH) * (360.0f / (2.0f * M_PI)) - 2.75f;
	//const float singleAngle = 25.0f;
	const float singleAngleLen = sqrt(UNITWIDTH*UNITWIDTH + UNITHEIGHT*UNITHEIGHT);

	const float doubleAngle = tan(4.0f * UNITHEIGHT / UNITWIDTH) * (360.0f / (2.0f * M_PI)) - 2.75f;	
	const float doubleAngleLen = sqrt(UNITWIDTH*UNITWIDTH + 4.0f*UNITHEIGHT*4.0f*UNITHEIGHT);

	RCTGLRGB primaryRGB, secondaryRGB;
	primaryRGB.r = RCTColorsR[rides->m_rides[e->rideIndex].primaryColors[e->colorCode]];
	primaryRGB.g = RCTColorsG[rides->m_rides[e->rideIndex].primaryColors[e->colorCode]];
	primaryRGB.b = RCTColorsB[rides->m_rides[e->rideIndex].primaryColors[e->colorCode]];

	secondaryRGB.r = RCTColorsR[rides->m_rides[e->rideIndex].secondaryColors[e->colorCode]];
	secondaryRGB.g = RCTColorsG[rides->m_rides[e->rideIndex].secondaryColors[e->colorCode]];
	secondaryRGB.b = RCTColorsB[rides->m_rides[e->rideIndex].secondaryColors[e->colorCode]];

	switch(e->elementID)
	{
	//straight piece
	case 0x00:
	//brake
	case 0x63:
	case 0x44:
	case 0x64:
	case 0x65:
	//station pieces
	case 0x01:
	case 0x02:
	case 0x03:
	{	
		float trackLen = UNITWIDTH;

		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);

		//addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
		//addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);

		e->obj.translate(RCTGLVertex(x * UNITWIDTH, e->baseHeight * UNITHEIGHT, y * UNITWIDTH));

		//e->obj.rotateAboutCenter(90.0f, false, true, false);

		break;
	}
	//25 degree incline
	case 0x04:
	{		
		float trackLen = singleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			//addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			//addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			//addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			//addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(singleAngle, false, false, true);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}

	//60 degree incline
	case 0x05:
	{		
		float trackLen = doubleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			//addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			//addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(doubleAngle, false, false, true);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}


	//25 degree decline
	case 0x0A:
	{		
		float trackLen = singleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			//addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			//addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(-singleAngle, false, false, true);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}

	//60 degree decline
	case 0x0B:
	{		
		float trackLen = doubleAngleLen;

		RCTGLVertex vert, tx;
		RCTGLPoly poly;

		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, rightRail);
		//addStraightRail(e, secondaryRGB, railHeight, trackLen, railRadius, leftRail);
		
		
		if(e->isLift)
		{			
			addBMHandrail(e, primaryRGB, 0.05f * UNITWIDTH, trackLen, railHeight);
			addBMHandrail(e, primaryRGB, 0.95f * UNITWIDTH, trackLen, railHeight);

			addBMStairs(e, primaryRGB, 0.05f * UNITWIDTH, 0.95f * UNITWIDTH, singleAngleLen, railHeight);

			addBMLiftCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			addBMLiftCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			
		}
		else
		{
			//addBMNormalCrosstie(e, primaryRGB, 0.25f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);
			//addBMNormalCrosstie(e, primaryRGB, 0.75f * trackLen, railHeight, railHeight - 0.5f, leftRail, rightRail);			

		}
		
		e->obj.rotateAboutCenter(doubleAngle, false, false, true);
		e->obj.rotateAboutCenter(180.0f, false, true, false);
		e->obj.translate(RCTGLVertex(x * UNITWIDTH, (e->baseHeight + 1.0f) * UNITHEIGHT, y * UNITWIDTH));

		break;
	}
	
	} //end switch

	switch(e->rotation)
	{
	case 0x00:
		e->obj.rotateAboutCenter(90.0f, false, true, false);
		break;
	//this is the base case
	case 0x01:
		break;
	case 0x02:
		e->obj.rotateAboutCenter(270.0f, false, true, false);
		break;
	case 0x03:
		e->obj.rotateAboutCenter(180.0f, false, true, false);
		break;
	}

	//stringstream s;
	//s << "Adding element to (" << (long)x <<", " << (long)(e->baseHeight) << ", " << (long)y << ")";
	//DebugLog::writeToLog(s.str());
}

void RCTGLElementSystem::compile(RCTGLRideSystem *rides)
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

	RCTGLElementElement *theElement;
	vector<RCTGLElementElement>::iterator it1;

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			for(it1=m_elementItems[i][j].begin(); it1!=m_elementItems[i][j].end(); it1++)
			{
				theElement = &(*it1);

				//if(!theElement->compiled) // && (theElement.index == 1 || theElement.index == 0))
				{
					if(rides->m_rides[theElement->rideIndex].rideType == 0x33)
					{
						buildSteelTwister(rides, theElement, i, j);
					}
					else if(rides->m_rides[theElement->rideIndex].rideType == 0x03)
					{
						buildInverted(rides, theElement, i, j);
					}

					theElement->compiled = true;					
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
	//glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);

	//initialize all polygons
	/*
	for(i=minX; i<maxX; i++)	
		for(j=minZ; j<maxZ; j++)
			for(k=0; k<m_elementItems[i][j].size(); k++)
				m_elementItems[i][j][k].wasDrawn = false;	
	*/	


	//for(i=minX; i<maxX; i++)
	for(i=0; i<128; i++)
	{
		//for(j=minZ; j<maxZ; j++)
		for(j=0; j<128; j++)
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
					m_elementItems[i][j][k].obj.draw();					
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

				m_elementItems[i][j][k].obj.clear();
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
	m_textures[BM_LIFT_NETTING] = texMan.addTexture("\\elements\\netting.tga", 0);
	m_textures[BM_NORMAL_CROSSTIE] = texMan.addTexture("\\elements\\BM-normalCrosstie.tga", 0);
	m_textures[BM_LIFT_CROSSTIE] = texMan.addTexture("\\elements\\BM-liftCrosstie.tga", 0);
	m_textures[BM_LIFT_BEAM] = texMan.addTexture("\\elements\\BM-liftBeam.tga", 0);

	DebugLog::endTask();
}
