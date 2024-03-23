#pragma once

#include "IRasterizer.h"

class GradientRasterizer : public IRasterizer
{
public:
	void Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h ) override;

	// doesn't support texturing
	void SetTexture(TextureIndex /*index*/, const ITextureSourcePtr& /*texture*/) override {}
};
