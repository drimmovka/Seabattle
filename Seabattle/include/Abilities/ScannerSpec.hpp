#ifndef SCANNER_SPEC_HPP
#define SCANNER_SPEC_HPP

#include "iAbilitySpec.hpp"
#include "GameMap.hpp"
#include "Coords.hpp"

namespace seabattle
{

class ScannerSpec : public iAbilitySpec {

public:
    ScannerSpec(GameMap& game_map, Coords top_left, bool& result);

    AbilityType abilityType() const override;

    GameMap& game_map;
    Coords top_left;
    bool& result;
    
};

} // namespace seabattle


#endif // SCANNER_SPEC_HPP