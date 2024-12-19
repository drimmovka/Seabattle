#include "GameDataHandler.hpp"
#include "Game.hpp"
#include "GameController.hpp"
#include "Displayers/CLIGameMapDisplayer.hpp"

#include <iostream>

using namespace seabattle; // REMOVE


int main() {
    std::cout << "Execution started" << std::endl;

    GameDataHandler game_data_handler;
    Game game(game_data_handler);
    GameController<CLIListener, CLIGameMapDisplayer> game_controller(game);
    game_controller.play();
    
    std::cout << "Execution successful" << std::endl;
    return 0;
}