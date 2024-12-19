#ifndef ACTION_HPP
#define ACTION_HPP

#include "Game.hpp"
#include "GamePhase.hpp"
#include "Exceptions/ActionException.hpp"

#include <unordered_set>
#include <iostream>

namespace seabattle
{

class Action {

public:

    Action(std::unordered_set<GamePhase> active_game_phases);

    ~Action();

    virtual void execute(Game& game) = 0;

protected:
    std::unordered_set<GamePhase> _active_game_phases; 

    bool canBeExecuted(const Game& game);
};

} // namespace seabattle


#endif // ACTION_HPP