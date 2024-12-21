#include "Listeners/CLIListener.hpp"

namespace seabattle
{

const std::unordered_map<std::string, std::string>& CLIListener::CommandComparator::keysMap() {
    return _keys_map;
}

CLIListener::CommandComparator::CommandComparator(
    const std::unordered_map<std::string, std::function<Action *()>>& handlers_map)
    : _settings_file_name("settings.txt")
    {
    try {
        this->readFromFile(handlers_map);
    } catch(const ListenerException& e) {
        std::cout << e.what() << "\n";
        _keys_map.clear(); // just in case
        for (const auto& [key, handler] : handlers_map) {
            _keys_map[key] = key;
        }
    }
}

CLIListener::CommandComparator::~CommandComparator() = default;

void CLIListener::CommandComparator::readFromFile(
    const std::unordered_map<std::string, std::function<Action *()>>& handlers_map) {
    
    // KEY IS REAL ACTION ID HERE!!!

    std::unordered_map<std::string, std::string> tmp_keys_map;
    
    for (const auto& [key, handler] : handlers_map) {
        tmp_keys_map[key] = "";
    }

    std::ifstream fin(_settings_file_name);

    if (!fin.is_open()) {
        throw ListenerException("The settings file could not be opened. Keys will be default");
    }

    std::string key;
    while (fin >> key) {
        // no such key (action)
        if (tmp_keys_map.find(key) == tmp_keys_map.end()) {
            fin.close();
            throw ListenerException("The settings file is set incorrectly. Key (action) not found");
        }

        // More than one command per key (action)
        // case
        // key1 command1
        // key1 command2
        if (tmp_keys_map.find(key) != tmp_keys_map.end() && tmp_keys_map[key] != "") {
            fin.close();
            throw ListenerException("The settings file is set incorrectly. More than one command per key!");
        }

        std::string command;
        if (fin >> command) {
            tmp_keys_map[key] = command;
        } else {
            // case:
            // command1 key1
            // command2 {nothing}
            
            fin.close();
            throw ListenerException("The settings file is set incorrectly or damaged");
        }
    }
    fin.close();

    for (auto& [key, command] : tmp_keys_map) {
        if (command == "") {
            // the command is not assigned to the key (not enough lines in file)
            // case:
            // key ""

            throw ListenerException("The settings file is set incorrectly or damaged. Not all commands were found");
        }
    }

    std::unordered_set<std::string> commands;
    for (auto& [key, command] : tmp_keys_map) {
        if (commands.find(command) != commands.end()) {
            // Several commands correspond to one key
            // case:
            // key1 command1
            // key2 command1
            throw ListenerException("The settings file is set incorrectly or damaged. Several commands correspond to one key");
        }
        commands.insert(command);
    }
    
    // swap places [key: command] -> [command: key] and write down to real _keys_map
    for (auto& [key, command] : tmp_keys_map) {
        _keys_map[command] = key;
    }
}

std::string CLIListener::CommandComparator::getKey(const std::string& command) {
    if (_keys_map.find(command) == _keys_map.end()) {
        return "";
    }
    return _keys_map.at(command);
}

CLIListener::CLIListener()
    : _handlers_map // keys MUST be unique here!!! 
    ({
        {"attack",      [this]() { return handleAttackCommand(); }},
        {"set",         [this]() { return handleSetSettingsCommand(); }},
        {"ready",       [this]() { return handleInformAboutReadinessCommand(); }},
        {"stop",        [this]() { return handleStopCommand(); }},
        {"placerand",   [this]() { return handlePlaceShipsRandomlyCommand(); }},
        {"applyB",      [this]() { return handleApplyBombingCommand(); }},
        {"applyS",      [this]() { return handleApplyScannerCommand(); }},
        {"applyDD",     [this]() { return handleApplyDoubleDamageCommand(); }},
        {"save",        [this]() { return handleSaveCommand(); }},
        {"load",        [this]() { return handleLoadCommand(); }}
    })
    , _command_comparator(_handlers_map)
{}

CLIListener::~CLIListener() = default;

const std::unordered_map<std::string, std::string>& CLIListener::keysMap() {
    return this->_command_comparator.keysMap();
}

bool CLIListener::userWantToRunGame()  {
    bool run_new_game;
    if (!(std::cin >> run_new_game)) {
        this->resetInputStream();
        throw ListenerException("Incorrect input");
    }
    return run_new_game;
}

Action *CLIListener::getAction() {
    std::string action;
    std::cin >> action;
    
    // no exception here bc action is string

    std::string key = _command_comparator.getKey(action);
    
    if (_handlers_map.find(key) == _handlers_map.end()) {
        throw ListenerException("No such command was found");
    }

    auto handler = _handlers_map.at(key);

    return handler();
}

Action *CLIListener::handleAttackCommand() {
    int x, y;
    this->inputCoords(x, y);
    return new Attack({x, y});
}

Action *CLIListener::handleSetSettingsCommand() {
    int game_map_width, game_map_height;
    this->inputGameMapSize(game_map_width, game_map_height);

    int number_of_ships;
    std::vector<int> ship_sizes;
    this->inputShipsSizes(number_of_ships, ship_sizes);
        
    return new SetSettings(game_map_width, game_map_height, ship_sizes);
}

Action *CLIListener::handleInformAboutReadinessCommand() {
    return new InformAboutReadiness();
}

Action *CLIListener::handleStopCommand() {
    return new Stop();
}

Action *CLIListener::handlePlaceShipsRandomlyCommand() {
    return new PlaceShipsRandomly();
}

Action *CLIListener::handleApplyBombingCommand() {
    return new ApplyBombing();
}

Action *CLIListener::handleApplyScannerCommand() {
    int x, y;
    this->inputCoords(x, y);
    return new ApplyScanner({x, y});
}

Action *CLIListener::handleApplyDoubleDamageCommand() {
    return new ApplyDoubleDamage();
}

Action *CLIListener::handleSaveCommand() {
    std::string save_file_name;
    this->inputFileName(save_file_name);
    return new Save(save_file_name);
}

Action *CLIListener::handleLoadCommand() {
    std::string load_file_name;
    this->inputFileName(load_file_name);
    return new Load(load_file_name);
}

void CLIListener::inputCoords(int& x, int& y) {
    std::cout << "Input coords: ";
    if (!(std::cin >> x >> y)) {
        this->resetInputStream();
        throw ListenerException("Incorrect input");
    }
}

void CLIListener::inputFileName(std::string& file_name) {
    std::cout << "Input file name: ";
    std::cin >> file_name;
    // no exception here bc file_name is string
}

void CLIListener::inputGameMapSize(int& game_map_width, int& game_map_height) {
    std::cout << "Input game map w & h: ";
    if (!(std::cin >> game_map_width >> game_map_height)) {
        this->resetInputStream();
        throw ListenerException("Incorrect input");
    }
}

void CLIListener::inputShipsSizes(int& number_of_ships, std::vector<int>& ship_sizes) {
    std::cout << "Input the number of ships: ";
    if (!(std::cin >> number_of_ships)) {
        this->resetInputStream();
        throw ListenerException("Incorrect input");
    }

    std::cout << "Input ships sizes: ";
    ship_sizes.assign(number_of_ships, 0);
    for (int i = 0; i < ship_sizes.size(); ++i) {
        if (!(std::cin >> ship_sizes[i])) {
            this->resetInputStream();
            throw ListenerException("Incorrect input");
        }
    }
}

void CLIListener::resetInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

} // namespace seabattle