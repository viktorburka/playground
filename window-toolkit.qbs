import qbs

CppApplication {
    consoleApplication: true
    files: ["main.cpp", "wtwaylandwindow.cpp", "wtwaylandwindow.h"]
    cpp.dynamicLibraries: "wayland-client"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
