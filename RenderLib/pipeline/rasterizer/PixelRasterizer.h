#pragma once

#include "IRasterizer.h"
#include "../texture/Array2D.h"

class TextureFileSource;

// Rendering to the back buffer
class PixelRasterizer : public IRasterizer
{
public:
	PixelRasterizer();
	void Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h ) override;
	void SetTexture(TextureIndex index, const ITextureSourcePtr& texture) override;
private:

	ITextureSourcePtr m_texture;
	Array2D<std::uint32_t> m_screenBuffer;
};
