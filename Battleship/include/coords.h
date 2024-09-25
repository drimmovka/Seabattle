#ifndef COORDS_H_
#define COORDS_H_

struct Coords {
    int x;
    int y;

    bool operator==(Coords& other) const {
        return (x == other.x && y == other.y);
    }
};

#endif