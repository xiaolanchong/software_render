#ifndef _GRADIENT_RASTERIZER_3370411010322394_
#define _GRADIENT_RASTERIZER_3370411010322394_

#include "IRasterizer.h"

class GradientRasterizer : public IRasterizer
{
public:
	GradientRasterizer();
	virtual ~GradientRasterizer();

	virtual void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h );
};

#endif // _GRADIENT_RASTERIZER_3370411010322394_