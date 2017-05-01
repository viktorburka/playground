#ifndef WTIMAGE_H
#define WTIMAGE_H

namespace Wt {

class PlatformImage;

class WtImage
{
public:
    WtImage(int width, int height, char* data);

private:
    PlatformImage* m_platformImage;
#ifdef GP_X11
    friend class PaintBrushX11;
#endif
};

}

#endif
