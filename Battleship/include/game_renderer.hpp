#ifndef GAME_RENDERER_HPP_
#define GAME_RENDERER_HPP_

#include "game_map.hpp"

#include <vector>

// CHANGE IT 

class GameRenderer {
public:
    GameRenderer();

    GameRenderer(int width, int height);
    
    ~GameRenderer();
    
    void renderGameMap(GameMap& game_field);

private:
    std::vector<std::vector<int>> game_field_;
    int game_field_width_;
    int game_field_height_;
};


#endif // GAME_RENDERER_HPP_