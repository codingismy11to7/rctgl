#include "vr3d.h"

int FileFormat;
float TrackOrientationsRad[8];
TrackStructType TrackSetup[500];
int TrackLength;

extern char RCTGL_Location[256];

/* -- decompressFile() --
 * decompresses a file that is compressed with RLE encoding
 */
void DecompressFile(char *filename, char *tempfilename)
{
//	char *commandline;
	
//	char RCTGLLocCopy[256];

//	char *dum;

	char countbyte;
	unsigned char databyte;

	int i;

	FILE *input, *output;

	//open the streams
	if((input = fopen(filename, "rb")) == NULL)
	{
		MessageBox(NULL, "fopen error(input)", "TITTIE", MB_OK);
		printf("fopen error (input)\n");
	}
	else
		printf("fopen %s sucessful\n", filename);

	
	if((output = fopen(tempfilename, "wb")) == NULL)
	{
		MessageBox(NULL, "fopen error(output)", "TITTIE", MB_OK);
		printf("fopen error (output) %s\n", tempfilename);
	}
	else
		printf("fopen %s successful\n", tempfilename);

	//loop through the input file
	while (!feof(input))
	{
		countbyte = fgetc(input);

		//if the most sig. bit is zero, we copy the next byte countbyte + 1 times
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


}

