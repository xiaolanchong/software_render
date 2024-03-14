#ifndef _GOURAUD_LIGHT_9073291314267220_
#define _GOURAUD_LIGHT_9073291314267220_

#include "ILightEngine.h"

//! \brief Освещение по Гуро.
//!			то же самое как и по Ламберту, но значение вычисляется по 
//!			вершинам и линейно интерполируется на грани
//!	
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class GouraudLight : public ILightEngineAdvance
{
public:
	GouraudLight(ILightTypePtr dir,
					const Vector& clLight,
					const Vector& clDiffuse,
					const Vector& clAmbient);
	virtual ~GouraudLight();

	virtual void	Shade(	const Face& f, 
							Vector& cl1, Vector& cl2, Vector& cl3 ) ;
};

#endif // _GOURAUD_LIGHT_9073291314267220_