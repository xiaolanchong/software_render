#include "stdafx.h"
#include "GradientRasterizer.h"

void GradientRasterizer::Rasterize( IDeviceContext& dc, ColorMesh_t& Mesh, unsigned int w, unsigned int h )
{
	PainterAlgoSort(Mesh);

	std::vector<IDeviceContext::PointAndColor> vertices(Mesh.size() * IDeviceContext::VERTICES_IN_TRIANGLE);
	for (size_t i = 0; i < Mesh.size(); ++i)
	{
		for (size_t j = 0; j < IDeviceContext::VERTICES_IN_TRIANGLE; ++j)
		{
			size_t nIndex = IDeviceContext::VERTICES_IN_TRIANGLE * i + j;
			auto pt = Trans2Viewport(w, h, Mesh[i].Vertices[j]);
			vertices[nIndex].pt.x = pt.x;
			vertices[nIndex].pt.y = pt.y;

			vertices[nIndex].r = GetR(Mesh[i].Color[j]);
			vertices[nIndex].g = GetG(Mesh[i].Color[j]);
			vertices[nIndex].b = GetB(Mesh[i].Color[j]);
		}
	}

	bool res = dc.DrawGradientTriangles(&vertices[0], Mesh.size());
	verify(res);
}
