#ifndef GUI_RENDERER_HPP_
#define GUI_RENDERER_HPP_

#include "Game.hpp"
#include "GameMap.hpp"

#include <SFML/Graphics.hpp>

namespace battleship
{

class GUIRenderer {

public:
    GUIRenderer();
    
    void render(GameMapViewModel& game_map_view_model);

    void renderGameMap(GameMapViewModel& game_map_view_model, int type);

private:
    sf::RenderWindow window_;
    int cell_size_;
    int line_width_;
    
    void renderUnionGameMap(GameMapViewModel& game_map_view_model);
    
    void renderEnemyGameMap(GameMapViewModel& game_map_view_model);
};

} // battleship

#endif // GUI_RENDERER_HPP_