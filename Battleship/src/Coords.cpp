#include "../include/Coords.hpp"

#include <cstddef>
#include <functional>

namespace battleship
{

size_t Coords::CoordsHash::operator()(Coords coords) const {
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1); // change hashfunc
}

bool Coords::operator==(const Coords& other) const {
    return (this->x == other.x && this->y == other.y);
}

} // battleship