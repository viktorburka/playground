#include "wt-x11-driver.h"
#include "paintbrush.h"

WtDriverWidget::WtDriverWidget(int width, int height)
    : Widget(width, height)
{

}

void WtDriverWidget::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setOutlineColor("Red");
    pb.drawRect(50, 50, 50, 50);
    pb.setOutlineColor("Green");
    pb.fillRect(100, 100, 100, 100);
}
