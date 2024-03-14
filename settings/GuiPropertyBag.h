#ifndef _GUI_PROPERTY_BAG_1272553053832792_
#define _GUI_PROPERTY_BAG_1272553053832792_

#include "IPropertyMap.h"

//! \brief Not available
//! \author 
//! \date   01.12.2005
//! \version 1.0
//! \bug 
//! \todo 

class GuiPropertyBag : public IPropertyMap::IPropertyHandler
	//, public std::enable_shared_from_this<GuiPropertyBag>
{
public:
	class ControlHandler
	{
	protected:
		CWnd *	m_pWnd;
		UINT	m_nControlID;
	public:
		ControlHandler(CWnd* pWnd, UINT nControlID) : 
		  m_pWnd (pWnd),
		  m_nControlID(nControlID)
		 {}

		virtual ~ControlHandler() = default;
		virtual float		GetNumericProperty() = 0;
		virtual CString		GetStringProperty() = 0;
	};
private:
	using ControlHandlerPtr = std::unique_ptr<ControlHandler>;
	std::map< DWORD, ControlHandlerPtr > m_Controls;
	void InsertControl(DWORD Id, ControlHandlerPtr p);
protected:

	void AddButton( DWORD Id, CWnd* pWnd, UINT nControlID );
	void AddSlider( DWORD Id, CWnd* pWnd, UINT nControlID );
	void AddColor( DWORD Id, CWnd* pWnd, UINT nControlID );	
	void AddText( DWORD Id, CWnd* pWnd, UINT nControlID );

	GuiPropertyBag();

	virtual void						Notify( DWORD /*dwID*/ )
	{
		// do nothing, overrided by descendants
	}

	virtual std::pair<bool, float>		GetNumericProperty(DWORD Id);
	virtual std::pair<bool, CString>	GetStringProperty(DWORD Id);
};

#endif // _GUI_PROPERTY_BAG_1272553053832792_