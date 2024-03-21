#include "stdafx.h"
#include "SolidSphere.h"

SolidSphere::SolidSphere(  float Radius, size_t Rings, size_t Segments ) : 
	m_Radius(Radius),
	m_Rings(Rings),
	m_Segments(Segments)
{

}

IGeoSolid::Faces SolidSphere::GetFaces() const
{
	Faces s;

	for ( size_t i = 0; i < m_Rings; ++i )
	{
		float Theta1 = Deg2Rad( 180.0f * i / m_Rings );
		float Theta2 = Deg2Rad( 180.0f * (i + 1) / m_Rings );

		for ( size_t j = 0; j < m_Segments; ++j )
		{
			float Phi1 = Deg2Rad( 360.0f * j / m_Segments );
			float Phi2 = Deg2Rad( 360.0f * (j + 1) / m_Segments );


			// normalization is not required
			Vector n0 ( cosf(Phi1) * sinf(Theta1) , cosf(Theta1), sinf(Phi1) * sinf(Theta1) );
			Vector n1 ( cosf(Phi2) * sinf(Theta1) , cosf(Theta1), sinf(Phi2) * sinf(Theta1) );
			Vector n2 ( cosf(Phi1) * sinf(Theta2) , cosf(Theta2), sinf(Phi1) * sinf(Theta2) );
			Vector n3 ( cosf(Phi2) * sinf(Theta2) , cosf(Theta2), sinf(Phi2) * sinf(Theta2) );

			Vector v0 = m_Radius * n0;
			Vector v1 = m_Radius * n1;
			Vector v2 = m_Radius * n2;
			Vector v3 = m_Radius * n3;

			Vector2D t0 ( float(j)/m_Segments,  float(i)/m_Rings );
			Vector2D t1 ( float(j+1)/m_Segments,  float(i)/m_Rings );
			Vector2D t2 ( float(j)/m_Segments,  float(i+1)/m_Rings  );
			Vector2D t3 ( float(j+1)/m_Segments,  float(i+1)/m_Rings  );

			Face f1(v2, v0, v1 , 
					n2, n0, n1, 
					t2, t0, t1 );

			Face f2(v2, v1, v3 , 
					n2, n1, n3, 
					t2, t1, t3 );

			s.push_back( f1 );
			s.push_back( f2 );
		}
	}

	return s;
}
