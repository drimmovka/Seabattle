#ifndef ABILITY_IS_ALREADY_USED_EXCEPTION_HPP
#define ABILITY_IS_ALREADY_USED_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class AbilityIsAlreadyUsedException : public GameException {

public:
    AbilityIsAlreadyUsedException(const std::string message);

};

} // namespace seabattle

#endif // ABILITY_IS_ALREADY_USED_EXCEPTION_HPP