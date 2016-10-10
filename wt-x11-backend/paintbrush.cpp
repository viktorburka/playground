#include "paintbrush.h"
#include "window-x11.h"
#include "display-x11.h"

PaintBrush::PaintBrush(WindowX11 *win)
    : m_surface(win)
{
    Display* display = DisplayX11::display;

//    XGCValues values;
//    values.foreground = WhitePixel(display, DefaultScreen(display));
//    values.line_width = 1;
//    values.line_style = LineSolid;
    m_gc = XCreateGC(display, win->id(),
                     //GCForeground|GCLineWidth|GCLineStyle,
                     0,
                     /*&values*/NULL);
    XSetFillStyle(display, m_gc, FillSolid);
}

void PaintBrush::drawRect(int x, int y, int width, int height)
{
    Display* display = DisplayX11::display;
    XDrawRectangle(display, m_surface->id(), m_gc, x, y, width, height);
}

void PaintBrush::fillRect(int x, int y, int width, int height)
{
    Display* display = DisplayX11::display;
    XFillRectangle(display, m_surface->id(), m_gc, x, y, width, height);
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
