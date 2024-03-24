#pragma once

#include "../RenderLib/IDeviceContext.h"

class GdiDeviceContext : public IDeviceContext
{
public:

   explicit GdiDeviceContext(CDC& dc)
      : m_dc(dc)
   {}
   
   bool DrawGradientTriangles(const PointAndColor* pVertex, size_t nVertex) override;
   bool DrawEmptyTriangles(const Point* lpPoints, size_t nTriangleCount) override;
   bool BitBlt(unsigned int w, unsigned int h, const void* image) override;

private:
   CDC& m_dc;
   std::vector<CPoint> m_vertices;
   std::vector<int> m_indices;
};

