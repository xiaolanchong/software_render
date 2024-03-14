#include "stdafx.h"
#include "SolidDodecahedron.h"

SolidDodecahedron::SolidDodecahedron(float Radius)
{
	// from glut32.dll - glut_shapes.c
//	const size_t c_VerticesInSolid = 20;
//	float dodec[c_VerticesInSolid][3];

	float alpha, beta;

	alpha = (float)sqrt(2.0 / (3.0 + sqrt(5.0)));
	beta =	float(	1.0 + sqrt(6.0 / (3.0 + sqrt(5.0)) -
					2.0 + 2.0 * sqrt(2.0 / (3.0 + sqrt(5.0)))) );
	/* *INDENT-OFF* */
	dodec[0][0] = -alpha; dodec[0][1] = 0; dodec[0][2] = beta;
	dodec[1][0] = alpha; dodec[1][1] = 0; dodec[1][2] = beta;
	dodec[2][0] = -1; dodec[2][1] = -1; dodec[2][2] = -1;
	dodec[3][0] = -1; dodec[3][1] = -1; dodec[3][2] = 1;
	dodec[4][0] = -1; dodec[4][1] = 1; dodec[4][2] = -1;
	dodec[5][0] = -1; dodec[5][1] = 1; dodec[5][2] = 1;
	dodec[6][0] = 1; dodec[6][1] = -1; dodec[6][2] = -1;
	dodec[7][0] = 1; dodec[7][1] = -1; dodec[7][2] = 1;
	dodec[8][0] = 1; dodec[8][1] = 1; dodec[8][2] = -1;
	dodec[9][0] = 1; dodec[9][1] = 1; dodec[9][2] = 1;
	dodec[10][0] = beta; dodec[10][1] = alpha; dodec[10][2] = 0;
	dodec[11][0] = beta; dodec[11][1] = -alpha; dodec[11][2] = 0;
	dodec[12][0] = -beta; dodec[12][1] = alpha; dodec[12][2] = 0;
	dodec[13][0] = -beta; dodec[13][1] = -alpha; dodec[13][2] = 0;
	dodec[14][0] = -alpha; dodec[14][1] = 0; dodec[14][2] = -beta;
	dodec[15][0] = alpha; dodec[15][1] = 0; dodec[15][2] = -beta;
	dodec[16][0] = 0; dodec[16][1] = beta; dodec[16][2] = alpha;
	dodec[17][0] = 0; dodec[17][1] = beta; dodec[17][2] = -alpha;
	dodec[18][0] = 0; dodec[18][1] = -beta; dodec[18][2] = alpha;
	dodec[19][0] = 0; dodec[19][1] = -beta; dodec[19][2] = -alpha;
	/* *INDENT-ON* */

	float sqrt_3 = (float)sqrt(3.0);
	for ( size_t i =0; i < 20; ++i )
		for ( size_t j=0; j < 3 ; ++j )
		{
			dodec[i][j] *= Radius / sqrt_3; 
		}
}

SolidDodecahedron::~SolidDodecahedron()
{
}

void SolidDodecahedron::GetFaces( Solid_t& s )
{
	s.reserve( 12 * 3);
	
	pentagon(s, 0, 1, 9, 16, 5);
	pentagon(s, 1, 0, 3, 18, 7);
	pentagon(s, 1, 7, 11, 10, 9);
	pentagon(s, 11, 7, 18, 19, 6);
	pentagon(s, 8, 17, 16, 9, 10);
	pentagon(s, 2, 14, 15, 6, 19);
	pentagon(s, 2, 13, 12, 4, 14);
	pentagon(s, 2, 19, 18, 3, 13);
	pentagon(s, 3, 0, 5, 12, 13);
	pentagon(s, 6, 15, 8, 10, 11);
	pentagon(s, 4, 17, 8, 15, 14);
	pentagon(s, 4, 12, 5, 16, 17);
}

Vector2D GenerateTexCoord( const Vector& v )
{
	float sq = sqrtf( v.x * v.x + v.z * v.z );
	float cosPhi	= v.y/ !v;
	float cosTheta	= v.x/ sq;

	float Phi = acosf( cosTheta );
	Phi += v.z < 0.0f ? float(M_PI) : 0.0f;

	return Vector2D( Phi/float(2*M_PI) , 0.5f - cosPhi/2.0f );
}

void SolidDodecahedron::pentagon(Solid_t& s,  
									size_t a, size_t b, size_t c, size_t d, size_t e)
{
	Vector v1 ( dodec[a][0], dodec[a][1], dodec[a][2] );
	Vector v2 ( dodec[b][0], dodec[b][1], dodec[b][2] );
	Vector v3 ( dodec[c][0], dodec[c][1], dodec[c][2] );
	Vector v4 ( dodec[d][0], dodec[d][1], dodec[d][2] );
	Vector v5 ( dodec[e][0], dodec[e][1], dodec[e][2] );

	Vector n0 = (v2 - v1 )^(v3 - v1);
	n0 = Normalize(n0);

	Vector2D t1 = GenerateTexCoord( v1 );
	Vector2D t2 = GenerateTexCoord( v2 );
	Vector2D t3 = GenerateTexCoord( v3 );
	Vector2D t4 = GenerateTexCoord( v4 );
	Vector2D t5 = GenerateTexCoord( v5 );

	s.push_back( Face( v1, v2, v3, n0, n0, n0, t1, t2, t3 ) );
	s.push_back( Face( v1, v3, v4, n0, n0, n0, t1, t3, t4 ) );
	s.push_back( Face( v1, v4, v5, n0, n0, n0, t1, t4, t5 ) );
}