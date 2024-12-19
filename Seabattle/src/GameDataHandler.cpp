#include "GameDataHandler.hpp"

namespace seabattle
{

GameDataHandler::GameDataHandler() {}

// game_data MUST be initialized by Game class!
void GameDataHandler::saveGame(GameData *game_data, const std::string save_file_name) const {
    std::ofstream fout;
    fout.open(save_file_name);
    if (!fout) {
        throw FileException("failed to open save file");
    }
    fout << *game_data;
    fout.close();
    this->createHashFile(save_file_name);
}

// game_data MUST be initialized by Game class!
void GameDataHandler::loadGame(GameData *game_data, const std::string load_file_name) const {
    if (!isLoadFileValid(load_file_name)) {
        throw FileException("Error: Hash mismatch");
    }
    std::ifstream fin;
    fin.open(load_file_name);
    if (!fin) {
        throw FileException("failed to open load file");
    }
    fin >> *game_data;
    fin.close();
}

void GameDataHandler::createHashFile(const std::string& save_file_name) const {
    
    std::ifstream fin(save_file_name);
    if (!fin) {
        throw FileException("failed to open save file for reading");
    }
    
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string content = buffer.str();
    fin.close();

    std::size_t hash_value = std::hash<std::string>()(content);

    std::ofstream hash_fout("hash_" + save_file_name);
    if (!hash_fout) {
        throw FileException("failed to open hash file for writing");
    }
    
    hash_fout << hash_value;
    hash_fout.close();
}

bool GameDataHandler::isLoadFileValid(const std::string& load_file_name) const {
    std::ifstream fin(load_file_name);
    if (!fin) {
        throw FileException("failed to open load file for reading");
    }
    
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string content = buffer.str();
    fin.close();

    std::size_t calculated_hash = std::hash<std::string>()(content);

    std::ifstream hash_file("hash_" + load_file_name);
    if (!hash_file.is_open()) {
        throw FileException("Could not open hash file");
    }

    std::size_t hash_value;
    if (!(hash_file >> hash_value)) {
        throw FileException("Hash file is corrupted");
    }

    return (calculated_hash == hash_value);
}

} // namespace seabattle