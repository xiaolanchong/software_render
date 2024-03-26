#pragma once

#include <utility>
#include <X11/Xlib.h>
#include "../RenderLib/IDeviceContext.h"

struct WindowContext
{
   Display* display;
   Window window;
   GC gc;
};

using Color = decltype(XColor::pixel);

class XDeviceContext: public IDeviceContext
{
public:
   explicit XDeviceContext(WindowContext wc) : m_wc(std::move(wc)) {}

   virtual bool DrawGradientTriangles(const PointAndColor* /*pVertex*/, size_t /*nVertex*/) override { return true; }
   virtual bool DrawEmptyTriangles(const Point* /*pVertex*/, size_t /*nTriangleCount*/) override { return true; }
   virtual bool BitBlt(unsigned int w, unsigned int h, const void* image) override;
private:

   WindowContext m_wc;
};