#include "../include/ship.hpp"

#include <stdexcept>
#include <vector>

namespace battleship
{

Ship::Ship()
    : Ship(1)
{}

Ship::Ship(int size)
    : kMaxSegmentHealth(2)
    , ship_segments_(size, Ship::Segment(kMaxSegmentHealth))
{}

Ship::Ship(const Ship& other)
    : kMaxSegmentHealth(other.kMaxSegmentHealth)
    , ship_segments_(other.ship_segments_)
{}

Ship::Ship(Ship&& other)
    : kMaxSegmentHealth(other.kMaxSegmentHealth)
    , ship_segments_(std::move(other.ship_segments_))
{}

Ship::~Ship() = default;

Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        this->ship_segments_ = other.ship_segments_;
    }
    return *this;
}

Ship& Ship::operator=(Ship&& other) {
    if (this != &other) {
        this->ship_segments_ = std::move(other.ship_segments_);
    }
    return *this;
}

int Ship::maxSegmentHealth() const {
    return kMaxSegmentHealth;
}

int Ship::size() const {
    return ship_segments_.size();
}

Ship::Status Ship::status() const {
    bool destroyed = true;
    bool intact = true;

    for (auto& segment : ship_segments_) {
        Status segment_status = segment.status();
        intact &= (segment_status == Status::kIntact);
        destroyed &= (segment_status == Status::kDestroyed);
    }
    
    if (destroyed) {
        return Status::kDestroyed;
    }
    if (intact) {
        return Status::kIntact;
    }
    
    return Status::kDamaged;
}

int Ship::segmentHealth(int segment_index) const {
    if (segment_index < 0 || segment_index >= size()) {
        throw std::out_of_range("segment index out of range");
    }

    return ship_segments_[segment_index].health();

}

void Ship::damageSegment(int segment_index, int damage) {
    if (segment_index < 0 || segment_index >= size()) {
        throw std::out_of_range("segment index out of range");
    }

    ship_segments_[segment_index].dealDamage(damage);
}

void Ship::repairSegment(int segment_index, int recoveryHealth) {
    if (segment_index < 0 || segment_index >= size()) {
        throw std::out_of_range("segment index out of range");
    }

    ship_segments_[segment_index].increaseHealth(recoveryHealth);
}

Ship::Segment::Segment()
    : Segment(0)
{}

Ship::Segment::Segment(int max_health)
    : max_health_(max_health)
    , health_(max_health)
{}

Ship::Segment::~Segment() = default;

int Ship::Segment::health() const {
    return health_;
}

Ship::Status Ship::Segment::status() const {
    if (health() == 0) {
        return Status::kDestroyed;
    }
    if (health() == max_health_) {
        return Status::kIntact;
    }
    return Status::kDamaged;
}

void Ship::Segment::dealDamage(int damage) {
    health_ = std::max(0, health_ - damage);
}

void Ship::Segment::increaseHealth(int recoveryHealth) {
    health_ = std::min(max_health_, health_ + recoveryHealth);
}

} // battleship