// ColorStatic.cpp : implementation file
//



#include "stdafx.h"
#include "ColorStatic.h"
#define USE_COLOR_DLG
//#include "Settings.h"
#ifndef USE_COLOR_DLG
#include "ut/OXColorPickerCtrl.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic(COLORREF cl) : m_clCurrent(cl)
{
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers

void CColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
	CRect rcClient;
	GetClientRect( &rcClient );

	CRect rcArea = GetColorRect();
	CRect rcText = GetTextRect();

	dc.DrawFrameControl( rcArea,  DFC_BUTTON, DFCS_BUTTONCHECK);
	rcArea.DeflateRect( 2, 2 );
	dc.FillSolidRect( &rcArea, m_clCurrent );

	CString str; 
	GetWindowText(str);
	dc.SetBkMode( TRANSPARENT );
	CFont * pFont = GetFont();
	CGdiObject* pOldFont = dc.SelectObject( pFont );
	dc.DrawText( str, &rcText, DT_SINGLELINE |DT_LEFT |DT_VCENTER );
	dc.SelectObject( pOldFont );
}

CRect	CColorStatic::GetTextRect()
{
	const int nGap = 3;
	CRect rcClient;
	GetClientRect( &rcClient );
	CRect rcArea(rcClient);
	rcArea.left += rcClient.Height() + nGap;
	return rcArea;
}

CRect CColorStatic::GetColorRect()
{
	CRect rcClient;
	GetClientRect( &rcClient );
	CRect rcArea(rcClient);
	rcArea.right = rcArea.left + rcArea.Height();

	return rcArea;
}

void CColorStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default


	CRect rcArea = GetColorRect();

	COLORREF	clRgb = m_clCurrent;

#ifdef USE_COLOR_DLG
	CColorDialog dlg( clRgb, 0, this) ;

	if( rcArea.PtInRect( point ) && dlg.DoModal() == IDOK )
	{
		COLORREF	clRgb = dlg.GetColor();
		m_clCurrent = clRgb;
		Invalidate();
	}
#else
	COXColorPickerCtrl wndPicker( 42, 6, clRgb, CSize(18,18), _T( "Default"), _T("Custom...") ) ;
	wndPicker.Create( this );
	wndPicker.SetSelectedColor( clRgb );
	if( wndPicker.Pick(  ) )
	{
		COLORREF	clRgb = wndPicker.GetSelectedColor();
		Color		cl;
		cl.SetFromCOLORREF(clRgb);
		GetSettings().SetProperty( m_dwNumber, cl.GetValue() );
		Invalidate();
	}
#endif	


	CStatic::OnLButtonDown(nFlags, point);
}

void CColorStatic::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle( 0, SS_NOTIFY );
	CStatic::PreSubclassWindow();
}
