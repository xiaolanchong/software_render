#ifndef _I_RASTERIZER_3781606653240254_
#define _I_RASTERIZER_3781606653240254_

#include "../../math/Face.h"

struct  ColorFace
{
	Vector		Vertices[3];
	COLORREF	Color[3];
	Vector2D	TexCoord[3];

	ColorFace(	const Vector& v1, const Vector& v2, const Vector& v3,
				COLORREF c1, COLORREF c2, COLORREF c3 ,
				const Vector2D& t1, 
				const Vector2D& t2, 
				const Vector2D& t3)
	{
		Vertices[0] = v1;
		Vertices[1] = v2;
		Vertices[2] = v3;
		Color[0]	= c1;
		Color[1]	= c2;
		Color[2]	= c3;
		TexCoord[0]	= t1;
		TexCoord[1]	= t2;
		TexCoord[2]	= t3;
	}
};

typedef		std::vector<ColorFace>	ColorMesh_t;

class IRasterizer
{	
protected:
	CPoint Trans2Viewport( WORD w, WORD h, const Vector& v )
	{
		return CPoint( int(w/2 + w/2 * v.x), int(h/2 - h/2 * v.y ) );
	}
	struct CompareFaces
	{
		bool operator() (	const ColorFace& f1, 
			const ColorFace& f2 ) const
		{
			float z1 = ( f1.Vertices[0].z + f1.Vertices[1].z + f1.Vertices[2].z  ); // /3
			float z2 = ( f2.Vertices[0].z + f2.Vertices[1].z + f2.Vertices[2].z  ); // /3
			return z1 < z2;
		}
	};

	void	PainterAlgoSort( ColorMesh_t& Mesh )
	{
		std::sort( Mesh.begin(), Mesh.end(), CompareFaces() );
	}
public:
	virtual void Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h ) = 0;
	virtual ~IRasterizer() {};
};

#endif // _I_RASTERIZER_3781606653240254_