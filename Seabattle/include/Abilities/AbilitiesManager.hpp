#ifndef ABILITIES_MANAGER_HPP
#define ABILITIES_MANAGER_HPP

#include "AbilityFactory.hpp"
#include "iAbility.hpp"
#include "iAbilitySpec.hpp"
#include "AbilityType.hpp"

#include <queue>
#include <algorithm>
#include <random>
#include <fstream>

namespace seabattle
{

class AbilitiesManager {

public:

    AbilitiesManager();

    AbilitiesManager(std::vector<AbilityType> abilities)
        : ability_factory_()
        , all_abilities_{AbilityType::kDoubleDamage, AbilityType::kScanner, AbilityType::kBombing}
        , rng_(std::random_device()())
        , distrib_(0, all_abilities_.size() - 1)
    {
        for (auto& i : abilities) {
            abilities_.push_back(i);
        }
    }

    ~AbilitiesManager();

    bool hasAbilities() const;

    AbilityType frontAbility() const;
    
    void addRandomAbility();
    
    void applyFrontAbility(const iAbilitySpec& ability_spec);

    friend std::ostream& operator<<(std::ostream& os, const AbilitiesManager& abilities_manager) {
        os << abilities_manager.abilities_.size() << "\n";
        for (const auto& i : abilities_manager.abilities_) {
            os << (int) i << " ";
        }
        os << "\n";
        return os;
    }

private:
    std::deque<AbilityType> abilities_;
    AbilityFactory ability_factory_;
    std::vector<AbilityType> all_abilities_;
    std::default_random_engine rng_;
    std::uniform_int_distribution<int> distrib_;
    
    void generateInitialAbilities();
};

} // namespace seabattle


#endif // ABILITIES_MANAGER_HPP