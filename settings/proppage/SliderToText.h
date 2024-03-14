#ifndef _SLIDER_TO_TEXT_7407280650225297_
#define _SLIDER_TO_TEXT_7407280650225297_

inline void	SetTextValue( int nStaticID, CSliderCtrl* pSlider, double MinValue, double MaxValue )
{
	int nMin, nMax;
	pSlider->GetRange(nMin, nMax);
	int nPos = pSlider->GetPos();	
	double Value = ( nPos - nMin ) * (MaxValue - MinValue)/(nMax - nMin) + MinValue;
	TCHAR buf[20];
	_sntprintf( buf, 20, _T("%2.1f"), Value );
	CWnd* pParent = pSlider->GetParent();
	ASSERT(pParent);
	if(pParent) pParent->SetDlgItemText( nStaticID, buf );
}

#endif // _SLIDER_TO_TEXT_7407280650225297_