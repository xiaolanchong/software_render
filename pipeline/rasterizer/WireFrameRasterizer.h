#pragma once

#include "IRasterizer.h"

class WireFrameRasterizer : public IRasterizer
{
public:
	void Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h ) override;

	// has no meaning
	void SetTexture(TextureIndex /*index*/, const ITextureSourcePtr& /*texture*/) override {}
private:
	std::vector<CPoint> m_vertices;
};
