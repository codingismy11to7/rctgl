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
	//what type of element are we drawing
	const uchar MULTI_TILE	=0;		//xxxxxxx0
	const uchar SINGLE_TILE	=1;		//xxxxxxx1
	const uchar TILE_TYPE_MASK = 1;	//00000001

	//where on the tile is it?
	//since this is a unique value, we can combine bits
	const uchar WHOLE_TILE	=4;		//xxxx000x
	const uchar SW_QUAD		=8;		//xxxx001x
	const uchar NW_QUAD		=12;	//xxxx010x
	const uchar NE_QUAD		=16;	//xxxx011x
	const uchar SE_QUAD		=20;	//xxxx100x
	const uchar QUAD_TYPE_MASK = 14;//00001110

	//which direction does the object face?
	//since this can only be one combination, we
	//can combine bits
	const uchar FACES_WEST	=00;	//xx00xxxx
	const uchar FACES_NORTH	=16;	//xx01xxxx
	const uchar FACES_EAST	=32;	//xx10xxxx
	const uchar FACES_SOUTH	=48;	//xx11xxxx
	const uchar FACE_MASK	=48;	//00110000

	const uchar numTreeObjects = 41;
	const uchar treeList[] = {
						0x00,
						0x01,
						0x02,
						0x03,
						0x04,
						0x05,
						0x06,
						0x07,
						0x0F,
						0x11,
						0x12,
						0x13,
						0x14,
						0x16,
						0x18,
						0x19,
						0x1A,
						0x1B,
						0x1D,
						0x1E,
						0x1F,
						0x20,
						0x21,
						0x22,
						0x24,
						0x25,
						0x26,
						0x27,
						0x28,
						0x29,
						0x2A,
						0x34,
						0x36,
						0x37,
						0x66,
						0x77,
						0x80,
						0x81,
						0x82,
						0x83,
						0x84};

}

enum sceneryTypes {SCENERY_TREE, SCENERY_MODEL, SCENERY_BILLBOARD};

struct RCTGLSceneryElement
{
	uchar descriptor;
	uchar baseHeight;
	uchar itemHeight;
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
	bool loadOffset(uchar *data, uchar x, uchar z, uchar tileType);
	void compile();
	void draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const;
	void clear();
	void loadTextures();

private:
	map<uchar, unsigned int> m_treeTextures;

	void loadTreeTextures();
	void loadFlowerTextures();

	bool isItemTree(uchar type);
};

#endif