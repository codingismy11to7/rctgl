#include "rctgl.h"

#include "depend/corona/corona.h"

#define PATH_NORTH	1	//00000001
#define PATH_NE		2	//00000010
#define PATH_EAST	4	//00000100
#define PATH_SE		8	//00001000
#define PATH_SOUTH	16	//00010000
#define PATH_SW		32	//00100000
#define PATH_WEST	64	//01000000
#define PATH_NW		128	//10000000

#define TEXTURE_CLAMP	1


class RCTGLTextureManager
{
public:
	void loadPathTex(char *filename, int texNum, uchar pathOptions);
	unsigned int loadTex(char *filename, uchar texOptions);		

	unsigned int addTexture(const char *filepath, uchar texOptions);

private:
	void BGRA2RGBA(uchar *pixels, int w, int h);
	void BGR2RGB(uchar *pixels, int w, int h);

	void buildPathTex(uchar *pixels, int w, int h, unsigned int pathOptions);

	int addPathTexture(const char *filepath, int texID, unsigned int options);	
	
};