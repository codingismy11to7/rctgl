#ifndef VRTRACKS_H

#define VRTRACKS_H

extern double sinTable[360];
extern double cosTable[360];
extern double tanTable[360];

struct trackInfo {
	float startHeight;
	float endHeight;
	int startAngle;
	int endAngle;
};


void drawRoundTube(float radius, float height, float z, float color[3], trackInfo thePiece);
void drawRoundTubeCurveRight(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece);
void drawRoundTubeCurveLeft(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece);

void drawSquareTube(float radius, float height, float z, float color[3], trackInfo thePiece);
void drawSquareTubeCurveRight(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece);
void drawSquareTubeCurveLeft(float trackRadius, float tubeRadius, float height, float color[3], trackInfo thePiece);

#endif