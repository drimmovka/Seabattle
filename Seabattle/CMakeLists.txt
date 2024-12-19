cmake_minimum_required(VERSION 3.8)

project(seabattle)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SOURCE_FILES
    ./src/Abilities/AbilitiesManager.cpp
    ./src/Abilities/AbilityFactory.cpp  
    ./src/Abilities/Bombing.cpp
    ./src/Abilities/BombingSpec.cpp
    ./src/Abilities/DoubleDamage.cpp
    ./src/Abilities/DoubleDamageSpec.cpp
    ./src/Abilities/Scanner.cpp
    ./src/Abilities/ScannerSpec.cpp

    ./src/Actions/Action.cpp
    ./src/Actions/ApplyBombing.cpp
    ./src/Actions/ApplyDoubleDamage.cpp
    ./src/Actions/ApplyScanner.cpp
    ./src/Actions/Attack.cpp
    ./src/Actions/InformAboutReadiness.cpp
    ./src/Actions/Load.cpp
    ./src/Actions/PlaceShipsRandomly.cpp
    ./src/Actions/Save.cpp
    ./src/Actions/SetSettings.cpp
    ./src/Actions/Stop.cpp

    ./src/Displayers/CLIDisplayer.cpp
    ./src/Displayers/GUIDisplayer.cpp
    ./src/Displayers/CLIGameMapDisplayer.cpp

    ./src/Exceptions/AbilityIsAlreadyUsedException.cpp
    ./src/Exceptions/ActionException.cpp
    ./src/Exceptions/AttackException.cpp
    ./src/Exceptions/FileException.cpp
    ./src/Exceptions/GameException.cpp
    ./src/Exceptions/ListenerException.cpp
    ./src/Exceptions/NoAbilitiesException.cpp
    ./src/Exceptions/ShipPlacementException.cpp
    ./src/Exceptions/ShipsAreNotPlacedException.cpp

    ./src/Listeners/CLIListener.cpp

    ./src/Coords.cpp
    ./src/Game.cpp
    ./src/GameMap.cpp
    ./src/GameController.cpp
    ./src/GameData.cpp
    ./src/GameDataHandler.cpp
    ./src/GameMapViewModel.cpp
    ./src/GameObserver.cpp
    ./src/Ship.cpp
    ./src/ShipsManager.cpp
    ./src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    sfml-graphics-d
    sfml-system-d
    sfml-window-d
    sfml-audio-d
    sfml-network-d)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)