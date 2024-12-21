#include "Coords.hpp"

#include <cstddef>
#include <utility>
#include <functional>

namespace seabattle
{

size_t Coords::CoordsHash::operator()(Coords coords) const {
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) >> 1);    
}

bool Coords::operator==(const Coords& other) const {
    return (this->x == other.x && this->y == other.y);
}

} // namespace seabattle