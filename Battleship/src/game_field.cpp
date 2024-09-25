#include "../include/game_field.h"

#include "../include/coords.h"
#include "../include/collision_handler.h"
#include "../include/ship.h"

#include <unordered_map>
#include <unordered_set>

/*
            width
    x →
    y 0 0 0 0 0 0 0 0 0 0 0 0
    ↓ 0 0 0 0 0 0 0 0 0 0 0 0
h   0 0 0 0 0 0 0 0 0 0 0 0
e   0 0 0 0 0 0 0 0 0 0 0 0
i   0 0 0 0 0 0 0 0 0 0 0 0
g   0 0 0 0 0 0 0 0 0 0 0 0
h   0 0 0 0 0 0 0 0 0 0 0 0
t   0 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0
*/




class GameField {
public:
    GameField()
        : width_(0)
        , height_(0)
    {}

    GameField(int width, int height)
        : width_(width)
        , height_(height)
    {}

    ~GameField() = default;

    int getWidth() const {
        return width_;
    }

    int getHeight() const {
        return height_;
    }

    void setSize(int width, int height) {
        width_ = width;
        height_ = height;
    }

    void setShip(Ship& ship, Coords top_left, Ship::Orientation orientation) {
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
    
    void attack(int x, int y) {
        
    }


private:

    struct EntityHash {
        size_t operator()(Entity* entity) const {
            Coords top_left = entity->getTopLeft();
            return std::hash<int>()(top_left.x) ^ (std::hash<int>()(top_left.y) >> 1); // change func
        }
    };

    struct CoordsHash {
        size_t operator()(Coords coords) const {
            return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1); // change func
        }
    };
    
    std::unordered_set<Entity*, EntityHash> map_entities_;
    std::unordered_set<Coords, CoordsHash> opened_cells_;
    int width_;
    int height_;
    CollisionHandler collision_handler_;
};