#pragma once

#include "../math/Face.h"

//! Geometric body description interface
class IGeoSolid
{
public:
	using Faces = std::vector<Face>;

	virtual ~IGeoSolid() = default;

	virtual Faces GetFaces() const = 0;
};
