#include "Abilities/AbilityFactory.hpp"

#include "Abilities/iAbility.hpp"
#include "Abilities/iAbilitySpec.hpp"
#include "Abilities/AbilityType.hpp"
#include "Abilities/DoubleDamageSpec.hpp"
#include "Abilities/ScannerSpec.hpp"
#include "Abilities/BombingSpec.hpp"
#include "Abilities/DoubleDamage.hpp"
#include "Abilities/Scanner.hpp"
#include "Abilities/Bombing.hpp"

namespace seabattle
{

AbilityFactory::AbilityFactory() = default;

iAbility *AbilityFactory::buildAbility(const iAbilitySpec *iability_spec) const {
    switch (iability_spec->abilityType())
    {
    case AbilityType::kDoubleDamage: return new DoubleDamage(static_cast<const DoubleDamageSpec *>(iability_spec));
    case AbilityType::kScanner: return new Scanner(static_cast<const ScannerSpec *>(iability_spec));
    case AbilityType::kBombing: return new Bombing(static_cast<const BombingSpec *>(iability_spec));
    default: break; // throw error
    }
}

} // namespace seabattle