#include "../include/GameMap.hpp"

#include "../include/Coords.hpp"
#include "../include/Ship.hpp"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

namespace battleship
{

GameMap::ShipLocation::ShipLocation(Ship *ship, Coords top_left, Ship::Orientation orientation)
    : top_left(top_left)
{
    int dx = (orientation == Ship::Orientation::kHorizontal) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::kVertical) ? 1 : 0;
    
    bottom_right = {top_left.x + (ship->size() - 1) * dx, top_left.y + (ship->size() - 1) * dy};

    for (int i = 0; i < ship->size(); i++) {
        coords_to_segment[{top_left.x + i * dx, top_left.y + i * dy}] = (*ship)[i];
    }
}

GameMap::GameMap(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Game map size must be greater than 0");
    }
    width_ = width;
    height_ = height;
}

GameMap::GameMap(const GameMap& other)
    : width_(other.width_)
    , height_(other.height_)
    , ship_to_ship_location_(other.ship_to_ship_location_)                              // DELETE
    , shots_coords_(other.shots_coords_)                                                // DELETE
{}

GameMap::GameMap(GameMap&& other)
    : width_(other.width_)
    , height_(other.height_)
    , ship_to_ship_location_(std::move(other.ship_to_ship_location_))                   // DELETE
    , shots_coords_(std::move(other.shots_coords_))                                     // DELETE
{}

GameMap::~GameMap() = default;

GameMap& GameMap::operator=(const GameMap& other) {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        ship_to_ship_location_ = other.ship_to_ship_location_;                          // DELETE
        shots_coords_ = other.shots_coords_;                                            // DELETE
    }
    return *this;
}

GameMap& GameMap::operator=(GameMap&& other) {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        ship_to_ship_location_ = std::move(other.ship_to_ship_location_);                 // DELETE
        shots_coords_ = std::move(other.shots_coords_);                                   // DELETE
    }
    return *this;
}

int GameMap::width() const {
    return width_;
}

int GameMap::height() const {
    return height_;
}

const std::unordered_map<Ship *, GameMap::ShipLocation *>& GameMap::shipToShipLocation() const {
    return ship_to_ship_location_;
}

const std::unordered_set<Coords, Coords::CoordsHash>& GameMap::shotsCoords() const {
    return shots_coords_;
}

void GameMap::placeShip(Ship *ship, Coords top_left, Ship::Orientation orientation) {
    ShipLocation *ship_locaton = new ShipLocation(ship, top_left, orientation);
    
    if (!this->coordsInsideGameMap(top_left) && this->placedOnGameMap(ship)) {
        this->removeShipFromMap(ship);
    }

    if (this->possibleToPlace(ship, ship_locaton)) {
        ship->placeOnGameMap();
        ship_to_ship_location_[ship] = ship_locaton;
    } else {
        return; // throw error
    }
}

void GameMap::attack(Coords shot_coords, int damage) {
    if (!this->coordsInsideGameMap(shot_coords)) {
        return;
    }
    for (auto& [ship, ship_locations] : ship_to_ship_location_) {
        this->hitScan(ship_locations, shot_coords, damage);
    }
    shots_coords_.insert(shot_coords);
}

bool GameMap::coordsInsideGameMap(Coords coords) const {
    return (coords.x >= 0 && coords.x <= width_ &&
            coords.y >= 0 && coords.y <= height_);
}

bool GameMap::shipInsideGameMap(const ShipLocation *ship_location) const {
    return (this->coordsInsideGameMap(ship_location->top_left) &&
            this->coordsInsideGameMap(ship_location->bottom_right));
}

bool GameMap::shipsCollide(const ShipLocation *a, const ShipLocation *b) const {
    return (a->top_left.x <= b->bottom_right.x &&
            a->top_left.y <= b->bottom_right.y &&
            a->bottom_right.x >= b->top_left.x &&
            a->bottom_right.y >= b->top_left.y);
}

void GameMap::hitScan(ShipLocation *ship_location, Coords shot_coords, int damage) const {
    if (ship_location->coords_to_segment.count(shot_coords) != 0) {
        ship_location->coords_to_segment[shot_coords]->dealDamage(damage);
    }
}

bool GameMap::placedOnGameMap(Ship *ship) const {
    return (ship_to_ship_location_.count(ship) != 0);
}

void GameMap::removeShipFromMap(Ship *ship) {
    if (this->placedOnGameMap(ship)) {
        delete ship_to_ship_location_[ship];
        ship_to_ship_location_.erase(ship);
        ship->removeFromGameMap();
    }
}

bool GameMap::possibleToPlace(const Ship *ship, const ShipLocation *ship_location) const {
    if (!this->shipInsideGameMap(ship_location)) {
        return false;
    }

    bool collision_found = false;
    for (auto& [other_ship, other_ship_location] : ship_to_ship_location_) {
        if (ship != other_ship) {
            collision_found |= this->shipsCollide(ship_location, other_ship_location);
        }
    }

    return !collision_found;
}

} // battleship