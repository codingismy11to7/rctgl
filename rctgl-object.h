#include <vector>
#include "rctgl-poly.h"

typedef vector <RCTGLPoly> polyListType;

class RCTGLObject
{
public:
	void addPoly(RCTGLPoly newPoly);
	void draw() const;
	void clear();

	void translate(RCTGLVertex transVert);
	void getCenter(RCTGLVertex *center);
	void rotateAboutCenter(float degrees, bool xAxis, bool yAxis, bool zAxis);
private:
	polyListType m_polyList;

	void rotatePointAboutCenter(float degrees, bool xAxis, bool yAxis, bool zAxis, RCTGLVertex *vert);

};