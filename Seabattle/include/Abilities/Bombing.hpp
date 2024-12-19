#ifndef BOMBING_HPP
#define BOMBING_HPP

#include "iAbility.hpp"
#include "BombingSpec.hpp"
#include "ShipsManager.hpp"

namespace seabattle
{

class Bombing : public iAbility {
public:
    Bombing(const BombingSpec *bombing_spec);

    void apply() override;

private:
    ShipsManager& ships_manager;
};

} // namespace seabattle


#endif // BOMBING_HPP