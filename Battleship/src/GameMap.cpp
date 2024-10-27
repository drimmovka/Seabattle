#include "../include/GameMap.hpp"

#include "../include/Coords.hpp"
#include "../include/Ship.hpp"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

namespace battleship
{

GameMap::ShipInfo::ShipInfo(int ship_size, Coords top_left, Ship::Orientation orientation)
    : top_left(top_left)
    , orientation(orientation)
{
    int dx = (orientation == Ship::Orientation::kHorizontal) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::kVertical) ? 1 : 0;

    shaping_hit_box = {
        {top_left.x, top_left.y},
        {top_left.x + (ship_size - 1) * dx, top_left.y + (ship_size - 1) * dy}
    };

    wrapping_hit_box = {
        {shaping_hit_box.top_left.x - 1, shaping_hit_box.top_left.y - 1},
        {shaping_hit_box.bottom_right.x + 1, shaping_hit_box.bottom_right.y + 1}
    };

    for (int i = 0; i < ship_size; i++) {
        coords_to_segment_indexes[{top_left.x + i * dx, top_left.y + i * dy}] = i;
    }
}

GameMap::GameMap(int width, int height)
    : width_( (width > 0) ? width : 0 )
    , height_( (height > 0) ? height : 0)
{
    if (width_ == 0 || height_ == 0) {
        throw std::invalid_argument("Game map size must be greater than 0");
    }
}

GameMap::GameMap(const GameMap& other)
    : width_(other.width_)
    , height_(other.height_)
    , ships_to_ship_info(other.ships_to_ship_info)                              // DELETE
    , opened_cells_(other.opened_cells_)                                        // DELETE
{}

GameMap::GameMap(GameMap&& other)
    : width_(other.width_)
    , height_(other.height_)
    , ships_to_ship_info(std::move(other.ships_to_ship_info))                   // DELETE
    , opened_cells_(std::move(other.opened_cells_))                             // DELETE
{}

GameMap::~GameMap() = default;

GameMap& GameMap::operator=(const GameMap& other) {
    if (this != &other) {
        this->width_ = other.width_;
        this->height_ = other.height_;
        this->ships_to_ship_info = other.ships_to_ship_info;                    // DELETE
        this->opened_cells_ = other.opened_cells_;                              // DELETE
    }
    return *this;
}

GameMap& GameMap::operator=(GameMap&& other) {
    if (this != &other) {
        this->width_ = other.width_;
        this->height_ = other.height_;
        this->ships_to_ship_info = std::move(other.ships_to_ship_info);         // DELETE
        this->opened_cells_ = std::move(other.opened_cells_);                   // DELETE
    }
    return *this;
}

int GameMap::width() const {
    return width_;
}

int GameMap::height() const {
    return height_;
}

const GameMap::uMapShipToShipInfo& GameMap::shipsToShipInfo() const {
    return ships_to_ship_info;
}

void GameMap::setShip(Ship *ship, Coords top_left, Ship::Orientation orientation) {
    ShipInfo *ship_info = new ShipInfo(ship->size(), top_left, orientation);

    if (this->possibleToSet(ship, ship_info)) {
        ships_to_ship_info[ship] = ship_info;
    } else {
        return; // throw error
    }
}

void GameMap::attack(Coords shot_coords, int damage) {
    for (auto& [ship, ship_info] : ships_to_ship_info) {
        if (this->hitScan(shot_coords, ship_info->coords_to_segment_indexes)) {
            ship->damageSegment(ship_info->coords_to_segment_indexes.at(shot_coords), damage);
        }
    }
    opened_cells_.insert(shot_coords);
}

bool GameMap::insideGameMap(const HitBox& hit_box, int width, int height) const {
    return (hit_box.top_left.x >= 0 && 
            hit_box.top_left.y >= 0 &&
            hit_box.bottom_right.x < width &&
            hit_box.bottom_right.y < height);
}

bool GameMap::coordsInsideHitBox(Coords coords, const HitBox& hit_box) const {
    return (coords.x >= hit_box.top_left.x && 
            coords.x <= hit_box.bottom_right.x && 
            coords.y >= hit_box.top_left.y && 
            coords.y <= hit_box.bottom_right.y);
}

bool GameMap::hitBoxCollision(const HitBox& a, const HitBox& b) const {

    return coordsInsideHitBox(a.top_left, b) ||
           coordsInsideHitBox(a.bottom_right, b) ||
           coordsInsideHitBox(b.top_left, a) ||
           coordsInsideHitBox(b.bottom_right, a);
}

bool GameMap::hitScan(Coords shot_coords, const ShipInfo::uMapCoordsToSegmentIndexes& coords_to_segment_indexes) const {
    return (coords_to_segment_indexes.find(shot_coords) != coords_to_segment_indexes.end());
}

bool GameMap::possibleToSet(Ship *ship, const ShipInfo *ship_info) const {
    bool inside_map = this->insideGameMap(ship_info->shaping_hit_box, width(), height());

    bool collision_found = false;
    for (auto& [other_ship, other_ship_info] : ships_to_ship_info) {
        if (ship != other_ship) {
            collision_found |= this->hitBoxCollision(ship_info->wrapping_hit_box, other_ship_info->shaping_hit_box);
        }
    }
    return inside_map && !(collision_found);
}

void GameMap::removeShip(Ship *ship) {
    ships_to_ship_info.erase(ship);
}

} // battleship