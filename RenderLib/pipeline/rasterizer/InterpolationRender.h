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

	std::uint8_t InterpolateByte(int v1, int v, int v2, std::uint8_t b1, std::uint8_t b2)
	{
		std::uint8_t val = InterpolateInt(v1, v, v2, b1, b2);
		assert(val >= 0);
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
		ColorType m_color;
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
	std::uint8_t r = InterpolateByte(v1, v, v2, GetR(b1.m_color), GetR(b2.m_color));
	std::uint8_t g = InterpolateByte(v1, v, v2, GetG(b1.m_color), GetG(b2.m_color));
	std::uint8_t b = InterpolateByte(v1, v, v2, GetB(b1.m_color), GetB(b2.m_color));
	int z = InterpolateInt(v1, v, v2, b1.m_z, b2.m_z);
	return InterpolatedValue{ Rgb(r, g, b), Vector2D(uc, vc), z };
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

	ColorType clTex = 0xffffffff;
	if (m_pTex)
		clTex = m_pTex->GetTexelColor(b.m_textureCoords.x, b.m_textureCoords.y);
	ColorType cf = Rgb(GetR(clTex) * GetR(b.m_color) / 255,
		               GetG(clTex) * GetG(b.m_color) / 255,
		               GetB(clTex) * GetB(b.m_color) / 255);
	m_pDC->SetPixel(x, y, cf);
}
