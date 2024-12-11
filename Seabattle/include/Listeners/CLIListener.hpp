#ifndef CLI_LISTENER_HPP
#define CLI_LISTENER_HPP

#include "Actions/Action.hpp"
#include "Actions/Attack.hpp"
#include "Actions/SetSettings.hpp"
#include "Actions/InformAboutReadiness.hpp"
#include "Actions/Stop.hpp"
#include "Actions/PlaceShipsRandomly.hpp"
#include "Actions/ApplyBombing.hpp"
#include "Actions/ApplyScanner.hpp"
#include "Actions/ApplyDoubleDamage.hpp"
#include "Actions/Save.hpp"
#include "Actions/Load.hpp"

#include "Exceptions/ListenerException.hpp"

#include <iostream>
#include <string>

namespace seabattle
{

class CLIListener {
public:
    CLIListener();
    ~CLIListener();

    bool userWantToRunGame();

    Action *getAction();
    
};

} // namespace seabattle


#endif // CLI_LISTENER_HPP