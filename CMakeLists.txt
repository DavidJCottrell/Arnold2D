cmake_minimum_required(VERSION 3.27)
project(arnold)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(arnold main.cpp
        Game.cpp
        Game.h
        Player.cpp
        Player.h
        Entity.h
        Enemy.cpp
        Enemy.h
        Constants.h)

target_link_directories(arnold PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(arnold PUBLIC SDL2)
