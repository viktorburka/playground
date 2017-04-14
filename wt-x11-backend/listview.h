#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "widget.h"

#include <string>
#include <list>

namespace Wt {

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

private:
    std::list<std::string>  m_items;
    int                     m_index;
};

}

#endif
