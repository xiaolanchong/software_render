#ifndef _PIXEL_RASTERIZER_5952036371517463_
#define _PIXEL_RASTERIZER_5952036371517463_

#include "IRasterizer.h"

class DCTextureAndColorPlotter;

class PixelRasterizer : public IRasterizer
{
public:
	PixelRasterizer();
	void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) override;

private:
	std::unique_ptr<DCTextureAndColorPlotter> m_plotter;
};

#endif // _PIXEL_RASTERIZER_5952036371517463_