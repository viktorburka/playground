#ifndef WTIMAGE_H
#define WTIMAGE_H

namespace Wt {

class PlatformImage;
class PaintBrush;

class WtImage
{
public:
    WtImage(int width, int height, char* data);

private:
    PlatformImage* m_platformImage;

    friend class PaintBrush;
};

}

#endif
