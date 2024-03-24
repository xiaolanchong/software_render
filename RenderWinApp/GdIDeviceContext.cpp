#include "stdafx.h"
#include "GdiDeviceContext.h"

bool GdiDeviceContext::DrawGradientTriangles(const PointAndColor* pVertex, size_t nTriangles)
{
	std::vector<TRIVERTEX>				vert(nTriangles * 3);
	std::vector<GRADIENT_TRIANGLE>	gTri(nTriangles);

	for (size_t i = 0; i < nTriangles; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			size_t nIndex = 3 * i + j;
			const auto& inVert = pVertex[nIndex];
			vert[nIndex].x = inVert.pt.x;
			vert[nIndex].y = inVert.pt.y;

			vert[nIndex].Red = inVert.r << 8;
			vert[nIndex].Green = inVert.g << 8;
			vert[nIndex].Blue = inVert.b << 8;
			vert[nIndex].Alpha = 0x0000;
		}
	}

	for (size_t i = 0; i < nTriangles; ++i)
	{
		gTri[i].Vertex1 = ULONG(3 * i + 0);
		gTri[i].Vertex2 = ULONG(3 * i + 1);
		gTri[i].Vertex3 = ULONG(3 * i + 2);
	}

	return !!m_dc.GradientFill(
      &vert[0], static_cast<ULONG>(vert.size()),
      (&gTri[0]), static_cast<ULONG>(gTri.size()),
      GRADIENT_FILL_TRIANGLE);
}

bool GdiDeviceContext::DrawEmptyTriangles(const Point* lpPoints, size_t nTriangleCount)
{
	CGdiObject* pPrevBrush = m_dc.SelectStockObject(NULL_BRUSH);
	CGdiObject* pPrevPen = m_dc.SelectStockObject(BLACK_PEN);

	m_vertices.resize(nTriangleCount * VERTICES_IN_TRIANGLE);
	m_indices.resize(nTriangleCount, VERTICES_IN_TRIANGLE);

	auto itOut = m_vertices.begin();
	auto itIn = lpPoints;
	for (size_t i = 0; i < nTriangleCount; ++i)
	{
		for (size_t j = 0; j < VERTICES_IN_TRIANGLE; ++j, ++itOut, ++itIn)
		{
			*itOut = { itIn->x, itIn->y };
		}
	}

	const auto res = m_dc.PolyPolygon(&m_vertices[0], &m_indices[0], static_cast<int>(nTriangleCount));

	m_dc.SelectObject(pPrevPen);
	m_dc.SelectObject(pPrevBrush);

	return !!res;
}

bool GdiDeviceContext::BitBlt(unsigned int w, unsigned int h, const void* image)
{
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	auto& header = bmi.bmiHeader;
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biWidth = w;
	header.biHeight = -static_cast<int>(h);
	header.biPlanes = 1;
	header.biBitCount = 32;
	header.biCompression = BI_RGB;
	header.biSizeImage = 0;

	auto res = ::SetDIBitsToDevice(m_dc.GetSafeHdc(),
		0, 0, w, h,
		0, 0, 0, h,
		image, &bmi, DIB_RGB_COLORS);
	return !!res;
}