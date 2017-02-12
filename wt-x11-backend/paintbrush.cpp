#include "paintbrush.h"
#include "window-x11.h"
#include "display-x11.h"
#include "widget.h"

using namespace Wt;

PaintBrush::PaintBrush(Widget* widget)
    : m_surface(widget)
{
    Display* display = DisplayX11::display;

//    XGCValues values;
//    values.foreground = WhitePixel(display, DefaultScreen(display));
//    values.line_width = 1;
//    values.line_style = LineSolid;
    m_gc = DisplayX11::currentGC();
    XSetFillStyle(display, m_gc, FillSolid);
}

void PaintBrush::drawRect(int x, int y, int width, int height)
{
    Display* display = DisplayX11::display;
    XDrawRectangle(display, m_surface->id(), m_gc, x, y, width, height);
}

void PaintBrush::fillRect(int x, int y, int width, int height)
{
//    int adjustedWidth = m_surface->width() - x - 1;
//    int adjustedHeight = m_surface->height() - y - 1;

    int adjustedWidth = x + width >= m_surface->width() ? m_surface->width()-x-1 : width;
    int adjustedHeight = y + height >= m_surface->height() ? m_surface->height()-y-1 : height;

    Display* display = DisplayX11::display;
    XFillRectangle(display, m_surface->id(), m_gc, x, y, adjustedWidth, adjustedHeight);
}

void PaintBrush::setOutlineColor(const std::string & colorName)
{
    Colormap colorMap;
    XColor xc, xc2;

    Display* display = DisplayX11::display;
    colorMap = DefaultColormap(display, DefaultScreen(display));

    XAllocNamedColor(display, colorMap, colorName.c_str(), &xc, &xc2);
    XSetForeground(display, m_gc, xc.pixel);
}

void PaintBrush::setFillColor(const std::string & colorName)
{
    Colormap colorMap;
    XColor xc, xc2;

    Display* display = DisplayX11::display;
    colorMap = DefaultColormap(display, DefaultScreen(display));

    XAllocNamedColor(display, colorMap, colorName.c_str(), &xc, &xc2);
    XSetForeground(display, m_gc, xc.pixel);
}
