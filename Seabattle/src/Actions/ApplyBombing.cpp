#include "Actions/ApplyBombing.hpp"

namespace seabattle
{

ApplyBombing::ApplyBombing()
    : Action({GamePhase::kMoving})
{}

ApplyBombing::~ApplyBombing() {}

void ApplyBombing::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        // Since the action can only be performed in the movement phase, it is guaranteed that the fields are initialized
        game.userApplyAbility( new BombingSpec(*game.gameData()->enemy_ships_manager) );
    } else {
        throw ActionException("ApplyBombing cannot be executed in current game phase");
    }
}

} // namespace seabattle