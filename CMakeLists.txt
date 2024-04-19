cmake_minimum_required(VERSION 3.22.1)
project(arnold)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
find_library(ZeroMQ czmq REQUIRED)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(arnold src/main.cpp
        src/Engine/Game.cpp
        include/Game.h
        src/Entities/Player/Player.cpp
        include/Player.h
        include/Entity.h
        src/Entities/Enemies/Enemy.cpp
        include/Enemy.h
        include/Constants.h
        src/Entities/Player/Projectile.cpp
        include/Projectile.h
        include/MessageHandler.h
        src/Engine/TextureManager.cpp
        include/TextureManager.h
        src/Engine/Map.cpp
        include/Map.h
        src/Engine/MessageHandler.cpp
        include/Utils.h
        src/Engine/Utils.cpp
        src/Entities/Enemies/Juggernaut.cpp
        include/Juggernaut.h
        include/Arnold.h
        include/Weapon.h
        src/Entities/Player/Weapon.cpp
        src/Entities/Pickups/WeaponPickup.cpp
        include/WeaponPickup.h
        src/Entities/Pickups/HealthPickup.cpp
        include/HealthPickup.h
)

target_link_directories(arnold PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(arnold PUBLIC SDL2 SDL2_mixer SDL2_image czmq zmq)
