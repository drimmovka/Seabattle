#include "Exceptions/ShipPlacementException.hpp"

#include <string>

namespace seabattle
{

ShipPlacementException::ShipPlacementException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle