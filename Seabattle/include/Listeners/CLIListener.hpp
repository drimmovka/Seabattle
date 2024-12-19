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
#include <functional>

namespace seabattle
{

class CLIListener {
public:
    CLIListener();
    
    ~CLIListener();
    
    const std::unordered_map<std::string, std::string>& keysMap();

    bool userWantToRunGame();

    Action *getAction();

private:
    class CommandComparator {
    public:
        explicit CommandComparator(const std::unordered_map<std::string, std::function<Action *()>>& handlers_map);

        ~CommandComparator();

        std::string getKey(const std::string& command);

        const std::unordered_map<std::string, std::string>& keysMap();
        
    private:
        std::unordered_map<std::string, std::string> _keys_map;

    };

private:

    const std::unordered_map<std::string, std::function<Action *()>> _handlers_map;

    CommandComparator _command_comparator;

private:

    Action *handleAttackCommand();

    Action *handleSetSettingsCommand();

    Action *handleInformAboutReadinessCommand();

    Action *handleStopCommand();

    Action *handlePlaceShipsRandomlyCommand();

    Action *handleApplyBombingCommand();

    Action *handleApplyScannerCommand();

    Action *handleApplyDoubleDamageCommand();

    Action *handleSaveCommand();

    Action *handleLoadCommand();

    void inputCoords(int& x, int& y);

    void inputFileName(std::string& file_name);

    void inputGameMapSize(int& game_map_width, int& game_map_height);

    void inputShipsSizes(int& number_of_ships, std::vector<int>& ship_sizes);

    void resetInputStream();
};

} // namespace seabattle


#endif // CLI_LISTENER_HPP