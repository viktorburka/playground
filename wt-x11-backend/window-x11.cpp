#include "window-x11.h"
#include "display-x11.h"
#include "verification.h"
#include "application-x11.h"
#include "paintbrush.h"

WindowX11::WindowX11(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_xpos(0)
    , m_ypos(0)
{
    Display* display = DisplayX11::display;
    check_display_x11(display);

    int screen_num = DefaultScreen(display);
    int border_width = 1;

    m_win = XCreateSimpleWindow(display,
                                RootWindow(display, screen_num),
                                m_xpos, m_ypos,
                                m_width, m_height,
                                border_width, BlackPixel(display, screen_num),
                                WhitePixel(display, screen_num));
    fprintf(stderr, "Created window: %u", (uint)m_win);

    m_gc = XCreateGC(display, m_win, 0, NULL);
    XSelectInput(display, m_win, ExposureMask | ButtonPressMask);

    ApplicationX11::instance()->addWindow(this);
}

void WindowX11::show()
{
    Display* display = DisplayX11::display;
    XMapWindow(display, m_win);
}

Window WindowX11::id() const
{
    return m_win;
}

void WindowX11::eventX11(XEvent *event)
{
    (void)event;
    fprintf(stderr, "Event: %d\n", event->type);

    switch (event->xany.type) {
    case Expose: {
        XExposeEvent ee = event->xexpose;
        if (ee.count == 0) { // ignoring queued up expose events
            exposeEvent();
            drawBackground(ee.x, ee.y, ee.width, ee.height);
            drawEvent(ee.x, ee.y, ee.width, ee.height);
        }
        break;
    }
    default:
        break;
    }
}

void WindowX11::drawBackground(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setOutlineColor("LightGrey");
    pb.fillRect(x, y, width, height);
}
