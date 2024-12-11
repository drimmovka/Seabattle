#ifndef CLI_DISPLAYER_HPP
#define CLI_DISPLAYER_HPP

#include "GameMapViewModel.hpp"
#include "Abilities/AbilityType.hpp"
#include "ShipsManager.hpp"

#include <iostream>

namespace seabattle
{

class CLIDisplayer {

public:
    CLIDisplayer();

    ~CLIDisplayer();

    void displayUserShipInfo(ShipsManager& ships_manager);

    void displayUserGameMap(GameMapViewModel& game_map_view_model);

    void displayEnemyGameMap(GameMapViewModel& game_map_view_model);

    void displayMessage(const char *message);

    void displayUserFrontAbilityType(AbilityType ability_type);
};

} // seabattle

#endif // CLI_DISPLAYER_HPP