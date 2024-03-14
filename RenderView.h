// RenderView.h : interface of the CRenderView class
//


#pragma once


class CRenderView : public CView
{
protected: // create from serialization only
	CRenderView();
	DECLARE_DYNCREATE(CRenderView)

// Attributes
public:
	CRenderDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRenderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::unique_ptr<CPropertySheet>		m_pSheet;
	std::vector<CPropertyPage*>			m_Pages;

// Generated message map functions
	virtual void	OnInitialUpdate();
	void			CreateSettingsWnd();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer( UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnShowSettings(WPARAM w, LPARAM l);
};

#ifndef _DEBUG  // debug version in RenderView.cpp
inline CRenderDoc* CRenderView::GetDocument() const
   { return reinterpret_cast<CRenderDoc*>(m_pDocument); }
#endif

