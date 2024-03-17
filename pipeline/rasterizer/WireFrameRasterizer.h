#pragma once

#include "IRasterizer.h"

class WireFrameRasterizer : public IRasterizer
{
public:
	void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) override;
};
