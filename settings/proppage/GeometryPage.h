#pragma once

#include "../GuiPropertyBag.h"
#include "../ColorStatic.h"

// CGeometryPage dialog

class CGeometryPage :	public CPropertyPage, 
						public GuiPropertyBag
{
	DECLARE_DYNAMIC(CGeometryPage)

public:
	CGeometryPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGeometryPage();

	virtual void						Notify( DWORD dwID )			;
//	virtual std::pair<bool, float>		GetNumericProperty(DWORD Id)	;
//	virtual std::pair<bool, CString>	GetStringProperty(DWORD Id)		;

// Dialog Data
	enum { IDD = IDD_PP_GEOMETRY };

protected:
	CSliderCtrl		m_sldCylinderSeg;
	CSliderCtrl		m_sldTorusSeg;
	CSliderCtrl		m_sldTorusRing;

	CColorStatic	m_stColorDodecahedron;
	CColorStatic	m_stColorCylinder;
	CColorStatic	m_stColorTorus;
	

	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
