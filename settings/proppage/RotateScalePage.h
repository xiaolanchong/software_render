#pragma once

#include "../GuiPropertyBag.h"
// CRotateScalePage dialog

class CRotateScalePage :	public CPropertyPage,
							public GuiPropertyBag
{
	DECLARE_DYNAMIC(CRotateScalePage)

public:
	CRotateScalePage();   // standard constructor
	virtual ~CRotateScalePage();

// Dialog Data
	enum { IDD = IDD_PP_ROTATE_SCALE };
protected:
	CSliderCtrl		m_sldRotateX;
	CSliderCtrl		m_sldRotateY;
	CSliderCtrl		m_sldRotateZ;
	CSliderCtrl		m_sldScaleX;
	CSliderCtrl		m_sldScaleY;
	CSliderCtrl		m_sldScaleZ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnPosChange( NMHDR* , LRESULT* pRes);

	DECLARE_MESSAGE_MAP()
};
