#ifndef _GUI_PROPERTY_BAG_1272553053832792_
#define _GUI_PROPERTY_BAG_1272553053832792_

#include "../RenderLib/IPropertyMap.h"

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
		virtual std::string		GetStringProperty() = 0;
	};

	static GuiPropertyBagPtr Create(IPropertyMap& propMap);
private:
	using ControlHandlerPtr = std::unique_ptr<ControlHandler>;
	std::map< PropertyId, ControlHandlerPtr > m_Controls;
	void InsertControl(PropertyId Id, ControlHandlerPtr p);

	GuiPropertyBag();
public:

	void AddButton(PropertyId Id, CWnd* pWnd, UINT nControlID );
	void AddSlider(PropertyId Id, CWnd* pWnd, UINT nControlID );
	void AddColor(PropertyId Id, CWnd* pWnd, UINT nControlID );
	void AddText(PropertyId Id, CWnd* pWnd, UINT nControlID );

	virtual std::optional<float>	GetNumericProperty(PropertyId Id) override;
	virtual std::string	GetStringProperty(PropertyId Id) override;
	virtual void Notify(PropertyId /*id*/) override {}
};

#endif // _GUI_PROPERTY_BAG_1272553053832792_