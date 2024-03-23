#pragma once

#include "IGeoSolid.h"

class SolidCylinder : public IGeoSolid
{
	float	m_Radius;
	float	m_Height;
	size_t	m_nSegmentNumber;
public:
	SolidCylinder( float Radius, float Height, size_t nSegmentNumber );

	Faces GetFaces() const override;
};
