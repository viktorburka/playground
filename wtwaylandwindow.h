#ifndef WT_WAYLANDWINDOW_H
#define WT_WAYLANDWINDOW_H

#include <wayland-client.h>

class CtTempFile;

class WtWaylandWindow
{
public:
    WtWaylandWindow(int width, int height);
	~WtWaylandWindow();

    wl_display* display() const;

    static int windowWidth;
    static int windowHeight;

private:
    CtTempFile * m_mappedFile;
};

#endif
