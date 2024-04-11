cmake_minimum_required(VERSION 3.22.1)
project(arnold)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_library(ZeroMQ czmq REQUIRED)

add_executable(arnold main.cpp
        Engine/Game.cpp
        Engine/Game.h
        Entities/Player.cpp
        Entities/Player.h
        Entities/Entity.h
        Entities/Enemy.cpp
        Entities/Enemy.h
        Constants.h
        Entities/Projectile.cpp
        Entities/Projectile.h
        Engine/MessageHandler.h
        Engine/MessageHandler.cpp
        Engine/AudioLoader.cpp
        Engine/AudioLoader.h
        Engine/Utilities/Utils.h
        Engine/Utilities/Utils.cpp
        Engine/Utilities/Geometry.h
)

target_link_directories(arnold PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(arnold PUBLIC SDL2 SDL2_mixer SDL2_image czmq zmq)
