#include "Abilities/DoubleDamage.hpp"

#include "Abilities/DoubleDamageSpec.hpp"

#include <iostream>

namespace seabattle
{

DoubleDamage::DoubleDamage(const DoubleDamageSpec *double_damage_spec)
    : damage_multiplier(double_damage_spec->damage_multiplier)
{}

void DoubleDamage::apply() {
    damage_multiplier = 2;
    std::cout << "DoubleDamage applied\n";
}

} // namespace seabattle