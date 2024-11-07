#include "CLIRenderer.hpp"

#include "GameMapViewModel.hpp"

#include <iostream>

namespace battleship
{

CLIRenderer::CLIRenderer() = default;

CLIRenderer::~CLIRenderer() = default;

void CLIRenderer::renderShipInfo(ShipManager& ship_manager) {
    std::cout << "Ships number: " << ship_manager.shipsNumber() << std::endl;
    std::cout << "All destroyed: " << ship_manager.allDestroyed() << std::endl;
    std::cout << "All placed on game map: " << ship_manager.allPlacedOnGameMap() << std::endl;


    for (int i = 0; i < ship_manager.shipsNumber(); i++) {
        std::cout << "Size: " << ship_manager[i]->size() << " | segments: ";
        for (int j = 0; j < ship_manager[i]->size(); j++) {
            std::cout << "[" << (*ship_manager[i])[j]->health() << "]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void CLIRenderer::render(GameMapViewModel& game_map_view_model) {
    this->renderGameMap(game_map_view_model, 0); std::cout << std::endl;
    this->renderGameMap(game_map_view_model, 1); std::cout << std::endl;
}

void CLIRenderer::renderGameMap(GameMapViewModel& game_map_view_model, int type) {
    // mb use pattern strategy?
    game_map_view_model.update();

    if (type == 0) {
        this->renderUnionGameMap(game_map_view_model);
    }
    if (type == 1) {
        this->renderEnemyGameMap(game_map_view_model);
    }
}

void CLIRenderer::renderUnionGameMap(GameMapViewModel& game_map_view_model) {
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

void CLIRenderer::renderEnemyGameMap(GameMapViewModel& game_map_view_model) {
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

} // battleship