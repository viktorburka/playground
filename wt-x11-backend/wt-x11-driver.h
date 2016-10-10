#ifndef WTX11DRIVER_H
#define WTX11DRIVER_H

#include "window-x11.h"

class WtX11DriverWindow: public WindowX11
{
public:
    WtX11DriverWindow(int width, int height);

protected:
    void drawEvent(int x, int y, int width, int height);
};

#endif
