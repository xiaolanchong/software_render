#pragma once

#include "../GuiPropertyBag.h"
#include "../ColorStatic.h"

// CGeometryPage dialog

class CGeometryPage: public CPropertyPage
{
	DECLARE_DYNAMIC(CGeometryPage)

public:
	CGeometryPage(IPropertyMap& propMap);   // standard constructor

// Dialog Data
	enum { IDD = IDD_PP_GEOMETRY };

protected:
	CSliderCtrl		m_sldCylinderSeg;
	CSliderCtrl		m_sldTorusSeg;
	CSliderCtrl		m_sldTorusRing;

	CColorStatic	m_stColorDodecahedron;
	CColorStatic	m_stColorCylinder;
	CColorStatic	m_stColorTorus;

	const GuiPropertyBagPtr m_propBag;
	
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
