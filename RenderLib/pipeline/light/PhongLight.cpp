#include "stdafx.h"
#include "PhongLight.h"

PhongLight::PhongLight(
					   ILightTypePtr dir,
					   const Vector& ViewerPos,
					   const Vector& clLight,
					   const Vector& clSpecular,
					   const Vector& clDiffuse,
					   const Vector& clAmbient,
					   float Shininess
					   ):
	LightEngineAdvance(std::move(dir), clLight, clDiffuse, clAmbient),
	m_clSpecular(clSpecular), 
	m_ViewPos(ViewerPos),
	m_Shininess(Shininess)
{
}

Vector Calculate( const Vector& LightDir, const Vector & /*ViewDir*/, const Vector& Normal,
				 /* const Vector& clLight, */const Vector& clDiffuse, const Vector& clSpecular,
				  float Shininess)
{
	Vector ReflectRay = 2 * ( Normal & LightDir ) * Normal - LightDir;
	float DiffPart = clamp( Normal & LightDir, 0.0f, 1.0f);
	float SpecPart = clamp( Normal & ReflectRay, 0.0f, 1.0f );
	SpecPart = expf( Shininess * logf(SpecPart) );
	return /*clLight **/ ( clDiffuse * DiffPart + clSpecular * SpecPart );
}

void	PhongLight::Shade(const Face& f, Vector& cl1, Vector& cl2, Vector& cl3 )
{
	assert(  m_pLightDirection.get());

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
