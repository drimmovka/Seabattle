#include "../include/collision_handler.h"

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