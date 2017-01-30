#include "widget.h"
#include "application-x11.h"
#include "verification.h"
#include "paintbrush.h"

#ifdef GP_X11
#include "window-x11.h"
#endif

using namespace Wt;

Widget::Widget(Widget* parent)
{
#ifdef GP_X11
    WindowX11* x11win = dynamic_cast<WindowX11*>(parent->m_platformWin);
    check_null_ptr(x11win);
    m_platformWin = new WindowX11(x11win);
#endif
    ApplicationX11::instance()->addWindow(this);
}

Widget::Widget(int width, int height)
{
#ifdef GP_X11
    m_platformWin = new WindowX11(width, height);
#endif
    ApplicationX11::instance()->addWindow(this);
}

void Widget::show()
{
    m_platformWin->show();
}

WindowId Widget::id() const
{
    return m_platformWin->id();
}

bool Widget::isTopLevel() const
{
    return m_platformWin->isTopLevel();
}

void Widget::drawBackground(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setOutlineColor("LightGrey");
    pb.fillRect(x, y, width, height);
}

//void Widget::event(Event* event)
//{

//}

//void Widget::exposeEvent()
//{

//}

//void Widget::drawEvent(int x, int y, int width, int height)
//{

//}

//void Widget::closeEvent()
//{

//}
