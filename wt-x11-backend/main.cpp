#include "application-x11.h"
#include "wt-x11-driver.h"

int main(int argc, char * argv[])
{
    ApplicationX11 application;
    WtX11DriverWindow window(800,600);
    window.show();
    application.run();
    return 0;
}
