#include "Exceptions/AttackException.hpp"

#include <string>

namespace seabattle
{

AttackException::AttackException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle