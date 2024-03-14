#ifndef _PIXEL_RASTERIZER_5952036371517463_
#define _PIXEL_RASTERIZER_5952036371517463_

#include "IRasterizer.h"

class PixelRasterizer : public IRasterizer
{
public:
	PixelRasterizer();
	virtual ~PixelRasterizer();

	virtual void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h );
};

#endif // _PIXEL_RASTERIZER_5952036371517463_