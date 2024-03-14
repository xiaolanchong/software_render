#ifndef _PHONG_LIGHT_6212698885417518_
#define _PHONG_LIGHT_6212698885417518_

#include "ILightEngine.h"

class PhongLight: public ILightEngineAdvance
{
protected:
	Vector		m_clSpecular;
	Vector		m_ViewPos;
	float		m_Shininess;
public:
	PhongLight(	
		std::auto_ptr<ILightType> dir,
		const Vector& ViewerPos,
		const Vector& clLight,
		const Vector& clSpecular,
		const Vector& clDiffuse,
		const Vector& clAmbient,
		float Shininess
		);
	virtual ~PhongLight();

	virtual void	Shade(	const Face& f, Vector& cl1, Vector& cl2, Vector& cl3 ) ;
};

#endif // _PHONG_LIGHT_6212698885417518_