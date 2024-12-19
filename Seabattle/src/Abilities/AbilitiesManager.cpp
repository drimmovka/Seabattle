#include "Abilities/AbilitiesManager.hpp"

#include "Abilities/iAbility.hpp"
#include "Abilities/iAbilitySpec.hpp"
#include "Abilities/AbilityType.hpp"
#include "Exceptions/NoAbilitiesException.hpp"

#include <algorithm>
#include <random>

namespace seabattle
{
AbilitiesManager::AbilitiesManager()
    : ability_factory_()
    , all_abilities_{AbilityType::kDoubleDamage, AbilityType::kScanner, AbilityType::kBombing}
    , rng_(std::random_device()())
    , distrib_(0, all_abilities_.size() - 1)
{
    this->generateInitialAbilities();
}

AbilitiesManager::~AbilitiesManager() = default;

bool AbilitiesManager::hasAbilities() const {

    return !abilities_.empty();
}

AbilityType AbilitiesManager::frontAbility() const {
    if (abilities_.empty()) {
        throw NoAbilitiesException("In AbilitiesManager::frontAbility: no abilities are available");
    }
    return abilities_.front();
}

void AbilitiesManager::addRandomAbility() {
    AbilityType random_ability = all_abilities_[distrib_(rng_)];
    abilities_.push_back(random_ability);
}

void AbilitiesManager::applyFrontAbility(const iAbilitySpec& ability_spec) {    
    if (abilities_.empty()) {
        throw NoAbilitiesException::NoAbilitiesException("In AbilitiesManager::castFrontAbility: no abilities are available");
    }
    if (abilities_.front() != ability_spec.abilityType()) {
        throw NoAbilitiesException::NoAbilitiesException("In AbilitiesManager::castFrontAbility: ability_spec does not match type");
    }
    
    iAbility* front_ability = ability_factory_.buildAbility(&ability_spec);

    front_ability->apply();
    
    delete front_ability;

    abilities_.pop_front();
}

void AbilitiesManager::generateInitialAbilities() {
    std::shuffle(all_abilities_.begin(), all_abilities_.end(), rng_);

    for (auto& ability : all_abilities_) {
        abilities_.push_back(ability);
    }
    
}

} // namespace seabattle