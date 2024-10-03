#include "../include/collision_handler.hpp"

namespace battleship
{

CollisionHandler::CollisionHandler() = default;

CollisionHandler::~CollisionHandler() = default;

bool CollisionHandler::hitBoxCollision(const HitBox& a, const HitBox& b) const {
    
    return coordsInsideHitBox(a.top_left, b) ||
           coordsInsideHitBox(a.bottom_right, b) ||
           coordsInsideHitBox(b.top_left, a) ||
           coordsInsideHitBox(b.bottom_right, a);
}

bool CollisionHandler::coordsInsideHitBox(Coords coords, const HitBox& hit_box) const {
    return (coords.x >= hit_box.top_left.x && 
            coords.x <= hit_box.bottom_right.x && 
            coords.y >= hit_box.top_left.y && 
            coords.y <= hit_box.bottom_right.y);
}

bool CollisionHandler::insideGameMap(const HitBox& hit_box, int width, int height) const {
    return (hit_box.top_left.x >= 0 && 
            hit_box.top_left.y >= 0 &&
            hit_box.bottom_right.x < width &&
            hit_box.bottom_right.y < height);
}

int CollisionHandler::hitScan(Coords shot_coords, const HitBox& hit_box) const {
    if (coordsInsideHitBox(shot_coords, hit_box)) {
        return ( (shot_coords.x - hit_box.top_left.x) + 
                 (shot_coords.y - hit_box.top_left.y) * 
                 (hit_box.bottom_right.x - hit_box.top_left.x + 1));
    }
    return -1;
}

} // battleship