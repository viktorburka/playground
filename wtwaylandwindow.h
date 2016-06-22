#ifndef WT_WAYLANDWINDOW_H
#define WT_WAYLANDWINDOW_H

#include <wayland-client.h>

class WtWaylandWindow
{
public:
	WtWaylandWindow();
	~WtWaylandWindow();

private:
	wl_display * display;
};

#endif
