#include <iostream>

#include "wtwaylandwindow.h"
#include "wteventloop.h"

using namespace std;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    WtWaylandWindow ww(480, 256);
    WtEventLoop eventLoop;
    eventLoop.run(&ww);
    return 0;
}
