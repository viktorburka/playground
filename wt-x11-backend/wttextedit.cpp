#include "wttextedit.h"
#include "paintbrush.h"

using namespace Wt;

WtTextEdit::WtTextEdit(Widget* parent)
    : Widget(parent)
{
}

void WtTextEdit::setText(const std::string & text)
{
    m_text = text;
    repaint();
}

void WtTextEdit::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    //pb.drawText();
    pb.drawGlyph("A");
}
