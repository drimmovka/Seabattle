#include "Abilities/Scanner.hpp"

#include "Abilities/ScannerSpec.hpp"

#include <iostream>

namespace seabattle
{

Scanner::Scanner(const ScannerSpec *scanner_spec)
    : game_map(scanner_spec->game_map)
    , top_left(scanner_spec->top_left)
    , result(scanner_spec->result)
{}

void Scanner::apply() {
    result = game_map.hasShipSegmentInArea(top_left, 2, 2);

    std::cout << "Scanner applied\n";
}

} // namespace seabattle