#include "GameDataHandler.hpp"
#include "Game.hpp"
#include "GameController.hpp"

#include <iostream>

using namespace seabattle; // REMOVE


int main() {
    std::cout << "Execution started" << std::endl;

    GameDataHandler game_data_handler;
    Game game(game_data_handler);
    GameController game_controller(game);
    game_controller.play();
    
    std::cout << "Execution successful" << std::endl;
    return 0;
}