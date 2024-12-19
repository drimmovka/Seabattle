#ifndef COORDS_HPP
#define COORDS_HPP

#include <cstddef>

namespace seabattle
{

struct Coords {
    int x;
    int y;

    struct CoordsHash {
        size_t operator()(Coords coords) const;
    };

    bool operator==(const Coords& other) const;
};

} // namespace seabattle


#endif // COORDS_HPP