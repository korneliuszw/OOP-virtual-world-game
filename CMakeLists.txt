cmake_minimum_required(VERSION 3.20)
project(Projekt1)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(Projekt1 main.cpp
        Swiat.h
        Swiat.cpp
        Organizm.cpp
        Organizm.h
        WindowManager.cpp
        WindowManager.h
        Zwierzeta.cpp
        Zwierzeta.h
        Logger.cpp
        Logger.h
        Rosliny.cpp
        Rosliny.h
        Player.cpp
        Player.h
        Player.h
        ScrollableList.cpp
        ScrollableList.h
        Loader.cpp
        Loader.h
        Loader.h
        Loader.h
)
target_link_libraries(Projekt1 PRIVATE ${CURSES_LIBRARIES})