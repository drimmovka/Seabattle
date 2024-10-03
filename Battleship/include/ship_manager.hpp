#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_

#include "ship.hpp"
#include "game_map.hpp"

#include <stdexcept> // FOR DEBUGGING HERE (REMOVE FROM H)

#include <vector>
#include <initializer_list>

// MAKE SHIP_ID AND USE UNORDERED_SET/UNORDERED_MAP INSTEAD OF VECTOR!!!

// mb u should check if all ships are seted before starting the game?

namespace battleship
{

class ShipManager {

public:
    ShipManager();
    
    ShipManager(const std::vector<int> &ship_sizes);
    
    ShipManager(const ShipManager& other);

    ShipManager(ShipManager&& other);

    ~ShipManager();

    ShipManager& operator=(const ShipManager& other);
    
    ShipManager& operator=(ShipManager&& other);

    int shipsNumber() const;

    bool allDestroyed() const;
    
    void addShip(int ship_size);
    
    void removeShip(int ship_index);

    void displayInfo() const;

    // TEMPORARY FOR DEBUGGING!!!
    Ship* operator[](int ship_index) {
        if (ship_index < 0 || ship_index >= shipsNumber()) {
            throw std::out_of_range("segment index out of range");
        }
        return ships_[ship_index];
    }

private:
    std::vector<Ship*> ships_;
};

}


#endif // SHIP_MANAGER_HPP_