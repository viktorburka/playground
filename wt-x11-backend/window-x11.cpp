#include "display-x11.h"
#include "verification.h"
#include "application-x11.h"
#include "paintbrush.h"
#include "window-x11.h"

using namespace Wt;

WindowX11::WindowX11(WindowX11 *parent)
    : m_width(0)
    , m_height(0)
    , m_xpos(0)
    , m_ypos(0)
    , m_topLevel(parent == nullptr)
{
    Display* display = DisplayX11::currentDisplay();

    int screen_num = DefaultScreen(display);
    int border_width = 1;

    m_win = XCreateSimpleWindow(display,
                                m_topLevel ? RootWindow(display, screen_num) : parent->id(),
                                m_xpos, m_ypos,
                                m_width, m_height,
                                border_width, BlackPixel(display, screen_num),
                                WhitePixel(display, screen_num));
    fprintf(stderr, "Created window: %u", (uint)m_win);

    if (m_topLevel && !DisplayX11::currentGC())
        DisplayX11::gc = XCreateGC(display, m_win, 0, NULL);

    XSelectInput(display, m_win, ExposureMask | ButtonPressMask);
    XSetWMProtocols(display, m_win, &DisplayX11::closeWinMsg, 1);
}

WindowX11::WindowX11(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_xpos(0)
    , m_ypos(0)
    , m_topLevel(true)
    //, m_closeWinMsg(0)
{
    Display* display = DisplayX11::currentDisplay();

    int screen_num = DefaultScreen(display);
    int border_width = 1;

    m_win = XCreateSimpleWindow(display,
                                RootWindow(display, screen_num),
                                m_xpos, m_ypos,
                                m_width, m_height,
                                border_width, BlackPixel(display, screen_num),
                                WhitePixel(display, screen_num));
    fprintf(stderr, "Created window: %u", (uint)m_win);

    if (!DisplayX11::currentGC())
        DisplayX11::gc = XCreateGC(display, m_win, 0, NULL);

    XSelectInput(display, m_win, ExposureMask | ButtonPressMask);
    XSetWMProtocols(display, m_win, &DisplayX11::closeWinMsg, 1);
}

void WindowX11::show()
{
    Display* display = DisplayX11::display;
    XMapWindow(display, m_win);
}

WindowId WindowX11::id() const
{
    return m_win;
}

bool WindowX11::isTopLevel() const
{
    return m_topLevel;
}

//void WindowX11::drawBackground(int x, int y, int width, int height)
//{
//    PaintBrush pb(this);
//    pb.setOutlineColor("LightGrey");
//    pb.fillRect(x, y, width, height);
//}

//void WindowX11::eventX11(XEvent *event)
//{
//    (void)event;
//    fprintf(stderr, "Event: %d\n", event->type);

//    switch (event->xany.type) {
//    case Expose: {
//        XExposeEvent ee = event->xexpose;
//        if (ee.count == 0) { // ignoring queued up expose events
//            exposeEvent();
//            drawBackground(ee.x, ee.y, ee.width, ee.height);
//            drawEvent(ee.x, ee.y, ee.width, ee.height);
//        }
//        break;
//    }
//    case ClientMessage: {
//        if (event->xclient.data.l[0] == m_closeWinMsg) {
//            closeEvent();
//            ApplicationX11::instance()->leaveEventLoop();
//        }
//        break;
//    }
//    default:
//        break;
//    }
//}
