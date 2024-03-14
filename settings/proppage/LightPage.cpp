// LightPage.cpp : implementation file
//

#include "stdafx.h"
#include "../../Resource.h"
#include "LightPage.h"


// CLightPage dialog

IMPLEMENT_DYNAMIC(CLightPage, CPropertyPage)
CLightPage::CLightPage( /*=NULL*/)
	: CPropertyPage(CLightPage::IDD, IDS_LIGHT )
{
}

CLightPage::~CLightPage()
{
}

void CLightPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX,  IDC_SLIDER_LIGHT_INTENSITY,		m_sldIntensity );
	DDX_Control(pDX,  IDC_SLIDER_LIGHT_POS_X,	m_sldLightPosX );
	DDX_Control(pDX,  IDC_SLIDER_LIGHT_POS_Y,	m_sldLightPosY );
	DDX_Control(pDX,  IDC_SLIDER_LIGHT_POS_Z,	m_sldLightPosZ );
}


BEGIN_MESSAGE_MAP(CLightPage, CPropertyPage)
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_LIGHT_POS_X, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_LIGHT_POS_Y, OnPosChange )
	ON_NOTIFY( NM_CUSTOMDRAW , IDC_SLIDER_LIGHT_POS_Z, OnPosChange )
	ON_COMMAND( IDC_RADIO_LIGHT_POINT, OnPointLight )
	ON_COMMAND( IDC_RADIO_LIGHT_DIRECTION, OnPointLight )
END_MESSAGE_MAP()

void	CLightPage::SetTextValue( int nStaticID, CSliderCtrl* pSlider, double MinValue, double MaxValue )
{
	int nMin, nMax;
	pSlider->GetRange(nMin, nMax);
	int nPos = pSlider->GetPos();	
	double Value = ( nPos - nMin ) * (MaxValue - MinValue)/(nMax - nMin) + MinValue;
	TCHAR buf[20] = {};
	_sntprintf_s( buf, 20, _T("%2.1f"), Value );
	SetDlgItemText( nStaticID, buf );
}

// CLightPage message handlers
BOOL	CLightPage::OnInitDialog()
{
	if ( !CPropertyPage::OnInitDialog() ) return FALSE;

	CheckDlgButton( IDC_RADIO_LIGHT_GOURAUD,		BST_CHECKED );
	CheckDlgButton( IDC_RADIO_LIGHT_POINT,			BST_CHECKED );

	m_sldIntensity.SetRange( 0, 20 );
	m_sldLightPosX.SetRange( 0, 20 );
	m_sldLightPosY.SetRange( 0, 20 );
	m_sldLightPosZ.SetRange( 0, 20 );

	m_sldIntensity.SetPos( 15 );
	m_sldLightPosX.SetPos( 10 );
	m_sldLightPosY.SetPos( 10 );
	m_sldLightPosZ.SetPos( 0 );

	m_stLightColor.SubclassDlgItem( IDC_STATIC_LIGHT_COLOR, this );
	m_stLightColor.SetColor( RGB( 255, 255, 255 ) );

	AddButton(  prop_light_lambert,	this, IDC_RADIO_LIGHT_LAMBERT	);
	AddButton(  prop_light_gouraud,	this, IDC_RADIO_LIGHT_GOURAUD	);
	AddButton(  prop_light_phong,	this, IDC_RADIO_LIGHT_PHONG		);

	AddButton(  prop_light_direct,	this, IDC_RADIO_LIGHT_DIRECTION );
	AddButton(  prop_light_point,	this, IDC_RADIO_LIGHT_POINT );

	AddColor(	prop_light_color,		this, IDC_STATIC_LIGHT_COLOR );

	AddSlider(  prop_light_intensity,	this, IDC_SLIDER_LIGHT_INTENSITY );
	AddText(  prop_light_pos_x,	this, IDC_EDIT_LIGHT_POS_X );
	AddText(  prop_light_pos_y,	this, IDC_EDIT_LIGHT_POS_Y );
	AddText(  prop_light_pos_z,	this, IDC_EDIT_LIGHT_POS_Z );

	LRESULT z;
	OnPosChange( 0, &z  );
	return TRUE;
}

//HACK
void CLightPage::OnPosChange( NMHDR* /*pHdr*/, LRESULT* pRes)
{
	SetTextValue( IDC_EDIT_LIGHT_POS_X, &m_sldLightPosX, -5.0, 5.0 );
	SetTextValue( IDC_EDIT_LIGHT_POS_Y, &m_sldLightPosY, -5.0, 5.0 );
	SetTextValue( IDC_EDIT_LIGHT_POS_Z, &m_sldLightPosZ, -5.0, 5.0 );

	*pRes = FALSE;
}

void CLightPage::OnPointLight(  )
{
	UINT nID[] = 
	{
		IDC_EDIT_LIGHT_POS_X,
		IDC_EDIT_LIGHT_POS_Y,
		IDC_EDIT_LIGHT_POS_Z,
		IDC_SLIDER_LIGHT_POS_X,
		IDC_SLIDER_LIGHT_POS_Y,
		IDC_SLIDER_LIGHT_POS_Z,
		IDC_SLIDER_LIGHT_INTENSITY
	//	IDC_STATIC_LIGHT_COLOR,
	};
	BOOL bEnable = ( IsDlgButtonChecked( IDC_RADIO_LIGHT_POINT ) == BST_CHECKED );
	for ( size_t i =0; i < sizeof(nID)/sizeof(nID[0]);++i )
	{
		GetDlgItem(nID[i])->EnableWindow( bEnable );
	}
}