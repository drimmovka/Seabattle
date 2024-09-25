#include "../include/game_field.h"

#include "../include/coords.h"
#include "../include/entity.h"
#include "../include/ship.h"
#include "../include/collision_handler.h"

#include <cstddef>
#include <unordered_set>


GameField::GameField()
    : width_(0)
    , height_(0)
{}

GameField::GameField(int width, int height)
    : width_(width)
    , height_(height)
{}

GameField::~GameField() = default;

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

void GameField::attack(int x, int y) {
    
}



size_t GameField::EntityHash::operator()(Entity* entity) const {
    Coords top_left = entity->getTopLeft();
    return std::hash<int>()(top_left.x) ^ (std::hash<int>()(top_left.y) >> 1); // change func
}

size_t GameField::CoordsHash::operator()(Coords coords) const {
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1); // change func
}