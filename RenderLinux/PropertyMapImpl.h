#pragma once

#include <string>
#include <optional>
#include <map>
#include <variant>
#include "../RenderLib/IPropertyMap.h"

class PropertyMapImpl: public IPropertyMap
{
public:
	explicit PropertyMapImpl(const std::string& fileName = std::string());

	float GetNumericProperty(PropertyId Id) override;
	std::string	GetStringProperty(PropertyId Id) override;
	
private:
	using PropertyVal = std::variant<float, std::string>;
	std::map<PropertyId, PropertyVal> m_values;
};
