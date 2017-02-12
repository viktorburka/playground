#include "widget.h"
#include "application.h"
#include "verification.h"
#include "paintbrush.h"

#ifdef GP_X11
#include "window-x11.h"
#endif

using namespace Wt;

Widget::Widget(Widget* parent)
    : m_x(0), m_y(0)
    , m_width(0), m_height(0)
    , m_visible(false)
    , m_parent(parent)
{
#ifdef GP_X11
    WindowX11* x11win = dynamic_cast<WindowX11*>(parent->m_platformWin);
    check_null_ptr(x11win);
    m_platformWin = new WindowX11(x11win);
#endif
    Application::instance()->addWindow(this);

    parent->m_children.push_back(this);

    if (parent->isVisible())
        show();
}

Widget::Widget(int width, int height)
    : m_x(0), m_y(0)
    , m_width(width), m_height(height)
    , m_visible(false)
    , m_parent(0)
{
#ifdef GP_X11
    m_platformWin = new WindowX11(width, height);
#endif
    Application::instance()->addWindow(this);
}

void Widget::show()
{
    m_platformWin->show();
    for(Widget* widget: m_children)
        widget->show();
}

void Widget::hide()
{
    m_platformWin->hide();
}

WindowId Widget::id() const
{
    return m_platformWin->id();
}

bool Widget::isTopLevel() const
{
    return m_platformWin->isTopLevel();
}

bool Widget::isVisible() const
{
    return m_visible;
}

int Widget::width() const
{
    return m_width;
}

int Widget::height() const
{
    return m_height;
}

int Widget::x() const
{
    return m_x;
}

int Widget::y() const
{
    return m_y;
}

void Widget::setSize(int width, int height)
{
    m_platformWin->setSize(width, height);
    m_width = width;
    m_height = height;
}

void Widget::setPosition(int x, int y)
{
    m_platformWin->setPosition(x, y);
    m_x = x;
    m_y = y;
}

void Widget::repaint()
{
    m_platformWin->repaint();
}

void Widget::drawBackground(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setOutlineColor("LightGrey");
    pb.fillRect(x, y, width, height);
    fprintf(stderr, "x = %d, y = %d, width = %d, height = %d\n", x, y, width, height);
}
