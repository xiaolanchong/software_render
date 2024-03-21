#pragma once

#include "../../math/vector.h"
#include "../texture/ITextureSource.h"

namespace
{
	BYTE InterpolateByte(int v1, int v, int v2, BYTE b1, BYTE b2)
	{
		auto val = (b2 - b1) * (v - v1) / (v2 - v1) + b1;
		ASSERT(val >= 0);
		return static_cast<BYTE>(val);
	}

	float	InterpolateFloat(int v1, int v, int v2, float b1, float b2)
	{
		return (b2 - b1) * (v - v1) / (v2 - v1) + b1;
	}
}

//! вспомогательный рендер с интерполяцией между вершинами
//! grayscale  - изображение
//! DeviceContext functions:
//!   SetPixel(int x, int y, COLORREF color) - set the pixel color with the given coordinates
template<typename DeviceContext>
class DCBytePlotter
{
	DeviceContext* m_pDC;
public:
	DCBytePlotter(DeviceContext* pDC ) : m_pDC(pDC){}

	BYTE	Interpolate( int v1, int v, int v2, BYTE b1, BYTE b2 )
	{
		return InterpolateByte(v1, v, v2, b1, b2);
	}

	void Plot( int x, int y, BYTE cl )
	{
		m_pDC->SetPixel( x, y, RGB(cl, cl, cl ));
	}
};

//! рендер с интерполяцией цветов между вершинами грани
template<typename DeviceContext>
class DCColorPlotter
{
	DeviceContext* m_pDC;

public:
	DCColorPlotter(DeviceContext* pDC, int width, int height)
		: m_pDC(pDC)
		, m_width(width)
		, m_height(height)
	{}

	COLORREF	Interpolate( int v1, int v, int v2, COLORREF b1, COLORREF b2 )
	{
		BYTE r = InterpolateByte( v1, v, v2, GetRValue(b1), GetRValue(b2) );
		BYTE g = InterpolateByte( v1, v, v2, GetGValue(b1), GetGValue(b2) );
		BYTE b = InterpolateByte( v1, v, v2, GetBValue(b1), GetBValue(b2) );
		return RGB(r, g, b);
	}

	void Plot( int x, int y, COLORREF cl )
	{
		if (x >= m_width || y >= m_height ||
			x < 0 || y < 0)
			return;

		m_pDC->SetPixel( x, y, cl );
	}

private:
	int m_width;
	int m_height;
};

//! вспомогательный рендер, для проверки текстурных координат
template<typename DeviceContext>
class DCTextureCoordPlotter
{
protected:
	DeviceContext* m_pDC;

public:
	DCTextureCoordPlotter(DeviceContext* pDC) : m_pDC(pDC){}

	Vector2D	Interpolate( int v1, int v, int v2, 
		Vector2D b1, 
		Vector2D b2 )
	{
		float uc = InterpolateFloat( v1, v, v2, b1.x, b2.x );
		float vc = InterpolateFloat( v1, v, v2, b1.y, b2.y );
		return Vector2D( uc, vc );
	}

	void Plot( int x, int y, Vector2D cl )
	{
		if (!m_pDC)
			return;

		BYTE g;
		if		( cl.y < 0.0f)  g = 0;
		else if	( cl.y > 1.0f)	g = 255;
		else					g = BYTE(255 * cl.y);
		COLORREF c = RGB( /*255 * cl.x*/0, g, 0 );
		m_pDC->SetPixel( x, y, c );
	}
};

//! текстурный рендер, интерполирует текстурные координаты
template<typename DeviceContext>
class DCTexturePlotter : public DCTextureCoordPlotter< DeviceContext>
{
protected:
	ITextureSourcePtr m_pTex;
public:
	DCTexturePlotter(DeviceContext* pDC, ITextureSourcePtr pTex ):
		DCTextureCoordPlotter< DeviceContext>(pDC),
		  m_pTex( std::move(pTex) )
	{}

	void Plot( int x, int y, Vector2D cl )
	{
		if (!m_pDC)
			return;
		COLORREF c = m_pTex->GetTexelColor( cl.x, cl.y );
		m_pDC->SetPixel( x, y, c );
	}
};

//! текстурный рендер, интерполирует текстурные координаты и цвет вершин
template<typename DeviceContext>
class DCTextureAndColorPlotter : protected DCTexturePlotter<DeviceContext>
{
public:
	typedef std::pair< COLORREF, Vector2D> ColorAndCoord_t;

	DCTextureAndColorPlotter(DeviceContext* pDC, ITextureSourcePtr pTex, int width, int height):
	  DCTexturePlotter(pDC, std::move(pTex) )
		, m_width(width)
		, m_height(height)
	{}

	ColorAndCoord_t	Interpolate(int v1, int v, int v2,
		ColorAndCoord_t b1,
		ColorAndCoord_t b2);

	void Plot(int x, int y, ColorAndCoord_t cl);
private:
	int m_width;
	int m_height;
};

template<typename DeviceContext>
typename DCTextureAndColorPlotter<DeviceContext>::ColorAndCoord_t
DCTextureAndColorPlotter<DeviceContext>::Interpolate(int v1, int v, int v2,
	ColorAndCoord_t b1, ColorAndCoord_t b2)
{
	float uc = InterpolateFloat(v1, v, v2, b1.second.x, b2.second.x);
	float vc = InterpolateFloat(v1, v, v2, b1.second.y, b2.second.y);
	BYTE r = InterpolateByte(v1, v, v2, GetRValue(b1.first), GetRValue(b2.first));
	BYTE g = InterpolateByte(v1, v, v2, GetGValue(b1.first), GetGValue(b2.first));
	BYTE b = InterpolateByte(v1, v, v2, GetBValue(b1.first), GetBValue(b2.first));
	return std::make_pair(RGB(r, g, b), Vector2D(uc, vc));
}

template<typename DeviceContext>
void DCTextureAndColorPlotter< DeviceContext>::Plot(int x, int y, ColorAndCoord_t cl)
{
	if (!m_pDC)
		return;
	// TODO: culling better to be on the vertex level
	if (x >= m_width || y >= m_height ||
		 x < 0 || y < 0)
		return;

	COLORREF c = m_pTex->GetTexelColor(cl.second.x, cl.second.y);
	COLORREF cf = RGB(GetRValue(c) * GetRValue(cl.first) / 255,
		GetGValue(c) * GetGValue(cl.first) / 255,
		GetBValue(c) * GetBValue(cl.first) / 255);
	m_pDC->SetPixel(x, y, cf);
}
