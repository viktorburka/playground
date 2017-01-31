#ifndef WINDOWX11_H
#define WINDOWX11_H

#include "window.h"

namespace Wt {

class ApplicationX11;

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
    WindowId m_win;
    int      m_width, m_height;
    int      m_xpos, m_ypos;
    bool     m_topLevel;

    friend class ApplicationX11;
};

}

#endif
