#ifndef NO_ABILITIES_EXCEPTION_HPP
#define NO_ABILITIES_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class NoAbilitiesException : public GameException {

public:
    NoAbilitiesException(const std::string message);

};

} // namespace seabattle

#endif // NO_ABILITIES_EXCEPTION_HPP