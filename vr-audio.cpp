#include "vr3d.h"

extern AudioStructType AudioSpecifiers[256];
extern int AudioSpecifierCount;


void clearAudioInformation(void)
{
	int i, j, k;

	AudioSpecifierCount = 0;

	//clear the subscription lists
	for(i=0; i<128; i++)
		for(j=0; j<128; j++)
			for(k=0 ;k<10; k++)
				thePark.audioSubscriptions[i][j][k] = -1;

	//clear the individual subscriptions
	for(i=0; i<256; i++)
	{
		AudioSpecifiers[i].audioType = CD;
		AudioSpecifiers[i].trackNum = -1;
		AudioSpecifiers[i].volume = -1;
		AudioSpecifiers[i].fileName[0] = '\0';
		AudioSpecifiers[i].triggerX = -1;
		AudioSpecifiers[i].triggerY = -1;
		AudioSpecifiers[i].triggerZ = -1;
		AudioSpecifiers[i].triggerRideIndex = -1;
		AudioSpecifiers[i].minTime = -1;
		AudioSpecifiers[i].maxTime = -1;
		AudioSpecifiers[i].soundType = ambient;
		AudioSpecifiers[i].sourceX = -1;
		AudioSpecifiers[i].sourceY = -1;
		AudioSpecifiers[i].sourceZ = -1;		
	}
}

int doesCDAudioExist(int tracknum, int volume)
{
	int retval = -1;
	int i;

	for(i=0; i<AudioSpecifierCount; i++)
	{
		if(AudioSpecifiers[i].audioType == CD &&
			AudioSpecifiers[i].trackNum == tracknum &&
			AudioSpecifiers[i].volume == volume)
		{
			retval = i;
			break;
		}
	}

	return retval;
}

int doesFileAmbientExist()
{
	int retval = -1;

	return retval;
}

int doesFileEffectExist()
{
	int retval = -1;

	return retval;
}

int doesFileEventExist()
{
	int retval = -1;

	return retval;
}



FILE* loadAudioDescriptor(FILE* infile)
{
	char tempstr[128];
	int returned;
	int tempval;
	int trackNum;
	int volume;


	int minX, minY, maxX, maxY;

	int i,j,k;
	
	printf("in loadAudioDescriptor\n");

	//get the audio type
	returned = -1;
	while(returned != 1)
		returned = fscanf(infile, "audioType = %s\n", &tempstr[0]);

	printf("audioType = %s\n", &tempstr[0]);

	//load the cd information
	if(strcmp(&tempstr[0], "CD") == 0)
	{
		int trackNum;

		//get the track number
		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "trackNum = %d\n", &trackNum);

		printf("trackNum = %d\n", trackNum);

		//get the volume
		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "volume = %d\n", &volume);

		printf("volume = %d\n", volume);

		//get the range
		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "minXRange = %d\n", &minX);

		printf("minXRange = %d\n", minX);

		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "minYRange = %d\n", &minY);

		printf("minYRange = %d\n", minY);

		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "maxXRange = %d\n", &maxX);

		printf("maxXRange = %d\n", maxX);

		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "maxYRange = %d\n", &maxY);

		printf("maxYRange = %d\n", maxY);

		tempval = doesCDAudioExist(trackNum, tempval);		

		if(doesCDAudioExist(trackNum, tempval) < 0)
		{
			printf("CDAudio doesn't exist\n");

			AudioSpecifiers[AudioSpecifierCount].audioType = CD;
			AudioSpecifiers[AudioSpecifierCount].trackNum = trackNum;
			AudioSpecifiers[AudioSpecifierCount].volume = tempval;

			tempval = AudioSpecifierCount;

			AudioSpecifierCount++;
		}
		else
			printf("CDAudio exists\n");

		//now populate the cells		
		for(i=minX; i<=maxX; i++)
		{
			for(j=minY; j<=maxY; j++)
			{
				for(k=0; k<10; k++)
				{
					if(thePark.audioSubscriptions[i][j][k] == -1)
					{
						thePark.audioSubscriptions[i][j][k] = tempval;
						break;
					}
				}
			}
		}
				


	}
	else if(strcmp(&tempstr[0], "fileAmbient") == 0)
	{
		//get the filename
		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "fileName = %d\n", &tempstr[0]);

		printf("fileName = %s\n", &tempstr[0]);

		//get the volume
		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "volume = %d\n", &volume);

		printf("volume = %d\n", volume);

		//get the range
		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "minXRange = %d\n", &tempval);

		printf("minXRange = %d\n", tempval);

		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "minYRange = %d\n", &tempval);

		printf("minYRange = %d\n", tempval);

		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "maxXRange = %d\n", &tempval);

		printf("maxXRange = %d\n", tempval);

		returned = -1;
		while(returned != 1)
			returned = fscanf(infile, "maxYRange = %d\n", &tempval);

		printf("maxYRange = %d\n", tempval);

	}
	else if(strcmp(&tempstr[0], "fileEvent") == 0)
	{

	}
	else if(strcmp(&tempstr[0], "fileEffect") == 0)
	{

	}

	
	return infile;
}

