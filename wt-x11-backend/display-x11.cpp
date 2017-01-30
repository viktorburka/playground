#include "display-x11.h"
#include "verification.h"

using namespace Wt;

Display* DisplayX11::display     = 0;
GC       DisplayX11::gc          = 0;
Atom     DisplayX11::closeWinMsg = 0;

Display *DisplayX11::currentDisplay()
{
    check_display_x11(display);
    return display;
}

GC DisplayX11::currentGC()
{
    return gc;
}

void DisplayX11::initWindowManager(Display* display)
{
    closeWinMsg = XInternAtom(display, "WM_DELETE_WINDOW", false);
}
