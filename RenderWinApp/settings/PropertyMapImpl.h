#pragma once

#include "../../RenderLib/IPropertyMap.h"

class PropertyMapImpl: public IPropertyMap
{
public:
	virtual float   GetNumericProperty(PropertyId Id) override;
	virtual std::string GetStringProperty(PropertyId Id) override;
	virtual void	AddHandler(IPropertyHandlerWeakPtr p) override;
	virtual void	Notify(PropertyId Id) override;

private:
	std::vector<IPropertyHandlerWeakPtr>	m_Handlers;
};

