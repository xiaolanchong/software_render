#pragma once

#include "../GuiPropertyBag.h"

class CRotateScalePage :	public CPropertyPage
{
	DECLARE_DYNAMIC(CRotateScalePage)

public:
	explicit CRotateScalePage(IComposePropertyMap& propMap);

// Dialog Data
	enum { IDD = IDD_PP_ROTATE_SCALE };

protected:
	CSliderCtrl		m_sldRotateX;
	CSliderCtrl		m_sldRotateY;
	CSliderCtrl		m_sldRotateZ;
	CSliderCtrl		m_sldScaleX;
	CSliderCtrl		m_sldScaleY;
	CSliderCtrl		m_sldScaleZ;

	const GuiPropertyBagPtr m_propBag;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnPosChange( NMHDR* , LRESULT* pRes);

	DECLARE_MESSAGE_MAP()
};
