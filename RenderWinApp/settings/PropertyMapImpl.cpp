#include "stdafx.h"
#include "PropertyMapImpl.h"


float		PropertyMapImpl::GetNumericProperty(PropertyId Id)
{
	for (size_t i = 0; i < m_Handlers.size(); ++i)
	{
		if (auto handlerPtr = m_Handlers[i].lock())
		{
			std::optional<float> p = handlerPtr->GetNumericProperty(Id);
			if (p) return *p;
		}
	}
	throw NoSuchProperty(Id);
}

std::string		PropertyMapImpl::GetStringProperty(PropertyId Id)
{
	for (size_t i = 0; i < m_Handlers.size(); ++i)
	{
		if (auto handlerPtr = m_Handlers[i].lock())
		{
			return handlerPtr->GetStringProperty(Id);
		}
	}
	throw NoSuchProperty(Id);
}

void	PropertyMapImpl::AddHandler(IPropertyHandlerWeakPtr p)
{
	m_Handlers.push_back(p);
}

void	PropertyMapImpl::Notify(PropertyId Id)
{
	std::for_each(m_Handlers.begin(), m_Handlers.end(),
		[Id](auto& handler)
		{
			if (auto handlerPtr = handler.lock())
				handlerPtr->Notify(Id);
		});
}