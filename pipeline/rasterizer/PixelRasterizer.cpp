#include "stdafx.h"
#include "PixelRasterizer.h"
#include "DrawTriangle.h"
#include "InterpolationRender.h"

#include "../texture/TextureFileSource.h"

void	DrawTriangleGraySclae( CDC* pDC, 
 int x1, int y1, int x2, int y2, int x3, int y3,
 BYTE cl1, BYTE cl2, BYTE cl3  )
{
	DCBytePlotter dc( pDC );
	DrawTriangle( dc, x1, y1, x2, y2, x3, y3, cl1, cl2, cl3 );
}

//#define		RASTERIZE_COLOR
//#define		RASTERIZE_TEXTURE
#define		RASTERIZE_COLOR_AND_TEXTURE

PixelRasterizer::PixelRasterizer()
	: m_screenBuffer(1, 1, 1)
{
#if		defined RASTERIZE_COLOR
	DCColorPlotter dc(pDC);
#elif	defined RASTERIZE_TEXTURE
	DCTexturePlotter dc(pDC,
		std::make_unique < TextureFileSource>(_T("earth.bmp")));
#elif	defined RASTERIZE_COLOR_AND_TEXTURE
	m_texture = std::make_shared< TextureFileSource>(_T("earth.bmp"));
#endif
}

class BufferContext
{
public:
	BufferContext(Array2D<DWORD>& buffer)
		: m_buffer(buffer)
	{}

	void SetPixel(int x, int y, COLORREF cl)
	{
		auto newCl = RGB(GetBValue(cl), GetGValue(cl), GetRValue(cl));
		m_buffer(x, y) = newCl;
	}
private:
	Array2D<DWORD>& m_buffer;
};

void PixelRasterizer::Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h )
{
	m_screenBuffer.resize(w, h, w);
	std::fill(m_screenBuffer.begin(), m_screenBuffer.end(), 0xffffffff);  // BGR
	BufferContext buffer(m_screenBuffer);

	using Plotter = DCTextureAndColorPlotter<BufferContext>;
	Plotter plotter(&buffer, m_texture, w, h);

	PainterAlgoSort( Mesh );
	CPoint	pt[3];
	for ( size_t i=0; i < Mesh.size(); ++i )
	{
		for( size_t j=0; j < 3; ++j )
		{
			pt[j] = Trans2Viewport( w, h, Mesh[i].Vertices[j] );
		}
#if defined RASTERIZE_COLOR
		DrawTriangle( dc, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
					  Mesh[i].Color[0], Mesh[i].Color[1], Mesh[i].Color[2] );
#elif	defined RASTERIZE_TEXTURE 
		DrawTriangle( dc, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
					  Mesh[i].TexCoord[0], Mesh[i].TexCoord[1], Mesh[i].TexCoord[2] );
#elif	defined RASTERIZE_COLOR_AND_TEXTURE
		DrawTriangle(plotter, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
			Plotter::ColorAndCoord_t( Mesh[i].Color[0], Mesh[i].TexCoord[0] ),
			Plotter::ColorAndCoord_t( Mesh[i].Color[1], Mesh[i].TexCoord[1] ),
			Plotter::ColorAndCoord_t( Mesh[i].Color[2], Mesh[i].TexCoord[2] ) );
#endif
	}

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	auto& header = bmi.bmiHeader;
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biWidth = w;
	header.biHeight = -h;
	header.biPlanes = 1;
	header.biBitCount = 32;
	header.biCompression = BI_RGB;
	header.biSizeImage = 0;

	auto res = ::SetDIBitsToDevice(pDC->GetSafeHdc(), 
		0, 0, w, h,
		0, 0, 0, h,
		&(*m_screenBuffer.begin()), &bmi, DIB_RGB_COLORS);
	VERIFY(res);
}
