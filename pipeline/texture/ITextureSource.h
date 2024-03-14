#ifndef _I_TEXTURE_SOURCE_8577321150828403_
#define _I_TEXTURE_SOURCE_8577321150828403_

struct ITextureSource
{
	virtual COLORREF	GetTexelColor( float u, float v ) = 0 ;

	virtual ~ITextureSource() {};
};

using ITextureSourcePtr = std::unique_ptr<ITextureSource>;

#endif // _I_TEXTURE_SOURCE_8577321150828403_