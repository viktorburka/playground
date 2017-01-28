#ifndef DISPLAYX11_H
#define DISPLAYX11_H

#include <X11/Xlib.h>

class DisplayX11
{
public:
    static Display* currentDisplay();
    static GC currentGC();
    
    static Display* display;
    static GC gc;
};

#endif
