#include "../include/game_renderer.hpp"

#include "../include/game_map.hpp"
#include "../include/ship.hpp"

#include <vector>
#include <iostream>

GameRenderer::GameRenderer()
    : game_field_height_(0)
    , game_field_width_(0)
{}

GameRenderer::GameRenderer(int width, int height)
    : game_field_(height, std::vector<int> (width, 0))
    , game_field_height_(height)
    , game_field_width_(width)
{}

GameRenderer::~GameRenderer() = default;

void GameRenderer::renderGameMap(GameMap& game_field) {
    // clear vector here

    for (auto& item : game_field.ships()) {
        HitBox shaping_hit_box = item.second.shaping;

        // another method
        int q = 0;
        for (int y = shaping_hit_box.top_left.y; y <= shaping_hit_box.bottom_right.y; y++) {
            for (int x = shaping_hit_box.top_left.x; x <= shaping_hit_box.bottom_right.x; x++) {
                game_field_[y][x] = item.first->segmentHealth(q);
                q++;
            }
        }
    }

    for (int y = 0; y < game_field_height_; y++) {
        std::cout << y << " ";
        for (int x = 0; x < game_field_width_; x++) {
            std::cout << game_field_[y][x] << " ";
        }
        std::cout << std::endl;
    }

}