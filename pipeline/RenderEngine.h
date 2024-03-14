#ifndef _RENDER_ENGINE_6898470234012872_
#define _RENDER_ENGINE_6898470234012872_

#include "../math/vector.h"
#include "../math/matrix.h"
#include "../math/face.h"
#include "../geometry/IGeoSolid.h"
#include "light/ILightEngine.h"
#include "rasterizer/IRasterizer.h"

//! \brief ����� ����������� ���
//! \author 
//! \date   29.11.2005
//! \version 1.0
//! \bug 
//! \todo 

class RenderEngine
{
	Matrix		m_MatWorld;
	Matrix		m_MatView;
	Matrix		m_MatProj;
	bool		m_bEnableCull;

	std::auto_ptr<ILightEngine>		m_pLightEngine;
	std::auto_ptr<IRasterizer>		m_pRasterizer;

	
	void		Rasterize( CDC* pDC, ColorMesh_t& Mesh, WORD w, WORD h );

	mutable ColorMesh_t	 m_RasterizeCache;



	COLORREF Vec2Color( const Vector& v )
	{
		return RGB( 255 * v.x, 255 * v.y, 255 * v.z );
	}
public:
	RenderEngine();
	virtual ~RenderEngine();

	void		SetWorldMatrix		( const Matrix & m ) { m_MatWorld = m; } 
	void		SetViewMatrix		( const Matrix & m ) { m_MatView = m; } 
	void		SetProjectionMatrix	( const Matrix & m ) { m_MatProj = m; } 

	void		SetCull( bool bEnable = true ) { m_bEnableCull = bEnable; }
	void		SetWireFrame( bool bWire = true ); 
	void		SetLight( std::auto_ptr<ILightEngine> LightEng )
	{
		m_pLightEngine = LightEng;
	}

	void		AddPrimitive(const IGeoSolid::Solid_t& s);

	void		Draw( CDC* pDC, WORD w, WORD h );
};

#endif // _RENDER_ENGINE_6898470234012872_