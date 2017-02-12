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

    pb.setFillColor(m_pressed ? "Web Gray" : "Dark Gray");
    pb.fillRect(0, 0, Widget::width(), Widget::height());

    pb.setOutlineColor("Black");
    pb.drawRect(0, 0, Widget::width()-1, Widget::height()-1);
}

void PushButton::mousePressEvent(int x, int y, MouseButtons state)
{
    m_pressed = state && LeftButton;
    repaint();
}

void PushButton::mouseReleaseEvent(int x, int y, MouseButtons state)
{
    m_pressed = !(state && LeftButton);
    repaint();
}
