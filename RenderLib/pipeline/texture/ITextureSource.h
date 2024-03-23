#pragma once

#include "../Color.h"

class ITextureSource
{
public:
	virtual ColorType GetTexelColor( float u, float v ) const = 0 ;

	virtual ~ITextureSource() = default;
};

using ITextureSourcePtr = std::shared_ptr<ITextureSource>;
