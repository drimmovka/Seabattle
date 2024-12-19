#ifndef CLI_outputER_HPP
#define CLI_outputER_HPP

#include "GameMapViewModel.hpp"
#include "Abilities/AbilityType.hpp"
#include "CLIGameMapDisplayer.hpp"

#include <iostream>
#include <iomanip>
#include <utility>

namespace seabattle
{

template<typename GameMapDisplayerT>
class CLIDisplayer {

public:

    CLIDisplayer() = default;

    ~CLIDisplayer() = default;

    void outputGameMaps(GameMapViewModel& user_game_map_view_model, GameMapViewModel& enemy_game_map_view_model) {
        _game_map_displayer.outputUserGameMap(user_game_map_view_model);
        _game_map_displayer.outputUserGameMap(enemy_game_map_view_model);
    }

    void outputHelp(const std::unordered_map<std::string, std::string>& keys_map) {
        int mx = INT_MIN;
        for (const auto& [command, key] : keys_map) {
            mx = std::max(mx, static_cast<int>(std::max(key.size(), command.size())));   
        }

        this->outputMessage("Help:\n");

        std::cout << std::setw(mx) << std::left << "COMMAND" << " - " 
                  << std::setw(mx) << std::left << "KEY" << std::endl;

        for (const auto& [command, key] : keys_map) {
            std::cout << std::setw(mx) << std::left << command << " : " 
                      << std::setw(mx) << std::left << key << std::endl;
        }
    }

    void outputGameStartMessage() {
        this->outputMessage("Game started\n");
    }

    void outputRestartQuestion() {
        this->outputMessage("Restart game (1 or 0): ");
    }

    void outputAskForCommandMessage() {
        this->outputMessage("Enter the command: ");
    }

    void outputCurrentScore(int score) {
        this->outputMessage(("Current score: " + std::to_string(score) + "\n").c_str());
    }
    
    void outputWinMessage() {
        this->outputMessage("Round won! Score increased\n");
    }

    void outputLooseMessage() {
        this->outputMessage("Game over(\n");
    }

    void outputEmptyLine() {
        this->outputMessage("\n");
    }

    void outputError(const std::exception& e) {
        this->outputMessage((std::string(e.what()) + "\n").c_str());
    }

    void outputUserFrontAbilityType(AbilityType ability_type) {
        this->outputMessage("Available: ");
        switch (ability_type)
        {
        case AbilityType::kBombing:
            this->outputMessage("Bombing\n");
            break;
        case AbilityType::kDoubleDamage:
            this->outputMessage("DoubleDamage\n");
            break;
        case AbilityType::kScanner:
            this->outputMessage("Scanner\n");
            break;
        default:
            this->outputMessage("-\n");
            break;
        }
    }

private:

    GameMapDisplayerT _game_map_displayer;

private:
    void outputMessage(const char *message) {
        std::cout << message;
    }

};

} // seabattle

#endif // CLI_outputER_HPP