#ifndef DOUBLE_DAMAGE_SPEC_HPP
#define DOUBLE_DAMAGE_SPEC_HPP

#include "iAbilitySpec.hpp"

namespace seabattle
{

class DoubleDamageSpec : public iAbilitySpec {

public:
    DoubleDamageSpec(int& damage_multiplier);

    AbilityType abilityType() const override;

    int& damage_multiplier;

};

} // namespace seabattle


#endif // DOUBLE_DAMAGE_SPEC_HPP