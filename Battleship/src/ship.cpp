#include "../include/ship.hpp"

#include "../include/coords.hpp"
#include "../include/entity.hpp"

#include <vector>

Ship::Ship()
    : orientation_(Orientation::undefined)
    , top_left_{-1, -1}
    , hit_box_{{-1, -1}, {-1, -1}}
    , bounding_hit_box_{{-1, -1}, {-1, -1}}
    , kMaxSegmentHealth(2)
{}

Ship::Ship(int size)
    : kMaxSegmentHealth(2)
    , ship_segments_(size, Entity::Segment(kMaxSegmentHealth))
    , orientation_(Orientation::undefined)
    , top_left_{-1, -1}
    , hit_box_{{-1, -1}, {-1, -1}}
    , bounding_hit_box_{{-1, -1}, {-1, -1}}
{}

Ship::Ship(int size, Orientation orientation, Coords top_left)
    : kMaxSegmentHealth(2)
    , ship_segments_(size, Entity::Segment(kMaxSegmentHealth))
    , orientation_(orientation)
{
    setShipCoords(top_left);
}

Ship::Ship(const Ship& other)
    : kMaxSegmentHealth(other.kMaxSegmentHealth)
    , ship_segments_(other.ship_segments_)
    , orientation_(other.orientation_)
    , top_left_(other.top_left_)
    , hit_box_(other.hit_box_)
    , bounding_hit_box_(other.bounding_hit_box_)
{}

Ship::Ship(Ship &&other)
    : kMaxSegmentHealth(other.kMaxSegmentHealth)
    , ship_segments_(other.ship_segments_)
    , orientation_(other.orientation_)
    , top_left_(other.top_left_)
    , hit_box_(other.hit_box_)
    , bounding_hit_box_(std::move(other.bounding_hit_box_))
{}

Ship::~Ship() = default;

Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        this->ship_segments_ = other.ship_segments_;
        this->orientation_ = other.orientation_;
        this->top_left_ = other.top_left_;
        this->hit_box_ = other.hit_box_;
        this->bounding_hit_box_ = other.bounding_hit_box_;
    }
    return *this;
}

Ship& Ship::operator=(Ship &&other) {
    if (this != &other) {
        this->ship_segments_ = std::move(other.ship_segments_);
        this->orientation_ = other.orientation_;
        this->top_left_ = other.top_left_;
        this->hit_box_ = other.hit_box_;
        this->bounding_hit_box_ = std::move(other.bounding_hit_box_);
    }
    return *this;
}

int Ship::getMaxSegmentHealth() const {
    return kMaxSegmentHealth;
}

int Ship::getSize() const {
    return ship_segments_.size();
}

Ship::Orientation Ship::getOrientation() const {
    return orientation_;
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
    ship_segments_ = std::vector<Entity::Segment> (size);
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