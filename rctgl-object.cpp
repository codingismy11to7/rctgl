#include "rctgl-object.h"

void RCTGLObject::addPoly(RCTGLPoly newPoly)
{
	m_polyList.push_back(newPoly);
}

void RCTGLObject::draw() const
{
	for(int i=0; i<m_polyList.size(); i++)
		m_polyList[i].draw();
}

void RCTGLObject::rotatePointAboutCenter(float degrees, bool xAxis, bool yAxis, bool zAxis, RCTGLVertex *vert)
{
	float multMatrix[3][3];
	float pointMatrix[1][3];

	bool multMatrixDefined = false;

	pointMatrix[0][0] = vert->x;
	pointMatrix[0][1] = vert->y;
	pointMatrix[0][2] = vert->z;

	//rotate all verticies
	if(xAxis)
	{
		/*
		 Rotate [ P.x P.y P.z ]T about the x-axis by t radians:

		[ P.x' ]   [  1    0       0    ]   [ P.x ]
		[ P.y' ] = [  0  cos(t) -sin(t) ] * [ P.y ]
		[ P.z' ]   [  0  sin(t)  cos(t) ]   [ P.z ]
		 */
		multMatrix[0][0] = 1.0f;
		multMatrix[1][0] = 0.0f;
		multMatrix[2][0] = 0.0f;

		multMatrix[0][1] = 0.0f;
		multMatrix[1][1] = cos(degrees);
		multMatrix[2][1] = -sin(degrees);

		multMatrix[0][2] = 0.0f;
		multMatrix[1][2] = sin(degrees);
		multMatrix[2][2] = cos(degrees);

		multMatrixDefined = true;
	}
	else if(yAxis)
	{
		/*
		 Rotate [ P.x P.y P.z ]T about the y-axis by t radians:

		[ P.x' ]   [  cos(t)  0  sin(t) ]   [ P.x ]
		[ P.y' ] = [    0     1    0    ] * [ P.y ]
		[ P.z' ]   [ -sin(t)  0  cos(t) ]   [ P.z ]
		 */
		multMatrix[0][0] = cos(degrees);
		multMatrix[1][0] = 0.0f;
		multMatrix[2][0] = sin(degrees);

		multMatrix[0][1] = 0.0f;
		multMatrix[1][1] = 1.0f;
		multMatrix[2][1] = 0.0f;

		multMatrix[0][2] = -sin(degrees);
		multMatrix[1][2] = 0.0f;
		multMatrix[2][2] = cos(degrees);

		multMatrixDefined = true;
	}
	else if(zAxis)
	{
		/*
		 Rotate [ P.x P.y P.z ]T about the z-axis by t radians:

		[ P.x' ]   [  cos(t) -sin(t)  0 ]   [ P.x ]
		[ P.y' ] = [  sin(t)  cos(t)  0 ] * [ P.y ]
		[ P.z' ]   [    0       0     1 ]   [ P.z ]
		 */
		multMatrix[0][0] = cos(degrees);
		multMatrix[1][0] = -sin(degrees);
		multMatrix[2][0] = 0.0f;

		multMatrix[0][1] = sin(degrees);
		multMatrix[1][1] = cos(degrees);
		multMatrix[2][1] = 0.0f;

		multMatrix[0][2] = 0.0f;
		multMatrix[1][2] = 0.0f;
		multMatrix[2][2] = 1.0f;

		multMatrixDefined = true;		
	}

	//only continue if multMatrix was defined
	if(multMatrixDefined)
	{
		vert->x = multMatrix[0][0] * pointMatrix[0][0] +
				multMatrix[1][0] * pointMatrix[0][1] + 
				multMatrix[2][0] * pointMatrix[0][2];
		vert->y = multMatrix[0][1] * pointMatrix[0][0] +
				multMatrix[1][1] * pointMatrix[0][1] + 
				multMatrix[2][1] * pointMatrix[0][2];
		vert->z = multMatrix[0][2] * pointMatrix[0][0] +
				multMatrix[1][2] * pointMatrix[0][1] + 
				multMatrix[2][2] * pointMatrix[0][2];
	}
}

void RCTGLObject::rotateAboutCenter(float degrees, bool xAxis, bool yAxis, bool zAxis)
{
	RCTGLVertex centerVert;

	//move the coordinates to the center
	getCenter(&centerVert);
	translate(RCTGLVertex(-1.0f * centerVert.x, -1.0f * centerVert.y, -1.0f * centerVert.z));

	polyListType::iterator it1;

	//convert degrees to radians
	degrees = degrees * M_PI / 180.0f;

	//rotate all points
	for(it1 = m_polyList.begin(); it1 != m_polyList.end(); it1++)
	{		
		vertexListType::iterator it2;

		vertexListType *vertList = &(it1->m_vertexList);

		for(it2 = vertList->begin(); it2 != vertList->end(); it2++)
		{
			rotatePointAboutCenter(degrees, xAxis, yAxis, zAxis, it2);
		}
	}	

	//move the object back where it used to be
	translate(centerVert);
}

void RCTGLObject::getCenter(RCTGLVertex *center)
{
	float netX, netY, netZ;
	int numPoints;

	netX = netY = netZ = 0.0f;
	numPoints = 0;

	polyListType::iterator it1;

	for(it1 = m_polyList.begin(); it1 != m_polyList.end(); it1++)
	{		
		vertexListType::iterator it2;

		vertexListType *vertList = &(it1->m_vertexList);

		for(it2 = vertList->begin(); it2 != vertList->end(); it2++)
		{
			netX += it2->x;
			netY += it2->y;
			netZ += it2->z;

			++numPoints;
		}
	}

	center->x = netX / numPoints;
	center->y = netY / numPoints;
	center->z = netZ / numPoints;
}

void RCTGLObject::translate(RCTGLVertex transVert)
{
	polyListType::iterator it1;

	for(it1 = m_polyList.begin(); it1 != m_polyList.end(); it1++)
	{		
		vertexListType::iterator it2;

		vertexListType *vertList = &(it1->m_vertexList);

		for(it2 = vertList->begin(); it2 != vertList->end(); it2++)
		{
			it2->x += transVert.x;
			it2->y += transVert.y;
			it2->z += transVert.z;
		}
	}
}	

void RCTGLObject::clear()
{
	m_polyList.clear();	
}