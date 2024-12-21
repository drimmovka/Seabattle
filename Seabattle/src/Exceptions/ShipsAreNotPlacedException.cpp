#include "Exceptions/ShipsAreNotPlacedException.hpp"

#include <string>

namespace seabattle
{

ShipsAreNotPlacedException::ShipsAreNotPlacedException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle