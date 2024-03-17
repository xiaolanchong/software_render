#ifndef _GOURAUD_LIGHT_9073291314267220_
#define _GOURAUD_LIGHT_9073291314267220_

#include "ILightEngine.h"

//! \brief Освещение по Гуро.
//!			то же самое как и по Ламберту, но значение вычисляется по 
//!			вершинам и линейно интерполируется на грани

class GouraudLight : public LightEngineAdvance
{
public:
	GouraudLight(ILightTypePtr dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient);

	void	Shade( const Face& f, 
					Vector& cl1, Vector& cl2, Vector& cl3 ) override;
};

#endif // _GOURAUD_LIGHT_9073291314267220_