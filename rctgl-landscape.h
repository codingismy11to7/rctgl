#include "rctgl.h"
#include "rctgl-poly.h"
#include <map>

//standard tiles
#define GRASS_TILE		0	//000xxxxx
#define SAND_TILE		1	//001xxxxx
#define DIRT_TILE		2	//010xxxxx
#define ROCK_TILE		3	//011xxxxx
#define MARTIAN_TILE	4	//100xxxxx
#define CHECKER_TILE	5	//101xxxxx
#define JUNGLE_TILE		6	//110xxxxx
#define ROOF_TILE		7	//111xxxxx

//LL tiles
#define ICE_TILE		0	//000xxxxx
#define LOG_ROOF		1	//001xxxxx
#define IRON_ROOF		2	//010xxxxx
#define GRAY_ROOF		3	//011xxxxx
#define RED_GRID		4	//100xxxxx
#define YELLOW_GRID		5	//101xxxxx
#define PURPLE_GRID		6	//110xxxxx
#define GREEN_GRID		7	//111xxxxx

//standard edges
#define ROCK_EDGE		0	//000xxxxx
#define BRICK_EDGE		1	//001xxxxx
#define IRON_EDGE		2	//010xxxxx
#define WOOD_EDGE		3	//011xxxxx
#define GRAY_WALL		4	//100xxxxx
#define YELLOW_WALL		5	//101xxxxx
#define BLACK_WALL		6	//110xxxxx
#define RED_WALL		7	//111xxxxx

//LL edges
#define ICE_WALL		0	//000xxxxx
#define PURPLE_WALL		1	//001xxxxx
#define GREEN_WALL		2	//010xxxxx
#define BROWN_STONE		3	//011xxxxx
#define GRAY_STONE		4	//100xxxxx
#define SKYSCRAPER_A	5	//101xxxxx
#define SKYSCRAPER_B	6	//110xxxxx

#define EDGE_NORTH	0
#define EDGE_SOUTH	1
#define EDGE_EAST	2
#define EDGE_WEST	3


//this class has an extra modifier so we can draw
//large polygons instead of drawing every one individually
class RCTGLLandscapePoly : public RCTGLPoly
{
public:
	bool wasDrawn;
	uchar length, width;
};

struct landscapeElement
{
	int edgeType;
	bool edgeLL;

	int surfaceType;	
	bool surfaceLL;

	int TR, TL, BR, BL;
	int waterLevel;
	int lowest, highest;

	RCTGLExtendedPoly *surface;
	RCTGLExtendedPoly *waterSurface;
	RCTGLExtendedPoly *edges[4];

	bool drawWater;			//this may save some time when rendering
	bool allLandUnderwater;	//this may save some time when rendering
};

class RCTGLLandscape
{
public:
	landscapeElement land[128][128];

	RCTGLLandscape();

	bool load(uchar *gameData);
	bool loadOffset(uchar *gameData, int x, int y);

	void loadTextures();

	void build();
	void compile();

	void clear();
	bool draw(uchar x1, uchar z1, uchar x2, uchar z2) const;

private:

	unsigned int numPolys, totalPolys;
	unsigned int surfaceTextures[16];
	unsigned int edgeTextures[16];
	unsigned int waterTexture;

	float getLowestPoint(int i, int j);
	float getHighestPoint(int i, int j);

	void compileSurfaces(void);
	void compileEdges(void);
	void compileWater(void);

	bool isFlatLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isFlatRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isLeftRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isLeftRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isRightRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isRightRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isUpperRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isUpperRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isLowerRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isLowerRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isUpperRightRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isUpperRightRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isUpperLeftRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isUpperLeftRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isLowerRightRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isLowerRightRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isLowerLeftRaisedLandSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isLowerLeftRaisedRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	bool isWaterSame(uchar x1, uchar z1, uchar x2, uchar z2);
	bool isWaterRowSame(uchar startX, uchar startZ, uchar row, uchar width);

	void assignSurfaceToLand(uchar startX, uchar xLen, uchar startZ, uchar zLen, RCTGLExtendedPoly *surface);
	void assignWaterSurfaceToLand(uchar startX, uchar xLen, uchar startZ, uchar zLen, RCTGLExtendedPoly *surface);
	void addVerticiesToSurface(uchar startX, uchar xLen, uchar startZ, uchar zLen, RCTGLExtendedPoly *surface, bool isWater);
};


