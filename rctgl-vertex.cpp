#include "rctgl-vertex.h"

RCTGLVertex::RCTGLVertex()
{
	 x = y = z = 0.0f;
}

RCTGLVertex::RCTGLVertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void RCTGLVertex::copy(RCTGLVertex inVertex)
{
	x = inVertex.x;
	y = inVertex.y;
	z = inVertex.z;
}