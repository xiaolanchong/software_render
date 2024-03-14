#include "stdafx.h"
#include "WireFrameRasterizer.h"

WireFrameRasterizer::WireFrameRasterizer()
{
}

WireFrameRasterizer::~WireFrameRasterizer()
{
}

void WireFrameRasterizer::Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h )
{
	CGdiObject * pPrevBrush = pDC->SelectStockObject( NULL_BRUSH );
	CGdiObject * pPrevPen = pDC->SelectStockObject( BLACK_PEN );

	CPoint pt[3];
	for ( size_t i=0; i < Mesh.size(); ++i )
	{
		for( size_t j=0; j < 3; ++j )
		{
			pt[j] = Trans2Viewport( w, h, Mesh[i].Vertices[j] );
		}
		pDC->Polygon( pt, 3 );
	}

	pDC->SelectObject(pPrevPen);
	pDC->SelectObject(pPrevBrush);
}