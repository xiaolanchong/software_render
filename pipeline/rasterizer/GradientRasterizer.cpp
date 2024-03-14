#include "stdafx.h"
#include "GradientRasterizer.h"

GradientRasterizer::GradientRasterizer()
{
}

GradientRasterizer::~GradientRasterizer()
{
}

void GradientRasterizer::Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h )
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
#if 1
	size_t i1 = vert.size();
	size_t i2 = Mesh.size();
	size_t i3 = gTri.size();
#endif
	for ( size_t i = 0 ; i < Mesh.size(); ++i  )
	{
		gTri[i].Vertex1	= ULONG( 3*i + 0 );
		gTri[i].Vertex2	= ULONG( 3*i + 1 );
		gTri[i].Vertex3	= ULONG( 3*i + 2 );
	}
#if 1
	const TRIVERTEX* pv = &vert[0];
	const GRADIENT_TRIANGLE *pi = &gTri[0];
#endif
	// shut up compiler, i guess 2^31 - 1 is much more
	BOOL res = GradientFill(pDC->GetSafeHdc(), &vert[0], (ULONG) vert.size(), &gTri[0], (ULONG)gTri.size(), GRADIENT_FILL_TRIANGLE);
	//	ASSERT(res);
}