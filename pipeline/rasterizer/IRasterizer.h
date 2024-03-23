#pragma once

#include "../../math/Face.h"
#include "../texture/ITextureSource.h"
#include "../IDeviceContext.h"

using TextureIndex = unsigned int;
constexpr TextureIndex NO_TEXTURE = 0;
constexpr TextureIndex TEXTURE_0 = 1;
constexpr TextureIndex TEXTURE_1 = 2;
constexpr TextureIndex TEXTURE_2 = 3;

struct  ColorFace
{
	Vector		Vertices[3];
	COLORREF	Color[3];
	Vector2D	TexCoord[3];
	TextureIndex m_texture;

	ColorFace(	const Vector& v1, const Vector& v2, const Vector& v3,
				COLORREF c1, COLORREF c2, COLORREF c3 ,
				const Vector2D& t1, const Vector2D& t2, const Vector2D& t3,
				TextureIndex texture)
		: m_texture(texture)
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

using ColorMesh_t = std::vector<ColorFace>;

class IRasterizer
{	
protected:
	static CPoint Trans2Viewport(unsigned int w, unsigned int h, const Vector& v )
	{
		return CPoint( int(w/2 + w/2 * v.x), int(h/2 - h/2 * v.y ) );
	}
	struct CompareFaces
	{
		bool operator() (const ColorFace& f1, const ColorFace& f2 ) const
		{
			float z1 = ( f1.Vertices[0].z + f1.Vertices[1].z + f1.Vertices[2].z  );
			float z2 = ( f2.Vertices[0].z + f2.Vertices[1].z + f2.Vertices[2].z  );
			return z1 < z2;
		}
	};

	static void	PainterAlgoSort(ColorMesh_t& mesh )
	{
		std::sort(mesh.begin(), mesh.end(), CompareFaces() );
	}
public:
	virtual void Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h ) = 0;
	virtual void SetTexture(TextureIndex index, const ITextureSourcePtr& texture) = 0;
	virtual ~IRasterizer() = default;
};
