#ifndef _I_GEO_SOLID_6697391762634109_
#define _I_GEO_SOLID_6697391762634109_

#include "../math/Face.h"

//! \brief Интерфейс геометрического тела
//! \author Eugene Gorbachev (Eugene.Gorbachev@biones.com)
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

struct IGeoSolid
{
	typedef std::vector<Face>	Solid_t;
	virtual void GetFaces( Solid_t& s ) = 0;
	virtual ~IGeoSolid() {};
};

#endif // _I_GEO_SOLID_6697391762634109_