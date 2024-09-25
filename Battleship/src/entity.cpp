#include "../include/entity.hpp"

#include <algorithm>

Entity::Entity() = default;

Entity::~Entity() = default;

Entity::Segment::Segment()
    : Segment(0)
{}

Entity::Segment::Segment(int max_health)
    : max_health_(max_health)
    , health_(max_health)
{}

Entity::Segment::~Segment() = default;

int Entity::Segment::getHealth() const {
    return health_;
}

Entity::Status Entity::Segment::getStatus() const {
    if (getHealth() == max_health_) {
        return Status::intact;
    }
    if (getHealth() == 0) {
        return Status::destroyed;
    }
    return Status::damaged;
}

void Entity::Segment::dealDamage(int damage) {
    health_ = std::max(0, health_ - damage);
}

void Entity::Segment::increaseHealth(int recoveryHealth) {
    health_ = std::min(max_health_, health_ + recoveryHealth);
}