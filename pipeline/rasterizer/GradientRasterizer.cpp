#include "stdafx.h"
#include "GradientRasterizer.h"

void GradientRasterizer::Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h )
{
	std::vector<TRIVERTEX>				vert(Mesh.size() * 3);
	std::vector<GRADIENT_TRIANGLE>		gTri(Mesh.size());

	PainterAlgoSort( Mesh );

	for ( size_t i = 0; i < Mesh.size(); ++i  )
	{
		for ( size_t j = 0; j < 3; ++j )
		{
			size_t nIndex = 3*i + j;
			CPoint pt = Trans2Viewport( w, h, Mesh[i].Vertices[j] );
			vert[nIndex].x = pt.x;
			vert[nIndex].y = pt.y;

			vert[nIndex].Red	= GetRValue(Mesh[i].Color[j]) << 8;
			vert[nIndex].Blue	= GetBValue(Mesh[i].Color[j]) << 8;
			vert[nIndex].Green	= GetGValue(Mesh[i].Color[j]) << 8;
			vert[nIndex].Alpha	= 0x0000;
		}
	}

	for ( size_t i = 0 ; i < Mesh.size(); ++i  )
	{
		gTri[i].Vertex1	= ULONG( 3*i + 0 );
		gTri[i].Vertex2	= ULONG( 3*i + 1 );
		gTri[i].Vertex3	= ULONG( 3*i + 2 );
	}

	bool res = dc.GradientFill(&vert[0], vert.size(), &gTri[0], gTri.size());
	//BOOL res = GradientFill(pDC->GetSafeHdc(), &vert[0], (ULONG) vert.size(), &gTri[0], (ULONG)gTri.size(), GRADIENT_FILL_TRIANGLE);
	VERIFY(res);
}
