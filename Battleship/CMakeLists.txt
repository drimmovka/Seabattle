cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

project(battleship)

set(SOURCE_FILES
    ./src/collision_handler.cpp
    ./src/entity.cpp
    ./src/game_field.cpp
    ./src/game_renderer.cpp
    ./src/main.cpp
    ./src/ship.cpp
    ./src/ship_manager.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


