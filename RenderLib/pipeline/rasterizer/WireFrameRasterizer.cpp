#include "stdafx.h"
#include "WireFrameRasterizer.h"

void WireFrameRasterizer::Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h )
{
	const auto VERTICES_IN_TRIANGLE = IDeviceContext::VERTICES_IN_TRIANGLE;
	m_vertices.resize(Mesh.size() * VERTICES_IN_TRIANGLE);

	for ( size_t i=0; i < Mesh.size(); ++i )
	{
		for( size_t j=0; j < VERTICES_IN_TRIANGLE; ++j )
		{
			auto pt = Trans2Viewport(w, h, Mesh[i].Vertices[j]);
			m_vertices[VERTICES_IN_TRIANGLE * i + j] = {pt.x, pt.y};
		}
	}

	auto res = dc.DrawEmptyTriangles(&m_vertices[0], Mesh.size());
	verify(res);
}
