#ifndef _TEXTURE_FILE_SOURCE_6001259116341356_
#define _TEXTURE_FILE_SOURCE_6001259116341356_

#include "ITextureSource.h"
#include "Array2D.h"

class TextureFileSource : public ITextureSource
{
public:
	TextureFileSource(const std::string& fileName);

	virtual COLORREF	GetTexelColor( float u, float v ) const override;

private:
	void loadFromFile(const std::string& fileName);
	void loadWithBitmap(LPCTSTR szFileName);

private:
	Array2D<std::uint8_t> m_RawData;
	size_t	m_bpp;
};

#endif // _TEXTURE_FILE_SOURCE_6001259116341356_