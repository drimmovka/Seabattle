#include "Listeners/CLIListener.hpp"

namespace seabattle
{

CLIListener::CLIListener() {}

CLIListener::~CLIListener() {}

bool CLIListener::userWantToRunGame() {
    bool run_new_game;
    std::cin >> run_new_game;
    return run_new_game;
}

Action *CLIListener::getAction() {
    std::string action;
    std::cin >> action;
    
    if (action == "set") {
        int game_map_width, game_map_height, number_of_ships;
        std::cin >> game_map_height >> game_map_width >> number_of_ships;
        
        std::vector<int> ship_sizes(number_of_ships);
        for (int i=0; i<number_of_ships; i++) {
            std::cin >> ship_sizes[i];
        }
        
        return new SetSettings(game_map_width, game_map_height, ship_sizes);
    }

    if (action == "ready") {
        return new InformAboutReadiness();
    }

    if (action == "stop") {
        return new Stop();
    }

    if (action == "placerand") {
        return new PlaceShipsRandomly();
    }

    if (action == "attack") {
        int x, y;
        std::cin >> x >> y;
        return new Attack({x, y});
    }
    
    if (action == "applyB") {
        return new ApplyBombing();
    }

    if (action == "applyS") {
        int x, y;
        std::cin >> x >> y;
        return new ApplyScanner({x, y});
    }

    if (action == "applyDD") {
        return new ApplyDoubleDamage();
    }

    if (action == "save") {
        std::string save_file_name;
        std::cin >> save_file_name;
        return new Save(save_file_name);
    }
    
    if (action == "load") {
        std::string load_file_name;
        std::cin >> load_file_name;
        return new Load(load_file_name);
    }

    throw ListenerException("No such command was found");
}

} // namespace seabattle