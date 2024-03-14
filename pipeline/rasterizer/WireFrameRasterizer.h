#ifndef _WIRE_FRAME_RASTERIZER_7523134573772507_
#define _WIRE_FRAME_RASTERIZER_7523134573772507_

#include "IRasterizer.h"

class WireFrameRasterizer : public IRasterizer
{
public:
	WireFrameRasterizer();
	virtual ~WireFrameRasterizer();

	virtual void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h );
};

#endif // _WIRE_FRAME_RASTERIZER_7523134573772507_