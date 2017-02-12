#include "application-x11.h"
#include "display-x11.h"
#include "window-x11.h"
#include "verification.h"
#include "widget.h"

#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace Wt;

using std::vector;
using std::string;

static const int MaxEventNumber = 36;
static const char* eventNames[] = {
    "NA"                ,   // 0
    "NA"                ,   // 1
    "KeyPress"          ,   // 2
    "KeyRelease"        ,   // 3
    "ButtonPress"       ,   // 4
    "ButtonRelease"     ,   // 5
    "MotionNotify"      ,   // 6
    "EnterNotify"       ,   // 7
    "LeaveNotify"       ,   // 8
    "FocusIn"           ,   // 9
    "FocusOut"          ,   // 10
    "KeymapNotify"      ,   // 11
    "Expose"            ,   // 12
    "GraphicsExpose"    ,   // 13
    "NoExpose"          ,   // 14
    "VisibilityNotify"  ,   // 15
    "CreateNotify"      ,   // 16
    "DestoryNotify"     ,   // 17
    "UnmapNotify"       ,   // 18
    "DestroyNotify"     ,   // 19
    "MapRequest"        ,   // 20
    "ReparentNotify"    ,   // 21
    "ConfigureNotify"   ,   // 22
    "ConfigureRequest"  ,   // 23
    "GravityNotify"     ,   // 24
    "ResizeRequest"     ,   // 25
    "CirculateNotify"   ,   // 26
    "CirculateRequest"  ,   // 27
    "PropertyNotify"    ,   // 28
    "SelectionClear"    ,   // 29
    "SelectionRequest"  ,   // 30
    "SelectionNotify"   ,   // 31
    "ColormapNotify"    ,   // 32
    "ClientMessage"     ,   // 33
    "MappingNotify"     ,   // 34
    "GenericEvent"      ,   // 35
    "LASTEvent"             // 36
};

//ApplicationX11* ApplicationX11::m_instance = 0;

ApplicationX11::ApplicationX11()
    : m_running(false)
{
//    if (m_instance) {
//        fprintf(stderr, "There can not be more than one instance of Application");
//        exit(-1);
//    }

    DisplayX11::display = XOpenDisplay(NULL); //TO-DO: read DISPLAY env variable
    if (DisplayX11::display == NULL) {
        fprintf(stderr, "Cannot connect to X server %s\n", ":0");
        exit(-1);
    } else {
        fprintf(stderr, "Connected to X server %s !\n", ":0");
    }

    DisplayX11::initWindowManager(DisplayX11::display);

//    m_instance = this;
}

ApplicationX11::~ApplicationX11()
{
    Display* display = DisplayX11::display;
    XCloseDisplay(display);
}

void ApplicationX11::run()
{   
    XEvent event;

    m_running = true;

    while (m_running) {
        XNextEvent(DisplayX11::display, &event);
        int eventType = (int)(event.xany.type);
        fprintf(stderr, "Event received. Type: %d, name: %s, window: %u\n",
                        eventType,
                        eventType > MaxEventNumber ? "Unknown" : eventNames[eventType],
                        (uint)(event.xany.window));
        auto it = m_windows.find(event.xany.window);
        if (it != m_windows.end()) {
            processEvent(&event, it->second);
        } else {
            fprintf(stderr, "Unknown window %u\n", (uint)(event.xany.window));
            exit(-1);
        }
    }
}

//ApplicationX11* ApplicationX11::instance()
//{
//    return m_instance;
//}

void ApplicationX11::addWindow(Widget* widget)
{
    m_windows[widget->id()] = widget;
}

void ApplicationX11::leaveEventLoop()
{
    m_running = false;
}

void ApplicationX11::processEvent(XEvent* event, Widget* widget)
{
    fprintf(stderr, "Event: %d\n", event->type);

    switch (event->xany.type) {
    case Expose: {
        XExposeEvent ee = event->xexpose;
        //if (ee.count == 0) { // ignoring queued up expose events
        widget->exposeEvent();
        widget->drawBackground(ee.x, ee.y, ee.width, ee.height);
        widget->drawEvent(ee.x, ee.y, ee.width, ee.height);
        //}
        break;
    }
    case ConfigureNotify: {
        XConfigureEvent ce = event->xconfigure;
        widget->m_x = ce.x;
        widget->m_y = ce.y;
        widget->m_width  = ce.width;
        widget->m_height = ce.height;
        break;
    }
    case ClientMessage: {
        if (event->xclient.data.l[0] == DisplayX11::closeWinMsg) {
            widget->closeEvent();
            leaveEventLoop();
        }
        break;
    }
    default:
        break;
    }
}
