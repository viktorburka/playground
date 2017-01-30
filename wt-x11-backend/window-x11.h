#ifndef WINDOWX11_H
#define WINDOWX11_H

#include "window.h"
#include "application-x11.h"

#include <X11/Xlib.h>

namespace Wt {

class WindowX11: public Window
{
public:
    WindowX11(WindowX11* parent);
    WindowX11(int width, int height);

    void show();
    WindowId id() const;
    bool isTopLevel() const;

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}

private:
    //void drawBackground(int x, int y, int width, int height);
    //void eventX11(XEvent * event);

    WindowId  m_win;
    int     m_width, m_height;
    int     m_xpos, m_ypos;
    bool    m_topLevel;
    //Atom    m_closeWinMsg;

    friend class ApplicationX11;
};

}

#endif
