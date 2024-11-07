#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_

#include "Ship.hpp"
#include "GameMap.hpp"

#include <vector>

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
    
    bool allPlacedOnGameMap() const;
    
    void addShip(int ship_size);
    
    void removeShip(int ship_index);

    // TEMPORARY FOR DEBUGGING!!!
    Ship* operator[](int ship_index);

private:
    
    std::vector<Ship*> ships_;

};

}


#endif // SHIP_MANAGER_HPP_