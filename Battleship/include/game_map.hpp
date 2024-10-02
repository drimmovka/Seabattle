#ifndef GAME_FIELD_HPP_
#define GAME_FIELD_HPP_

#include "coords.hpp"
#include "ship.hpp"
#include "collision_handler.hpp"

#include <cstddef>
#include <unordered_map>
#include <unordered_set>

class GameMap {
public:

    GameMap();

    GameMap(int width, int height);

    GameMap(const GameMap& other);

    GameMap(GameMap&& other);

    ~GameMap();

    GameMap& operator=(const GameMap& other);

    GameMap& operator=(GameMap&& other);
    
    int width() const;
    
    int height() const;
    
    const std::unordered_map<Ship*, CollisionBounds>& ships() const;
    
    void setShip(Ship *ship, Coords top_left, Ship::Orientation orientation);
    
    void attack(Coords shot_coords, int damage);

private:

    CollisionBounds calculateCollisionBounds(int ship_size, Coords top_left, Ship::Orientation orientation);

    bool possibleToSet(CollisionBounds collision_bounds) const;

    struct CoordsHash {
        size_t operator()(Coords coords) const;
    };
    
    std::unordered_map<Ship*, CollisionBounds> ships_;
    std::unordered_set<Coords, CoordsHash> opened_cells_;
    int width_;
    int height_;
    CollisionHandler collision_handler_;
};

#endif // GAME_FIELD_HPP_