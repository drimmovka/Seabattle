#include "../include/coords.hpp"

#include <cstddef>
#include <functional>

namespace battleship
{

bool Coords::operator==(const Coords& other) const {
    return (this->x == other.x && this->y == other.y);
}

size_t CoordsHash::operator()(Coords coords) const {
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1); // change hashfunc
}

} // battleship