#pragma once

#include "IPropertyMap.h"

class PropertyMapImpl: public IPropertyMap
{
public:
	virtual float		GetNumericProperty(DWORD Id) override;
	virtual CString		GetStringProperty(DWORD Id) override;
	virtual void	AddHandler(IPropertyHandlerWeakPtr p) override;
	virtual void	Notify(DWORD Id) override;

private:
	std::vector<IPropertyHandlerWeakPtr>	m_Handlers;
};

