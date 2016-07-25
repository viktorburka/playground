import qbs

CppApplication {
    consoleApplication: true
    files: [
        "cttempfile.cpp",
        "cttempfile.h",
        "main.cpp",
        "wteventloop.cpp",
        "wteventloop.h",
        "wtwaylandwindow.cpp",
        "wtwaylandwindow.h",
    ]
    cpp.dynamicLibraries: "wayland-client"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
