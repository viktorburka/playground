cmake_minimum_required (VERSION 2.6)
project (wt-x11-driver)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(wt-x11-driver
               main.cpp
               window-x11.cpp
               window-x11.h
               verification.h
               display-x11.cpp
               display-x11.h
               application-x11.cpp
               application-x11.h
               paintbrush.cpp
               paintbrush.h
               wt-x11-driver.cpp
               wt-x11-driver.h)
target_link_libraries(wt-x11-driver X11)
