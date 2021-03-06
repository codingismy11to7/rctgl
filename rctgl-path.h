#ifndef RCTGL_PATH_H
#define RCTGL_PATH_H

#include "rctgl.h"
#include "rctgl-texman.h"
#include "rctgl-poly.h"
#include <vector>
#include <map>

using namespace std;

namespace RCTPath {

// Structure of pathModifier1
// Bits 0-1: Path subtype
// Bits 2-4: Path type
// Bits 5-7: Unused
const uchar BLUE_QUEUE	=	0;			//xxxxxx00
const uchar RED_QUEUE	=	1;			//xxxxxx01
const uchar YELLOW_QUEUE=	2;			//xxxxxx10
const uchar GREEN_QUEUE	=	3;			//xxxxxx11

const uchar GRAY_TARMAC	=	0;			//xxxxxx00
const uchar RED_TARMAC	=	1;			//xxxxxx01
const uchar BROWN_TARMAC=	2;			//xxxxxx10
const uchar GREEN_TARMAC=	3;			//xxxxxx11

const uchar PLAIN_TILE	=	0;			//xxxxxx00
const uchar GRAY_TILE	=	1;			//xxxxxx01
const uchar RED_TILE	=	2;			//xxxxxx10
const uchar GREEN_TILE	=	3;			//xxxxxx11

const uchar CRAZY_TILE	=	0;			//xxxxxx00

const uchar BROWN_DIRT	=	0;			//xxxxxx00
const uchar BLACK_DIRT	=	1;			//xxxxxx01

const uchar PATH_SUBTYPE_MASK = 3;		//xxxxxx11

const uchar PATH_STYLE_QUEUE		=0;	//xxxx000xx
const uchar PATH_STYLE_TARMAC		=4;	//xxxx001xx
const uchar PATH_STYLE_DIRT			=8;	//xxxx010xx
const uchar	PATH_STYLE_CRAZY_TILE	=12;//xxxx011xx
const uchar PATH_STYLE_ROAD			=16;//xxxx100xx
const uchar PATH_STYLE_TILE			=20;//xxxx101xx
const uchar PATH_STYLE_MASK			=28;//xxxx111xx

// Structure of pathModifier2
// Bits 0-1: Support type
// Bits 2-4: Path slope
// Bit 5: Queue entry
// Bits 4-7: Unused
const uchar NORMAL_SUPPORT=	0;			//xxxxxx00
const uchar WOOD_SUPPORT=	1;			//xxxxxx01
const uchar STEEL_SUPPORT=	2;			//xxxxxx10
const uchar BAMBOO_SUPPORT=	3;			//xxxxxx11


const uchar PATH_SLOPE_NONE	=	0;		//xxx000xx
const uchar PATH_SLOPE_WEST	=	8;		//xxx001xx
const uchar PATH_SLOPE_NORTH=	12;		//xxx010xx
const uchar PATH_SLOPE_EAST	=	16;		//xxx100xx
const uchar PATH_SLOPE_SOUTH=	20;		//xxx101xx
const uchar PATH_SLOPE_MASK=	28;		//xxx111xx

const uchar PATH_QUEUE_ENTRY=	32;		//xx1xxxxx


//structure of pathExtras
// Bits 0-3: item on path
// Bits 4-7: which face does the mod apply to (pre-render optimization)
// Bit 4: does mod apply to north face
// Bit 5: does mod apply to south face
// Bit 6: does mod apply to east face
// Bit 7: does mod apply to west face
const uchar MOD_NONE					=0x00;
const uchar MOD_SINGLE_LAMP				=0x01;
const uchar MOD_TRIPLE_LAMP				=0x02;
const uchar MOD_LITTER_BIN				=0x03;
const uchar MOD_BENCH					=0x04;
const uchar MOD_JUMPING_FOUNTAINS		=0x05;
const uchar MOD_EGYPT_LAMP				=0x06;
const uchar MOD_MARTIAN_LAMP			=0x07;
const uchar MOD_SINGLE_LAMP_VANDALIZED	=0x08;
const uchar MOD_TRIPLE_LAMP_VANDALIZED	=0x09;
const uchar MOD_LITTER_BIN_VANDALIZED	=0x0A;
const uchar MOD_BENCH_VANDALIZED		=0x0B;
const uchar MOD_EGYPT_LAMP_VANDALIZED	=0x0C;
const uchar MOD_MARTIAN_LAMP_VANDALIZED	=0x0D;
const uchar MOD_JUMPING_SNOWBALLS		=0x0E;

const uchar MOD_APPLY_NORTH	=	16;
const uchar MOD_APPLY_SOUTH	=	32;
const uchar MOD_APPLY_EAST	=	64;
const uchar MOD_APPLY_WEST	=	128;

const uchar PATH_EXTEND_SW	=	128;	//10000000
const uchar PATH_EXTEND_SE	=	64;		//01000000
const uchar PATH_EXTEND_NE	=	32;		//00100000
const uchar PATH_EXTEND_NW	=	16;		//00010000
const uchar PATH_EXTEND_S	=	8;		//00001000	
const uchar PATH_EXTEND_E	=	4;		//00000100
const uchar PATH_EXTEND_N	=	2;		//00000010
const uchar PATH_EXTEND_W	=	1;		//00000001

const uchar NUM_MASKS = 14;

}

struct RCTGLPathElement {
	uchar pathModifier1;
	uchar pathModifier2;
	uchar baseHeight;
	uchar pathExtras;
	uchar pathExtensions;

	RCTGLExtendedPoly *surface;

	bool compiled;
};

class RCTGLPathSystem
{
public:	
	vector <RCTGLPathElement> paths[128][128];

	RCTGLPathSystem();
	bool loadOffset(uchar *data, uchar x, uchar z);
	void draw(uchar minX, uchar minZ, uchar maxX, uchar maxZ) const;
	void compile();
	void clear();
	void loadTextures();

private:
	unsigned int m_queueTextures[4][3];	//4 queue types, with three fundamental
										//tiles per queue type
	unsigned int m_otherTextures[6][4][RCTPath::NUM_MASKS];

	void loadPathTextureGroup(uchar index1, uchar index2, char *baseFilename);

	bool isPathLinear(uchar i, uchar j, uchar k) const;
	bool isPathTwoPronged(uchar i, uchar j, uchar k) const;

	bool isPathSame(uchar x1, uchar z1, uchar idx1, uchar x2, uchar z2, uchar idx2) const;

	uchar numCardinals(uchar i, uchar j, uchar k) const;
	uchar numDiagonals(uchar i, uchar j, uchar k) const;
};




#endif
