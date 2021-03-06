#include "rctgl-frustum.h"

void RCTGLFrustum::extractFrustum(void)
{
	float   proj[16];
	float   modl[16];
	float   clip[16];
	float   t;

	/* Get the current PROJECTION matrix from OpenGL */
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	/* Combine the two matrices (multiply projection by modelview) */
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

	/* Extract the numbers for the RIGHT plane */
	m_frustum[0][0] = clip[ 3] - clip[ 0];
	m_frustum[0][1] = clip[ 7] - clip[ 4];
	m_frustum[0][2] = clip[11] - clip[ 8];
	m_frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = (float) sqrt(m_frustum[0][0] * m_frustum[0][0] + m_frustum[0][1] * m_frustum[0][1] + m_frustum[0][2] * m_frustum[0][2] );
	m_frustum[0][0] /= t;
	m_frustum[0][1] /= t;
	m_frustum[0][2] /= t;
	m_frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	m_frustum[1][0] = clip[ 3] + clip[ 0];
	m_frustum[1][1] = clip[ 7] + clip[ 4];
	m_frustum[1][2] = clip[11] + clip[ 8];
	m_frustum[1][3] = clip[15] + clip[12];

	/* Normalize the result */
	t = (float) sqrt( m_frustum[1][0] * m_frustum[1][0] + m_frustum[1][1] * m_frustum[1][1] + m_frustum[1][2] * m_frustum[1][2] );
	m_frustum[1][0] /= t;
	m_frustum[1][1] /= t;
	m_frustum[1][2] /= t;
	m_frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	m_frustum[2][0] = clip[ 3] + clip[ 1];
	m_frustum[2][1] = clip[ 7] + clip[ 5];
	m_frustum[2][2] = clip[11] + clip[ 9];
	m_frustum[2][3] = clip[15] + clip[13];

	/* Normalize the result */
	t = (float) sqrt( m_frustum[2][0] * m_frustum[2][0] + m_frustum[2][1] * m_frustum[2][1] + m_frustum[2][2] * m_frustum[2][2] );
	m_frustum[2][0] /= t;
	m_frustum[2][1] /= t;
	m_frustum[2][2] /= t;
	m_frustum[2][3] /= t;

	/* Extract the TOP plane */
	m_frustum[3][0] = clip[ 3] - clip[ 1];
	m_frustum[3][1] = clip[ 7] - clip[ 5];
	m_frustum[3][2] = clip[11] - clip[ 9];
	m_frustum[3][3] = clip[15] - clip[13];

	/* Normalize the result */
	t = (float) sqrt( m_frustum[3][0] * m_frustum[3][0] + m_frustum[3][1] * m_frustum[3][1] + m_frustum[3][2] * m_frustum[3][2] );
	m_frustum[3][0] /= t;
	m_frustum[3][1] /= t;
	m_frustum[3][2] /= t;
	m_frustum[3][3] /= t;

	/* Extract the FAR plane */
	m_frustum[4][0] = clip[ 3] - clip[ 2];
	m_frustum[4][1] = clip[ 7] - clip[ 6];
	m_frustum[4][2] = clip[11] - clip[10];
	m_frustum[4][3] = clip[15] - clip[14];

	/* Normalize the result */
	t = (float) sqrt( m_frustum[4][0] * m_frustum[4][0] + m_frustum[4][1] * m_frustum[4][1] + m_frustum[4][2] * m_frustum[4][2] );
	m_frustum[4][0] /= t;
	m_frustum[4][1] /= t;
	m_frustum[4][2] /= t;
	m_frustum[4][3] /= t;

	/* Extract the NEAR plane */
	m_frustum[5][0] = clip[ 3] + clip[ 2];
	m_frustum[5][1] = clip[ 7] + clip[ 6];
	m_frustum[5][2] = clip[11] + clip[10];
	m_frustum[5][3] = clip[15] + clip[14];

	/* Normalize the result */
	t = (float) sqrt( m_frustum[5][0] * m_frustum[5][0] + m_frustum[5][1] * m_frustum[5][1] + m_frustum[5][2] * m_frustum[5][2] );
	m_frustum[5][0] /= t;
	m_frustum[5][1] /= t;
	m_frustum[5][2] /= t;
	m_frustum[5][3] /= t;
}

bool RCTGLFrustum::isCubeInFrustum(float x, float y, float z, float dx, float dy, float dz) const
{ 
	unsigned char p;

	for( p = 0; p < 6; p++ )
	{
		if( m_frustum[p][0] * x + m_frustum[p][1]        * y + m_frustum[p][2]        * z + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * (x + dx) + m_frustum[p][1] * y + m_frustum[p][2]        * z + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * x + m_frustum[p][1]        * (y + dy) + m_frustum[p][2] * z + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * (x + dx) + m_frustum[p][1] * (y + dy) + m_frustum[p][2] * z + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * x + m_frustum[p][1]        * y + m_frustum[p][2]        * (z + dz) + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * (x + dx) + m_frustum[p][1] * y + m_frustum[p][2]        * (z + dz) + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * x + m_frustum[p][1]        * (y + dy) + m_frustum[p][2] * (z + dz) + m_frustum[p][3] > 0 )
			continue;
		if( m_frustum[p][0] * (x + dx) + m_frustum[p][1] * (y + dy) + m_frustum[p][2] * (z + dz) + m_frustum[p][3] > 0 )
			continue;
		return false;
	}

	return true;
}