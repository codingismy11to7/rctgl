#include "rctgl.h"

// Structure of pathModifier1
// Bits 0-1: Path subtype
// Bits 2-4: Path type
// Bits 5-7: Unused
#define BLUE_QUEUE		0			//xxxxxx00
#define RED_QUEUE		1			//xxxxxx01
#define YELLOW_QUEUE	2			//xxxxxx10
#define GREEN_QUEUE		3			//xxxxxx11

#define GRAY_TARMAC		0			//xxxxxx00
#define RED_TARMAC		1			//xxxxxx01
#define BROWN_TARMAC	2			//xxxxxx10
#define GREEN_TARMAC	3			//xxxxxx11

#define PLAIN_TILE		0			//xxxxxx00
#define GRAY_TILE		1			//xxxxxx01
#define RED_TILE		2			//xxxxxx10
#define GREEN_TILE		3			//xxxxxx11

#define CRAZY_TILE		0			//xxxxxx00

#define BROWN_DIRT		0			//xxxxxx00
#define BLACK_DIRT		1			//xxxxxx01

#define PATH_STYLE_QUEUE		0	//xxxx000xx
#define PATH_STYLE_TARMAC		4	//xxxx001xx
#define PATH_STYLE_DIRT			8	//xxxx010xx
#define	PATH_STYLE_CRAZY_TILE	12	//xxxx011xx
#define PATH_STYLE_ROAD			16	//xxxx100xx
#define PATH_STYLE_TILE			20	//xxxx101xx

// Structure of pathModifier2
// Bits 0-1: Support type
// Bits 2-4: Path slope
// Bit 5: Queue entry
// Bits 4-7: Unused
#define NORMAL_SUPPORT	0			//xxxxxx00
#define WOOD_SUPPORT	1			//xxxxxx01
#define STEEL_SUPPORT	2			//xxxxxx10
#define BAMBOO_SUPPORT	3			//xxxxxx11


#define PATH_SLOPE_NONE		0		//xxx000xx
#define PATH_SLOPE_WEST		8		//xxx001xx
#define PATH_SLOPE_NORTH	12		//xxx010xx
#define PATH_SLOPE_EAST		16		//xxx100xx
#define PATH_SLOPE_SOUTH	20		//xxx101xx

#define PATH_QUEUE_ENTRY	32		//xx1xxxxx


//structure of pathExtras
// Bits 0-3: item on path
// Bits 4-7: which face does the mod apply to (pre-render optimization)
// Bit 4: does mod apply to north face
// Bit 5: does mod apply to south face
// Bit 6: does mod apply to east face
// Bit 7: does mod apply to west face
#define MOD_NONE					0x00
#define MOD_SINGLE_LAMP				0x01
#define MOD_TRIPLE_LAMP				0x02
#define MOD_LITTER_BIN				0x03
#define MOD_BENCH					0x04
#define MOD_JUMPING_FOUNTAINS		0x05
#define MOD_EGYPT_LAMP				0x06
#define MOD_MARTIAN_LAMP			0x07
#define MOD_SINGLE_LAMP_VANDALIZED	0x08
#define MOD_TRIPLE_LAMP_VANDALIZED	0x09
#define MOD_LITTER_BIN_VANDALIZED	0x0A
#define MOD_BENCH_VANDALIZED		0x0B
#define MOD_EGYPT_LAMP_VANDALIZED	0x0C
#define MOD_MARTIAN_LAMP_VANDALIZED	0x0D
#define MOD_JUMPING_SNOWBALLS		0x0E

#define MOD_APPLY_NORTH		16
#define MOD_APPLY_SOUTH		32
#define MOD_APPLY_EAST		64
#define MOD_APPLY_WEST		128

#define PATH_EXTEND_SW		128		//10000000
#define PATH_EXTEND_SE		64		//01000000
#define PATH_EXTEND_NE		32		//00100000
#define PATH_EXTEND_NW		16		//00010000
#define PATH_EXTEND_S		8		//00001000	
#define PATH_EXTEND_E		4		//00000100
#define PATH_EXTEND_N		2		//00000010
#define PATH_EXTEND_W		1		//00000001


class RCTGLPath
{
public:
	uchar m_pathModifier1;
	uchar m_pathModifier2;		;
	uchar m_baseHeight;
	uchar m_pathExtras;
	uchar m_pathExtensions;

	RCTGLPath(void);
	bool loadOffset(uchar *data);
	
private:
};




