#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"

namespace Wt {

class Window
{
public:
    virtual ~Window() {}

    virtual void show() {}
    virtual WindowId id() const { return (WindowId)0; }
    virtual bool isTopLevel() const { return false; }

    //virtual void event(Event * event) {}

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}
};

}

#endif
