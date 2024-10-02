#include "../include/coords.hpp"

bool Coords::operator==(const Coords& other) const {
    return (this->x == other.x && this->y == other.y);
}