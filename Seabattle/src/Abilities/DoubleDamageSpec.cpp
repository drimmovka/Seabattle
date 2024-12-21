#include "Abilities/DoubleDamageSpec.hpp"

namespace seabattle
{

DoubleDamageSpec::DoubleDamageSpec(int& damage_multiplier)
    : damage_multiplier(damage_multiplier)
{}

AbilityType DoubleDamageSpec::abilityType() const {
    return AbilityType::kDoubleDamage;
}

} // namespace seabattle