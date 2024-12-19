#include "Exceptions/AbilityIsAlreadyUsedException.hpp"

#include <string>

namespace seabattle
{

AbilityIsAlreadyUsedException::AbilityIsAlreadyUsedException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle