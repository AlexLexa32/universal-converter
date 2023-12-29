cmake_minimum_required(VERSION 3.26)
project(untitled11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(untitled11 main.cpp
        App.cpp
        App.h
        Fraction.h
        MegaInt.h
        solve.h
)
target_link_libraries(untitled11
        Qt::Core
        Qt::Gui
        Qt::Widgets
)