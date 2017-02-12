#ifndef WIDGET_H
#define WIDGET_H

#include "types.h"

#include <list>

namespace Wt {

class Window;

class Widget
{
public:
    Widget(Widget* parent);
    Widget(int width, int height);

    void show();
    void hide();
    WindowId id() const;
    bool isTopLevel() const;
    bool isVisible() const;

    int width() const;
    int height() const;
    int x() const;
    int y() const;

    void setSize(int width, int height);
    void setPosition(int x, int y);

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}

private:
    void drawBackground(int x, int y, int width, int height);

    int     m_x, m_y;
    int     m_width, m_height;
    bool    m_visible;

    Window* m_platformWin;

    Widget* m_parent;
    std::list<Widget*> m_children;

#ifdef GP_X11
    friend class ApplicationX11;
#endif
};

}

#endif
