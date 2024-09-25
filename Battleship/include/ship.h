#ifndef SHIP_H_
#define SHIP_H_

#include "coords.h"
#include "entity.h"

#include <vector>

class Ship : public Entity {
public:

    enum class Status : int {
        intact,
        damaged,
        destroyed
    };

    enum class Orientation : int {
        vertical,
        horizontal,
        undefined
    };

    Ship();
    
    explicit Ship(int size);
    
    explicit Ship(int size, Orientation orientation);

    explicit Ship(int size, Orientation orientation, Coords top_left);

    ~Ship();

    Orientation getOrientation() const;

    int getSize() const;

    Status getStatus() const;
    
    Coords getTopLeft() const override;

    HitBox getHitBox() const override;

    HitBox getBoundingHitBox() const override;
    
    void setSize(int size);

    void setOrientation(Orientation orientation);

    void setShipCoords(Coords top_left);

    void damageSegment(int segment_index, int damage);

    void repairSegment(int segment_index, int recoveryHealth);

private:
    class ShipSegment {
    public:
        ShipSegment();
        
        ~ShipSegment();

        Status getStatus() const;
        
        void dealDamage(int damage);
        
        void increaseHealth(int recoveryHealth);

    private:
        const int kMaxHealth;
        int health_;
    
    };

    void setHitBoxes();

    template <typename T>
    bool checkOutOfBounds(int index, std::vector<T>& vec) {
        return (index < 0 || index > vec.size());
    }
    
    std::vector<ShipSegment> ship_segments_;
    Orientation orientation_;
    Coords top_left_;
    HitBox hit_box_;
    HitBox bounding_hit_box_;
};

#endif