#include "../include/ship.h"

#include "coords.h"
#include "entity.h"

#include <vector>

Ship::Ship()
    : orientation_(Orientation::undefined)
    , top_left_{-1, -1}
    , hit_box_{{-1, -1}, {-1, -1}}
    , bounding_hit_box_{{-1, -1}, {-1, -1}}
{}

Ship::Ship(int size)
    : ship_segments_(size, ShipSegment())
    , orientation_(Orientation::undefined)
    , top_left_{-1, -1}
    , hit_box_{{-1, -1}, {-1, -1}}
    , bounding_hit_box_{{-1, -1}, {-1, -1}}
{}

Ship::Ship(int size, Orientation orientation)
    : ship_segments_(size, ShipSegment())
    , orientation_(orientation)
    , top_left_{-1, -1}
    , hit_box_{{-1, -1}, {-1, -1}}
    , bounding_hit_box_{{-1, -1}, {-1, -1}}
{}

Ship::Ship(int size, Orientation orientation, Coords top_left)
    : ship_segments_(size, ShipSegment())
    , orientation_(orientation)
{
    setShipCoords(top_left);
}


Ship::~Ship() = default;

Ship::Orientation Ship::getOrientation() const {
    return orientation_;
}

int Ship::getSize() const {
    return ship_segments_.size();
}


Ship::Status Ship::getStatus() const {
    // !!!
    // think about giving status DESTROYED if ship has size 0 (doesnt exist)
    // !!!
    bool destroyed = true;
    bool intact = true;

    for (auto& segment : ship_segments_) {
        Status segment_status = segment.getStatus();
        intact &= (segment_status == Status::intact);
        destroyed &= (segment_status == Status::destroyed);
    }
    
    if (intact) {
        return Status::intact;
    }
    if (destroyed) {
        return Status::destroyed;
    }
    
    return Status::damaged;
}

Coords Ship::getTopLeft() const {
    return top_left_;
}

Entity::HitBox Ship::getHitBox() const {
    return hit_box_;
}

Entity::HitBox Ship::getBoundingHitBox() const {
    return bounding_hit_box_;
}

void Ship::setSize(int size) {
    ship_segments_ = std::vector<ShipSegment> (size);
}

void Ship::setOrientation(Orientation orientation) {
    orientation_ = orientation;
}

void Ship::damageSegment(int segment_index, int damage) {
    if (checkOutOfBounds(segment_index, ship_segments_)) {
        return; // throw error
    }
    ship_segments_[segment_index].dealDamage(damage);
}

void Ship::setShipCoords(Coords top_left) {
    if (getSize() == 0 || orientation_ == Orientation::undefined) {
        return; // throw error
    }
    top_left_ = top_left;
    setHitBoxes();
}

void Ship::setHitBoxes() {
    
    if (orientation_ == Orientation::horizontal) {
        hit_box_ = {
            {top_left_.x, top_left_.y},
            {top_left_.x + getSize() - 1, top_left_.y}
        };

    }

    if (orientation_ == Orientation::vertical) {
        hit_box_ = {
            {top_left_.x, top_left_.y},
            {top_left_.x, top_left_.y + getSize() - 1}
        };
    }

    bounding_hit_box_ = {
        {hit_box_.top_left.x - 1, hit_box_.top_left.y - 1},
        {hit_box_.bottom_right.x + 1, hit_box_.bottom_right.y + 1}
    };
}


void Ship::repairSegment(int segment_index, int recoveryHealth) {
    if (checkOutOfBounds(segment_index, ship_segments_)) {
        return; // throw error
    }
    ship_segments_[segment_index].increaseHealth(recoveryHealth);
}


Ship::ShipSegment::ShipSegment()
    : kMaxHealth(2)
{}

Ship::ShipSegment::~ShipSegment() = default;

Ship::Status Ship::ShipSegment::getStatus() const {
    if (health_ == kMaxHealth) {
        return Status::intact;
    }
    if (health_ == 0) {
        return Status::destroyed;
    }
    return Status::damaged;
}

void Ship::ShipSegment::dealDamage(int damage) {
    health_ = std::max(0, health_ - damage);
}

void Ship::ShipSegment::increaseHealth(int recoveryHealth) {
    health_ = std::min(kMaxHealth, health_ + recoveryHealth);
}