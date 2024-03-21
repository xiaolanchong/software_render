#pragma once

#include "IRasterizer.h"

class GradientRasterizer : public IRasterizer
{
public:
	void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) override;

	// doesn't support texturing
	void SetTexture(TextureIndex /*index*/, const ITextureSourcePtr& /*texture*/) override {}
};
