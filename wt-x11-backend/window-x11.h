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

private:
    Window m_win;
    int m_width, m_height;
    int m_xpos, m_ypos;
};

#endif
