
// RenderView.h : interface of the CChildView class
//

#pragma once

#include "scene/SceneRender.h"
#include "settings/PropertyMapImpl.h"

// CRenderView window

class CRenderView : public CWnd
{
// Construction
public:
	CRenderView();

// Attributes
private:
	using CPropertyPagePtr = std::unique_ptr<CPropertyPage>;

	std::unique_ptr<CPropertySheet>		m_pSheet;
	std::vector<CPropertyPagePtr>			m_Pages;
	PropertyMapImpl m_propMap;
	SceneRender m_sr;

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

	//virtual void	OnInitialUpdate() override;
	void			CreateSettingsWnd();
// Implementation
public:
	virtual ~CRenderView();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer( UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnShowSettings(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()
};

