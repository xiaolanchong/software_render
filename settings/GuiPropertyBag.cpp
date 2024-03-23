#include "stdafx.h"
#include "GuiPropertyBag.h"
#include "ColorStatic.h"

//////////////////////////////////////////////////////////////////////////

class ButtonHandler : public GuiPropertyBag::ControlHandler
{
public:
	ButtonHandler( CWnd* pWnd, UINT nControlID  ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty() override
	{
		if(m_pWnd->GetSafeHwnd())
			m_currentValue = m_pWnd->IsDlgButtonChecked(m_nControlID) != BST_UNCHECKED;
		return m_currentValue ? 1.0f : 0.0f;
	}
	virtual std::string GetStringProperty() override
	{
		ASSERT(FALSE);
		return {};
	}
private:
	bool m_currentValue = false;
};

//////////////////////////////////////////////////////////////////////////

class SliderHandler : public GuiPropertyBag::ControlHandler
{
public:
	SliderHandler( CWnd* pWnd, UINT nControlID ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty() override
	{
		if (m_pWnd->GetSafeHwnd())
		{
			CSliderCtrl* pSlider = static_cast<CSliderCtrl*>(m_pWnd->GetDlgItem(m_nControlID));
			ASSERT(pSlider);
			m_currentValue = pSlider->GetPos();
		}

		return float(m_currentValue);
	}
	virtual std::string 	GetStringProperty() override
	{
		ASSERT(FALSE);
		return {};
	}

private:
	int m_currentValue = 0;
};

//////////////////////////////////////////////////////////////////////////

class ColorHandler : public GuiPropertyBag::ControlHandler
{
public:
	ColorHandler( CWnd* pWnd, UINT nControlID ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty() override
	{
		if (m_pWnd->GetSafeHwnd())
		{
			CColorStatic* pSlider = static_cast<CColorStatic*>(m_pWnd->GetDlgItem(m_nControlID));
			ASSERT(pSlider);
			m_currentValue = pSlider->GetColor();
		}
		return float(m_currentValue);
	}
	virtual std::string		GetStringProperty() override
	{
		ASSERT(FALSE);
		return {};
	}

private:
	COLORREF m_currentValue = 0;
};

//////////////////////////////////////////////////////////////////////////

class TextHandler : public GuiPropertyBag::ControlHandler
{
public:
	TextHandler( CWnd* pWnd, UINT nControlID ) : ControlHandler( pWnd, nControlID ){}

	virtual float		GetNumericProperty() override
	{
		if (m_pWnd->GetSafeHwnd())
		{
			CString val;
			m_pWnd->GetDlgItemText(m_nControlID, val);
			m_currentValue = CT2CA(val);
		}
		char* p = NULL;
		double v = strtod(m_currentValue.c_str(), &p);
		ASSERT( p == NULL || *p == NULL );
		return static_cast<float>(v);
	}
	virtual std::string		GetStringProperty() override
	{
		if (m_pWnd->GetSafeHwnd())
		{
			CString val;
			m_pWnd->GetDlgItemText(m_nControlID, val);
			m_currentValue = CT2CA(val);
		}
		return m_currentValue;
	}

private:
	std::string m_currentValue;
};

//////////////////////////////////////////////////////////////////////////

GuiPropertyBag::GuiPropertyBag()
{
}

GuiPropertyBagPtr GuiPropertyBag::Create(IPropertyMap& propMap)
{
	GuiPropertyBagPtr newBag(new GuiPropertyBag);
	propMap.AddHandler(newBag);
	return newBag;
}

void GuiPropertyBag::InsertControl(PropertyId Id, GuiPropertyBag::ControlHandlerPtr p)
{
	auto res = m_Controls.emplace(  Id, std::move(p)  );
	ASSERT( res.second );
}

void GuiPropertyBag::AddButton(PropertyId Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, std::make_unique<ButtonHandler>(pWnd, nControlID ) );
}

void GuiPropertyBag::AddSlider(PropertyId Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, std::make_unique < SliderHandler>(pWnd, nControlID )  ) ;
}

void GuiPropertyBag::AddColor(PropertyId Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, std::make_unique < ColorHandler>(pWnd, nControlID )  );
}

void GuiPropertyBag::AddText(PropertyId Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, std::make_unique < TextHandler>(pWnd, nControlID )  );
}

//////////////////////////////////////////////////////////////////////////


std::optional<float>	GuiPropertyBag::GetNumericProperty(PropertyId Id)
{
	auto it = m_Controls.find( Id );
	if( it != m_Controls.end() )
	{
		return it->second->GetNumericProperty();
	}
	else
		return {};
}

std::string	GuiPropertyBag::GetStringProperty(PropertyId Id)
{
	auto it =	m_Controls.find( Id );
	if( it != m_Controls.end() )
	{
		return it->second->GetStringProperty();
	}
	else
		return {};
}