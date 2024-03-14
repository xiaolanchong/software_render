#ifndef _INTERPOLATION_RENDER_1724244415444253_
#define _INTERPOLATION_RENDER_1724244415444253_

#include "../../math/vector.h"
#include "../texture/ITextureSource.h"

//! вспомогательный рендер с интерполяцией между вершинами
//! grayscale  - изображение
class DCBytePlotter
{
	CDC* m_pDC;
public:
	DCBytePlotter( CDC* pDC ) : m_pDC(pDC){}

	BYTE	Interpolate( int v1, int v, int v2, BYTE b1, BYTE b2 )
	{
		return (b2 - b1 )*(v - v1)/(v2 - v1) + b1;
	}

	void Plot( int x, int y, BYTE cl )
	{
		m_pDC->SetPixel( x, y, RGB(cl, cl, cl ));
	}
};

//! рендер с интерполяцией цветов между вершинами грани
class DCColorPlotter
{
	CDC* m_pDC;

	BYTE	InterpolateByte( int v1, int v, int v2, BYTE b1, BYTE b2 )
	{
		return ( b2 - b1 )*(v - v1)/(v2 - v1) + b1;
	}
public:
	DCColorPlotter( CDC* pDC ) : m_pDC(pDC){}

	COLORREF	Interpolate( int v1, int v, int v2, COLORREF b1, COLORREF b2 )
	{
		BYTE r = InterpolateByte( v1, v, v2, GetRValue(b1), GetRValue(b2) );
		BYTE g = InterpolateByte( v1, v, v2, GetGValue(b1), GetGValue(b2) );
		BYTE b = InterpolateByte( v1, v, v2, GetBValue(b1), GetBValue(b2) );
		return RGB(r, g, b);
	}

	void Plot( int x, int y, COLORREF cl )
	{
		m_pDC->SetPixel( x, y, cl );
	}
};

//! вспомогательный рендер, для проверки текстурных координат
class DCTextureCoordPlotter
{
protected:
	CDC* m_pDC;

	float	InterpolateFloat( int v1, int v, int v2, float b1, float b2 )
	{
		return ( b2 - b1 )*(v - v1)/(v2 - v1) + b1;
	}
public:
	DCTextureCoordPlotter( CDC* pDC ) : m_pDC(pDC){}

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
		BYTE g;
		if		( cl.y < 0.0f)  g = 0;
		else if	( cl.y > 1.0f)	g = 255;
		else					g = BYTE(255 * cl.y);
		COLORREF c = RGB( /*255 * cl.x*/0, g, 0 );
		m_pDC->SetPixel( x, y, c );
	}
};

//! текстурный рендер, интерполирует текстурные координаты
class DCTexturePlotter : public DCTextureCoordPlotter
{
protected:
	std::auto_ptr<ITextureSource> m_pTex;
public:
	DCTexturePlotter( CDC* pDC,  std::auto_ptr<ITextureSource> pTex ):
		DCTextureCoordPlotter(pDC),
		  m_pTex( pTex )
	  {}

	  void Plot( int x, int y, Vector2D cl )
	  {
		  COLORREF c = m_pTex->GetTexelColor( cl.x, cl.y );
		  m_pDC->SetPixel( x, y, c );
	  }
};

//! текстурный рендер, интерполирует текстурные координаты и цвет вершин
class DCTextureAndColorPlotter : protected DCTexturePlotter
{
public:
	typedef std::pair< COLORREF, Vector2D> ColorAndCoord_t;

	DCTextureAndColorPlotter( CDC* pDC,  std::auto_ptr<ITextureSource> pTex ):
	  DCTexturePlotter(pDC, pTex )
	  {}

	  BYTE	InterpolateByte( int v1, int v, int v2, BYTE b1, BYTE b2 )
	  {
		  return ( b2 - b1 )*(v - v1)/(v2 - v1) + b1;
	  }

	  ColorAndCoord_t	Interpolate( int v1, int v, int v2, 
									 ColorAndCoord_t b1, 
									 ColorAndCoord_t b2 )
	  {
		  float uc = InterpolateFloat( v1, v, v2, b1.second.x, b2.second.x );
		  float vc = InterpolateFloat( v1, v, v2, b1.second.y, b2.second.y );
		  BYTE r  = InterpolateByte( v1, v, v2, GetRValue(b1.first), GetRValue(b2.first) );
		  BYTE g  = InterpolateByte( v1, v, v2, GetGValue(b1.first), GetGValue(b2.first) );
		  BYTE b  = InterpolateByte( v1, v, v2, GetBValue(b1.first), GetBValue(b2.first) );
		  return std::make_pair( RGB(r, g, b), Vector2D( uc, vc ) );
	  }

	  void Plot( int x, int y, ColorAndCoord_t cl )
	  {
		  COLORREF c = m_pTex->GetTexelColor( cl.second.x, cl.second.y );
		  COLORREF cf = RGB(	GetRValue(c) * GetRValue(cl.first)/255, 
								GetGValue(c) * GetGValue(cl.first)/255, 
								GetBValue(c) * GetBValue(cl.first)/255 );
		  m_pDC->SetPixel( x, y, cf );
	  }
};


#endif // _INTERPOLATION_RENDER_1724244415444253_