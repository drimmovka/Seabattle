#ifndef APPLY_DOUBLE_DAMAGE_HPP
#define APPLY_DOUBLE_DAMAGE_HPP

#include "Action.hpp"
#include "Abilities/DoubleDamageSpec.hpp"

namespace seabattle
{

class ApplyDoubleDamage : public Action {

public:

    ApplyDoubleDamage();

    ~ApplyDoubleDamage();
    
    void execute(Game& game) override;

};
} // namespace seabattle


#endif // APPLY_DOUBLE_DAMAGE_HPP