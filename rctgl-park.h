#ifndef RCTGL_PARK_H
#define RCTGL_PARK_H

#include "rctgl.h"
#include "rctgl-landscape.h"
#include "rctgl-path.h"
#include "rctgl-scenery.h"

#include <vector>

namespace RCTPark {

//determines what each 8-byte block describes
const uchar SEGMENT_LANDSCAPE		=0x00;
const uchar SEGMENT_PATH			=0x01;
const uchar SEGMENT_ELEMENT			=0x02;	
const uchar SEGMENT_SCENERY_SINGLE	=0x03;
const uchar SEGMENT_ENTRANCE		=0x04;
const uchar SEGMENT_WALL			=0x05;
const uchar SEGMENT_SCENERY_MULTI	=0x06;
const uchar SEGMENT_BANNER			=0x07;

//MSB on a single byte
const uchar SEGMENT_LAST			=0x80;

const unsigned int MAX_GAME_DATA	=0x6000F; //393231

const unsigned short PARK_MAX_NAMES	=1024;
const uchar PARK_NAME_SIZE			=32;

const unsigned int SV4_NAME_START	=0x19B89C;

}

using namespace std;

class RCTGLPark
{
public:
	RCTGLPark();
	bool loadPark(const string &filename);
	bool clearPark();
	string getName(int index) const;
	void loadTextures();
	void draw() const;

private:
	uchar m_sizeX, m_sizeZ;

	RCTGLLandscape m_landscape;
	RCTGLPathSystem m_paths;
	
	/*
	vector <RCTGLScenery> sceneryList[128][128];
	vector <RCTGLElement> elementList[128][128];
	vector <RCTGLEntrance> entranceList[128][128];
	vector <RCTGLBanner> bannerList[128][128];
	*/

	vector <string> m_rideNameList;

	bool uncompressFile(const string &inFile, const string &outFile);
	bool loadNames(uchar *parkData);
	void unloadNames();
};

#endif