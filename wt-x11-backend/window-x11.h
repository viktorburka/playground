#ifndef WINDOWX11_H
#define WINDOWX11_H

#include <X11/Xlib.h>

class WindowX11
{
public:
    WindowX11(WindowX11* parent);
    WindowX11(int width, int height);

    void show();
    Window id() const;
    bool isTopLevel() const;

    void eventX11(XEvent * event);

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}

private:
    void drawBackground(int x, int y, int width, int height);
    Window nativeWindowId() const;

    Window  m_win;
    int     m_width, m_height;
    int     m_xpos, m_ypos;
    bool    m_topLevel;
    Atom    m_closeWinMsg;
};

#endif
