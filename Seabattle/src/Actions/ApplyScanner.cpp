#include "Actions/ApplyScanner.hpp"

namespace seabattle
{

ApplyScanner::ApplyScanner(Coords coords)
    : Action({GamePhase::kMoving})
    , _coords(coords)
{}

ApplyScanner::~ApplyScanner() {}

void ApplyScanner::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        // Since the action can only be performed in the movement phase, it is guaranteed that the game_data fields are initialized
        game.userApplyAbility( new ScannerSpec(*game.gameData()->enemy_game_map, _coords, *game.gameData()->user_scanner_result) );
        
        std::cout << "Scanner result: " << *game.gameData()->user_scanner_result << "\n"; // DEBUG observer needed

    } else {
        throw ActionException("ApplyScanner cannot be executed in current game phase");
    }
}

} // namespace seabattle