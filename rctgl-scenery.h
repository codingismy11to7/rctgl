#ifndef RCTGL_SCENERY_H
#define RCTGL_SCENERY_H

#include "rctgl.h"
#include "rctgl-texman.h"

#include "rctgl-rgb.h"
#include "rctgl-vertex.h"
#include "rctgl-poly.h"


#include <vector>
#include <map>


namespace RCTScenery
{
	const uchar WHOLE_TILE	=00;
	const uchar SW_QUAD		=00;
	const uchar NW_QUAD		=01;
	const uchar NE_QUAD		=02;
	const uchar SE_QUAD		=03;

	const uchar FACES_WEST	=00;
	const uchar FACES_NORTH	=01;
	const uchar FACES_EAST	=02;
	const uchar FACES_SOUTH	=03;
}

enum sceneryTypes {SCENERY_TREE, SCENERY_MODEL, SCENERY_BILLBOARD};

struct RCTGLSceneryElement
{
	uchar baseQuad;
	uchar faceDirection;
	uchar baseHeight;
	uchar clearance;
	uchar sceneryID;
	sceneryTypes sceneryType;
	uchar index;
	uchar color;
	bool compiled;
	bool drawn;

	vector <RCTGLPoly> surfaces;
};


class RCTGLScenerySystem
{
public:
	vector <RCTGLSceneryElement> m_scenItems[128][128];
	RCTGLScenerySystem();
	bool loadOffset(uchar *data, uchar x, uchar z);
	void compile();
	void draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const;
	void clear();
	void loadTextures();

private:
	map<uchar, unsigned int> m_treeTextures;

	void loadTreeTextures();
	void loadFlowerTextures();

};

#endif