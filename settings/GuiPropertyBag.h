#ifndef _GUI_PROPERTY_BAG_1272553053832792_
#define _GUI_PROPERTY_BAG_1272553053832792_

#include "IPropertyMap.h"

class GuiPropertyBag;
using GuiPropertyBagPtr = std::shared_ptr<GuiPropertyBag>;

class GuiPropertyBag : public IPropertyMap::IPropertyHandler
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

	static GuiPropertyBagPtr Create(IPropertyMap& propMap);
private:
	using ControlHandlerPtr = std::unique_ptr<ControlHandler>;
	std::map< DWORD, ControlHandlerPtr > m_Controls;
	void InsertControl(DWORD Id, ControlHandlerPtr p);

	GuiPropertyBag();
public:

	void AddButton( DWORD Id, CWnd* pWnd, UINT nControlID );
	void AddSlider( DWORD Id, CWnd* pWnd, UINT nControlID );
	void AddColor( DWORD Id, CWnd* pWnd, UINT nControlID );	
	void AddText( DWORD Id, CWnd* pWnd, UINT nControlID );

	virtual std::pair<bool, float>	GetNumericProperty(DWORD Id) override;
	virtual std::pair<bool, CString>	GetStringProperty(DWORD Id) override;
	virtual void Notify(DWORD /*id*/) override {}
};

#endif // _GUI_PROPERTY_BAG_1272553053832792_