#pragma once

#include "ILightEngine.h"

//! \brief Освещение по Ламберту.
//	intensity = Ambient + Diffuse * LightColor * Atten * cos(n, L),
//	где n - нормаль к грани.
//		L - направление на свет
//		Atten - интенсивность
//		Diffuse - диффузный цвет материала
//		LightColor - цвет источника
//		Ambient - рассеянный цвет материала
//	Освещение постоянно по всей грани.

class LambertLight : public LightEngineAdvance
{

public:
	LambertLight(ILightTypePtr dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient);
	
	void	Shade(const Face& f, 
					Vector& cl1, Vector& cl2, Vector& cl3 ) override;
};
