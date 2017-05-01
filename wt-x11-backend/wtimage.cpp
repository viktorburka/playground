#include "wtimage.h"

#ifdef GP_X11
#include "image-x11.h"
#endif

using namespace Wt;

WtImage::WtImage(int width, int height, char* data)
{
#ifdef GP_X11
    m_platformImage = new ImageX11(width, height, data);
#endif
}
