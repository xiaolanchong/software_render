
// RenderView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "resource.h"
#include "MemDC.h"
#include "RenderView.h"

#include "settings\proppage\GeometryPage.h"
#include "settings\proppage\LightPage.h"
#include "settings\proppage\RotateScalePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRenderView

CRenderView::CRenderView()
{
}

CRenderView::~CRenderView()
{
}


BEGIN_MESSAGE_MAP(CRenderView, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_SHOW_SETTINGS, OnShowSettings )
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CRenderView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CRenderView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	
	CMemDC memDC(&dc);
	CRect rc;
	GetClientRect(&rc);
	m_sr.Render( &memDC, static_cast<WORD>(rc.Width()), static_cast<WORD>(rc.Height()), m_propMap);
}

BOOL CRenderView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

const UINT_PTR c_transformEvent		= 0xff;
const UINT	 c_transformPeriodMSec	= 100;
//const float  c_transformPeriodSec   = c_transformPeriodMSec / 1000.f;

void CRenderView::OnTimer( UINT_PTR /*nIDEvent*/)
{
	m_sr.Tick(m_propMap);
	InvalidateRect(nullptr);
}

int CRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CreateSettingsWnd();

	SetTimer(c_transformEvent, c_transformPeriodMSec, NULL);

	return 0;
}

void CRenderView::OnDestroy()
{
	m_pSheet->DestroyWindow();
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	m_Pages.clear();
	m_pSheet.reset();
}

#define SHOW_PROP_WINDOW

void CRenderView::CreateSettingsWnd()
{
	m_pSheet	= std::unique_ptr<CPropertySheet>( new CPropertySheet(IDS_SETTINGS ) );

	{
		auto page = std::make_unique<CGeometryPage>(m_propMap);
		m_Pages.push_back(std::move(page));
	}
	{
		auto page = std::make_unique<CLightPage>(m_propMap);
		m_Pages.push_back(std::move(page));
	}
	{
		auto page = std::make_unique<CRotateScalePage>(m_propMap);
		m_Pages.push_back(std::move(page));
	}

	m_pSheet->m_psh.dwFlags |= PSH_MODELESS|PSH_NOAPPLYNOW;

	for ( size_t i =0 ; i < m_Pages.size(); ++i )
	{
		m_pSheet->AddPage( m_Pages[i].get() );
	}

	m_pSheet->Create(	NULL, 
						WS_SYSMENU | WS_POPUP | WS_CAPTION | 
						DS_MODALFRAME | DS_CONTEXTHELP/* | WS_VISIBLE*/ , 
						WS_EX_TOOLWINDOW|WS_EX_TOPMOST );

	for ( size_t i =0 ; i < m_Pages.size(); ++i )
	{
		m_pSheet->SetActivePage( m_Pages[i].get() );
	}
	m_pSheet->SetActivePage( m_Pages[0].get() );
#ifdef SHOW_PROP_WINDOW
	m_pSheet->ShowWindow( SW_SHOW );
#endif
	CWnd* pWnd = AfxGetMainWnd();
	CRect rc;
	pWnd->GetWindowRect( &rc );
	m_pSheet->SetWindowPos( 0, rc.right , rc.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE );
}

LRESULT CRenderView::OnShowSettings(WPARAM w, LPARAM /*l*/)
{
#ifdef SHOW_PROP_WINDOW
	if( m_pSheet.get() )
		m_pSheet->ShowWindow( w > 0 ? SW_SHOW : SW_HIDE );
#endif
	return 0;
}
