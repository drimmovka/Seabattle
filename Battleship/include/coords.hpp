#ifndef COORDS_HPP_
#define COORDS_HPP_

struct Coords {
    int x;
    int y;

    bool operator==(const Coords& other) const {
        return (x == other.x && y == other.y);
    }
};

#endif