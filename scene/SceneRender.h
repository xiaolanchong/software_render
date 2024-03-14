#ifndef _SCENE_RENDER_5780562940148396_
#define _SCENE_RENDER_5780562940148396_

#include "../math/Matrix.h"

//! \brief ������� ������ ����� - ��������� ���������, ��������� � �.�.
//! \author Eugene Gorbachev (Eugene.Gorbachev@biones.com)
//! \date   01.12.2005
//! \version 1.0
//! \bug 
//! \todo 

struct	ILightType;
class	ILightEngine;

class SceneRender
{
	Matrix	GetWorldMatrix() const;
	Matrix	GetViewMatrix() const;
	Matrix	GetProjMatrix(WORD w, WORD h) const;
	Vector	GetViewerPos() const ;

	Vector	GetPointLightPos() const;
	Vector	GetDirLightDir() const;

	std::auto_ptr<ILightType>		GetLightType() const;
	std::auto_ptr<ILightEngine>		GetLightEngine
		(
			std::auto_ptr<ILightType> lt, 
			const Vector& clLight, const Vector& clDiffuse, const Vector& clAmbient
		) const;

	mutable float m_AngleX, m_AngleY, m_AngleZ;
public:
	SceneRender();
	virtual ~SceneRender();

	void	Render( CDC* pDC, WORD w, WORD h );
	void	Tick(float fTime);
};

#endif // _SCENE_RENDER_5780562940148396_