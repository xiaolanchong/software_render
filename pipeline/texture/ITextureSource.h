#ifndef _I_TEXTURE_SOURCE_8577321150828403_
#define _I_TEXTURE_SOURCE_8577321150828403_

struct ITextureSource
{
public:
	virtual COLORREF	GetTexelColor( float u, float v ) const = 0 ;

	virtual ~ITextureSource() = default;
};

using ITextureSourcePtr = std::unique_ptr<ITextureSource>;

#endif // _I_TEXTURE_SOURCE_8577321150828403_