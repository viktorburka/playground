#include "wteventloop.h"
#include "wtwaylandwindow.h"

#include <wayland-client.h>
#include <stdio.h>
#include <stdlib.h>

WtEventLoop::WtEventLoop()
{

}

void WtEventLoop::run(WtWaylandWindow * window)
{
    if (!window->display()) {
        fprintf(stderr, "Can't locate Wayland display\n");
        exit(1);
    }
    while (true) {
        fprintf(stdout, "display = %p\n", window->display());
        int status = wl_display_dispatch(window->display());
        if (status == -1) {
            fprintf(stderr, "wl_display_dispatch failed: %m\n");
            exit(1);
        }
    }
}
