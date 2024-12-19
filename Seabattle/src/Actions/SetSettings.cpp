#include "Actions/SetSettings.hpp"

#include <iostream>

namespace seabattle
{

SetSettings::SetSettings(int game_map_width, int game_map_height, std::vector<int>& ship_sizes)
    : Action({GamePhase::kSettingSettings})
    , game_map_width(game_map_width)
    , game_map_height(game_map_height)
    , ship_sizes(ship_sizes)
{}

SetSettings::~SetSettings() {}

void SetSettings::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        game.setSettings(game_map_width, game_map_height, ship_sizes);
    } else {
        throw ActionException("SetSettings cannot be executed in current game phase");
    }
}

} // namespace seabattle