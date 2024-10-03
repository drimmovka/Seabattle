#include "../include/ship_manager.hpp"

#include "../include/ship.hpp"

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

bool ShipManager::allDestroyed() const {
    bool all_destroyed = true;
    for (auto& ship : ships_) {
        all_destroyed &= (ship->status() == Ship::Status::kDestroyed);
    }
    return all_destroyed;
}

int ShipManager::shipsNumber() const {
    return ships_.size();
}

void ShipManager::addShip(int ship_size) {
    Ship *new_ship = new Ship(ship_size);
    ships_.push_back(new_ship);
}

void ShipManager::removeShip(int ship_index) {
    if (ship_index < 0 || ship_index >= shipsNumber()) {
        throw std::out_of_range("segment index out of range");
    }
    ships_.erase(ships_.begin() + ship_index);
}

// rewrite
void ShipManager::displayInfo() const {
    std::cout << "Ships number: " << shipsNumber() << std::endl;
    for (auto& ship : ships_) {
        std::cout << "Size: " << ship->size() << " | segments: ";
        for (int i = 0; i < ship->size(); i++) {
            std::cout << "[" << ship->segmentHealth(i) << "]";
        }
        std::cout << std::endl;
    }
}

} // battleship