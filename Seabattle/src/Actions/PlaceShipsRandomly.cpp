#include "Actions/PlaceShipsRandomly.hpp"

namespace seabattle
{

PlaceShipsRandomly::PlaceShipsRandomly()
    : Action({GamePhase::kPlacingShips})
{}

PlaceShipsRandomly::~PlaceShipsRandomly() {}

void PlaceShipsRandomly::execute(Game& game) {
    if (this->canBeExecuted(game)) {
        game.userPlaceShipsRandomly();
    } else {
        throw ActionException("PlaceShipsRandomly cannot be executed in current game phase");
    }
}


} // namespace seabattle