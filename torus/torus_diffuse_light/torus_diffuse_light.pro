TEMPLATE = app

QT += gui opengl
CONFIG += c++11

SOURCES += main.cpp \
    applicationwindow.cpp \
    shaderprogram.cpp

HEADERS += \
    applicationwindow.h \
    shaderprogram.h

DISTFILES += \
    shaders/main_fsh.sh \
    shaders/main_vsh.sh
