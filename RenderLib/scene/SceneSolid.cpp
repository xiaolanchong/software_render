#include "stdafx.h"
#include "SceneSolid.h"
#include "../pipeline/RenderEngine.h"
#include "../IPropertyMap.h"

#include "../geometry/SolidDodecahedron.h"
#include "../geometry/SolidCylinder.h"
#include "../geometry/SolidTorus.h"
#include "../geometry/SolidSphere.h"
#include "PropertyUtils.h"

Vector	DodecahedronSceneSolid::GetDiffuse(IPropertyMap& propMap)
{
	return GetColorVector(propMap, prop_geo_dodecahedron_color );
}

void	DodecahedronSceneSolid::AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap)
{
	if( !propMap.GetBoolProperty( prop_geo_dodecahedron_enable ) ) return;
	
	if (m_faces.empty())
	{
		SolidDodecahedron	sc(1.0f);
		m_faces = sc.GetFaces();
	}
	
	Matrix MatRotDod = RotateZ(Deg2Rad(32.0f));
	Matrix MatWorldTor = Translate( Vector(0.0f, 1.7f, 0.0f) ) ;
	MatWorldTor = MatRotDod * MatWorldTor * MatWorld;
	re.SetWorldMatrix( MatWorldTor );
	re.AddPrimitive(m_faces, TEXTURE_0);
}

//////////////////////////////////////////////////////////////////////////

Vector	CylinderSceneSolid::GetDiffuse(IPropertyMap& propMap)
{
	return GetColorVector(propMap, prop_geo_cylinder_color );
}

void	CylinderSceneSolid::AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap)
{
	if( !propMap.GetBoolProperty( prop_geo_cylinder_enable ) )
		return;

	const size_t newSegments = (size_t)propMap.GetIntProperty(prop_geo_cylinder_segments);
	if (newSegments != m_lastSegments)
	{
		SolidCylinder		sc(0.78f, 1.75f, newSegments);
		m_faces = sc.GetFaces();
		m_lastSegments = newSegments;
	}

	Matrix MatWorldCyl = Translate( Vector(0.0f, 0.0f, 0.0f) ) ;
	MatWorldCyl = MatWorldCyl * MatWorld;
	re.SetWorldMatrix( MatWorldCyl );
	re.AddPrimitive(m_faces, NO_TEXTURE);
}

//////////////////////////////////////////////////////////////////////////

Vector	SphereSceneSolid::GetDiffuse(IPropertyMap& /*propMap*/)
{
	return Vector(0.9f, 0.9f, 0.9f);;
}

void	SphereSceneSolid::AddGeometry(RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap)
{
	if (!propMap.GetBoolProperty(prop_geo_cylinder_enable))
		return;

	const size_t segments = static_cast<size_t>(propMap.GetIntProperty(prop_geo_cylinder_segments));
	if (m_lastSegments != segments)
	{
		SolidSphere	sc(1.5f, segments / 2, segments / 2);
		m_faces = sc.GetFaces();
		m_lastSegments = segments;
	}

	Matrix MatWorldCyl = Translate(Vector(3.0f, 0.0f, 0.0f));
	MatWorldCyl = MatWorldCyl * MatWorld;
	re.SetWorldMatrix(MatWorldCyl);
	re.AddPrimitive(m_faces, TEXTURE_0);
}

//////////////////////////////////////////////////////////////////////////
Vector TorusSceneSolid::GetDiffuse(IPropertyMap& propMap)
{
	return GetColorVector( propMap, prop_geo_torus_color );
}

void	TorusSceneSolid::AddGeometry( RenderEngine& re, const Matrix& MatWorld, IPropertyMap& propMap)
{
	if( !propMap.GetBoolProperty( prop_geo_torus_enable ) )
		return;

	const auto newRings = (size_t)propMap.GetIntProperty(prop_geo_torus_rings);
	const auto newSegments = (size_t)propMap.GetIntProperty(prop_geo_torus_segments);

	if (std::tie(newRings, newSegments) !=
		std::tie(m_lasRings, m_lastSegments))
	{
		SolidTorus sc(1.0f, 0.25f, newRings, newSegments);
		m_faces = sc.GetFaces();
		m_lasRings = newRings;
		m_lastSegments = newSegments;
	}

	Matrix MatWorldTor = Translate(Vector(0.0f, -1.f, 0.0f));
	MatWorldTor = MatWorldTor * MatWorld;
	re.SetWorldMatrix(MatWorldTor);
	re.AddPrimitive(m_faces, NO_TEXTURE);
}

//////////////////////////////////////////////////////////////////////////

Vector PointLightSolid::GetDiffuse(IPropertyMap& /*propMap*/)
{
	return Vector( 0.0f, 1.0f, 1.0f  ) ;
}

void	PointLightSolid::AddGeometry( RenderEngine& re, const Matrix& /*MatWorld*/, IPropertyMap& propMap)
{
	if( !propMap.GetBoolProperty( prop_light_point ) )
		return;
	SolidSphere			sc( 0.2f, 6, 6 );
	IGeoSolid::Faces faces = sc.GetFaces( );

	Matrix MatPos = Translate(Vector (propMap.GetFloatProperty( prop_light_pos_x ),
		propMap.GetFloatProperty( prop_light_pos_y ),
		propMap.GetFloatProperty( prop_light_pos_z )) );

	re.SetWorldMatrix( MatPos );
	re.AddPrimitive(faces, NO_TEXTURE);
}
