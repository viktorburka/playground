#include "listview.h"
#include "paintbrush.h"
#include "rect.h"
#include "wt.h"

#include <cmath>

using namespace Wt;

ListView::ListView(Widget * parent)
    : Widget(parent)
    , m_index(-1)
{
}

void ListView::setData(const std::list<std::string> & items)
{
    m_items = items;
    repaint();
}

int ListView::selectedIndex() const
{
    return m_index;
}

void ListView::setSelectedIndex(int index)
{
    m_index = index;
    repaint();
}

void ListView::drawEvent(int x, int y, int width, int height)
{
    const int ItemHeight = 30;
    const int ScrollBarWidth = 20;

    PaintBrush pb(this);

    int ycoord = 0;
    int effective_width = this->width();

    // draw scroll bar
    if (ItemHeight*m_items.size() > this->height()) {
        effective_width = this->width() - ScrollBarWidth;
        pb.setPaintColor("Light Steel Blue");
        pb.fillRect(effective_width, 0, ScrollBarWidth, this->height());
        drawThumb(pb, m_thumbUpRect, true);
        drawThumb(pb, m_thumbDownRect, false);
        drawScroller(pb, m_scrollerAreaRect);
    }

    int i = 0;
    for(auto it = m_items.begin(); it != m_items.end(); ++it, ++i) {
        pb.setPaintColor(i == m_index ? "Light Sky Blue" : "White");
        pb.fillRect(0, ycoord, effective_width-1, ItemHeight);
        pb.setPaintColor("Black");
        pb.drawRect(0, ycoord, effective_width-1, ItemHeight);
        pb.setPaintColor("Black");
        pb.drawText(*it, Rect(0, ycoord, effective_width-1, ItemHeight));
        ycoord += ItemHeight;
    }
}

void ListView::mousePressEvent(int x, int y, MouseButtons state)
{
    const int ItemHeight = 30;

    if (state && LeftButton) {
        if (m_viewRect.contains(x,y)) {
            int index = y / ItemHeight;
            setSelectedIndex(index);
        } else if (m_thumbUpRect.contains(x,y)) {
            m_viewOffset = Wt::boundary(m_viewOffset + ItemHeight, 0, m_maxViewOffset);
            repaint();
        } else if (m_thumbDownRect.contains(x,y)) {
            m_viewOffset = Wt::boundary(m_viewOffset - ItemHeight, 0, m_maxViewOffset);
            repaint();
        }
    }
}

void ListView::mouseReleaseEvent(int x, int y, MouseButtons state)
{
    if (m_index != -1)
        sendEvent("selectedItemChanged");
}

void ListView::geometryChangeEvent(int x, int y, int width, int height)
{
    const int ThumbLength = 20;

    int viewWidth = width - ThumbLength;
    m_thumbUpRect      = Rect(viewWidth, 0, ThumbLength-1, ThumbLength);
    m_thumbDownRect    = Rect(viewWidth, height-ThumbLength, ThumbLength-1, ThumbLength);
    m_scrollerAreaRect = Rect(viewWidth, ThumbLength, ThumbLength, height-ThumbLength*2);
    m_viewRect         = Rect(0, 0, viewWidth, height);
}

void ListView::drawThumb(PaintBrush & pb, const Rect & rect, bool up) const
{
    pb.setPaintColor("Steel Blue");
    pb.fillRect(rect);
    pb.setPaintColor("Black");
    pb.drawRect(rect);
}

void ListView::drawScroller(PaintBrush & pb, const Rect & rect) const
{
    const int ThumbLength = 20;
    const int ItemHeight  = 30;

    int scrollerAreaHeight = height() - ThumbLength*2;
    int scrollerHeight = scrollerAreaHeight;

    if (m_items.size()) {
        scrollerHeight = scrollerAreaHeight * height()/(m_items.size()*ItemHeight);
    }

    Rect scrollerRect(rect.x()+1, rect.y()+1, rect.width()-3, scrollerHeight-1);

    pb.setPaintColor("Powder Blue");
    pb.fillRect(scrollerRect);
    pb.setPaintColor("Black");
    pb.drawRect(scrollerRect);
}
