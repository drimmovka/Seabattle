#include "../include/ship_manager.hpp"
#include "../include/ship.hpp"

#include <vector>
#include <iostream>

ShipManager::ShipManager() = default;
    
ShipManager::ShipManager(const std::initializer_list<int> ship_sizes) {
    for (auto& ship_size : ship_sizes) {
        Ship *new_ship = new Ship(ship_size);
        ships_.push_back(new_ship);
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