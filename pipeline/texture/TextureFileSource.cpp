#include "stdafx.h"
#include "TextureFileSource.h"

struct BitampInfoEx : BITMAPINFO
{
	RGBQUAD s[255];
};

TextureFileSource::TextureFileSource( LPCTSTR szFileName ) : 
	m_RawData(0,0, 0)
{
	HBITMAP hBmp = 
		(HBITMAP)LoadImage( 0, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ); 
	if( !hBmp ) throw FileNotFound();
	m_Bmp.Attach( hBmp );

	BitampInfoEx	bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO) );
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//	bi.bmiHeader.biPlanes	= 1;
//	bi.bmiHeader.biBitCount = 24;
	HWND hWnd	= GetDesktopWindow();
	HDC	 hDC	= GetDC(hWnd);
	int res = -1;
	res = GetDIBits( hDC, hBmp, 0, 0, 0, &bi, DIB_RGB_COLORS );
	ASSERT(res);
	m_bpp = bi.bmiHeader.biBitCount;
	m_RawData.resize(	bi.bmiHeader.biWidth * m_bpp/8, bi.bmiHeader.biHeight, 
						bi.bmiHeader.biWidth * m_bpp/8 );
	res = GetDIBits( hDC, hBmp, 0, bi.bmiHeader.biHeight, &m_RawData(0,0), &bi, DIB_RGB_COLORS );
	ASSERT(res);
	
	ReleaseDC(hWnd, hDC);
	
}

TextureFileSource::~TextureFileSource()
{
}

size_t ClampCoord( float x, size_t b, size_t t )
{
	if		( x < 0.0f )		return b;
	else if ( x > 1.0f )		return t;
	else						return size_t(( t - b ) * x);
}

COLORREF	TextureFileSource::GetTexelColor( float u, float v )
{
	v = 1.0f - v;
	size_t indexX = ClampCoord( u, 0, m_RawData.GetWidth() / 4 - 1);
	size_t indexY = ClampCoord( v, 0, m_RawData.GetHeight() - 1    );
	
	const BYTE* p = &m_RawData(0,0);
	BYTE	b = m_RawData( 4 * indexX + 0, indexY );
	BYTE	g = m_RawData( 4 * indexX + 1, indexY );
	BYTE	r = m_RawData( 4 * indexX + 2, indexY );

	return RGB(r, g, b);
}