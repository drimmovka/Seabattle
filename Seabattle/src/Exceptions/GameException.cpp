#include "Exceptions/GameException.hpp"

namespace seabattle
{

GameException::GameException(const std::string& message)
    : _message(message)
{}

const char *GameException::what() const noexcept {
    return _message.c_str();
}

} // namespace seabattle