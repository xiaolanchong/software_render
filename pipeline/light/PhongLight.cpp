#include "stdafx.h"
#include "PhongLight.h"

PhongLight::PhongLight(
					   std::auto_ptr<ILightType> dir,
					   const Vector& ViewerPos,
					   const Vector& clLight,
					   const Vector& clSpecular,
					   const Vector& clDiffuse,
					   const Vector& clAmbient,
					   float Shininess
					   ):
	ILightEngineAdvance(dir, clLight, clDiffuse, clAmbient),
	m_clSpecular(clSpecular), 
	m_ViewPos(ViewerPos),
	m_Shininess(Shininess)
{
}

PhongLight::~PhongLight()
{
}

Vector Calculate( const Vector& LightDir, const Vector & ViewDir, const Vector& Normal,
				 /* const Vector& clLight, */const Vector& clDiffuse, const Vector& clSpecular,
				  float Shininess)
{
	Vector ReflectRay = 2 * ( Normal & LightDir ) * Normal - LightDir;
	float DiffPart = clamp( Normal & LightDir, 0.0f, 1.0f);
	float SpecPart = clamp( Normal & ReflectRay, 0.0f, 1.0f );
	SpecPart = exp( Shininess * log(SpecPart) );
	return /*clLight **/ ( clDiffuse * DiffPart + clSpecular * SpecPart );
}

void	PhongLight::Shade(const Face& f, Vector& cl1, Vector& cl2, Vector& cl3 )
{
	ASSERT(  m_pLightDirection.get());
#if 0
	std::pair<Vector, float> dir1 = m_pLightDirection->GetDirection( f[0] );
	std::pair<Vector, float> dir2 = m_pLightDirection->GetDirection( f[1] );
	std::pair<Vector, float> dir3 = m_pLightDirection->GetDirection( f[2] );

	float dot1 = clamp(dir1.first & f.n[0], 0.0f, 1.0f);
	float dot2 = clamp(dir2.first & f.n[1], 0.0f, 1.0f);
	float dot3 = clamp(dir3.first & f.n[2], 0.0f, 1.0f);

	cl1 = ClampLight(m_clAmbient + dot1 * dir1.second * m_clLight * m_clDiffuse);
	cl2 = ClampLight(m_clAmbient + dot2 * dir2.second * m_clLight * m_clDiffuse);
	cl3 = ClampLight(m_clAmbient + dot3 * dir3.second * m_clLight * m_clDiffuse);
#endif
	Vector clAll[3];
	Vector ViewDir;
	std::pair<Vector, float> LightProp;
	for ( size_t i =0; i < 3; ++i )
	{
		ViewDir = Normalize(m_ViewPos - f[i]);
		LightProp = m_pLightDirection->GetDirection( f[i] );
		clAll[i] = Calculate(	LightProp.first, ViewDir, f.n[i], 
								m_clDiffuse, m_clSpecular, m_Shininess);
		clAll[i] = ClampLight(m_clAmbient + LightProp.second * m_clLight * clAll[i]);
	}

	cl1 = clAll[0];
	cl2 = clAll[1];
	cl3 = clAll[2];
}