#ifndef BOMBING_SPEC_HPP
#define BOMBING_SPEC_HPP

#include "iAbilitySpec.hpp"
#include "AbilityType.hpp"
#include "ShipsManager.hpp"

namespace seabattle
{
class BombingSpec : public iAbilitySpec {

public:
    BombingSpec(ShipsManager& ships_manager);

    AbilityType abilityType() const override;

    ShipsManager& ships_manager;

};

} // namespace seabattle


#endif // BOMBING_SPEC_HPP