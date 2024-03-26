
#include <cstdlib>
#include <cstring>
#include <X11/Xutil.h>
#include "XDeviceContext.h"

bool XDeviceContext::BitBlt(unsigned int w, unsigned int h, const void* imageData)
{
   const auto bytes_per_pixel = 4;
   const auto wp = w;
   const auto hp = h;
   void* data = malloc(wp * hp * bytes_per_pixel);
   memcpy(data, imageData, wp * hp* bytes_per_pixel);

   auto screen = DefaultScreen(m_wc.display);
   auto depth = DefaultDepth(m_wc.display, screen);
   XImage* image = XCreateImage(m_wc.display,
      DefaultVisual(m_wc.display, screen),
      depth,
      ZPixmap,
      0,
      static_cast<char*>(data),
      wp, hp, 8,
      0);
   if (image == nullptr)
   {
      free(data);
      return false;
   }
   Status res = XPutImage(m_wc.display, m_wc.window, m_wc.gc, image, 0, 0, 0, 0, wp, hp);
   XDestroyImage(image); // frees data
   return res == 0;
}