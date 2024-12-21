#ifndef LISTENER_EXCEPTION_HPP
#define LISTENER_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class ListenerException : public GameException {

public:
    ListenerException(const std::string message);

};

} // namespace seabattle

#endif // LISTENER_EXCEPTION_HPP