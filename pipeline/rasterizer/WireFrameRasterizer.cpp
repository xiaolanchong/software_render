#include "stdafx.h"
#include "WireFrameRasterizer.h"

void WireFrameRasterizer::Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h )
{
	constexpr size_t VERTICES_IN_TRIANGLE = 3;
	m_vertices.resize(Mesh.size() * VERTICES_IN_TRIANGLE);

	for ( size_t i=0; i < Mesh.size(); ++i )
	{
		for( size_t j=0; j < VERTICES_IN_TRIANGLE; ++j )
		{
			m_vertices[VERTICES_IN_TRIANGLE * i + j] = Trans2Viewport( w, h, Mesh[i].Vertices[j] );
		}
	}

	auto res = dc.DrawEmptyTriangles(&m_vertices[0], Mesh.size());
	assert(res);
}
