// GeometryPage.cpp : implementation file
//

#include "stdafx.h"
#include "../../Resource.h"
#include "GeometryPage.h"


// CGeometryPage dialog

IMPLEMENT_DYNAMIC(CGeometryPage, CPropertyPage)

CGeometryPage::CGeometryPage(IPropertyMap& propMap)
	: CPropertyPage(CGeometryPage::IDD, IDS_GEOMETRY)
	, m_propBag(GuiPropertyBag::Create(propMap))
{
}

void CGeometryPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX,  IDC_SLIDER_GEO_CYL,		m_sldCylinderSeg );
	DDX_Control(pDX,  IDC_SLIDER_GEO_TOR_SEG,	m_sldTorusSeg );
	DDX_Control(pDX,  IDC_SLIDER_GEO_TOR_RING,	m_sldTorusRing );
}


BEGIN_MESSAGE_MAP(CGeometryPage, CPropertyPage)
END_MESSAGE_MAP()


// CGeometryPage message handlers

BOOL	CGeometryPage::OnInitDialog()
{
	if ( !CPropertyPage::OnInitDialog() ) return FALSE;

	CheckDlgButton( IDC_CHECK_GEO_DOD,		BST_CHECKED );
	CheckDlgButton( IDC_CHECK_GEO_CYL,		BST_CHECKED );
	CheckDlgButton( IDC_CHECK_GEO_TORUS,	BST_CHECKED );

	m_sldCylinderSeg.SetRange( 16, 48 );
	m_sldTorusSeg.SetRange( 16, 48 );
	m_sldTorusRing.SetRange( 16, 48 );

	m_sldCylinderSeg.SetPos( 32 );
	m_sldTorusSeg.SetPos( 32 );
	m_sldTorusRing.SetPos( 32 );

	m_stColorDodecahedron.SubclassDlgItem( IDC_STATIC_GEO_DOD, this );
	m_stColorCylinder.SubclassDlgItem( IDC_STATIC_GEO_CYL, this );
	m_stColorTorus.SubclassDlgItem( IDC_STATIC_GEO_TORUS, this );

	m_stColorDodecahedron.SetColor( RGB( 255, 0, 0) );
	m_stColorCylinder.SetColor( RGB( 0, 255, 0) );
	m_stColorTorus.SetColor( RGB( 0, 0, 255) );

	m_propBag->AddButton(  prop_geo_dodecahedron_enable,	this, ( IDC_CHECK_GEO_DOD ) );
	m_propBag->AddButton(	prop_geo_cylinder_enable,		this, ( IDC_CHECK_GEO_CYL ) );
	m_propBag->AddButton(	prop_geo_torus_enable,			this, ( IDC_CHECK_GEO_TORUS ) );

	m_propBag->AddSlider(  prop_geo_cylinder_segments,	this, ( IDC_SLIDER_GEO_CYL ) );
	m_propBag->AddSlider(	prop_geo_torus_segments,	this, ( IDC_SLIDER_GEO_TOR_SEG ) );
	m_propBag->AddSlider(	prop_geo_torus_rings,		this, ( IDC_SLIDER_GEO_TOR_RING ) );

	m_propBag->AddButton(	prop_geo_wireframe,			this, ( IDC_RADIO_GEO_WIRE ) );
	m_propBag->AddButton(prop_geo_fill, this, (IDC_RADIO_GEO_FILL));
	m_propBag->AddButton(prop_geo_fill_and_textures, this, (IDC_RADIO_GEO_TEXTURE));

	m_propBag->AddColor(  prop_geo_dodecahedron_color,		this, IDC_STATIC_GEO_DOD );
	m_propBag->AddColor(  prop_geo_cylinder_color,		this, IDC_STATIC_GEO_CYL );
	m_propBag->AddColor(  prop_geo_torus_color,		this, IDC_STATIC_GEO_TORUS );

	CheckDlgButton(IDC_RADIO_GEO_FILL, BST_CHECKED);

	return TRUE;
}

// IPropertyHandler
