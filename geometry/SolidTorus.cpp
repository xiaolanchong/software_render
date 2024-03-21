#include "stdafx.h"
#include "SolidTorus.h"

SolidTorus::SolidTorus(float innerRadius, float outerRadius, size_t sides, size_t rings):
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius),
	m_sides(sides),
	m_rings(rings)
{
	ASSERT( innerRadius >= outerRadius );
	ASSERT( sides > 2 );
	ASSERT( rings > 2 );
}

IGeoSolid::Faces SolidTorus::GetFaces() const
{
	Faces s;
	float ringDelta, sideDelta;

	ringDelta = Deg2Rad( 360.0f/ m_rings);
	sideDelta = Deg2Rad( 360.0f/ m_sides);

	for ( size_t i =0; i < m_rings; ++i )
	{
		float Theta1 = (i + 0) * ringDelta;
		float Theta2 = (i + 1) * ringDelta;

		float cosTheta1 = cosf(Theta1);
		float sinTheta1 = sinf(Theta1);

		float cosTheta2 = cosf(Theta2);
		float sinTheta2 = sinf(Theta2);



		for ( size_t j =0; j < m_sides; ++j )
		{
			float Phi1 = (j + 0) * sideDelta;
			float Phi2 = (j + 1) * sideDelta; 

			float cosPhi1 = cosf(Phi1);
			float sinPhi1 = sinf(Phi1);

			float cosPhi2 = cosf(Phi2);
			float sinPhi2 = sinf(Phi2);

			float Dist1 = m_innerRadius + m_outerRadius * cosPhi1;
			float Dist2 = m_innerRadius + m_outerRadius * cosPhi2;

			Vector v1( Dist1 * cosTheta1, m_outerRadius * sinPhi1, Dist1 * sinTheta1);
			Vector v2( Dist1 * cosTheta2, m_outerRadius * sinPhi1, Dist1 * sinTheta2 );
			Vector v3( Dist2 * cosTheta1, m_outerRadius * sinPhi2, Dist2 * sinTheta1 );
			Vector v4( Dist2 * cosTheta2, m_outerRadius * sinPhi2, Dist2 * sinTheta2 );

			Vector n1( cosTheta1 * cosPhi1, sinPhi1, sinTheta1 * cosPhi1 );
			Vector n2( cosTheta2 * cosPhi1, sinPhi1, sinTheta2 * cosPhi1 );
			Vector n3( cosTheta1 * cosPhi2, sinPhi2, sinTheta1 * cosPhi2 );
			Vector n4( cosTheta2 * cosPhi2, sinPhi2, sinTheta2 * cosPhi2 );

			Vector2D t1 ( float(i)/m_rings,		float(j)/m_sides );
			Vector2D t2 ( float(i+1)/m_rings,	float(j)/m_sides  );
			Vector2D t3 ( float(i)/m_rings,		float(j+1)/m_sides );
			Vector2D t4 ( float(i+1)/m_rings,	float(j+1)/m_sides  );

			Face f1(v1, v3, v4, n1, n3, n4, t1, t3, t4 );
			Face f2(v4, v2, v1, n4, n2, n1, t4, t2, t1 );
			s.push_back( f1 );
			s.push_back( f2 );
		}
	}

	return s;
}
