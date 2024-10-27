cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

project(battleship)

set(SOURCE_FILES
    ./src/main.cpp
    ./src/Coords.cpp
    ./src/GameMap.cpp
    ./src/GameRenderer.cpp
    ./src/ShipManager.cpp
    ./src/Ship.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})