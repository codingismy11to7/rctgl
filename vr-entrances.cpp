#include "vr3d.h"

//ElementStructType ElementList[15876];
//int ElementListSize;

extern ParkStructType thePark;

extern float edgeLighting[4][4];

extern double ambientRValue, ambientGValue, ambientBValue;
extern double lightRValue, lightGValue, lightBValue;

extern double calcLightFactor(double n1, double n2, double n3);


void LoadEntrances(char *filename)
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

	printf("- in LoadEntrances()\n");

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

				/*
				00 0100 00	16
				00 0100	01	17
				00 0100	10	18
				00 0100	11	19
				01 0100 00	80
				01 0100	01	81
				01 0100	10	82
				01 0100	11	83
				10 0100 00	142
				10 0100	01	143
				10 0100	10	144
				10 0100	11	145
				11 0100 00	208
				11 0100	01	209
				11 0100	10	210
				11 0100	11	211
				*/



				//check the buffer values
				if (buffer >= 16 && buffer <= 19)
				{
					AddEntrance(input, currentbyte, i, j, buffer - 16, -1);
					//break;
				}
				if (buffer >= 80 && buffer <= 83)
				{
					AddEntrance(input, currentbyte, i, j, buffer - 80, -1);
					//break;
				}
				if (buffer >= 142 && buffer <= 145)
				{
					AddEntrance(input, currentbyte, i, j, buffer - 142, 1);
					//break;
				}
				if (buffer >= 208 && buffer <= 211)
				{
					AddEntrance(input, currentbyte, i, j, buffer - 208, 1);
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

/* adds a ride to the linked list of rides */
void AddEntrance(FILE *input, int offset, int x, int z, int modifier, int liftpiece)
{
	//printf("adding entrance\n");

	unsigned char buffer;
//	float objBase, objCeiling;
//	int objIdentity;
	int tempheight;

	

	// the file should already be at the correct position, so
	// we can retrieve the scenery information

	/*	byte #0 - scenery type
		byte #1 - N/A
		byte #2 - base height
		byte #3 - object clearance
		byte #4 - type
		byte #5 - element index (relative to ride piece)
		byte #6 - path type
		byte #7 - ride index
	*/

	// get the lift information
	//ElementList[ElementListSize].isLift = liftpiece;

	// we can skip over byte #0 since it was already checked

	
	// we can skip over byte #1 for now

	EntranceStructType *newEnt = new EntranceStructType;

	
	// we need to get the item's base height (byte #2)
	fseek(input, offset + 2, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;

	if (tempheight > 0)
		newEnt->base = (float)tempheight / 4.0f;
	else
		newEnt->base = 0.0f;
	
	// we need to get the item's ceiling (byte #3)
	fseek(input, offset + 3, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	//if (tempheight > 0)
		//thePark.entrances[x][z][entranceIndex].ceiling = tempheight / 4.0;
	//else
		//thePark.entrances[x][z][entranceIndex].ceiling = 0.0;

	// we need to get the entrance type
	fseek(input, offset + 4, SEEK_SET);
	tempheight = fgetc(input);
	if(tempheight == 0)
		newEnt->entranceType = rideEnt;
	else if(tempheight == 1)
		newEnt->entranceType = rideExit;
	else if(tempheight == 2)
		newEnt->entranceType = parkEnt;

	// get the element index
	fseek(input, offset + 5, SEEK_SET);
	tempheight = fgetc(input);
	newEnt->elementIndex = tempheight;

	if(newEnt->elementIndex == 1 &&	newEnt->entranceType == parkEnt)
	{
		thePark.parkEntranceX = x;
		thePark.parkEntranceY = newEnt->base;
		thePark.parkEntranceZ = z;
	}

	// get the color
	fseek(input, offset + 6, SEEK_SET);
	tempheight = fgetc(input);
	newEnt->pathType = tempheight;

	// get the ride index
	fseek(input, offset + 7, SEEK_SET);
	tempheight = fgetc(input);
	newEnt->rideIndex = tempheight;

	//finally, we need to assign the x and z coordinates to the path
	newEnt->x = x;
	newEnt->z = z;

	thePark.entrances[x][z].push_back(*newEnt);	
}

void DrawEntrances(int a, int b)
{
	int c,d;

	bool rideDir;

	bool drawIt;

	//loop through the list of elements
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	for(c=0; c<thePark.trees[a][b].size(); c++)
	{
		if(thePark.trees[a][b][c].identity >= 0x41 &&
			thePark.trees[a][b][c].identity <= 0x4D)
		{
			drawIt = true;

			//glDisable(GL_TEXTURE_2D);

			glPushMatrix();
		
				glTranslated(a * UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);
				
				glColor3f(1.0f, 1.0f, 1.0f);
				
				//all patches in kiddie-land (cinescape) - done 11
				if(thePark.trees[a][b][c].identity == 0x41)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_41] );
				}
				//in front of woodie (cinescape) - done 14
				else if(thePark.trees[a][b][c].identity == 0x42)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_42] );
				}
				//in front of space mtn and betlejuice ride (cinescape) - done (13)
				else if(thePark.trees[a][b][c].identity == 0x43)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_43] );
				}
				//outside edge of kiddieland (cinescape) - done 18
				else if(thePark.trees[a][b][c].identity == 0x45) 
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_45] );
				}
				//by music-land dock in cinescape - done 17
				else if(thePark.trees[a][b][c].identity == 0x46)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_46] );
				}
				//sides of hangar in space ville (cinescape) - done 16
				else if(thePark.trees[a][b][c].identity == 0x48)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_48] );
				}
				//around lake boobs in space ville (cinescape) - done 15
				else if(thePark.trees[a][b][c].identity == 0x4A)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_4A] );
				}
				//plus part of gardens at front of park heading to dock (sleepy woods) - done 20
				else if(thePark.trees[a][b][c].identity == 0x4B)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_4B] );
				}
				//next to wharf (DCA) - done 19
				else if(thePark.trees[a][b][c].identity == 0x4C)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_4C] );
				}
				//around trees in front of kiddie land in cinescape - done 12
				else if(thePark.trees[a][b][c].identity == 0x4D)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_4D] );					
				}
								
				
				
				//plus part of gardens at front of park heading to dock (sleepy woods)
				/*
				else if(thePark.trees[a][b][c].identity == 0x49)
				{
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_4D] );
				}
				*/
				else// if(thePark.trees[a][b][c].identity == 0x44)
				{	
					drawIt = false;
				}

				if(drawIt)
				{
					glBegin(GL_QUADS);
						glTexCoord2d(0.0f, 0.0f);
						glVertex3d(0.0f, 0.1f, 0.0f);
						glTexCoord2d(0.0f, 1.0f);
						glVertex3d(0.0f, 0.1f, UNITWIDTH);
						glTexCoord2d(1.0f, 1.0f);
						glVertex3d(UNITWIDTH, 0.1f, UNITWIDTH);
						glTexCoord2d(1.0f, 0.0f);
						glVertex3d(UNITWIDTH, 0.1f, 0.0f);					
					glEnd();
				}
					
				glColor3f(0.5f, 0.5f, 0.5f);

			glPopMatrix();
		}
		else if((thePark.trees[a][b][c].identity >= 0xAC &&
			thePark.trees[a][b][c].identity <= 0xB2) || thePark.trees[a][b][c].identity == 0x39)
		{
			drawIt = true;

			glPushMatrix();


										
		
				glTranslated(a * UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);
				
				if(thePark.trees[a][b][c].identity == 0xAC)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AC] );
				//in mayan land and dirt road land
				else if(thePark.trees[a][b][c].identity == 0xAD)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AD] );	
				//blue around park entrance
				else if(thePark.trees[a][b][c].identity == 0xAE)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AE] );	
				//scattered patches under glacier's corkscrews
				else if(thePark.trees[a][b][c].identity == 0xAF)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AF] );	
				else if(thePark.trees[a][b][c].identity == 0xB0)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_B0] );	
				//frontierland
				else if(thePark.trees[a][b][c].identity == 0xB1)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_B1] );	
				//right of entrance
				else if(thePark.trees[a][b][c].identity == 0xB2)
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_B2] );							
				else
				{
					drawIt = false;
					//glColor3f(0.0f, 0.0f, 1.0f);
				}

				if(drawIt)
				{
					if(thePark.trees[a][b][c].NEquad == true)
					{
						glBegin(GL_QUADS);
							glNormal3d(0.0f, 1.0f, 0.0f);
							glTexCoord2d(0.0f, 0.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glTexCoord2d(0.0f, 1.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
							glTexCoord2d(1.0f, 1.0f);
							glVertex3d(1.0f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
							glTexCoord2d(1.0f, 0.0f);
							glVertex3d(1.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
						glEnd();																						
					}
					else if(thePark.trees[a][b][c].NWquad == true)
					{
						glBegin(GL_QUADS);
							glNormal3d(0.0f, 1.0f, 0.0f);
							glTexCoord2d(0.0f, 0.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
							glTexCoord2d(0.0f, 1.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glTexCoord2d(1.0f, 1.0f);
							glVertex3d(1.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glTexCoord2d(1.0f, 0.0f);
							glVertex3d(1.0f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
						glEnd();				
					}
					else if(thePark.trees[a][b][c].SWquad == true)
					{
						glBegin(GL_QUADS);
							glNormal3d(0.0f, 1.0f, 0.0f);
							glTexCoord2d(0.0f, 0.0f);
							glVertex3d(0.0f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
							glTexCoord2d(0.0f, 1.0f);
							glVertex3d(0.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glTexCoord2d(1.0f, 1.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glTexCoord2d(1.0f, 0.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
						glEnd();


					}
					else if(thePark.trees[a][b][c].SEquad == true)
					{
						glBegin(GL_QUADS);
							glNormal3d(0.0f, 1.0f, 0.0f);
							glTexCoord2d(0.0f, 0.0f);
							glVertex3d(0.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glTexCoord2d(0.0f, 1.0f);
							glVertex3d(0.0f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
							glTexCoord2d(1.0f, 1.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
							glTexCoord2d(1.0f, 0.0f);
							glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
						glEnd();				

						
					}
				}

			glPopMatrix();
			
		}
	}

	for(c=0; c<thePark.entrances[a][b].size(); c++)
	{	
		glPushMatrix();
		
			glTranslated(a * UNITWIDTH, thePark.entrances[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);

			//printf("draring entrance\n");
		if(thePark.entrances[a][b][c].entranceType == rideEnt)
		{

			rideDir = false;

			for(d=0; d<thePark.elements[a+1][b].size(); d++)
				if(thePark.elements[a+1][b][d].base == thePark.entrances[a][b][c].base) 
					rideDir = true;

			for(d=0; d<thePark.elements[a-1][b].size(); d++)
				if(thePark.elements[a-1][b][d].base == thePark.entrances[a][b][c].base)
					rideDir = true;

			glEnable(GL_TEXTURE_2D);

			if(rideDir == true)
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );
			else
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );

			//set_material_color(0.82f, 0.74f, 0.55f);

			double val = calcLightFactor(-1.0f, 0.0f, 0.0f);
			glColor3d(ambientRValue * 1.0f + val * lightRValue,
				ambientGValue * 1.0f + val * lightGValue,
				ambientBValue * 1.0f + val * lightBValue);					


			glBegin(GL_QUADS);			
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
			glEnd();


			val = calcLightFactor(1.0f, 0.0f, 0.0f);
			glColor3d(ambientRValue * 1.0f + val * lightRValue,
				ambientGValue * 1.0f + val * lightGValue,
				ambientBValue * 1.0f + val * lightBValue);					

			glBegin(GL_QUADS);				
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
			glEnd();


			if(rideDir == true)
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );
			else
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );


			val = calcLightFactor(0.0f, 0.0f, 1.0f);
			glColor3d(ambientRValue * 1.0f + val * lightRValue,
				ambientGValue * 1.0f + val * lightGValue,
				ambientBValue * 1.0f + val * lightBValue);

			glBegin(GL_QUADS);				
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
			glEnd();

			val = calcLightFactor(0.0f, 0.0f, -1.0f);
			glColor3d(ambientRValue * 1.0f + val * lightRValue,
				ambientGValue * 1.0f + val * lightGValue,
				ambientBValue * 1.0f + val * lightBValue);
			
			glBegin(GL_QUADS);				
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
			glEnd();

			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT3] );


			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
			glEnd();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
			glEnd();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
			glEnd();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
			glEnd();


		}
		else if(thePark.entrances[a][b][c].entranceType == rideExit)
		{
			rideDir = false;

			for(d=0; d<thePark.elements[a+1][b].size(); d++)
				if(thePark.elements[a+1][b][d].base == thePark.entrances[a][b][c].base)
					rideDir = true;

			for(d=0; d<thePark.elements[a-1][b].size(); d++)
				if(thePark.elements[a-1][b][d].base == thePark.entrances[a][b][c].base)
					rideDir = true;

			glEnable(GL_TEXTURE_2D);

			if(rideDir == true)
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );
			else
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );

			//set_material_color(0.82f, 0.74f, 0.55f);

			glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);

			glBegin(GL_QUADS);
				glNormal3d(1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
			glEnd();


			glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);

			glBegin(GL_QUADS);
				glNormal3d(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
			glEnd();


			if(rideDir == true)
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );
			else
				glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );


			glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);

			glBegin(GL_QUADS);
				glNormal3d(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
			glEnd();					

			glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);
			
			glBegin(GL_QUADS);
				glNormal3d(0.0f, 0.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
			glEnd();


			glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT3] );


			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
			glEnd();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
			glEnd();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
			glEnd();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.5f, 1.0f);
				glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
			glEnd();

		}
		else
		{
		/*	
			set_material_color(0.0f, 0.0f, 1.0f);

			glBegin(GL_QUADS);
				glNormal3d(0.0f, 1.0f, 0.0f);
				glVertex3d(0.0f, 0.1f, 0.0f);
				glVertex3d(0.0f, 0.1f, UNITWIDTH);
				glVertex3d(UNITWIDTH, 0.1f, UNITWIDTH);
				glVertex3d(UNITWIDTH, 0.1f, 0.0f);
			glEnd();
			*/
			
		}

		glPopMatrix();
	}

	glDisable    ( GL_ALPHA_TEST   );
	glDisable(GL_TEXTURE_2D);

	
}


void oldDrawEntrances(void)
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

	int a,b,c,d;

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

	//glDisable(GL_LIGHTING);

	bool rideDir;

	//loop through the list of elements
	for(a=(int)startX; a<(int)endX; a++)
	{
		for(b=(int)startZ; b<(int)endZ; b++)
		{
			glColor3f(1.0f, 1.0f, 1.0f);

			for(c=0; c<thePark.trees[a][b].size(); c++)
			{
				
				
				if(thePark.trees[a][b][c].identity >= 0x41 &&
					thePark.trees[a][b][c].identity <= 0x4D)
				{
					glDisable(GL_TEXTURE_2D);

					glPushMatrix();
				
						glTranslated(a * UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);
						
						//around trees in front of kiddie land in cinescape
						if(thePark.trees[a][b][c].identity == 0x4D)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//next to wharf (DCA)
						else if(thePark.trees[a][b][c].identity == 0x4C)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//plus part of gardens at front of park heading to dock (sleepy woods)
						else if(thePark.trees[a][b][c].identity == 0x4B)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//around lake boobs in space ville (cinescape)
						else if(thePark.trees[a][b][c].identity == 0x4A)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//sides of hangar in space ville (cinescape)
						else if(thePark.trees[a][b][c].identity == 0x48)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//by music-land dock in cinescape
						else if(thePark.trees[a][b][c].identity == 0x46)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//outside edge of kiddieland (cinescape)
						else if(thePark.trees[a][b][c].identity == 0x45)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//in front of space mtn and betlejuice ride (cinescape)
						else if(thePark.trees[a][b][c].identity == 0x43)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//in front of woodie (cinescape)
						else if(thePark.trees[a][b][c].identity == 0x42)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//all patches in kiddie-land (cinescape)
						else if(thePark.trees[a][b][c].identity == 0x41)
						{
							glColor3f(0.0f, 0.0f, 0.0f);
						}
						//plus part of gardens at front of park heading to dock (sleepy woods)
						else if(thePark.trees[a][b][c].identity == 0x49)
						{
							glColor3f(1.0f, 1.0f, 0.0f);
						}
						else
						{							
							glColor3f(1.0f, 0.0f, 1.0f);
						}

						glBegin(GL_QUADS);
							glNormal3d(0.0f, 1.0f, 0.0f);
							glVertex3d(0.0f, 0.1f, 0.0f);
							glVertex3d(0.0f, 0.1f, UNITWIDTH);
							glVertex3d(UNITWIDTH, 0.1f, UNITWIDTH);
							glVertex3d(UNITWIDTH, 0.1f, 0.0f);
						glEnd();
						
						glColor3f(0.5f, 0.5f, 0.5f);

					glPopMatrix();
				}
				else if((thePark.trees[a][b][c].identity >= 0xAC &&
					thePark.trees[a][b][c].identity <= 0xB2) || thePark.trees[a][b][c].identity == 0x39)
				{
					glPushMatrix();

						glEnable(GL_TEXTURE_2D);						
				
						glTranslated(a * UNITWIDTH, thePark.trees[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);
						
						if(thePark.trees[a][b][c].identity == 0xAC)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AC] );
						//in mayan land and dirt road land
						else if(thePark.trees[a][b][c].identity == 0xAD)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AD] );	
						//blue around park entrance
						else if(thePark.trees[a][b][c].identity == 0xAE)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AE] );	
						//scattered patches under glacier's corkscrews
						else if(thePark.trees[a][b][c].identity == 0xAF)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_AF] );	
						else if(thePark.trees[a][b][c].identity == 0xB0)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_B0] );	
						//frontierland
						else if(thePark.trees[a][b][c].identity == 0xB1)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_B1] );	
						//right of entrance
						else if(thePark.trees[a][b][c].identity == 0xB2)
							glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_TREE_B2] );							
						else
						{
							glDisable(GL_TEXTURE_2D);
							glColor3f(0.0f, 0.0f, 1.0f);
						}

						if(thePark.trees[a][b][c].NEquad == true)
						{
							glBegin(GL_QUADS);
								glNormal3d(0.0f, 1.0f, 0.0f);
								glTexCoord2d(0.0f, 0.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
								glTexCoord2d(0.0f, 1.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
								glTexCoord2d(1.0f, 1.0f);
								glVertex3d(1.0f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
								glTexCoord2d(1.0f, 0.0f);
								glVertex3d(1.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glEnd();																						
						}
						else if(thePark.trees[a][b][c].NWquad == true)
						{
							glBegin(GL_QUADS);
								glNormal3d(0.0f, 1.0f, 0.0f);
								glTexCoord2d(0.0f, 0.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
								glTexCoord2d(0.0f, 1.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
								glTexCoord2d(1.0f, 1.0f);
								glVertex3d(1.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
								glTexCoord2d(1.0f, 0.0f);
								glVertex3d(1.0f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
							glEnd();				
						}
						else if(thePark.trees[a][b][c].SWquad == true)
						{
							glBegin(GL_QUADS);
								glNormal3d(0.0f, 1.0f, 0.0f);
								glTexCoord2d(0.0f, 0.0f);
								glVertex3d(0.0f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
								glTexCoord2d(0.0f, 1.0f);
								glVertex3d(0.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
								glTexCoord2d(1.0f, 1.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
								glTexCoord2d(1.0f, 0.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.0f * UNITWIDTH);
							glEnd();


						}
						else if(thePark.trees[a][b][c].SEquad == true)
						{
							glBegin(GL_QUADS);
								glNormal3d(0.0f, 1.0f, 0.0f);
								glTexCoord2d(0.0f, 0.0f);
								glVertex3d(0.0f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
								glTexCoord2d(0.0f, 1.0f);
								glVertex3d(0.0f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
								glTexCoord2d(1.0f, 1.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 1.0f * UNITWIDTH);
								glTexCoord2d(1.0f, 0.0f);
								glVertex3d(0.5f * UNITWIDTH, 0.1f, 0.5f * UNITWIDTH);
							glEnd();				

							
						}

					glPopMatrix();
					
				}
			}

			for(c=0; c<thePark.entrances[a][b].size(); c++)
			{	
				glPushMatrix();
				
					glTranslated(a * UNITWIDTH, thePark.entrances[a][b][c].base * UNITHEIGHT, b * UNITWIDTH);

					//printf("draring entrance\n");
				if(thePark.entrances[a][b][c].entranceType == rideEnt)
				{

					rideDir = false;

					for(d=0; d<thePark.elements[a+1][b].size(); d++)
						if(thePark.elements[a+1][b][d].base == thePark.entrances[a][b][c].base &&
							thePark.elements[a+1][b][d].identity >= 0x01 && thePark.elements[a+1][b][d].identity >= 0x03) 
							rideDir = true;

					for(d=0; d<thePark.elements[a-1][b].size(); d++)
						if(thePark.elements[a-1][b][d].base == thePark.entrances[a][b][c].base &&
							thePark.elements[a-1][b][d].identity >= 0x01 && thePark.elements[a-1][b][d].identity >= 0x03) 
							rideDir = true;

					glEnable(GL_TEXTURE_2D);

					if(rideDir == true)
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );
					else
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );

					//set_material_color(0.82f, 0.74f, 0.55f);

					double val = calcLightFactor(1.0f, 0.0f, 0.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);					

					glBegin(GL_QUADS);						
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
					glEnd();

					val = calcLightFactor(-1.0f, 0.0f, 0.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);					

					glBegin(GL_QUADS);						
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
					glEnd();


					if(rideDir == true)
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );
					else
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );


					val = calcLightFactor(0.0f, 0.0f, 1.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);					

					glBegin(GL_QUADS);						
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
					glEnd();

					val = calcLightFactor(0.0f, 0.0f, -1.0f);
					glColor3d(ambientRValue * 1.0f + val * lightRValue,
						ambientGValue * 1.0f + val * lightGValue,
						ambientBValue * 1.0f + val * lightBValue);					

					glBegin(GL_QUADS);						
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
					glEnd();

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT3] );


					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 3.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
					glEnd();


				}
				else if(thePark.entrances[a][b][c].entranceType == rideExit)
				{
					rideDir = false;

					for(d=0; d<thePark.elements[a+1][b].size(); d++)
						if(thePark.elements[a+1][b][d].base == thePark.entrances[a][b][c].base)
							rideDir = true;

					for(d=0; d<thePark.elements[a-1][b].size(); d++)
						if(thePark.elements[a-1][b][d].base == thePark.entrances[a][b][c].base)
							rideDir = true;

					glEnable(GL_TEXTURE_2D);

					if(rideDir == true)
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );
					else
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );

					//set_material_color(0.82f, 0.74f, 0.55f);

					glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);

					glBegin(GL_QUADS);
						glNormal3d(1.0f, 0.0f, 0.0f);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
					glEnd();


					glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);

					glBegin(GL_QUADS);
						glNormal3d(-1.0f, 0.0f, 0.0f);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
					glEnd();


					if(rideDir == true)
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT2] );
					else
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT1] );


					glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);

					glBegin(GL_QUADS);
						glNormal3d(0.0f, 0.0f, 1.0f);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.1f * UNITWIDTH);
					glEnd();					

					glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);
					
					glBegin(GL_QUADS);
						glNormal3d(0.0f, 0.0f, -1.0f);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3d(0.1f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3d(0.9f * UNITWIDTH, 2 * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 0.0f, 0.9f * UNITWIDTH);
					glEnd();


					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RIDE_ENT3] );


					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.1f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
					glEnd();

					glBegin(GL_TRIANGLES);
						glTexCoord2f(0.5f, 1.0f);
						glVertex3d(0.5f * UNITWIDTH, 2.8f * UNITHEIGHT, 0.5f * UNITWIDTH);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.1f * UNITWIDTH);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d(0.9f * UNITWIDTH, 2.0f * UNITHEIGHT, 0.9f * UNITWIDTH);
					glEnd();

				}
				else
				{
				/*	
					set_material_color(0.0f, 0.0f, 1.0f);

					glBegin(GL_QUADS);
						glNormal3d(0.0f, 1.0f, 0.0f);
						glVertex3d(0.0f, 0.1f, 0.0f);
						glVertex3d(0.0f, 0.1f, UNITWIDTH);
						glVertex3d(UNITWIDTH, 0.1f, UNITWIDTH);
						glVertex3d(UNITWIDTH, 0.1f, 0.0f);
					glEnd();
					*/
					
				}

				glPopMatrix();
			}
		}
	}

	glDisable    ( GL_ALPHA_TEST   );
	glDisable(GL_TEXTURE_2D);

	
}

