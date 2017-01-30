#ifndef WTX11DRIVER_H
#define WTX11DRIVER_H

#include "widget.h"

using namespace Wt;

class WtX11DriverWindow: public Widget
{
public:
    WtX11DriverWindow(int width, int height);

protected:
    void drawEvent(int x, int y, int width, int height);
};

#endif
