#ifndef APPLY_SCANNER_HPP
#define APPLY_SCANNER_HPP

#include "Action.hpp"
#include "Abilities/ScannerSpec.hpp"
#include <iostream> // REMOVE

namespace seabattle
{

class ApplyScanner : public Action {

public:

    ApplyScanner(Coords coords);

    ~ApplyScanner();
    
    void execute(Game& game) override;

private:
    Coords _coords;

};
} // namespace seabattle


#endif // APPLY_SCANNER_HPP