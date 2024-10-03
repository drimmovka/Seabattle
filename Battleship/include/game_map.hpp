#ifndef GAME_MAP_HPP_
#define GAME_MAP_HPP_

#include "coords.hpp"
#include "ship.hpp"
#include "collision_handler.hpp"

#include <unordered_map>
#include <unordered_set>

namespace battleship
{

class GameMap {
public:

    GameMap();

    explicit GameMap(int width, int height);

    GameMap(const GameMap& other);

    GameMap(GameMap&& other);

    ~GameMap();

    GameMap& operator=(const GameMap& other);

    GameMap& operator=(GameMap&& other);
    
    int width() const;
    
    int height() const;
    
    const std::unordered_map<Ship *, CollisionBounds>& ships() const;
    
    void setShip(Ship *ship, Coords top_left, Ship::Orientation orientation);
    
    void attack(Coords shot_coords, int damage);
    
private:

    bool possibleToSet(Ship *ship, CollisionBounds collision_bounds) const;

    bool sameShip(const Ship *a, const Ship *b) const;

    CollisionBounds calculateCollisionBounds(int ship_size, Coords top_left, Ship::Orientation orientation);
    
    std::unordered_map<Ship *, CollisionBounds> ships_; // CHANGE TO Q-TREE
    std::unordered_set<Coords, CoordsHash> opened_cells_;
    int width_;
    int height_;
    CollisionHandler collision_handler_;
};

}


#endif // GAME_MAP_HPP_