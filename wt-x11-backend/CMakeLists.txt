cmake_minimum_required (VERSION 2.6)
project (wt-x11-driver)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(wt-x11-driver
               main.cpp
               application.cpp
               application.h
               platforms/xlib/window-x11.cpp
               platforms/xlib/window-x11.h
               platforms/xlib/application-x11.cpp
               platforms/xlib/application-x11.h
#               interfaces/platformapplication.cpp
               interfaces/platformapplication.h
#               interfaces/window.cpp
               interfaces/window.h
               verification.cpp
               verification.h
               display-x11.cpp
               display-x11.h
               paintbrush.cpp
               paintbrush.h
               wt-x11-driver.cpp
               wt-x11-driver.h
               pushbutton.cpp
               pushbutton.h
               wtlabel.cpp
               wtlabel.h
               widget.cpp
               widget.h
               bindevent.cpp
               bindevent.h
               listview.cpp
               listview.h
               rect.cpp
               rect.h
               wt.cpp
               wt.h
               types.h)
target_link_libraries(wt-x11-driver X11)
add_definitions(-DGP_X11)
add_definitions(-DVISUAL_DEBUG)
target_include_directories(wt-x11-driver PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/platforms/xlib
  ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
)
