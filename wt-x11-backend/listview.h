#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "widget.h"
#include "rect.h"

#include <string>
#include <list>

namespace Wt {

class PaintBrush;

class ListView: public Widget
{
public:
    ListView(Widget * parent);

    void setData(const std::list<std::string> & items);

    int selectedIndex() const;
    void setSelectedIndex(int index);

protected:
    void drawEvent(int x, int y, int width, int height);
    void mousePressEvent(int x, int y, MouseButtons state);
    void mouseReleaseEvent(int x, int y, MouseButtons state);
    void geometryChangeEvent(int x, int y, int width, int height);

private:
    void drawThumb(PaintBrush & pb, const Rect & rect, bool up) const;
    void drawScroller(PaintBrush & pb, const Rect & rect) const;

    std::list<std::string>  m_items;
    int                     m_index{-1};
    int                     m_viewOffset{0};
    int                     m_maxViewOffset{0};
    Rect                    m_thumbUpRect;
    Rect                    m_thumbDownRect;
    Rect                    m_scrollerAreaRect;
    Rect                    m_viewRect;
};

}

#endif
