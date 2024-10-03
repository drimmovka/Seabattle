#ifndef COORDS_HPP_
#define COORDS_HPP_

#include <cstddef>

namespace battleship
{

struct Coords {
    int x;
    int y;

    bool operator==(const Coords& other) const;
};

struct CoordsHash {
    size_t operator()(Coords coords) const;
};

} // battleship


#endif // COORDS_HPP_