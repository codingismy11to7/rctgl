#define WHOLE_TILE	00
#define SW_QUAD		00
#define NW_QUAD		01
#define NE_QUAD		02
#define SE_QUAD		03

#define FACES_WEST	00
#define FACES_NORTH	01
#define FACES_EAST	02
#define FACES_SOUTH	03

class RCTGLScenery
{
public:
	unsigned char baseQuad;
	unsigned char faceDirection;
	unsigned char baseHeight;
	unsigned char sceneryType;
	unsigned char index;
	unsigned char color;

	RCTGLScenery(void);
	bool loadOffset(unsigned char *data);
private:

};