#include "Exceptions/ListenerException.hpp"

#include <string>

namespace seabattle
{

ListenerException::ListenerException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle