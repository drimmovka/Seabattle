#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_

#include "ship.hpp"
#include "game_map.hpp"

#include <vector>
#include <initializer_list>

class ShipManager {

public:
    ShipManager();
    
    ShipManager(const std::initializer_list<int> ship_sizes);
    
    ShipManager(const ShipManager& other);

    ShipManager(ShipManager&& other);

    ~ShipManager();

    ShipManager& operator=(const ShipManager& other);
    
    ShipManager& operator=(ShipManager&& other);

private:
    std::vector<Ship*> ships_;
};

#endif // SHIP_MANAGER_HPP_