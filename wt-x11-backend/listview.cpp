#include "listview.h"
#include "paintbrush.h"
#include "rect.h"
#include "wt.h"

#include <cmath>

using namespace Wt;

//ScrollerGeometry::ScrollerGeometry(int x, int y, int width, int height)
//    : Rect(x, y, width, height)
//{
//}

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
        drawThumb(pb, m_sg.thumbUpRect(), true);
        drawThumb(pb, m_sg.thumbDownRect(), false);
        drawScroller(pb, m_sg.scrollerAreaRect());
    }

    int i = 0;
    for(auto it = m_items.begin(); it != m_items.end(); ++it, ++i) {
        Rect itemRect(0, ycoord-m_viewOffset, effective_width-1, ItemHeight);
        pb.setPaintColor(i == m_index ? "Light Sky Blue" : "White");
        pb.fillRect(itemRect);
        pb.setPaintColor("Black");
        pb.drawRect(itemRect);
        pb.setPaintColor("Black");
        pb.drawText(*it, itemRect);
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
        } else if (m_sg.thumbUpRect().contains(x,y)) {
            m_viewOffset = Wt::boundary(m_viewOffset - ItemHeight/2, 0, m_maxViewOffset);
            int scrollerHeight = m_sg.scrollerHeight(ItemHeight, m_items.size());
            m_scrollerOffset = (m_sg.scrollerAreaRect().height() - scrollerHeight) * m_viewOffset/m_maxViewOffset;
            repaint();
            WtPrint() << "Up, offset:" << m_viewOffset;
        } else if (m_sg.thumbDownRect().contains(x,y)) {
            m_viewOffset = Wt::boundary(m_viewOffset + ItemHeight/2, 0, m_maxViewOffset);
            int scrollerHeight = m_sg.scrollerHeight(ItemHeight, m_items.size());
            m_scrollerOffset = (m_sg.scrollerAreaRect().height() - scrollerHeight) * m_viewOffset/m_maxViewOffset;
            repaint();
            WtPrint() << "Down, offset:" << m_viewOffset;
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
    const int ItemHeight  = 30;

    int viewWidth = width - ThumbLength;
    Rect thumbUpRect      = Rect(viewWidth, 0, ThumbLength-1, ThumbLength);
    Rect thumbDownRect    = Rect(viewWidth, height-ThumbLength, ThumbLength-1, ThumbLength);
    Rect scrollerAreaRect = Rect(viewWidth, ThumbLength, ThumbLength, height-ThumbLength*2);

    m_sg.setRect(viewWidth, 0, ThumbLength, height);
    m_sg.setThumbUpRect(thumbUpRect);
    m_sg.setThumbDownRect(thumbDownRect);
    m_sg.setScrollerAreaRect(scrollerAreaRect);

    m_viewRect = Rect(0, 0, viewWidth, height);

    int totalHeight = m_items.size()*ItemHeight;
    m_maxViewOffset    = totalHeight <= height ? 0 : (totalHeight - height);
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
    const int ItemHeight  = 30;

    int scrollerHeight = m_sg.scrollerHeight(ItemHeight, m_items.size());
    Rect scrollerRect(rect.x()+1, rect.y()+2+m_scrollerOffset,
                      rect.width()-3, scrollerHeight-4);

    pb.setPaintColor("Powder Blue");
    pb.fillRect(scrollerRect);
    pb.setPaintColor("Black");
    pb.drawRect(scrollerRect);
}
