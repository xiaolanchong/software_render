#ifndef _SCENE_RENDER_5780562940148396_
#define _SCENE_RENDER_5780562940148396_

#include "../math/Matrix.h"

//! Главный рендер сцены - настройка геометрии, освещения и т.д.

class	ILightType;
using ILightTypePtr = std::unique_ptr<ILightType>;
class	ILightEngine;
using ILightEnginePtr = std::unique_ptr<ILightEngine>;
class IPropertyMap;
class ISceneSolid;
class ITextureSource;
using ITextureSourcePtr = std::shared_ptr<ITextureSource>;

class RenderEngine;

class SceneRender
{
private:
	Matrix	GetWorldMatrix(IPropertyMap& propMap) const;
	Matrix	GetViewMatrix() const;
	Matrix	GetProjMatrix(WORD w, WORD h) const;
	Vector	GetViewerPos() const ;

	Vector	GetPointLightPos(IPropertyMap& propMap) const;
	Vector	GetDirLightDir() const;

	ILightTypePtr		GetLightType(IPropertyMap& propMap) const;
	ILightEnginePtr		GetLightEngine
		(
			ILightTypePtr lt,
			const Vector& clLight, const Vector& clDiffuse, const Vector& clAmbient,
			IPropertyMap& propMap
		) const;


public:
	SceneRender();
	~SceneRender();

	void	Render( CDC* pDC, WORD w, WORD h, IPropertyMap& propMap );
	void	Tick(IPropertyMap& propMap);

private:

	mutable float m_AngleX, m_AngleY, m_AngleZ;

	using ISceneSolidPtr = std::unique_ptr<ISceneSolid>;
	std::vector<ISceneSolidPtr> m_sceneParts;

	std::unique_ptr<RenderEngine> m_eng;

	ITextureSourcePtr m_texture;
};

#endif // _SCENE_RENDER_5780562940148396_