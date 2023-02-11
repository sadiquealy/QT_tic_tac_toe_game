cmake_minimum_required(VERSION 3.16)

project(Tic-Taco-fix VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appTic-Taco-fix
    main.cpp
    gameboard.h gameboard.cpp
)

qt_add_qml_module(appTic-Taco-fix
    URI Tic-Taco-fix
    VERSION 1.0    
)

set_target_properties(appTic-Taco-fix PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Resources:
set(qml_resource_files
    "qml/main.qml"
)

qt6_add_resources(appTic-Taco-fix "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)

set(images_resource_files
    "qml/images/0.png"
    "qml/images/x.png"
    "qml/images/bg.png"
)

qt6_add_resources(appTic-Taco-fix "images"
    PREFIX
        "/"
    FILES
        ${images_resource_files}
)

target_link_libraries(appTic-Taco-fix
    PRIVATE Qt6::Quick)

install(TARGETS appTic-Taco-fix
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
