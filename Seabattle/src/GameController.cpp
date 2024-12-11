#include "GameController.hpp"


namespace seabattle
{

GameController::GameController(Game& game)
    : _game(game)
{}

void GameController::play() {
    bool run_new_game = true;
    while (run_new_game) {
        _displayer.displayMessage( "Game started" );

        this->runGame();
        _displayer.displayMessage( "Restart game: 1 or 0" );
        run_new_game = _listener.userWantToRunGame();
    }
}

void GameController::runGame() {
    _game.run();
    
    while (_game.isRunning()) {
        
        if (_game.currentPhase() != GamePhase::kSettingSettings) {
            // display info here (create new class + observer to show needed info)
            // game maps, ships managers must be initialized by now using set ("set settings") command
            this->displayGameInfo();
        }
        
        // trying to get command from user
        Action *action = nullptr;
        while (action == nullptr) { // if listener will return any type of command it wont be nullptr
            try {
                // valid command input should be guaranteed (no parsing right now)
                action = _listener.getAction();
            } catch(const ListenerException& e) {
                _displayer.displayMessage(e.what());
            }
        }
        
        // trying to exec command
        try {
            action->execute(_game);
        } catch(const std::exception& e) {
            _displayer.displayMessage(e.what());
            // if command was not executed
            // then game phase is not suitable or command params are invalid
            // -> trying to get another command
            continue;
        }
        
        // we will get into this part of the cycle only if the game_data (by set action) is initialized

        if (!_game.isRunning()) {break;} // if "stop" command was executed
        
        _game.tryToAddAbilitiesForUser();

        if (_game.roundWon()) { // reset game loop with old user data
            _game.resetEnemy();
            _game.increaseScore();
            _displayer.displayMessage("Round won! Score increased");
            continue;
        }

        if (_game.isEnemyMove()) {
            _game.enemyMakeMove(); // enemy cannot make move until user attacks
            this->displayGameInfo();
        }

        if (_game.over()) {
            _game.stop();
            _displayer.displayMessage("Game over(");
        } // game can be over only if enemy wins after enemy move


    }
}

void GameController::displayGameInfo() {
    _displayer.displayMessage("Current score:");
    _displayer.displayMessage(std::to_string(_game.score()).c_str());
    _displayer.displayUserFrontAbilityType(_game.userAvailableAbilityType());
    _displayer.displayUserGameMap(*_game.userGameMapViewModel());
    _displayer.displayUserGameMap(*_game.enemyGameMapViewModel()); // change to Enemy for release version
    _displayer.displayMessage("\n");
}

} // namespace seabattle