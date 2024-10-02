#include <iostream>

#include "../include/coords.hpp"
#include "../include/ship.hpp"
#include "../include/collision_handler.hpp"
#include "../include/game_map.hpp"
#include "../include/ship_manager.hpp"
#include "../include/game_renderer.hpp"

int main() {
    GameMap game_map(10, 10);

    Ship a(5);
    Ship b(2);
    Ship c(3);
    Ship d(3);



    game_map.setShip(&a, {1, 2}, Ship::Orientation::kHorizontal);
    game_map.setShip(&b, {7, 7}, Ship::Orientation::kHorizontal);
    
    game_map.setShip(&c, {5, 5}, Ship::Orientation::kVertical);

    game_map.setShip(&d, {2, 4}, Ship::Orientation::kVertical);


    game_map.attack({1, 2}, 2);
    game_map.attack({2, 2}, 1);
    game_map.attack({3, 2}, 2);
    game_map.attack({4, 2}, 1);
    game_map.attack({5, 2}, 2);



    std::cout << (int)a.status() << std::endl;
    GameRenderer game_renderer(10, 10);
    game_renderer.renderGameMap(game_map);
}