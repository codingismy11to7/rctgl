#include "vr3d.h"
#include "vr-tracks.h"
#include "bbVertex.h"

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];

extern void crossProduct(bbVertex v1, bbVertex v2, bbVertex *out);

float quickCos(int degrees)
{	
	/*
	if(degrees >= 360)
		return quickCos(degrees - 360);
	else if(degrees < 0)
		return quickCos(degrees + 360);
	else	
	*/
		return cosTable[degrees];
}

float quickSin(int degrees)
{	
	/*
	if(degrees >= 360)
		return quickSin(degrees - 360);
	else if(degrees < 0)
		return quickSin(degrees + 360);
	else	
	*/
		return sinTable[degrees];
}

float quickTan(int degrees)
{	
	/*
	if(degrees >= 360)
		return quickTan(degrees - 360);
	else if(degrees < 0)
		return quickTan(degrees + 360);
	else	
	*/
		return tanTable[degrees];
}


void drawRoundTube(float radius, float height, float z, float color[3], trackInfo thePiece)
{
	if(thePiece.startAngle < 0)
		thePiece.startAngle += 360;
	if(thePiece.endAngle < 0)
		thePiece.endAngle += 360;

	float val1, val2, val3, val4;
	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r4, g4, b4;

	float baseColor[3] = {color[0], color[1], color[2]};

	//top start
	val1 = calcLightFactor(-quickSin(thePiece.startAngle), quickCos(thePiece.startAngle), 0.0f);
	//top end
	val2 = calcLightFactor(-quickSin(thePiece.endAngle),   quickCos(thePiece.endAngle),   0.0f);
	//outside edge
	val3 = calcLightFactor(0.0f, 0.0f, 1.0f);

	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);
	calcColor(baseColor, val3, &r3, &g3, &b3);


	glShadeModel(GL_SMOOTH);
	
	//draw the top support beam
	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex3d(0.0f,		2.0f * radius + height + thePiece.startHeight, z);
		glColor3f(r3, g3, b3);
		glVertex3d(0.0f,		radius + height + thePiece.startHeight,		z + radius);
		glVertex3d(UNITWIDTH,	radius + height + thePiece.endHeight,		z + radius);
		glColor3f(r2, g2, b2);
		glVertex3d(UNITWIDTH,	2.0f * radius + height + thePiece.endHeight, z);
	glEnd();

	//top start
	val1 = calcLightFactor(quickSin(thePiece.startAngle), -quickCos(thePiece.startAngle), 0.0f);
	//top end
	val2 = calcLightFactor(quickSin(thePiece.endAngle),   -quickCos(thePiece.endAngle),   0.0f);
	
	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);
	

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex3d(0.0f,		height + thePiece.startHeight, z);
		glColor3f(r3, g3, b3);
		glVertex3d(0.0f,		radius + height + thePiece.startHeight,		z + radius);
		glVertex3d(UNITWIDTH,	radius + height + thePiece.endHeight,		z + radius);
		glColor3f(r2, g2, b2);
		glVertex3d(UNITWIDTH,	height + thePiece.endHeight, z);
	glEnd();

	//outside edge
	val3 = calcLightFactor(0.0f, 0.0f, -1.0f);
	calcColor(baseColor, val3, &r3, &g3, &b3);

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex3d(0.0f,		height + thePiece.startHeight, z);
		glColor3f(r3, g3, b3);
		glVertex3d(0.0f,		radius + height + thePiece.startHeight,		z - radius);
		glVertex3d(UNITWIDTH,	radius + height + thePiece.endHeight,		z - radius);
		glColor3f(r2, g2, b2);
		glVertex3d(UNITWIDTH,	height + thePiece.endHeight, z);
	glEnd();

	//top start
	val1 = calcLightFactor(-quickSin(thePiece.startAngle), quickCos(thePiece.startAngle), 0.0f);
	//top end
	val2 = calcLightFactor(-quickSin(thePiece.endAngle),   quickCos(thePiece.endAngle),   0.0f);
	
	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);

	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex3d(0.0f,		2.0f * radius + height + thePiece.startHeight, z);
		glColor3f(r3, g3, b3);
		glVertex3d(0.0f,		radius + height + thePiece.startHeight,		z - radius);
		glVertex3d(UNITWIDTH,	radius + height + thePiece.endHeight,		z - radius);
		glColor3f(r2, g2, b2);
		glVertex3d(UNITWIDTH,	2.0f * radius + height + thePiece.endHeight, z);
	glEnd();	
}


void drawSquareTube(float radius, float height, float z, float color[3], trackInfo thePiece)
{
	if(thePiece.startAngle < 0)
		thePiece.startAngle += 360;
	if(thePiece.endAngle < 0)
		thePiece.endAngle += 360;

	float val1, val2, val3, val4;
	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r4, g4, b4;

	float baseColor[3] = {color[0], color[1], color[2]};

	//top start
	val1 = calcLightFactor(-quickSin(thePiece.startAngle), quickCos(thePiece.startAngle), 0.0f);
	//top end
	val2 = calcLightFactor(-quickSin(thePiece.endAngle),   quickCos(thePiece.endAngle),   0.0f);
	//outside edges
	val3 = calcLightFactor(0.0f, 0.0f, 1.0f);
	val4 = calcLightFactor(0.0f, 0.0f, -1.0f);

	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);
	calcColor(baseColor, val3, &r3, &g3, &b3);
	calcColor(baseColor, val4, &r4, &g4, &b4);

	glShadeModel(GL_SMOOTH);
	
	//draw the top support beam
	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex3d(0.0f,		2.0f * radius + height + thePiece.startHeight,		z - radius);		
		glVertex3d(0.0f,		2.0f * radius + height + thePiece.startHeight,		z + radius);
		glColor3f(r2, g2, b2);
		glVertex3d(UNITWIDTH,	2.0f * radius + height + thePiece.endHeight,		z + radius);		
		glVertex3d(UNITWIDTH,	2.0f * radius + height + thePiece.endHeight,		z - radius);
	glEnd();

	//top start
	val1 = calcLightFactor(quickSin(thePiece.startAngle), -quickCos(thePiece.startAngle), 0.0f);
	//top end
	val2 = calcLightFactor(quickSin(thePiece.endAngle),   -quickCos(thePiece.endAngle),   0.0f);
	
	calcColor(baseColor, val1, &r1, &g1, &b1);
	calcColor(baseColor, val2, &r2, &g2, &b2);
	

	//draw the bottom support beam
	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex3d(0.0f,		height + thePiece.startHeight,		z - radius);		
		glVertex3d(0.0f,		height + thePiece.startHeight,		z + radius);
		glColor3f(r2, g2, b2);
		glVertex3d(UNITWIDTH,	height + thePiece.endHeight,		z + radius);		
		glVertex3d(UNITWIDTH,	height + thePiece.endHeight,		z - radius);
	glEnd();

	//outside edge
	val3 = calcLightFactor(0.0f, 0.0f, -1.0f);
	calcColor(baseColor, val3, &r3, &g3, &b3);

	glBegin(GL_QUADS);
		glColor3f(r3, g3, b3);
		glVertex3d(0.0f,		height + thePiece.startHeight,					z - radius);
		glVertex3d(0.0f,		2.0f * radius + height + thePiece.startHeight,	z - radius);
		glVertex3d(UNITWIDTH,	2.0f * radius + height + thePiece.endHeight,	z - radius);
		glVertex3d(UNITWIDTH,	height + thePiece.endHeight,					z - radius);
	glEnd();

	
	//outside edge
	val3 = calcLightFactor(0.0f, 0.0f, 1.0f);
	calcColor(baseColor, val3, &r3, &g3, &b3);

	glBegin(GL_QUADS);
		glColor3f(r3, g3, b3);
		glVertex3d(0.0f,		height + thePiece.startHeight,					z + radius);
		glVertex3d(0.0f,		2.0f * radius + height + thePiece.startHeight,	z + radius);
		glVertex3d(UNITWIDTH,	2.0f * radius + height + thePiece.endHeight,	z + radius);
		glVertex3d(UNITWIDTH,	height + thePiece.endHeight,					z + radius);
	glEnd();	
}



void drawRoundTubeCurveRight(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2, radius3;
	int degrees[5];
	int i;

	float val1, val2, val3, val3b, val4, val4b;
	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r3b, g3b, b3b;
	float r4, g4, b4;
	float r4b, g4b, b4b;

	float baseColor[3] = {color[0], color[1], color[2]};

	if(thePiece.endAngle < 0)
		thePiece.endAngle += 360;
	if(thePiece.startAngle < 0)
		thePiece.startAngle += 360;


	//float halfRailDiameter;

	//halfRailDiameter = STEELCORKSCREW_RAILDIAMETER / 2.0f;	

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 180;	//180-0
	degrees[1] = 157;//180-23
	degrees[2] = 135;//180-45
	degrees[3] = 112;//180-68
	degrees[4] = 90;//180-90

	int angleDeg[5];
	angleDeg[0] = 0;
	angleDeg[1] = 23;
	angleDeg[2] = 45;
	angleDeg[3] = 68;
	angleDeg[4] = 90;

	//draw the beam
	radius1 = trackRadius + tubeRadius;
	radius2 = trackRadius - tubeRadius;
	radius3 = trackRadius;

	//glColor3f(color[0], color[1], color[2]);
	glColor3f(1.0f, 0.0f, 0.0f);

	val1 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);

	val2 = calcLightFactor(0.0f, -1.0f, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);

	float heightStep = (thePiece.startHeight - thePiece.endHeight) / 4.0f;
	float curHeight = thePiece.startHeight;


	glShadeModel(GL_SMOOTH);

	float curTopVal, nextTopVal;
	float curBotVal, nextBotVal;

	float curTR, curTG, curTB;
	float curBR, curBG, curBB;

	float nextTR, nextTG, nextTB;
	float nextBR, nextBG, nextBB;

	int startDeg = 91;

	float multFactor;
	multFactor = -quickSin(thePiece.startAngle);
	
	for(i=0; i<4; i++)
	{
		curTopVal = calcLightFactor(multFactor * quickSin(angleDeg[i]), quickCos(thePiece.startAngle), multFactor * quickCos(angleDeg[i]));
		nextTopVal = calcLightFactor(multFactor * quickSin(angleDeg[i+1]), quickCos(thePiece.startAngle), multFactor * quickCos(angleDeg[i+1]));

		curBotVal = calcLightFactor(multFactor * -quickSin(angleDeg[i]), -quickCos(thePiece.startAngle), multFactor * -quickCos(angleDeg[i]));
		nextBotVal = calcLightFactor(multFactor * -quickSin(angleDeg[i+1]), -quickCos(thePiece.startAngle), multFactor * -quickCos(angleDeg[i+1]));
		
		calcColor(baseColor, curTopVal, &curTR, &curTG, &curTB);
		calcColor(baseColor, curBotVal, &curBR, &curBG, &curBB);
		calcColor(baseColor, nextTopVal, &nextTR, &nextTG, &nextTB);
		calcColor(baseColor, nextBotVal, &nextBR, &nextBG, &nextBB);

		//curBR = nextBR;
		//curBB = nextBB;
		//curBG = nextBG;
				
		//series1 = top
		//series2 = bottom
		//series3 = left
		//series4 = right
		//precalc the left and right light values
		val3 = calcLightFactor(-quickCos(degrees[i]), 0.0f, -quickSin(degrees[i]));
		calcColor(baseColor, val3, &r3, &g3, &b3);

		val3b = calcLightFactor(-quickCos(degrees[i+1]), 0.0f, -quickSin(degrees[i+1]));
		calcColor(baseColor, val3b, &r3b, &g3b, &b3b);

		val4 = calcLightFactor(quickCos(degrees[i]), 0.0f, quickSin(degrees[i]));
		calcColor(baseColor, val4, &r4, &g4, &b4);

		val4b = calcLightFactor(quickCos(degrees[i+1]), 0.0f, quickSin(degrees[i+1]));
		calcColor(baseColor, val4b, &r4b, &g4b, &b4b);

		//take care of the top
		glBegin(GL_QUADS);
			glColor3f(curTR, curTG, curTB);
			glVertex3d(-radius3 * quickCos(degrees[i]),	  curHeight + height + (2 * tubeRadius), -radius3 * quickSin(degrees[i]));
			glColor3f(r3, g3, b3);
			glVertex3d(-radius1 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       -radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(-radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       -radius1 * quickSin(degrees[i+1]));
			glColor3f(nextTR, nextTG, nextTB);
			glVertex3d(-radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), -radius3 * quickSin(degrees[i+1]));
		glEnd();		

		glBegin(GL_QUADS);
			glColor3f(curTR, curTG, curTB);
			glVertex3d(-radius3 * quickCos(degrees[i]),	  curHeight + height + (2 * tubeRadius), -radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(-radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       -radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(-radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       -radius2 * quickSin(degrees[i+1]));
			glColor3f(nextTR, nextTG, nextTB);
			glVertex3d(-radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), -radius3 * quickSin(degrees[i+1]));
		glEnd();

		//now do the bottom
		glBegin(GL_QUADS);
			glColor3f(curBR, curBG, curBB);
			glVertex3d(-radius3 * quickCos(degrees[i]),	  curHeight + height,                -radius3 * quickSin(degrees[i]));
			glColor3f(r3, g3, b3);
			glVertex3d(-radius1 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   -radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(-radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   -radius1 * quickSin(degrees[i+1]));
			glColor3f(nextBR, nextBG, nextBB);
			glVertex3d(-radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                -radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(curBR, curBG, curBB);
			glVertex3d(-radius3 * quickCos(degrees[i]),	  curHeight + height,                -radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(-radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   -radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(-radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   -radius2 * quickSin(degrees[i+1]));
			glColor3f(nextBR, nextBG, nextBB);
			glVertex3d(-radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                -radius3 * quickSin(degrees[i+1]));
		glEnd();

		curHeight += heightStep;

		//startDeg += 23;
	}

	glShadeModel(GL_FLAT);
}


void drawSquareTubeCurveRight(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2, radius3;
	int degrees[5];
	int i;

	float val1, val2, val3, val3b, val4, val4b;
	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r3b, g3b, b3b;
	float r4, g4, b4;
	float r4b, g4b, b4b;	

	float baseColor[3] = {color[0], color[1], color[2]};

	while(thePiece.startAngle <0 || thePiece.endAngle >= 360)
	{
		if(thePiece.startAngle < 0)
			thePiece.startAngle += 360;
		else if(thePiece.startAngle >= 360)
			thePiece.startAngle <= 360;
	}

	bbVertex inside1, inside2, outside1, outside2;
	bbVertex input1, input2, output;

	//float halfRailDiameter;

	//halfRailDiameter = STEELCORKSCREW_RAILDIAMETER / 2.0f;	

	radius = 2.5f * UNITWIDTH;

	degrees[0] = 180;	//180-0
	degrees[1] = 157;//180-23
	degrees[2] = 135;//180-45
	degrees[3] = 112;//180-68
	degrees[4] = 90;//180-90

	int angleDeg[5];
	angleDeg[0] = 0;
	angleDeg[1] = 23;
	angleDeg[2] = 45;
	angleDeg[3] = 68;
	angleDeg[4] = 90;

	//draw the beam
	radius1 = trackRadius + tubeRadius;
	radius2 = trackRadius - tubeRadius;
	radius3 = trackRadius;

	//glColor3f(color[0], color[1], color[2]);
	glColor3f(1.0f, 0.0f, 0.0f);

	val1 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);

	val2 = calcLightFactor(0.0f, -1.0f, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);

	float heightStep = (thePiece.startHeight - thePiece.endHeight) / 4.0f;
	float curHeight = thePiece.startHeight;


	glShadeModel(GL_SMOOTH);

	float multFactor;
	multFactor = -quickSin(thePiece.startAngle);
	
	for(i=0; i<4; i++)
	{
		//series1 = top
		//series2 = bottom
		//series3 = left
		//series4 = right
		//precalc the left and right light values
		val3 = calcLightFactor(-quickCos(degrees[i]), 0.0f, -quickSin(degrees[i]));
		calcColor(baseColor, val3, &r3, &g3, &b3);

		val3b = calcLightFactor(-quickCos(degrees[i+1]), 0.0f, -quickSin(degrees[i+1]));
		calcColor(baseColor, val3b, &r3b, &g3b, &b3b);

		val4 = calcLightFactor(quickCos(degrees[i]), 0.0f, quickSin(degrees[i]));
		calcColor(baseColor, val4, &r4, &g4, &b4);

		val4b = calcLightFactor(quickCos(degrees[i+1]), 0.0f, quickSin(degrees[i+1]));
		calcColor(baseColor, val4b, &r4b, &g4b, &b4b);

		glBegin(GL_QUADS);
			glColor3f(r3, g3, b3);
			glVertex3d(-radius1 * quickCos(degrees[i]),	  curHeight + height + (2 * tubeRadius),				-radius1 * quickSin(degrees[i]));
			glVertex3d(-radius1 * quickCos(degrees[i]),   curHeight + height,									-radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(-radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height,						-radius1 * quickSin(degrees[i+1]));
			glVertex3d(-radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius),	-radius1 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r4, g4, b4);
			glVertex3d(-radius2 * quickCos(degrees[i]),	  curHeight + height + (2 * tubeRadius),				-radius2 * quickSin(degrees[i]));
			glVertex3d(-radius2 * quickCos(degrees[i]),   curHeight + height,									-radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(-radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height,						-radius2 * quickSin(degrees[i+1]));
			glVertex3d(-radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius),	-radius2 * quickSin(degrees[i+1]));
		glEnd();

		//top part of rail
		inside1.x = -radius1 * quickCos(degrees[i]);
		inside1.y = curHeight + height + (2 * tubeRadius);
		inside1.z = -radius1 * quickSin(degrees[i]);

		inside2.x = -radius1 * quickCos(degrees[i+1]);
		inside2.y = curHeight + heightStep + height + (2 * tubeRadius);
		inside2.z = -radius1 * quickSin(degrees[i+1]);

		outside1.x = -radius2 * quickCos(degrees[i]);
		outside1.y = curHeight + height + (2 * tubeRadius);
		outside1.z = -radius2 * quickSin(degrees[i]);

		outside2.x = -radius2 * quickCos(degrees[i+1]);
		outside2.y = curHeight + heightStep + height + (2 * tubeRadius);
		outside2.z = -radius2 * quickSin(degrees[i+1]);
		
		glBegin(GL_QUADS);
			val4 = calcLightFactor(multFactor * quickSin(angleDeg[i]), quickCos(thePiece.startAngle), multFactor * quickCos(angleDeg[i]));
			calcColor(baseColor, val4, &r4, &g4, &b4);
			
			val4b = calcLightFactor(multFactor * quickSin(angleDeg[i+1]), quickCos(thePiece.startAngle), multFactor * quickCos(angleDeg[i+1]));			
			calcColor(baseColor, val4b, &r4b, &g4b, &b4b);			
			
			glColor3f(r4, g4, b4);			
			glVertex3d(inside1.x, inside1.y, inside1.z);
			glVertex3d(outside1.x, outside1.y, outside1.z);

			glColor3f(r4b, g4b, b4b);
			glVertex3d(outside2.x, outside2.y, outside2.z);
			glVertex3d(inside2.x, inside2.y, inside2.z);
		glEnd();

		inside1.y = curHeight + height;
		inside2.y = curHeight + heightStep + height;
		outside1.y = curHeight + height;
		outside2.y = curHeight + heightStep + height;

		glBegin(GL_QUADS);			
			val4 = calcLightFactor(multFactor * -quickSin(angleDeg[i]), -quickCos(thePiece.startAngle), multFactor * -quickCos(angleDeg[i]));
			calcColor(baseColor, val4, &r4, &g4, &b4);
			
			val4b = calcLightFactor(multFactor * -quickSin(angleDeg[i+1]), -quickCos(thePiece.startAngle), multFactor * -quickCos(angleDeg[i+1]));
			calcColor(baseColor, val4b, &r4b, &g4b, &b4b);			

			glColor3f(r4, g4, b4);
			glVertex3d(inside1.x, inside1.y, inside1.z);
			glVertex3d(outside1.x, outside1.y, outside1.z);

			glColor3f(r4b, g4b, b4b);
			glVertex3d(outside2.x, outside2.y, outside2.z);
			glVertex3d(inside2.x, inside2.y, inside2.z);
		glEnd();

		/*

		glBegin(GL_QUADS);
			glColor3f(r1, g1, b1);
			glVertex3d(-radius3 * quickCos(degrees[i]),	  curHeight + height + (2 * tubeRadius), -radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(-radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       -radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(-radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       -radius2 * quickSin(degrees[i+1]));
			glColor3f(r1, g1, b1);
			glVertex3d(-radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), -radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r2, g2, b2);
			glVertex3d(-radius3 * quickCos(degrees[i]),	  curHeight + height,                -radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(-radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   -radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(-radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   -radius2 * quickSin(degrees[i+1]));
			glColor3f(r2, g2, b2);
			glVertex3d(-radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                -radius3 * quickSin(degrees[i+1]));
		glEnd();
		*/

		curHeight += heightStep;
	}

	glShadeModel(GL_FLAT);
}




void drawRoundTubeCurveLeft(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2, radius3;
	int degrees[5];
	int i;

	float val1, val2, val3, val3b, val4, val4b;
	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r3b, g3b, b3b;
	float r4, g4, b4;
	float r4b, g4b, b4b;
	

	float baseColor[3] = {color[0], color[1], color[2]};

	float halfRailDiameter;

	//halfRailDiameter = STEELCORKSCREW_RAILDIAMETER / 2.0f;	

	//radius = 2.5f * UNITWIDTH;

	degrees[0] = 0;	//180-0
	degrees[1] = 23;//180-23
	degrees[2] = 45;//180-45
	degrees[3] = 68;//180-68
	degrees[4] = 90;//180-90

	//draw the beam
	radius1 = trackRadius + tubeRadius;
	radius2 = trackRadius - tubeRadius;
	radius3 = trackRadius;

	//glColor3f(color[0], color[1], color[2]);
	glColor3f(1.0f, 0.0f, 0.0f);

	val1 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);

	val2 = calcLightFactor(0.0f, -1.0f, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);


	glShadeModel(GL_SMOOTH);

	float heightStep = (thePiece.startHeight - thePiece.endHeight) / 4.0f;
	float curHeight = thePiece.startHeight;
	
	for(i=0; i<4; i++)
	{
		//series1 = top
		//series2 = bottom
		//series3 = left
		//series4 = right
		//precalc the left and right light values
		val3 = calcLightFactor(quickCos(degrees[i]), 0.0f, quickSin(degrees[i]));
		calcColor(baseColor, val3, &r3, &g3, &b3);

		val3b = calcLightFactor(quickCos(degrees[i+1]), 0.0f, quickSin(degrees[i+1]));
		calcColor(baseColor, val3b, &r3b, &g3b, &b3b);

		val4 = calcLightFactor(-quickCos(degrees[i]), 0.0f, -quickSin(degrees[i]));
		calcColor(baseColor, val4, &r4, &g4, &b4);

		val4b = calcLightFactor(-quickCos(degrees[i+1]), 0.0f, -quickSin(degrees[i+1]));
		calcColor(baseColor, val4b, &r4b, &g4b, &b4b);

		glBegin(GL_QUADS);
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height + (2 * tubeRadius), radius3 * quickSin(degrees[i]));
			glColor3f(r3, g3, b3);
			glVertex3d(radius1 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       radius1 * quickSin(degrees[i+1]));
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height,                radius3 * quickSin(degrees[i]));
			glColor3f(r3, g3, b3);
			glVertex3d(radius1 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   radius1 * quickSin(degrees[i+1]));
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height + (2 * tubeRadius), radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       radius2 * quickSin(degrees[i+1]));
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height,                radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   radius2 * quickSin(degrees[i+1]));
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                radius3 * quickSin(degrees[i+1]));
		glEnd();

		curHeight += heightStep;
	}

	glShadeModel(GL_FLAT);
}


void drawSquareTubeCurveLeft(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece)
{
	double radius;
	double radius1a, radius1b, radius2a, radius2b;
	double radius1, radius2, radius3;
	int degrees[5];
	int i;

	float val1, val2, val3, val3b, val4, val4b;
	float r1, g1, b1;
	float r2, g2, b2;
	float r3, g3, b3;
	float r3b, g3b, b3b;
	float r4, g4, b4;
	float r4b, g4b, b4b;
	

	float baseColor[3] = {color[0], color[1], color[2]};

	float halfRailDiameter;

	//halfRailDiameter = STEELCORKSCREW_RAILDIAMETER / 2.0f;	

	//radius = 2.5f * UNITWIDTH;

	degrees[0] = 0;	//180-0
	degrees[1] = 23;//180-23
	degrees[2] = 45;//180-45
	degrees[3] = 68;//180-68
	degrees[4] = 90;//180-90

	//draw the beam
	radius1 = trackRadius + tubeRadius;
	radius2 = trackRadius - tubeRadius;
	radius3 = trackRadius;

	//glColor3f(color[0], color[1], color[2]);
	glColor3f(1.0f, 0.0f, 0.0f);

	val1 = calcLightFactor(0.0f, 1.0f, 0.0f);
	calcColor(baseColor, val1, &r1, &g1, &b1);

	val2 = calcLightFactor(0.0f, -1.0f, 0.0f);
	calcColor(baseColor, val2, &r2, &g2, &b2);


	glShadeModel(GL_SMOOTH);

	float heightStep = (thePiece.startHeight - thePiece.endHeight) / 4.0f;
	float curHeight = thePiece.startHeight;
	
	for(i=0; i<4; i++)
	{
		//series1 = top
		//series2 = bottom
		//series3 = left
		//series4 = right
		//precalc the left and right light values
		val3 = calcLightFactor(quickCos(degrees[i]), 0.0f, quickSin(degrees[i]));
		calcColor(baseColor, val3, &r3, &g3, &b3);

		val3b = calcLightFactor(quickCos(degrees[i+1]), 0.0f, quickSin(degrees[i+1]));
		calcColor(baseColor, val3b, &r3b, &g3b, &b3b);

		val4 = calcLightFactor(-quickCos(degrees[i]), 0.0f, -quickSin(degrees[i]));
		calcColor(baseColor, val4, &r4, &g4, &b4);

		val4b = calcLightFactor(-quickCos(degrees[i+1]), 0.0f, -quickSin(degrees[i+1]));
		calcColor(baseColor, val4b, &r4b, &g4b, &b4b);

		glBegin(GL_QUADS);
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height + (2 * tubeRadius), radius3 * quickSin(degrees[i]));
			glColor3f(r3, g3, b3);
			glVertex3d(radius1 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       radius1 * quickSin(degrees[i+1]));
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height,                radius3 * quickSin(degrees[i]));
			glColor3f(r3, g3, b3);
			glVertex3d(radius1 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   radius1 * quickSin(degrees[i]));
			glColor3f(r3b, g3b, b3b);
			glVertex3d(radius1 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   radius1 * quickSin(degrees[i+1]));
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height + (2 * tubeRadius), radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,       radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,       radius2 * quickSin(degrees[i+1]));
			glColor3f(r1, g1, b1);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height + (2 * tubeRadius), radius3 * quickSin(degrees[i+1]));
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i]),	 curHeight + height,                radius3 * quickSin(degrees[i]));
			glColor3f(r4, g4, b4);
			glVertex3d(radius2 * quickCos(degrees[i]),   curHeight + height + tubeRadius,   radius2 * quickSin(degrees[i]));
			glColor3f(r4b, g4b, b4b);
			glVertex3d(radius2 * quickCos(degrees[i+1]), curHeight + heightStep + height + tubeRadius,   radius2 * quickSin(degrees[i+1]));
			glColor3f(r2, g2, b2);
			glVertex3d(radius3 * quickCos(degrees[i+1]), curHeight + heightStep + height,                radius3 * quickSin(degrees[i+1]));
		glEnd();

		curHeight += heightStep;
	}

	glShadeModel(GL_FLAT);
}
