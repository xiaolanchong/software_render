// RotateScale.cpp : implementation file
//

#include "stdafx.h"
#include "../../Render.h"
#include "RotateScalePage.h"
#include "SliderToText.h"

// CRotateScale dialog

IMPLEMENT_DYNAMIC(CRotateScalePage, CPropertyPage)

CRotateScalePage::CRotateScalePage(IPropertyMap& propMap)
	: CPropertyPage(CRotateScalePage::IDD, IDS_ROTATE_SCALE)
	, m_propBag(GuiPropertyBag::Create(propMap))
{
}

void CRotateScalePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control( pDX, IDC_SLIDER_RS_ROTATE_X, m_sldRotateX );
	DDX_Control( pDX, IDC_SLIDER_RS_ROTATE_Y, m_sldRotateY );
	DDX_Control( pDX, IDC_SLIDER_RS_ROTATE_Z, m_sldRotateZ );
	DDX_Control( pDX, IDC_SLIDER_RS_SCALE_X, m_sldScaleX );
	DDX_Control( pDX, IDC_SLIDER_RS_SCALE_Y, m_sldScaleY );
	DDX_Control( pDX, IDC_SLIDER_RS_SCALE_Z, m_sldScaleZ );
}


BEGIN_MESSAGE_MAP(CRotateScalePage, CPropertyPage)
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_RS_ROTATE_X, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_RS_ROTATE_Y, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_RS_ROTATE_Z, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_RS_SCALE_X, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_RS_SCALE_Y, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_RS_SCALE_Z, OnPosChange )
END_MESSAGE_MAP()


// CRotateScalePage message handlers

BOOL CRotateScalePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_sldRotateX.SetRange( 0, 20 );
	m_sldRotateY.SetRange( 0, 20 );
	m_sldRotateZ.SetRange( 0, 20 );
	m_sldScaleX.SetRange( 0, 20 );
	m_sldScaleY.SetRange( 0, 20 );
	m_sldScaleZ.SetRange( 0, 20 );

	m_sldRotateX.SetPos( 10 );
	m_sldRotateY.SetPos( 10 );
	m_sldRotateZ.SetPos( 10 );
	m_sldScaleX.SetPos( 9 );
	m_sldScaleY.SetPos( 9 );
	m_sldScaleZ.SetPos( 9 );

	CheckDlgButton( IDC_RADIO_RS_SIMPLE, BST_CHECKED );

	m_propBag->AddText(  prop_rs_rotate_x,	this, IDC_EDIT_RS_ROTATE_X );
	m_propBag->AddText(  prop_rs_rotate_y,	this, IDC_EDIT_RS_ROTATE_Y );
	m_propBag->AddText(  prop_rs_rotate_z,	this, IDC_EDIT_RS_ROTATE_Z );
	m_propBag->AddText(  prop_rs_scale_x,	this, IDC_EDIT_RS_SCALE_X );
	m_propBag->AddText(  prop_rs_scale_y,	this, IDC_EDIT_RS_SCALE_Y );
	m_propBag->AddText(  prop_rs_scale_z,	this, IDC_EDIT_RS_SCALE_Z );

	m_sldRotateY.SetPos(15);

	LRESULT z;
	OnPosChange(0, &z);
	return TRUE;
}

void CRotateScalePage::OnPosChange( NMHDR* , LRESULT* pRes)
{
	SetTextValue( IDC_EDIT_RS_ROTATE_X, &m_sldRotateX, -20.0, 20.0 );
	SetTextValue( IDC_EDIT_RS_ROTATE_Y, &m_sldRotateY, -20.0, 20.0 );
	SetTextValue( IDC_EDIT_RS_ROTATE_Z, &m_sldRotateZ, -20.0, 20.0 );
	SetTextValue( IDC_EDIT_RS_SCALE_X, &m_sldScaleX, 0.2, 2.0 );
	SetTextValue( IDC_EDIT_RS_SCALE_Y, &m_sldScaleY, 0.2, 2.0 );
	SetTextValue( IDC_EDIT_RS_SCALE_Z, &m_sldScaleZ, 0.2, 2.0 );

	*pRes = FALSE;
}