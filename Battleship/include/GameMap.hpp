#ifndef GAME_MAP_HPP_
#define GAME_MAP_HPP_

#include "Coords.hpp"
#include "Ship.hpp"

#include <unordered_map>
#include <unordered_set>

namespace battleship
{

class GameMap {

public:

    struct ShipLocation {
        explicit ShipLocation(Ship *ship, Coords top_left, Ship::Orientation orientation);

        Coords top_left;
        Coords bottom_right;
        std::unordered_map<Coords, Ship::Segment *, Coords::CoordsHash> coords_to_segment;
    };

    explicit GameMap(int width, int height);

    GameMap(const GameMap& other);

    GameMap(GameMap&& other);

    ~GameMap();

    GameMap& operator=(const GameMap& other);

    GameMap& operator=(GameMap&& other);
    
    int width() const;
    
    int height() const;
    
    const std::unordered_map<Ship *, GameMap::ShipLocation *>& shipToShipLocation() const;

    const std::unordered_set<Coords, Coords::CoordsHash>& shotsCoords() const;
    
    void placeShip(Ship *ship, Coords top_left, Ship::Orientation orientation);
    
    void attack(Coords shot_coords, int damage);
    
private:
    std::unordered_map<Ship *, ShipLocation *> ship_to_ship_location_; // CHANGE TO Q-TREE
    std::unordered_set<Coords, Coords::CoordsHash> shots_coords_;
    int width_;
    int height_;

    bool possibleToPlace(const Ship *, const ShipLocation *ship_location) const;
    
    bool coordsInsideGameMap(Coords coords) const;

    bool shipInsideGameMap(const ShipLocation *ship_location) const;

    bool shipsCollide(const ShipLocation *a, const ShipLocation *b) const;
    
    void hitScan(ShipLocation *ship_location, Coords shot_coords, int damage) const;

    bool placedOnGameMap(Ship *ship) const;

    void removeShipFromMap(Ship *ship);
};

}


#endif // GAME_MAP_HPP_