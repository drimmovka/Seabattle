#ifndef COLLISION_HANDLER_H_
#define COLLISION_HANDLER_H_

#include "coords.h"
#include "entity.h"


class CollisionHandler {
public:

    CollisionHandler();
    ~CollisionHandler();
    
    bool checkHitBoxCollision(const Entity::HitBox& a, const Entity::HitBox& b) const;

    bool checkEntityInsideMap(const Entity *entity, int width, int height) const;

private:

    bool checkCoordsInsideHitBox(Coords coords, const Entity::HitBox& hit_box) const;
};

#endif