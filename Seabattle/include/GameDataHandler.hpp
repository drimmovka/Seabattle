#ifndef GAME_DATA_HANDLER_HPP
#define GAME_DATA_HANDLER_HPP

#include "GameData.hpp"
#include "Exceptions/FileException.hpp"

namespace seabattle
{

class GameDataHandler {

public:
    GameDataHandler();

    // game_data MUST be initialized by Game class!
    void saveGame(GameData *game_data, const std::string save_file_name) const;

    // game_data MUST be initialized by Game class!
    void loadGame(GameData *game_data, const std::string load_file_name) const;

private:
    
    void createHashFile(const std::string& save_file_name) const;

    bool isLoadFileValid(const std::string& load_file_name) const;
};

} // namespace seabattle


#endif // GAME_DATA_HANDLER_HPP