#include "stdafx.h"
#include <execution>
#include "PixelRasterizer.h"
#include "DrawTriangle.h"
#include "InterpolationRender.h"

PixelRasterizer::PixelRasterizer()
	: m_screenBuffer(1, 1, 1)
{
}

class BufferContext
{
public:
	BufferContext(Array2D<std::uint32_t>& buffer)
		: m_buffer(buffer)
	{}

	void SetPixel(int x, int y, ColorType cl)
	{
		auto newCl = Rgb(GetB(cl), GetG(cl), GetR(cl));
		m_buffer(x, y) = newCl;
	}
private:
	Array2D<std::uint32_t>& m_buffer;
};

void PixelRasterizer::SetTexture(TextureIndex index, const ITextureSourcePtr& texture)
{
	verify(index == TEXTURE_0);
	m_texture = texture;
}

int toIntZ(float z)
{
	const float maxZ = 10000.f;
	const float minZ = -10000.f;
	return static_cast<int>((z / (maxZ - minZ)) * (std::numeric_limits<int>::max)());
}

void PixelRasterizer::Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h )
{
	m_screenBuffer.resize(w, h, w);
	std::fill(m_screenBuffer.begin(), m_screenBuffer.end(), 0xffffffff);  // BGR
	BufferContext buffer(m_screenBuffer);

	using Plotter = DCTextureAndColorPlotter<BufferContext>;
	Plotter texturePlotter(&buffer, nullptr, w, h);

	auto drawFace = [w, h, this, &texturePlotter](const ColorFace& face)
	{
		Point pt[3];
		for (size_t j = 0; j < 3; ++j)
		{
			pt[j] = Trans2Viewport(w, h, face.Vertices[j]);
		}

		if (face.m_texture == NO_TEXTURE)
		{
			texturePlotter.SetTexture(nullptr);
		}
		else
		{
			texturePlotter.SetTexture(m_texture);
		}
		DrawTriangle(texturePlotter,
			pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y,
			Plotter::InterpolatedValue{ face.Color[0], face.TexCoord[0], toIntZ(face.Vertices[0].z) },
			Plotter::InterpolatedValue{ face.Color[1], face.TexCoord[1], toIntZ(face.Vertices[1].z) },
			Plotter::InterpolatedValue{ face.Color[2], face.TexCoord[2], toIntZ(face.Vertices[2].z) });
	};

	PainterAlgoSort( Mesh );

#if 0
	std::for_each(std::execution::par, std::begin(Mesh), std::end(Mesh),
		[&drawFace](const ColorFace& face)
		{
			drawFace(face);
		});
#else
	for (const auto& face: Mesh)
	{
		drawFace(face);
	}
#endif

	auto res = dc.BitBlt(w, h, &(*m_screenBuffer.begin()));
	verify(res);
}
