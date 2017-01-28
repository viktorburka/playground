#include "display-x11.h"
#include "verification.h"

Display* DisplayX11::display = 0;
GC DisplayX11::gc = 0;

Display *DisplayX11::currentDisplay()
{
    check_display_x11(display);
    return display;
}

GC DisplayX11::currentGC()
{
    return gc;
}
