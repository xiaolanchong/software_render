#include "stdafx.h"
#include "GouraudLight.h"

GouraudLight::GouraudLight
	(ILightTypePtr dir,
	 const Vector& clLight,
	 const Vector& clDiffuse,
	 const Vector& clAmbient): 
	LightEngineAdvance(std::move(dir), clLight, clDiffuse, clAmbient)
{
}

void	GouraudLight::Shade(	const Face& f, 
								Vector& cl1, Vector& cl2, Vector& cl3 )
{
	assert(  m_pLightDirection.get());

	std::pair<Vector, float> dir1 = m_pLightDirection->GetDirection( f[0] );
	std::pair<Vector, float> dir2 = m_pLightDirection->GetDirection( f[1] );
	std::pair<Vector, float> dir3 = m_pLightDirection->GetDirection( f[2] );

	float dot1 = clamp(dir1.first & f.n[0], 0.0f, 1.0f);
	float dot2 = clamp(dir2.first & f.n[1], 0.0f, 1.0f);
	float dot3 = clamp(dir3.first & f.n[2], 0.0f, 1.0f);

	cl1 = ClampLight(m_clAmbient + dot1 * dir1.second * m_clLight * m_clDiffuse);
	cl2 = ClampLight(m_clAmbient + dot2 * dir2.second * m_clLight * m_clDiffuse);
	cl3 = ClampLight(m_clAmbient + dot3 * dir3.second * m_clLight * m_clDiffuse);
}