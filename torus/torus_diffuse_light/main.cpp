#include <QGuiApplication>

#include "applicationwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    ApplicationWindow window;
    window.resize(800,600);
    window.show();
    return app.exec();
}
