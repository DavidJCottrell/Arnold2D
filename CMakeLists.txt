cmake_minimum_required(VERSION 3.22.1)
project(arnold)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_library(ZeroMQ czmq REQUIRED)

add_executable(arnold main.cpp
        Game.cpp
        Game.h
        Entities/Player.cpp
        Entities/Player.h
        Entities/Entity.h
        Entities/Enemy.cpp
        Entities/Enemy.h
        Constants.h
        Entities/Projectile.cpp
        Entities/Projectile.h
        MessageHandler.h
        MessageHandler.cpp
)

target_link_directories(arnold PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(arnold PUBLIC SDL2 czmq zmq)
