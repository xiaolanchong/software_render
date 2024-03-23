
// RenderView.h : interface of the CChildView class
//

#pragma once

#include "RenderLib/ISceneRender.h"
#include "settings/PropertyMapImpl.h"

// CRenderView window

class CRenderView : public CWnd
{
public:
	~CRenderView() override;

protected:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer( UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateTogglePropertyWindow(CCmdUI* pCmdUI);
	afx_msg void TogglePropertyWindow();
	DECLARE_MESSAGE_MAP()

private:
	void CreatePropertyWindow(bool visible);

private:
	using CPropertyPagePtr = std::unique_ptr<CPropertyPage>;

	std::unique_ptr<CPropertySheet>		m_pSheet;
	std::vector<CPropertyPagePtr>			m_Pages;
	PropertyMapImpl m_propMap;
	ISceneRenderPtr m_sr;
};

