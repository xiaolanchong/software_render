#include "stdafx.h"
#include "GuiPropertyBag.h"
#include "ColorStatic.h"

//////////////////////////////////////////////////////////////////////////

class ButtonHandler : public GuiPropertyBag::ControlHandler
{
public:
	ButtonHandler( CWnd* pWnd, UINT nControlID  ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty()
	{
		bool b = m_pWnd ->IsDlgButtonChecked(m_nControlID) != 0;//BST_CHECKED;
		return b ? 1.0f : 0.0f;
	}
	virtual CString		GetStringProperty()
	{
		ASSERT(FALSE);
		return CString();
	}
};

//////////////////////////////////////////////////////////////////////////

class SliderHandler : public GuiPropertyBag::ControlHandler
{
public:
	SliderHandler( CWnd* pWnd, UINT nControlID ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty()
	{
		CSliderCtrl* pSlider = static_cast< CSliderCtrl* >( m_pWnd->GetDlgItem( m_nControlID ) );
		ASSERT(pSlider);
		int b = pSlider->GetPos(  );
		return float(b);
	}
	virtual CString		GetStringProperty()
	{
		ASSERT(FALSE);
		return CString();
	}
};

//////////////////////////////////////////////////////////////////////////

class ColorHandler : public GuiPropertyBag::ControlHandler
{
public:
	ColorHandler( CWnd* pWnd, UINT nControlID ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty()
	{
		CColorStatic* pSlider = static_cast< CColorStatic* >( m_pWnd->GetDlgItem( m_nControlID ) );
		ASSERT(pSlider);
		COLORREF b = pSlider->GetColor(  );
		return float(b);
	}
	virtual CString		GetStringProperty()
	{
		ASSERT(FALSE);
		return CString();
	}
};

//////////////////////////////////////////////////////////////////////////

class TextHandler : public GuiPropertyBag::ControlHandler
{
public:
	TextHandler( CWnd* pWnd, UINT nControlID ) : ControlHandler( pWnd, nControlID ){}
	virtual float		GetNumericProperty()
	{
		CString sText;
		m_pWnd->GetDlgItemText( m_nControlID, sText );
		TCHAR* p = NULL;
		double v = _tcstod( sText, &p );
		ASSERT( p == NULL || *p == NULL );
		return float(v);
	}
	virtual CString		GetStringProperty()
	{
		CString sText;
		m_pWnd->GetDlgItemText( m_nControlID, sText );
		return sText;
	}
};

//////////////////////////////////////////////////////////////////////////

GuiPropertyBag::GuiPropertyBag()
{
	GetPropertyMap()->AddHandler( this );
}

struct  DeleteMapMem
{
	void  operator () ( const std::pair< DWORD, GuiPropertyBag::ControlHandler* >& p ) const
	{
		delete p.second;
	}
};

GuiPropertyBag::~GuiPropertyBag()
{
	std::for_each( m_Controls.begin(), m_Controls.end(), DeleteMapMem() );
}

void GuiPropertyBag::InsertControl(DWORD Id, ControlHandler* p)
{
	std::pair< std::map< DWORD, GuiPropertyBag::ControlHandler* >::iterator, bool >
		res = m_Controls.insert( std::make_pair( Id, p  ) );
	ASSERT( res.second );
}

void GuiPropertyBag::AddButton( DWORD Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, new ButtonHandler(pWnd, nControlID ) );
}

void GuiPropertyBag::AddSlider( DWORD Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, new SliderHandler(pWnd, nControlID )  ) ;
}

void GuiPropertyBag::AddColor( DWORD Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, new ColorHandler(pWnd, nControlID )  );
}

void GuiPropertyBag::AddText( DWORD Id, CWnd* pWnd, UINT nControlID )
{
	InsertControl( Id, new TextHandler(pWnd, nControlID )  );
}

//////////////////////////////////////////////////////////////////////////


std::pair<bool, float>		GuiPropertyBag::GetNumericProperty(DWORD Id)
{
	std::map< DWORD, ControlHandler* >::iterator it =
		m_Controls.find( Id );
	if( it != m_Controls.end() )
	{
		return std::make_pair( true, it->second->GetNumericProperty() );
	}
	else
		return std::make_pair( false, float() );
}

std::pair<bool, CString>	GuiPropertyBag::GetStringProperty(DWORD Id)
{
	std::map< DWORD, ControlHandler* >::iterator it =
		m_Controls.find( Id );
	if( it != m_Controls.end() )
	{
		return std::make_pair( true, it->second->GetStringProperty() );
	}
	else
		return std::make_pair( false, CString() );
}