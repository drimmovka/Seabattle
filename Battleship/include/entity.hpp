#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "coords.hpp"

class Entity
{
public:
    enum class Status : int {
        intact,
        damaged,
        destroyed
    };

    struct HitBox {
        Coords top_left;
        Coords bottom_right;
    };

    Entity();
    ~Entity();

    virtual Coords getTopLeft() const = 0;

    virtual HitBox getHitBox() const = 0;
    
    virtual HitBox getBoundingHitBox() const = 0;
    
    virtual void damageSegment(int segment_index, int damage) = 0;

    virtual void repairSegment(int segment_index, int recoveryHealth) = 0;

protected:
    class Segment {
    public:
        
        Segment();

        Segment(int max_health);

        ~Segment();

        int getHealth() const;

        Status getStatus() const;

        void dealDamage(int damage);
        
        void increaseHealth(int recoveryHealth);

    private:
        int max_health_;
        int health_;
    
    };

};

#endif