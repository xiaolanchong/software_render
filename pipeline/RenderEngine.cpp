#include "stdafx.h"
#include "RenderEngine.h"

#include "rasterizer/GradientRasterizer.h"
#include "rasterizer/WireFrameRasterizer.h"
#include "rasterizer/PixelRasterizer.h"

#include "texture/TextureFileSource.h"

IRasterizer * GetPreferredRasterizer()
{
	return new 
#if 1
		GradientRasterizer
#else
		PixelRasterizer
#endif
		;
}

RenderEngine::RenderEngine():
	m_bEnableCull(true),
	m_pRasterizer(std::make_unique<GradientRasterizer>()),
	m_mode(Mode::Fill)
{
	// guess enough
	m_RasterizeCache.reserve( 2048 );

	//SetMode(Mode::Fill);
}

RenderEngine::~RenderEngine()
{
}

void		RenderEngine::Draw( CDC* pDC, WORD w, WORD h )
{
	Rasterize(pDC, m_RasterizeCache, w, h);
	m_RasterizeCache.clear();
}


//! для преобразования нормалей в мировые координаты убираем столбец переноса
void ForNormal( Matrix& m )
{
	m.x[3][0] = 
		m.x[3][1] = 
		m.x[3][2] = 
		m.x[0][3] =
		m.x[1][3] =
		m.x[2][3] = 0.0f;
	m.x[3][3] = 1.0f;
}

void	RenderEngine::AddPrimitive(const IGeoSolid::Solid_t& s)
{
	Matrix MatAll = m_MatWorld * m_MatView * m_MatProj;

	IGeoSolid::Solid_t		TransformedSolid;
	std::vector<COLORREF>	VertexColors ( TransformedSolid.size() * 3 );

	
	Matrix MatWorldForNormals = m_MatWorld;
	Matrix MatViewForNormals = m_MatView;
	ForNormal(MatWorldForNormals);
	ForNormal(MatViewForNormals);
	//! преобразуем нормали в систему координат наблюдателя и посмотрим знак
	Matrix MatWorldViewForNormals = MatWorldForNormals * MatViewForNormals;

	for ( size_t i = 0; i < s.size(); ++i )
	{
		Face f( MatAll * s[i][0], MatAll * s[i][1], MatAll * s[i][2],
			    MatWorldViewForNormals * s[i].n[0], 
				MatWorldViewForNormals * s[i].n[1], 
				MatWorldViewForNormals * s[i].n[2],
				s[i].t[0], s[i].t[1], s[i].t[2]);

		TransformedSolid.push_back( f );
		
		Face fw( m_MatWorld * s[i][0], m_MatWorld * s[i][1], m_MatWorld * s[i][2],
			MatWorldForNormals * s[i].n[0], MatWorldForNormals * s[i].n[1], MatWorldForNormals * s[i].n[2]);
		fw.n[0] = Normalize(fw.n[0]);
		fw.n[1] = Normalize(fw.n[1]);
		fw.n[2] = Normalize(fw.n[2]);

		Vector cl1, cl2, cl3;
		m_pLightEngine->Shade( fw, cl1, cl2, cl3  );
		VertexColors.push_back( Vec2Color(cl1) );
		VertexColors.push_back( Vec2Color(cl2) );
		VertexColors.push_back( Vec2Color(cl3) );
	}

	ColorMesh_t		ScreenMesh;
	ScreenMesh.reserve( s.size() );
	for ( size_t i = 0; i < TransformedSolid.size(); ++i )
	{
		const Vector& v1 = TransformedSolid[i][0];
		const Vector& v2 = TransformedSolid[i][1];
		const Vector& v3 = TransformedSolid[i][2];

		//! отсечение невидимых поверхностей(culling)
		//! если z нормали > 0, то грань смотрит от нас
		if( (v2.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (v2.y - v1.y) > 0 && m_bEnableCull )
			continue;
		ScreenMesh.push_back(ColorFace(
			TransformedSolid[i][0], 
			TransformedSolid[i][1],
			TransformedSolid[i][2],
			VertexColors[ 3*i + 0 ],
			VertexColors[ 3*i + 1 ],
			VertexColors[ 3*i + 2 ],
			TransformedSolid[i].t[0],
			TransformedSolid[i].t[1],
			TransformedSolid[i].t[2]) );
	}
	m_RasterizeCache.insert( m_RasterizeCache.begin(), 
							 ScreenMesh.begin(), ScreenMesh.end() );
}

void	RenderEngine::Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h )
{
	ASSERT( m_pRasterizer.get() );
	m_pRasterizer->Rasterize( pDC, Mesh, w, h );
	Mesh.clear();
}

void	RenderEngine::SetMode( Mode mode )
{
	if (m_mode == mode)
		return;

	m_mode = mode;
	switch (mode)
	{
	case Mode::OnlyWire:
		m_pRasterizer = std::make_unique<WireFrameRasterizer>();
		SetCull(false);
		break;
	case Mode::Fill:
		m_pRasterizer = std::make_unique<GradientRasterizer>();
		SetCull(true);
		break;
	case Mode::FillAndTextures:
		m_pRasterizer = std::make_unique<PixelRasterizer>();
		SetCull(true);
		break;
	default:
		ASSERT(!"Uknown rasterizing mode");
	};
}