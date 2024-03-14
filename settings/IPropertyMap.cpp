#include "stdafx.h"
#include "IPropertyMap.h"

class PropertyMapImpl : public IPropertyMap
{
	std::vector<IPropertyHandlerWeakPtr>	m_Handlers;
public:

	virtual float		GetNumericProperty(DWORD Id)
	{
		for ( size_t i =0; i < m_Handlers.size(); ++i )
		{
			if (auto handlerPtr = m_Handlers[i])
			{
				std::pair<bool, float> p = handlerPtr->GetNumericProperty(Id);
				if (p.first) return p.second;
			}
		}
		throw NoSuchProperty(Id);
	}

	virtual CString		GetStringProperty(DWORD Id)
	{
		for ( size_t i =0; i < m_Handlers.size(); ++i )
		{
			if (auto handlerPtr = m_Handlers[i])
			{
				std::pair<bool, CString> p = handlerPtr->GetStringProperty(Id);
				if (p.first) return p.second;
			}
		}
		throw NoSuchProperty(Id);
	}

	virtual void	AddHandler( IPropertyHandlerWeakPtr p)	
	{
		m_Handlers.push_back( p );
	}

	virtual void	Notify( DWORD Id )
	{
		std::for_each( m_Handlers.begin(), m_Handlers.end(), 
			[Id](auto& handler)
					{
						if (auto handlerPtr = handler)
							handlerPtr->Notify(Id); 
					});
	}

};

IPropertyMap* GetPropertyMap()
{
	static PropertyMapImpl p;
	return &p;
}