#include "GameData.hpp"

namespace seabattle
{

GameData::GameData()
    : game_phase(GamePhase::kSettingSettings)
    , is_enemy_move(false)
    , ability_has_been_applied(false)
    , score(0)
{}

GameData::~GameData() = default;

std::ostream& operator<<(std::ostream& os, const GameData& game_data) {
    
    os << (int) game_data.game_phase << "\n";
    os << (int) game_data.is_enemy_move << "\n";
    os << (int) game_data.ability_has_been_applied << "\n";
    os << (int) game_data.score << "\n\n";
    
    os << game_data.ship_sizes.size() << "\n";
    for (int i=0; i<game_data.ship_sizes.size(); i++) {
        os << game_data.ship_sizes[i] << " ";
    }
    os << "\n\n";

    os << game_data.game_map_width << "\n";
    os << game_data.game_map_height << "\n";
    
    os << *game_data.user_ships_manager << "\n";
    os << *game_data.user_game_map << "\n";
    os << *game_data.user_abilities_manager << "\n";
    os << *game_data.user_damage << "\n";
    os << *game_data.user_scanner_result << "\n";

    os << *game_data.enemy_ships_manager << "\n";
    os << *game_data.enemy_game_map << "\n";
    os << *game_data.enemy_alive_ships_number << "\n";
    
    return os;
}

std::istream& operator>>(std::istream& is, GameData& game_data) {
    
    int game_phase;
    is >> game_phase;
    switch (game_phase)
    {
    case (int) GamePhase::kSettingSettings :
        game_data.game_phase = GamePhase::kSettingSettings;
        break;
    case (int) GamePhase::kPlacingShips :
        game_data.game_phase = GamePhase::kPlacingShips;
        break;
    case (int) GamePhase::kMoving :
        game_data.game_phase = GamePhase::kMoving;
        break;
    default:
        throw FileException("Error when reading the file. The game phase could not be determined");
        break;
    }
    
    is >> game_data.is_enemy_move;
    is >> game_data.ability_has_been_applied;
    is >> game_data.score;

    int ship_sizes_size;
    is >> ship_sizes_size;
    game_data.ship_sizes = std::vector<int>(ship_sizes_size);
    for (int i=0; i<ship_sizes_size; ++i) {
        is >> game_data.ship_sizes[i];
    }

    is >> game_data.game_map_width;
    is >> game_data.game_map_height;


    game_data.user_ships_manager = new ShipsManager();
    is >> *game_data.user_ships_manager;


    game_data.user_game_map = new GameMap(game_data.game_map_width, game_data.game_map_height);        
    is >> *game_data.user_game_map;
    
    int placed_on_game_map;
    is >> placed_on_game_map;
    for (int i=0; i<placed_on_game_map; ++i) {
        int id, x, y, ori;
        is >> id >> x >> y >> ori;
        game_data.user_game_map->placeShip((*game_data.user_ships_manager)[id], {x, y}, 
            (ori == (int)Ship::Orientation::kHorizontal) ?
            Ship::Orientation::kHorizontal : Ship::Orientation::kVertical);
    }


    int number_of_abilities;
    is >> number_of_abilities;
    std::vector<AbilityType> abilities(number_of_abilities);
    for (int i=0; i<number_of_abilities; ++i) {
        int ability_type;
        is >> ability_type;
        switch (ability_type)
        {
        case (int)AbilityType::kBombing :
            abilities[i] = AbilityType::kBombing;
            break;
        case (int)AbilityType::kDoubleDamage :
            abilities[i] = AbilityType::kDoubleDamage;
            break;
        case (int)AbilityType::kScanner :
            abilities[i] = AbilityType::kScanner;
            break;
        default:
            throw FileException("Error when reading the file. The ability type could not be determined");
            break;
        }
    }

    game_data.user_abilities_manager = new AbilitiesManager(abilities);


    game_data.user_damage = new int();
    is >> *game_data.user_damage;

    game_data.user_scanner_result = new bool();        
    is >> *game_data.user_scanner_result;
    

    game_data.enemy_ships_manager = new ShipsManager();
    is >> *game_data.enemy_ships_manager;
    
    game_data.enemy_game_map= new GameMap(game_data.game_map_width, game_data.game_map_height);
    is >> *game_data.enemy_game_map;

    is >> placed_on_game_map;
    for (int i=0; i<placed_on_game_map; ++i) {
        int id, x, y, ori;
        is >> id >> x >> y >> ori;
        game_data.enemy_game_map->placeShip((*game_data.enemy_ships_manager)[id], {x, y}, 
            (ori == (int)Ship::Orientation::kHorizontal) ?
            Ship::Orientation::kHorizontal : Ship::Orientation::kVertical);
    }


    game_data.enemy_alive_ships_number = new int();
    is >> *game_data.enemy_alive_ships_number;
    
    return is;
}

} // namespace seabattle