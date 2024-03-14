#ifndef _I_LIGHT_ENGINE_4629847507434217_
#define _I_LIGHT_ENGINE_4629847507434217_

#include "../../math/face.h"
#include "ILightDirection.h"

//! \brief Интерфейс для расчета освещения грани
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class ILightEngine
{
protected:
	ILightTypePtr	m_pLightDirection;
	
	Vector	ClampLight( const Vector& cl )
	{
		return Vector(	clamp(cl.x, 0.0f, 1.0f),
						clamp(cl.y, 0.0f, 1.0f),
						clamp(cl.z, 0.0f, 1.0f));
	}
public:
	ILightEngine( ILightTypePtr dir ) :
		m_pLightDirection(std::move(dir))
	{

	}
	virtual ~ILightEngine() {};
	virtual void	Shade(	const Face& f, 
							Vector& cl1, Vector& cl2, Vector& cl3 ) = 0;
};

using ILightEnginePtr = std::unique_ptr<ILightEngine>;

struct ILightEngineAdvance : ILightEngine
{
protected:
	Vector	m_clLight;
	Vector	m_clAmbient;
	Vector	m_clDiffuse;

	ILightEngineAdvance(ILightTypePtr dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient) :
		ILightEngine(std::move(dir)),
		m_clAmbient(clAmbient) ,
		m_clDiffuse(clDiffuse),
		m_clLight(clLight)
	{

	}
public:
	void	SetDiffuse( const Vector& cl ) { m_clDiffuse = cl; }
};

#endif // _I_LIGHT_ENGINE_4629847507434217_