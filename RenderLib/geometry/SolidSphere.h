#pragma once

#include "IGeoSolid.h"

class SolidSphere : public IGeoSolid
{
	float		m_Radius;
	size_t		m_Rings;
	size_t		m_Segments;
public:
	SolidSphere( float Radius, size_t Rings, size_t Segments );

	Faces GetFaces() const override;
};
