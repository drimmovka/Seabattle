#ifndef SHIPS_MANAGER_HPP
#define SHIPS_MANAGER_HPP

#include "Ship.hpp"
#include "GameMap.hpp"

#include <vector>
#include <fstream>
#include <iostream>

namespace seabattle
{

class ShipsManager {

public:
    ShipsManager();
    
    explicit ShipsManager(const std::vector<int> &ship_sizes);
    
    ShipsManager(const ShipsManager& other);

    ShipsManager(ShipsManager&& other);

    ~ShipsManager();

    ShipsManager& operator=(const ShipsManager& other);
    
    ShipsManager& operator=(ShipsManager&& other);

    int shipsNumber() const;

    int aliveShipsNumber() const;

    bool allDestroyed() const;
    
    bool allPlacedOnGameMap() const;
    
    void addShip(Ship *new_ship);
    
    void removeShip(int ship_index);

    Ship* operator[](int ship_index);

    friend std::ostream& operator<<(std::ostream& os, ShipsManager& ships_manager);

    friend std::istream& operator>>(std::istream& is, ShipsManager& ships_manager);

private:
    
    std::vector<Ship*> ships_;

};

} // namespace seabattle

#endif // SHIP_MANAGER_HPP