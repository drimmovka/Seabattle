#include "../include/ship_manager.h"
#include "../include/ship.h"

#include <vector>

class ShipManager {

public:
    ShipManager() = default;
    
    ShipManager(const std::vector<int>& ship_sizes) { // change to initializer list
        for (auto& ship_size : ship_sizes) {
            ships_.emplace_back(ship_size);
        }
    }
    
    ~ShipManager() = default;
private:
    std::vector<Ship> ships_;
};