#include "stdafx.h"
#include "GdiDeviceContext.h"

bool GdiDeviceContext::GradientFill(const TRIVERTEX* pVertex, size_t nVertex, const void* pMesh, size_t nMesh)
{
	return !!m_dc.GradientFill(
      const_cast<TRIVERTEX*>(pVertex), static_cast<ULONG>(nVertex),
      const_cast<void*>(pMesh), static_cast<ULONG>(nMesh),
      GRADIENT_FILL_TRIANGLE);
}

bool GdiDeviceContext::DrawEmptyTriangles(const CPoint* lpPoints, size_t nTriangleCount)
{
	CGdiObject* pPrevBrush = m_dc.SelectStockObject(NULL_BRUSH);
	CGdiObject* pPrevPen = m_dc.SelectStockObject(BLACK_PEN);

	constexpr size_t VERTICES_IN_TRIANGLE = 3;
	m_indices.resize(nTriangleCount, VERTICES_IN_TRIANGLE);

	const auto res = m_dc.PolyPolygon(lpPoints, &m_indices[0], static_cast<int>(nTriangleCount));

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