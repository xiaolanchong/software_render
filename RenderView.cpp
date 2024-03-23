
// RenderView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "resource.h"
#include "MemDC.h"
#include "GdiDeviceContext.h"
#include "RenderView.h"
#include "RenderLib/RenderLib.h"

#include "settings/proppage/GeometryPage.h"
#include "settings/proppage/LightPage.h"
#include "settings/proppage/RotateScalePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRenderView::~CRenderView()
{
}

BEGIN_MESSAGE_MAP(CRenderView, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_PROPERTYWINDOW, TogglePropertyWindow)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOW, OnUpdateTogglePropertyWindow)
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
	
	CMemDC memDC(&dc);
	CRect rc;
	GetClientRect(&rc);
	GdiDeviceContext devCon(memDC);
	m_sr->Render(devCon, static_cast<unsigned int>(rc.Width()), static_cast<unsigned int>(rc.Height()), m_propMap);
}

BOOL CRenderView::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

const UINT_PTR c_transformEvent		= 0xff;
const auto c_fps = 30;
const UINT	 c_transformPeriodMSec	= 1000 / c_fps;

void CRenderView::OnTimer( UINT_PTR /*nIDEvent*/)
{
	m_sr->Tick(m_propMap);
	InvalidateRect(nullptr);
}

int CRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_sr = CreateRender();
	CreatePropertyWindow(true);
	SetTimer(c_transformEvent, c_transformPeriodMSec, NULL);
	return 0;
}

void CRenderView::OnDestroy()
{
	m_pSheet->DestroyWindow();
	CWnd::OnDestroy();

	m_Pages.clear();
	m_pSheet.reset();
}

void CRenderView::CreatePropertyWindow(bool visible)
{
	m_Pages.clear();
	m_pSheet	= std::make_unique<CPropertySheet>(IDS_SETTINGS );

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
						DS_MODALFRAME | DS_CONTEXTHELP, 
						WS_EX_TOOLWINDOW|WS_EX_TOPMOST );

	for ( size_t i =0 ; i < m_Pages.size(); ++i )
	{
		m_pSheet->SetActivePage( m_Pages[i].get() );
	}
	m_pSheet->SetActivePage( m_Pages[0].get() );

	m_pSheet->ShowWindow( visible ? SW_SHOW : SW_HIDE );

	CWnd* pWnd = AfxGetMainWnd();
	CRect rc;
	pWnd->GetWindowRect( &rc );
	m_pSheet->SetWindowPos( 0, rc.right , rc.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE );
}

void CRenderView::OnUpdateTogglePropertyWindow(CCmdUI* pCmdUI)
{
	if (m_pSheet.get())
	{
		if (m_pSheet->GetSafeHwnd())
			pCmdUI->SetCheck(m_pSheet->IsWindowVisible() ? BST_CHECKED : BST_UNCHECKED);
		else
		{
			m_pSheet = nullptr;
			pCmdUI->SetCheck(BST_UNCHECKED);
		}
	}
		
	else
		pCmdUI->SetCheck(BST_UNCHECKED);
}

void CRenderView::TogglePropertyWindow()
{
	if (m_pSheet.get())
		m_pSheet->ShowWindow(!m_pSheet->IsWindowVisible() ? SW_SHOW : SW_HIDE);
	else
		CreatePropertyWindow(true);
}