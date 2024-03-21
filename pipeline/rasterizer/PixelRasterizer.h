#pragma once

#include "IRasterizer.h"
#include "../texture/Array2D.h"

class TextureFileSource;

// Rendering to the back buffer
class PixelRasterizer : public IRasterizer
{
public:
	PixelRasterizer();
	void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) override;
	void SetTexture(TextureIndex index, const ITextureSourcePtr& texture) override;
private:

	ITextureSourcePtr m_texture;
	Array2D<DWORD> m_screenBuffer;
};
