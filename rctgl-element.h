#ifndef RCTGL_Element_H
#define RCTGL_Element_H

#include "rctgl.h"
#include "rctgl-texman.h"
#include "rctgl-rides.h"

#include "rctgl-rgb.h"
#include "rctgl-vertex.h"
#include "rctgl-poly.h"

#include "rctgl-object.h"


#include <vector>
#include <map>


namespace RCTElement
{
	const float BM_RAIL_HEIGHT	=1.0f;

	const uchar BM_LIFT_STAIRS		=0;
	const uchar BM_HAND_RAIL		=1;
	const uchar BM_LIFT_NETTING		=2;
	const uchar BM_NORMAL_CROSSTIE	=3;
	const uchar BM_LIFT_CROSSTIE	=4;
	const uchar BM_LIFT_BEAM		=5;
}

struct RCTGLElementElement
{
	uchar rotation;
	uchar baseHeight;
	uchar itemHeight;
	bool isLift;
	uchar elementID;
	uchar index;
	uchar colorCode;
	uchar rideIndex;

	bool compiled;
	bool drawn;

	RCTGLObject obj;
};


class RCTGLElementSystem
{
public:
	vector <RCTGLElementElement> m_elementItems[128][128];
	RCTGLElementSystem();
	bool loadOffset(uchar *data, uchar x, uchar z);
	void compile(RCTGLRideSystem *rideList);
	void draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const;
	void clear();
	void loadTextures();

private:
	map<uchar, unsigned int> m_textures;

	bool isElementSame(RCTGLElementElement sourceElement);
	void buildSteelTwister(RCTGLRideSystem *rides, RCTGLElementElement *e, uchar x, uchar y);
	void buildInverted(RCTGLRideSystem *rides, RCTGLElementElement *e, uchar x, uchar y);

	void addStraightRail(RCTGLElementElement *e, RCTGLRGB color, float height, float length, float radius, float z);
	void addBMHandrail(RCTGLElementElement *e, RCTGLRGB rgb, float z, float length, float baseHeight);
	void addBMStairs(RCTGLElementElement *e, RCTGLRGB rgb, float z1, float z2, float length, float baseHeight);
	void addBMLiftBeam(RCTGLElementElement *e, RCTGLRGB rgb, float z1, float z2, float length, float baseHeight);
	void addBMNormalCrosstie(RCTGLElementElement *e, RCTGLRGB color, float xOffset, float top, float bottom, float left, float right);
	void addBMLiftCrosstie(RCTGLElementElement *e, RCTGLRGB color, float xOffset, float top, float bottom, float left, float right);
};

#endif