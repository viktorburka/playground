#ifndef WTLABEL_H
#define WTLABEL_H

#include "widget.h"

#include <string>

/*class TestObj
{
public:
    TestObj() { str = "Hello!"; }
    std::string str;
};*/

namespace Wt {

class WtLabel: public Widget
{
public:
    WtLabel(Widget* parent);

    std::string text() const;
    void setText(const std::string & text);

    //void test(TestObj && t);

protected:
    void drawEvent(int x, int y, int width, int height);

private:
    std::string m_text;
};

}

#endif
