#ifndef SHIP_PLACEMENT_EXCEPTION_HPP
#define SHIP_PLACEMENT_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class ShipPlacementException : public GameException {

public:
    ShipPlacementException(const std::string message);

};

} // namespace seabattle

#endif // SHIP_PLACEMENT_EXCEPTION_HPP