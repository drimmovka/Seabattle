#include "Actions/Attack.hpp"

namespace seabattle {

Attack::Attack(Coords coords)
    : Action({GamePhase::kMoving})
    , _coords(coords)
{}

Attack::~Attack() {}

void Attack::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        game.userAttack(_coords);
    } else {
        throw ActionException("Attack cannot be executed in current game phase");
    }
}


} // namespace seabattle