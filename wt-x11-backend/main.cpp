#include "application.h"
#include "wt-x11-driver.h"
#include "pushbutton.h"
#include "wtlabel.h"

#include "stdio.h"

#include <string>
#include <string.h>

using namespace Wt;


int main(int argc, char * argv[])
{
    Application application;

    WtDriverWidget window(800,600);

    PushButton pb(&window);
    pb.setSize(150, 80);
    pb.setPosition((window.width()-pb.width())/2,
                   (window.height()-pb.height())/2);
    pb.setText("Button");

    WtLabel label(&window);
    label.setSize(150, 50);
    label.setPosition(10, 10);
    label.setText("Hello!");

    pb.bindEvent("click").to([&label]{label.setText("Button");});

    window.show();

    application.run();

    return 0;
}
