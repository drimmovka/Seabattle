#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Game.hpp"
#include "Listeners/CLIListener.hpp"
#include "Displayers/CLIDisplayer.hpp"
#include "Exceptions/ListenerException.hpp"
#include "GameObserver.hpp"

#include <unordered_map>

namespace seabattle
{

template<typename ListenerT, typename GameMapDisplayerT>
class GameController {
public:
    
    GameController(Game& game)
        : _game(game)
    {
        _game.signObserver(_observer);
    }

    void play() {
        bool run_new_game = true;
        while (run_new_game) {
            _displayer.outputHelp(_listener.keysMap()); _displayer.outputEmptyLine();
            _displayer.outputGameStartMessage(); _displayer.outputEmptyLine();


            this->runGame();
            _displayer.outputRestartQuestion();
            run_new_game = _listener.userWantToRunGame();
        }
    }

private:

    void runGame() {
        _game.run();
        
        while (_game.isRunning()) {
            
            // display after enemy move or in the pre-game stage
            if (_observer.shouldBeDisplayed()) {
                this->displayGameInfo();
            }
            
            // trying to get command from user
            Action *action = nullptr;
            while (action == nullptr) { // if listener will return any type of command it wont be nullptr
                _displayer.outputAskForCommandMessage();
                try {
                    // valid command input should be guaranteed (no parsing right now)
                    action = _listener.getAction();
                } catch(const ListenerException& e) {
                    _displayer.outputError(e);
                }
            }
            
            // trying to exec command
            try {
                action->execute(_game);
            } catch(const std::exception& e) {
                _displayer.outputError(e);
                // if command was not executed
                // then game phase is not suitable or command params are invalid
                // -> trying to get another command
                continue;
            }
            
            // we will get into this part of the cycle only if the game_data (by set action) is initialized

            if (!_game.isRunning()) {break;} // if "stop" command was executed
            
            _game.tryToAddAbilitiesForUser();

            // display after user move
            if (_observer.shouldBeDisplayed()) {
                this->displayGameInfo();
            }

            if (_game.roundWon()) { // reset game loop with old user data
                _game.resetEnemy();
                _game.increaseScore();
                _displayer.outputWinMessage();
                continue;
            }

            if (_game.isEnemyMove()) {
                _game.enemyMakeMove(); // enemy cannot make move until user attacks
            }

            if (_game.over()) {
                this->displayGameInfo();
                _game.stop();
                _displayer.outputLooseMessage();
            } // game can be over only if enemy wins after enemy move
        }
    }
    
    void displayGameInfo() {
        _displayer.outputCurrentScore(_game.score());
        _displayer.outputUserFrontAbilityType(_game.userAvailableAbilityType());
        _displayer.outputGameMaps(*_game.userGameMapViewModel(), *_game.enemyGameMapViewModel());
        _displayer.outputEmptyLine();
    }

private:
    Game& _game;
    ListenerT _listener;
    CLIDisplayer<GameMapDisplayerT> _displayer;
    GameObserver _observer;
};

} // namespace seabattle

#endif // GAME_CONTROLLER_HPP