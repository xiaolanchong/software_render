#ifndef _SOLID_DODECAHEDRON_4933700737521826_
#define _SOLID_DODECAHEDRON_4933700737521826_

#include "IGeoSolid.h"

class SolidDodecahedron : public IGeoSolid
{
//	float	m_Radius;
	float	dodec[20][3];

	void pentagon(	Solid_t& s,  
					size_t a, size_t b, size_t c, size_t d, size_t e);
public:
	SolidDodecahedron(float Radius);
	virtual ~SolidDodecahedron();

	virtual void GetFaces( Solid_t& s );
};

#endif // _SOLID_DODECAHEDRON_4933700737521826_