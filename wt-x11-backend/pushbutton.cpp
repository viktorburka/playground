#include "pushbutton.h"
#include "paintbrush.h"

using namespace Wt;

PushButton::PushButton(Widget* parent)
    : Widget(parent)
    , m_pressed(false)
{
}

void PushButton::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);

    pb.setFillColor(m_pressed ? "Red" : "Red");
    pb.fillRect(0, 0, Widget::width(), Widget::height());

    //pb.fillRect(100, 100, 100, 100);

//    pb.setOutlineColor("Red");
//    pb.drawRect(0, 0, Widget::width()-1, Widget::height()-1);
}
