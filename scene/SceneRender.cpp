#include "stdafx.h"
#include "SceneRender.h"

#include "../pipeline/RenderEngine.h"
#include "../math/MatrixUtil.h"

#include "../pipeline/light/LambertLight.h"
#include "../pipeline/light/GouraudLight.h"
#include "../pipeline/light/PhongLight.h"

#include "../settings/IPropertyMap.h"
#include "SceneSolid.h"

SceneRender::SceneRender() :
	m_AngleX(0.0f), m_AngleY(0.0f), m_AngleZ(0.0f)
{
}

SceneRender::~SceneRender()
{
}

float GetIntensity(float x)
{
	float y = (float)exp( 5 * log((20.0000001 - x)/10 ) ) / 10.0f;
	return y;
}

std::auto_ptr<ILightType>	SceneRender::GetLightType() const
{
	ILightType* lt = NULL;
	if		( BoolProperty( prop_light_point ) )
	{
		float nIntensity = FloatProperty( prop_light_intensity );
		lt = new PointLightWithAttenuation(GetPointLightPos(), GetIntensity( nIntensity )  ) ;
	}
	else if	( BoolProperty( prop_light_direct ) )
		lt = new DirectLight(GetDirLightDir());
	else if	( BoolProperty( prop_light_spot ) )
		SpotLight( Vector( 0.0f, 0.0f, -8.0f), Vector( 0.0f, 0.0f, 1.0f ),
					0.05f, 20.0f, 90.0f, 3.0f );
	else 
		ASSERT(FALSE);
	ASSERT(lt);
	return std::auto_ptr<ILightType> (lt);
}

std::auto_ptr<ILightEngine>		SceneRender::GetLightEngine
				(
					std::auto_ptr<ILightType> lt, 
					const Vector& clLight, const Vector& clDiffuse, const Vector& clAmbient
				) const
{
	ILightEngine* ple = NULL;

	if		( BoolProperty( prop_light_lambert ) )
		ple = new LambertLight ( lt, clLight, clDiffuse, clAmbient );
	else if ( BoolProperty( prop_light_gouraud ) )
		ple = new GouraudLight ( lt, clLight, clDiffuse, clAmbient );
	else if ( BoolProperty( prop_light_phong ) )
		ple = new PhongLight(	lt, GetViewerPos(), 
								clLight, Vector(1.0f, 1.0f, 1.0f), clDiffuse, clAmbient,
								50.0f
		);
	else 
		ASSERT(FALSE);
	ASSERT(ple);
	return std::auto_ptr<ILightEngine>(ple);
}

void	SceneRender::Render( CDC* pDC, WORD w, WORD h )
{
	std::vector<ISceneSolid*> SceneParts;

	SceneParts.push_back( new DodecahedronSceneSolid );
	SceneParts.push_back( new CylinderSceneSolid );
	SceneParts.push_back( new TorusSceneSolid );

	RenderEngine eng;

	Matrix MatWorld = GetWorldMatrix( );
	Matrix MatProj	= GetProjMatrix(w, h);	
	Matrix MatView	= GetViewMatrix();
	eng.SetViewMatrix(  MatView );
	eng.SetProjectionMatrix( MatProj );

	Vector clAmbient( 0.0f, 0.0f, 0.0f );
	Vector clLight = GetColorVector( prop_light_color );

	if( BoolProperty( prop_geo_wireframe ) )
		eng.SetWireFrame(true);

	for ( size_t i =0; i < SceneParts.size(); ++i )
	{
		Vector clDiffuse = SceneParts[i]->GetDiffuse();
		std::auto_ptr<ILightType>	lt = GetLightType();
		std::auto_ptr<ILightEngine>	le = GetLightEngine( lt, clLight, clDiffuse, clAmbient );
		eng.SetLight( le );
		SceneParts[i]->AddGeometry( eng, MatWorld );
	}
#if 0
	std::auto_ptr<IPointSolid> Light;
	std::auto_ptr lt = new DirectLight(GetDirLightDir());
#endif

	eng.Draw( pDC, w, h  );

	for( size_t i =0; i < SceneParts.size(); ++i )
	{
		delete SceneParts[i];
	}
}

Matrix	SceneRender::GetViewMatrix() const
{
	Matrix MatView;
	LookAt( MatView, GetViewerPos(),  
					 Vector( 0.0f, 0.0f, 4.0f ),
					 Vector( 0.0f, 1.0f, 0.0f ));
	return MatView;
}

Matrix	SceneRender::GetProjMatrix( WORD w, WORD h ) const
{
	Matrix MatProj;
	PerspectiveFov( MatProj, Deg2Rad(45.0f), float(w)/h, 0.1f, 20.0f);
	//	OrthoOffCenter( MatProj, -1.5f, 1.5f, -1.0f, 1.0f,  0.1f, 20.0f );
	return MatProj;
}

Vector	SceneRender::GetViewerPos() const
{
	return Vector( 0.0f, 3.0f, -8.0f );
}

Vector	SceneRender::GetDirLightDir() const
{
	return Vector(0.0f, 0.0f, -1.0f);
}

Vector	SceneRender::GetPointLightPos() const
{
	return Vector (	FloatProperty( prop_light_pos_x ),
					FloatProperty( prop_light_pos_y ),
					FloatProperty( prop_light_pos_z )
					);
}

void	SceneRender::Tick( float fTime )
{
	float RotX = FloatProperty( prop_rs_rotate_x );
	float RotY = FloatProperty( prop_rs_rotate_y );
	float RotZ = FloatProperty( prop_rs_rotate_z );
	m_AngleX += Deg2Rad( RotX );
	m_AngleY += Deg2Rad( RotY );
	m_AngleZ += Deg2Rad( RotZ );
}

Matrix	SceneRender::GetWorldMatrix(  ) const
{

	Matrix MatRotX = RotateX( m_AngleX );
	Matrix MatRotY = RotateY( m_AngleY );
	Matrix MatRotZ = RotateZ( m_AngleZ );
	Matrix MatRot = MatRotX * MatRotY * MatRotZ;
	Matrix MatScale = Scale(Vector( FloatProperty( prop_rs_scale_x ), 
									FloatProperty( prop_rs_scale_y ),
									FloatProperty( prop_rs_scale_z )
									)
							);
	return MatScale * MatRot;
}