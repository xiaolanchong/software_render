#ifndef _TEXTURE_FILE_SOURCE_6001259116341356_
#define _TEXTURE_FILE_SOURCE_6001259116341356_

#include "ITextureSource.h"
#include "Array2D.h"

class TextureFileSource : public ITextureSource
{
	Array2D<BYTE> m_RawData;
	CBitmap	m_Bmp;
	size_t	m_bpp;
public:
	class TextureFileSourceException : public std::exception {};
	class FileNotFound				 : public TextureFileSourceException {};

	TextureFileSource( LPCTSTR szFileName );
	virtual ~TextureFileSource();

	virtual COLORREF	GetTexelColor( float u, float v ) ;
};

#endif // _TEXTURE_FILE_SOURCE_6001259116341356_