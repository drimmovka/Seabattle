#include "Actions/Load.hpp"

namespace seabattle
{


Load::Load(std::string load_file_name)
    : Action({GamePhase::kSettingSettings, GamePhase::kPlacingShips, GamePhase::kMoving})
    , _load_file_name(load_file_name)
{}

Load::~Load() {}

void Load::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        game.userLoad(_load_file_name);
    } else {
        throw ActionException("Load cannot be executed in current game phase");
    }
}


} // namespace seabattle