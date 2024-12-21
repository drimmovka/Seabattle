#include "Actions/InformAboutReadiness.hpp"

namespace seabattle {

InformAboutReadiness::InformAboutReadiness()
    : Action({GamePhase::kPlacingShips})
{}

InformAboutReadiness::~InformAboutReadiness() {}

void InformAboutReadiness::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        try {
            game.allowUserMakingMoves();
        } catch(const ShipsAreNotPlacedException& e) {
            throw ActionException("InformAboutReadiness cannot be executed until the ships are placed on the game map");
        }
    } else {
        throw ActionException("InformAboutReadiness cannot be executed in current game phase");
    }
}


} // namespace seabattle

