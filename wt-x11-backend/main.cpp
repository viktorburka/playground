#include "application-x11.h"
#include "window-x11.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    ApplicationX11 application;
    WindowX11 window(800,600);
    window.show();
    application.run();
    return 0;
}
