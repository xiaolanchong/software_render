// RenderView.cpp : implementation of the CRenderView class
//

#include "stdafx.h"
#include "Render.h"

#include "RenderDoc.h"
#include "RenderView.h"
#include "MemDC.h"
#include ".\renderview.h"

#include "settings\proppage\GeometryPage.h"
#include "settings\proppage\LightPage.h"
#include "settings\proppage\RotateScalePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRenderView

IMPLEMENT_DYNCREATE(CRenderView, CView)

BEGIN_MESSAGE_MAP(CRenderView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_SHOW_SETTINGS, OnShowSettings )
END_MESSAGE_MAP()

// CRenderView construction/destruction

CRenderView::CRenderView()
{
	// TODO: add construction code here

}

CRenderView::~CRenderView()
{
}

BOOL CRenderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRenderView drawing

void CRenderView::OnDraw(CDC* pDC)
{
	CRenderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CMemDC memDC(pDC);
	CRect rc;
	GetClientRect(rc);
	GetDocument()->Draw( &memDC, static_cast<WORD>(rc.Width()), static_cast<WORD>(rc.Height()) );
}


// CRenderView printing

BOOL CRenderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRenderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRenderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRenderView diagnostics

#ifdef _DEBUG
void CRenderView::AssertValid() const
{
	CView::AssertValid();
}

void CRenderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRenderDoc* CRenderView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRenderDoc)));
	return (CRenderDoc*)m_pDocument;
}
#endif //_DEBUG


// CRenderView message handlers

BOOL CRenderView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;//CView::OnEraseBkgnd(pDC);
}

UINT_PTR Timer_Draw		= 0xff;
UINT	 Period_Draw	= 100; 

void CRenderView::OnTimer( UINT_PTR /*nIDEvent*/)
{
	GetDocument()->Tick( Period_Draw );
}

void	CRenderView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CreateSettingsWnd();

	SetTimer( Timer_Draw, Period_Draw, NULL );
}
void CRenderView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	for ( size_t i =0; i < m_Pages.size() ; ++i )
	{
		delete m_Pages[i];
	}
	m_pSheet.reset();
}

#define SHOW_PROP_WINDOW

void CRenderView::CreateSettingsWnd()
{
	m_pSheet	= std::unique_ptr<CPropertySheet>( new CPropertySheet(IDS_SETTINGS ) );
	m_Pages.push_back( new CGeometryPage( ) ) ;
	m_Pages.push_back( new CLightPage(  ) ) ;
	m_Pages.push_back( new CRotateScalePage(  ) ) ;

	m_pSheet->m_psh.dwFlags |= PSH_MODELESS|PSH_NOAPPLYNOW;

	for ( size_t i =0 ; i < m_Pages.size(); ++i )
	{
		m_pSheet->AddPage( m_Pages[i] );
	}

	m_pSheet->Create(	NULL, 
						WS_SYSMENU | WS_POPUP | WS_CAPTION | 
						DS_MODALFRAME | DS_CONTEXTHELP/* | WS_VISIBLE*/ , 
						WS_EX_TOOLWINDOW|WS_EX_TOPMOST );

	for ( size_t i =0 ; i < m_Pages.size(); ++i )
	{
		m_pSheet->SetActivePage( m_Pages[i] );
	}
	m_pSheet->SetActivePage( m_Pages[0] );
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
