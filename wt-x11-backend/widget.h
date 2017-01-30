#ifndef WIDGET_H
#define WIDGET_H

#include "types.h"

namespace Wt {

class Window;

class Widget
{
public:
    Widget(Widget* parent);
    Widget(int width, int height);

    void show();
    WindowId id() const;
    bool isTopLevel() const;

//    void event(Event* event);

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}

private:
    void drawBackground(int x, int y, int width, int height);
//    Window nativeWindowId() const;

//    Window  m_win;
//    int     m_width, m_height;
//    int     m_xpos, m_ypos;
//    bool    m_topLevel;
    Window* m_platformWin;
#ifdef GP_X11
    friend class ApplicationX11;
#endif
};

}

#endif
