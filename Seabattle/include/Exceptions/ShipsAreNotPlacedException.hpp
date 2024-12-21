#ifndef SHIPS_ARE_NOT_PLACED_EXCEPTION_HPP
#define SHIPS_ARE_NOT_PLACED_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class ShipsAreNotPlacedException : public GameException {

public:
    ShipsAreNotPlacedException(const std::string message);

};

} // namespace seabattle

#endif // SHIPS_ARE_NOT_PLACED_EXCEPTION_HPP