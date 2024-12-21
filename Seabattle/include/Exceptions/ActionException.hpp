#ifndef ACTION_EXCEPTION_HPP
#define ACTION_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class ActionException : public GameException {

public:
    ActionException(const std::string message);

};

} // namespace seabattle

#endif // ACTION_EXCEPTION_HPP