#include "rctgl-park.h"

using namespace RCTPark;

float xWaterOffset1, zWaterOffset1, xWaterOffset2, zWaterOffset2;

void RCTGLPark::dumpData()
{
	int posX = userView.XV / UNITWIDTH;
	int posZ = userView.ZV / UNITWIDTH;

	stringstream x;
	x << "User at " << posX << ", " << posZ;
	DebugLog::writeToLog(x.str());
	printf("%s\n", x.str().c_str());

	string str = "=== Elements ===";
	DebugLog::writeToLog(str);
	printf("%s\n", str.c_str());

	for(int i=0; i<m_elements.m_elementItems[posX][posZ].size(); i++)
	{
		RCTGLElementElement e = m_elements.m_elementItems[posX][posZ][i];

		x.str("");
		x << "Element #" << (int)(i);
		DebugLog::writeToLog(x.str());
		printf("%s\n", x.str().c_str());

		x.str("");
		x << "baseHeight: " << (int)(e.baseHeight);
		DebugLog::writeToLog(x.str());
		printf("%s\n", x.str().c_str());

		x.str("");
		x << "elementID: " << (int)(e.elementID);
		DebugLog::writeToLog(x.str());
		printf("%s\n", x.str().c_str());

		x.str("");
		x << "rideID: " << (int)(e.rideIndex);
		DebugLog::writeToLog(x.str());
		printf("%s\n", x.str().c_str());

		x.str("");
		x << "itemIndex: " << (int)(e.index);
		DebugLog::writeToLog(x.str());
		printf("%s\n", x.str().c_str());

		x.str("");
		x << "rotation: " << (int)(e.rotation);
		DebugLog::writeToLog(x.str());
		printf("%s\n\n", x.str().c_str());
	}
		

}

RCTGLPark::RCTGLPark()
{	
	//set a default for SV4 files, but add support for SV6
	//when RCTGL gets to that point
	m_sizeX = m_sizeZ = 128;
	xWaterOffset1 = zWaterOffset1 = xWaterOffset2 = zWaterOffset2 = 0.0f;
}

bool RCTGLPark::clearPark()
{
	/*for(unsigned int i=0; i<m_rideNameList.size(); i++)
		free(m_rideNameList[i]);*/

	m_rideNameList.clear();
	m_landscape.clear();
	m_paths.clear();
	m_scenery.clear();
	m_elements.clear();

	xWaterOffset1 = zWaterOffset1 = 0.0f;
	xWaterOffset2 = zWaterOffset2 = 0.1f;

	timeOfDay = 12.0f;

	return true;
}

string RCTGLPark::getName(unsigned int index) const
{
	if(index < 0 || index > m_rideNameList.size())
		return NULL;
	else
		return m_rideNameList[index];	
}

bool RCTGLPark::loadNames(uchar *parkData)
{
	long i, offset;

	DebugLog::beginTask("RCTGLPark::loadNames()");

	int validNames = 0;

	long nameStart = SV4_NAME_START;

	char *tmp = new char[PARK_NAME_SIZE];
	for(i=0; i<PARK_MAX_NAMES; i++)
	{
		tmp[0] = 0;

		//tmp = (char *)malloc(PARK_NAME_SIZE);

		/*if(!tmp)
		{
			MessageBox(NULL, "Error allocating memory for name", "ERROR", MB_SETFOREGROUND | MB_OK);
			stringstream x;
			x << "Error in malloc. i=" << i;
			DebugLog::writeToLog(x.str());
			DebugLog::endTask();
			return false;
		}*/		
		
		offset = PARK_NAME_SIZE * i;

		for(int j=0; j<PARK_NAME_SIZE; j++)
			tmp[j] = (char)parkData[nameStart + offset + j];


		if(strlen(tmp) > 0)
			validNames++;

		m_rideNameList.push_back(tmp);
	}
	delete[] tmp;

	stringstream x;
	x << "Read " << validNames << " names";

	DebugLog::writeToLog(x.str());
	DebugLog::endTask();

	return true;
}

void RCTGLPark::unloadNames()
{
	//for(long i=0; i<rideNameList.size(); i++)
	//	free(rideNameList[i]);
	
	m_rideNameList.clear();
}

bool RCTGLPark::uncompressFile(const string &inFile, const string &outFile)
{
	char countbyte;
	uchar databyte;

	int i;

	FILE *input, *output;

	//open the streams
	if((input = fopen(inFile.c_str(), "rb")) == NULL)
	{
		MessageBox(NULL, "Error opening SV4", "ERROR", MB_SETFOREGROUND | MB_OK);
		return false;
	}
	
	if((output = fopen(outFile.c_str(), "wb")) == NULL)
	{
		MessageBox(NULL, "Error opening temp file", "ERROR", MB_SETFOREGROUND | MB_OK);
		return false;
	}

	//loop through the input file
	while (!feof(input))
	{
		countbyte = fgetc(input);

		//if the MSB is zero, we copy the next byte countbyte + 1 times
		if (countbyte < 0)
		{
			countbyte = -1 * countbyte;

			databyte = fgetc(input);

			for(i=0; i<=countbyte; i++)
				fputc(databyte, output);
		}
		else
		{
			// now we duplicate data
			for(i=0; i<=countbyte; i++)
			{
				databyte = (uchar)fgetc(input);

				fputc(databyte, output);
			}
		}
	}

	fclose(input);
	fclose(output);

	return true;
}

bool RCTGLPark::loadPark(const string &filename)
{
	DebugLog::beginTask("RCTGLPark::loadPark");
	DebugLog::writeToLog(string("Loading ") + filename);

	clearPark();

	//uncompress the file
	char *uncompressedFilename = "uncomp.dat";

	if(!uncompressFile(filename, uncompressedFilename))
		return false;	

	//load the uncompressed data into memory
	FILE *input;

	if((input = fopen(uncompressedFilename, "rb")) == NULL)
	{
		MessageBox(NULL, "Error loading uncompressed data", "ERROR", MB_SETFOREGROUND | MB_OK);
		return false;
	}

	long fileSize;

	fseek (input, 0, SEEK_END);
    fileSize=ftell (input);

	uchar *parkData;

	parkData = (uchar *)malloc(fileSize);
	
	if(parkData == NULL)
	{
		MessageBox(NULL, "Error allocating memory", "ERROR", MB_SETFOREGROUND | MB_OK);
		return false;
	}

	fseek(input, 0, SEEK_SET);

	for(long x=0; x<fileSize; x++)
		parkData[x] = fgetc(input);

	//process the data
	if(!loadNames(parkData))
	{
		free(parkData);
		return false;
	}

	long offset = 0x10;
	long nextSegment = 0x10;

	uchar buffer;

	bool lastItem;

	for(uchar i=0; i<m_sizeX; i++)
	{
		for(uchar j=0; j<m_sizeZ; j++)
		{
			lastItem = false;

			while(!lastItem)
			{
				if(offset >= MAX_GAME_DATA)
				{
					MessageBox(NULL, "Error: We are beyond the game map", "ERROR", MB_OK | MB_SETFOREGROUND);

					stringstream x;

					x << "Aborting. Landscape loader went beyond the game map. offset=0x" << hex << offset << dec;
					x << "i=" << i << " j=" << j;
					DebugLog::writeToLog(x.str());

					return false;
				}

				//mask with 00111100 to get the middle 4 bits				
				buffer = parkData[offset];
				buffer = ((buffer & 0x3C) >> 2);

				//these middle 4 bits determine what type of object
				//the next 8 bytes describe
				switch(buffer)
				{
				case SEGMENT_LANDSCAPE:
					m_landscape.loadOffset(parkData + offset, i, j);
					break;				
				case SEGMENT_PATH:
					m_paths.loadOffset(parkData + offset, i, j);
					break;					
				case SEGMENT_ELEMENT:
					m_elements.loadOffset(parkData + offset, i, j);
					break;
				case SEGMENT_SCENERY_SINGLE:
					m_scenery.loadOffset(parkData + offset, i, j, RCTScenery::SINGLE_TILE);
					break;	
				case SEGMENT_SCENERY_MULTI:
					m_scenery.loadOffset(parkData + offset, i, j, RCTScenery::MULTI_TILE);
					break;					
				case SEGMENT_ENTRANCE:
					/*
					{
						RCTGLEntrance *ent = new RCTGLEntrance;
						ent->loadOffset(parkData + offset);

						entranceList[i][j].push_back(ent);
					}					
					*/
					break;
				case SEGMENT_WALL:
					/*
					{
						RCTGLWall *wall = new RCTGLWall;
						wall->loadOffset(parkData + offset);

						wallList[i][j].push_back(wall);
					}					
					*/
					break;
				case SEGMENT_BANNER:
					/*
					{
						RCTGLBanner *banner = new RCTGLBanner;
						banner->loadOffset(parkData + offset);

						bannerList[i][j].push_back(banner);
					}
					*/
					break;				
				default:
					{
						stringstream x;
						x << "Unrecognized item type (" << (short)buffer << ") at byte 0x" << hex << offset;
						DebugLog::writeToLog(x.str());
					}
					break;
				}

				if(parkData[offset + 1] & SEGMENT_LAST)
					lastItem = true;

				offset += 8;
			}
		}
	}

	m_rides.load(parkData + 0x1A38A0);

	//release the uncompressed data
	free(parkData);

	//compile the landscape
	m_landscape.compile();
	m_paths.compile();
	m_scenery.compile();
	m_elements.compile(&m_rides);

	DebugLog::endTask();

	displayMode = GAME;

	userView.XV = 0.0f;
	userView.YV = m_landscape.land[1][1].highest + 10.0f;
	userView.ZV = 0.0f;

	userView.XR = 0.0f;
	userView.YR = 45.0f;
	userView.ZR = 0.0f;

	return true;
}

void RCTGLPark::loadTextures()
{
	m_landscape.loadTextures();
	m_paths.loadTextures();
	m_scenery.loadTextures();
	m_elements.loadTextures();

	unsigned int texID;
	RCTGLTextureManager texMan;

	texID = texMan.addTexture("\\clouds.tga", 0);
	m_skyDome.setCloudTexture(texID);
	texID = texMan.addTexture("\\clearSky2d.png", 0);
	m_skyDome.setSkyTexture(texID);
}

void RCTGLPark::draw()
{
	int minX = 0, maxX = m_sizeX, minZ = 0, maxZ = m_sizeZ;

	minX = (int)(userView.XV / UNITWIDTH) - 40;
	maxX = (int)(userView.XV / UNITWIDTH) + 40;

	minZ = (int)(userView.ZV / UNITWIDTH) - 40;
	maxZ = (int)(userView.ZV / UNITWIDTH) + 40;

	if(minX < 0)	minX = 0;
	if(minZ < 0)	minZ = 0;
	if(maxX > 127)	maxX = 127;
	if(maxZ > 127)	maxZ = 127;

	xWaterOffset1 += (0.025f / 2.0f);
	zWaterOffset1 += (0.01f / 2.0f);

	xWaterOffset2 += (0.02f / 2.0f);
	zWaterOffset2 += (0.005f / 2.0f);

	if(xWaterOffset1 >= 1.0f)
		xWaterOffset1 = 0.0f;
	if(xWaterOffset2 >= 1.1f)
		xWaterOffset2 = 0.1f;

	if(zWaterOffset1 >= 1.0f)
		zWaterOffset1 = 0.0f;
	if(zWaterOffset2 >= 1.1f)
		zWaterOffset2 = 0.1f;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_FOG);

	m_landscape.draw((uchar)minX, (uchar)minZ, (uchar)maxX, (uchar)maxZ);
	m_paths.draw((uchar)minX, (uchar)minZ, (uchar)maxX, (uchar)maxZ);	
	m_scenery.draw((uchar)minX, (uchar)minZ, (uchar)maxX, (uchar)maxZ);
	m_elements.draw((uchar)minX, (uchar)minZ, (uchar)maxX, (uchar)maxZ);

	glDisable(GL_FOG);

}

void RCTGLPark::drawSkyDome()
{
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_skyDome.setTime(timeOfDay);
	m_skyDome.draw();

	glDisable(GL_BLEND);
	glBlendFunc (GL_ONE, GL_ONE);
	glEnable(GL_CULL_FACE);
}