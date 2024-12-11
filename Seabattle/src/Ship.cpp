#include "Ship.hpp"

#include "Coords.hpp"

#include <stdexcept>
#include <vector>

#include <iostream>

namespace seabattle
{

Ship::Segment::Segment(int max_health)
    : kMaxHealth(max_health)
{
    if (kMaxHealth < 0) {
        throw std::invalid_argument("Max segment health cannot be negative");
    }
    health_ = kMaxHealth;
}

Ship::Segment::~Segment() = default;

int Ship::Segment::health() const {
    return health_;
}

Ship::Segment::Status Ship::Segment::status() const {
    if (health_ == 0) {
        return Status::kDestroyed;
    }
    if (health_ == kMaxHealth) {
        return Status::kIntact;
    }
    return Status::kDamaged;
}

void Ship::Segment::dealDamage(int damage) {
    std::cout << damage << "\n";
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }
    health_ = std::max(0, health_ - damage);
}

Ship::Ship(int size)
    : kMaxSegmentHealth(2)
    , placed_on_game_map_(false)
    , id_(-1)
{
    if (size <= 0) {
        throw std::invalid_argument("Ship size must be greater than 0");
    }
    for (int i = 0; i < size; i++) {
        segments_.push_back(new Segment(kMaxSegmentHealth));
    }
}

Ship::Ship(const Ship& other)
    : kMaxSegmentHealth(other.kMaxSegmentHealth)
    , placed_on_game_map_(other.placed_on_game_map_)
    , segments_(other.segments_)
    , id_(other.id_)
{}

Ship::Ship(Ship&& other)
    : kMaxSegmentHealth(other.kMaxSegmentHealth)
    , placed_on_game_map_(other.placed_on_game_map_)
    , segments_(std::move(other.segments_))
    , id_(other.id_)
{}

Ship::~Ship() {
    for (auto& segment : segments_) {
        delete segment;
    }
}

Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        placed_on_game_map_ = other.placed_on_game_map_;
        segments_ = other.segments_;
    }
    return *this;
}

Ship& Ship::operator=(Ship&& other) {
    if (this != &other) {
        placed_on_game_map_ = other.placed_on_game_map_;
        segments_ = std::move(other.segments_);
    }
    return *this;
}

Ship::Segment *Ship::operator[](int segment_index) {
    if (segment_index < 0 || segment_index >= segments_.size()) {
        throw std::out_of_range("Segment index out of range");
    }
    return segments_[segment_index];
}

int Ship::size() const {
    return segments_.size();
}

int Ship::maxSegHealth() const {return kMaxSegmentHealth;}

int Ship::id() const {return id_;}

Ship::Status Ship::status() const {
    bool destroyed = true;
    bool intact = true;

    for (auto& segment : segments_) {
        Segment::Status segment_status = segment->status();
        intact &= (segment_status == Segment::Status::kIntact);
        destroyed &= (segment_status == Segment::Status::kDestroyed);
    }
    
    if (destroyed) {
        return Status::kDestroyed;
    }
    if (intact) {
        return Status::kIntact;
    }
    
    return Status::kDamaged;
}

void Ship::setId(int id) {id_ = id;}


void Ship::placeOnGameMap() {
    placed_on_game_map_ = true;
}

void Ship::removeFromGameMap() {
    placed_on_game_map_ = false;
}

bool Ship::placedOnGameMap() {
    return placed_on_game_map_;
}

} // namespace seabattle