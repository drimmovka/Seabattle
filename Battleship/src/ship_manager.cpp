#include "../include/ship_manager.hpp"
#include "../include/ship.hpp"

#include <vector>


ShipManager::ShipManager() = default;
    
ShipManager::ShipManager(const std::vector<int>& ship_sizes) { // change to initializer list
    for (auto& ship_size : ship_sizes) {
        ships_.emplace_back(ship_size);
    }
}

ShipManager::ShipManager(const ShipManager& other)
    : ships_(other.ships_)
{}

ShipManager::ShipManager(ShipManager&& other)
    : ships_(std::move(other.ships_))
{}

ShipManager::~ShipManager() = default;

ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) {
        this->ships_ = other.ships_;
    }
    return *this;
}

ShipManager& ShipManager::operator=(ShipManager&& other) {
    if (this != &other) {
        this->ships_ = std::move(other.ships_);
    }
    return *this;
}