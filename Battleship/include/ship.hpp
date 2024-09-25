#ifndef SHIP_HPP_
#define SHIP_HPP_

#include "coords.hpp"
#include "entity.hpp"

#include <vector>

class Ship : public Entity {
public:

    

    enum class Orientation : int {
        vertical,
        horizontal,
        undefined
    };

    Ship();
    
    explicit Ship(int size);
    
    explicit Ship(int size, Ship::Orientation orientation);

    explicit Ship(int size, Ship::Orientation orientation, Coords top_left);

    ~Ship();

    Ship::Orientation getOrientation() const;

    int getSize() const;

    Entity::Status getStatus() const;
    
    Coords getTopLeft() const override;

    HitBox getHitBox() const override;

    HitBox getBoundingHitBox() const override;
    
    void setSize(int size);

    void setOrientation(Ship::Orientation orientation);

    void setShipCoords(Coords top_left);

    void damageSegment(int segment_index, int damage) override;

    void repairSegment(int segment_index, int recoveryHealth) override;

private:
    std::vector<Entity::Segment> ship_segments_;
    Orientation orientation_;
    Coords top_left_;
    HitBox hit_box_;
    HitBox bounding_hit_box_;

    template <typename T>
    bool checkOutOfBounds(int index, const std::vector<T>& vec) const {
        return (index < 0 || index > vec.size());
    }

    void setHitBoxes();
};

#endif