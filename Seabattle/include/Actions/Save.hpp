#ifndef SAVE_HPP
#define SAVE_HPP

#include "Action.hpp"

#include <iostream>

namespace seabattle
{

class Save : public Action {

public:

    Save(std::string save_file_name);

    ~Save();

    void execute(Game& game) override;

private:
    std::string _save_file_name;
};

} // namespace seabattle


#endif // SAVE_HPP