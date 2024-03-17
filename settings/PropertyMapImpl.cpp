#include "stdafx.h"
#include "PropertyMapImpl.h"


float		PropertyMapImpl::GetNumericProperty(DWORD Id)
{
	for (size_t i = 0; i < m_Handlers.size(); ++i)
	{
		if (auto handlerPtr = m_Handlers[i].lock())
		{
			std::pair<bool, float> p = handlerPtr->GetNumericProperty(Id);
			if (p.first) return p.second;
		}
	}
	throw NoSuchProperty(Id);
}

CString		PropertyMapImpl::GetStringProperty(DWORD Id)
{
	for (size_t i = 0; i < m_Handlers.size(); ++i)
	{
		if (auto handlerPtr = m_Handlers[i].lock())
		{
			std::pair<bool, CString> p = handlerPtr->GetStringProperty(Id);
			if (p.first) return p.second;
		}
	}
	throw NoSuchProperty(Id);
}

void	PropertyMapImpl::AddHandler(IPropertyHandlerWeakPtr p)
{
	m_Handlers.push_back(p);
}

void	PropertyMapImpl::Notify(DWORD Id)
{
	std::for_each(m_Handlers.begin(), m_Handlers.end(),
		[Id](auto& handler)
		{
			if (auto handlerPtr = handler.lock())
				handlerPtr->Notify(Id);
		});
}