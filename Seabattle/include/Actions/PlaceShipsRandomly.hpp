#ifndef PLACE_SHIPS_RANDOMLY_HPP
#define PLACE_SHIPS_RANDOMLY_HPP

#include "Action.hpp"

#include <iostream>

namespace seabattle
{

class PlaceShipsRandomly : public Action {

public:

    PlaceShipsRandomly();

    ~PlaceShipsRandomly();

    void execute(Game& game) override;

};

} // namespace seabattle


#endif // PLACE_SHIPS_RANDOMLY_HPP