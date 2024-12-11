#include "Game.hpp"

namespace seabattle
{

Game::Game(GameDataHandler& game_data_handler)
    : _is_running(false)
    , _game_data_handler(game_data_handler)
{}

Game::~Game() {
    if (_game_data != nullptr) {delete _game_data;}
    if (_user_game_map_view_model != nullptr) {delete _user_game_map_view_model;}
    if (_enemy_game_map_view_model != nullptr) {delete _enemy_game_map_view_model;}
}

bool Game::isRunning() {
    return _is_running;
}    

int Game::score() {
    return _game_data->score;
}

bool Game::roundWon() {
    return _game_data->enemy_ships_manager->allDestroyed();
}

bool Game::over() {
    return _game_data->user_ships_manager->allDestroyed();
}

void Game::run() {
    _game_data = new GameData;
    _is_running = true;
}

void Game::stop() {
    _is_running = false;
}

GamePhase Game::currentPhase() const {
    return _game_data->game_phase;
}

AbilityType Game::userAvailableAbilityType() {
    if (_game_data->user_abilities_manager->hasAbilities()) {
        return _game_data->user_abilities_manager->frontAbility();
    } else {
        return AbilityType::kNoAbility;
    }
}

bool Game::isEnemyMove() const {
    return _game_data->is_enemy_move;
}

GameMapViewModel *Game::userGameMapViewModel() {
    return _user_game_map_view_model;
}

GameMapViewModel *Game::enemyGameMapViewModel() {
    return _enemy_game_map_view_model;
}

GameData *Game::gameData() {
    return _game_data;
}

void Game::increaseScore() {
    _game_data->score += 1;
}

void Game::resetEnemy() {
    this->initEnemy();
    
    // so that the user has the opportunity to use the ability on the first move
    // after winning and after that the opponent could not move until user attacks
    _game_data->is_enemy_move = false;

    _game_data->ability_has_been_applied = false; // if the game ended with the use of bombing
}

void Game::tryToAddAbilitiesForUser() {
    if (*_game_data->enemy_alive_ships_number != _game_data->enemy_ships_manager->aliveShipsNumber()) {
        _game_data->user_abilities_manager->addRandomAbility();
        *_game_data->enemy_alive_ships_number = _game_data->enemy_ships_manager->aliveShipsNumber();
    }
}

void Game::setSettings(int game_map_width, int game_map_height, std::vector<int>& ship_sizes) {
    _game_data->game_map_width = game_map_width;
    _game_data->game_map_height = game_map_height;
    _game_data->ship_sizes = ship_sizes;
    
    this->initUser();
    this->initEnemy();

    this->setGamePhase(GamePhase::kPlacingShips);
}

void Game::userPlaceShipsRandomly() {
    this->placeShipsRandomly(_game_data->user_ships_manager, _game_data->user_game_map);
}

void Game::allowUserMakingMoves() {
    if (_game_data->user_ships_manager->allPlacedOnGameMap()) {
        this->setGamePhase(GamePhase::kMoving);
    } else {
        throw ShipsAreNotPlacedException("User ships are not placed exception");
    }
}

void Game::userAttack(Coords coords) {
    _game_data->enemy_game_map->attack(coords, *_game_data->user_damage);
    *_game_data->user_damage = 1;                       // reset user damage
    *_game_data->user_scanner_result = false;           // reset user scanner result;
    _game_data->ability_has_been_applied = false;       // reset ability usage
    _game_data->is_enemy_move = true;                   // Allow enemy to make move
}

void Game::userApplyAbility(iAbilitySpec *ability_spec) {

    if (!_game_data->ability_has_been_applied) { // user cannot use more than one ability while moving

        // errors such as lack of abilities or mismatch of action and available ability
        // considered at a lower level (in user_abilities_manager)
        _game_data->user_abilities_manager->applyFrontAbility(*ability_spec);
        _game_data->ability_has_been_applied = true;
    } else {
        throw AbilityIsAlreadyUsedException("You have already used the ability");
    }
}

void Game::userSave(const std::string save_file_name) {
    _game_data_handler.saveGame(_game_data, save_file_name);
}

void Game::userLoad(const std::string load_file_name) {
    if (_game_data != nullptr) {delete _game_data;}
    _game_data = new GameData;
    _game_data_handler.loadGame(_game_data, load_file_name);

    // pinning view_models after game data reinitialized
    _user_game_map_view_model = new GameMapViewModel(*_game_data->user_game_map);
    _enemy_game_map_view_model = new GameMapViewModel(*_game_data->enemy_game_map);

}

void Game::enemyMakeMove() {
    srand(time(0));
    _game_data->user_game_map->attack({rand()%_game_data->user_game_map->width(), rand()%_game_data->user_game_map->height()}, 1);
    _game_data->is_enemy_move = false;     // prohibit enemy to make move
}

GameData *_game_data;
bool _is_running;

GameMapViewModel *_user_game_map_view_model;
GameMapViewModel *_enemy_game_map_view_model;

void Game::setGamePhase(GamePhase next_game_phase) {
    _game_data->game_phase = next_game_phase;
}

void Game::initUser() {
    _game_data->user_damage = new int(1);
    _game_data->user_scanner_result = new bool(false);           
    _game_data->user_ships_manager = new ShipsManager(_game_data->ship_sizes);
    _game_data->user_game_map = new GameMap(_game_data->game_map_width, _game_data->game_map_height);
    _game_data->user_abilities_manager = new AbilitiesManager();

    // pin view model to a model
    _user_game_map_view_model = new GameMapViewModel(*_game_data->user_game_map);
}

void Game::initEnemy() {
    _game_data->enemy_ships_manager = new ShipsManager(_game_data->ship_sizes);
    _game_data->enemy_game_map = new GameMap(_game_data->game_map_width, _game_data->game_map_height);
    _game_data->enemy_alive_ships_number = new int(_game_data->enemy_ships_manager->aliveShipsNumber());

    // pin view model to a model
    _enemy_game_map_view_model = new GameMapViewModel(*_game_data->enemy_game_map);
    
    // place enemy ships
    this->placeShipsRandomly(_game_data->enemy_ships_manager, _game_data->enemy_game_map);
}

void Game::placeShipsRandomly(ShipsManager *ships_manager, GameMap *game_map) {
    srand(time(0));
    
    // possible to get into an endless loop so used cnt=100000 (DEBUG VERSION here; in future, there will be a normal algorithm!!!)

    int cnt = 1000000; // DEBUG

    for (int i = 0; i < ships_manager->shipsNumber(); ++i) {
        // DEBUG
        while (true) {
            cnt--;
            if (cnt < 0) {
                throw std::runtime_error("endless loop in placing ships");
            }

            try {
                int x = rand() % game_map->width();
                int y = rand() % game_map->height();
                Ship::Orientation ori = (rand() % 2 == 0) ? Ship::Orientation::kHorizontal : Ship::Orientation::kVertical;
                game_map->placeShip((*ships_manager)[i], {x, y}, ori);
                break;
            } catch (const ShipPlacementException& e) {
                continue;
            }
        }
        // DEBUG
    }
}


} // namespace seabattle