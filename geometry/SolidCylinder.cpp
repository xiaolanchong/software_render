#include "stdafx.h"
#include "SolidCylinder.h"

SolidCylinder::SolidCylinder(float Radius, float Height, size_t nSegmentNumber):
	m_Radius(Radius), m_Height(Height), m_nSegmentNumber(nSegmentNumber)
{
	ASSERT( nSegmentNumber );
	ASSERT( Radius > 0.0f );
	ASSERT( Height > 0.0f );
}

SolidCylinder::~SolidCylinder()
{
}

void SolidCylinder::GetFaces( Solid_t& s )
{
	s.clear();

	// texture bounds
	const float c_TopCircle		= m_Radius/( 2 * m_Radius + m_Height );
	const float c_BottomCircle	= (m_Radius + m_Height)/( 2 * m_Radius + m_Height );
	for ( size_t i = 0; i < m_nSegmentNumber; ++i )
	{
		float fAngle1 = Deg2Rad( 360.0f * i / m_nSegmentNumber );
		float fAngle2 = Deg2Rad( 360.0f * (i + 1) / m_nSegmentNumber );
		float x1 = m_Radius * cos(fAngle1);
		float z1 = m_Radius * sin(fAngle1);

		float x2 = m_Radius * cos(fAngle2);
		float z2 = m_Radius * sin(fAngle2);

		// normalization is not required
		Vector n0 ( cos(fAngle1), 0.0f, sin(fAngle1) );
		Vector n1 ( cos(fAngle2), 0.0f, sin(fAngle2) );
		Vector n2 ( 0.0f, 1.0f, 0.0f );
		Vector n3 ( 0.0f, -1.0f, 0.0f );

		Face f1(Vector( x1, m_Height/2, z1 ), 
				Vector( x2, m_Height/2, z2 ),
				Vector( x1, -m_Height/2, z1 ),
				n0, n1, n0,
				Vector2D( float(i)/m_nSegmentNumber, c_TopCircle ),
				Vector2D( float(i+1)/m_nSegmentNumber, c_TopCircle ),
				Vector2D( float(i)/m_nSegmentNumber, c_BottomCircle )
				);

		Face f2(Vector( x2, m_Height/2, z2 ),
				Vector( x2, -m_Height/2, z2 ),
				Vector( x1, -m_Height/2, z1 ),
				n1, n1, n0,
				Vector2D( float(i+1)/m_nSegmentNumber, c_TopCircle ),
				Vector2D( float(i+1)/m_nSegmentNumber, c_BottomCircle ),
				Vector2D( float(i)/m_nSegmentNumber, c_BottomCircle )
				);

		Face f3(Vector( x1, m_Height/2, z1 ),
				Vector( 0,  m_Height/2, 0 ),
				Vector( x2, m_Height/2, z2 ) ,
				n2, n2, n2,
				Vector2D( float(i)/m_nSegmentNumber, c_TopCircle ),
				Vector2D( 0.5f, 0.0f ),
				Vector2D( float(i+1)/m_nSegmentNumber, c_TopCircle )
			    );

		Face f4(Vector( x2, -m_Height/2, z2 ),
				Vector( 0,  -m_Height/2, 0 ),
				Vector( x1, -m_Height/2, z1 ),
				n3, n3, n3,
				Vector2D( float(i+1)/m_nSegmentNumber, c_BottomCircle ),
				Vector2D( 0.5f, 1.0f ),
				Vector2D( float(i)/m_nSegmentNumber, c_BottomCircle )
				);
		
		s.push_back( f1 );
		s.push_back( f2 );

		s.push_back( f3 );
		s.push_back( f4 );
	}
}