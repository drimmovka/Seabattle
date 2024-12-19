#include "Actions/Save.hpp"

namespace seabattle
{

Save::Save(std::string save_file_name)
    : Action({GamePhase::kPlacingShips, GamePhase::kMoving}) // game cannot be saved until game data initialized!!!
    , _save_file_name(save_file_name)
{}

Save::~Save() {}

void Save::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        game.userSave(_save_file_name);
    } else {
        throw ActionException("Save cannot be executed in current game phase");
    }
}

} // namespace seabattle