#ifndef APPLY_BOMBING_HPP
#define APPLY_BOMBING_HPP

#include "Action.hpp"
#include "Abilities/BombingSpec.hpp"

namespace seabattle
{

class ApplyBombing : public Action {

public:

    ApplyBombing();

    ~ApplyBombing();
    
    void execute(Game& game) override;

};
} // namespace seabattle


#endif // APPLY_BOMBING_HPP