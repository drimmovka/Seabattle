#include "Exceptions/NoAbilitiesException.hpp"

#include <string>

namespace seabattle
{

NoAbilitiesException::NoAbilitiesException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle