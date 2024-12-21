#include "Abilities/BombingSpec.hpp"

namespace seabattle
{

BombingSpec::BombingSpec(ShipsManager& ships_manager)
    : ships_manager(ships_manager)
{}

AbilityType BombingSpec::abilityType() const {
    return AbilityType::kBombing;
}

} // namespace seabattle