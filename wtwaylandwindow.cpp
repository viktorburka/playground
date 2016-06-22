#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "wtwaylandwindow.h"

WtWaylandWindow::WtWaylandWindow()
	: display(0)
{
	display = wl_display_connect(NULL);
	if (!display) {
        fprintf(stderr, "Error connecting to the Wayland display: %s\n", strerror(errno));
		exit(-1);
    }
}

WtWaylandWindow::~WtWaylandWindow()
{
    if (display) {
        wl_display_disconnect(display); // This should call free on display
        display = 0;
    }
}
