#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Game.hpp"
#include "Listeners/CLIListener.hpp"
#include "Displayers/CLIDisplayer.hpp"
#include "Exceptions/ListenerException.hpp"

#include <unordered_map>

namespace seabattle
{

class GameController {
public:
    
    GameController(Game& game);

    void play();

private:
    void runGame();
    
    void displayGameInfo();

private:
    Game& _game;
    CLIListener _listener;
    CLIDisplayer _displayer;
};

} // namespace seabattle



#endif // GAME_CONTROLLER_HPP