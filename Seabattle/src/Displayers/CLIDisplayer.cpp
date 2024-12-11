#include "Displayers/CLIDisplayer.hpp"

#include "GameMapViewModel.hpp"

#include <iostream>

namespace seabattle
{

CLIDisplayer::CLIDisplayer() = default;

CLIDisplayer::~CLIDisplayer() = default;

void CLIDisplayer::displayUserShipInfo(ShipsManager& ships_manager) {
    std::cout << "Ships number: " << ships_manager.shipsNumber() << std::endl;
    std::cout << "All destroyed: " << ships_manager.allDestroyed() << std::endl;
    std::cout << "All placed on game map: " << ships_manager.allPlacedOnGameMap() << std::endl;


    for (int i = 0; i < ships_manager.shipsNumber(); i++) {
        std::cout << "Size: " << ships_manager[i]->size() << " | segments: ";
        for (int j = 0; j < ships_manager[i]->size(); j++) {
            std::cout << "[" << (*ships_manager[i])[j]->health() << "]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void CLIDisplayer::displayUserGameMap(GameMapViewModel& game_map_view_model) {
    game_map_view_model.update();

    std::cout << "User:" << std::endl;
    for (int y = 0; y < game_map_view_model.height(); y++) {
        for (int x = 0; x < game_map_view_model.width(); x++) {
            const GameMapViewModel::Cell& cell = game_map_view_model.at({x, y});
            if (cell.shotted) {
                if (cell.content == GameMapViewModel::Cell::Content::kShipSegment) {
                    std::cout << "[" << cell.ship_segment_health << "]";
                } else {
                    std::cout << "[" << "S" << "]";
                }
            } else {
                if (cell.content == GameMapViewModel::Cell::Content::kShipSegment) {
                    std::cout << "(" << cell.ship_segment_health << ")";
                } else {
                    std::cout << " " << "S" << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void CLIDisplayer::displayEnemyGameMap(GameMapViewModel& game_map_view_model) {
    game_map_view_model.update();

    std::cout << "Enemy:" << std::endl;

    for (int y = 0; y < game_map_view_model.height(); y++) {
        for (int x = 0; x < game_map_view_model.width(); x++) {
            const GameMapViewModel::Cell& cell = game_map_view_model.at({x, y});
            if (cell.shotted) {
                if (cell.content == GameMapViewModel::Cell::Content::kShipSegment) {
                    std::cout << "[" << cell.ship_segment_health << "]";
                } else {
                    std::cout << "[" << "S" << "]";
                }
            } else {
                std::cout << " " << "?" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void CLIDisplayer::displayMessage(const char *message) {
    std::cout << message << "\n";
}

void CLIDisplayer::displayUserFrontAbilityType(AbilityType ability_type) {
    switch (ability_type)
    {
    case AbilityType::kBombing:
        this->displayMessage("Available: Bombing");
        break;
    case AbilityType::kDoubleDamage:
        this->displayMessage("Available: DoubleDamage");
        break;
    case AbilityType::kScanner:
        this->displayMessage("Available: Scanner");
        break;
    default:
        this->displayMessage("Available: -");
        break;
    }
}

} // namespace seabattle