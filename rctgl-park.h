#ifndef RCTGL_PARK_H
#define RCTGL_PARK_H

#include "rctgl.h"
#include "rctgl-landscape.h"
#include "rctgl-path.h"
#include "rctgl-scenery.h"

#include <vector>

//determines what each 8-byte block describes
#define SEGMENT_LANDSCAPE		0x00
#define SEGMENT_PATH			0x01
#define SEGMENT_ELEMENT			0x02	
#define SEGMENT_SCENERY_SINGLE	0x03
#define SEGMENT_ENTRANCE		0x04
#define SEGMENT_WALL			0x05
#define SEGMENT_SCENERY_MULTI	0x06
#define SEGMENT_BANNER			0x07

//MSB on a single byte
#define SEGMENT_LAST			0x80

#define MAX_GAME_DATA			0x6000F //393231

#define PARK_MAX_NAMES			1024
#define PARK_NAME_SIZE			32

#define SV4_NAME_START			0x19B89C

using namespace std;

class RCTGLPark
{
public:
	RCTGLPark(void);
	bool loadPark(const string &filename);
	bool clearPark(void);
	char * getName(int index);
	void loadTextures(void);
	void draw(void);

private:
	uchar sizeX, sizeZ;

	RCTGLLandscape landscape;
	RCTGLPathSystem paths;
	
	/*
	vector <RCTGLScenery> sceneryList[128][128];
	vector <RCTGLElement> elementList[128][128];
	vector <RCTGLEntrance> entranceList[128][128];
	vector <RCTGLBanner> bannerList[128][128];
	*/

	vector <char*> rideNameList;

	bool uncompressFile(const string &inFile, const string &outFile);
	bool loadNames(uchar *parkData);
	void unloadNames(void);
};

#endif