#include "ShipManager.hpp"

#include "Ship.hpp"

#include <stdexcept> // TEMPORARY FOR DEBUGGING
#include <vector>
#include <iostream>

namespace battleship
{

ShipManager::ShipManager() = default;
    
ShipManager::ShipManager(const std::vector<int> &ship_sizes) {
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

ShipManager::~ShipManager() {
    for (auto& ship : ships_) {
        delete ship;
    }
}

ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) {
        ships_ = other.ships_;
    }
    return *this;
}

ShipManager& ShipManager::operator=(ShipManager&& other) {
    if (this != &other) {
        ships_ = std::move(other.ships_);
    }
    return *this;
}

bool ShipManager::allDestroyed() const {
    for (auto& ship : ships_) {
        if (ship->status() != Ship::Status::kDestroyed) {
            return false;
        }
    }
    return true;
}

bool ShipManager::allPlacedOnGameMap() const {
    for (auto& ship : ships_) {
        if (!ship->placedOnGameMap()) {
            return false;
        }
    }
    return true;
}

int ShipManager::shipsNumber() const {
    return ships_.size();
}

void ShipManager::addShip(int ship_size) {
    Ship *new_ship = new Ship(ship_size);
    ships_.push_back(new_ship);
}

void ShipManager::removeShip(int ship_index) {
    if (ship_index < 0 || ship_index >= ships_.size()) {
        throw std::out_of_range("segment index out of range");
    }
    ships_.erase(ships_.begin() + ship_index);
}

Ship* ShipManager::operator[](int ship_index) {
    if (ship_index < 0 || ship_index >= ships_.size()) {
        throw std::out_of_range("segment index out of range");
    }
    return ships_[ship_index];
}

} // battleship