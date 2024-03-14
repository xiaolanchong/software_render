#include "stdafx.h"
#include "PixelRasterizer.h"
#include "DrawTriangle.h"
#include "InterpolationRender.h"

//stub
#include "../texture/TextureFileSource.h"

void	DrawTriangleGraySclae
( CDC* pDC, 
 int x1, int y1, int x2, int y2, int x3, int y3,
 BYTE cl1, BYTE cl2, BYTE cl3  )
{
	DCBytePlotter dc( pDC );
	DrawTriangle( dc, x1, y1, x2, y2, x3, y3, cl1, cl2, cl3 );
}

PixelRasterizer::PixelRasterizer()
{
}

PixelRasterizer::~PixelRasterizer()
{
}

//#define		RASTERIZE_COLOR
//#define		RASTERIZE_TEXTURE
#define		RASTERIZE_COLOR_AND_TEXTURE

void PixelRasterizer::Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h )
{
#if		defined RASTERIZE_COLOR
	DCColorPlotter dc(pDC);
#elif	defined RASTERIZE_TEXTURE
	DCTexturePlotter dc(pDC, 
		std::make_unique < TextureFileSource>( _T("earth.bmp") ));
#elif	defined RASTERIZE_COLOR_AND_TEXTURE
	DCTextureAndColorPlotter dc(pDC, 
		std::make_unique<TextureFileSource>( _T("earth.bmp") ) );
#endif
	PainterAlgoSort( Mesh );
	CPoint	pt[3];
	for ( size_t i=0; i < Mesh.size(); ++i )
	{
		for( size_t j=0; j < 3; ++j )
		{
			pt[j] = Trans2Viewport( w, h, Mesh[i].Vertices[j] );
		}
#if		defined RASTERIZE_COLOR
		DrawTriangle( dc, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
					  Mesh[i].Color[0], Mesh[i].Color[1], Mesh[i].Color[2] );
#elif	defined RASTERIZE_TEXTURE 
		DrawTriangle( dc, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
					  Mesh[i].TexCoord[0], Mesh[i].TexCoord[1], Mesh[i].TexCoord[2] );
#elif	defined RASTERIZE_COLOR_AND_TEXTURE
		DrawTriangle( dc, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
						DCTextureAndColorPlotter::ColorAndCoord_t( Mesh[i].Color[0], Mesh[i].TexCoord[0] ), 
						DCTextureAndColorPlotter::ColorAndCoord_t( Mesh[i].Color[1], Mesh[i].TexCoord[1] ), 
						DCTextureAndColorPlotter::ColorAndCoord_t( Mesh[i].Color[2], Mesh[i].TexCoord[2] ) );
#endif
	}
}