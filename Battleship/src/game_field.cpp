#include "../include/game_field.hpp"

#include "../include/coords.hpp"
#include "../include/entity.hpp"
#include "../include/ship.hpp"
#include "../include/collision_handler.hpp"

#include <cstddef>
#include <unordered_set>


GameField::GameField()
    : GameField(0, 0)
{}

GameField::GameField(int width, int height)
    : width_(width)
    , height_(height)
{}

GameField::GameField(const GameField &other)
    : width_(other.width_)
    , height_(other.height_)
{}

GameField::GameField(GameField &&other)
    : width_(other.width_)
    , height_(other.height_)
{}

GameField::~GameField() = default;

GameField& GameField::operator=(const GameField &other) {
    if (this != &other) {
        this->width_ = other.width_;
        this->height_ = other.height_;
    }
    return *this;
}

GameField& GameField::operator=(GameField &&other) {
    if (this != &other) {
        this->width_ = other.width_;
        this->height_ = other.height_;
    }
    return *this;
}


int GameField::getWidth() const {
    return width_;
}

int GameField::getHeight() const {
    return height_;
}

void GameField::setSize(int width, int height) {
    width_ = width;
    height_ = height;
}

void GameField::setShip(Ship& ship, Coords top_left, Ship::Orientation orientation) {
    ship.setOrientation(orientation);
    ship.setShipCoords(top_left);
    
    bool possible_to_set = collision_handler_.checkEntityInsideMap(&ship, width_, height_);
    
    for (auto& entity : map_entities_) {
        possible_to_set &= collision_handler_.checkHitBoxCollision(ship.getBoundingHitBox(), entity->getHitBox());
    }

    if (possible_to_set) {
        map_entities_.insert(&ship);
    } else {
        return; // throw error
    }
}

void GameField::attack(Coords shot_coords, int damage) {
    int segment_number;
    for (auto& entity : map_entities_) {
        segment_number = collision_handler_.hitScan(shot_coords, entity);
        if (segment_number != -1) {
            entity->damageSegment(segment_number, damage);
        }
    }
    opened_cells_.insert(shot_coords);
}


size_t GameField::CoordsHash::operator()(Coords coords) const {
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1); // change func
}