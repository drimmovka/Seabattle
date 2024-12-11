#ifndef INFORM_ABOUT_READINESS_HPP
#define INFORM_ABOUT_READINESS_HPP

#include "Action.hpp"

#include "Exceptions/ShipsAreNotPlacedException.hpp"

#include <iostream>

namespace seabattle
{

class InformAboutReadiness : public Action {

public:

    InformAboutReadiness();

    ~InformAboutReadiness();

    void execute(Game& game) override;

};

} // namespace seabattle


#endif // INFORM_ABOUT_READINESS_HPP