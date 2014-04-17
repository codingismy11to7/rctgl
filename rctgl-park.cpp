#include "rctgl-park.h"

RCTGLPark::RCTGLPark(void)
{	
}

bool RCTGLPark::clearPark(void)
{
	for(unsigned int i=0; i<rideNameList.size(); i++)
		free(rideNameList[i]);

	rideNameList.clear();

	landscape.clear();

	return true;
}

char * RCTGLPark::getName(int index)
{
	if(index < 0 || index > rideNameList.size())
		return NULL;
	else
		return rideNameList[index];	
}

bool RCTGLPark::loadNames(unsigned char *parkData)
{
	long i, offset;

	RCTGLLog.beginTask("RCTGLPark::loadNames()");

	int validNames = 0;

	for(i=0; i<1024; i++)
	{
		char *tmp;

		tmp = (char *)malloc(32);

		if(!tmp)
		{
			MessageBox(NULL, "Error allocating memory for name", "ERROR", MB_SETFOREGROUND | MB_OK);
			RCTGLLog.writeToLog("Error in malloc. i=%d\n", (long)i);
			return false;
		}		
		
		offset = 32 * i;

		for(int j=0; j<32; j++)
			tmp[j] = (char)parkData[0x19B89C + offset + j];


		if(strlen(tmp) > 0)
			validNames++;

		rideNameList.push_back(tmp);
	}

	RCTGLLog.writeToLog("Read %d names\n", (long)validNames);

	RCTGLLog.endTask();

	return true;
}

bool RCTGLPark::uncompressFile(char *inFile, char *outFile)
{
	char countbyte;
	unsigned char databyte;

	int i;

	FILE *input, *output;

	//open the streams
	if((input = fopen(inFile, "rb")) == NULL)
	{
		MessageBox(NULL, "Error opening SV4", "ERROR", MB_SETFOREGROUND | MB_OK);
		return false;
	}
	
	if((output = fopen(outFile, "wb")) == NULL)
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
				databyte = (unsigned char)fgetc(input);

				fputc(databyte, output);
			}
		}
	}

	fclose(input);
	fclose(output);

	return true;
}

bool RCTGLPark::loadPark(char *filename)
{
	RCTGLLog.beginTask("RCTGLPark::loadPark");
	RCTGLLog.writeToLog("Loading %s\n", filename);

	//uncompress the file
	char *uncompressedFilename = "uncomp.dat";

	unsigned char *parkData;

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

	parkData = (unsigned char *)malloc(fileSize);
	
	if(parkData == NULL)
	{
		MessageBox(NULL, "Error allocating memory", "ERROR", MB_SETFOREGROUND | MB_OK);
		return false;
	}

	fseek(input, 0, SEEK_SET);

	for(long i=0; i<fileSize; i++)
		parkData[i] = fgetc(input);

	//process the data
	if(!loadNames(parkData))
	{
		free(parkData);
		return false;
	}

	long offset = 0x10;
	long nextSegment = 0x10;

	unsigned char buffer, buf1;

	bool lastItem;

	for(i=0; i<128; i++)
	{
		for(int j=0; j<128; j++)
		{
			lastItem = false;

			while(!lastItem)
			{
				if(offset >= 393231)
				{
					MessageBox(NULL, "Error: We are beyond the game map", "ERROR", MB_OK | MB_SETFOREGROUND);
					
					RCTGLLog.writeToLog("Aborting. Landscape loader went beyond the game map. ");
					RCTGLLog.writeToLog("offset=%d. ", (long)offset);
					RCTGLLog.writeToLog("i=%d ", (long)i);
					RCTGLLog.writeToLog("j=%d\n", (long)j);

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
					landscape.loadOffset(parkData + offset, i, j);
					break;
				/*
				case SEGMENT_PATH:
					{
						RCTGLPath *path = new RCTGLPath;
						path->loadOffset(parkData + offset);

						pathList[i][j].push_back(path);
					}
					break;				
				case SEGMENT_ELEMENT:
					RCTGLElement *element = new RCTGLElement;
					element->loadOffset(parkData + offset);

					elementList[i][j].push_back(element);
					break;
				case SEGMENT_SCENERY_SINGLE:
				case SEGMENT_SCENERY_MULTI:
					RCTGLScenery *scenery = new RCTGLScenery;
					scenery->loadOffset(parkData + offset);

					sceneryList[i][j].push_back(scenery);
					break;
				case SEGMENT_ENTRANCE:
					break;
				case SEGMENT_BANNER:
					break;
				*/
				default:
					break;
				}

				if(parkData[offset + 1] & SEGMENT_LAST)
					lastItem = true;

				offset += 8;
			}
		}
	}

	//for(i=0; i<1024; i++)
	//	RCTGLLog.writeToLog("retrieved '%s'\n", getName(i));

	//release the uncompressed data
	free(parkData);

	RCTGLLog.endTask();

	return true;
}

void RCTGLPark::loadTextures(void)
{
	landscape.loadTextures();
}

void RCTGLPark::draw(void)
{
	unsigned char minX = 0, maxX = 128, minZ = 0, maxZ = 128;

	landscape.draw(minX, minZ, maxX, maxZ);
}