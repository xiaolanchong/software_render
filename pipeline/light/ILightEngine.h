#pragma once

#include "../../math/face.h"
#include "ILightDirection.h"

//! Интерфейс для расчета освещения грани
class ILightEngine
{
public:
	virtual ~ILightEngine() = default;
	virtual void Shade(const Face& f,
		Vector& cl1, Vector& cl2, Vector& cl3) = 0;
};

using ILightEnginePtr = std::unique_ptr<ILightEngine>;

class BasicLightEngine: public ILightEngine
{
protected:
	ILightTypePtr	m_pLightDirection;
protected:
	Vector	ClampLight( const Vector& cl )
	{
		return Vector(	clamp(cl.x, 0.0f, 1.0f),
						clamp(cl.y, 0.0f, 1.0f),
						clamp(cl.z, 0.0f, 1.0f));
	}
public:
	BasicLightEngine( ILightTypePtr dir ) :
		m_pLightDirection(std::move(dir))
	{
	}
};

class LightEngineAdvance : public BasicLightEngine
{
protected:
	Vector	m_clLight;
	Vector	m_clAmbient;
	Vector	m_clDiffuse;
protected:
	LightEngineAdvance(ILightTypePtr dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient) :
		BasicLightEngine(std::move(dir)),
		m_clAmbient(clAmbient) ,
		m_clDiffuse(clDiffuse),
		m_clLight(clLight)
	{

	}
public:
	void	SetDiffuse( const Vector& cl ) { m_clDiffuse = cl; }
};
