#ifndef GAME_RENDERER_HPP_
#define GAME_RENDERER_HPP_

#include "game_map.hpp"

#include <vector>
#include <string>

namespace battleship
{

// CHANGE IT
class GameRenderer {
public:
    GameRenderer();

    explicit GameRenderer(int width, int height);
    
    ~GameRenderer();
    
    void renderGameMap(const GameMap& game_map);

private:
    std::vector<std::vector<std::string>> game_map_; // solution for CLI (in GUI no additional memory usage)
    int game_map_width_;
    int game_map_height_;
};

} // battleship


#endif // GAME_RENDERER_HPP_