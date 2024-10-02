#include "../include/game_map.hpp"

#include "../include/coords.hpp"
#include "../include/ship.hpp"
#include "../include/collision_handler.hpp"

#include <cstddef>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

GameMap::GameMap()
    : GameMap(0, 0)
{}

GameMap::GameMap(int width, int height)
    : width_(width)
    , height_(height)
{}

GameMap::GameMap(const GameMap& other)
    : width_(other.width_)
    , height_(other.height_)
{}

GameMap::GameMap(GameMap&& other)
    : width_(other.width_)
    , height_(other.height_)
{}

GameMap::~GameMap() = default;

GameMap& GameMap::operator=(const GameMap& other) {
    if (this != &other) {
        this->width_ = other.width_;
        this->height_ = other.height_;
    }
    return *this;
}

GameMap& GameMap::operator=(GameMap&& other) {
    if (this != &other) {
        this->width_ = other.width_;
        this->height_ = other.height_;
    }
    return *this;
}

int GameMap::width() const {
    return width_;
}

int GameMap::height() const {
    return height_;
}

const std::unordered_map<Ship*, CollisionBounds>& GameMap::ships() const {
    return ships_;
}

void GameMap::setShip(Ship *ship, Coords top_left, Ship::Orientation orientation) {
    CollisionBounds collision_bounds = calculateCollisionBounds(ship->size(), top_left, orientation);

    if (possibleToSet(collision_bounds)) {
        ships_.insert({ship, collision_bounds});
    } else {
        return; // throw error
    }
}

void GameMap::attack(Coords shot_coords, int damage) {
    int segment_number;
    for (auto& item : ships_) {
        segment_number = collision_handler_.hitScan(shot_coords, item.second.shaping);
        if (segment_number != -1) {
            item.first->damageSegment(segment_number, damage);
        }
    }
    opened_cells_.insert(shot_coords);
}

CollisionBounds GameMap::calculateCollisionBounds(int ship_size, Coords top_left, Ship::Orientation orientation) {
    
    HitBox shaping_hit_box;
    HitBox wrapping_hit_box;

    if (orientation == Ship::Orientation::kHorizontal) {
        shaping_hit_box = {
            {top_left.x, top_left.y},
            {top_left.x + ship_size - 1, top_left.y}
        };
    }

    if (orientation == Ship::Orientation::kVertical) {
        shaping_hit_box = {
            {top_left.x, top_left.y},
            {top_left.x, top_left.y + ship_size - 1}
        };
    }

    wrapping_hit_box = {
        {shaping_hit_box.top_left.x - 1, shaping_hit_box.top_left.y - 1},
        {shaping_hit_box.bottom_right.x + 1, shaping_hit_box.bottom_right.y + 1}
    };
    return {shaping_hit_box, wrapping_hit_box};
}


bool GameMap::possibleToSet(CollisionBounds collision_bounds) const {
    bool inside_map = collision_handler_.insideGameMap(collision_bounds.shaping, width(), height());

    bool collision_found = false;
    for (auto& item : ships_) {
        collision_found |= collision_handler_.hitBoxCollision(collision_bounds.wrapping, item.second.shaping);
    }
    return inside_map && !(collision_found);
}

size_t GameMap::CoordsHash::operator()(Coords coords) const {
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1); // change func
}