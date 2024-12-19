#ifndef FILE_EXCEPTION_HPP
#define FILE_EXCEPTION_HPP

#include "GameException.hpp"

#include <string>

namespace seabattle
{

class FileException : public GameException {

public:
    FileException(const std::string message);

};

} // namespace seabattle

#endif // FILE_EXCEPTION_HPP