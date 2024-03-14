#ifndef _SOLID_TORUS_1160498783178629_
#define _SOLID_TORUS_1160498783178629_

#include "IGeoSolid.h"
//! \brief Тор как геометрическое тело
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class SolidTorus : public IGeoSolid
{
	float	m_innerRadius;
	float	m_outerRadius;
	size_t	m_sides;
	size_t	m_rings;
public:
	SolidTorus(float innerRadius, float outerRadius, size_t sides, size_t rings);
	virtual ~SolidTorus();

	virtual void GetFaces( Solid_t& s );
};

#endif // _SOLID_TORUS_1160498783178629_