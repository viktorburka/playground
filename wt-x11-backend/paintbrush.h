#ifndef PAINTBRUSH_H
#define PAINTBRUSH_H

#include <X11/Xlib.h>

#include <string>

class WindowX11;

class PaintBrush
{
public:
    PaintBrush(WindowX11 * win);

    void drawRect(int x, int y, int width, int height);
    void setOutlineColor(const std::string & colorName);

private:
    WindowX11* m_surface;
    GC m_gc;
};

#endif
