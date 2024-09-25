#include "../include/collision_handler.hpp"

CollisionHandler::CollisionHandler() = default;

CollisionHandler::~CollisionHandler() = default;

bool CollisionHandler::checkHitBoxCollision(const Entity::HitBox& a, const Entity::HitBox& b) const {    
    return checkCoordsInsideHitBox(a.top_left, b) || checkCoordsInsideHitBox(a.bottom_right, b);
}

bool CollisionHandler::checkCoordsInsideHitBox(Coords coords, const Entity::HitBox& hit_box) const {
    return (coords.x >= hit_box.top_left.x && 
            coords.x <= hit_box.bottom_right.x && 
            coords.y >= hit_box.top_left.y && 
            coords.y <= hit_box.bottom_right.y);
}

bool CollisionHandler::checkEntityInsideMap(const Entity *entity, int width, int height) const {
    Entity::HitBox hit_box = entity->getHitBox(); 
    return (hit_box.top_left.x >= 0 && 
            hit_box.top_left.y >= 0 &&
            hit_box.bottom_right.x <= width &&
            hit_box.bottom_right.y <= height);
}

int CollisionHandler::hitScan(Coords shot_coords, const Entity *entity) const {
    if (checkCoordsInsideHitBox(shot_coords, entity->getHitBox())) {
        Entity::HitBox hit_box = entity->getHitBox();

        return ( (shot_coords.x - hit_box.top_left.x) + 
                 (shot_coords.y - hit_box.top_left.y) * 
                 (hit_box.bottom_right.x - hit_box.top_left.x + 1));
    }
    return -1;
}