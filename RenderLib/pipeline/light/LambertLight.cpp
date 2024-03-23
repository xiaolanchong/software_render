#include "stdafx.h"
#include "LambertLight.h"

LambertLight::LambertLight(ILightTypePtr dir,
						   const Vector& clLight,
						   const Vector& clDiffuse,
						   const Vector& clAmbient):
	LightEngineAdvance( std::move(dir), clLight, clDiffuse, clAmbient)
{
	m_clAmbient = clAmbient;
}

void	LambertLight::Shade(	const Face& f, 
								Vector& cl1, Vector& cl2, Vector& cl3 )
{
	assert(  m_pLightDirection.get());

	std::pair<Vector, float> dir1 = m_pLightDirection->GetDirection( f[0] );
	Vector dir = dir1.first;
	float  fIntensity	= dir1.second;

	Vector n1 = ( f.n[0] + f.n[1] + f.n[2] )/3;
	n1 = Normalize( n1 );
	float dot1 = clamp(dir & n1, 0.0f, 1.0f);
	cl1 = ClampLight(m_clAmbient + dot1 * fIntensity * m_clLight * m_clDiffuse);
	cl2 = cl1;
	cl3 = cl2;
}