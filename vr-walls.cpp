#include "vr3d.h" 

//WallStructType WallList[15876];
//int WallListSize;

//extern landscape_t parkLandscape[128][128];

extern ParkStructType thePark;

extern float edgeLighting[4][4];

void LoadWalls(char *filename)
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

	//WallListSize = 0;

	printf("- in LoadWalls()\n");

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
				//if (buffer >= 4 && buffer <= 7)
				if (buffer >= 20 && buffer <= 23)
				{
					AddWall(input, currentbyte, i, j, buffer - 20);
					//break;
				}
				if (buffer >= 84 && buffer <= 87)
				{
					AddWall(input, currentbyte, i, j, buffer - 84);
					//break;
				}
				if (buffer >= 148 && buffer <= 151)
				{
					AddWall(input, currentbyte, i, j, buffer - 148);
					//break;
				}
				if (buffer >= 212 && buffer <= 215)
				{
					AddWall(input, currentbyte, i, j, buffer - 212);
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

	//printf("WallListSize = %d\n", WallListSize);
}

/* adds a path to the linked list of paths */
void AddWall(FILE *input, int offset, int x, int z, int modifier)
{
	unsigned char buffer;
//	float objBase, objCeiling;
//	int objIdentity;
	int tempheight;

	int NWall, SWall, EWall, WWall;
	int tempbyte1, tempbyte2, tempbyte3;
	

	// the file should already be at the correct position, so
	// we can retrieve the scenery information

	/*	byte #0 - scenery type
		byte #1 - not important
		byte #2 - base height
		byte #3 - object clearance
		byte #4 - slope
		byte #5 -	bit 7 = S5, bit 6 = S4, bit 5 = E5, bit 4 = E4
					bit 3 = N5, bit 2 = N4, bit 1 = W5, bit 0 = W4
		byte #6 -	bit 7 = N3, bit 6 = N2, bit 5 = N1, bit 4 = N0
					bit 3 = W3, bit 2 = W2, bit 1 = W1, bit 0 = W0
		byte #7 -	bit 7 = S3, bit 6 = S2, bit 5 = S1, bit 4 = S0
					bit 3 = E3, bit 2 = E2, bit 1 = E1, bit 0 = E0
		
	*/

	// we can skip over byte #0 since it was already checked
	
	// we can skip over byte #1 for now

	WallStructType *newWall = new WallStructType;
	
	// we need to get the item's base height (byte #2)
	fseek(input, offset + 2, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newWall->base = (float)(tempheight / 4.0f);
	else
		newWall->base = 0.0f;

	// we need to get the item's ceiling (byte #3)
	fseek(input, offset + 3, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newWall->ceiling = (float)(tempheight / 4.0f);
	else
		newWall->ceiling = 0.0f;

	// we need to get the wall type and slope
	fseek(input, offset + 5, SEEK_SET);
	tempbyte1 = fgetc(input);

	fseek(input, offset + 6, SEEK_SET);
	tempbyte2 = fgetc(input);

	fseek(input, offset + 7, SEEK_SET);
	tempbyte3 = fgetc(input);

	NWall = 0;
	SWall = 0;
	EWall = 0;
	WWall = 0;

	//process the first byte
	if(tempbyte1 >= 128)
	{
		SWall += 32;
		tempbyte1 -= 128;
	}
	if(tempbyte1 >= 64)
	{
		SWall += 16;
		tempbyte1 -= 64;
	}
	if(tempbyte1 >= 32)
	{
		EWall += 32;
		tempbyte1 -= 32;
	}
	if(tempbyte1 >= 16)
	{
		EWall += 16;
		tempbyte1 -= 16;
	}
	if(tempbyte1 >= 8)
	{
		NWall += 32;
		tempbyte1 -= 8;
	}
	if(tempbyte1 >= 4)
	{
		NWall += 16;
		tempbyte1 -= 4;
	}
	if(tempbyte1 >= 2)
	{
		WWall += 32;
		tempbyte1 -= 2;
	}
	if(tempbyte1 >= 1)
	{
		WWall += 16;
		tempbyte1 -= 1;
	}

	//process the second byte
	if(tempbyte2 >= 128)
	{
		NWall += 8;
		tempbyte2 -= 128;
	}
	if(tempbyte2 >= 64)
	{
		NWall += 4;
		tempbyte2 -= 64;
	}
	if(tempbyte2 >= 32)
	{
		NWall += 2;
		tempbyte2 -= 32;
	}
	if(tempbyte2 >= 16)
	{
		NWall += 1;
		tempbyte2 -= 16;
	}
	if(tempbyte2 >= 8)
	{
		WWall += 8;
		tempbyte2 -= 8;
	}
	if(tempbyte2 >= 4)
	{
		WWall += 4;
		tempbyte2 -= 4;
	}
	if(tempbyte2 >= 2)
	{
		WWall += 2;
		tempbyte2 -= 2;
	}
	if(tempbyte2 >= 1)
	{
		WWall += 1;
		tempbyte2 -= 1;
	}

	//process the third byte
	if(tempbyte3 >= 128)
	{
		SWall += 8;
		tempbyte3 -= 128;
	}
	if(tempbyte3 >= 64)
	{
		SWall += 4;
		tempbyte3 -= 64;
	}
	if(tempbyte3 >= 32)
	{
		SWall += 2;
		tempbyte3 -= 32;
	}
	if(tempbyte3 >= 16)
	{
		SWall += 1;
		tempbyte3 -= 16;
	}
	if(tempbyte3 >= 8)
	{
		EWall += 8;
		tempbyte3 -= 8;
	}
	if(tempbyte3 >= 4)
	{
		EWall += 4;
		tempbyte3 -= 4;
	}
	if(tempbyte3 >= 2)
	{
		EWall += 2;
		tempbyte3 -= 2;
	}
	if(tempbyte3 >= 1)
	{
		EWall += 1;
		tempbyte3 -= 1;
	}

	newWall->wallTypeN = NWall;
	newWall->wallTypeS = SWall;
	newWall->wallTypeE = EWall;
	newWall->wallTypeW = WWall;
	
	//finally, we need to assign the x and z coordinates to the path

	newWall->x = x;
	newWall->z = z;

	thePark.walls[x][z].push_back(*newWall);
}

void DrawWalls(int a, int b)
{
	float tmpHeight1, tmpHeight2;

	int c;
	int texSupported;

	glEnable(GL_TEXTURE_2D);

	if(CubeInFrustum((float)(a*UNITWIDTH), (float)((thePark.landscape[a][b].lowest * UNITHEIGHT) - 0.1f), (float)(b*UNITWIDTH), (float)(UNITWIDTH), (float)((thePark.landscape[a][b].lowest + 1) + 0.1f), (float)(UNITWIDTH)) == TRUE) 
	{
		for(c=0; c<thePark.walls[a][b].size(); c++)
		{
			if(thePark.walls[a][b][c].wallTypeN != 0x0F && thePark.walls[a][b][c].wallTypeN != 0x1F &&
				thePark.walls[a][b][c].wallTypeN != 0x2F && thePark.walls[a][b][c].wallTypeN != 0x3F)
			{
				//printf("tmpheight=%f\n",tmpHeight);
				tmpHeight1 = (float)thePark.landscape[a][b].TL;
				tmpHeight2 = (float)thePark.landscape[a][b].BL;

				if(thePark.walls[a][b][c].base > tmpHeight1 && thePark.walls[a][b][c].base > tmpHeight2)
					tmpHeight1 = tmpHeight2 = thePark.walls[a][b][c].base;

				texSupported = 1;

				if(thePark.walls[a][b][c].wallTypeN == 0x00)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x01)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x02)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x03)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x04)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x05)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x06)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x07)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x08)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x09)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x11)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x12)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x14)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x1A)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x20)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x21)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x22)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x23)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x24)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x26)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x27)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x28)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x2B)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x30)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x31)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x33)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x34)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x35)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x36)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x37)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x38)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
				}
				else if(thePark.walls[a][b][c].wallTypeN == 0x3B)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
				}
				else
				{
					texSupported = -1;

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );
				}

				if(texSupported > 0)
				{
					glPushMatrix();

						glTranslated((thePark.walls[a][b][c].x + 0.98f) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z) * UNITWIDTH);

						glBegin(GL_QUADS);

							if(XV <= (a + 0.5f) * UNITWIDTH)
								glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);
							else
								glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);
						
							//glColor3f(1.0f, 1.0f, 1.0f);
							glTexCoord2f(0.0f, 0.0f);
							glVertex3d(0.0f,	tmpHeight2 * UNITHEIGHT,		0.0f);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3d(0.0f,	tmpHeight1 * UNITHEIGHT,		UNITWIDTH);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3d(0.0f,	(tmpHeight1 + 1.0f) * UNITHEIGHT, UNITWIDTH);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3d(0.0f,	(tmpHeight2 + 1.0f) * UNITHEIGHT, 0.0f);
						glEnd();

					glPopMatrix();
				}

				glDisable(GL_ALPHA_TEST);
			}

			if(thePark.walls[a][b][c].wallTypeS != 0x0F && thePark.walls[a][b][c].wallTypeS != 0x1F &&
				thePark.walls[a][b][c].wallTypeS != 0x2F && thePark.walls[a][b][c].wallTypeS != 0x3F)
			{
				tmpHeight1 = (float)thePark.landscape[a][b].TR;
				tmpHeight2 = (float)thePark.landscape[a][b].BR;

				if(thePark.walls[a][b][c].base > tmpHeight1 && thePark.walls[a][b][c].base > tmpHeight2)
					tmpHeight1 = tmpHeight2 = thePark.walls[a][b][c].base;

				texSupported = 1;

				if(thePark.walls[a][b][c].wallTypeS == 0x00)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x01)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x02)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x03)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x04)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x05)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x06)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x07)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x08)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x09)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x11)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x12)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x14)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x1A)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x20)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x21)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x22)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x23)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x24)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x26)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x27)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x28)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x2B)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x30)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x31)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x33)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x34)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x35)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x36)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x37)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x38)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
				}
				else if(thePark.walls[a][b][c].wallTypeS == 0x3B)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
				}
				else
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

					texSupported = -1;
				}

				if(texSupported > 0)
				{
					glPushMatrix();

						glTranslated((thePark.walls[a][b][c].x + 0.02f) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z) * UNITWIDTH);

						glBegin(GL_QUADS);
						
							if(XV <= (a + 0.5f) * UNITWIDTH)
								glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);
							else
								glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);


							glTexCoord2f(0.0f, 0.0f);
							glVertex3d(0.0f,	tmpHeight2 * UNITHEIGHT,		0.0f);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3d(0.0f,	tmpHeight1 * UNITHEIGHT,		UNITWIDTH);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3d(0.0f,	(tmpHeight1 + 1.0f) * UNITHEIGHT, UNITWIDTH);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3d(0.0f,	(tmpHeight2 + 1.0f) * UNITHEIGHT, 0.0f);
						glEnd();

					glPopMatrix();
				}

				glDisable(GL_ALPHA_TEST);
			}

			if(thePark.walls[a][b][c].wallTypeW != 0x0F && thePark.walls[a][b][c].wallTypeW != 0x1F &&
				thePark.walls[a][b][c].wallTypeW != 0x2F && thePark.walls[a][b][c].wallTypeW != 0x3F)
			{
				tmpHeight1 = (float)thePark.landscape[a][b].BR;
				tmpHeight2 = (float)thePark.landscape[a][b].BL;

				if(thePark.walls[a][b][c].base > tmpHeight1 && thePark.walls[a][b][c].base > tmpHeight2)
					tmpHeight1 = tmpHeight2 = thePark.walls[a][b][c].base;

				texSupported = 1;

				if(thePark.walls[a][b][c].wallTypeW == 0x00)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x01)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x02)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x03)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x04)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x05)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x06)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x07)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x08)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x09)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x11)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x12)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x14)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x1A)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x20)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x21)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x22)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x23)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x24)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x26)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x27)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x28)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x2B)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x30)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x31)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x33)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x34)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x35)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x36)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x37)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x38)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
				}
				else if(thePark.walls[a][b][c].wallTypeW == 0x3B)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
				}
				else
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

					texSupported = -1;
				}

				if(texSupported > 0)
				{
					glPushMatrix();

						glTranslated((thePark.walls[a][b][c].x) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z + 0.02f) * UNITWIDTH);

						//glColor3f(1.0f, 1.0f, 1.0f);
						
						glBegin(GL_QUADS);

							if(ZV <= (b + 0.5f) * UNITWIDTH)
								glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);
							else
								glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);

							glTexCoord2f(0.0f, 0.0f);
							glVertex3d(0.0f,		(tmpHeight1 + 0.0f) * UNITHEIGHT,	0.0f);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3d(UNITWIDTH,	(tmpHeight2 + 0.0f) * UNITHEIGHT,	0.0f);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3d(UNITWIDTH,	(tmpHeight2 + 1.0f) * UNITHEIGHT,	0.0f);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3d(0.0f,		(tmpHeight1 + 1.0f) * UNITHEIGHT,	0.0f);
						glEnd();							

					glPopMatrix();
				}

				glDisable(GL_ALPHA_TEST);

			}

			if(thePark.walls[a][b][c].wallTypeE != 0x0F && thePark.walls[a][b][c].wallTypeE != 0x1F &&
				thePark.walls[a][b][c].wallTypeE != 0x2F && thePark.walls[a][b][c].wallTypeE != 0x3F)
			{
				tmpHeight1 = (float)thePark.landscape[a][b].TR;
				tmpHeight2 = (float)thePark.landscape[a][b].TL;

				if(thePark.walls[a][b][c].base > tmpHeight1 && thePark.walls[a][b][c].base > tmpHeight2)
					tmpHeight1 = tmpHeight2 = thePark.walls[a][b][c].base;

				texSupported = 1;

				if(thePark.walls[a][b][c].wallTypeE == 0x00)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x01)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x02)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x03)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x04)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x05)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x06)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x07)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x08)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x09)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x11)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x12)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x14)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x1A)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x20)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x21)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x22)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x23)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x24)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x26)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x27)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x28)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x2B)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x30)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x31)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x33)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x34)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x35)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x36)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x37)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x38)
				{
					glAlphaFunc ( GL_LESS, 0.4f );
					glEnable    ( GL_ALPHA_TEST   );

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
				}
				else if(thePark.walls[a][b][c].wallTypeE == 0x3B)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
				}
				else
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

					texSupported = -1;
				}


				if(texSupported > 0)
				{
					glPushMatrix();

						glTranslated((thePark.walls[a][b][c].x) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z + 0.98f) * UNITWIDTH);

						glBegin(GL_QUADS);
							if(ZV <= (b + 0.5f) * UNITWIDTH)
								glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);
							else
								glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);
						
							//glColor3f(1.0f, 1.0f, 1.0f);

							glTexCoord2f(0.0f, 0.0f);
							glVertex3d(0.0f,		(tmpHeight1 + 0.0f)* UNITHEIGHT,			0.0f);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3d(UNITWIDTH,	(tmpHeight2 + 0.0f) * UNITHEIGHT,	0.0f);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3d(UNITWIDTH,	(tmpHeight2 + 1.0f) * UNITHEIGHT,	0.0f);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3d(0.0f,		(tmpHeight1 + 1.0f) * UNITHEIGHT,			0.0f);
						glEnd();

					glPopMatrix();
				}

				glDisable(GL_ALPHA_TEST);
				
			}
		}
	}

	glDisable(GL_TEXTURE_2D);	
}


void oldDrawWalls(void)
{
//	int i;
//	int faceID;
//	int side1, side2;
	int Mdetailsize = 20;
	int Hdetailsize = 50;
	int mapsize = 128;
	double gridX, gridZ;
	double startX, endX;
	double startZ, endZ;

//	float tmpHeight;
	float tmpHeight1, tmpHeight2;

	//find the grid location of the viewpoint
	gridX = XV / UNITWIDTH;
	gridZ = ZV / UNITWIDTH;

	//printf("gridX:%d   gridZ:%d\n", gridX, gridZ);

	//precalculate the detailed regions to draw

	if(detailLevel == M_LOW_DETAIL || detailLevel == M_MEDIUM_DETAIL)
	{	
		//find the grid location of the viewpoint
		gridX = XV / UNITWIDTH;
		gridZ = ZV / UNITWIDTH;

		//printf("gridX:%d   gridZ:%d\n", gridX, gridZ);

		//precalculate the detailed regions to draw
		if (gridX - Mdetailsize < 0)
			startX = 0;
		else
			startX = gridX - Mdetailsize;

		if (gridX + Mdetailsize > mapsize)
			endX = mapsize;
		else
			endX = gridX + Mdetailsize;

		if (gridZ - Mdetailsize < 0)
			startZ = 0;
		else
			startZ = gridZ - Mdetailsize;

		if (gridZ + Mdetailsize > mapsize)
			endZ = mapsize;
		else
			endZ = gridZ + Mdetailsize;
	}
	else if(detailLevel == M_HIGH_DETAIL)
	{
		//find the grid location of the viewpoint
		gridX = XV / UNITWIDTH;
		gridZ = ZV / UNITWIDTH;

		//printf("gridX:%d   gridZ:%d\n", gridX, gridZ);

		//precalculate the detailed regions to draw
		if (gridX - Hdetailsize < 0)
			startX = 0;
		else
			startX = gridX - Hdetailsize;

		if (gridX + Hdetailsize > mapsize)
			endX = mapsize;
		else
			endX = gridX + Hdetailsize;

		if (gridZ - Hdetailsize < 0)
			startZ = 0;
		else
			startZ = gridZ - Hdetailsize;

		if (gridZ + Hdetailsize > mapsize)
			endZ = mapsize;
		else
			endZ = gridZ + Hdetailsize;
	}
	else
	{
		startX = 0;
		endX = mapsize;
		startZ = 0;
		endZ = mapsize;
	}

	int a,b,c;
	int texSupported;

	glEnable(GL_TEXTURE_2D);

	for(a=(int)(startX); a<(int)(endX); a++)
	{
		for(b=(int)(startZ); b<(int)(endZ); b++)
		{
			for(c=0; c<thePark.walls[a][b].size(); c++)
			{
				if(thePark.walls[a][b][c].wallTypeN != 0x0F && thePark.walls[a][b][c].wallTypeN != 0x1F &&
					thePark.walls[a][b][c].wallTypeN != 0x2F && thePark.walls[a][b][c].wallTypeN != 0x3F)
				{
					//printf("tmpheight=%f\n",tmpHeight);
					tmpHeight1 = (float)thePark.landscape[a][b].TL;
					tmpHeight2 = (float)thePark.landscape[a][b].BL;

					texSupported = 1;

					if(thePark.walls[a][b][c].wallTypeN == 0x00)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x01)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x02)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x03)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x04)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x05)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x06)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x07)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x08)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x09)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x11)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x12)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x14)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x1A)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x20)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x21)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x22)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x23)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x24)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x26)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x27)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x28)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x2B)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x30)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x31)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x33)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x34)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x35)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x36)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x37)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x38)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
					}
					else if(thePark.walls[a][b][c].wallTypeN == 0x3B)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
					}
					else
					{
						texSupported = -1;

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );
					}

					if(texSupported > 0)
					{
						glPushMatrix();

							glTranslated((thePark.walls[a][b][c].x + 0.98f) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z) * UNITWIDTH);

							glBegin(GL_QUADS);

								if(XV <= (a + 0.5f) * UNITWIDTH)
									glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);
								else
									glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);
							
								//glColor3f(1.0f, 1.0f, 1.0f);
								glTexCoord2f(0.0f, 0.0f);
								glVertex3d(0.0f,	tmpHeight2 * UNITHEIGHT,		0.0f);
								glTexCoord2f(1.0f, 0.0f);
								glVertex3d(0.0f,	tmpHeight1 * UNITHEIGHT,		UNITWIDTH);
								glTexCoord2f(1.0f, 1.0f);
								glVertex3d(0.0f,	(tmpHeight1 + 1.0f) * UNITHEIGHT, UNITWIDTH);
								glTexCoord2f(0.0f, 1.0f);
								glVertex3d(0.0f,	(tmpHeight2 + 1.0f) * UNITHEIGHT, 0.0f);
							glEnd();

						glPopMatrix();
					}

					glDisable(GL_ALPHA_TEST);
				}

				if(thePark.walls[a][b][c].wallTypeS != 0x0F && thePark.walls[a][b][c].wallTypeS != 0x1F &&
					thePark.walls[a][b][c].wallTypeS != 0x2F && thePark.walls[a][b][c].wallTypeS != 0x3F)
				{
					tmpHeight1 = (float)thePark.landscape[a][b].TR;
					tmpHeight2 = (float)thePark.landscape[a][b].BR;

					texSupported = 1;

					if(thePark.walls[a][b][c].wallTypeS == 0x00)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x01)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x02)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x03)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x04)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x05)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x06)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x07)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x08)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x09)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x11)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x12)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x14)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x1A)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x20)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x21)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x22)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x23)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x24)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x26)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x27)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x28)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x2B)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x30)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x31)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x33)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x34)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x35)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x36)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x37)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x38)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
					}
					else if(thePark.walls[a][b][c].wallTypeS == 0x3B)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
					}
					else
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

						texSupported = -1;
					}

					if(texSupported > 0)
					{
						glPushMatrix();

							glTranslated((thePark.walls[a][b][c].x + 0.02f) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z) * UNITWIDTH);

							glBegin(GL_QUADS);
							
								if(XV <= (a + 0.5f) * UNITWIDTH)
									glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);
								else
									glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);


								glTexCoord2f(0.0f, 0.0f);
								glVertex3d(0.0f,	tmpHeight2 * UNITHEIGHT,		0.0f);
								glTexCoord2f(1.0f, 0.0f);
								glVertex3d(0.0f,	tmpHeight1 * UNITHEIGHT,		UNITWIDTH);
								glTexCoord2f(1.0f, 1.0f);
								glVertex3d(0.0f,	(tmpHeight1 + 1.0f) * UNITHEIGHT, UNITWIDTH);
								glTexCoord2f(0.0f, 1.0f);
								glVertex3d(0.0f,	(tmpHeight2 + 1.0f) * UNITHEIGHT, 0.0f);
							glEnd();

						glPopMatrix();
					}

					glDisable(GL_ALPHA_TEST);
				}

				if(thePark.walls[a][b][c].wallTypeW != 0x0F && thePark.walls[a][b][c].wallTypeW != 0x1F &&
					thePark.walls[a][b][c].wallTypeW != 0x2F && thePark.walls[a][b][c].wallTypeW != 0x3F)
				{
					tmpHeight1 = (float)thePark.landscape[a][b].BR;
					tmpHeight2 = (float)thePark.landscape[a][b].BL;

					texSupported = 1;

					if(thePark.walls[a][b][c].wallTypeW == 0x00)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x01)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x02)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x03)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x04)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x05)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x06)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x07)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x08)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x09)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x11)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x12)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x14)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x1A)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x20)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x21)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x22)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x23)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x24)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x26)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x27)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x28)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x2B)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x30)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x31)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x33)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x34)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x35)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x36)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x37)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x38)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
					}
					else if(thePark.walls[a][b][c].wallTypeW == 0x3B)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
					}
					else
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

						texSupported = -1;
					}

					if(texSupported > 0)
					{
						glPushMatrix();

							glTranslated((thePark.walls[a][b][c].x) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z + 0.02f) * UNITWIDTH);

							//glColor3f(1.0f, 1.0f, 1.0f);
							
							glBegin(GL_QUADS);

								if(ZV <= (b + 0.5f) * UNITWIDTH)
									glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);
								else
									glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);

								glTexCoord2f(0.0f, 0.0f);
								glVertex3d(0.0f,		(tmpHeight1 + 0.0f) * UNITHEIGHT,	0.0f);
								glTexCoord2f(1.0f, 0.0f);
								glVertex3d(UNITWIDTH,	(tmpHeight2 + 0.0f) * UNITHEIGHT,	0.0f);
								glTexCoord2f(1.0f, 1.0f);
								glVertex3d(UNITWIDTH,	(tmpHeight2 + 1.0f) * UNITHEIGHT,	0.0f);
								glTexCoord2f(0.0f, 1.0f);
								glVertex3d(0.0f,		(tmpHeight1 + 1.0f) * UNITHEIGHT,	0.0f);
							glEnd();							

						glPopMatrix();
					}

					glDisable(GL_ALPHA_TEST);

				}

				if(thePark.walls[a][b][c].wallTypeE != 0x0F && thePark.walls[a][b][c].wallTypeE != 0x1F &&
					thePark.walls[a][b][c].wallTypeE != 0x2F && thePark.walls[a][b][c].wallTypeE != 0x3F)
				{
					tmpHeight1 = (float)thePark.landscape[a][b].TR;
					tmpHeight2 = (float)thePark.landscape[a][b].TL;

					texSupported = 1;

					if(thePark.walls[a][b][c].wallTypeE == 0x00)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_00] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x01)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_01] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x02)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_02] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x03)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_03] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x04)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_04] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x05)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_05] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x06)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_06] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x07)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_07] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x08)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_08] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x09)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_09] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x11)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_11] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x12)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_12] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x14)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_14] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x1A)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_1A] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x20)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_20] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x21)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_21] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x22)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_22] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x23)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_23] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x24)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_24] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x26)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_26] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x27)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_27] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x28)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_28] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x2B)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_2B] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x30)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_30] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x31)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_31] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x33)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_33] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x34)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_34] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x35)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_35] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x36)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_36] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x37)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_37] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x38)
					{
						glAlphaFunc ( GL_LESS, 0.4f );
						glEnable    ( GL_ALPHA_TEST   );

						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_38] );
					}
					else if(thePark.walls[a][b][c].wallTypeE == 0x3B)
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WALL_3B] );
					}
					else
					{
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

						texSupported = -1;
					}


					if(texSupported > 0)
					{
						glPushMatrix();

							glTranslated((thePark.walls[a][b][c].x) * UNITWIDTH, 0.0f, (thePark.walls[a][b][c].z + 0.98f) * UNITWIDTH);

							glBegin(GL_QUADS);
								if(ZV <= (b + 0.5f) * UNITWIDTH)
									glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);
								else
									glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);
							
								//glColor3f(1.0f, 1.0f, 1.0f);

								glTexCoord2f(0.0f, 0.0f);
								glVertex3d(0.0f,		(tmpHeight1 + 0.0f)* UNITHEIGHT,			0.0f);
								glTexCoord2f(1.0f, 0.0f);
								glVertex3d(UNITWIDTH,	(tmpHeight2 + 0.0f) * UNITHEIGHT,	0.0f);
								glTexCoord2f(1.0f, 1.0f);
								glVertex3d(UNITWIDTH,	(tmpHeight2 + 1.0f) * UNITHEIGHT,	0.0f);
								glTexCoord2f(0.0f, 1.0f);
								glVertex3d(0.0f,		(tmpHeight1 + 1.0f) * UNITHEIGHT,			0.0f);
							glEnd();

						glPopMatrix();
					}

					glDisable(GL_ALPHA_TEST);
					
				}
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	
}
