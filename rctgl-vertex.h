#ifndef RCTGL_VERTEX_H
#define RCTGL_VERTEX_H

class RCTGLVertex
{
public:
	float x, y, z;

	RCTGLVertex();
	RCTGLVertex(float x, float y, float z);

	void copy(RCTGLVertex inVertex);
};

#endif
