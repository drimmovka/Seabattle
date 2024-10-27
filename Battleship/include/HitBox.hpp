#ifndef HIT_BOX_HPP_
#define HIT_BOX_HPP_

#include "Coords.hpp"

namespace battleship
{

struct HitBox {
    Coords top_left;
    Coords bottom_right;
};

}

#endif // HIT_BOX_HPP_