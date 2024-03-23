#pragma once

struct TRIVERTEX;

class IDeviceContext
{
public:
   virtual ~IDeviceContext() = default;

   virtual bool GradientFill(const TRIVERTEX* pVertex, size_t nVertex, const void* pMesh, size_t nMesh) = 0;
};
