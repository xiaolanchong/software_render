#pragma once

#include "IRasterizer.h"

class GradientRasterizer : public IRasterizer
{
public:
	void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) override;
};
