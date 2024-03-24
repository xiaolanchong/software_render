#include "stdafx.h"
#include <fstream>
#include "TextureFileSource.h"

namespace
{

#pragma pack(push)
#pragma pack(1)

struct alignas(1) BitmapFileHeader
{
	unsigned short	Type;
	unsigned int	Size;
	unsigned short	Reserved1;
	unsigned short	Reserved2;
	unsigned int	OffBits;
};

struct alignas(1) BitmapInfoHeader
{
	unsigned int	Size;
	int		Width;
	int		Height;
	unsigned short	Planes;
	unsigned short	BitCount;
	unsigned int	Compression;
	unsigned int	SizeImage;
	int		XPelsPerMeter;
	int		YPelsPerMeter;
	unsigned int	ClrUsed;
	unsigned int	ClrImrportant;
};

#pragma pack(pop)

}

TextureFileSource::TextureFileSource(const std::string& fileName):
	m_RawData(0, 0, 0)
{
	loadFromFile(fileName);
}

#ifdef WIN32

struct BitampInfoEx : BITMAPINFO
{
	RGBQUAD s[255];
};

void TextureFileSource::loadWithBitmap(const std::string& fileName)
{
	HBITMAP hBmp = 
		(HBITMAP)LoadImageA( 0, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if( !hBmp ) throw std::runtime_error("Can't load file: ");
	CBitmap Bmp;
	Bmp.Attach(hBmp);

	BitampInfoEx	bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO) );
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
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
#endif

size_t ClampCoord( float x, size_t b, size_t t )
{
	if		( x < 0.0f )		return b;
	else if ( x > 1.0f )		return t;
	else						return size_t(( t - b ) * x);
}

ColorType	TextureFileSource::GetTexelColor( float u, float v ) const
{
	v = 1.0f - v;
#if windows_load
	constexpr size_t BYTES_PER_PIXEL = 4;
	size_t indexX = ClampCoord( u, 0, m_RawData.GetWidth() / BYTES_PER_PIXEL - 1);
	size_t indexY = ClampCoord( v, 0, m_RawData.GetHeight() - 1    );
	
	std::uint8_t	b = m_RawData( 4 * indexX + 0, indexY );
	std::uint8_t	g = m_RawData( 4 * indexX + 1, indexY );
	std::uint8_t	r = m_RawData( 4 * indexX + 2, indexY );
	std::uint8_t	a = m_RawData( 4 * indexX + 3, indexY);
#else
	constexpr size_t BYTES_PER_PIXEL = 3;
	size_t indexX = ClampCoord(u, 0, m_RawData.GetWidth() / BYTES_PER_PIXEL - 1);
	size_t indexY = ClampCoord(v, 0, m_RawData.GetHeight() - 1);

	std::uint8_t	b = m_RawData(BYTES_PER_PIXEL * indexX + 0, indexY);
	std::uint8_t	g = m_RawData(BYTES_PER_PIXEL * indexX + 1, indexY);
	std::uint8_t	r = m_RawData(BYTES_PER_PIXEL * indexX + 2, indexY);
#endif

	return Rgb(r, g, b);
}

void TextureFileSource::loadFromFile(const std::string& fileName)
{
	std::ifstream f(fileName, std::ios::binary);
	if (!f.is_open())
	{
		throw std::runtime_error("Can't open file " + fileName);
	}

	BitmapFileHeader fileHeader{};
	BitmapInfoHeader infoHeader{};

	f.exceptions(std::ifstream::failbit);
	f.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
	f.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));

	if (infoHeader.Compression != 0)
	{
		throw std::runtime_error("Bitmap is compressed");
	}
	if (infoHeader.BitCount != 24)
	{
		throw std::runtime_error("Bitmap bits/pixel is not 24");
	}
	if (infoHeader.Width >= 10000 || infoHeader.Height >= 10000)
	{
		throw std::runtime_error("Image is too large");
	}

	const unsigned int assumedSize = infoHeader.Height * infoHeader.Width * infoHeader.BitCount / 8;
#if 0
	
	if (infoHeader.SizeImage <= assumedSize)
	{
		throw std::runtime_error("Image is truncated");
	}
#endif

	m_bpp = infoHeader.BitCount;

	m_RawData.resize(infoHeader.Width * m_bpp / 8, infoHeader.Height,
		infoHeader.Width * m_bpp / 8);
	
	f.read(reinterpret_cast<char*>(&m_RawData(0, 0)), assumedSize);
}