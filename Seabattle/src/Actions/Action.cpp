#include "Actions/Action.hpp"


namespace seabattle
{

Action::Action(std::unordered_set<GamePhase> active_game_phases)
    : _active_game_phases(active_game_phases)
{}

Action::~Action() {}


bool Action::canBeExecuted(const Game& game) {
    return (_active_game_phases.count(game.currentPhase()) != 0);
}


} // namespace seabattle

