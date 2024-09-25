#ifndef GAME_FIELD_H_
#define GAME_FIELD_H_

#include "coords.h"
#include "entity.h"
#include "ship.h"
#include "collision_handler.h"

#include <cstddef>
#include <unordered_set>

class GameField {
public:
    GameField();

    GameField(int width, int height);

    ~GameField();

    int getWidth() const;

    int getHeight() const;

    void setSize(int width, int height);

    void setShip(Ship& ship, Coords top_left, Ship::Orientation orientation);
    
    void attack(int x, int y);


private:

    struct EntityHash {
        size_t operator()(Entity* entity) const;
    };

    struct CoordsHash {
        size_t operator()(Coords coords) const;
    };
    
    std::unordered_set<Entity*, EntityHash> map_entities_;
    std::unordered_set<Coords, CoordsHash> opened_cells_;
    int width_;
    int height_;
    CollisionHandler collision_handler_;
};

#endif