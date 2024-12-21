#ifndef DOUBLE_DAMAGE_HPP
#define DOUBLE_DAMAGE_HPP

#include "iAbility.hpp"
#include "DoubleDamageSpec.hpp"

namespace seabattle
{
class DoubleDamage : public iAbility {
public:
    DoubleDamage(const DoubleDamageSpec *double_damage_spec);

    void apply() override;

private:
    int& damage_multiplier;

};

} // namespace seabattle


#endif // DOUBLE_DAMAGE_HPP