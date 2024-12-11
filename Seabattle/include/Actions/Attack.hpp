#ifndef ATTACK_HPP
#define ATTACK_HPP

#include "Action.hpp"

#include <iostream>

namespace seabattle
{

class Attack : public Action {

public:

    Attack(Coords coords);

    ~Attack();

    void execute(Game& game) override;

private:
    Coords _coords;
};

} // namespace seabattle


#endif // ATTACK_HPP