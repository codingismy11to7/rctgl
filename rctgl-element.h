#ifndef RCTGL_Element_H
#define RCTGL_Element_H

#include "rctgl.h"
#include "rctgl-texman.h"
#include "rctgl-rides.h"

#include "rctgl-rgb.h"
#include "rctgl-vertex.h"
#include "rctgl-poly.h"


#include <vector>
#include <map>


namespace RCTElement
{
	const float BM_RAIL_HEIGHT	=1.0f;

	const uchar BM_LIFT_STAIRS	=0;
	const uchar BM_HAND_RAIL	=1;
}

struct RCTGLElementElement
{
	uchar baseHeight;
	uchar itemHeight;
	bool isLift;
	uchar elementID;
	uchar index;
	uchar colorCode;
	uchar rideIndex;

	bool compiled;
	bool drawn;

	vector <RCTGLPoly> surfaces;
};


class RCTGLElementSystem
{
public:
	vector <RCTGLElementElement> m_elementItems[128][128];
	RCTGLElementSystem();
	bool loadOffset(uchar *data, uchar x, uchar z);
	void compile(RCTGLRideSystem rideList);
	void draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const;
	void clear();
	void loadTextures();

private:
	map<uchar, unsigned int> m_textures;

	bool isElementSame(RCTGLElementElement sourceElement);
	void buildSteelTwister(RCTGLRideSystem rides, RCTGLElementElement *e, uchar x, uchar y);
};

#endif