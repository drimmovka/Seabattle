#include "Exceptions/FileException.hpp"

#include <string>

namespace seabattle
{

FileException::FileException(const std::string message)
    : GameException(message)
{}

} // namespace seabattle