#pragma once

#include "../../math/vector.h"
#include "../texture/ITextureSource.h"

namespace
{
	template<typename IntType>
	IntType InterpolateInt(int v1, int v, int v2, IntType b1, IntType b2)
	{
		auto val = (b2 - b1) * (v - v1) / (v2 - v1) + b1;
		return static_cast<IntType>(val);
	}

	BYTE InterpolateByte(int v1, int v, int v2, BYTE b1, BYTE b2)
	{
		BYTE val = InterpolateInt(v1, v, v2, b1, b2);
		ASSERT(val >= 0);
		return val;
	}

	float	InterpolateFloat(int v1, int v, int v2, float b1, float b2)
	{
		return (b2 - b1) * (v - v1) / (v2 - v1) + b1;
	}
}

//! текстурный рендер, интерполирует текстурные координаты и цвет вершин
template<typename DeviceContext>
class DCTextureAndColorPlotter
{
public:
	struct InterpolatedValue
	{
		COLORREF m_color;
		Vector2D m_textureCoords;
		int m_z;
	};

	DCTextureAndColorPlotter(DeviceContext* pDC, ITextureSourcePtr pTex, int width, int height)
		: m_pDC(pDC)
		, m_width(width)
		, m_height(height)
		, m_pTex(std::move(pTex))
	{}

	InterpolatedValue	Interpolate(int v1, int v, int v2,
		const InterpolatedValue& b1, const InterpolatedValue& b2);

	void Plot(int x, int y, const InterpolatedValue& b);

	void SetTexture(ITextureSourcePtr pTex) { m_pTex = std::move(pTex); };
private:
	int m_width;
	int m_height;
	ITextureSourcePtr m_pTex;
	DeviceContext* m_pDC;
};

template<typename DeviceContext>
typename DCTextureAndColorPlotter<DeviceContext>::InterpolatedValue
DCTextureAndColorPlotter<DeviceContext>::Interpolate(int v1, int v, int v2,
	const InterpolatedValue& b1, const InterpolatedValue& b2)
{
	float uc = InterpolateFloat(v1, v, v2, b1.m_textureCoords.x, b2.m_textureCoords.x);
	float vc = InterpolateFloat(v1, v, v2, b1.m_textureCoords.y, b2.m_textureCoords.y);
	BYTE r = InterpolateByte(v1, v, v2, GetRValue(b1.m_color), GetRValue(b2.m_color));
	BYTE g = InterpolateByte(v1, v, v2, GetGValue(b1.m_color), GetGValue(b2.m_color));
	BYTE b = InterpolateByte(v1, v, v2, GetBValue(b1.m_color), GetBValue(b2.m_color));
	int z = InterpolateInt(v1, v, v2, b1.m_z, b2.m_z);
	return InterpolatedValue{ RGB(r, g, b), Vector2D(uc, vc), z };
}

template<typename DeviceContext>
void DCTextureAndColorPlotter< DeviceContext>::Plot(int x, int y, const InterpolatedValue& b)
{
	if (!m_pDC)
		return;
	// TODO: culling better to be on the vertex level
	if (x >= m_width || y >= m_height ||
		 x < 0 || y < 0)
		return;

	COLORREF clTex = 0xffffffff;
	if (m_pTex)
		clTex = m_pTex->GetTexelColor(b.m_textureCoords.x, b.m_textureCoords.y);
	COLORREF cf = RGB(GetRValue(clTex) * GetRValue(b.m_color) / 255,
		               GetGValue(clTex) * GetGValue(b.m_color) / 255,
		               GetBValue(clTex) * GetBValue(b.m_color) / 255);
	m_pDC->SetPixel(x, y, cf);
}
