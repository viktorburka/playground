#include <stdio.h>
#include <stdlib.h>

#include "application-x11.h"
#include "display-x11.h"
#include "window-x11.h"

ApplicationX11* ApplicationX11::m_instance = 0;

ApplicationX11::ApplicationX11()
    : m_running(false)
{
    if (m_instance) {
        fprintf(stderr, "There can not be more than one instance of Application");
        exit(-1);
    }

    DisplayX11::display = XOpenDisplay(NULL); //TO-DO: read DISPLAY env variable
    if (DisplayX11::display == NULL) {
        fprintf(stderr, "Cannot connect to X server %s\n", ":0");
        exit(-1);
    } else {
        fprintf(stderr, "Connected to X server %s !\n", ":0");
    }

    m_instance = this;
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
        fprintf(stderr, "Event received\n");
        auto it = m_windows.find(event.xany.window);
        if (it != m_windows.end()) {
            it->second->eventX11(&event);
        } else {
            fprintf(stderr, "Unknown window %u\n", (uint)(event.xany.window));
            exit(-1);
        }
    }
}

ApplicationX11* ApplicationX11::instance()
{
    return m_instance;
}

void ApplicationX11::addWindow(WindowX11 *win)
{
    m_windows[win->id()] = win;
}

void ApplicationX11::leaveEventLoop()
{
    m_running = false;
}
