#ifndef _SOLID_CYLINDER_6159010435812994_
#define _SOLID_CYLINDER_6159010435812994_

#include "IGeoSolid.h"

//! \brief Интерфейс Цилиндра как геометрического тела
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class SolidCylinder : public IGeoSolid
{
	float	m_Radius;
	float	m_Height;
	size_t	m_nSegmentNumber;
public:
	SolidCylinder( float Radius, float Height, size_t nSegmentNumber );

	virtual void GetFaces( Solid_t& s );
	virtual ~SolidCylinder();
};

#endif // _SOLID_CYLINDER_6159010435812994_