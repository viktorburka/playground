#ifndef WINDOWX11_H
#define WINDOWX11_H

#include <X11/Xlib.h>

class WindowX11
{
public:
    WindowX11(int width, int height);

    void show();
    Window id() const;

    void eventX11(XEvent * event);

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}

private:
    void drawBackground(int x, int y, int width, int height);

    Window  m_win;
    GC      m_gc;
    int     m_width, m_height;
    int     m_xpos, m_ypos;
};

#endif
