#include "vr3d.h"

#include "vr-slc.h"
#include "vr-inverted.h"
#include "vr-suspendedsinglerail.h"
#include "vr-steeltwister.h"
#include "vr-wooden.h"

//ElementStructType ElementList[15876];
//int ElementListSize;

extern ParkStructType thePark;
int itemRot;

void DrawTempThing(int rideIndex, int colorIndex)
{
	//draw the top support beam
	glColor3f(RCTColorsR[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsG[RideList[rideIndex].SecondaryColor[colorIndex]], RCTColorsB[RideList[rideIndex].SecondaryColor[colorIndex]]);

	glBegin(GL_QUADS);
		glVertex3d(0.1f,			0.0f, 0.1f);
		glVertex3d(0.1f,			0.0f, UNITWIDTH - 0.1f);
		glVertex3d(UNITWIDTH - 0.1f,0.0f, UNITWIDTH - 0.1f);
		glVertex3d(UNITWIDTH - 0.1f,0.0f, 0.1f);
	glEnd();
}
	
void LoadElements(char *filename)
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

				/*
				00 0010 00	8
				00 0010	01	9
				00 0010	10	10
				00 0010	11	11
				01 0010 00	72
				01 0010	01	73
				01 0010	10	74
				01 0010	11	75
				10 0010 00	136
				10 0010	01	137
				10 0010	10	138
				10 0010	11	139
				11 0010 00	200
				11 0010	01	201
				11 0010	10	202
				11 0010	11	203
				*/



				//check the buffer values
				if (buffer >= 8 && buffer <= 11)
				{
					AddElement(input, currentbyte, i, j, buffer - 8, -1);
					//break;
				}
				if (buffer >= 72 && buffer <= 75)
				{
					AddElement(input, currentbyte, i, j, buffer - 72, -1);
					//break;
				}
				if (buffer >= 136 && buffer <= 139)
				{
					AddElement(input, currentbyte, i, j, buffer - 136, 1);
					//break;
				}
				if (buffer >= 200 && buffer <= 203)
				{
					AddElement(input, currentbyte, i, j, buffer - 200, 1);
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
void AddElement(FILE *input, int offset, int x, int z, int modifier, int liftpiece)
{
	unsigned char buffer;
//	float objBase, objCeiling;
//	int objIdentity;
	unsigned char tempheight;	

	// the file should already be at the correct position, so
	// we can retrieve the scenery information

	/*	byte #0 - scenery type
		byte #1 - N/A
		byte #2 - base height
		byte #3 - object clearance
		byte #4 - element type
		byte #5 - element index (relative to ride)
		byte #6 - color
		byte #7 - ride index
	*/

	// get the lift information
	//ElementList[ElementListSize].isLift = liftpiece;

	// we can skip over byte #0 since it was already checked

	
	// we can skip over byte #1 for now
	
	ElementStructType *newElement = new ElementStructType;
	
	// we need to get the item's base height (byte #2)
	fseek(input, offset + 2, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)	
		newElement->base = (float)tempheight / 4.0f;
	else
		newElement->base = 0.0f;

	newElement->isLift = liftpiece;

	// we need to get the item's ceiling (byte #3)
	fseek(input, offset + 3, SEEK_SET);
	buffer = fgetc(input);
	tempheight = buffer;
	if (tempheight > 0)
		newElement->ceiling = (float)tempheight / 4.0f;
	else
		newElement->ceiling = 0.0f;
	
	// we need to get the path type and slope
	fseek(input, offset + 4, SEEK_SET);	
	newElement->identity = fgetc(input);

	// get the element index
	fseek(input, offset + 5, SEEK_SET);	
	newElement->elementIndex = fgetc(input);

	// get the color
	fseek(input, offset + 6, SEEK_SET);	
	newElement->baseColor = fgetc(input);

	// get the ride index
	fseek(input, offset + 7, SEEK_SET);
	newElement->rideIndex = fgetc(input);

	//finally, we need to assign the x and z coordinates to the path
	newElement->x = x;
	newElement->z = z;

	newElement->elementOrientation = modifier;

	thePark.elements[x][z].push_back(*newElement);
}

void DrawElements(int a, int b)
{
	int c;

	//loop through the list of elements
	for(c=0; c<thePark.elements[a][b].size(); c++)
	{	
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);	

		//printf("looping1\n");
		if(CubeInFrustum(thePark.elements[a][b][c].x * UNITWIDTH, (thePark.elements[a][b][c].base * UNITHEIGHT) + 0.1f, (thePark.elements[a][b][c].z + 1)*UNITWIDTH, UNITWIDTH, (thePark.elements[a][b][c].base + 1) + 0.1f, UNITWIDTH) == TRUE) 
		//if(1 == 1) 
		{			
			glColor3f(1.0f, 1.0f, 1.0f);

			glPushMatrix();

			glTranslated((thePark.elements[a][b][c].x) * UNITWIDTH, (thePark.elements[a][b][c].base * UNITHEIGHT) + 0.1f, (thePark.elements[a][b][c].z + 1) * UNITWIDTH);
			
			
			if(thePark.elements[a][b][c].elementOrientation == 0)
			{
				glTranslated(0.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
				itemRot = -90; //fixed
			}
			else if(thePark.elements[a][b][c].elementOrientation == 1)
			{
				glTranslated(0.0f, 0.0f, -UNITWIDTH);
				glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
				itemRot = 180; //fixed?
			}
			else if(thePark.elements[a][b][c].elementOrientation == 2)
			{
				glTranslated(UNITWIDTH, 0.0f, -UNITWIDTH);
				glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
				itemRot = 90; //fixed?
			}
			else if(thePark.elements[a][b][c].elementOrientation == 3)
			{
				glTranslated(UNITWIDTH, 0.0f, 0.0f);
				glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
				itemRot = 0; //fixed
			}
			
			
			//draw the railroad
			if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x05)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawRailroad_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawRailroad_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawRailroad_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawRailroad_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawRailroad_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawRailroad_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawRailroad_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawRailroad_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawRailroad_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawRailroad_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawRailroad_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawRailroad_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawRailroad_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawRailroad_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawRailroad_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawRailroad_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
			}					
			

			//draw the wooden R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x00 ||
				RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x34 ||
				RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x35 ||
				RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x41)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawWoodenRC_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawWoodenRC_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawWoodenRC_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawWoodenRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawWoodenRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawWoodenRC_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawWoodenRC_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawWoodenRC_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawWoodenRC_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawWoodenRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawWoodenRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawWoodenRC_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawWoodenRC_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawWoodenRC_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawWoodenRC_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawWoodenRC_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawWoodenRC_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawWoodenRC_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawWoodenRC_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawWoodenRC_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawWoodenRC_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawWoodenRC_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawWoodenRC_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawWoodenRC_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawWoodenRC_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x20)
					DrawWoodenRC_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x21)
					DrawWoodenRC_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawWoodenRC_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRC_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}


			//draw the steel looping R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0F)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03 ||
					thePark.elements[a][b][c].identity == 0x63 ||
					thePark.elements[a][b][c].identity == 0x64)
					DrawSteelRC_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelRC_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelRC_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelRC_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelRC_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelRC_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelRC_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelRC_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelRC_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelRC_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelRC_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelRC_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelRC_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelRC_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelRC_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelRC_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelRC_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x20)
					DrawSteelRC_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x21)
					DrawSteelRC_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelRC_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelRC_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}

			//draw the mine train
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x11)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawMineTrain_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawMineTrain_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawMineTrain_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawMineTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawMineTrain_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawMineTrain_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawMineTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawMineTrain_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawMineTrain_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawMineTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawMineTrain_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawMineTrain_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawMineTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawMineTrain_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawMineTrain_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawMineTrain_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawMineTrain_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawMineTrain_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawMineTrain_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawMineTrain_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawMineTrain_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawMineTrain_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawMineTrain_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawMineTrain_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawMineTrain_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x20)
					DrawMineTrain_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x21)
					DrawMineTrain_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawMineTrain_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawMineTrain_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}


			//draw the inverted R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x03)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawInvertedRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawInvertedRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawInvertedRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawInvertedRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawInvertedRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawInvertedRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawInvertedRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawInvertedRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawInvertedRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawInvertedRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawInvertedRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawInvertedRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawInvertedRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawInvertedRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawInvertedRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawInvertedRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawInvertedRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawInvertedRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawInvertedRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawInvertedRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawInvertedRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawInvertedRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawInvertedRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawInvertedRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawInvertedRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawInvertedRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x66 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_66(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x67 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_67(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x68 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_68(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x69 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_69(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawInvertedRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawInvertedRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}


			
			//draw the suspended R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x02)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSLCRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSLCRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSLCRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSLCRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSLCRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSLCRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSLCRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSLCRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSLCRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSLCRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSLCRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSLCRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSLCRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSLCRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSLCRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSLCRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSLCRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSLCRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSLCRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSLCRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSLCRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSLCRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSLCRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSLCRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x6A && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_6A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x6B && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_6B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x6C && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_6C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x6D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_6D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}
			

			//draw the steel corkscrew R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x13)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelCorkscrewRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelCorkscrewRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelCorkscrewRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelCorkscrewRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelCorkscrewRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelCorkscrewRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelCorkscrewRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelCorkscrewRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelCorkscrewRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelCorkscrewRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelCorkscrewRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelCorkscrewRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelCorkscrewRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSteelCorkscrewRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelCorkscrewRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelCorkscrewRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelCorkscrewRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelCorkscrewRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelCorkscrewRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelCorkscrewRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelCorkscrewRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelCorkscrewRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelCorkscrewRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelCorkscrewRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelCorkscrewRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelCorkscrewRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}

			

			//draw the steel mini R.C.				
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x04)
			{
				
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelMini_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelMini_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelMini_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelMini_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelMini_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelMini_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelMini_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelMini_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelMini_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelMini_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelMini_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelMini_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelMini_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelMini_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelMini_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelMini_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelMini_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x20)
					DrawSteelMini_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x21)
					DrawSteelMini_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}					


			//water coaster
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x4A)
			{

				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelMini_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelMini_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelMini_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelMini_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelMini_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelMini_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelMini_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelMini_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelMini_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelMini_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelMini_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelMini_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelMini_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelMini_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelMini_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelMini_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelMini_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x20)
					DrawSteelMini_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x21)
					DrawSteelMini_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
				else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelMini_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelMini_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				//now take care of the water-based portions of the ride
				else if(thePark.elements[a][b][c].identity == 0x44)
					DrawRiverRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x51 && thePark.elements[a][b][c].elementIndex == 1)
					DrawRiverRide_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x52 && thePark.elements[a][b][c].elementIndex == 1)
					DrawRiverRide_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);



			}					

			
			


			//draw the steel twister R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x33)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelTwisterRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelTwisterRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelTwisterRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelTwisterRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelTwisterRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelTwisterRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelTwisterRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelTwisterRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelTwisterRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelTwisterRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelTwisterRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelTwisterRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelTwisterRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelTwisterRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelTwisterRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelTwisterRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelTwisterRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelTwisterRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelTwisterRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelTwisterRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelTwisterRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelTwisterRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelTwisterRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelTwisterRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xB6)
					DrawSteelTwisterRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);

				else if(thePark.elements[a][b][c].identity == 0xB7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_B7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xB8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_B8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xB9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_B9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xBA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_BA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				

				/*
				else if(thePark.elements[a][b][c].identity >= 0xB8 && thePark.elements[a][b][c].identity <= 0xBA)
					DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
					*/

			}

			
			
			//draw the vertical R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x2C)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelTwisterRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelTwisterRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelTwisterRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelTwisterRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelTwisterRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelTwisterRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelTwisterRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelTwisterRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelTwisterRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelTwisterRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelTwisterRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelTwisterRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelTwisterRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelTwisterRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelTwisterRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelTwisterRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelTwisterRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelTwisterRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelTwisterRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelTwisterRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelTwisterRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelTwisterRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelTwisterRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelTwisterRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelTwisterRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}



			//draw the SLC R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x49)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSLCRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSLCRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSLCRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSLCRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSLCRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSLCRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSLCRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSLCRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSLCRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSLCRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSLCRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSLCRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSLCRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSLCRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSLCRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSLCRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSLCRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSLCRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSLCRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSLCRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSLCRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSLCRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSLCRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSLCRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x66 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_66(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x67 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_67(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x68 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_68(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x69 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_69(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawSLCRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}

			
			//draw the flying R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3E)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelCorkscrewRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelCorkscrewRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelCorkscrewRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelCorkscrewRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelCorkscrewRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelCorkscrewRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelCorkscrewRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelCorkscrewRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelCorkscrewRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelCorkscrewRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelCorkscrewRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelCorkscrewRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelCorkscrewRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSteelCorkscrewRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x12)
					DrawSteelCorkscrewRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x13)
					DrawSteelCorkscrewRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x14)
					DrawSteelCorkscrewRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x15)
					DrawSteelCorkscrewRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x18)
					DrawSteelCorkscrewRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x19)
					DrawSteelCorkscrewRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1A)
					DrawSteelCorkscrewRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1B)
					DrawSteelCorkscrewRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1C)
					DrawSteelCorkscrewRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1D)
					DrawSteelCorkscrewRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1E)
					DrawSteelCorkscrewRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x1F)
					DrawSteelCorkscrewRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelCorkscrewRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
					DrawSteelCorkscrewRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}
			

			
			/*
			//draw the wooden twister R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x34)
			{
				if(thePark.elements[a][b][c].identity == 0x00)
					DrawWoodenRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawWoodenRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawWoodenRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawWoodenRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawWoodenRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawWoodenRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawWoodenRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawWoodenRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawWoodenRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawWoodenRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawWoodenRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawWoodenRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawWoodenRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawWoodenRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}
			*/

			//draw the single rail R.C.
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0A)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSingleRailRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSingleRailRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSingleRailRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSingleRailRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSingleRailRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSingleRailRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSingleRailRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSingleRailRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSingleRailRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 1)
					DrawSingleRailRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 1)
					DrawSingleRailRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}
			
			
			
			//draw the ghost train
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x32)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawGhostTrain_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawGhostTrain_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawGhostTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawGhostTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawGhostTrain_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawGhostTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawGhostTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawGhostTrain_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawGhostTrain_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawGhostTrain_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawGhostTrain_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
					
			}

			//draw the wild mouse
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x09)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawWildMouse_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawWildMouse_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawWildMouse_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawWildMouse_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawWildMouse_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawWildMouse_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawWildMouse_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawWildMouse_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawWildMouse_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);				
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawWildMouse_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawWildMouse_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawWildMouse_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawWildMouse_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWildMouse_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawWildMouse_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawWildMouse_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawWildMouse_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x3E)
					DrawWildMouse_3E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x3F)
					DrawWildMouse_3E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x40)
					DrawWildMouse_40(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x41)
					DrawWildMouse_40(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					
			}


			//draw the virginia reel
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3B)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawVirginiaReel_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawVirginiaReel_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawVirginiaReel_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawVirginiaReel_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawVirginiaReel_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawVirginiaReel_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawVirginiaReel_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawVirginiaReel_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawVirginiaReel_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawVirginiaReel_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawVirginiaReel_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
			}


			//draw the steel wild mouse
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x36)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSteelWildMouse_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSteelWildMouse_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x05)
					DrawSteelWildMouse_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSteelWildMouse_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x07)
					DrawSteelWildMouse_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x08)
					DrawSteelWildMouse_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSteelWildMouse_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSteelWildMouse_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawSteelWildMouse_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);				
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSteelWildMouse_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawSteelWildMouse_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawSteelWildMouse_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSteelWildMouse_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelWildMouse_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawSteelWildMouse_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawSteelWildMouse_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawSteelWildMouse_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x3E)
					DrawSteelWildMouse_3E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x3F)
					DrawSteelWildMouse_3E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x40)
					DrawSteelWildMouse_40(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x41)
					DrawSteelWildMouse_40(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					
			}


			//draw the sky buckets
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x12)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSkyWay_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSkyWay_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSkyWay_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSkyWay_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSkyWay_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSkyWay_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSkyWay_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawSkyWay_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawSkyWay_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
					
			}

			//draw the car ride
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0B)
			{
				//printf("drawing car ride\n");
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawCarRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawCarRide_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawCarRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawCarRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawCarRide_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawCarRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawCarRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawCarRide_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
					DrawCarRide_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawCarRide_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawCarRide_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
					
			}
								

			//draw the log flume
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x17)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawLogFlume_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawLogFlume_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawLogFlume_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawLogFlume_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawLogFlume_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawLogFlume_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawLogFlume_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 1)
					DrawLogFlume_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 1)
					DrawLogFlume_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 1)
					DrawLogFlume_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 1)
					DrawLogFlume_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}

			//draw the rapids ride
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x18)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawRapids_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawRapids_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawRapids_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawRapids_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawRapids_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawRapids_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawRapids_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x32)
					DrawRapids_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x33)
					DrawRapids_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}
			

			//draw the river ride
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3C ||
				RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x4F)
			{
				//printf("drawing river ride\n");

				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawRiverRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawRiverRide_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawRiverRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawRiverRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawRiverRide_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0B)
					DrawRiverRide_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawRiverRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0D)
					DrawRiverRide_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0E)
					DrawRiverRide_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawRiverRide_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawRiverRide_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawRiverRide_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 1)
					DrawRiverRide_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 1)
					DrawRiverRide_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
			}

			
			//draw the space shot
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0C)
			{
				if(thePark.elements[a][b][c].identity == 0x42 && thePark.elements[a][b][c].elementIndex == 4)
					DrawSpaceShot_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				if(thePark.elements[a][b][c].identity == 0x43 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSpaceShot_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);					
				
			}
			//draw the roto drop
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x45)
			{
				//glPushMatrix();

					//glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
					//glTranslated(0.0f, 0.0f, -UNITWIDTH);

				if(thePark.elements[a][b][c].identity == 0x42 && thePark.elements[a][b][c].elementIndex == 128)
				{
					//printf("elementIndex=%d\n", thePark.elements[a][b][c].elementIndex);
					//DrawRotoDrop_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					DrawObservationTower_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				}
				if(thePark.elements[a][b][c].identity == 0x43 && thePark.elements[a][b][c].elementIndex == 0)
					//DrawRotoDrop_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);					
					DrawObservationTower_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				//glPopMatrix();
			}

			//draw the observation tower
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0E)
			{
				if(thePark.elements[a][b][c].identity == 0x42 && thePark.elements[a][b][c].elementIndex == 128)
					DrawObservationTower_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				if(thePark.elements[a][b][c].identity == 0x43 && thePark.elements[a][b][c].elementIndex == 0)
					DrawObservationTower_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);					
			}
			
			//draw the monorail
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x06)
			{
				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawMonorail_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawMonorail_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				
			}


			//draw the suspended monorail
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3F)
			{
				glPushMatrix();

					glTranslated(0.0f, 1.5 * UNITHEIGHT, 0.0f);

				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawMonorail_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawMonorail_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawMonorail_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				glPopMatrix();
				
			}

			//draw the suspended single rail coaster
			else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x07)
			{
				glPushMatrix();

					//glTranslated(0.0f, 1.5 * UNITHEIGHT, 0.0f);

				if(thePark.elements[a][b][c].identity == 0x00 ||
					thePark.elements[a][b][c].identity == 0x01 ||
					thePark.elements[a][b][c].identity == 0x02 ||
					thePark.elements[a][b][c].identity == 0x03)
					DrawSuspendedSingleRail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x04)
					DrawSuspendedSingleRail_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x06)
					DrawSuspendedSingleRail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x09)
					DrawSuspendedSingleRail_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0A)
					DrawSuspendedSingleRail_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0C)
					DrawSuspendedSingleRail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x0F)
					DrawSuspendedSingleRail_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x63)
					DrawSuspendedSingleRail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
				else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
					DrawSuspendedSingleRail_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
				else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
					DrawSuspendedSingleRail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

				glPopMatrix();
				
			}




			glPopMatrix();
		}
	}

	glDisable    ( GL_ALPHA_TEST   );
	glDisable(GL_TEXTURE_2D);

	
}


void oldDrawElements(void)
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

	int a,b,c;

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

	//loop through the list of elements
	for(a=(int)startX; a<(int)endX; a++)
	{
		for(b=(int)startZ; b<(int)endZ; b++)
		{
			for(c=0; c<thePark.elements[a][b].size(); c++)
			{	
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_ALPHA_TEST);
				//printf("looping1\n");
				if(CubeInFrustum(thePark.elements[a][b][c].x * UNITWIDTH, (thePark.elements[a][b][c].base * UNITHEIGHT) + 0.1f, (thePark.elements[a][b][c].z + 1)*UNITWIDTH, UNITWIDTH, (thePark.elements[a][b][c].base + 1) + 0.1f, UNITWIDTH) == TRUE) 
				//if(1 == 1) 
				{			
					glColor3f(1.0f, 1.0f, 1.0f);

					glPushMatrix();

					glTranslated((thePark.elements[a][b][c].x) * UNITWIDTH, (thePark.elements[a][b][c].base * UNITHEIGHT) + 0.1f, (thePark.elements[a][b][c].z + 1) * UNITWIDTH);						
					
					if(thePark.elements[a][b][c].elementOrientation == 0)
					{
						glTranslated(0.0f, 0.0f, 0.0f);
						glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
					}
					else if(thePark.elements[a][b][c].elementOrientation == 1)
					{
						glTranslated(0.0f, 0.0f, -UNITWIDTH);
						glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
					}
					else if(thePark.elements[a][b][c].elementOrientation == 2)
					{
						glTranslated(UNITWIDTH, 0.0f, -UNITWIDTH);
						glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
					}
					else if(thePark.elements[a][b][c].elementOrientation == 3)
					{
						glTranslated(UNITWIDTH, 0.0f, 0.0f);
						glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
					}
					
					
					//draw the railroad
					if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x05)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawRailroad_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawRailroad_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawRailroad_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawRailroad_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawRailroad_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawRailroad_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawRailroad_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawRailroad_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawRailroad_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawRailroad_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawRailroad_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawRailroad_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawRailroad_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawRailroad_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawRailroad_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawRailroad_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
					}					
					

					//draw the wooden R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x00 ||
						RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x34)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawWoodenRC_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawWoodenRC_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawWoodenRC_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawWoodenRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawWoodenRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawWoodenRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawWoodenRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawWoodenRC_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawWoodenRC_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawWoodenRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawWoodenRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawWoodenRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawWoodenRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawWoodenRC_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawWoodenRC_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawWoodenRC_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawWoodenRC_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawWoodenRC_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawWoodenRC_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawWoodenRC_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawWoodenRC_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawWoodenRC_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawWoodenRC_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawWoodenRC_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawWoodenRC_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x20)
							DrawWoodenRC_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x21)
							DrawWoodenRC_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawWoodenRC_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRC_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}


					//draw the steel looping R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0F)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03 ||
							thePark.elements[a][b][c].identity == 0x63 ||
							thePark.elements[a][b][c].identity == 0x64)
							DrawSteelRC_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSteelRC_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSteelRC_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSteelRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSteelRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSteelRC_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSteelRC_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSteelRC_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSteelRC_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSteelRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSteelRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSteelRC_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSteelRC_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelRC_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelRC_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelRC_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelRC_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelRC_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelRC_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelRC_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelRC_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelRC_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelRC_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelRC_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelRC_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x20)
							DrawSteelRC_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x21)
							DrawSteelRC_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelRC_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelRC_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}

					//draw the mine train
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x11)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawMineTrain_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawMineTrain_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawMineTrain_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawMineTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawMineTrain_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawMineTrain_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawMineTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawMineTrain_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawMineTrain_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawMineTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawMineTrain_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawMineTrain_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawMineTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawMineTrain_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawMineTrain_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawMineTrain_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawMineTrain_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawMineTrain_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawMineTrain_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawMineTrain_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawMineTrain_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawMineTrain_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawMineTrain_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawMineTrain_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawMineTrain_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x20)
							DrawMineTrain_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x21)
							DrawMineTrain_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawMineTrain_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawMineTrain_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}


					//draw the inverted R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x03)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawInvertedRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawInvertedRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawInvertedRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawInvertedRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawInvertedRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawInvertedRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawInvertedRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawInvertedRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawInvertedRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawInvertedRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawInvertedRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawInvertedRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawInvertedRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawInvertedRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawInvertedRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawInvertedRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawInvertedRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawInvertedRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawInvertedRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawInvertedRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawInvertedRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawInvertedRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawInvertedRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawInvertedRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawInvertedRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawInvertedRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}


					
					//draw the suspended R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x02)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawInvertedRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawInvertedRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawInvertedRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawInvertedRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawInvertedRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawInvertedRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawInvertedRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawInvertedRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawInvertedRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawInvertedRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawInvertedRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawInvertedRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawInvertedRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawInvertedRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawInvertedRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawInvertedRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawInvertedRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawInvertedRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawInvertedRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawInvertedRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawInvertedRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawInvertedRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawInvertedRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawInvertedRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawInvertedRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawInvertedRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawInvertedRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawInvertedRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}
					

					//draw the steel corkscrew R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x13)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSteelCorkscrewRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSteelCorkscrewRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSteelCorkscrewRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSteelCorkscrewRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSteelCorkscrewRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSteelCorkscrewRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSteelCorkscrewRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSteelCorkscrewRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSteelCorkscrewRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSteelCorkscrewRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSteelCorkscrewRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSteelCorkscrewRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSteelCorkscrewRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawSteelCorkscrewRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelCorkscrewRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelCorkscrewRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelCorkscrewRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelCorkscrewRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelCorkscrewRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelCorkscrewRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelCorkscrewRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelCorkscrewRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelCorkscrewRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelCorkscrewRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelCorkscrewRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelCorkscrewRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelCorkscrewRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelCorkscrewRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}

					

					//draw the steel mini R.C.				
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x04)
					{
						
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSteelMini_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSteelMini_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSteelMini_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSteelMini_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSteelMini_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelMini_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelMini_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelMini_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelMini_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelMini_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelMini_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelMini_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelMini_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelMini_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelMini_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelMini_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelMini_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x20)
							DrawSteelMini_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x21)
							DrawSteelMini_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}					


					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x4A)
					{

						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSteelMini_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSteelMini_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSteelMini_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSteelMini_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSteelMini_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSteelMini_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSteelMini_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSteelMini_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSteelMini_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x11 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelMini_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelMini_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelMini_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelMini_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x16 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x17 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelMini_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelMini_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelMini_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelMini_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelMini_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelMini_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelMini_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelMini_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x20)
							DrawSteelMini_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x21)
							DrawSteelMini_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);						
						else if(thePark.elements[a][b][c].identity == 0x22 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x23 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x24 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x25 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2C &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2E &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2F &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x30 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x31 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x85 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x86 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x87 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x88 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x89 &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8A &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8B &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8C &&  thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelMini_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8D &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x8F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x90 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						else if(thePark.elements[a][b][c].identity == 0x9E &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelMini_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						//now take care of the water-based portions of the ride
						else if(thePark.elements[a][b][c].identity == 0x44)
							DrawRiverRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x51 && thePark.elements[a][b][c].elementIndex == 1)
							DrawRiverRide_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x52 && thePark.elements[a][b][c].elementIndex == 1)
							DrawRiverRide_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);



					}					

					
					


					//draw the steel twister R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x33)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSteelTwisterRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSteelTwisterRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSteelTwisterRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSteelTwisterRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSteelTwisterRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSteelTwisterRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSteelTwisterRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSteelTwisterRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSteelTwisterRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSteelTwisterRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSteelTwisterRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSteelTwisterRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelTwisterRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelTwisterRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelTwisterRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelTwisterRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelTwisterRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelTwisterRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelTwisterRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelTwisterRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelTwisterRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelTwisterRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelTwisterRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelTwisterRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xB6)
							DrawSteelTwisterRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);

					}

					
					
					//draw the vertical R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x2C)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSteelTwisterRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSteelTwisterRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSteelTwisterRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSteelTwisterRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSteelTwisterRollerCoaster_08(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSteelTwisterRollerCoaster_09(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSteelTwisterRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSteelTwisterRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSteelTwisterRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSteelTwisterRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSteelTwisterRollerCoaster_0E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSteelTwisterRollerCoaster_0F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawSteelTwisterRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSteelTwisterRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSteelTwisterRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSteelTwisterRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSteelTwisterRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSteelTwisterRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSteelTwisterRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSteelTwisterRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSteelTwisterRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSteelTwisterRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSteelTwisterRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSteelTwisterRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSteelTwisterRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSteelTwisterRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawSteelTwisterRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}



					//draw the SLC R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x49)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSLCRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSLCRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSLCRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSLCRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSLCRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSLCRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSLCRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSLCRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSLCRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSLCRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSLCRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSLCRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSLCRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSLCRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSLCRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSLCRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSLCRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSLCRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSLCRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSLCRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSLCRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSLCRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSLCRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSLCRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}

					
					//draw the flying R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3E)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSLCRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawSLCRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSLCRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawSLCRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawSLCRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSLCRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSLCRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawSLCRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSLCRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawSLCRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawSLCRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSLCRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawSLCRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x12)
							DrawSLCRollerCoaster_12(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x13)
							DrawSLCRollerCoaster_13(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x14)
							DrawSLCRollerCoaster_14(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x15)
							DrawSLCRollerCoaster_15(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x16 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_16(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x17 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_17(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x18)
							DrawSLCRollerCoaster_18(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x19)
							DrawSLCRollerCoaster_19(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1A)
							DrawSLCRollerCoaster_1A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1B)
							DrawSLCRollerCoaster_1B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1C)
							DrawSLCRollerCoaster_1C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1D)
							DrawSLCRollerCoaster_1D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1E)
							DrawSLCRollerCoaster_1E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x1F)
							DrawSLCRollerCoaster_1F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x20 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_20(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x21 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_21(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x22 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_22(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x23 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_23(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x24 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_24(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x25 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_25(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2D && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_2F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x30 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_30(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x31 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_31(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x5F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_5F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x60 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_60(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x61 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_61(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x62 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_62(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x89 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_89(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8A && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_8A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8B && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_8B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8C && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_8C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSLCRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9E && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_9E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x9F && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_9F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA0 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A0(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA1 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A1(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA2 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A2(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA3 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A3(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA4 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A4(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA5 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A5(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA6 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A6(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA7 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A7(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA8 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A8(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xA9 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_A9(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAA && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_AA(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0xAB && thePark.elements[a][b][c].elementIndex == 0)
							DrawSLCRollerCoaster_AB(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}
					

					
					/*
					//draw the wooden twister R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x34)
					{
						if(thePark.elements[a][b][c].identity == 0x00)
							DrawWoodenRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawWoodenRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x05)
							DrawWoodenRollerCoaster_05(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawWoodenRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x07)
							DrawWoodenRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x08)
							DrawWoodenRollerCoaster_07(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawWoodenRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawWoodenRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawWoodenRollerCoaster_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawWoodenRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawWoodenRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawWoodenRollerCoaster_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawWoodenRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8F && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_8F(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x91 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_91(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x92 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_92(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x95 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_95(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x97 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x98 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_97(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawWoodenRollerCoaster_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}
					*/

					//draw the single rail R.C.
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0A)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSingleRailRollerCoaster_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSingleRailRollerCoaster_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSingleRailRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSingleRailRollerCoaster_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSingleRailRollerCoaster_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSingleRailRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSingleRailRollerCoaster_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSingleRailRollerCoaster_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawSingleRailRollerCoaster_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 1)
							DrawSingleRailRollerCoaster_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 1)
							DrawSingleRailRollerCoaster_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}
					
					
					
					//draw the ghost train
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x32)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawGhostTrain_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawGhostTrain_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawGhostTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawGhostTrain_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawGhostTrain_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawGhostTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawGhostTrain_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawGhostTrain_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawGhostTrain_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
						else if(thePark.elements[a][b][c].identity == 0x32)
							DrawGhostTrain_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x33)
							DrawGhostTrain_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
							
					}


					//draw the sky buckets
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x12)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawSkyWay_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawSkyWay_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawSkyWay_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawSkyWay_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawSkyWay_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawSkyWay_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawSkyWay_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x32)
							DrawSkyWay_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x33)
							DrawSkyWay_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
							
					}

					//draw the car ride
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0B)
					{
						//printf("drawing car ride\n");
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawCarRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawCarRide_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawCarRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawCarRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawCarRide_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawCarRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawCarRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawCarRide_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x2B &&  thePark.elements[a][b][c].elementIndex == 1)
							DrawCarRide_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);												
						else if(thePark.elements[a][b][c].identity == 0x32)
							DrawCarRide_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
						else if(thePark.elements[a][b][c].identity == 0x33)
							DrawCarRide_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);						
							
					}
										

					//draw the log flume
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x17)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawLogFlume_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawLogFlume_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawLogFlume_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawLogFlume_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawLogFlume_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawLogFlume_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawLogFlume_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 1)
							DrawLogFlume_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 1)
							DrawLogFlume_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 1)
							DrawLogFlume_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 1)
							DrawLogFlume_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}

					//draw the rapids ride
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x18)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawRapids_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawRapids_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawRapids_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawRapids_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawRapids_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawRapids_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawRapids_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x32)
							DrawRapids_32(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x33)
							DrawRapids_33(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
					}
					

					//draw the river ride and raft ride
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3C ||
						RideList[thePark.elements[a][b][c].rideIndex].rideType == 79)
					{
						if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x4F)
							printf("drawing raft ride\n");

						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawRiverRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawRiverRide_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawRiverRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawRiverRide_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawRiverRide_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0B)
							DrawRiverRide_0B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawRiverRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0D)
							DrawRiverRide_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0E)
							DrawRiverRide_0D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawRiverRide_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawRiverRide_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawRiverRide_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 1)
							DrawRiverRide_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 1)
							DrawRiverRide_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x44)
							DrawRiverRide_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						

					}

					
					//draw the space shot
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0C)
					{
						if(thePark.elements[a][b][c].identity == 0x42 && thePark.elements[a][b][c].elementIndex == 4)
							DrawSpaceShot_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						if(thePark.elements[a][b][c].identity == 0x43 && thePark.elements[a][b][c].elementIndex == 0)
							DrawSpaceShot_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);					
						
					}
					//draw the roto drop
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x45)
					{
						if(thePark.elements[a][b][c].identity == 0x42 && thePark.elements[a][b][c].elementIndex == 128)
						{
							//printf("elementIndex=%d\n", thePark.elements[a][b][c].elementIndex);
							DrawRotoDrop_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						}
						if(thePark.elements[a][b][c].identity == 0x43 && thePark.elements[a][b][c].elementIndex == 0)
							DrawRotoDrop_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);					
					}

					//draw the observation tower
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x0E)
					{
						if(thePark.elements[a][b][c].identity == 0x42 && thePark.elements[a][b][c].elementIndex == 128)
							DrawObservationTower_42(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						if(thePark.elements[a][b][c].identity == 0x43 && thePark.elements[a][b][c].elementIndex == 0)
							DrawObservationTower_43(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);					
					}
					
					//draw the monorail
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x06)
					{
						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawMonorail_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawMonorail_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						
					}


					//draw the suspended single rail coaster and suspended monorail
					else if(RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x07 ||
						RideList[thePark.elements[a][b][c].rideIndex].rideType == 0x3F)
					{
						glPushMatrix();

							glTranslated(0.0f, 1.5 * UNITHEIGHT, 0.0f);

						if(thePark.elements[a][b][c].identity == 0x00 ||
							thePark.elements[a][b][c].identity == 0x01 ||
							thePark.elements[a][b][c].identity == 0x02 ||
							thePark.elements[a][b][c].identity == 0x03)
							DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x04)
							DrawMonorail_04(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x06)
							DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x09)
							DrawMonorail_06(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0A)
							DrawMonorail_0A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0C)
							DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x0F)
							DrawMonorail_0C(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x10 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_10(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x11 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_11(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x26 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_26(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x27 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_27(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x63)
							DrawMonorail_00(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor, false);
						else if(thePark.elements[a][b][c].identity == 0x2A && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_2A(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x2B && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_2B(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x85 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_85(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x86 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_86(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x87 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_87(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x88 && thePark.elements[a][b][c].elementIndex == 0)
							DrawMonorail_88(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8D && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_8D(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x8E && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_8E(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x90 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_90(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x93 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_93(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x94 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_94(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x96 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);
						else if(thePark.elements[a][b][c].identity == 0x99 && thePark.elements[a][b][c].elementIndex == 1)
							DrawMonorail_96(thePark.elements[a][b][c].rideIndex, thePark.elements[a][b][c].baseColor);

						glPopMatrix();
						
					}



					glPopMatrix();
				}
			}
		}
	}

	glDisable    ( GL_ALPHA_TEST   );
	glDisable(GL_TEXTURE_2D);

	
}
