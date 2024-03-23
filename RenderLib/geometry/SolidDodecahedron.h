#pragma once

#include "IGeoSolid.h"

// 20 faces platonic solid
class SolidDodecahedron : public IGeoSolid
{
	float	dodec[20][3];

	void pentagon(IGeoSolid::Faces& s,
					size_t a, size_t b, size_t c, size_t d, size_t e) const;
public:
	SolidDodecahedron(float Radius);

	Faces GetFaces() const override;
};
