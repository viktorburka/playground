#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "widget.h"

namespace Wt {

class PushButton: public Widget
{
public:
    PushButton(Widget* parent);

protected:
    void drawEvent(int x, int y, int width, int height);
    void mousePressEvent(int x, int y, MouseButtons state);
    void mouseReleaseEvent(int x, int y, MouseButtons state);

private:
    bool m_pressed;
};

}

#endif
