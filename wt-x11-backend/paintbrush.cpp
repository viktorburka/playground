#include "paintbrush.h"
#include "window-x11.h"
#include "display-x11.h"
#include "widget.h"
#include "rect.h"

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

    int adjustedWidth = x + width >= m_surface->width() ? m_surface->width()-x : width;
    int adjustedHeight = y + height >= m_surface->height() ? m_surface->height()-y : height;

    Display* display = DisplayX11::display;
    XFillRectangle(display, m_surface->id(), m_gc, x, y, adjustedWidth, adjustedHeight);
}

void PaintBrush::setPaintColor(const std::string & colorName)
{
    Colormap colorMap;
    XColor xc, xc2;

    Display* display = DisplayX11::display;
    colorMap = DefaultColormap(display, DefaultScreen(display));

    XAllocNamedColor(display, colorMap, colorName.c_str(), &xc, &xc2);
    XSetForeground(display, m_gc, xc.pixel);
}

/*void PaintBrush::setFillColor(const std::string & colorName)
{
    Colormap colorMap;
    XColor xc, xc2;

    Display* display = DisplayX11::display;
    colorMap = DefaultColormap(display, DefaultScreen(display));

    XAllocNamedColor(display, colorMap, colorName.c_str(), &xc, &xc2);
    //XSetForeground(display, m_gc, xc.pixel);
    XSetBackground(display, m_gc, xc.pixel);
}*/

void PaintBrush::drawText(const std::string & text)
{
    Display* display = DisplayX11::display;
    XFontStruct* fontInfo = DisplayX11::fontInfo;

    auto textWidth = XTextWidth(fontInfo, text.data(), text.length());

    XDrawString(display, m_surface->id(), m_gc,
                (m_surface->width()-textWidth)/2,
                (m_surface->height() + fontInfo->ascent)/2,
                text.data(), text.length());
}

void PaintBrush::drawText(const std::string & text, const Rect & rect)
{
    Display* display = DisplayX11::display;
    XFontStruct* fontInfo = DisplayX11::fontInfo;

    auto textWidth = XTextWidth(fontInfo, text.data(), text.length());

//    XDrawString(display, m_surface->id(), m_gc,
//                (rect.width()-textWidth)/2,
//                (rect.height()+fontInfo->ascent)/2 + rect.y(),
//                text.data(), text.length());
    XDrawString(display, m_surface->id(), m_gc,
                (rect.geometry(Rect::w)-textWidth)/2,
                (rect.geometry(Rect::h)+fontInfo->ascent)/2 + rect.y(),
                text.data(), text.length());
}
