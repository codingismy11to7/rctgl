#include "vr3d.h" 

//TreeStructType TreeList[15876];
//int TreeListSize;

extern ParkStructType thePark;

extern float edgeLighting[4][4];

bool isTreeSupported(int id)
{
	int supportedTrees[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
							0x0F, 0x11, 0x12, 0x13, 0x14, 0x16, 0x18, 0x19,
							0x1A, 0x1B, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22,
							0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34,
							0x36, 0x37, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
							0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x66,
							0x77, 0x80, 0x81, 0x82, 0x83, 0x84, 0x97, 0x98,
							0x9E, 0x9F, 0xA3, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0,
							0xB1, 0xB2, -1};
	int i;

	for(i=0; supportedTrees[i] != -1; i++)
		if(id == supportedTrees[i])
			return true;

	return false;
}

bool isTreeQuarter(int id)
{
	int quarterTiles[] = {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x10,
		0x15, 0x17, 0x1C, 0x23, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x38, 0x39,
		0x3B, 0x3C, 0x3D, 0x3F, 0x40, -1};

	int i;

	for(i=0; quarterTiles[i] != -1; i++)
		if(id == quarterTiles[i])
			return true;

	return false;
}

void NewLoadTrees1(char *filename)
{
	FILE *input;

	int i,j;
	long nextbyte;
	long currentbyte;
//	int tempheight;
//	int LLmodifier;
	int looping;

	unsigned char buffer;
	unsigned char endCheckBuffer;

	//TreeListSize = 0;

	printf("- in LoadTrees1\n");

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

			looping = 0;

			// now we're after the land height info. now loop until
			// we hit a scenery element, or the next land piece

			/* here are the bytes we're looking for 
			 * we need anything with middle bits 0011
			 * 00 0011 00 = 12
			 * 00 0011 01 = 13
			 * 00 0011 10 = 14
			 * 00 0011 11 = 15
			 * 01 0011 00 = 76
			 * 01 0011 01 = 77
			 * 01 0011 10 = 78
			 * 01 0011 11 = 79
			 * 10 0011 00 = 140
			 * 10 0011 01 = 141
			 * 10 0011 10 = 142
			 * 10 0011 11 = 143
			 * 11 0011 00 = 204
			 * 11 0011 01 = 205
			 * 11 0011 10 = 206
			 * 11 0011 11 = 207
			 */
			while(1)
			{

				//move to the next land segment
				fseek(input, currentbyte + 9, SEEK_SET);

				endCheckBuffer = fgetc(input);

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				currentbyte = nextbyte;

				buffer = fgetc(input);

				nextbyte += 8;

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
				if (buffer >= 12 && buffer <= 15)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 76 && buffer <= 79)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 140 && buffer <= 143)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 204 && buffer <= 207)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}

				//if(looping == 1)
				//	printf("looping for land at %d\n", nextbyte);

				looping++;

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				currentbyte = nextbyte;

				buffer = fgetc(input);

				//nextbyte += 8;

				if((nextbyte + 8) >= 393231)
				{
					if((i != 127) && (j != 127))
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
				if(endCheckBuffer >= 128)
					break;
			}

			//nextbyte -= 8;
		}
	}

	//printf("TreeListSize = %d\n", TreeListSize);
}


void LoadTrees1(char *filename)
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

	//ElementListSize = 0;

	printf("- in LoadElements()\n");

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
				//move to the next land segment
				fseek(input, currentbyte + 9, SEEK_SET);

				endCheckBuffer = fgetc(input);

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				currentbyte = nextbyte;

				buffer = fgetc(input);

				nextbyte += 8;

				/* here are the bytes we're looking for 
				 * we need anything with middle bits 0011
				 * 00 0011 00 = 12
				 * 00 0011 01 = 13
				 * 00 0011 10 = 14
				 * 00 0011 11 = 15
				 * 01 0011 00 = 76
				 * 01 0011 01 = 77
				 * 01 0011 10 = 78
				 * 01 0011 11 = 79
				 * 10 0011 00 = 140
				 * 10 0011 01 = 141
				 * 10 0011 10 = 142
				 * 10 0011 11 = 143
				 * 11 0011 00 = 204
				 * 11 0011 01 = 205
				 * 11 0011 10 = 206
				 * 11 0011 11 = 207
				 */



				//check the buffer values
				if (buffer >= 12 && buffer <= 15)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 76 && buffer <= 79)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 140 && buffer <= 143)
				{
					AddTree(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 204 && buffer <= 207)
				{
					AddTree(input, currentbyte, i, j);
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

	//printf("ElementListSize = %d\n", ElementListSize);
}



/* adds a single-tile tree to the linked list of trees */
void AddTree(FILE *input, int offset, int x, int z)
{
	unsigned char buffer;
//	float objBase, objCeiling;
//	int objIdentity;
	int tempheight;


	// the file should already be at the correct position, so
	// we can retrieve the scenery information

	/*	byte #0 - scenery type
		byte #1 - quadrant (not applicable yet)
		byte #2 - base height
		byte #3 - object clearance
		byte #4 - item identifier
		byte #5 - age (not applicable yet)
		byte #6 - color (not applicable yet)
		byte #7 - not used
	*/

	// we can skip over byte #0 since it was already checked
	
	// we can skip over byte #1 for now

	TreeStructType *newTree = new TreeStructType;
	
	// we need to get the item's base height (byte #2)
	fseek(input, offset + 2, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;

	//printf("adding tree to %d %d\n", x, z);
	if (tempheight > 0)
		newTree->base = (float)(tempheight / 4.0);
	else
		newTree->base = 0.0f;

	
	//get the quadrant details
	fseek(input, offset, SEEK_SET);
	buffer = fgetc(input);

	newTree->SEquad = false;
	newTree->NEquad = false;
	newTree->NWquad = false;
	newTree->SWquad = false;
	


	if(buffer & 192)		//11xx xxxx
		newTree->SEquad = true;
	else if(buffer & 128)	//10xx xxxx
		newTree->NEquad = true;
	else if(buffer & 64)	//01xx xxxx
		newTree->NWquad = true;
	else					//00xx xxxx
		newTree->SWquad = true;

	
	// we need to get the item's ceiling (byte #3)
	fseek(input, offset + 3, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newTree->ceiling = (float)(tempheight / 4.0f);
	else
		newTree->ceiling = 0.0f;

	// we need to get the item's identity
	fseek(input, offset + 4, SEEK_SET);
	newTree->identity = fgetc(input);

	//finally, we need to assign the x and z coordinates to the tree
	newTree->x = x;
	newTree->z = z;


	if(isTreeQuarter(newTree->identity))
		newTree->quarterItem = true;
	else
		newTree->quarterItem = false;

	thePark.trees[x][z].push_back(*newTree);
}

void DrawTrees1(int a, int b)
{
	int c;
	int side1, side2;
	int lastTexture;

	glAlphaFunc ( GL_LESS, 0.4f );
	glEnable    ( GL_ALPHA_TEST   );

	glEnable(GL_TEXTURE_2D);

	//TreeStructType *tmpTree = new TreeStructType;

	lastTexture = -1;

	//loop through the list of trees
	for(c=0; c<thePark.trees[a][b].size(); c++)
	{
		//printf("drawing tree %d at (%d, %d)", c, a, b);		
		
		if(thePark.trees[a][b][c].identity >= 0x41 &&
			thePark.trees[a][b][c].identity <= 0x4D)
		{
			/*
			glColor3f(1.0f, 1.0f, 1.0f);

			glPushMatrix();

				glTranslated(a * UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT + 0.1f, b * UNITWIDTH);

				glBegin(GL_QUADS);

				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(UNITWIDTH, 0.0f, 0.0f);
				glVertex3f(UNITWIDTH, 0.0f, UNITWIDTH);
				glVertex3f(0.0f, 0.0f, UNITWIDTH);

				glEnd();
			glPopMatrix();
			*/
		}
		else if(thePark.trees[a][b][c].identity >= 0xAC &&
			thePark.trees[a][b][c].identity <= 0xB2)
		{
			/*

			//printf("drawing quarter-tile garden at %f %f %f\n", a * UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			
			//set_material_color(1.0f, 0.0f, 0.0f);

			//glDisable(GL_BLEND);
			//glDisable(GL_TEXTURE_2D);
			//glDisable(GL_LIGHTING);
			//glDisable(GL_LIGHT0);

			//glDisable(GL_CULL_FACE);

			//glPushMatrix();

//glEnable(GL_TEXTURE_2D);
//glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_QUADS);
//glTexCoord2d(0.0, 1.0);	
glVertex3d(0.0f,		0.1f, 0.0f);

//glTexCoord2d(1.0, 1.0);
glVertex3d(0.0f,		0.1f, UNITWIDTH);

//glTexCoord2d(1.0, 0.0);
glVertex3d(UNITWIDTH,	0.1f, UNITWIDTH);

//glTexCoord2d(0.0, 0.0);
glVertex3d(UNITWIDTH,	0.1f, 0.0f);
glEnd();
			//glPopMatrix();

			//glEnable(GL_BLEND);


*/

		}
		else
		
		{
			
			switch(thePark.trees[a][b][c].identity)
			{
			case 0x00:
				side1 = TEXTURE_TREE_00_1;
				//side2 = TEXTURE_TREE_00_2;
				side2 = TEXTURE_TREE_00_1;
				break;
			case 0x01:
				side1 = TEXTURE_TREE_01_1;
				side2 = TEXTURE_TREE_01_2;
				break;
			case 0x02:
				side1 = TEXTURE_TREE_02_1;
				side2 = TEXTURE_TREE_02_2;
				break;
			case 0x03:
				side1 = TEXTURE_TREE_03_1;
				side2 = TEXTURE_TREE_03_2;
				break;
			case 0x04:
				side1 = TEXTURE_TREE_04_1;
				side2 = TEXTURE_TREE_04_2;
				break;
			case 0x05:
				side1 = TEXTURE_TREE_05_1;
				side2 = TEXTURE_TREE_05_2;
				break;
			case 0x06:
				side1 = TEXTURE_TREE_06_1;
				side2 = TEXTURE_TREE_06_2;
				break;
			case 0x07:
				side1 = TEXTURE_TREE_07_1;
				side2 = TEXTURE_TREE_07_2;
				break;
			case 0x0F:
				side1 = TEXTURE_TREE_0F_1;
				side2 = TEXTURE_TREE_0F_2;
				break;
			case 0x11:
				side1 = TEXTURE_TREE_11_1;
				side2 = TEXTURE_TREE_11_2;
				break;
			case 0x12:
				side1 = TEXTURE_TREE_12_1;
				side2 = TEXTURE_TREE_12_2;
				break;
			case 0x13:
				side1 = TEXTURE_TREE_13_1;
				side2 = TEXTURE_TREE_13_2;
				break;
			case 0x14:
				side1 = TEXTURE_TREE_14_1;
				side2 = TEXTURE_TREE_14_2;
				break;
			case 0x16:
				side1 = TEXTURE_TREE_16_1;
				side2 = TEXTURE_TREE_16_2;
				break;
			case 0x18:
				side1 = TEXTURE_TREE_18_1;
				side2 = TEXTURE_TREE_18_2;
				break;
			case 0x19:
				side1 = TEXTURE_TREE_19_1;
				side2 = TEXTURE_TREE_19_2;
				break;
			case 0x1A:
				side1 = TEXTURE_TREE_1A_1;
				side2 = TEXTURE_TREE_1A_2;
				break;
			case 0x1B:
				side1 = TEXTURE_TREE_1B_1;
				side2 = TEXTURE_TREE_1B_2;
				break;
			case 0x1C:
				side1 = TEXTURE_TREE_1C_1;
				side2 = TEXTURE_TREE_1C_2;
				break;
			case 0x1D:
				side1 = TEXTURE_TREE_1D_1;
				side2 = TEXTURE_TREE_1D_2;
				break;
			case 0x1E:
				side1 = TEXTURE_TREE_1E_1;
				side2 = TEXTURE_TREE_1E_2;
				break;
			case 0x1F:
				side1 = TEXTURE_TREE_1F_1;
				side2 = TEXTURE_TREE_1F_2;
				break;
			case 0x20:
				side1 = TEXTURE_TREE_20_1;
				side2 = TEXTURE_TREE_20_2;
				break;
			case 0x21:
				side1 = TEXTURE_TREE_21_1;
				side2 = TEXTURE_TREE_21_2;
				break;
			case 0x22:
				side1 = TEXTURE_TREE_22_1;
				side2 = TEXTURE_TREE_22_2;
				break;
			case 0x24:
				side1 = TEXTURE_TREE_24_1;
				side2 = TEXTURE_TREE_24_2;
				break;
			case 0x25:
				side1 = TEXTURE_TREE_25_1;
				side2 = TEXTURE_TREE_25_2;
				break;
			case 0x26:
				side1 = TEXTURE_TREE_26_1;
				side2 = TEXTURE_TREE_26_2;
				break;
			case 0x27:
				side1 = TEXTURE_TREE_27_1;
				side2 = TEXTURE_TREE_27_2;
				break;
			case 0x28:
				side1 = TEXTURE_TREE_28_1;
				side2 = TEXTURE_TREE_28_2;
				break;
			case 0x29:
				side1 = TEXTURE_TREE_29_1;
				side2 = TEXTURE_TREE_29_2;
				break;
			case 0x2A:
				side1 = TEXTURE_TREE_2A_1;
				side2 = TEXTURE_TREE_2A_2;
				break;
			case 0x34:
				side1 = TEXTURE_TREE_34_1;
				side2 = TEXTURE_TREE_34_2;
				break;
			case 0x36:
				side1 = TEXTURE_TREE_36_1;
				side2 = TEXTURE_TREE_36_2;
				break;
			case 0x37:
				side1 = TEXTURE_TREE_37_1;
				side2 = TEXTURE_TREE_37_2;
				break;
			case 0x66:
				side1 = TEXTURE_TREE_66_1;
				side2 = TEXTURE_TREE_66_2;
				break;
			case 0x77:
				side1 = TEXTURE_TREE_77_1;
				side2 = TEXTURE_TREE_77_2;
				break;
			case 0x80:
				side1 = TEXTURE_TREE_80_1;
				side2 = TEXTURE_TREE_80_2;
				break;
			case 0x81:
				side1 = TEXTURE_TREE_81_1;
				side2 = TEXTURE_TREE_81_2;
				break;
			case 0x82:
				side1 = TEXTURE_TREE_82_1;
				side2 = TEXTURE_TREE_82_2;
				break;
			case 0x83:
				side1 = TEXTURE_TREE_83_1;
				side2 = TEXTURE_TREE_83_2;
				break;
			case 0x84:
				side1 = TEXTURE_TREE_84_1;
				side2 = TEXTURE_TREE_84_2;
				break;
			case 0x97:
				side1 = TEXTURE_TREE_97_1;
				side2 = TEXTURE_TREE_97_1;
				break;					
			case 0x98:
				side1 = TEXTURE_TREE_98_1;
				side2 = TEXTURE_TREE_98_1;
				break;	
			case 0x9E:
				side1 = TEXTURE_TREE_9E_1;
				side2 = TEXTURE_TREE_9E_1;
				break;
			case 0x9F:
				side1 = TEXTURE_TREE_9F_1;
				side2 = TEXTURE_TREE_9F_1;
				break;
			case 0xA3:
				side1 = TEXTURE_TREE_A3_1;
				side2 = TEXTURE_TREE_A3_1;
				break;
			default:
				side1 = -1;
				side2 = -1;
			}

			//if side1 == -1, then the texture/object is undefined
			if (side1 > 0)
			{
				//if(CubeInFrustum(thePark.trees[a][b][c].x*UNITWIDTH, (thePark.trees[a][b][c].base * UNITHEIGHT) - 0.1f, thePark.trees[a][b][c].z*UNITWIDTH, UNITWIDTH, (thePark.trees[a][b][c].ceiling - thePark.trees[a][b][c].base) * UNITHEIGHT + 0.1f, UNITWIDTH) == TRUE) 
				if(CubeInFrustum((float)(a*UNITWIDTH), (float)((thePark.trees[a][b][c].base * UNITHEIGHT) - 0.1f), (float)(b*UNITWIDTH), (float)(UNITWIDTH), (float)((thePark.trees[a][b][c].ceiling - thePark.trees[a][b][c].base) * UNITHEIGHT + 0.1f), (float)(UNITWIDTH)) == TRUE) 
				{

					glPushMatrix();

						if(ZV <= (b + 0.5f) * UNITWIDTH)
							glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);
						else
							glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);


						glTranslated(a * UNITWIDTH, 0.0f, b * UNITWIDTH + 0.5f * UNITWIDTH);

						//if(lastTexture != side1)
							glBindTexture (GL_TEXTURE_2D, texture_id[side1] );

						glBegin(GL_QUADS);
									
							glTexCoord2f(0.0, 0.0);
							glVertex3d(   0.0f,   thePark.trees[a][b][c].base * UNITHEIGHT,    0.0f);
							glTexCoord2f(1.0, 0.0);
							glVertex3d(UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT,    0.0f);
							glTexCoord2f(1.0, 1.0);
							glVertex3d(UNITWIDTH, thePark.trees[a][b][c].ceiling * UNITHEIGHT, 0.0f);
							glTexCoord2f(0.0, 1.0);
							glVertex3d(   0.0f,   thePark.trees[a][b][c].ceiling * UNITHEIGHT, 0.0f);

						glEnd();

						if(XV <= (a + 0.5f) * UNITWIDTH)
							glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);
						else
							glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);

						//if(lastTexture != side1)
						{
							//glBindTexture (GL_TEXTURE_2D, texture_id[side2] );
							//lastTexture = side1;
						}

						glBegin(GL_QUADS);
									
							glTexCoord2f(0.0, 0.0);
							glVertex3d((UNITWIDTH / 2.0f), thePark.trees[a][b][c].base * UNITHEIGHT,    -(UNITWIDTH / 2.0f));
							glTexCoord2f(1.0, 0.0);
							glVertex3d((UNITWIDTH / 2.0f), thePark.trees[a][b][c].base * UNITHEIGHT,     (UNITWIDTH / 2.0f));
							glTexCoord2f(1.0, 1.0);
							glVertex3d((UNITWIDTH / 2.0f), thePark.trees[a][b][c].ceiling * UNITHEIGHT,  (UNITWIDTH / 2.0f));
							glTexCoord2f(0.0, 1.0);
							glVertex3d((UNITWIDTH / 2.0f), thePark.trees[a][b][c].ceiling * UNITHEIGHT, -(UNITWIDTH / 2.0f));

						glEnd();

					glPopMatrix();
				}
			}
		}
	}

	glDisable(GL_ALPHA_TEST);

	glDisable(GL_TEXTURE_2D);


}


void LoadBigScenery(char *filename)
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

	//ElementListSize = 0;

	printf("- in LoadElements()\n");

	input = fopen(filename, "rb");

	if(input == NULL)
		perror("fopen\n");

	//move to the map info
	fseek(input, 0x10, SEEK_SET);

	currentbyte = 0x10;
	nextbyte = 0x10;

	for(i=0; i<128; i++)
		for(j=0; j<128; j++)
			thePark.bigScenery[i][j].clear();


	for(i=0; i<128; i++)
	{
		//printf("row %d\n", i);

		for(j=0; j<128; j++)
		{
			buffer = 10;
			endCheckBuffer = 10;

			while(1)
			{
				//move to the next land segment
				fseek(input, currentbyte + 9, SEEK_SET);

				endCheckBuffer = fgetc(input);

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				currentbyte = nextbyte;

				buffer = fgetc(input);

				nextbyte += 8;

				/* here are the bytes we're looking for 
				 * we need anything with middle bits 0011
				 * 00 0110 00 = 24
				 * 00 0110 01 = 25
				 * 00 0110 10 = 26
				 * 00 0110 11 = 27
				 * 01 0110 00 = 88
				 * 01 0110 01 = 89
				 * 01 0110 10 = 90
				 * 01 0110 11 = 91
				 * 10 0110 00 = 152
				 * 10 0110 01 = 153
				 * 10 0110 10 = 154
				 * 10 0110 11 = 155
				 * 11 0110 00 = 216
				 * 11 0110 01 = 217
				 * 11 0110 10 = 218
				 * 11 0110 11 = 219
				 */



				//check the buffer values
				if (buffer >= 24 && buffer <= 27)
				{
					AddBigScenery(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 88 && buffer <= 91)
				{
					AddBigScenery(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 152 && buffer <= 155)
				{
					AddBigScenery(input, currentbyte, i, j);
					//break;
				}
				if (buffer >= 216 && buffer <= 219)
				{
					AddBigScenery(input, currentbyte, i, j);
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

	//printf("ElementListSize = %d\n", ElementListSize);
}



/* adds a multiple-tile scenery element to the linked list of trees */
void AddBigScenery(FILE *input, int offset, int x, int z)
{
	unsigned char buffer;
//	float objBase, objCeiling;
//	int objIdentity;
	int tempheight;


	// the file should already be at the correct position, so
	// we can retrieve the scenery information

	/*	byte #0 - scenery type
		byte #1 - quadrant (not applicable yet)
		byte #2 - base height
		byte #3 - object clearance
		byte #4 - item identifier
		byte #5 - index
		byte #6 - color (not applicable yet)
		byte #7 - not used
	*/

	// we can skip over byte #0 since it was already checked
	
	// we can skip over byte #1 for now

	BigSceneryStructType *newBigScenery = new BigSceneryStructType;
	
	// we need to get the item's base height (byte #2)
	fseek(input, offset + 2, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;

	//printf("adding tree to %d %d\n", x, z);
	if (tempheight > 0)
		newBigScenery->base = (float)(tempheight / 4.0);
	else
		newBigScenery->base = 0.0f;


	//get the quadrant details
	fseek(input, offset, SEEK_SET);
	buffer = fgetc(input);

	// we need to get the item's ceiling (byte #3)
	fseek(input, offset + 3, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newBigScenery->ceiling = (float)(tempheight / 4.0f);
	else
		newBigScenery->ceiling = 0.0f;

	// we need to get the item's identity
	fseek(input, offset + 4, SEEK_SET);
	newBigScenery->identity = fgetc(input);

	// we need to get the item's sequence
	fseek(input, offset + 5, SEEK_SET);
	newBigScenery->elementIndex = fgetc(input);

	//finally, we need to assign the x and z coordinates to the tree
	newBigScenery->x = x;
	newBigScenery->z = z;

	thePark.bigScenery[x][z].push_back(*newBigScenery);


}

void DrawBigScenery(int a, int b)
{
	int c;

	for(c=0; c<thePark.bigScenery[a][b].size(); c++)
	{
		switch(thePark.bigScenery[a][b][c].identity)
		{
		case 0x08:
			if(thePark.bigScenery[a][b][c].elementIndex == 0)
			{
				glColor3f(0.91f, 0.87f, 0.69f);
				//glColor3f(1.0f, 0.0f, 0.0f);

				glPushMatrix();

					//glTranslated(thePark.bigScenery[a][b][c].x* UNITWIDTH, thePark.bigScenery[a][b][c].base * UNITHEIGHT, thePark.bigScenery[a][b][c].z * UNITWIDTH);
	

					
					glBegin(GL_TRIANGLES);
						glVertex3f((thePark.bigScenery[a][b][c].x + 0.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 0.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 3.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].ceiling * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 3.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 6.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 0.0f) * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glVertex3f((thePark.bigScenery[a][b][c].x + 0.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 6.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 3.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].ceiling * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 3.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 6.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 6.0f) * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glVertex3f((thePark.bigScenery[a][b][c].x + 0.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 0.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 3.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].ceiling * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 3.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 0.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 6.0f) * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glVertex3f((thePark.bigScenery[a][b][c].x + 6.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 0.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 3.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].ceiling * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 3.0f) * UNITWIDTH);
						glVertex3f((thePark.bigScenery[a][b][c].x + 6.0f) * UNITWIDTH,
							thePark.bigScenery[a][b][c].base * UNITHEIGHT,
							(thePark.bigScenery[a][b][c].z + 6.0f) * UNITWIDTH);
					glEnd();
					
					

				glPopMatrix();
			}

			break;
		}
	}
}
