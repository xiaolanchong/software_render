#ifndef _SOLID_SPHERE_7479645654308649_
#define _SOLID_SPHERE_7479645654308649_
//! \brief Интерфейс сферы как геометрического тела
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

#include "IGeoSolid.h"

// not implemented currently
class SolidSphere : public IGeoSolid
{
	float		m_Radius;
	size_t		m_Rings;
	size_t		m_Segments;
public:
	SolidSphere( float Radius,size_t Rings, size_t Segments );
	virtual ~SolidSphere();

	virtual void GetFaces( Solid_t& s );
};

#endif // _SOLID_SPHERE_7479645654308649_