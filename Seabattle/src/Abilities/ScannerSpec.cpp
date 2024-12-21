#include "Abilities/ScannerSpec.hpp"

namespace seabattle
{

ScannerSpec::ScannerSpec(GameMap& game_map, Coords top_left, bool& result)
    : game_map(game_map)
    , top_left(top_left)
    , result(result)
{}

AbilityType ScannerSpec::abilityType() const {
    return AbilityType::kScanner;
}

} // namespace seabattle