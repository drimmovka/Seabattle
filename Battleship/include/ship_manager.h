#ifndef SHIP_MANAGER_H_
#define SHIP_MANAGER_H_

#include "ship.h"

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