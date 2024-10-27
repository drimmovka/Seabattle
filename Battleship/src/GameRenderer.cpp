#include "../include/GameRenderer.hpp"

#include "../include/GameMap.hpp"
#include "../include/Ship.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace battleship
{

GameRenderer::GameRenderer()
    : game_map_height_(0)
    , game_map_width_(0)
{}

GameRenderer::GameRenderer(int width, int height)
    : game_map_(height, std::vector<std::string> (width, "*"))
    , game_map_height_(height)
    , game_map_width_(width)
{}

GameRenderer::~GameRenderer() = default;

void GameRenderer::renderGameMap(const GameMap& game_map) {
    // clear vector here
    for (int y = 0; y < game_map_height_; y++) {
        for (int x = 0; x < game_map_height_; x++) {
            game_map_[y][x] = "*";
        }
    }

    std::cout << "  ";
    for (int i = 0; i < game_map.width(); i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto& item : game_map.shipsToShipInfo()) {
        for (auto& [coords, idx] : item.second->coords_to_segment_indexes) {
            game_map_[coords.y][coords.x] = std::to_string(item.first->segmentHealth(idx));
        }
    }

    for (int y = 0; y < game_map_height_; y++) {
        std::cout << y << " ";
        for (int x = 0; x < game_map_width_; x++) {
            std::cout << game_map_[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

} // battleship