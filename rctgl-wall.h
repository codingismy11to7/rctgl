#ifndef RCTGL_Wall_H
#define RCTGL_Wall_H

#include "rctgl.h"
#include "rctgl-texman.h"

#include "rctgl-rgb.h"
#include "rctgl-vertex.h"
#include "rctgl-poly.h"


#include <vector>
#include <map>


namespace RCTWall
{
	const uchar NORTH_EDGE	=0;
	const uchar SOUTH_EDGE	=1;
	const uchar EAST_EDGE	=2;
	const uchar WEST_EDGE	=4;
}

struct RCTGLWallElement
{
	uchar descriptor;
	uchar baseHeight;
	uchar itemHeight;
	uchar WallID;
	WallTypes WallType;
	uchar index;
	uchar color;
	bool compiled;
	bool drawn;

	vector <RCTGLPoly> surfaces;
};


class RCTGLWallSystem
{
public:
	vector <RCTGLWallElement> m_wallItems[128][128];
	RCTGLWallSystem();
	bool loadOffset(uchar *data, uchar x, uchar z);
	void compile();
	void draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const;
	void clear();
	void loadTextures();

private:
	map<uchar, unsigned int> m_textures;
};

#endif