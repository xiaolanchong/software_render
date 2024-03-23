#pragma once

#include "pipeline/IDeviceContext.h"

class GdiDeviceContext : public IDeviceContext
{
public:

   explicit GdiDeviceContext(CDC& dc)
      : m_dc(dc)
   {}
   
   bool GradientFill(const TRIVERTEX* pVertex, size_t nVertex, const void* pMesh, size_t nMesh) override;
   bool DrawEmptyTriangles(const CPoint* lpPoints, size_t nTriangleCount) override;
   bool BitBlt(unsigned int w, unsigned int h, const void* image) override;

private:
   CDC& m_dc;
   std::vector<int> m_indices;
};

