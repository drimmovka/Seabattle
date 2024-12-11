#include "ShipsManager.hpp"

#include "Ship.hpp"

#include <stdexcept> // TEMPORARY FOR DEBUGGING
#include <vector>
#include <iostream>

namespace seabattle
{

ShipsManager::ShipsManager() = default;
    
ShipsManager::ShipsManager(const std::vector<int> &ship_sizes) {
    int i = 0;
    for (auto& ship_size : ship_sizes) {
        Ship *new_ship = new Ship(ship_size);
        new_ship->setId(i++);
        ships_.push_back(new_ship);
    }
}

ShipsManager::ShipsManager(const ShipsManager& other)
    : ships_(other.ships_)
{}

ShipsManager::ShipsManager(ShipsManager&& other)
    : ships_(std::move(other.ships_))
{}

ShipsManager::~ShipsManager() {
    for (auto& ship : ships_) {
        delete ship;
    }
}

ShipsManager& ShipsManager::operator=(const ShipsManager& other) {
    if (this != &other) {
        ships_ = other.ships_;
    }
    return *this;
}

ShipsManager& ShipsManager::operator=(ShipsManager&& other) {
    if (this != &other) {
        ships_ = std::move(other.ships_);
    }
    return *this;
}

bool ShipsManager::allDestroyed() const {
    for (auto& ship : ships_) {
        if (ship->status() != Ship::Status::kDestroyed) {
            return false;
        }
    }
    return true;
}

bool ShipsManager::allPlacedOnGameMap() const {
    for (auto& ship : ships_) {
        if (!ship->placedOnGameMap()) {
            return false;
        }
    }
    return true;
}

int ShipsManager::shipsNumber() const {
    return ships_.size();
}

int ShipsManager::aliveShipsNumber() const {
    int count = 0;
    for (auto& ship : ships_) {
        if (ship->status() != Ship::Status::kDestroyed) {
            count++;
        }
    }
    return count;
}

void ShipsManager::addShip(Ship *new_ship) {
    new_ship->setId(ships_.size());
    ships_.push_back(new_ship);
}

void ShipsManager::removeShip(int ship_index) {
    if (ship_index < 0 || ship_index >= ships_.size()) {
        throw std::out_of_range("segment index out of range");
    }
    ships_.erase(ships_.begin() + ship_index);
}

Ship* ShipsManager::operator[](int ship_index) {
    if (ship_index < 0 || ship_index >= ships_.size()) {
        throw std::out_of_range("segment index out of range");
    }
    return ships_[ship_index];
}

std::ostream& operator<<(std::ostream& os, ShipsManager& ships_manager) {
    os << ships_manager.shipsNumber() << "\n";
    for (int i=0; i<ships_manager.shipsNumber(); ++i) {
        os << ships_manager[i]->size() << "\n";
        for (int j=0; j<ships_manager[i]->size(); ++j) {
            os << (*ships_manager[i])[j]->health() << " ";
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, ShipsManager& ships_manager) {
    int ship_count;
    is >> ship_count;
    std::cout << ship_count << "\n";
    for (int i=0; i<ship_count; ++i) {
        int ship_size;
        is >> ship_size;
        Ship *ship = new Ship(ship_size);
        for (int j=0; j<ship_size; ++j) {
            int ship_segment_hp;
            is >> ship_segment_hp;
            std::cout << ship_segment_hp << " ";
            (*ship)[j]->dealDamage(std::max(0, ship->maxSegHealth()-ship_segment_hp));
        }
        std::cout << "\n";
        ships_manager.addShip(ship);
    }
    return is;
}

} // namespace seabattle