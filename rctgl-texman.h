#include "rctgl.h"

#include "depend/corona/corona.h"

namespace RCTTextureManager {

const uchar PATH_NORTH	=1;		//00000001
const uchar PATH_NE		=2;		//00000010
const uchar PATH_EAST	=4;		//00000100
const uchar PATH_SE		=8;		//00001000
const uchar PATH_SOUTH	=16;	//00010000
const uchar PATH_SW		=32;	//00100000
const uchar PATH_WEST	=64;	//01000000
const uchar PATH_NW		=128;	//10000000

const uchar TEXTURE_CLAMP	=1;

}

class RCTGLTextureManager
{
public:
	unsigned int loadPathTex(const string &filename, uchar pathOptions);
	unsigned int loadTex(const string &filename, uchar texOptions);		

	unsigned int addTexture(const string &filepath, uchar texOptions);

private:
	void BGRA2RGBA(uchar *pixels, int w, int h);
	void BGR2RGB(uchar *pixels, int w, int h);

	void buildPathTex(uchar *pixels, int w, int h, unsigned int pathOptions);

	unsigned int addPathTexture(const string &filepath, unsigned int options);	
	
};