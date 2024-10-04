#include <iostream>


// MAKE ONE HEADER FOR ALL aka battleship.h
#include "../include/coords.hpp"
#include "../include/ship.hpp"
#include "../include/collision_handler.hpp"
#include "../include/game_map.hpp"
#include "../include/ship_manager.hpp"
#include "../include/game_renderer.hpp"

int main() {
    battleship::GameMap game_map(10, 10);
    battleship::GameRenderer game_renderer(10, 10);

    battleship::ShipManager ship_manager({5, 2, 3, 3, 5, 1});

    ship_manager.displayInfo();

    ship_manager.removeShip(4);
    
    ship_manager.displayInfo();

    // std::cout << ship_manager.shipsNumber() << std::endl;
    // std::cout << ship_manager.allDestroyed() << std::endl;
    
    // ship_manager.removeShip(1);
    
    // std::cout << ship_manager.shipsNumber() << std::endl;
    // std::cout << ship_manager.allDestroyed() << std::endl;

    // // ship_manager.removeShip(0);
    // // ship_manager.removeShip(0);
    // // ship_manager.removeShip(0);
    

    game_map.setShip(ship_manager[0], {1, 2}, battleship::Ship::Orientation::kHorizontal);
    
    game_map.setShip(ship_manager[1], {7, 7}, battleship::Ship::Orientation::kHorizontal);
    
    game_map.setShip(ship_manager[2], {5, 5}, battleship::Ship::Orientation::kVertical);

    game_map.setShip(ship_manager[3], {2, 4}, battleship::Ship::Orientation::kVertical);

    game_map.setShip(ship_manager[4], {0, 0}, battleship::Ship::Orientation::kVertical);


    game_renderer.renderGameMap(game_map);
    std::cout << std::endl;
    
    game_map.attack({2, 5}, 1);
    game_renderer.renderGameMap(game_map);
    std::cout << std::endl;

    game_map.setShip(ship_manager[3], {1, 4}, battleship::Ship::Orientation::kVertical);

    game_renderer.renderGameMap(game_map);
    std::cout << std::endl;

    game_map.setShip(ship_manager[3], {1, 4}, battleship::Ship::Orientation::kHorizontal);



    game_map.attack({1, 2}, 2);
    game_map.attack({2, 2}, 1);
    game_map.attack({3, 2}, 2);
    game_map.attack({4, 2}, 1);
    game_map.attack({5, 2}, 2);

    game_map.attack({-1, -1}, 2);
    game_map.attack({9, 9}, 2);

    // game_map.attack({0, 0}, -10); // see how to handle invalid arguments
    game_map.attack({0, 0}, 10);


    game_renderer.renderGameMap(game_map);
    std::cout << std::endl;

    
    std::cout << "All destroyed: " << ship_manager.allDestroyed() << std::endl;
    std::cout << "Ship[0] status: " << (int)ship_manager[0]->status() << std::endl;

    ship_manager.displayInfo();
}