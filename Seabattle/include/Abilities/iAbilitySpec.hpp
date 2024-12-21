#ifndef iABILITY_SPEC_HPP
#define iABILITY_SPEC_HPP

#include "AbilityType.hpp"

namespace seabattle
{

class iAbilitySpec {
public:
    virtual AbilityType abilityType() const = 0;
};

} // namespace seabattle


#endif // iABILITY_SPEC_HPP