#ifndef GAME_HPP
#define GAME_HPP

#include "GameData.hpp"
#include "GameMapViewModel.hpp"
#include "Abilities/iAbilitySpec.hpp"
#include "Abilities/AbilityType.hpp"
#include "GameDataHandler.hpp"
#include "Exceptions/ShipsAreNotPlacedException.hpp"
#include "Exceptions/ShipPlacementException.hpp"
#include "Exceptions/AbilityIsAlreadyUsedException.hpp"
#include "GameObserver.hpp"

#include <iostream>

namespace seabattle
{

class Game {

public:
    
    Game(GameDataHandler& game_data_handler);
    
    ~Game();

    void signObserver(GameObserver& observer);

    bool isRunning();

    int score();

    bool roundWon();
    
    bool over();

    void run();

    void stop();

    GamePhase currentPhase() const;

    AbilityType userAvailableAbilityType();

    bool isEnemyMove() const;
    
    GameMapViewModel *userGameMapViewModel();

    GameMapViewModel *enemyGameMapViewModel();

    GameData *gameData();
    
    void increaseScore();

    void resetEnemy();

    void tryToAddAbilitiesForUser();

    void setSettings(int game_map_width, int game_map_height, std::vector<int>& ship_sizes);

    void userPlaceShipsRandomly();

    void allowUserMakingMoves();

    void userAttack(Coords coords);

    void userApplyAbility(iAbilitySpec *ability_spec);

    void userSave(const std::string save_file_name);

    void userLoad(const std::string load_file_name);

    void enemyMakeMove();

private:
    GameData *_game_data;
    GameDataHandler& _game_data_handler;
    bool _is_running;
    bool _should_be_displayed;
    GameMapViewModel *_user_game_map_view_model;
    GameMapViewModel *_enemy_game_map_view_model;

    void setGamePhase(GamePhase next_game_phase);

    void initUser();

    void initEnemy();
    
    void placeShipsRandomly(ShipsManager *ships_manager, GameMap *game_map);

};

} // namespace seabattle


#endif // GAME_HPP