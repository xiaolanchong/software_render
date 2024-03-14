#include "stdafx.h"
#include "LambertLight.h"

LambertLight::LambertLight( std::auto_ptr<ILightType> dir,
						   const Vector& clLight,
						   const Vector& clDiffuse,
						   const Vector& clAmbient):
	ILightEngineAdvance( dir, clLight, clDiffuse, clAmbient)
{
	m_clAmbient = clAmbient;
}

LambertLight::~LambertLight()
{
}

void	LambertLight::Shade(	const Face& f, 
								Vector& cl1, Vector& cl2, Vector& cl3 )
{
	ASSERT(  m_pLightDirection.get());

#if 1
	std::pair<Vector, float> dir1 = m_pLightDirection->GetDirection( f[0] );
	Vector dir = dir1.first;
	float  fIntensity	= dir1.second;
#else
	std::pair<Vector, float> dir1 = m_pLightDirection->GetDirection( f[0] );
	std::pair<Vector, float> dir2 = m_pLightDirection->GetDirection( f[1] );
	std::pair<Vector, float> dir3 = m_pLightDirection->GetDirection( f[2] );
	Vector dir			= (dir1.first + dir2.first + dir3.first)/3;
	dir = Normalize(dir);
	float  fIntensity	= (dir1.second + dir2.second + dir3.second)/3; 
#endif
/*	Vector dir2 = m_pLightDirection->GetDirection( f[1] );
	Vector dir3 = m_pLightDirection->GetDirection( f[2] );
	Vector dir = (dir1 + dir)*/

	Vector n1 = ( f.n[0] + f.n[1] + f.n[2] )/3;
	n1 = Normalize( n1 );
	float dot1 = clamp(dir & n1, 0.0f, 1.0f);
	cl1 = ClampLight(m_clAmbient + dot1 * fIntensity * m_clLight * m_clDiffuse);
	cl2 = cl1;
	cl3 = cl2;
}