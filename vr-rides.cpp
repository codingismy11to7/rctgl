#include "vr3d.h"
#include <string.h>

RideStructType RideList[256];
int RideListSize;


void LoadRides(char *filename)
{
	FILE *input;

	int i;

//	int i,j;
//	long nextbyte;
//	long currentbyte;
//	int tempheight;
//	int LLmodifier;
//	int looping;
	int mapsize = 128;

	unsigned char nameString[32];

	unsigned char buffer1, buffer2;
	int testOffset;
//	unsigned char endCheckBuffer;

	RideListSize = 0;

	printf("- in LoadRides()\n");

	input = fopen(filename, "rb");

	if(input == NULL)
		perror("fopen\n");

	//move to the ride info
	//fseek(input, 0x1A38A0, SEEK_SET);

	for(i=0; i<255; i++)
	{
		fseek(input, (i * 608) + 0x1A38A0 + 0x22, SEEK_SET);
		buffer1 = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x23, SEEK_SET);
		buffer2 = fgetc(input);

		testOffset = 0;

		if(buffer2 >= 128)
		{
			//buffer1 -= 128;

			testOffset = buffer1;

			
			if(buffer2 >= 128)
			{
				buffer2 -= 128;				
			}			

			if(buffer2 >= 64)
			{
				buffer2 -= 64;				
			}

			if(buffer2 >= 32)
			{
				buffer2 -= 32;				
			}

			if(buffer2 >= 16)
			{
				buffer2 -= 16;				
			}

			if(buffer2 >= 8)
			{
				buffer2 -= 8;				
			}

			if(buffer2 >= 4)
			{
				buffer2 -= 4;				
			}

			if(buffer2 >= 2)
			{
				buffer2 -= 2;
				testOffset += 512;
			}

			if(buffer2 >= 1)
			{
				buffer2 -= 1;	
				testOffset += 256;
			}

			fseek(input, 0x19B89C + (testOffset * 32), SEEK_SET);
			//fseek(input, 0x1A389B - (testOffset * 32), SEEK_SET);
			fread(&nameString[0], 1, 32, input);

			RideList[i].nameStringOffset = testOffset;
			//int len = strlen(testOffset);
			//*(testOffset + len - 1) = NULL;

			int tmp = strlen(thePark.nameStrings[RideList[i].nameStringOffset]);
			//thePark.nameStrings[RideList[i].nameStringOffset][tmp - 2] = NULL;

			for(int i=0; i<tmp; i++)
				printf("%c(%d) ", thePark.nameStrings[RideList[i].nameStringOffset][i], thePark.nameStrings[RideList[i].nameStringOffset][i]);

			printf("\n");


			//printf("text string index (%d): %d %s\n", i, RideList[i].nameStringOffset, &nameString[0]);

		}
		else
			RideList[i].nameStringOffset = -1;


		//fseek(input, (i * 608) + 0x1A38A0 + 0x22, SEEK_SET);
		//printf("text string index2 = %d\n", fgetc(input));

		//move to the ride info
		fseek(input, (i * 608) + 0x1A38A0, SEEK_SET);
		RideList[i].rideType = fgetc(input);

		//printf("foud ride type %d\n", RideList[i].rideType);

		fseek(input, (i * 608) + 0x1A38A0 + 0x01, SEEK_SET);
		RideList[i].vehicleType = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x04, SEEK_SET);
		RideList[i].operatingMode = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x16C, SEEK_SET);
		RideList[i].PrimaryColor[0] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x16D, SEEK_SET);
		RideList[i].PrimaryColor[1] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x16E, SEEK_SET);
		RideList[i].PrimaryColor[2] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x16F, SEEK_SET);
		RideList[i].PrimaryColor[3] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x170, SEEK_SET);
		RideList[i].SecondaryColor[0] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x171, SEEK_SET);
		RideList[i].SecondaryColor[1] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x172, SEEK_SET);
		RideList[i].SecondaryColor[2] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x173, SEEK_SET);
		RideList[i].SecondaryColor[3] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x174, SEEK_SET);
		RideList[i].SupportColor[0] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x175, SEEK_SET);
		RideList[i].SupportColor[1] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x176, SEEK_SET);
		RideList[i].SupportColor[2] = fgetc(input);

		fseek(input, (i * 608) + 0x1A38A0 + 0x177, SEEK_SET);
		RideList[i].SupportColor[3] = fgetc(input);

		//printf("colors for ride %d (%d %d %d)\n", i, RideList[i].PrimaryColor[0], RideList[i].SecondaryColor[0], RideList[i].SupportColor[0]);
	}

	//for(i=0; i<256; i++)
	//	printf("string index for ride #%d is %d\n", i, thePark.rides[i].nameStringOffset);

	printf("RideListSize = %d\n", RideListSize);
}

