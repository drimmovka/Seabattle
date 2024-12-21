#ifndef ATTACK_EXCEPTION_HPP
#define ATTACK_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class AttackException : public GameException {

public:
    AttackException(const std::string message);

};

} // namespace seabattle

#endif // ATTACK_EXCEPTION_HPP