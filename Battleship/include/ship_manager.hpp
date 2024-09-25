#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_

#include "ship.hpp"

#include <vector>

class ShipManager {

public:
    ShipManager();
    
    ShipManager(const std::vector<int>& ship_sizes); // change to initializer list
    
    ~ShipManager();

private:
    std::vector<Ship> ships_;
};

#endif