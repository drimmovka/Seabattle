#ifndef STOP_HPP
#define STOP_HPP

#include "Action.hpp"

namespace seabattle
{

class Stop : public Action {

public:

    Stop();

    ~Stop();

    void execute(Game& game) override;

private:
    Coords _coords;
};

} // namespace seabattle


#endif // STOP_HPP