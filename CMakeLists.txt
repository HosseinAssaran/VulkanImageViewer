# Generated from vulkanimageviewer.pro.

cmake_minimum_required(VERSION 3.16)
project(vulkanimageviewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)


qt_add_executable(vulkanimageviewer
    vulkanimageviewer.cpp vulkanimageviewer.h
    main.cpp
)
set_target_properties(vulkanimageviewer PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(vulkanimageviewer PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)


# Resources:
set(vulkanimageviewer_resource_files
    "texture_frag.spv"
    "texture_vert.spv"
)

qt6_add_resources(vulkanimageviewer "vulkanimageviewer"
    PREFIX
        "/"
    FILES
        ${vulkanimageviewer_resource_files}
)

