#ifndef _RENDER_ENGINE_6898470234012872_
#define _RENDER_ENGINE_6898470234012872_

#include "../math/vector.h"
#include "../math/matrix.h"
#include "../math/face.h"
#include "../geometry/IGeoSolid.h"
#include "light/ILightEngine.h"
#include "rasterizer/IRasterizer.h"
#include "../IDeviceContext.h"

//! Класс отображения тел
class RenderEngine
{
public:
	enum class Mode
	{
		OnlyWire,
		Fill,
		FillAndTextures,
	};

	RenderEngine();

	void		SetWorldMatrix		( const Matrix & m ) { m_MatWorld = m; } 
	void		SetViewMatrix		( const Matrix & m ) { m_MatView = m; } 
	void		SetProjectionMatrix	( const Matrix & m ) { m_MatProj = m; } 

	void		SetCull( bool bEnable = true ) { m_bEnableCull = bEnable; }
	void		SetMode(Mode mode);
	void		SetLight( ILightEnginePtr LightEng )
	{
		m_pLightEngine = std::move(LightEng);
	}

	void		AddPrimitive(const IGeoSolid::Faces& s, TextureIndex textureIndex);
	void		SetTexture(TextureIndex index, const ITextureSourcePtr& texture);

	void		Draw( IDeviceContext& pDC, unsigned int w, unsigned int h );

private:
	ColorType Vec2Color(const Vector& v)
	{
		return Rgb(std::uint8_t(255 * v.x), std::uint8_t(255 * v.y), std::uint8_t(255 * v.z));
	}
	void		Rasterize(IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h);


private:
	Matrix		m_MatWorld;
	Matrix		m_MatView;
	Matrix		m_MatProj;
	bool			m_bEnableCull;
	Mode			m_mode;

	ILightEnginePtr					   m_pLightEngine;
	std::unique_ptr<IRasterizer>		m_pRasterizer;
	ColorMesh_t								m_RasterizeCache;
};

#endif // _RENDER_ENGINE_6898470234012872_