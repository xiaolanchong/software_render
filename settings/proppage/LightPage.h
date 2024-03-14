#pragma once

#include "../GuiPropertyBag.h"
#include "../ColorStatic.h"
#include "SliderToText.h"

// CLightPage dialog

class CLightPage :	public CPropertyPage,
					public GuiPropertyBag
{
	DECLARE_DYNAMIC(CLightPage)

	void	SetTextValue( int nStaticID, CSliderCtrl* pSlider, double MinValue, double MaxValue );
public:
	CLightPage();   // standard constructor
	virtual ~CLightPage();

// Dialog Data
	enum { IDD = IDD_PP_LIGHT };
protected:
	CColorStatic	m_stLightColor;

	CSliderCtrl		m_sldIntensity;
	CSliderCtrl		m_sldLightPosX;
	CSliderCtrl		m_sldLightPosY;
	CSliderCtrl		m_sldLightPosZ;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg void OnPosChange( NMHDR* pHdr, LRESULT* pRes );
	afx_msg void OnPointLight( );
};
