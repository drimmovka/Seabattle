#ifndef GAME_MAP_HPP_
#define GAME_MAP_HPP_

#include "Coords.hpp"
#include "HitBox.hpp"
#include "Ship.hpp"

#include <unordered_map>
#include <unordered_set>

namespace battleship
{

class GameMap {

public:

    struct ShipInfo {
    
        using uMapCoordsToSegmentIndexes = std::unordered_map<Coords, int, CoordsHash>;

        explicit ShipInfo(int ship_size, Coords top_left, Ship::Orientation orientation);

        Coords top_left;
        Ship::Orientation orientation;
        HitBox shaping_hit_box;
        HitBox wrapping_hit_box;
        uMapCoordsToSegmentIndexes coords_to_segment_indexes;
    };

    using uMapShipToShipInfo = std::unordered_map<Ship *, const ShipInfo *>;
    using uSetCoords = std::unordered_set<Coords, CoordsHash>;

    explicit GameMap(int width, int height);

    GameMap(const GameMap& other);

    GameMap(GameMap&& other);

    ~GameMap();

    GameMap& operator=(const GameMap& other);

    GameMap& operator=(GameMap&& other);
    
    int width() const;
    
    int height() const;
    
    const uMapShipToShipInfo& shipsToShipInfo() const;
    
    void setShip(Ship *ship, Coords top_left, Ship::Orientation orientation);
    
    void attack(Coords shot_coords, int damage);
    
private:

    uMapShipToShipInfo ships_to_ship_info; // CHANGE TO Q-TREE
    uSetCoords opened_cells_;
    int width_;
    int height_;

    bool insideGameMap(const HitBox& hit_box, int width, int height) const;

    bool coordsInsideHitBox(Coords coords, const HitBox& hit_box) const;

    bool hitBoxCollision(const HitBox& a, const HitBox& b) const;
    
    bool hitScan(Coords shot_coords, const ShipInfo::uMapCoordsToSegmentIndexes& coords_to_segment_indexes) const;

    bool possibleToSet(Ship *ship, const ShipInfo *ship_info) const;

    void removeShip(Ship *ship);
};

}


#endif // GAME_MAP_HPP_