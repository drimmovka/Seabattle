#include "Displayers/CLIGameMapDisplayer.hpp"

namespace seabattle
{

CLIGameMapDisplayer::CLIGameMapDisplayer() = default;

CLIGameMapDisplayer::~CLIGameMapDisplayer() = default;

void CLIGameMapDisplayer::outputUserGameMap(GameMapViewModel& game_map_view_model) {
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

void CLIGameMapDisplayer::outputEnemyGameMap(GameMapViewModel& game_map_view_model) {
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

} // namespace seabattle