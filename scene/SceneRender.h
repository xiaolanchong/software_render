#ifndef _SCENE_RENDER_5780562940148396_
#define _SCENE_RENDER_5780562940148396_

#include "../math/Matrix.h"

//! \brief Главный рендер сцены - настройка геометрии, освещения и т.д.
//! \author Eugene Gorbachev (Eugene.Gorbachev@biones.com)
//! \date   01.12.2005
//! \version 1.0
//! \bug 
//! \todo 

class	ILightType;
using ILightTypePtr = std::unique_ptr<ILightType>;
class	ILightEngine;
using ILightEnginePtr = std::unique_ptr<ILightEngine>;
class ISceneSolid;

class RenderEngine;

class SceneRender
{
private:
	Matrix	GetWorldMatrix() const;
	Matrix	GetViewMatrix() const;
	Matrix	GetProjMatrix(WORD w, WORD h) const;
	Vector	GetViewerPos() const ;

	Vector	GetPointLightPos() const;
	Vector	GetDirLightDir() const;

	ILightTypePtr		GetLightType() const;
	ILightEnginePtr		GetLightEngine
		(
			ILightTypePtr lt,
			const Vector& clLight, const Vector& clDiffuse, const Vector& clAmbient
		) const;

	mutable float m_AngleX, m_AngleY, m_AngleZ;

	using ISceneSolidPtr = std::unique_ptr<ISceneSolid>;
	std::vector<ISceneSolidPtr> m_sceneParts;

	std::unique_ptr<RenderEngine> m_eng;
public:
	SceneRender();
	virtual ~SceneRender();

	void	Render( CDC* pDC, WORD w, WORD h );
	void	Tick(float fTime);
};

#endif // _SCENE_RENDER_5780562940148396_