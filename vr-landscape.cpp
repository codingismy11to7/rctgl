#include "vr3d.h" 
#include "bbVertex.h"

GLuint LANDSCAPE_LIST;
//extern landscape_t thePark.landscape[128][128];
extern ParkStructType thePark;

extern float edgeLighting[4][4];

void crossProduct(bbVertex v1, bbVertex v2, bbVertex *out)
{
	/*
	x = Ay * Bz - By * Az
	y = Az * Bx - Bz * Ax
	z = Ax * By - Bx * Ay
	*/
	out->x = v1.x * v2.z - v2.y * v1.z;
	out->y = v1.z * v2.x - v2.z * v1.x;
	out->z = v1.x * v2.y - v2.x * v1.y;
}

void CreateLandscape(void)
{
	printf(" - Building display list for landscape\n");

	LANDSCAPE_LIST = glGenLists(1);

	glNewList(LANDSCAPE_LIST, GL_COMPILE);
		DrawLandscape();
	glEndList();

	printf("%d Polygons in Landscape\n", NumPolys);
}


void LoadLandscape(char *filename)
{
	FILE *input;

	int i,j;
	long nextbyte;
	long currentbyte;
	int tempheight;
	//int LLmodifier;
	int looping;

	unsigned char buffer;

	printf("- in LoadLandscape\n");

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
			
			/* The following bit configurations mean that we've hit the land segment
			 * basically, we don't care what the outer four bits are
			 * 00000000 - 0		- basic land piece
			 * 00000001 - 1		- land w/extended surface flag
			 * 00000010 - 2
			 * 00000011	- 3
			 * 01000000 - 64
			 * 01000001 - 65
			 * 01000010 - 66
			 * 01000011 - 67
			 * 10000000 - 128	- land w/extended edge flag
			 * 10000001 - 129	- land with both extended surface & edge
			 * 10000010 - 130
			 * 10000011 - 131
			 * 11000000 - 192
			 * 11000001 - 193
			 * 11000010 - 194
			 * 11000011 - 195
			 */

			//while(buffer != 0 && buffer != 1 && buffer != 128 && buffer != 129) //28)
			while(1)
			{
				if (buffer >= 0 && buffer <= 3)
					break;
				if (buffer >= 64 && buffer <= 67)
					break;
				if (buffer >= 128 && buffer <= 131)
					break;
				if (buffer >= 192 && buffer <= 195)
					break;

				//if(looping == 1)
				//	printf("looping for land at %d\n", nextbyte);

				looping++;

				//move to the next land segment
				fseek(input, nextbyte, SEEK_SET);

				buffer = fgetc(input);

				nextbyte += 8;

				if((nextbyte - 8) >= 393231)
				{
					printf("Error1: We are beyond the game map. stop at %d, %d (%d)\nAborting\n", i, j, nextbyte - 8);
					exit(-1);
				}
			}			//6728

			//printf("found land at %d\n", nextbyte - 8);
			

			// check the rightmost bit for LL-surface extensions
			if((buffer % 2 == 0) || buffer == 0)
				thePark.landscape[i][j].LLmodifierS = 0;
			else
				thePark.landscape[i][j].LLmodifierS = 1;

			// check the leftmost bit for LL-edge extensions
			if(buffer < 128)
				thePark.landscape[i][j].LLmodifierE = 0;
			else
				thePark.landscape[i][j].LLmodifierE = 1;


			currentbyte = nextbyte - 8;

			// if we're here, then buffer is zero, which means that we've
			// hit a land piece (as opposed to an object piece)

			// get the height of the land
			fseek(input, currentbyte + 2, SEEK_SET);

			buffer = fgetc(input);

			tempheight = buffer;

			if (tempheight > 0)
			{
				thePark.landscape[i][j].TL = tempheight / 4;
				thePark.landscape[i][j].TR = tempheight / 4;
				thePark.landscape[i][j].BL = tempheight / 4;
				thePark.landscape[i][j].BR = tempheight / 4;
			}
			else
			{
				thePark.landscape[i][j].TL = 0;
				thePark.landscape[i][j].TR = 0;
				thePark.landscape[i][j].BL = 0;
				thePark.landscape[i][j].BR = 0;
			}

			//printf("height for (%d, %d) is %d (byte %d)\n", j, i, thePark.landscape[i][j].TR, currentbyte + 2);

			// get the edge type
			fseek(input, currentbyte + 4, SEEK_SET);

			buffer = fgetc(input);

			/*
			if(thePark.landscape[i][j].LLmodifierE == 0)
			{
			*/
				//is it a red wall?
				if (buffer >= 224)
				{
					thePark.landscape[i][j].sidetexture = 0x111;
					buffer -= 224;
				}
				//is it a black wall?
				else if(buffer >=192)
				{
					thePark.landscape[i][j].sidetexture = 0x110;
					buffer -= 192;
				}
				//is it a yellow wall?
				else if(buffer >=160)
				{
					thePark.landscape[i][j].sidetexture = 0x101;
					buffer -= 160;
				}
				//is it a gray wall?
				else if(buffer >=128)
				{
					thePark.landscape[i][j].sidetexture = 0x100;
					buffer -= 128;
				}
				//is it a wood wall?
				else if(buffer >=96)
				{
					thePark.landscape[i][j].sidetexture = 0x011;
					buffer -= 96;
				}
				//is it a iron wall?
				else if(buffer >=64)
				{
					thePark.landscape[i][j].sidetexture = 0x010;
					buffer -= 64;
				}
				//is it a brick wall?
				else if(buffer >=32)
				{
					thePark.landscape[i][j].sidetexture = 0x001;
					buffer -= 32;
				}
				// it must be a dirt wall
				else
				{
					thePark.landscape[i][j].sidetexture = 0x000;
					buffer -= 0;
				}
			/*
			}
			else
				thePark.landscape[i][j].sidetexture = -1;
				*/


			// now that we have the edge type, we can calculate the terrain-style
			switch(buffer)
			{
			//one corner is raised
			case 1:
				thePark.landscape[i][j].TL++;
				break;
			case 2:
				thePark.landscape[i][j].TR++;
				break;
			case 4:
				thePark.landscape[i][j].BR++;
				break;
			case 8:
				thePark.landscape[i][j].BL++;
				break;

			// both corners are raised
			case 5:
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].BR++;
				break;
			case 10:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].BL++;
				break;

			// one edge is raised
			case 3:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].TL++;
				break;
			case 6:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].BR++;
				break;
			case 12:
				thePark.landscape[i][j].BR++;
				thePark.landscape[i][j].BL++;
				break;
			case 9:
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].BL++;
				break;

			// one corner is lowered
			case 14:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].BR++;
				thePark.landscape[i][j].BL++;
				break;
			case 13:
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].BR++;
				thePark.landscape[i][j].BL++;
				break;
			case 11:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].BL++;
				break;
			case 7:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].BR++;
				break;

			// one corner raises whole piece
			case 23:
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].TR+=2;
				thePark.landscape[i][j].BR++;
				break;
			case 27:
				thePark.landscape[i][j].TL+=2;
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].BL++;
				break;
			case 30:
				thePark.landscape[i][j].TR++;
				thePark.landscape[i][j].BR+=2;
				thePark.landscape[i][j].BL++;
				break;
			case 29:
				thePark.landscape[i][j].TL++;
				thePark.landscape[i][j].BR++;
				thePark.landscape[i][j].BL+=2;
				break;


			// this is flat land
			default:
				break;
			}


			// get the terrain type
			fseek(input, currentbyte + 5, SEEK_SET);

			buffer = fgetc(input);

			//is it a roofing or green grid tile?
			if (buffer >= 224)
			{
				thePark.landscape[i][j].toptexture = 0x111;
				buffer -= 224;
			}
			//is it a dirt/grass or purple grid tile?
			else if(buffer >=192)
			{
				thePark.landscape[i][j].toptexture = 0x110;
				buffer -= 192;
			}
			//is it a checkerboard or yellow grid tile?
			else if(buffer >=160)
			{
				thePark.landscape[i][j].toptexture = 0x101;
				buffer -= 160;
			}
			//is it a martian or red grid tile?
			else if(buffer >=128)
			{
				thePark.landscape[i][j].toptexture = 0x100;
				buffer -= 128;
			}
			//is it a rock or grey roofing tile?
			else if(buffer >=96)
			{
				thePark.landscape[i][j].toptexture = 0x011;
				buffer -= 96;
			}
			//is it a dirt or iron roof tile?
			else if(buffer >=64)
			{
				thePark.landscape[i][j].toptexture = 0x010;
				buffer -= 64;
			}
			//is it a sand or log roof tile?
			else if(buffer >=32)
			{
				thePark.landscape[i][j].toptexture = 0x001;
				buffer -= 32;
			}
			// it must be a grass or ice tile
			else
				thePark.landscape[i][j].toptexture = 0x000;

			// now that we remove the top 3 bits from the byte, we can get the level
			if(buffer < 64)
				thePark.landscape[i][j].waterlevel = buffer;
			else
				thePark.landscape[i][j].waterlevel = 0;

			//printf("height for (%d, %d) is %d (byte %d)\n", j, i, thePark.landscape[i][j].height, currentbyte + 2);


			// loop until we get the 'last element' bit
			buffer = 1;

			currentbyte = nextbyte - 8;

			/*
			printf("starting endbyte seek at %d\n", nextbyte);
			
			looping = 0;
			
			while(buffer < 128)
			{
				if(looping == 1)
					printf("looping for land end at %d\n", nextbyte);

				looping = 1;

				//move to the next land segment
				fseek(input, currentbyte + 1, SEEK_SET);

				buffer = fgetc(input);

				if((nextbyte - 8) > 393231)
				{
					printf("Error2: We are beyond the game map. stop at %d, %d (%d)\nAborting\n", i, j, nextbyte - 8);
					exit(-1);
				}

				nextbyte += 8;
				currentbyte += 8;
			}

			nextbyte -= 8;

			printf("finishing endbyte seek at %d\n", nextbyte);
			*/

			//printf("end of block at %d\n", nextbyte);
		}
	}
	
	//now we need to populate the highest / lowest variables
	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			thePark.landscape[i][j].highest = -1;
			thePark.landscape[i][j].lowest = 999;
		}
	}

	for(i=0; i<128; i++)
	{
		for(j=0; j<128; j++)
		{
			if(thePark.landscape[i][j].BL < thePark.landscape[i][j].lowest)
				thePark.landscape[i][j].lowest = thePark.landscape[i][j].BL;

			if(thePark.landscape[i][j].BL > thePark.landscape[i][j].highest)
				thePark.landscape[i][j].highest = thePark.landscape[i][j].BL;

			if(thePark.landscape[i][j].BR < thePark.landscape[i][j].lowest)
				thePark.landscape[i][j].lowest = thePark.landscape[i][j].BR;

			if(thePark.landscape[i][j].BR > thePark.landscape[i][j].highest)
				thePark.landscape[i][j].highest = thePark.landscape[i][j].BR;

			if(thePark.landscape[i][j].TR < thePark.landscape[i][j].lowest)
				thePark.landscape[i][j].lowest = thePark.landscape[i][j].TR;

			if(thePark.landscape[i][j].TR > thePark.landscape[i][j].highest)
				thePark.landscape[i][j].highest = thePark.landscape[i][j].TR;

			if(thePark.landscape[i][j].TL < thePark.landscape[i][j].lowest)
				thePark.landscape[i][j].lowest = thePark.landscape[i][j].TL;

			if(thePark.landscape[i][j].TL > thePark.landscape[i][j].highest)
				thePark.landscape[i][j].highest = thePark.landscape[i][j].TL;

		}
	}


}

void drawWater(void)
{
	int mapsize = 128;
	int Mdetailsize = 20;
	int Hdetailsize = 50;

	int gridX, gridZ;
	int startX, startZ;
	int endX, endZ;

	//move the water
	xWaterOffset += 0.025f;
	zWaterOffset += 0.01f;


	if(xWaterOffset > 1.0f)
		xWaterOffset = 0.0f;

	if(zWaterOffset > 1.0f)
		zWaterOffset = 0.0f;

	if(detailLevel == M_LOW_DETAIL || detailLevel == M_MEDIUM_DETAIL)
	{	
		//find the grid location of the viewpoint
		gridX = (int)(XV / UNITWIDTH);
		gridZ = (int)(ZV / UNITWIDTH);

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
		gridX = (int)(XV / UNITWIDTH);
		gridZ = (int)(ZV / UNITWIDTH);

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

	int startQuad, endQuad;

	float val, r, g, b;
	float baseColor[3] = {1.0f, 1.0f, 1.0f};

	glEnable(GL_BLEND);

	val = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val, &r, &g, &b);

	glColor4f(r, g, b, 0.75f);

	glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

	float waterlevel, oldwaterlevel;

	int i, j;

	for(i=startX; i<endX; i++)
	{
		startQuad = -1;
		endQuad = -1;
		oldwaterlevel = -1;

		for(j=startZ; j<endZ; j++)
		{
			waterlevel = thePark.landscape[i][j].waterlevel;

			if(waterlevel > thePark.landscape[i][j].BR ||
			   waterlevel > thePark.landscape[i][j].BL ||
			   waterlevel > thePark.landscape[i][j].TL ||
			   waterlevel > thePark.landscape[i][j].TR)
			{
				glBegin(GL_QUADS);
					//1
					glTexCoord2f(0.0f + xWaterOffset, 0.0f + zWaterOffset);
					glVertex3f(i * UNITWIDTH,     waterlevel * UNITHEIGHT - 0.1f, j * UNITWIDTH);
					//4
					glTexCoord2f(0.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
					glVertex3f(i * UNITWIDTH,     waterlevel * UNITHEIGHT - 0.1f, (j + 1.0f) * UNITWIDTH);
					//3
					glTexCoord2f(1.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
					glVertex3f((i+1) * UNITWIDTH, waterlevel * UNITHEIGHT - 0.1f, (j + 1.0f) * UNITWIDTH);
					//2
					glTexCoord2f(1.0f + xWaterOffset, 0.0f + zWaterOffset);
					glVertex3f((i+1) * UNITWIDTH, waterlevel * UNITHEIGHT - 0.1f, j * UNITWIDTH);
				glEnd();
			}
			/*
			
			//is the water higher than any point?
			if(startQuad == -1 && (waterlevel > thePark.landscape[i][j].BR ||
			   waterlevel > thePark.landscape[i][j].BL ||
			   waterlevel > thePark.landscape[i][j].TL ||
			   waterlevel > thePark.landscape[i][j].TR))
			{
			   startQuad = endQuad = j;			   
			   oldwaterlevel = waterlevel;
			}
			else if //if we have a start point defined and 
				(startQuad > -1 && oldwaterlevel == waterlevel &&
				(waterlevel <= thePark.landscape[i][j].BR &&
				waterlevel <= thePark.landscape[i][j].BL &&
				waterlevel <= thePark.landscape[i][j].TL &&
				waterlevel <= thePark.landscape[i][j].TR))
			{				
				//if(CubeInFrustum((float)(i*UNITWIDTH), (float)((thePark.landscape[i][j].waterlevel * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH), (float)(UNITWIDTH), 0.1f, (float)((savecount + 1.0f) * UNITWIDTH)) == TRUE) 
				{
					glBegin(GL_QUADS);
						//1
						glTexCoord2f(0.0f + xWaterOffset, 0.0f + zWaterOffset);
						glVertex3f(i * UNITWIDTH,     oldwaterlevel * UNITHEIGHT, startQuad * UNITWIDTH);
						//4
						glTexCoord2f(0.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
						glVertex3f(i * UNITWIDTH,     oldwaterlevel * UNITHEIGHT, (endQuad + 1.0f) * UNITWIDTH);
						//3
						glTexCoord2f(1.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
						glVertex3f((i+1) * UNITWIDTH, oldwaterlevel * UNITHEIGHT, (endQuad + 1.0f) * UNITWIDTH);
						//2
						glTexCoord2f(1.0f + xWaterOffset, 0.0f + zWaterOffset);
						glVertex3f((i+1) * UNITWIDTH, oldwaterlevel * UNITHEIGHT, startQuad * UNITWIDTH);
					glEnd();					
				}

				startQuad = endQuad = waterlevel = -1;
			}
			//water levels are different. restart the cycle
			else if(startQuad > -1 && (oldwaterlevel != waterlevel) &&
				(waterlevel > thePark.landscape[i][j].BR ||
				waterlevel > thePark.landscape[i][j].BL ||
				waterlevel > thePark.landscape[i][j].TL ||
				waterlevel > thePark.landscape[i][j].TR))
			{
				//if(CubeInFrustum((float)(i*UNITWIDTH), (float)((thePark.landscape[i][j].waterlevel * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH), (float)(UNITWIDTH), 0.1f, (float)((savecount + 1.0f) * UNITWIDTH)) == TRUE) 
				{
					glBegin(GL_QUADS);
						//1
						glTexCoord2f(0.0f + xWaterOffset, 0.0f + zWaterOffset);
						glVertex3f(i * UNITWIDTH,     oldwaterlevel * UNITHEIGHT - 0.1f, startQuad * UNITWIDTH);
						//4
						glTexCoord2f(0.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
						glVertex3f(i * UNITWIDTH,     oldwaterlevel * UNITHEIGHT - 0.1f, (endQuad + 1.0f) * UNITWIDTH);
						//3
						glTexCoord2f(1.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
						glVertex3f((i+1) * UNITWIDTH, oldwaterlevel * UNITHEIGHT - 0.1f, (endQuad + 1.0f) * UNITWIDTH);
						//2
						glTexCoord2f(1.0f + xWaterOffset, 0.0f + zWaterOffset);
						glVertex3f((i+1) * UNITWIDTH, oldwaterlevel * UNITHEIGHT - 0.1f, startQuad * UNITWIDTH);
					glEnd();					
				}

				startQuad = endQuad = j;
				oldwaterlevel = waterlevel;
			}
			//water level is still > ground level
			else if(startQuad > -1 && (oldwaterlevel == waterlevel) &&
				(waterlevel > thePark.landscape[i][j].BR ||
				waterlevel > thePark.landscape[i][j].BL ||
				waterlevel > thePark.landscape[i][j].TL ||
				waterlevel > thePark.landscape[i][j].TR))
			{
				endQuad++;
			}
			*/
		}


		/*
		//draw to the edge of the map
		if(startQuad > -1)
		{
			//if(CubeInFrustum((float)(i*UNITWIDTH), (float)((thePark.landscape[i][j].waterlevel * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH), (float)(UNITWIDTH), 0.1f, (float)((savecount + 1.0f) * UNITWIDTH)) == TRUE) 
			{
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f + xWaterOffset, 0.0f + zWaterOffset);
					glVertex3f(i * UNITWIDTH,     oldwaterlevel * UNITHEIGHT, startQuad * UNITWIDTH);
					glTexCoord2f(1.0f + xWaterOffset, 0.0f + zWaterOffset);
					glVertex3f((i+1) * UNITWIDTH, oldwaterlevel * UNITHEIGHT, startQuad * UNITWIDTH);
					glTexCoord2f(1.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
					glVertex3f((i+1) * UNITWIDTH, oldwaterlevel * UNITHEIGHT, (endQuad + 1) * UNITWIDTH);
					glTexCoord2f(0.0f + xWaterOffset, (endQuad - startQuad) + 1.0f + zWaterOffset);
					glVertex3f(i * UNITWIDTH,     oldwaterlevel * UNITHEIGHT, (endQuad + 1) * UNITWIDTH);
				glEnd();					
			}
		}
		*/
	}

	glDisable(GL_BLEND);
}



void DrawLandscape(void)
{
	int i,j,k;
	int LOD;
	int DrawEdge;

	int mapsize = 128;
	int Mdetailsize = 20;
	int Hdetailsize = 50;

	int gridX, gridZ;
	int startX, startZ;
	int endX, endZ;

	int saveLL, saveheight, savecount, savetexture;

	int waterHigh = FALSE;
	int originalWaterlevel;

	float lowPoint, pointDelta;


	float refLevel;

	//glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);


	if(detailLevel == M_LOW_DETAIL || detailLevel == M_MEDIUM_DETAIL)
	{	
		//find the grid location of the viewpoint
		gridX = (int)(XV / UNITWIDTH);
		gridZ = (int)(ZV / UNITWIDTH);

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
		gridX = (int)(XV / UNITWIDTH);
		gridZ = (int)(ZV / UNITWIDTH);

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



	
	if(detailLevel == M_LOW_DETAIL)
		LOD = 1;
	if(detailLevel == M_MEDIUM_DETAIL)
		LOD = 0; //CalcDetail(i * UNITWIDTH, thePark.landscape[i][j].TR * UNITHEIGHT, j * UNITWIDTH);
	if(detailLevel == M_HIGH_DETAIL || detailLevel == M_PROTOTYPE_DETAIL_1)
		LOD = 0;

	glColor3f(1.0f, 1.0f, 1.0f);

	bool drawUnderwater = true;

	// draw the map
	for(i=startX; i<endX; i++)
	{
		for(j=startZ; j<endZ; j++)
		{

			NumPolys++;

			k = j;
			savecount = 0;

			// --- BEGIN OPTIMIZATION CODE ---
			// first we need to check the water level
			// if the water is above any of the points, we check for variations in waterlevel
			// otherwise, we check for a change to a waterlevel above the surface
			if(1)
			/*
			if((thePark.landscape[i][j].waterlevel > thePark.landscape[i][j].BR ||
			   thePark.landscape[i][j].waterlevel > thePark.landscape[i][j].BL ||
			   thePark.landscape[i][j].waterlevel > thePark.landscape[i][j].TL ||
			   thePark.landscape[i][j].waterlevel > thePark.landscape[i][j].TR)
			   && !drawUnderwater)
			   */
			{
				originalWaterlevel = thePark.landscape[i][j].waterlevel;
				waterHigh = TRUE;
			}
			else
			{
				waterHigh = FALSE;
			}

			//check if all heights are the same	(flat surface) for the current piece
			// piece 0000
			if((thePark.landscape[i][j].BR) == (thePark.landscape[i][j].BL) && (thePark.landscape[i][j].BL == thePark.landscape[i][j].TL) && (thePark.landscape[i][j].TL == thePark.landscape[i][j].TR))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}

					// if the next piece isn't flat, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR) == (thePark.landscape[i][k+1].BL) && (thePark.landscape[i][k+1].BL == thePark.landscape[i][k+1].TL) && (thePark.landscape[i][k+1].TL == thePark.landscape[i][k+1].TR)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight)
						break;

					savecount++;
				}
			}

			//check if all heights are the same	(flat surface) for the current piece
			// piece 1001
			if((thePark.landscape[i][j].BR + 1) == (thePark.landscape[i][j].BL) && (thePark.landscape[i][j].TR + 1 == thePark.landscape[i][j].TL) && (thePark.landscape[i][j].BR == thePark.landscape[i][j].TR))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}					

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR + 1) == (thePark.landscape[i][k+1].BL) && (thePark.landscape[i][k+1].TR + 1 == thePark.landscape[i][k+1].TL) && (thePark.landscape[i][k+1].BR == thePark.landscape[i][k+1].TR)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight)
						break;

					savecount++;
				}
			}

			//check if all heights are the same	(flat surface) for the current piece
			// piece 0110
			if((thePark.landscape[i][j].BR) == (thePark.landscape[i][j].BL + 1) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].TL + 1) && (thePark.landscape[i][j].BR == thePark.landscape[i][j].TR))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}
					

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR) == (thePark.landscape[i][k+1].BL + 1) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].TL + 1) && (thePark.landscape[i][k+1].BR == thePark.landscape[i][k+1].TR)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight)
						break;

					savecount++;
				}
			}

			//check if all heights are the same	(flat surface) for the current piece
			// piece 0011
			if((thePark.landscape[i][j].BR) == (thePark.landscape[i][j].BL) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].TL) && (thePark.landscape[i][j].BR + 1 == thePark.landscape[i][j].TR))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}					

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR) == (thePark.landscape[i][k+1].BL) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].TL) && (thePark.landscape[i][k+1].BR + 1 == thePark.landscape[i][k+1].TR)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight + savecount + 1)
						break;

					savecount++;
				}
			}


			//check if all heights are the same	(flat surface) for the current piece
			// piece 1100
			if((thePark.landscape[i][j].BR) == (thePark.landscape[i][j].BL) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].TL) && (thePark.landscape[i][j].BR == thePark.landscape[i][j].TR + 1))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}
					

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR) == (thePark.landscape[i][k+1].BL) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].TL) && (thePark.landscape[i][k+1].BR == thePark.landscape[i][k+1].TR + 1)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight - savecount - 1)
						break;

					savecount++;
				}
			}


			//check if all heights are the same	(flat surface) for the current piece
			// piece 10111
			if((thePark.landscape[i][j].BR) == (thePark.landscape[i][j].BL + 1) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].BL + 2) && (thePark.landscape[i][j].TL == thePark.landscape[i][j].BL + 1))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR) == (thePark.landscape[i][k+1].BL + 1) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].BL + 2) && (thePark.landscape[i][k+1].TL == thePark.landscape[i][k+1].BL + 1)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight + savecount + 1)
						break;

					savecount++;
				}
			}


			//check if all heights are the same	(flat surface) for the current piece
			// piece 10111
			if((thePark.landscape[i][j].BL) == (thePark.landscape[i][j].BR + 1) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].BR + 1) && (thePark.landscape[i][j].TL == thePark.landscape[i][j].BR + 2))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BL) == (thePark.landscape[i][k+1].BR + 1) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].BR + 1) && (thePark.landscape[i][k+1].TL == thePark.landscape[i][k+1].BR + 2)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight + savecount + 1)
						break;

					savecount++;
				}
			}


			//check if all heights are the same	(flat surface) for the current piece
			// piece 10111
			if((thePark.landscape[i][j].BL) == (thePark.landscape[i][j].BR - 1) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].BR - 1) && (thePark.landscape[i][j].TL == thePark.landscape[i][j].BR - 2))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BL) == (thePark.landscape[i][k+1].BR - 1) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].BR - 1) && (thePark.landscape[i][k+1].TL == thePark.landscape[i][k+1].BR - 2)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight - savecount - 1)
						break;

					savecount++;
				}
			}


			//check if all heights are the same	(flat surface) for the current piece
			// piece 10111
			if((thePark.landscape[i][j].BR) == (thePark.landscape[i][j].BL - 1) && (thePark.landscape[i][j].TR == thePark.landscape[i][j].BL - 2) && (thePark.landscape[i][j].TL == thePark.landscape[i][j].BL - 1))
			{
				// get the settings
				saveLL = thePark.landscape[i][j].LLmodifierS;
				savetexture = thePark.landscape[i][j].toptexture;
				saveheight = thePark.landscape[i][j].BR;

				//loop until the end of the row
				for(k=j; k<endZ - 1;k++)
				{
					if(!drawUnderwater)
					{
						// check the waterlevel
						if(waterHigh == TRUE)
						{
							//if the waterlevel isn't the same as the original, break
							if(!(thePark.landscape[i][k+1].waterlevel == originalWaterlevel))
								break;
						}
						else
						{
							//if the waterlevel is now above the surface, break
							if((thePark.landscape[i][k+1].BR < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].BL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TL < thePark.landscape[i][k+1].waterlevel) ||
							   (thePark.landscape[i][k+1].TR < thePark.landscape[i][k+1].waterlevel))
							   break;
						}
					}

					// if the next piece isn't the same, then break out of the for loop
					if(!((thePark.landscape[i][k+1].BR) == (thePark.landscape[i][k+1].BL - 1) && (thePark.landscape[i][k+1].TR == thePark.landscape[i][k+1].BL - 2) && (thePark.landscape[i][k+1].TL == thePark.landscape[i][k+1].BL - 1)))
						break;

					// if we're here, then the next piece is flat. let's check the texture
					if((thePark.landscape[i][k+1].LLmodifierS != saveLL) || (thePark.landscape[i][k+1].toptexture != savetexture))
						break;

					// is the height of the next piece the same as the reference?
					if(thePark.landscape[i][k+1].BR != saveheight - savecount - 1)
						break;

					savecount++;
				}
			}



			// --- END OPTIMIZATION CODE ---

			float val, r, g, b;
			float baseColor[3] = {1.0f, 1.0f, 1.0f};


			/*
			// if any points are below the water level, draw the water
			//if (thePark.landscape[i][j].BR <= thePark.landscape[i][j].waterlevel || thePark.landscape[i][j+savecount].TR <= thePark.landscape[i][j].waterlevel || thePark.landscape[i][j+savecount].TL <= thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].BL <= thePark.landscape[i][j].waterlevel)
			if (thePark.landscape[i][j].BR <= thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].TR <= thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].TL <= thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].BL <= thePark.landscape[i][j].waterlevel)
			{
				if(CubeInFrustum((float)(i*UNITWIDTH), (float)((thePark.landscape[i][j].waterlevel * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH), (float)(UNITWIDTH), 0.1f, (float)((savecount + 1.0f) * UNITWIDTH)) == TRUE) 
				{
					glEnable(GL_BLEND);

					val = calcLightFactor(0.0f, 1.0f, 0.0f);
					calcColor(baseColor, val, &r, &g, &b);

					glColor4f(r, g, b, 0.5f);

					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WATER1] );

					//Draw the water surface				

					glBegin(GL_QUADS);					

						//glColor3f(1.0f, 1.0f, 1.0f);

						glNormal3d(0,1,0);
					
						//1						
						glTexCoord2f(0.0f + xWaterOffset, savecount + 1.0f + zWaterOffset);
						glVertex3d((float)(i * UNITWIDTH),     (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)(j * UNITWIDTH));
						
						//4
						glTexCoord2f(0.0f + xWaterOffset, 0.0f + zWaterOffset);
						glVertex3d((float)(i * UNITWIDTH),     (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + savecount + 1) * UNITWIDTH));
						
												
						//3
						glTexCoord2f(1.0f + xWaterOffset, 0.0f + zWaterOffset);
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + savecount + 1) * UNITWIDTH));

						//2
						glTexCoord2f(1.0f + xWaterOffset, savecount + 1.0f + zWaterOffset);
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)(j * UNITWIDTH));
						
						

					glEnd();  

					glDisable(GL_BLEND);
				}
			}
			*/


			if(thePark.landscape[i][j].LLmodifierS == 0)
			{
				switch(thePark.landscape[i][j].toptexture)
				{
				case 0x111:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_ROOFING1] );
					break;						
				case 0x110:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_JUNGLE1] );
					break;
				case 0x101:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_CHECKER1] );
					break;
				case 0x100:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_MARS1] );
					break;
				case 0x011:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAVEL1] );
					break;						
				case 0x010:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_DIRT1] );
					break;
				case 0x001:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SAND1] );
					break;
				case 0x000:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRASS1] );
					break;
				default:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRASS1] );
					break;
				}
			}
			else if(thePark.landscape[i][j].LLmodifierS == 1)
			{
				switch(thePark.landscape[i][j].toptexture)
				{
				case 0x111:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREEN1] );
					break;						
				case 0x110:
					// purple grid
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_JUNGLE1] );
					break;
				case 0x101:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_YELLOW1] );
					break;
				case 0x100:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_RED1] );
					break;
				case 0x011:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYROOF1] );
					break;						
				case 0x010:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_IRONROOF1] );
					break;
				case 0x001:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_LOGROOF1] );
					break;
				case 0x000:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_ICETOP1] );
					break;
				default:
					glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRASS1] );
					break;
				}		  
			}

			//now calculate the color of the piece of land			
			val = -1;
			

			LandscapeStructType ls;

			ls = thePark.landscape[i][j];

			glColor3f(1.0f, 1.0f, 1.0f);

			//triangle1 = BR, TR, TL
			//triangle2 = TL, BL, BR

			bbVertex in1, in2;
			bbVertex vec1, vec2;

			//BR -> TR
			in1.x = 0.0f;
			in1.y = (ls.BR - ls.TR) * UNITHEIGHT;
			in1.z = UNITWIDTH;

			//BR -> BL
			in2.x = -UNITWIDTH;
			in2.y = (ls.BR - ls.BL) * UNITHEIGHT;
			in2.z = 0.0f;

			crossProduct(in1, in2, &vec1);			
			val = calcLightFactor(vec1.x, vec1.y, vec1.z);
			calcColor(baseColor, val, &r, &g, &b);

			//if(val != -1)
				glColor3f(r, g, b);
			//else
			//	glColor3f(1.0f, 1.0f, 1.0f);
				


			

			// if any points are above the water level, draw the surface
			//if (thePark.landscape[i][j].BR > thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].TR > thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].TL > thePark.landscape[i][j].waterlevel || thePark.landscape[i][j].BL > thePark.landscape[i][j].waterlevel)
			if(1)
			{
				//now that we've got our texture/color set, we can draw the polygon
				/*
				glBegin(GL_QUADS);
				
					glNormal3d(0,1,0);
					glTexCoord2f(0.0, 1.0);	
					glVertex3d(i * UNITWIDTH,     thePark.landscape[i][j].BR * UNITHEIGHT, j * UNITWIDTH);
					glTexCoord2f(1.0, 1.0);
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i][j].BL * UNITHEIGHT, j * UNITWIDTH);
					glTexCoord2f(1.0, 0.0);
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i][j].TL * UNITHEIGHT, (j + 1) * UNITWIDTH);
					glTexCoord2f(0.0, 0.0);
					glVertex3d(i * UNITWIDTH,     thePark.landscape[i][j].TR * UNITHEIGHT, (j + 1) * UNITWIDTH);

				glEnd();
				*/
				lowPoint = getLowestPoint(i, j);
				pointDelta = getHighestPoint(i, j + savecount) - lowPoint;

				
				if(CubeInFrustum((float)(i*UNITWIDTH), (float)((lowPoint * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH), (float)UNITWIDTH, (float)(pointDelta + 0.1f), (float)((savecount + 1.0f) * UNITWIDTH)) == TRUE) 
				{
					

					glBegin(GL_TRIANGLE_STRIP);

						//glColor3f(1.0f, 1.0f, 1.0f);
					
						glTexCoord2f(1.0f, savecount + 1.0f);
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].BL * UNITHEIGHT), (float)(j * UNITWIDTH));
						glTexCoord2f(0.0f, savecount + 1.0f);
						glVertex3d((float)(i * UNITWIDTH),     (float)(thePark.landscape[i][j].BR * UNITHEIGHT), (float)(j * UNITWIDTH));
						glTexCoord2f(1.0f, 0.0f);
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+savecount].TL * UNITHEIGHT), (float)((j + savecount + 1) * UNITWIDTH));
						glTexCoord2f(0.0f, 0.0f);
						glVertex3d((float)(i * UNITWIDTH),     (float)(thePark.landscape[i][j+savecount].TR * UNITHEIGHT), (float)((j + savecount + 1) * UNITWIDTH));

					glEnd();
				}
				
			}

			

			lowPoint = getLowestPoint(i, j);
			pointDelta = getHighestPoint(i, j + savecount) - lowPoint;

			/*
			if(CubeInFrustum((float)(i*UNITWIDTH), (float)((lowPoint * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH), (float)(UNITWIDTH), (float)(pointDelta + 0.1f), (float)((savecount + 1.0f) * UNITWIDTH)) == TRUE) 
			{
				// draw the outline of the piece if any corner is above the water
				if((thePark.landscape[i][j].BL > thePark.landscape[i][j].waterlevel) ||
				   (thePark.landscape[i][j].BR > thePark.landscape[i][j].waterlevel) ||
				   (thePark.landscape[i][j+savecount].TR > thePark.landscape[i][j+savecount].waterlevel) ||
				   (thePark.landscape[i][j+savecount].TL > thePark.landscape[i][j+savecount].waterlevel))
				{
					glLineWidth(1.0f);
					glColor3f(0.0f, 0.0f, 0.0f);

					glBegin(GL_LINE_LOOP);
					glVertex3d((float)((i + 1) * UNITWIDTH),	(float)(thePark.landscape[i][j].BL * UNITHEIGHT + 0.01f),			(float)(j * UNITWIDTH));
					glVertex3d((float)(i * UNITWIDTH),		(float)(thePark.landscape[i][j].BR * UNITHEIGHT + 0.01f),			(float)(j * UNITWIDTH));
					glVertex3d((float)(i * UNITWIDTH),		(float)(thePark.landscape[i][j+savecount].TR * UNITHEIGHT + 0.01f),	(float)((j + savecount + 1) * UNITWIDTH));
					glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+savecount].TL * UNITHEIGHT + 0.01f),	(float)((j + savecount + 1) * UNITWIDTH));
					
					glEnd();
				}
			}
			*/

			j = k;
		}
	}	 



	// now draw the edges between the tiles (sideways)
	for(i=startX; i<endX; i++)
	{
		for(j=startZ; j<endZ-1; j++)
		{
			DrawEdge = -1;

			if(detailLevel == M_LOW_DETAIL)
				LOD = 1;
			if(detailLevel == M_MEDIUM_DETAIL)
				LOD = 0; //CalcDetail(i * UNITWIDTH, thePark.landscape[i][j].TR * UNITHEIGHT, j * UNITWIDTH);
			if(detailLevel == M_HIGH_DETAIL || detailLevel == M_PROTOTYPE_DETAIL_1)
				LOD = 0;


			// if the first tile is shorter than the second one,
			// we'll, use the second one to determine the surface
			// any bottom j+1 points > top j points
			if(((thePark.landscape[i][j].TR < thePark.landscape[i][j+1].BR || thePark.landscape[i][j].TL < thePark.landscape[i][j+1].BL) && thePark.landscape[i][j].TR >= thePark.landscape[i][j].waterlevel && thePark.landscape[i][j].TL >= thePark.landscape[i][j].waterlevel && thePark.landscape[i][j+1].BR >= thePark.landscape[i][j+1].waterlevel && thePark.landscape[i][j+1].BL >= thePark.landscape[i][j+1].waterlevel)
			// j and j+1 have water, and j+1 water > j water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR && thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL && thePark.landscape[i][j].waterlevel < thePark.landscape[i][j+1].waterlevel)
			// j has water and j+1 is land, and j+1 land > j water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && (thePark.landscape[i][j].waterlevel < thePark.landscape[i][j+1].BR || thePark.landscape[i][j].waterlevel < thePark.landscape[i][j+1].BL))
			// j+1 is water and j is land, and j+1 water > j land
			   || (thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR && thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j+1].TL && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j+1].TR && (thePark.landscape[i][j+1].waterlevel > thePark.landscape[i][j].TR || thePark.landscape[i][j+1].waterlevel > thePark.landscape[i][j].TL))
			   )
			{
				
				//glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);
				

				DrawEdge = 1;
				if(thePark.landscape[i][j+1].LLmodifierE == 0)
				{
					switch(thePark.landscape[i][j+1].sidetexture)
					{
					case 0x111:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_REDWALL1] );
						break;
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BLACKWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_YELLOWWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOODWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_IRONWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICKWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_DIRTWALL1] );
						break;
					default:
						break;
					}
				}
				else if(thePark.landscape[i][j+1].LLmodifierE == 1)
				{
					switch(thePark.landscape[i][j+1].sidetexture)
					{
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERBWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERAWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAYSTONEWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BROWNSTONEWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREENWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_PURPLEWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_ICEWALL1] );
						break;
					default:
						break;
					}
				}
			}
			// if the second tile is shorter than the second one,
			// we'll, use the second one to determine the surface
			// any j+1 bottom points > j top points
			else if(((thePark.landscape[i][j].TR > thePark.landscape[i][j+1].BR || thePark.landscape[i][j].TL > thePark.landscape[i][j+1].BL) && thePark.landscape[i][j].TR >= thePark.landscape[i][j].waterlevel && thePark.landscape[i][j].TL >= thePark.landscape[i][j].waterlevel && thePark.landscape[i][j+1].BR >= thePark.landscape[i][j+1].waterlevel && thePark.landscape[i][j+1].BL >= thePark.landscape[i][j+1].waterlevel)
			// j and j+1 have water, and j+1 water < j water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR && thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL && thePark.landscape[i][j].waterlevel > thePark.landscape[i][j+1].waterlevel)
			// j has water and j+1 is land, and j+1 land < j water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && (thePark.landscape[i][j].waterlevel > thePark.landscape[i][j+1].BR || thePark.landscape[i][j].waterlevel > thePark.landscape[i][j+1].BL))
			// j+1 is water and j is land, and j+1 water < j land
			   || (thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR && thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j+1].TL && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j+1].TR && (thePark.landscape[i][j+1].waterlevel < thePark.landscape[i][j].TR || thePark.landscape[i][j+1].waterlevel < thePark.landscape[i][j].TL))
			   )			
			{				
				//glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);				

				DrawEdge = 1;
				if(thePark.landscape[i][j].LLmodifierE == 0)
				{
					switch(thePark.landscape[i][j].sidetexture)
					{
					case 0x111:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_REDWALL1] );
						break;
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BLACKWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_YELLOWWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOODWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_IRONWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICKWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_DIRTWALL1] );
						break;
					default:
						break;
					}
				}
				else if(thePark.landscape[i][j].LLmodifierE == 1)
				{
					switch(thePark.landscape[i][j].sidetexture)
					{
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERBWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERAWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAYSTONEWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BROWNSTONEWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREENWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_PURPLEWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_ICEWALL1] );
						break;
					default:
						break;
					}
				}
			}

			// DrawEdge is still 0 if there isn't a height difference
			if(DrawEdge == 1)
			{
				NumPolys++;

				// start a new strip
				/*
			    glBegin(GL_QUADS);
	
					glNormal3d(0,1,0);
					//glTexCoord2f(0.0, 1.0);	
					glTexCoord2f(0.0, (thePark.landscape[i][j+1].BR / 2.0f));	
					glVertex3d(i * UNITWIDTH, thePark.landscape[i][j+1].BR * UNITHEIGHT, (j + 1) * UNITWIDTH);
					//glTexCoord2f(1.0, 1.0);
					glTexCoord2f(1.0, (thePark.landscape[i][j+1].BL / 2.0f));
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i][j+1].BL * UNITHEIGHT, (j + 1) * UNITWIDTH);
					//glTexCoord2f(1.0, 0.0);
					glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i][j].TL * UNITHEIGHT, (j + 1) * UNITWIDTH);
					//glTexCoord2f(0.0, 0.0);
					glTexCoord2f(0.0, (thePark.landscape[i][j].TR / 2.0f));
					glVertex3d(i * UNITWIDTH, thePark.landscape[i][j].TR * UNITHEIGHT, (j + 1) * UNITWIDTH);

				glEnd();
				*/			
				
				
				
				
				//if j+1 is higher than j
				if(thePark.landscape[i][j+1].BR > thePark.landscape[i][j].TR ||
					thePark.landscape[i][j+1].BL > thePark.landscape[i][j].TL)
				{								
					
					if(CubeInFrustum((float)(i*UNITWIDTH), (float)((thePark.landscape[i][j].lowest * UNITHEIGHT) - 0.1f), (float)((j+1)*UNITWIDTH),
						(float)(UNITWIDTH), (float)((thePark.landscape[i][j+1].highest - thePark.landscape[i][j].lowest) * UNITWIDTH), 0.1f) == TRUE) 
					{
						glBegin(GL_TRIANGLE_STRIP);

							glColor3f(edgeLighting[0][0], edgeLighting[0][1], edgeLighting[0][2]);

							if((thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL) &&
							   (thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR))
							{
								//printf("higher water1\n");
								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i][j+1].waterlevel / 2.0f));	
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j+1].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j+1].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+1].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));												
							}
							else
							{
								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i][j+1].BR / 2.0f));	
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j+1].BR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j+1].BL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+1].BL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));						
							}

							if((thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL) &&
							   (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR))
							{
								//printf("higher water2\n");
								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i][j].waterlevel / 2.0f));	
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));						
							}
							else
							{
								//glTexCoord2f(0.0, 0.0);
								glTexCoord2f(0.0, (thePark.landscape[i][j].TR / 2.0f));
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j].TR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 0.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].TL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));						
							}

						glEnd();			
					}
				}
				//if j is higher than j+1
				else if(thePark.landscape[i][j+1].BR < thePark.landscape[i][j].TR ||
					thePark.landscape[i][j+1].BL < thePark.landscape[i][j].TL)
				{								
					
					if(CubeInFrustum((float)(i*UNITWIDTH), (float)((thePark.landscape[i][j+1].lowest * UNITHEIGHT) - 0.1f), (float)((j+1)*UNITWIDTH),
						(float)(UNITWIDTH), (float)((thePark.landscape[i][j].highest - thePark.landscape[i][j+1].lowest) * UNITWIDTH), 0.1f) == TRUE) 
					{
						glBegin(GL_TRIANGLE_STRIP);

							glColor3f(edgeLighting[2][0], edgeLighting[2][1], edgeLighting[2][2]);

							/*
							if((thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL) &&
							   (thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR))
							{
								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i][j+1].waterlevel / 2.0f));	
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j+1].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j+1].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+1].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));												
							}
							else
							*/
							{
								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i][j+1].BR / 2.0f));	
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j+1].BR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j+1].BL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+1].BL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));						
							}

							/*
							if((thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL) &&
							   (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR))
							{
								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i][j].waterlevel / 2.0f));	
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));						
							}
							else
							*/
							{
								//glTexCoord2f(0.0, 0.0);
								glTexCoord2f(0.0, (thePark.landscape[i][j].TR / 2.0f));
								glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j].TR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(1.0, 0.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].TL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));						
							}

						glEnd();			
					}
				}

				//else
				//	printf("didn't draw edge at %d, %d\n", i, j);


				/*
				glBegin(GL_TRIANGLE_STRIP);

					if((thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BL) &&
					   (thePark.landscape[i][j+1].waterlevel >= thePark.landscape[i][j+1].BR))
					{
						//glTexCoord2f(1.0, 1.0);
						glTexCoord2f(1.0, (thePark.landscape[i][j+1].waterlevel / 2.0f));
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+1].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

						//glTexCoord2f(0.0, 1.0);	
						glTexCoord2f(0.0, (thePark.landscape[i][j+1].waterlevel / 2.0f));	
						glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j+1].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
					}
					else
					{
						//glTexCoord2f(1.0, 1.0);
						glTexCoord2f(1.0, (thePark.landscape[i][j+1].BL / 2.0f));
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j+1].BL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

						//glTexCoord2f(0.0, 1.0);	
						glTexCoord2f(0.0, (thePark.landscape[i][j+1].BR / 2.0f));	
						glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j+1].BR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
					}

					if((thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL) &&
					   (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TR))
					{
						//glTexCoord2f(1.0, 1.0);
						glTexCoord2f(1.0, (thePark.landscape[i][j].waterlevel / 2.0f));
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

						//glTexCoord2f(0.0, 1.0);	
						glTexCoord2f(0.0, (thePark.landscape[i][j].waterlevel / 2.0f));	
						glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
					}
					else
					{
						//glTexCoord2f(1.0, 0.0);
						glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
						glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].TL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

						//glTexCoord2f(0.0, 0.0);
						glTexCoord2f(0.0, (thePark.landscape[i][j].TR / 2.0f));
						glVertex3d((float)(i * UNITWIDTH), (float)(thePark.landscape[i][j].TR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
					}

				glEnd();			
				*/

				
			}
		}
	}	
	

	// now draw the edges between the tiles (the other direction)
	for(i=startX; i<endX-1; i++)
	{
		for(j=startZ; j<endZ; j++)
		{
			DrawEdge = -1;

			// if the first tile is shorter than the second one,
			// we'll, use the second one to determine the surface
			if(((thePark.landscape[i][j].TL < thePark.landscape[i+1][j].TR || thePark.landscape[i][j].BL < thePark.landscape[i+1][j].BR) && thePark.landscape[i][j].BL >= thePark.landscape[i][j].waterlevel && thePark.landscape[i][j].TL >= thePark.landscape[i][j].waterlevel && thePark.landscape[i+1][j].TR >= thePark.landscape[i+1][j].waterlevel && thePark.landscape[i+1][j].BR >= thePark.landscape[i+1][j].waterlevel)
			// i and i+1 have water, and i+1 water > i water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].BL && thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].TR && thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].BR && thePark.landscape[i][j].waterlevel < thePark.landscape[i+1][j].waterlevel)
			// i has water and i+1 is land, and i+1 land > i water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].BL && (thePark.landscape[i][j].waterlevel < thePark.landscape[i+1][j].TR || thePark.landscape[i][j].waterlevel < thePark.landscape[i+1][j].BR))
			// i+1 is water and i is land, and i+1 water > i land
			   || (thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].BR && thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].TR && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j].TL && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j].BL && (thePark.landscape[i+1][j].waterlevel > thePark.landscape[i][j].TR || thePark.landscape[i+1][j].waterlevel > thePark.landscape[i][j].BR))
			   )			
			
			//if(thePark.landscape[i][j].TR < thePark.landscape[i+1][j].BR || thePark.landscape[i][j].TL < thePark.landscape[i+1][j].BL) 
			{
				DrawEdge = 1;

				//glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);
				

				if(thePark.landscape[i+1][j].LLmodifierE == 0)
				{
					switch(thePark.landscape[i+1][j].sidetexture)
					{
					case 0x111:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_REDWALL1] );
						break;
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BLACKWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_YELLOWWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOODWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_IRONWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICKWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_DIRTWALL1] );
						break;
					default:
						break;
					}
				}
				else if(thePark.landscape[i+1][j].LLmodifierE == 1)
				{
					switch(thePark.landscape[i+1][j].sidetexture)
					{
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERBWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERAWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAYSTONEWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BROWNSTONEWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREENWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_PURPLEWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_ICEWALL1] );
						break;
					default:
						break;
					}
				}
			}
			// if the second tile is shorter than the second one,
			// we'll, use the second one to determine the surface
			else if(((thePark.landscape[i][j].TL > thePark.landscape[i+1][j].TR || thePark.landscape[i][j].BL > thePark.landscape[i+1][j].BR) && thePark.landscape[i][j].BL >= thePark.landscape[i][j].waterlevel && thePark.landscape[i][j].TL >= thePark.landscape[i][j].waterlevel && thePark.landscape[i+1][j].TR >= thePark.landscape[i+1][j].waterlevel && thePark.landscape[i+1][j].BR >= thePark.landscape[i+1][j].waterlevel)
			// i and i+1 have water, and i+1 water < i water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].BL && thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].TR && thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].BR && thePark.landscape[i][j].waterlevel > thePark.landscape[i+1][j].waterlevel)
			// i has water and i+1 is land, and i+1 land < i water
			   || (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL && thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].BL && (thePark.landscape[i][j].waterlevel > thePark.landscape[i+1][j].TR || thePark.landscape[i][j].waterlevel > thePark.landscape[i+1][j].BR))
			// i+1 is water and i is land, and i+1 water < i land
			   || (thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].BR && thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].TR && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j].TL && thePark.landscape[i][j].waterlevel <= thePark.landscape[i][j].BL && (thePark.landscape[i+1][j].waterlevel < thePark.landscape[i][j].TR || thePark.landscape[i+1][j].waterlevel < thePark.landscape[i][j].BR))
			   )			

			{
				DrawEdge = 1;

				//glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);

				if(thePark.landscape[i][j].LLmodifierE == 0)
				{
					switch(thePark.landscape[i][j].sidetexture)
					{
					case 0x111:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_REDWALL1] );
						break;
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BLACKWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_YELLOWWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREYWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_WOODWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_IRONWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BRICKWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_DIRTWALL1] );
						break;
					default:
						break;
					}
				}
				else if(thePark.landscape[i][j].LLmodifierE == 1)
				{
					switch(thePark.landscape[i][j].sidetexture)
					{
					case 0x110:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERBWALL1] );
						break;
					case 0x101:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_SKYSCRAPERAWALL1] );
						break;
					case 0x100:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GRAYSTONEWALL1] );
						break;
					case 0x011:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_BROWNSTONEWALL1] );
						break;
					case 0x010:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_GREENWALL1] );
						break;
					case 0x001:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_PURPLEWALL1] );
						break;
					case 0x000:
						glBindTexture (GL_TEXTURE_2D, texture_id[TEXTURE_ICEWALL1] );
						break;
					default:
						break;
					}
				}
			}

			// DrawEdge is still 0 if there isn't a height difference
			if(DrawEdge == 1)
			{
				NumPolys++;

				// start a new strip
			    /*
				glBegin(GL_QUADS);
	
					glNormal3d(0,1,0);
					//glTexCoord2f(0.0, 1.0);	
					glTexCoord2f(0.0, (thePark.landscape[i+1][j].BR / 2.0f));	
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i+1][j].BR * UNITHEIGHT, j * UNITWIDTH);
					//glTexCoord2f(1.0, 1.0);
					glTexCoord2f(1.0, (thePark.landscape[i+1][j].TR / 2.0f));
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i+1][j].TR * UNITHEIGHT, (j + 1) * UNITWIDTH);
					//glTexCoord2f(1.0, 0.0);
					glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i][j].TL * UNITHEIGHT, (j + 1) * UNITWIDTH);
					//glTexCoord2f(0.0, 0.0);
					glTexCoord2f(0.0, (thePark.landscape[i][j].BL / 2.0f));
					glVertex3d((i + 1) * UNITWIDTH, thePark.landscape[i][j].BL * UNITHEIGHT, j * UNITWIDTH);

				glEnd();
				*/

				//if i+1 is higher than i
				if(thePark.landscape[i+1][j].TR > thePark.landscape[i][j].TL ||
					thePark.landscape[i+1][j].BR > thePark.landscape[i][j].BL)
				{								
					if(CubeInFrustum((float)((i+1)*UNITWIDTH), (float)((thePark.landscape[i][j].lowest * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH),
						0.1f, (float)((thePark.landscape[i+1][j].highest - thePark.landscape[i][j].lowest) * UNITWIDTH), (float)(UNITWIDTH)) == TRUE) 
					{
						glBegin(GL_TRIANGLE_STRIP);
							glColor3f(edgeLighting[1][0], edgeLighting[1][1], edgeLighting[1][2]);

							/*
							if((thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].TR) &&
							   (thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].BR))
							{
								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i+1][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i+1][j].waterlevel / 2.0f));	
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].waterlevel * UNITHEIGHT), (float)(j * UNITWIDTH));
							}
							else
							*/
							{
								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i+1][j].TR / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].TR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i+1][j].BR / 2.0f));	
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].BR * UNITHEIGHT), (float)(j * UNITWIDTH));
							}
							
							/*
							if((thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL) &&
							   (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].BL))
							{
								//glTexCoord2f(1.0, 0.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
								
								//glTexCoord2f(0.0, 0.0);
								glTexCoord2f(0.0, (thePark.landscape[i][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)(j * UNITWIDTH));
							}
							else
							*/
							{
								//glTexCoord2f(1.0, 0.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].TL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
								
								//glTexCoord2f(0.0, 0.0);
								glTexCoord2f(0.0, (thePark.landscape[i][j].BL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].BL * UNITHEIGHT), (float)(j * UNITWIDTH));
							}

						glEnd();
					}
				}
				//if i is higher than i+1
				else if(thePark.landscape[i+1][j].TR < thePark.landscape[i][j].TL ||
					thePark.landscape[i+1][j].BR < thePark.landscape[i][j].BL)
				{								
					if(CubeInFrustum((float)((i+1)*UNITWIDTH), (float)((thePark.landscape[i+1][j].lowest * UNITHEIGHT) - 0.1f), (float)(j*UNITWIDTH),
						0.1f, (float)((thePark.landscape[i][j].highest - thePark.landscape[i+1][j].lowest) * UNITWIDTH), (float)(UNITWIDTH)) == TRUE) 
					{
						glBegin(GL_TRIANGLE_STRIP);
							glColor3f(edgeLighting[3][0], edgeLighting[3][1], edgeLighting[3][2]);

							if((thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].TR) &&
							   (thePark.landscape[i+1][j].waterlevel >= thePark.landscape[i+1][j].BR))
							{
								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i+1][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i+1][j].waterlevel / 2.0f));	
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].waterlevel * UNITHEIGHT), (float)(j * UNITWIDTH));
							}
							else
							{
								//glTexCoord2f(1.0, 1.0);
								glTexCoord2f(1.0, (thePark.landscape[i+1][j].TR / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].TR * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));

								//glTexCoord2f(0.0, 1.0);	
								glTexCoord2f(0.0, (thePark.landscape[i+1][j].BR / 2.0f));	
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i+1][j].BR * UNITHEIGHT), (float)(j * UNITWIDTH));
							}
							
							if((thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].TL) &&
							   (thePark.landscape[i][j].waterlevel >= thePark.landscape[i][j].BL))
							{
								//glTexCoord2f(1.0, 0.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
								
								//glTexCoord2f(0.0, 0.0);
								glTexCoord2f(0.0, (thePark.landscape[i][j].waterlevel / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].waterlevel * UNITHEIGHT), (float)(j * UNITWIDTH));
							}
							else
							{
								//glTexCoord2f(1.0, 0.0);
								glTexCoord2f(1.0, (thePark.landscape[i][j].TL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].TL * UNITHEIGHT), (float)((j + 1) * UNITWIDTH));
								
								//glTexCoord2f(0.0, 0.0);
								glTexCoord2f(0.0, (thePark.landscape[i][j].BL / 2.0f));
								glVertex3d((float)((i + 1) * UNITWIDTH), (float)(thePark.landscape[i][j].BL * UNITHEIGHT), (float)(j * UNITWIDTH));
							}

						glEnd();
					}
				}
			}
		}
	}
	
	glDisable(GL_CULL_FACE);

	drawWater();

	glDisable(GL_TEXTURE_2D);

	//glDisable(GL_BLEND);
}



float getLowestPoint(int i, int j)
{
	float lowest;

	lowest = (float)thePark.landscape[i][j].TR;

	if (thePark.landscape[i][j].TL < lowest)
		lowest = (float)thePark.landscape[i][j].TL;
	if (thePark.landscape[i][j].BL < lowest)
		lowest = (float)thePark.landscape[i][j].BL;
	if (thePark.landscape[i][j].BR < lowest)
		lowest = (float)thePark.landscape[i][j].BR;

	return lowest;
}

float getHighestPoint(int i, int j)
{
	float highest;

	highest = (float)thePark.landscape[i][j].TR;

	if (thePark.landscape[i][j].TL > highest)
		highest = (float)thePark.landscape[i][j].TL;
	if (thePark.landscape[i][j].BL > highest)
		highest = (float)thePark.landscape[i][j].BL;
	if (thePark.landscape[i][j].BR > highest)
		highest = (float)thePark.landscape[i][j].BR;

	return highest;
}