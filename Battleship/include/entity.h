#ifndef ENTITY_H_
#define ENTITY_H_

#include "coords.h"

class Entity
{
public:

    struct HitBox {
        Coords top_left;
        Coords bottom_right;
    };

    virtual Coords getTopLeft() const = 0;

    virtual HitBox getHitBox() const = 0;
    
    virtual HitBox getBoundingHitBox() const = 0;
        
    Entity();
    ~Entity();
};

#endif