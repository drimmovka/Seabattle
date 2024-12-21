#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include "GameMap.hpp"
#include "ShipsManager.hpp"
#include "Abilities/AbilitiesManager.hpp"
#include "GamePhase.hpp"
#include "Exceptions/FileException.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace seabattle
{

class GameData {

public:

    GamePhase game_phase;
    bool is_enemy_move;
    bool ability_has_been_applied;
    int score;

    std::vector<int> ship_sizes;
    int game_map_width;
    int game_map_height;

    GameMap *user_game_map;
    ShipsManager *user_ships_manager;
    AbilitiesManager *user_abilities_manager;
    int *user_damage;
    bool *user_scanner_result;

    GameMap *enemy_game_map;
    ShipsManager *enemy_ships_manager;
    int *enemy_alive_ships_number;

    GameData();

    ~GameData();
    
    friend std::ostream& operator<<(std::ostream& os, const GameData& game_data);
    
    friend std::istream& operator>>(std::istream& is, GameData& game_data);

};

} // namespace seabattle


#endif // GAME_DATA_HPP