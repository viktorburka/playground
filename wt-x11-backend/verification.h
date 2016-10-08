#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

void check_display_x11(Display * display)
{
    if (display == NULL) {
        fprintf(stderr, "X11 display is not initialized. Create ApplicationX11 instance first\n");
        exit(-1);
    }
}
