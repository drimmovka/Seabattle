#ifndef CLI_GAME_MAP_DISPLAYER_HPP
#define CLI_GAME_MAP_DISPLAYER_HPP

#include "GameMapViewModel.hpp"

#include <iostream>

namespace seabattle
{

class CLIGameMapDisplayer {

public:
    CLIGameMapDisplayer();

    ~CLIGameMapDisplayer();
    
    void outputUserGameMap(GameMapViewModel& game_map_view_model);

    void outputEnemyGameMap(GameMapViewModel& game_map_view_model);

};

} // namespace seabattle

#endif // CLI_GAME_MAP_DISPLAYER_HPP