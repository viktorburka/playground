#ifndef PAINTBRUSH_H
#define PAINTBRUSH_H

#include <X11/Xlib.h>

#include <string>

namespace Wt {

class Widget;
class WindowX11;
class Rect;

class PaintBrush
{
public:
    PaintBrush(Widget* widget);

    void drawRect(const Rect & rect);
    void drawRect(int x, int y, int width, int height);
    void fillRect(const Rect & rect);
    void fillRect(int x, int y, int width, int height);
    void setPaintColor(const std::string & colorName);
    void drawText(const std::string & text);
    void drawText(const std::string & text, const Rect & rect);

private:
    Widget* m_surface;
    GC      m_gc;
};

}

#endif
