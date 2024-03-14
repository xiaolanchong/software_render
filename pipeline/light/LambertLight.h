#ifndef _LAMBERT_LIGHT_4403499311454775_
#define _LAMBERT_LIGHT_4403499311454775_

#include "ILightEngine.h"

//! \brief Освещение по Ламберту.
//	intensity = Ambient + Diffuse * LightColor * Atten * cos(n, L),
//	где n - нормаль к грани.
//		L - направление на свет
//		Фееут - интунсивность
//		Diffuse - диффузный цвет материала
//		LightColor - цвет источника
//		Ambient - рассеянный цвет материала
//	Освещение постоянно по всей грани.
//	
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class LambertLight : public ILightEngineAdvance
{

public:
	LambertLight(	std::auto_ptr<ILightType> dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient);
	virtual ~LambertLight();

	
	virtual void	Shade(	const Face& f, 
							Vector& cl1, Vector& cl2, Vector& cl3 ) ;
};

#endif // _LAMBERT_LIGHT_4403499311454775_