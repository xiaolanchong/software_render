#include "stdafx.h"
#include "InterpolationRender.h"

DCTextureAndColorPlotter::ColorAndCoord_t DCTextureAndColorPlotter::Interpolate(int v1, int v, int v2,
	ColorAndCoord_t b1,
	ColorAndCoord_t b2)
{
	float uc = InterpolateFloat(v1, v, v2, b1.second.x, b2.second.x);
	float vc = InterpolateFloat(v1, v, v2, b1.second.y, b2.second.y);
	BYTE r = InterpolateByte(v1, v, v2, GetRValue(b1.first), GetRValue(b2.first));
	BYTE g = InterpolateByte(v1, v, v2, GetGValue(b1.first), GetGValue(b2.first));
	BYTE b = InterpolateByte(v1, v, v2, GetBValue(b1.first), GetBValue(b2.first));
	return std::make_pair(RGB(r, g, b), Vector2D(uc, vc));
}

void DCTextureAndColorPlotter::Plot(int x, int y, ColorAndCoord_t cl)
{
	if (!m_pDC)
		return;

	COLORREF c = m_pTex->GetTexelColor(cl.second.x, cl.second.y);
	COLORREF cf = RGB(GetRValue(c) * GetRValue(cl.first) / 255,
		GetGValue(c) * GetGValue(cl.first) / 255,
		GetBValue(c) * GetBValue(cl.first) / 255);
	m_pDC->SetPixel(x, y, cf);
}
