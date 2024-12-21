#include "Actions/ApplyDoubleDamage.hpp"

namespace seabattle
{

ApplyDoubleDamage::ApplyDoubleDamage()
    : Action({GamePhase::kMoving})
{}

ApplyDoubleDamage::~ApplyDoubleDamage() {}

void ApplyDoubleDamage::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        // Since the action can only be performed in the movement phase, it is guaranteed that the fields are initialized
        game.userApplyAbility( new DoubleDamageSpec(*game.gameData()->user_damage) );
    } else {
        throw ActionException("ApplyDoubleDamage cannot be executed in current game phase");
    }
}

} // namespace seabattle

