#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "iAbility.hpp"
#include "ScannerSpec.hpp"
#include "GameMap.hpp"
#include "Coords.hpp"

namespace seabattle
{

class Scanner : public iAbility {
public:
    Scanner(const ScannerSpec *scanner_spec);

    void apply() override;
private:
    GameMap& game_map;
    Coords top_left;
    bool& result;
};

} // namespace seabattle


#endif // SCANNER_HPP