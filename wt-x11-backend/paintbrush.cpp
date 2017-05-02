#include "paintbrush.h"
#include "widget.h"
#include "rect.h"
#include "wt.h"
#include "wtimage.h"
#include "platformimage.h"

#ifdef GP_X11
#include "paintbrush-x11.h"
#include "window-x11.h"
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace Wt;

PaintBrush::PaintBrush(Widget* widget)
    : m_surface(widget)
{
#ifdef GP_X11
    WindowX11* winX11 = static_cast<WindowX11*>(widget->m_platformWin.get());
    m_platformBrush = new PaintBrushX11(winX11);
#endif
}

void PaintBrush::drawRect(const Rect & rect)
{
    drawRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void PaintBrush::drawRect(int x, int y, int width, int height)
{
    m_platformBrush->drawRect(x, y, width, height);
}

void PaintBrush::fillRect(const Rect & rect)
{
    fillRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void PaintBrush::fillRect(int x, int y, int width, int height)
{
    int adjustedWidth = x + width >= m_surface->width() ? m_surface->width()-x : width;
    int adjustedHeight = y + height >= m_surface->height() ? m_surface->height()-y : height;

    m_platformBrush->fillRect(x, y, adjustedWidth, adjustedHeight);
}

void PaintBrush::setPaintColor(const std::string & colorName)
{
    m_platformBrush->setPaintColor(colorName);
}

//void PaintBrush::drawText(const std::string & text)
//{
//    m_platformBrush->drawText(text);
//}

void PaintBrush::drawText(const std::string & text, const Rect & rect)
{
    m_platformBrush->drawText(text, rect);
}

void PaintBrush::drawGlyph(const std::string & str)
{
    auto validate = [](FT_Error error,
                       const std::string & msg)
    {
        if (error != FT_Err_Ok) {
            WtPrint() << msg;
            exit(-1);
        }
    };

    auto TRUNC = [](int x) { return (x >> 6); };

    const std::string fontFile = "/home/victor/Dev/roboto-master/src/hinted/Roboto-Regular.ttf";
    const int pointSize = 32;

    FT_Library library     = 0;
    FT_Face    face        = 0;
    FT_UInt    glyph_index = 0;
    FT_Error   error       = FT_Err_Ok;

    error = FT_Init_FreeType(&library);
    validate(error, "Error initializing FreeType library");

    error = FT_New_Face(library, fontFile.c_str(), 0, &face);
    validate(error, "Error creating font face");

    error = FT_Set_Char_Size(face, 0,
                             pointSize * 64,
                             m_surface->dpiX(),
                             m_surface->dpiY());
    validate(error, "Error setting font size");


    glyph_index = FT_Get_Char_Index(face, str[0]);
    error = FT_Load_Glyph(face, glyph_index,
                          FT_LOAD_DEFAULT);
    validate(error, "Error setting font size");

    FT_Pos left   = face->glyph->metrics.horiBearingX;
    FT_Pos right  = left + face->glyph->metrics.width;
    FT_Pos top    = face->glyph->metrics.horiBearingY;
    FT_Pos bottom = top - face->glyph->metrics.height;

    Rect glyphRect = Rect(TRUNC(left), -TRUNC(top) + 1,
                          TRUNC(right - left) + 1, TRUNC(top - bottom) + 1);

    WtPrint() << "Glyph rect:" << glyphRect;

    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    validate(error, "Error rendering glyph");

    WtPrint() << "Pixel mode:" << (int)face->glyph->bitmap.pixel_mode;

    int width  = 100;
    int height = 100;

    char* data = (char*)malloc(width*height*4);
    int size = width*height*4;
    for(int i=0; i<size; i+=4) {
        //                    B     G     R     A
        const char bgra[] = { 0x00, 0x00, 0xFF, 0x00 };
        memcpy(data+i, bgra, 4);
    }

    WtImage image("/home/victor/Dev/test.png");
    drawImage(image, Rect(0, 0, image.width(), image.height()));

//    WtImage image(width, height, data);
//    drawImage(image, Rect(0, 0, width, height));

//    WtImage image(m_face->glyph->bitmap.buffer,
//                  m_face->glyph->bitmap.width,
//                  m_face->glyph->bitmap.rows,
//                  m_face->glyph->bitmap.pitch,
//                  QImage::Format_Indexed8);
}

void PaintBrush::drawImage(const WtImage & image, const Rect & rect)
{
    m_platformBrush->drawImage(image, rect);
}
