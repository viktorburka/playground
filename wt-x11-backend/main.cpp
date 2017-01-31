#include "application.h"
#include "wt-x11-driver.h"

using namespace Wt;

int main(int argc, char * argv[])
{
    Application application;
    WtX11DriverWindow window(800,600);
    window.show();
    application.run();
    return 0;
}
