#ifndef LOAD_HPP
#define LOAD_HPP

#include "Action.hpp"

#include <iostream>

namespace seabattle
{

class Load : public Action {

public:

    Load(std::string load_file_name);

    ~Load();

    void execute(Game& game) override;

private:
    std::string _load_file_name;
};

} // namespace seabattle


#endif // LOAD_HPP