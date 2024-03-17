#ifndef _PHONG_LIGHT_6212698885417518_
#define _PHONG_LIGHT_6212698885417518_

#include "ILightEngine.h"

class PhongLight: public LightEngineAdvance
{
protected:
	Vector		m_clSpecular;
	Vector		m_ViewPos;
	float		m_Shininess;
public:
	PhongLight(	
		ILightTypePtr dir,
		const Vector& ViewerPos,
		const Vector& clLight,
		const Vector& clSpecular,
		const Vector& clDiffuse,
		const Vector& clAmbient,
		float Shininess
		);

	void	Shade(	const Face& f, Vector& cl1, Vector& cl2, Vector& cl3 ) override;
};

#endif // _PHONG_LIGHT_6212698885417518_