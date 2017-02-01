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

private:
    bool m_pressed;
};

}

#endif
