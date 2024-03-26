// RenderLinux.cpp : Defines the entry point for the application.
//

#include <memory>
#include <cmath>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "RenderLinux.h"
#include "../RenderLib/ISceneRender.h"
#include "../RenderLib/RenderLib.h"
#include "PropertyMapImpl.h"
#include "XDeviceContext.h"

int wait_fd(int fd, double seconds)
{
   struct timeval tv;
   fd_set in_fds;
   FD_ZERO(&in_fds);
   FD_SET(fd, &in_fds);
   tv.tv_sec = std::trunc(seconds);
   tv.tv_usec = (seconds - std::trunc(seconds)) * 1000000;
   return select(fd + 1, &in_fds, 0, 0, &tv);
}

enum class EventType
{
   Timer,
   XEvent
};

EventType XNextEventTimeout(Display* display, XEvent* event, double seconds)
{
   if (XPending(display) || wait_fd(ConnectionNumber(display), seconds)) 
   {
      XNextEvent(display, event);
      return EventType::XEvent;
   }
   else
   {
      return EventType::Timer;
   }
}

void redraw(const WindowContext& wc, IDeviceContext& dc, ISceneRender& sc, IPropertyMap& pm)
{
   XWindowAttributes window_attributes_return{};
   XGetWindowAttributes(wc.display, wc.window, &window_attributes_return);
   sc.Render(dc, window_attributes_return.width, window_attributes_return.height, pm);
}

int main()
{
   Display* const display = XOpenDisplay(nullptr);

   const auto screen = DefaultScreen(display);
   const auto black = BlackPixel(display, screen);	/* get color black */
   const auto white = WhitePixel(display, screen);  /* get color white */

   Window window = XCreateSimpleWindow(
      display, XDefaultRootWindow(display),
      100, 100, 800, 600, 4, white, black);

   auto gc = XCreateGC(display, window, 0, 0);
   const WindowContext wc{ display, window, gc };

   XMapWindow(display, window);
   XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask);
   
   PropertyMapImpl propMap("settings.txt");
   XDeviceContext dc(wc);
   ISceneRenderPtr render = CreateRender();

   redraw(wc, dc, *render, propMap);
  // XFlush(wc.display);

   XEvent event{};
   for(;;)
   {
      if (XNextEventTimeout(display, &event, 0.05) == EventType::Timer) 
      {
         render->Tick(propMap);
         redraw(wc, dc, *render, propMap);
       //  XFlush(wc.display);
         continue;
      }

      switch (event.type)
      {
      case Expose:
         if (event.xexpose.count == 0)
         {
            redraw(wc, dc, *render, propMap);
            XFlush(wc.display);
         }
         break;
      case KeyPress:
      {
         /*
         XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') {
               //close_x();
            }
            printf("You pressed the %c key!\n", text[0]);
         }*/
         break;
      }
      case ButtonPress:
      {
         printf("You pressed a button at (%i,%i)\n",
            event.xbutton.x, event.xbutton.y);
         break;
      }
      default:;

      }
   }

	return 0;
}
