#include "stdafx.h"
#include "SceneSolid.h"
#include "../pipeline/RenderEngine.h"
#include "../settings/IPropertyMap.h"

#include "../geometry/SolidDodecahedron.h"
#include "../geometry/SolidCylinder.h"
#include "../geometry/SolidTorus.h"
#include "../geometry/SolidSphere.h"

Vector	DodecahedronSceneSolid::GetDiffuse()
{
	return GetColorVector( prop_geo_dodecahedron_color );
}

void	DodecahedronSceneSolid::AddGeometry( RenderEngine& re, const Matrix& MatWorld )
{
	if( !BoolProperty( prop_geo_dodecahedron_enable ) ) return;

	IGeoSolid::Solid_t Faces;
	SolidDodecahedron	sc( 1.0f );
	sc.GetFaces( Faces );
	
	Matrix MatRotDod = RotateZ(Deg2Rad(32.0f));
	Matrix MatWorldTor = Translate( Vector(0.0f, 2.70f, 0.0f) ) ;
	MatWorldTor = MatRotDod * MatWorldTor * MatWorld;
	re.SetWorldMatrix( MatWorldTor );
	re.AddPrimitive( Faces );
}

//////////////////////////////////////////////////////////////////////////

Vector	CylinderSceneSolid::GetDiffuse()
{
	return GetColorVector( prop_geo_cylinder_color );
}

void	CylinderSceneSolid::AddGeometry( RenderEngine& re, const Matrix& MatWorld )
{
	if( !BoolProperty( prop_geo_cylinder_enable ) ) return;
#if 1
	SolidCylinder		sc( 0.78f, 1.75f,  
		(size_t)IntProperty( prop_geo_cylinder_segments )  );
#else
	SolidSphere			sc( 1.0f, 32, 32 );
#endif
	IGeoSolid::Solid_t Faces;
	sc.GetFaces( Faces );

	Matrix MatWorldCyl = Translate( Vector(0.0f, 1.0f, 0.0f) ) ;
	MatWorldCyl = MatWorldCyl * MatWorld;
	re.SetWorldMatrix( MatWorldCyl );
	re.AddPrimitive( Faces );
}

//////////////////////////////////////////////////////////////////////////

Vector TorusSceneSolid::GetDiffuse()
{
	return GetColorVector( prop_geo_torus_color );
}


void	TorusSceneSolid::AddGeometry( RenderEngine& re, const Matrix& MatWorld )
{
	if( !BoolProperty( prop_geo_torus_enable ) ) return;
	SolidTorus			sc( 1.0f, 0.25f, 
		(size_t)IntProperty( prop_geo_torus_rings ), 
		(size_t)IntProperty( prop_geo_torus_segments )							
		);
	IGeoSolid::Solid_t Faces;
	sc.GetFaces( Faces );

	re.SetWorldMatrix( MatWorld );
	re.AddPrimitive( Faces );
}

//////////////////////////////////////////////////////////////////////////

Vector PointLightSolid::GetDiffuse()
{
	return Vector( 0.0f, 1.0f, 1.0f  ) ;
}


void	PointLightSolid::AddGeometry( RenderEngine& re, const Matrix& /*MatWorld*/ )
{
	if( !BoolProperty( prop_light_point ) ) return;
	SolidSphere			sc( 0.2f, 6, 6 );
	IGeoSolid::Solid_t Faces;
	sc.GetFaces( Faces );

	Matrix MatPos = Translate( 	Vector (	FloatProperty( prop_light_pos_x ),
											FloatProperty( prop_light_pos_y ),
											FloatProperty( prop_light_pos_z )
										) );

	re.SetWorldMatrix( MatPos );
	re.AddPrimitive( Faces );
}
