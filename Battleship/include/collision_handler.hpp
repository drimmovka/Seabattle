#ifndef COLLISION_HANDLER_HPP_
#define COLLISION_HANDLER_HPP_

#include "coords.hpp"
#include "entity.hpp"


class CollisionHandler {
public:

    CollisionHandler();
    ~CollisionHandler();
    
    bool checkHitBoxCollision(const Entity::HitBox& a, const Entity::HitBox& b) const;

    bool checkEntityInsideMap(const Entity *entity, int width, int height) const;

    int hitScan(Coords shot_coords, const Entity *entity) const;

private:

    bool checkCoordsInsideHitBox(Coords coords, const Entity::HitBox& hit_box) const;
};

#endif