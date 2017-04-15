#include "listview.h"
#include "paintbrush.h"
#include "rect.h"

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

    PaintBrush pb(this);

    int ycoord = 0;

    //for(int i = 0; i < m_items.size(); ++i) {
    std::list<std::string>::iterator it;
    int i = 0;
    for(it = m_items.begin(); it != m_items.end(); ++it, ++i) {
        pb.setPaintColor(i == m_index ? "Light Sky Blue" : "White");
        pb.fillRect(0, ycoord, this->width()-1, ItemHeight);
        pb.setPaintColor("Black");
        pb.drawRect(0, ycoord, this->width()-1, ItemHeight);
        pb.setPaintColor("Black");
        pb.drawText(*it, Rect(0, ycoord, this->width()-1, ItemHeight));
        ycoord += ItemHeight;
    }
}

void ListView::mousePressEvent(int x, int y, MouseButtons state)
{
    const int ItemHeight = 30;

    if (state && LeftButton) {
        int index = y / ItemHeight;
        setSelectedIndex(index);
    }
}

void ListView::mouseReleaseEvent(int x, int y, MouseButtons state)
{
    if (m_index != -1)
        sendEvent("selectedItemChanged");
}
