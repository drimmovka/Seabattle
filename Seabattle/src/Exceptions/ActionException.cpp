#include "Exceptions/ActionException.hpp"

#include <string>

namespace seabattle
{

ActionException::ActionException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle