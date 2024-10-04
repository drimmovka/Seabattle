#include "../include/ship.hpp"

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace battleship
{

Ship::Ship()
    : Ship(1)
{}

Ship::Ship(uint32_t size)
    : kMaxSegmentHealth(2)
    , ship_segments_(size, Ship::Segment(kMaxSegmentHealth)) // mb move it inside scope?
{
    if (size == 0) {
        throw std::invalid_argument("Ship size must be greater than 0");
    }
}

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

uint32_t Ship::size() const {
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

int Ship::segmentHealth(uint32_t segment_index) const {
    if (segment_index < 0 || segment_index >= size()) {
        throw std::out_of_range("segment index out of range");
    }

    return ship_segments_[segment_index].health();

}

void Ship::damageSegment(uint32_t segment_index, int damage) {
    if (segment_index < 0 || segment_index >= size()) {
        throw std::out_of_range("segment index out of range");
    }

    ship_segments_[segment_index].dealDamage(damage);
}

void Ship::repairSegment(uint32_t segment_index, int recoveryHealth) {
    if (segment_index < 0 || segment_index >= size()) {
        throw std::out_of_range("segment index out of range");
    }

    ship_segments_[segment_index].increaseHealth(recoveryHealth);
}

Ship::Segment::Segment()
    : Segment(0)
{}

Ship::Segment::Segment(uint32_t max_health)
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
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }
    health_ = std::max(0, health_ - damage);
}

void Ship::Segment::increaseHealth(int recoveryHealth) {
    if (recoveryHealth < 0) {
        throw std::invalid_argument("Recovery health cannot be negative");
    }
    health_ = std::min(max_health_, health_ + recoveryHealth);
}

} // battleship