#include "stdafx.h"
#include "SceneRender.h"

#include "../pipeline/RenderEngine.h"
#include "../math/MatrixUtil.h"

#include "../pipeline/light/LambertLight.h"
#include "../pipeline/light/GouraudLight.h"
#include "../pipeline/light/PhongLight.h"
#include "../pipeline/texture/TextureFileSource.h"
#include "PropertyUtils.h"

#include "../IPropertyMap.h"

#include "SceneSolid.h"

SceneRender::SceneRender() :
	m_AngleX(0.0f), m_AngleY(0.0f), m_AngleZ(0.0f)
{
	m_sceneParts.push_back(std::make_unique<DodecahedronSceneSolid>());
	m_sceneParts.push_back(std::make_unique<CylinderSceneSolid>());
	m_sceneParts.push_back(std::make_unique<TorusSceneSolid>());
	m_sceneParts.push_back(std::make_unique<SphereSceneSolid>());
	m_sceneParts.push_back(std::make_unique<PointLightSolid>());

	m_eng = std::make_unique<RenderEngine>();

	m_texture = std::make_shared< TextureFileSource>("earth.bmp");
}

SceneRender::~SceneRender()
{

}

float GetIntensity(float x)
{
	float y = expf( 5 * logf((20.0000001f - x)/10 ) ) / 10.0f;
	return y;
}

ILightTypePtr	SceneRender::GetLightType(IPropertyMap& propMap) const
{
	if		(propMap.GetBoolProperty( prop_light_point ) )
	{
		float nIntensity = propMap.GetFloatProperty( prop_light_intensity );
		return std::make_unique<PointLightWithAttenuation>(GetPointLightPos(propMap), GetIntensity( nIntensity )  ) ;
	}
	else if	(propMap.GetBoolProperty( prop_light_direct ) )
		return std::make_unique < DirectLight>(GetDirLightDir());
	else if	(propMap.GetBoolProperty( prop_light_spot ) )
		return std::make_unique < SpotLight>( Vector( 0.0f, 0.0f, -8.0f), Vector( 0.0f, 0.0f, 1.0f ),
					0.05f, 20.0f, 90.0f, 3.0f );
	else 
		assert(false);
	return nullptr;
}

ILightEnginePtr		SceneRender::GetLightEngine
				(
					ILightTypePtr lt,
					const Vector& clLight, const Vector& clDiffuse, const Vector& clAmbient,
					IPropertyMap& propMap
				) const
{
	if	(propMap.GetBoolProperty( prop_light_lambert ) )
		return std::make_unique<LambertLight>( std::move(lt), clLight, clDiffuse, clAmbient );
	else if (propMap.GetBoolProperty( prop_light_gouraud ) )
		return std::make_unique<GouraudLight>(std::move(lt), clLight, clDiffuse, clAmbient );
	else if (propMap.GetBoolProperty( prop_light_phong ) )
		return std::make_unique<PhongLight>(std::move(lt), GetViewerPos(),
								clLight, Vector(1.0f, 1.0f, 1.0f), clDiffuse, clAmbient,
								50.0f);
	else 
		assert(false);
	return nullptr;
}

void	SceneRender::Render( IDeviceContext& dc, unsigned int w, unsigned int h, IPropertyMap& propMap )
{
	Matrix MatWorld = GetWorldMatrix( propMap );
	Matrix MatProj	= GetProjMatrix(w, h);	
	Matrix MatView	= GetViewMatrix();
	m_eng->SetViewMatrix(  MatView );
	m_eng->SetProjectionMatrix( MatProj );

	Vector clAmbient( 0.0f, 0.0f, 0.0f );
	Vector clLight = GetColorVector(propMap, prop_light_color );

	if(propMap.GetBoolProperty( prop_geo_wireframe ) )
		m_eng->SetMode(RenderEngine::Mode::OnlyWire);
	else if(propMap.GetBoolProperty(prop_geo_fill))
		m_eng->SetMode(RenderEngine::Mode::Fill);
	else if (propMap.GetBoolProperty(prop_geo_fill_and_textures))
		m_eng->SetMode(RenderEngine::Mode::FillAndTextures);

	m_eng->SetTexture(TEXTURE_0, m_texture);

	for ( size_t i =0; i < m_sceneParts.size(); ++i )
	{
		Vector clDiffuse = m_sceneParts[i]->GetDiffuse(propMap);
		ILightTypePtr	lt = GetLightType(propMap);
		ILightEnginePtr le = GetLightEngine( std::move(lt), clLight, clDiffuse, clAmbient, propMap );
		m_eng->SetLight( std::move(le) );
		m_sceneParts[i]->AddGeometry(*m_eng, MatWorld, propMap);
	}

	m_eng->Draw( dc, w, h  );
}

Matrix	SceneRender::GetViewMatrix() const
{
	Matrix MatView;
	LookAt( MatView, GetViewerPos(),  
					 Vector( 0.0f, 0.0f, 1.0f ),
					 Vector( 0.0f, 1.0f, 0.0f ));
	return MatView;
}

Matrix	SceneRender::GetProjMatrix(unsigned int w, unsigned int h ) const
{
	Matrix MatProj;
	PerspectiveFov( MatProj, Deg2Rad(45.0f), float(w)/h, 0.1f, 2000.0f);
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

Vector	SceneRender::GetPointLightPos(IPropertyMap& propMap) const
{
	return Vector (propMap.GetFloatProperty( prop_light_pos_x ),
		propMap.GetFloatProperty( prop_light_pos_y ),
		propMap.GetFloatProperty( prop_light_pos_z )
		);
}

void	SceneRender::Tick(IPropertyMap& propMap)
{
	float RotX = propMap.GetFloatProperty( prop_rs_rotate_x );
	float RotY = propMap.GetFloatProperty( prop_rs_rotate_y );
	float RotZ = propMap.GetFloatProperty( prop_rs_rotate_z );
	m_AngleX += Deg2Rad( RotX );
	m_AngleY += Deg2Rad( RotY );
	m_AngleZ += Deg2Rad( RotZ );
}

Matrix	SceneRender::GetWorldMatrix(IPropertyMap& propMap) const
{
	Matrix MatRotX = RotateX( m_AngleX );
	Matrix MatRotY = RotateY( m_AngleY );
	Matrix MatRotZ = RotateZ( m_AngleZ );
	Matrix MatRot = MatRotX * MatRotY * MatRotZ;
	Matrix MatScale = Scale(Vector(propMap.GetFloatProperty( prop_rs_scale_x ),
		propMap.GetFloatProperty( prop_rs_scale_y ),
		propMap.GetFloatProperty( prop_rs_scale_z ))
	);
	return MatScale * MatRot;
}