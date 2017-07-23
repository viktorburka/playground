#ifndef WTEVENTLOOP_H
#define WTEVENTLOOP_H

class WtWaylandWindow;

class WtEventLoop
{
public:
    WtEventLoop();

    void run(WtWaylandWindow * window);
};

#endif // WTEVENTLOOP_H
