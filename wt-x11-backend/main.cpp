#include "application.h"
#include "wt-x11-driver.h"
#include "pushbutton.h"

using namespace Wt;

int main(int argc, char * argv[])
{
    Application application;

    WtDriverWidget window(800,600);
    PushButton pb(&window);
    //pb.setSize(200, 100);

    window.show();

    application.run();

    return 0;
}
