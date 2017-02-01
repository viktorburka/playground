#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"

namespace Wt {

class Window
{
public:
    virtual ~Window() {}

    virtual void show() {}
    virtual void hide() {}
    virtual WindowId id() const { return (WindowId)0; }
    virtual bool isTopLevel() const { return false; }
    virtual void setSize(int width, int height) {}

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}

//private:
//    Window* m_parent;
//    std::list<Window*> m_children;
};

}

#endif
