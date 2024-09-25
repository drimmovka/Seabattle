#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_

#include "ship.hpp"

#include <vector>

class ShipManager {

public:
    ShipManager();
    
    ShipManager(const std::vector<int>& ship_sizes); // change to initializer list
    
    ShipManager(const ShipManager& other);

    ShipManager(ShipManager&& other);

    ~ShipManager();

    ShipManager& operator=(const ShipManager& other);
    ShipManager& operator=(ShipManager&& other);

private:
    std::vector<Ship> ships_;
};

#endif