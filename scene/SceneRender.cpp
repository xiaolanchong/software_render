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
	m_sceneParts.push_back(std::make_unique<DodecahedronSceneSolid>());
	m_sceneParts.push_back(std::make_unique < CylinderSceneSolid>());
	m_sceneParts.push_back(std::make_unique < TorusSceneSolid>());

	m_eng = std::make_unique<RenderEngine>();
}

SceneRender::~SceneRender()
{
}

float GetIntensity(float x)
{
	float y = expf( 5 * logf((20.0000001f - x)/10 ) ) / 10.0f;
	return y;
}

ILightTypePtr	SceneRender::GetLightType() const
{
	if		( BoolProperty( prop_light_point ) )
	{
		float nIntensity = FloatProperty( prop_light_intensity );
		return std::make_unique<PointLightWithAttenuation>(GetPointLightPos(), GetIntensity( nIntensity )  ) ;
	}
	else if	( BoolProperty( prop_light_direct ) )
		return std::make_unique < DirectLight>(GetDirLightDir());
	else if	( BoolProperty( prop_light_spot ) )
		return std::make_unique < SpotLight>( Vector( 0.0f, 0.0f, -8.0f), Vector( 0.0f, 0.0f, 1.0f ),
					0.05f, 20.0f, 90.0f, 3.0f );
	else 
		ASSERT(FALSE);
	return nullptr;
}

ILightEnginePtr		SceneRender::GetLightEngine
				(
					ILightTypePtr lt,
					const Vector& clLight, const Vector& clDiffuse, const Vector& clAmbient
				) const
{
	ILightEngine* ple = NULL;

	if		( BoolProperty( prop_light_lambert ) )
		ple = new LambertLight ( std::move(lt), clLight, clDiffuse, clAmbient );
	else if ( BoolProperty( prop_light_gouraud ) )
		ple = new GouraudLight (std::move(lt), clLight, clDiffuse, clAmbient );
	else if ( BoolProperty( prop_light_phong ) )
		ple = new PhongLight(std::move(lt), GetViewerPos(),
								clLight, Vector(1.0f, 1.0f, 1.0f), clDiffuse, clAmbient,
								50.0f
		);
	else 
		ASSERT(FALSE);
	ASSERT(ple);
	return ILightEnginePtr(ple);
}

void	SceneRender::Render( CDC* pDC, WORD w, WORD h )
{


	Matrix MatWorld = GetWorldMatrix( );
	Matrix MatProj	= GetProjMatrix(w, h);	
	Matrix MatView	= GetViewMatrix();
	m_eng->SetViewMatrix(  MatView );
	m_eng->SetProjectionMatrix( MatProj );

	Vector clAmbient( 0.0f, 0.0f, 0.0f );
	Vector clLight = GetColorVector( prop_light_color );

	if( BoolProperty( prop_geo_wireframe ) )
		m_eng->SetMode(RenderEngine::Mode::OnlyWire);
	else if(BoolProperty(prop_geo_fill))
		m_eng->SetMode(RenderEngine::Mode::Fill);
	else if (BoolProperty(prop_geo_fill_and_textures))
		m_eng->SetMode(RenderEngine::Mode::FillAndTextures);

	for ( size_t i =0; i < m_sceneParts.size(); ++i )
	{
		Vector clDiffuse = m_sceneParts[i]->GetDiffuse();
		ILightTypePtr	lt = GetLightType();
		ILightEnginePtr le = GetLightEngine( std::move(lt), clLight, clDiffuse, clAmbient );
		m_eng->SetLight( std::move(le) );
		m_sceneParts[i]->AddGeometry(*m_eng, MatWorld );
	}

	m_eng->Draw( pDC, w, h  );
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

void	SceneRender::Tick( float /*fTime*/ )
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