#ifndef _GRADIENT_RASTERIZER_3370411010322394_
#define _GRADIENT_RASTERIZER_3370411010322394_

#include "IRasterizer.h"

class GradientRasterizer : public IRasterizer
{
public:
	void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) override;
};

#endif // _GRADIENT_RASTERIZER_3370411010322394_