#ifndef COLLISION_HANDLER_HPP_
#define COLLISION_HANDLER_HPP_

#include "coords.hpp"

namespace battleship
{

struct HitBox {
    Coords top_left;
    Coords bottom_right;
};

struct CollisionBounds {
    HitBox shaping;
    HitBox wrapping;
};

class CollisionHandler {
public:

    CollisionHandler();

    ~CollisionHandler();
    
    bool hitBoxCollision(const HitBox& a, const HitBox& b) const;

    bool insideGameMap(const HitBox& hit_box, int width, int height) const;
    
    int hitScan(Coords shot_coords, const HitBox& hit_box) const;

private:

    bool coordsInsideHitBox(Coords coords, const HitBox& hit_box) const;

};

} // battleship


#endif // COLLISION_HANDLER_HPP_