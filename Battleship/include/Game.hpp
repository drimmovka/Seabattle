#ifndef GAME_HPP_
#define GAME_HPP_

#include "GameMapViewModel.hpp"
#include "GameMap.hpp"

namespace battleship
{

class Game {
public:
    Game();

    GameMap game_map;
    GameMapViewModel game_map_view_model;
};

} // battleship


#endif // GAME_HPP_