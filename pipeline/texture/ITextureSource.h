#pragma once

struct ITextureSource
{
public:
	virtual COLORREF	GetTexelColor( float u, float v ) const = 0 ;

	virtual ~ITextureSource() = default;
};

using ITextureSourcePtr = std::shared_ptr<ITextureSource>;
