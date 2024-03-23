#pragma once

#include "IGeoSolid.h"

class SolidTorus : public IGeoSolid
{
	float	m_innerRadius;
	float	m_outerRadius;
	size_t	m_sides;
	size_t	m_rings;
public:
	SolidTorus(float innerRadius, float outerRadius, size_t sides, size_t rings);

	Faces GetFaces() const override;
};
