#ifndef PAINTBRUSH_H
#define PAINTBRUSH_H

#include <X11/Xlib.h>

#include <string>

namespace Wt {

class Widget;
class WindowX11;

class PaintBrush
{
public:
    PaintBrush(Widget * widget);

    void drawRect(int x, int y, int width, int height);
    void fillRect(int x, int y, int width, int height);
    void setOutlineColor(const std::string & colorName);

private:
    Widget* m_surface;
    GC      m_gc;
};

}

#endif
