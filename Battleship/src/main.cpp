#include <iostream>

#include "../include/coords.hpp"
#include "../include/ship.hpp"
#include "../include/collision_handler.hpp"
#include "../include/game_field.hpp"
#include "../include/ship_manager.hpp"


int main() {
    std::cout << "test" << std::endl;
    Ship a(5, Ship::Orientation::horizontal, {1, 2});
    
    Ship b(Ship(5, Ship::Orientation::horizontal, {1, 2}));
    std::cout << b.getSize() << " " << b.getMaxSegmentHealth() << " " << (int)b.getOrientation() << " " << b.getTopLeft().x << std::endl;

    b = a;
    
    std::cout << b.getSize() << " " << b.getMaxSegmentHealth() << " " << (int)b.getOrientation() << " " << b.getTopLeft().x << std::endl;
    CollisionHandler collision_handler;
    GameField game_field;
    ShipManager ship_manager;
    std::cout << "test" << std::endl;
}