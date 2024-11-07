cmake_minimum_required(VERSION 3.8)

project(battleship)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SOURCE_FILES
    ./src/main.cpp
    ./src/CLIRenderer.cpp
    ./src/Coords.cpp
    ./src/GameMap.cpp
    ./src/GameMapViewModel.cpp
    ./src/GUIRenderer.cpp
    ./src/Ship.cpp
    ./src/ShipManager.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    sfml-graphics-d
    sfml-system-d
    sfml-window-d
    sfml-audio-d
    sfml-network-d)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)