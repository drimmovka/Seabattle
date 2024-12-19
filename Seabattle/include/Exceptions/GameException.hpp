#ifndef GAME_EXCEPTION_HPP
#define GAME_EXCEPTION_HPP

#include <string>
#include <exception>

namespace seabattle
{

class GameException : public std::exception {

public:

    explicit GameException(const std::string& message);

    const char *what() const noexcept override;

protected:
    const std::string _message;
};

} // namespace seabattle

#endif // GAME_EXCEPTION_HPP