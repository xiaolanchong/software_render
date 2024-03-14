#include "stdafx.h"
#include "IPropertyMap.h"
/*
IPropertyMap::IPropertyMap()
{
}
*/

class PropertyMapImpl : public IPropertyMap
{
	std::vector<IPropertyHandler*>	m_Handlers;
public:

	virtual float		GetNumericProperty(DWORD Id)
	{
		for ( size_t i =0; i < m_Handlers.size(); ++i )
		{
			std::pair<bool, float> p = m_Handlers[i]->GetNumericProperty( Id );
			if( p.first ) return p.second;
		}
		throw NoSuchProperty();
	}

	virtual CString		GetStringProperty(DWORD Id)
	{
		for ( size_t i =0; i < m_Handlers.size(); ++i )
		{
			std::pair<bool, CString> p = m_Handlers[i]->GetStringProperty( Id );
			if( p.first ) return p.second;
		}
		throw NoSuchProperty();
	}

	virtual void	AddHandler( IPropertyHandler * p)	
	{
		m_Handlers.push_back( p );
	}

	virtual void	Notify( DWORD Id )
	{
		std::for_each( m_Handlers.begin(), m_Handlers.end(), 
						std::bind2nd( std::mem_fun( IPropertyHandler::Notify ), Id )
					 );
	}

};

IPropertyMap* GetPropertyMap()
{
	static PropertyMapImpl p;
	return &p;
}