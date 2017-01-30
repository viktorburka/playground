#include "wt-x11-driver.h"
#include "paintbrush.h"

WtX11DriverWindow::WtX11DriverWindow(int width, int height)
    : Widget(width, height)
{

}

void WtX11DriverWindow::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setOutlineColor("Red");
    pb.drawRect(50, 50, 50, 50);
    pb.setOutlineColor("Green");
    pb.fillRect(100, 100, 100, 100);
}
