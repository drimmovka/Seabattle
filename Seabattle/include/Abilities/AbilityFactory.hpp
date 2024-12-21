#ifndef ABILITY_FACTORY_HPP
#define ABILITY_FACTORY_HPP

#include "iAbilitySpec.hpp"
#include "iAbility.hpp"

namespace seabattle
{

class AbilityFactory {
public:
    AbilityFactory();

    iAbility *buildAbility(const iAbilitySpec *iability_spec) const;
};

} // namespace seabattle


#endif // ABILITY_FACTORY_HPP