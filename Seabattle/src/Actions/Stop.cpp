#include "Actions/Stop.hpp"

namespace seabattle
{

Stop::Stop()
    : Action({GamePhase::kSettingSettings, GamePhase::kPlacingShips, GamePhase::kMoving})
{}

Stop::~Stop() {}

void Stop::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        game.stop();
    } else {
        throw ActionException("Stop cannot be executed in current game phase");
    }
}

} // namespace seabattle