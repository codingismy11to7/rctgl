#include "vr3d.h" 

//PathStructType PathList[15876];
//int PathListSize;

extern ParkStructType thePark;

extern double ambientRValue, ambientGValue, ambientBValue;
extern double lightRValue, lightGValue, lightBValue;

extern double calcLightFactor(double n1, double n2, double n3);


int queueRide;
bool inQueue;

int calcQueueRide(int xTile, int zTile, int count, int approach)
{
	/*
	The approaches are:
	-1 - none
	0 - from N
	1 - from S
	2 - from E
	3 - from W

	for queues, thePark.paths[a][b][c].pathType == 0

	pathSlope == 0 for flat land

	*/

	printf("in calcQueueRide(%d, %d, %d, %d)\n", xTile, zTile, count, approach);
	printf("connections N-%d S-%d E-%d W-%d\n", thePark.paths[xTile][zTile][count].connectN,
		thePark.paths[xTile][zTile][count].connectS, thePark.paths[xTile][zTile][count].connectE,
		thePark.paths[xTile][zTile][count].connectW);

	int returnTemp, returnSave;
	int i;

	// check to see if this is a ride entrance
	for(i=0; i<thePark.entrances[xTile][zTile].size(); i++)
		if(thePark.entrances[xTile][zTile][i].base == thePark.paths[xTile][zTile][count].base &&
			thePark.entrances[xTile][zTile][count].entranceType == rideEnt)
		{
			printf("found an entrance\n");
			return thePark.entrances[xTile][zTile][count].rideIndex;
		}

	returnTemp = -1;
	
	//check the east side
	for(i=0; i<thePark.paths[xTile][zTile+1].size(); i++)
	{
		if(thePark.paths[xTile][zTile][count].connectE > 0 && approach != 2 &&
			thePark.paths[xTile][zTile][count].pathType == 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][count].pathSlope == 0)
			{
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 0)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				
				else if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 6)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				else if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 4)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				
			}
			
			//if we start going uphill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 6)
			{
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 0)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 4)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 6)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
			}
			//if we start going downhill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 4)
			{
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 0)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 4)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
				if(thePark.paths[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile][zTile+1][i].pathSlope == 6)
				{
					returnTemp = calcQueueRide(xTile, zTile+1, i, 3);
					break;
				}
			}
			
		}		
	}
	if(returnTemp == -1)
	{
		// check to see if this is a ride entrance
		for(i=0; i<thePark.entrances[xTile][zTile+1].size(); i++)
		{
			if(thePark.entrances[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base &&
				thePark.entrances[xTile][zTile+1][count].entranceType == rideEnt &&
				(thePark.paths[xTile][zTile][count].pathSlope == 4 || thePark.paths[xTile][zTile][count].pathSlope == 0))
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile][zTile+1][count].rideIndex;
			}
			else if(thePark.entrances[xTile][zTile+1][i].base == thePark.paths[xTile][zTile][count].base + 1 &&
				thePark.entrances[xTile][zTile+1][count].entranceType == rideEnt &&
				thePark.paths[xTile][zTile][count].pathSlope == 6)
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile][zTile+1][count].rideIndex;
			}
		}
	}
	
		

	returnSave = returnTemp;

	returnTemp = -1;

	//check the west side
	for(i=0; i<thePark.paths[xTile][zTile-1].size(); i++)
	{
		if(thePark.paths[xTile][zTile][count].connectW > 0 && approach != 3 &&
			thePark.paths[xTile][zTile][count].pathType == 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][count].pathSlope == 0)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				
				// piece is continuing up-hill
				else if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 4)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				// piece is continuing downhill
				else if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 6)
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				
			}
			
			// if we start uphill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 4)
			{
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 4)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 6)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
			}
			//if we start downhill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 6)
			{
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 4)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
				if(thePark.paths[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile][zTile-1][i].pathSlope == 6)			
				{
					returnTemp = calcQueueRide(xTile, zTile-1, i, 2);
					break;
				}
			}
			
		}
	}
	if(returnTemp == -1)
	{
		// check to see if this is a ride entrance
		for(i=0; i<thePark.entrances[xTile][zTile-1].size(); i++)
		{
			if(thePark.entrances[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base &&
				thePark.entrances[xTile][zTile-1][count].entranceType == rideEnt &&
				(thePark.paths[xTile][zTile][count].pathSlope == 6 || thePark.paths[xTile][zTile][count].pathSlope == 0))
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile][zTile-1][count].rideIndex;
			}
			else if(thePark.entrances[xTile][zTile-1][i].base == thePark.paths[xTile][zTile][count].base + 1 &&
				thePark.entrances[xTile][zTile-1][count].entranceType == rideEnt &&
				thePark.paths[xTile][zTile][count].pathSlope == 4)
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile][zTile-1][count].rideIndex;
			}
		}
	}


	if(returnSave == -1)
		returnSave = returnTemp;

	returnTemp = -1;

	//check the north side
	for(i=0; i<thePark.paths[xTile+1][zTile].size(); i++)
	{
		if(thePark.paths[xTile][zTile][count].connectN > 0 && approach != 0 &&
			thePark.paths[xTile][zTile][count].pathType == 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][count].pathSlope == 0)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
				
				// piece goes up-hill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 5)			
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
				// piece goes downhill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 7)
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
			}
			
			
			// if we start uphill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 5)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
				// piece goes up-hill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 5)			
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
				// piece goes downhill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 7)
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
			}		
			//if we start downhill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 7)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
				// piece goes up-hill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 5)			
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
				// piece goes downhill
				else if(thePark.paths[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile+1][zTile][i].pathSlope == 7)
				{
					returnTemp = calcQueueRide(xTile+1, zTile, i, 1);
					break;
				}
			}
			
		}
		
	}
	if(returnTemp == -1)
	{
		// check to see if this is a ride entrance
		for(i=0; i<thePark.entrances[xTile+1][zTile].size(); i++)
		{
			if(thePark.entrances[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base &&
				thePark.entrances[xTile+1][zTile][count].entranceType == rideEnt &&
				(thePark.paths[xTile][zTile][count].pathSlope == 7 || thePark.paths[xTile][zTile][count].pathSlope == 0))
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile+1][zTile][count].rideIndex;
			}
			else if(thePark.entrances[xTile+1][zTile][i].base == thePark.paths[xTile][zTile][count].base + 1 &&
				thePark.entrances[xTile+1][zTile][count].entranceType == rideEnt &&
				thePark.paths[xTile][zTile][count].pathSlope == 5)
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile+1][zTile][count].rideIndex;
			}
		}

	}

	if(returnSave == -1)
		returnSave = returnTemp;

	returnTemp = -1;

	//check the south side
	for(i=0; i<thePark.paths[xTile-1][zTile].size(); i++)
	{
		if(thePark.paths[xTile][zTile][count].connectS > 0 && approach != 1 &&
			thePark.paths[xTile][zTile][count].pathType == 0)
		{
			//if we start on flat land
			if(thePark.paths[xTile][zTile][count].pathSlope == 0)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				
				// piece goes up-hill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 5)			
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				// piece goes downhill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 7)
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				
			}
						
			// if we start uphill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 5)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				// piece goes up-hill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base - 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 5)			
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				// piece goes downhill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 7)
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
			}		
			//if we start downhill
			else if(thePark.paths[xTile][zTile][count].pathSlope == 7)
			{
				// adjacent piece is flat and on the same base
				if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 0)			
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				// piece goes up-hill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 5)			
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
				// piece goes downhill
				else if(thePark.paths[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base + 1
					&& thePark.paths[xTile-1][zTile][i].pathSlope == 7)
				{
					returnTemp = calcQueueRide(xTile-1, zTile, i, 0);
					break;
				}
			}
			
		}
	}
	if(returnTemp == -1)
	{
		// check to see if this is a ride entrance
		for(i=0; i<thePark.entrances[xTile-1][zTile].size(); i++)
		{
			if(thePark.entrances[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base &&
				thePark.entrances[xTile-1][zTile][count].entranceType == rideEnt &&
				(thePark.paths[xTile][zTile][count].pathSlope == 5 || thePark.paths[xTile][zTile][count].pathSlope == 0))
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile-1][zTile][count].rideIndex;
			}
			else if(thePark.entrances[xTile-1][zTile][i].base == thePark.paths[xTile][zTile][count].base + 1 &&
				thePark.entrances[xTile-1][zTile][count].entranceType == rideEnt &&
				thePark.paths[xTile][zTile][count].pathSlope == 7)
			{
				printf("found an entrance\n");
				return thePark.entrances[xTile-1][zTile][count].rideIndex;
			}
		}

	}


	if(returnSave == -1)
		returnSave = returnTemp;

	printf("end calcQueueRide()\n");

	return returnSave;
}

void LoadPaths2(char *filename)
{
	FILE *input;

	int i,j;
	long nextbyte;
	long currentbyte;
//	int tempheight;
//	int LLmodifier;
	int looping;
	int mapsize = 128;

	unsigned char buffer;
	unsigned char endCheckBuffer;

	//PathListSize = 0;

	printf("- in LoadPath()\n");

	input = fopen(filename, "rb");

	if(input == NULL)
		perror("fopen\n");

	//move to the map info
	fseek(input, 0x10, SEEK_SET);

	currentbyte = 0x10;
	nextbyte = 0x10;

	for(i=0; i<128; i++)
	{
		//printf("row %d\n", i);

		for(j=0; j<128; j++)
		{
			buffer = 10;
			endCheckBuffer = 10;

			looping = 0;

			//first, we get the next piece of land
			// allegedly, everything after the land belongs to that
			// section

			// when we hit the next piece of land, we loop

			//while(buffer != 0 && buffer != 1 && buffer != 128 && buffer != 129) //28)
			while(1)
			{
				if(endCheckBuffer >= 128)
					break;

				/*
				if (buffer >= 0 && buffer <= 3)
					break;
				if (buffer >= 64 && buffer <= 67)
					break;
				if (buffer >= 128 && buffer <= 131)
					break;
				if (buffer >= 192 && buffer <= 195)
					break;
					*/

				//if(looping == 1)
				//	printf("looping for land at %d\n", nextbyte);

				looping++;

				//move to the next land segment
				fseek(input, nextbyte - 7, SEEK_SET);

				endCheckBuffer = fgetc(input);

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				buffer = fgetc(input);

				
				nextbyte += 8;

				if((nextbyte - 8) >= 393231)
				{
					printf("Error1A: We are beyond the game map. stop at %d, %d (%d)\nAborting\n", i, j, nextbyte - 8);
					exit(-1);					
				}
			}			//6728
			

			//printf("found land at %d\n", nextbyte - 8);

			/*
			currentbyte = nextbyte;

			nextbyte += 8;
			*/

			// now we're after the land height info. now loop until
			// we hit a path element, or the next land piece

			buffer = 10;
			endCheckBuffer = 10;

			/* here are the bytes we're looking for 
			 * we need anything with middle bits 0001
			 * 00 0001 00 = 4
			 * 00 0001 01 = 5
			 * 00 0001 10 = 6
			 * 00 0001 11 = 7
			 * 01 0001 00 = 68
			 * 01 0001 01 = 69
			 * 01 0001 10 = 70
			 * 01 0001 11 = 71
			 * 10 0001 00 = 132
			 * 10 0001 01 = 133
			 * 10 0001 10 = 134
			 * 10 0001 11 = 135
			 * 11 0001 00 = 196
			 * 11 0001 01 = 197
			 * 11 0001 10 = 198
			 * 11 0001 11 = 199
			 */
			while(1)
			{
				// check the land values
				/*
				if (buffer >= 0 && buffer <= 3)
					break;
				if (buffer >= 64 && buffer <= 67)
					break;
				if (buffer >= 128 && buffer <= 131)
					break;
				if (buffer >= 192 && buffer <= 195)
					break;
					*/
				
				

				//check the scenery values
				if (buffer >= 4 && buffer <= 7)
				{
					AddPath(input, currentbyte, i, j, buffer - 4);
					//break;
				}
				if (buffer >= 68 && buffer <= 71)
				{
					AddPath(input, currentbyte, i, j, buffer - 68);
					//break;
				}
				if (buffer >= 132 && buffer <= 135)
				{
					AddPath(input, currentbyte, i, j, buffer - 132);
					//break;
				}
				if (buffer >= 196 && buffer <= 199)
				{
					AddPath(input, currentbyte, i, j, buffer - 196);
					//break;
				}

				if(endCheckBuffer >= 128)
					break;




				//if(looping == 1)
				//	printf("looping for land at %d\n", nextbyte);

				looping++;

				//move to the next land segment
				fseek(input, currentbyte + 1, SEEK_SET);

				endCheckBuffer = fgetc(input);

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				currentbyte = nextbyte;

				buffer = fgetc(input);

				
				nextbyte += 8;

				if((nextbyte + 8) >= 393231)
				{
					if((i != mapsize - 1) && (j != mapsize - 1))
					{
						printf("Error1B: We are beyond the game map. stop at %d, %d (%d)\nAborting\n", i, j, nextbyte - 8);
						exit(-1);					
					}
					else
					{
						printf("met break condition\n");
						break;
					}
				}			
			}

			nextbyte -= 8;
		}
	}

	//printf("PathListSize = %d\n", PathListSize);
}

void LoadPaths(char *filename)
{
	FILE *input;

	int i,j;
	long nextbyte;
	long currentbyte;
//	int tempheight;
//	int LLmodifier;
	int looping;
	int mapsize = 128;

	unsigned char buffer;
	unsigned char endCheckBuffer;

	//PathListSize = 0;

	printf("- in LoadPath()\n");

	input = fopen(filename, "rb");

	if(input == NULL)
		perror("fopen\n");

	//move to the map info
	fseek(input, 0x10, SEEK_SET);

	currentbyte = 0x10;
	nextbyte = 0x10;

	for(i=0; i<128; i++)
	{
		//printf("row %d\n", i);

		for(j=0; j<128; j++)
		{
			buffer = 10;
			endCheckBuffer = 10;

			while(1)
			{
				// check the land values
				/*
				if (buffer >= 0 && buffer <= 3)
					break;
				if (buffer >= 64 && buffer <= 67)
					break;
				if (buffer >= 128 && buffer <= 131)
					break;
				if (buffer >= 192 && buffer <= 195)
					break;
					*/
				//move to the next land segment
				fseek(input, currentbyte + 9, SEEK_SET);

				endCheckBuffer = fgetc(input);

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				currentbyte = nextbyte;

				buffer = fgetc(input);

				nextbyte += 8;

				//check the scenery values
				if (buffer >= 4 && buffer <= 7)
				{
					AddPath(input, currentbyte, i, j, buffer - 4);
					//break;
				}
				if (buffer >= 68 && buffer <= 71)
				{
					AddPath(input, currentbyte, i, j, buffer - 68);
					//break;
				}
				if (buffer >= 132 && buffer <= 135)
				{
					AddPath(input, currentbyte, i, j, buffer - 132);
					//break;
				}
				if (buffer >= 196 && buffer <= 199)
				{
					AddPath(input, currentbyte, i, j, buffer - 196);
					//break;
				}

				
				//if(looping == 1)
				//	printf("looping for land at %d\n", nextbyte);

				looping++;


				if((nextbyte + 8) >= 393231)
				{
					if((i != mapsize - 1) && (j != mapsize - 1))
					{
						printf("Error1B: We are beyond the game map. stop at %d, %d (%d)\nAborting\n", i, j, nextbyte - 8);
						exit(-1);					
					}
					else
					{
						printf("met break condition\n");
						break;
					}
				}			

				if(endCheckBuffer >= 128)
					break;

			}

			//nextbyte -= 8;
		}
	}

	//printf("PathListSize = %d\n", PathListSize);
}

#define TILE_PATH			5	//0101
#define TILE_PATH_VALUE		80	//0101 0000
#define ROAD_PATH			4	//0100
#define ROAD_PATH_VALUE		64	//0100 0000
#define CRAZY_PATH			3	//0011
#define CRAZY_PATH_VALUE	48	//0011 0000
#define DIRT_PATH			2	//0010
#define DIRT_PATH_VALUE		32	//0010 0000
#define TARMAC_PATH			1	//0001
#define TARMAC_PATH_VALUE	16	//0001 0000
#define QUEUE_PATH			0	//0000
#define QUEUE_PATH_VALUE	0	//0000 0000

#define QUEUE_ENTRY_VALUE	8	//0000 1000


/* adds a path to the linked list of paths */
void AddPath(FILE *input, int offset, int x, int z, int modifier)
{
	unsigned char buffer;
//	float objBase, objCeiling;
//	int objIdentity;
	int tempheight;	

	// the file should already be at the correct position, so
	// we can retrieve the scenery information

	/*	byte #0 - scenery type
		byte #1 - support type for paths (not applicable yet)
		byte #2 - base height
		byte #3 - object clearance
		byte #4 - path type and slope
		byte #5 - path additions (not applicable yet)
		byte #6 - extensions
		byte #7 - location of byte #5
	*/

	// we can skip over byte #0 since it was already checked
	
	// we can skip over byte #1 for now

	PathStructType *newPath = new PathStructType;
	
	// we need to get the item's base height (byte #2)
	fseek(input, offset + 2, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newPath->base = (float)(tempheight / 4.0);
	else
		newPath->base = 0.0f;

	// we need to get the item's ceiling (byte #3)
	fseek(input, offset + 3, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newPath->ceiling = (float)(tempheight / 4.0);
	else
		newPath->ceiling = 0.0f;


	// we need to get the path type and slope
	fseek(input, offset + 4, SEEK_SET);
	tempheight = fgetc(input);
	// tile      = 0101 xxxx
	//if(tempheight >= 80)
	if((tempheight & TILE_PATH_VALUE) == TILE_PATH_VALUE)
		newPath->pathType = TILE_PATH;
	// roads     = 0100 xxxx
	else if((tempheight & ROAD_PATH_VALUE) == ROAD_PATH_VALUE)
		newPath->pathType = ROAD_PATH;
	// crzy tile = 0011 xxxx
	else if((tempheight & CRAZY_PATH_VALUE) == CRAZY_PATH_VALUE)
		newPath->pathType = CRAZY_PATH;
	// dirt      = 0010 xxxx
	else if((tempheight & DIRT_PATH_VALUE) == DIRT_PATH_VALUE)
		newPath->pathType = DIRT_PATH;
	// tarmac    = 0001 xxxx
	else if((tempheight & TARMAC_PATH_VALUE) == TARMAC_PATH_VALUE)
		newPath->pathType = TARMAC_PATH;
	// queue     = 0000 xxxx
	else if((tempheight & QUEUE_PATH_VALUE) == QUEUE_PATH_VALUE)
		newPath->pathType = QUEUE_PATH;
	else
		newPath->pathType = TARMAC_PATH;
	
	// now that we have the type, we can get the queue entry
	if ((tempheight & QUEUE_ENTRY_VALUE) == QUEUE_ENTRY_VALUE)
		newPath->queueEntry = TRUE;
	else
		newPath->queueEntry = FALSE;
	
	// finally, we can get the slope, which is the resolved value of the byte
	newPath->pathSlope = tempheight & 7; //0000 0111

	// get the path extensions
	fseek(input, offset + 6, SEEK_SET);
	tempheight = fgetc(input);

	newPath->connectSW = FALSE;
	newPath->connectNW = FALSE;
	newPath->connectSE = FALSE;
	newPath->connectNE = FALSE;
	newPath->connectN = FALSE;
	newPath->connectS = FALSE;
	newPath->connectE = FALSE;
	newPath->connectW = FALSE;

	// bit structure of 6th byte
	// SW SE NE NW S E N W
	//check SW connection
	if(tempheight & 128)
		newPath->connectSW = TRUE;
	//check SE connection
	if(tempheight & 64)
		newPath->connectSE = TRUE;
	//check NE connection
	if(tempheight & 32)
		newPath->connectNE = TRUE;
	//check NW connection
	if(tempheight & 16)
		newPath->connectNW = TRUE;
	//check S connection
	if(tempheight & 8)
		newPath->connectS = TRUE;
	//check E connection
	if(tempheight & 4)
		newPath->connectE = TRUE;
	//check N connection
	if(tempheight & 2)
		newPath->connectN = TRUE;
	//check W connection
	if(tempheight & 1)
		newPath->connectW = TRUE;


	//finally, we need to assign the x and z coordinates to the path
	newPath->x = x;
	newPath->z = z;

	newPath->pathModifier = modifier;

	thePark.paths[x][z].push_back(*newPath);

	delete newPath;
}

void DrawPaths(int a, int b)
{
	int faceID;
	int side1; //, side2;

	int lastTexture;

	int c;

	

	glEnable(GL_TEXTURE_2D);

	int flipHoriz, flipVert;
	int rotateClock, rotateCClock;

	lastTexture = -1;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	for(c=0; c<thePark.paths[a][b].size(); c++)
	{				

		//printf("drawing path\n");
		faceID = TEXTURE_PATH_02_00;
		side1 = 5;

		flipHoriz = -1;
		flipVert = -1;
		rotateClock = -1;
		rotateCClock = -1;

		int xTile, zTile;

		xTile = XV / UNITWIDTH;
		zTile = ZV / UNITWIDTH;

		if((thePark.paths[a][b][c].base < thePark.landscape[a][b].lowest) && (thePark.landscape[xTile][zTile].lowest * UNITHEIGHT > YV))
		{
			/*
			glDisable    ( GL_ALPHA_TEST   );

			//if it's a flat path
			if(thePark.paths[a][b][c].pathSlope == 0)
			{
				//draw the floor, walls, and ceiling of tunnel, if necessary
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAVEL1] );

				glColor3f(0.8f, 0.8f, 0.8f);

				//ceiling
				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH,			(thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH,	(thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH,	(thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH,			(thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

				glEnd();

				//floor
				if(!(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE &&
					thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE &&
					thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectNW == TRUE &&
					thePark.paths[a][b][c].connectNW == TRUE && thePark.paths[a][b][c].connectSW == TRUE))
				{
					glBegin(GL_QUADS);
						glTexCoord2d(0.0f, 0.0f);
						glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH,			(thePark.paths[a][b][c].base) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

						glTexCoord2d(0.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH,	(thePark.paths[a][b][c].base) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

						glTexCoord2d(1.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH,	(thePark.paths[a][b][c].base) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

						glTexCoord2d(1.0f, 0.0f);
						glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH,			(thePark.paths[a][b][c].base) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glEnd();
				}

				glColor3f(0.75f, 0.75f, 0.75f);

				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );

				if(!thePark.paths[a][b][c].connectN)
				{
					
					glBegin(GL_QUADS);
						glTexCoord2d(0.0f, 0.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

						glTexCoord2d(0.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

						glTexCoord2d(1.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

						glTexCoord2d(1.0f, 0.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glEnd();

				}
				
				if(!thePark.paths[a][b][c].connectS)
				{
					
					glBegin(GL_QUADS);
						glTexCoord2d(0.0f, 0.0f);
						glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

						glTexCoord2d(0.0f, 1.0f);
						glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

						glTexCoord2d(1.0f, 1.0f);
						glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

						glTexCoord2d(1.0f, 0.0f);
						glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glEnd();

				}

				if(!thePark.paths[a][b][c].connectE)
				{
					
					glBegin(GL_QUADS);
						glTexCoord2d(0.0f, 0.0f);
						glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base) * UNITHEIGHT,			(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

						glTexCoord2d(0.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

						glTexCoord2d(1.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

						glTexCoord2d(1.0f, 0.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base) * UNITHEIGHT,			(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glEnd();

				}
				
				if(!thePark.paths[a][b][c].connectW)
				{
					
					glBegin(GL_QUADS);
						glTexCoord2d(0.0f, 0.0f);
						glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base) * UNITHEIGHT,			thePark.paths[a][b][c].z * UNITWIDTH + 0.02f);

						glTexCoord2d(0.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	thePark.paths[a][b][c].z * UNITWIDTH + 0.02f);

						glTexCoord2d(1.0f, 1.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	thePark.paths[a][b][c].z * UNITWIDTH + 0.02f);

						glTexCoord2d(1.0f, 0.0f);
						glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base) * UNITHEIGHT,			thePark.paths[a][b][c].z * UNITWIDTH + 0.02f);

					glEnd();

				}
			}
			//slope to the east
			else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 4)
			{
				//draw the floor, walls, and ceiling of tunnel, if necessary
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAVEL1] );

				glColor3f(0.8f, 0.8f, 0.8f);

				//floor
				glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);				

				glEnd();

				//ceiling
				glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);				

				glEnd();

				glColor3f(0.75f, 0.75f, 0.75f);
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );

				//walls
				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

				glEnd();

			
				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

				glEnd();
				
			}
			
			// slope of 5 = slope to North
			else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 5)
			{

				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAVEL1] );

				glColor3f(0.8f, 0.8f, 0.8f);

				//floor
				glBegin(GL_QUADS);
				
					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1)* UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);			
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

				glEnd();

				//ceiling
				glBegin(GL_QUADS);
				
					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);			
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

				glEnd();

				//walls

				glColor3f(0.75f, 0.75f, 0.75f);
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );

				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

				glEnd();

				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

				glEnd();
			}
			
			// slope of 6 = slope to West
			else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 6)
			{

				//draw the floor, walls, and ceiling of tunnel, if necessary
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAVEL1] );

				glColor3f(0.8f, 0.8f, 0.8f);

				//floor
				glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);				

				glEnd();

				//ceiling
				glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);				

				glEnd();

				glColor3f(0.75f, 0.75f, 0.75f);
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );

				//walls
				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

				glEnd();

			
				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT, thePark.paths[a][b][c].z * UNITWIDTH);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d(thePark.paths[a][b][c].x * UNITWIDTH + 0.02f,	(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH);

				glEnd();


			}			
			// slope of 7 = slope to South
			else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 7)
			{
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAVEL1] );

				glColor3f(0.8f, 0.8f, 0.8f);

				//floor
				glBegin(GL_QUADS);
				
					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);			
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

				glEnd();

				//ceiling
				glBegin(GL_QUADS);
				
					glTexCoord2f(0.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT,       thePark.paths[a][b][c].z * UNITWIDTH);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);			
					glTexCoord2f(1.0f, 0.0f);
					glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 2.9f) * UNITHEIGHT, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

				glEnd();

				//walls

				glColor3f(0.75f, 0.75f, 0.75f);
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );

				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 1.0f) * UNITWIDTH - 0.02f);

				glEnd();

				glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 1.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

					glTexCoord2d(0.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x) * UNITWIDTH - 0.02f,			(thePark.paths[a][b][c].base + 3.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

					glTexCoord2d(1.0f, 1.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 2.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

					glTexCoord2d(1.0f, 0.0f);
					glVertex3d((thePark.paths[a][b][c].x + 1.0f) * UNITWIDTH - 0.02f,	(thePark.paths[a][b][c].base + 0.0f) * UNITHEIGHT,	(thePark.paths[a][b][c].z + 0.0f) * UNITWIDTH + 0.02f);

				glEnd();
			}
			*/
			


			glColor3f(0.8f, 0.8f, 0.8f);

			
		}
		else
			glColor3f(1.0f, 1.0f, 1.0f);

		
		
		//if we have a queue
		if(thePark.paths[a][b][c].pathType == 0)
		{
			// blue queue
			if(thePark.paths[a][b][c].pathModifier == 0)
			{
				if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					faceID = TEXTURE_PATH_00_07;
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
				{
					faceID = TEXTURE_PATH_00_07;
					rotateClock = 1;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					faceID = TEXTURE_PATH_00_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					flipVert = 1;
					faceID = TEXTURE_PATH_00_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					flipVert = 1;
					faceID = TEXTURE_PATH_00_05;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					faceID = TEXTURE_PATH_00_05;
				}
				else
					faceID = TEXTURE_PATH_00_00;
			}
			// red queue
			else if(thePark.paths[a][b][c].pathModifier == 1)
			{
				if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					faceID = TEXTURE_PATH_01_07;
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
				{
					rotateClock = 1;
					faceID = TEXTURE_PATH_01_07;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					faceID = TEXTURE_PATH_01_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					flipVert = 1;
					faceID = TEXTURE_PATH_01_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					flipVert = 1;
					faceID = TEXTURE_PATH_01_05;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					faceID = TEXTURE_PATH_01_05;
				}
				else
					faceID = TEXTURE_PATH_01_00;
			}

			// yellow queue
			else if(thePark.paths[a][b][c].pathModifier == 2)
			{
				if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					faceID = TEXTURE_PATH_02_07;
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
				{
					faceID = TEXTURE_PATH_02_07;
					rotateClock = 1;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					faceID = TEXTURE_PATH_02_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					flipVert = 1;
					faceID = TEXTURE_PATH_02_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					flipVert = 1;
					faceID = TEXTURE_PATH_02_05;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					faceID = TEXTURE_PATH_02_05;
				}
				else
					faceID = TEXTURE_PATH_02_00;
			}

			// green queue
			else
			{
				if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					faceID = TEXTURE_PATH_03_07;
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
				{
					faceID = TEXTURE_PATH_03_07;
					rotateClock = 1;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					faceID = TEXTURE_PATH_03_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					flipVert = 1;
					faceID = TEXTURE_PATH_03_05;
				}
				else if(thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE)
				{
					flipVert = 1;
					faceID = TEXTURE_PATH_03_05;
				}
				else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectS == TRUE)
				{
					flipHoriz = 1;
					faceID = TEXTURE_PATH_03_05;
				}
				else
					faceID = TEXTURE_PATH_03_00;
			}
		}
		
		//if we have tarmac
		else if(thePark.paths[a][b][c].pathType == 1)
		{
			// grey tarmac
			if(thePark.paths[a][b][c].pathModifier == 0)
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_04_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_04_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_04_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_04_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_04_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_04_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_04_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_04_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_04_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_04_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_04_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_04_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_04_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_04_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_04_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_04_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_04_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_04_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_04_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_04_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_04_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_04_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_04_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_04_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_04_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_04_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_04_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_04_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_04_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_04_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_04_1D;
					}
				}
			}

			// red tarmac
			else if(thePark.paths[a][b][c].pathModifier == 1)
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_05_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_05_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_05_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_05_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_05_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_05_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_05_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_05_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_05_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_05_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_05_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_05_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_05_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_05_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_05_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_05_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_05_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_05_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_05_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_05_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_05_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_05_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_05_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_05_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_05_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_05_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_05_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_05_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_05_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_05_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_05_1D;
					}
				}
			}

			// brown tarmac
			else if(thePark.paths[a][b][c].pathModifier == 2)
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_06_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_06_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_06_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_06_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_06_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_06_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_06_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_06_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_06_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_06_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_06_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_06_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_06_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_06_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_06_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_06_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_06_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_06_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_06_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_06_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_06_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_06_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_06_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_06_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_06_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_06_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_06_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_06_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_06_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_06_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_06_1D;
					}
				}
			}

			// green tarmac
			else
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_07_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_07_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_07_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_07_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_07_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_07_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_07_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_07_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_07_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_07_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_07_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_07_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_07_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_07_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_07_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_07_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_07_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_07_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_07_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_07_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_07_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_07_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_07_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_07_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_07_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_07_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_07_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_07_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_07_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_07_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_07_1D;
					}
				}
			}
		}								
		//if we have dirt
		else if(thePark.paths[a][b][c].pathType == 2)
		{
			// dirt
			if(thePark.paths[a][b][c].pathModifier == 0)
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_0D_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_0D_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_0D_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_0D_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_0D_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0D_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0D_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_0D_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0D_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_0D_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_0D_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0D_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0D_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0D_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0D_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0D_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_0D_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0D_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_0D_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0D_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_0D_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_0D_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0D_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_0D_1D;
					}
				}

			}
			// black dirt
			else 
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_0E_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_0E_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_0E_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_0E_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_0E_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0E_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0E_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_0E_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0E_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_0E_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_0E_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0E_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0E_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0E_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0E_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0E_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_0E_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0E_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_0E_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0E_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_0E_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_0E_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0E_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_0E_1D;
					}
				}					
			}
		}
		
		//if we have crazy tile
		else if(thePark.paths[a][b][c].pathType == 3)
		{
			if(thePark.paths[a][b][c].pathModifier == 0)
			{
				if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
				{
					if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						faceID = TEXTURE_PATH_0C_14;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_0C_05;
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_0C_05;
						rotateClock = 1;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						faceID = TEXTURE_PATH_0C_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;								
						faceID = TEXTURE_PATH_0C_07;
					}
					else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_07;
					}
					else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0C_10;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0C_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_10;
					}
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_10;
					}

					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						faceID = TEXTURE_PATH_0C_01;
					else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_01;
					}
					else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0C_01;
					}
					else						
					// these paths have no corner connections
						faceID = TEXTURE_PATH_0C_00;
				}
				else
				{
					//these paths have at least one corner connection
					if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_0C_0B;

					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0C_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_0C;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0C_0C;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_0C;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0C_15;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_15;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0C_15;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						faceID = TEXTURE_PATH_0C_21;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_21;
					}

					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_0C_19;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_19;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						faceID = TEXTURE_PATH_0C_19;
					}


					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						faceID = TEXTURE_PATH_0C_23;
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipHoriz = 1;
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
					{
						flipVert = 1;																
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
					{
						flipHoriz = 1;																
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_23;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{
						rotateClock = 1;								
						faceID = TEXTURE_PATH_0C_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{																
						flipVert = 1;
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{								
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
						&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
					{							
						faceID = TEXTURE_PATH_0C_27;
					}
					else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						faceID = TEXTURE_PATH_0C_1D;
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						flipHoriz = 1;
						faceID = TEXTURE_PATH_0C_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
					{
						rotateClock = 1;
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_1D;
					}
					else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						flipVert = 1;
						faceID = TEXTURE_PATH_0C_1D;
					}
				}
			}
		}
		//if we have tile
		else if(thePark.paths[a][b][c].pathType == 5)
		{
			// beige tile
			if(thePark.paths[a][b][c].pathModifier == 0)
			{
				if(thePark.paths[a][b][c].pathModifier == 0)
				{
					if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
							faceID = TEXTURE_PATH_08_14;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_08_05;
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_08_05;
							rotateClock = 1;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_08_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;								
							faceID = TEXTURE_PATH_08_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_08_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_08_10;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_08_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_08_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_08_10;
						}

						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_08_01;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_08_01;
						}
						else						
						// these paths have no corner connections
							faceID = TEXTURE_PATH_08_00;
					}
					else
					{
						//these paths have at least one corner connection
						if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_08_0B;

						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_08_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_08_0C;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_0C;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_08_15;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_08_15;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_08_21;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_21;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_08_19;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_08_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_08_19;
						}


						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_08_23;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							rotateClock = 1;								
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;																
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;																
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_08_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_08_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{																
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_08_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{							
							faceID = TEXTURE_PATH_08_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_08_1D;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_08_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_08_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_08_1D;
						}
					}
				}
			}
			
			// grey tile
			else if(thePark.paths[a][b][c].pathModifier == 1)
			{
					if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
							faceID = TEXTURE_PATH_09_14;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_09_05;
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_09_05;
							rotateClock = 1;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_09_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;								
							faceID = TEXTURE_PATH_09_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_09_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_09_10;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_09_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_09_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_09_10;
						}

						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_09_01;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_09_01;
						}
						else						
						// these paths have no corner connections
							faceID = TEXTURE_PATH_09_00;
					}
					else
					{
						//these paths have at least one corner connection
						if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_09_0B;

						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_09_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_09_0C;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_0C;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_09_15;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_09_15;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_09_21;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_21;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_09_19;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_09_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_09_19;
						}


						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_09_23;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							rotateClock = 1;								
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;																
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;																
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_09_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_09_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{																
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_09_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{							
							faceID = TEXTURE_PATH_09_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_09_1D;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_09_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_09_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_09_1D;
						}
					}
			
			}
			
			// red tile
			else if(thePark.paths[a][b][c].pathModifier == 2)
			{
					if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
							faceID = TEXTURE_PATH_0A_14;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_0A_05;
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_0A_05;
							rotateClock = 1;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_0A_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;								
							faceID = TEXTURE_PATH_0A_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0A_10;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0A_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_10;
						}

						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_0A_01;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0A_01;
						}
						else						
						// these paths have no corner connections
							faceID = TEXTURE_PATH_0A_00;
					}
					else
					{
						//these paths have at least one corner connection
						if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_0A_0B;

						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0A_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0A_0C;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_0C;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0A_15;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0A_15;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0A_21;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_21;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_0A_19;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0A_19;
						}


						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_0A_23;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							rotateClock = 1;								
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;																
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;																
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_0A_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{																
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{							
							faceID = TEXTURE_PATH_0A_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_0A_1D;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0A_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_0A_1D;
						}
					}
			}
			// green tile
			else
			{
					if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE)
					{
						if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
							faceID = TEXTURE_PATH_0B_14;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_0B_05;
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_0B_05;
							rotateClock = 1;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							faceID = TEXTURE_PATH_0B_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;								
							faceID = TEXTURE_PATH_0B_07;
						}
						else if(thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_07;
						}
						else if(thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0B_10;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0B_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_10;
						}
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_10;
						}

						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE)
							faceID = TEXTURE_PATH_0B_01;
						else if(thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == FALSE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_01;
						}
						else if(thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE && thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == FALSE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0B_01;
						}
						else						
						// these paths have no corner connections
							faceID = TEXTURE_PATH_0B_00;
					}
					else
					{
						//these paths have at least one corner connection
						if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_0B_0B;

						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0B_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_0C;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0B_0C;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_0C;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0B_15;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_15;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0B_15;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
							faceID = TEXTURE_PATH_0B_21;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_21;
						}

						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_0B_19;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_19;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							faceID = TEXTURE_PATH_0B_19;
						}


						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
							faceID = TEXTURE_PATH_0B_23;
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipHoriz = 1;
							rotateClock = 1;								
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == FALSE && thePark.paths[a][b][c].connectW == TRUE)
						{
							flipVert = 1;																
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == FALSE)
						{
							flipHoriz = 1;																
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == FALSE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == FALSE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_23;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{
							rotateClock = 1;								
							faceID = TEXTURE_PATH_0B_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{																
							flipVert = 1;
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{								
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == FALSE
							&& thePark.paths[a][b][c].connectN == TRUE && thePark.paths[a][b][c].connectS == TRUE && thePark.paths[a][b][c].connectE == TRUE && thePark.paths[a][b][c].connectW == TRUE)
						{							
							faceID = TEXTURE_PATH_0B_27;
						}
						else if(thePark.paths[a][b][c].connectNE == FALSE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
							faceID = TEXTURE_PATH_0B_1D;
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == FALSE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							flipHoriz = 1;
							faceID = TEXTURE_PATH_0B_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == FALSE && thePark.paths[a][b][c].connectNW == TRUE)
						{
							rotateClock = 1;
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_1D;
						}
						else if(thePark.paths[a][b][c].connectNE == TRUE && thePark.paths[a][b][c].connectSE == TRUE && thePark.paths[a][b][c].connectSW == TRUE && thePark.paths[a][b][c].connectNW == FALSE)
						{
							flipVert = 1;
							faceID = TEXTURE_PATH_0B_1D;
						}
					}

			}
			
		}
		

		
		if(CubeInFrustum((float)(thePark.paths[a][b][c].x*UNITWIDTH), (float)((thePark.paths[a][b][c].base * UNITHEIGHT) - 0.1f), (float)(thePark.paths[a][b][c].z*UNITWIDTH), (float)(UNITWIDTH), (float)((thePark.paths[a][b][c].base + 1) + 0.1f), (float)(UNITWIDTH)) == TRUE) 
		{
			glPushMatrix();

				float texCoord[4][2];

				texCoord[0][0] = 1.0f;
				texCoord[0][1] = 1.0f;

				texCoord[1][0] = 0.0f;
				texCoord[1][1] = 1.0f;

				texCoord[2][0] = 1.0f;
				texCoord[2][1] = 0.0f;

				texCoord[3][0] = 0.0f;
				texCoord[3][1] = 0.0f;

				if(rotateClock > 0)
				{
					texCoord[0][0] = 1.0f;
					texCoord[0][1] = 0.0f;

					texCoord[1][0] = 1.0f;
					texCoord[1][1] = 1.0f;

					texCoord[2][0] = 0.0f;
					texCoord[2][1] = 0.0f;

					texCoord[3][0] = 0.0f;
					texCoord[3][1] = 1.0f;
				}

				if(flipVert > 0)
				{
					if(texCoord[0][1] == 1.0f)
						texCoord[0][1] = 0.0f;
					else
						texCoord[0][1] = 1.0f;

					if(texCoord[1][1] == 1.0f)
						texCoord[1][1] = 0.0f;
					else
						texCoord[1][1] = 1.0f;

					if(texCoord[2][1] == 1.0f)
						texCoord[2][1] = 0.0f;
					else
						texCoord[2][1] = 1.0f;

					if(texCoord[3][1] == 1.0f)
						texCoord[3][1] = 0.0f;
					else
						texCoord[3][1] = 1.0f;

				}

				if(flipHoriz > 0)
				{
					if(texCoord[0][0] == 1.0f)
						texCoord[0][0] = 0.0f;
					else
						texCoord[0][0] = 1.0f;

					if(texCoord[1][0] == 1.0f)
						texCoord[1][0] = 0.0f;
					else
						texCoord[1][0] = 1.0f;

					if(texCoord[2][0] == 1.0f)
						texCoord[2][0] = 0.0f;
					else
						texCoord[2][0] = 1.0f;

					if(texCoord[3][0] == 1.0f)
						texCoord[3][0] = 0.0f;
					else
						texCoord[3][0] = 1.0f;
				}


				//glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

				//if side1 == -1, then the texture/object is undefined
				if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 0)
				{

					glDisable(GL_LIGHTING);
					glShadeModel(GL_FLAT);

					double val = calcLightFactor(0.0f, 1.0f, 0.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);		



					if(faceID != lastTexture)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[faceID] );
						lastTexture = faceID;
					}

					glBegin(GL_TRIANGLE_STRIP);

					//glNormal3f(0.0f, 1.0f, 0.0f);

						glTexCoord2f(texCoord[0][0], texCoord[0][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[1][0], texCoord[1][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[2][0], texCoord[2][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
						glTexCoord2f(texCoord[3][0], texCoord[3][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

					glEnd();

					//glEnable(GL_LIGHTING);
					//glShadeMode(GL_FLAT);

				}
				// slope of 4 = slope to East
				else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 4)
				{

					glDisable(GL_LIGHTING);
					glShadeModel(GL_FLAT);

					double val = calcLightFactor(0.0f, UNITWIDTH, -UNITHEIGHT);
					//double val = calcLightFactor(-UNITHEIGHT, UNITWIDTH, 0.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);		

					if(faceID != lastTexture)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[faceID] );
						lastTexture = faceID;
					}


					glBegin(GL_TRIANGLE_STRIP);

						glTexCoord2f(texCoord[0][0], texCoord[0][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[1][0], texCoord[1][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[2][0], texCoord[2][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
						glTexCoord2f(texCoord[3][0], texCoord[3][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

					glEnd();

					//glEnable(GL_LIGHTING);
				}
				// slope of 5 = slope to North
				else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 5)
				{
					glDisable(GL_LIGHTING);
					glShadeModel(GL_FLAT);

					//double val = calcLightFactor(0.0f, UNITWIDTH, -UNITHEIGHT);
					double val = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);	

					if(faceID != lastTexture)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[faceID] );
						lastTexture = faceID;
					}


					glBegin(GL_TRIANGLE_STRIP);
					
						glTexCoord2f(texCoord[0][0], texCoord[0][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1)* UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[1][0], texCoord[1][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[2][0], texCoord[2][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
						glTexCoord2f(texCoord[3][0], texCoord[3][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

					glEnd();

					glDisable(GL_LIGHTING);
				}
				// slope of 6 = slope to West
				else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 6)
				{
					glDisable(GL_LIGHTING);
					glShadeModel(GL_FLAT);

					//double val = calcLightFactor(UNITHEIGHT, UNITWIDTH, 0.0f);
					double val = calcLightFactor(0.0f, UNITWIDTH, UNITWIDTH);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);		

					if(faceID != lastTexture)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[faceID] );
						lastTexture = faceID;
					}


					glBegin(GL_TRIANGLE_STRIP);
					
						glTexCoord2f(texCoord[0][0], texCoord[0][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[1][0], texCoord[1][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[2][0], texCoord[2][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
						glTexCoord2f(texCoord[3][0], texCoord[3][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

					glEnd();

					glDisable(GL_LIGHTING);
				}
				// slope of 7 = slope to South
				else if (side1 > 0 && thePark.paths[a][b][c].pathSlope == 7)
				{

					double val = calcLightFactor(-UNITHEIGHT, UNITWIDTH, 0.0f);
					//double val = calcLightFactor(0.0f, UNITWIDTH, UNITHEIGHT);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);	


					if(faceID != lastTexture)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[faceID] );
						lastTexture = faceID;
					}


					glBegin(GL_TRIANGLE_STRIP);
					
						glTexCoord2f(texCoord[0][0], texCoord[0][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[1][0], texCoord[1][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1)* UNITHEIGHT + 0.1,       thePark.paths[a][b][c].z * UNITWIDTH);
						glTexCoord2f(texCoord[2][0], texCoord[2][1]);
						glVertex3d((thePark.paths[a][b][c].x + 1) * UNITWIDTH,     thePark.paths[a][b][c].base * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);
						glTexCoord2f(texCoord[3][0], texCoord[3][1]);
						glVertex3d(      thePark.paths[a][b][c].x * UNITWIDTH,     (thePark.paths[a][b][c].base + 1) * UNITHEIGHT + 0.1, (thePark.paths[a][b][c].z + 1) * UNITWIDTH);

					glEnd();

					glDisable(GL_LIGHTING);
				}
			glPopMatrix();	
		}
	}

	glDisable(GL_ALPHA_TEST);

	glDisable(GL_TEXTURE_2D);


}


