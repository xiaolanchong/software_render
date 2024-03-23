#pragma once

#include "../IPropertyMap.h"
#include "../math/Vector.h"
#include "../pipeline/Color.h"

inline Vector GetColorVector(IPropertyMap& propMap, PropertyId id)
{
	auto cl = static_cast<ColorType>(propMap.GetNumericProperty( id ));
	return Vector(GetR(cl) / 255.0f, GetG(cl) / 255.0f, GetB(cl) / 255.0f);
}
