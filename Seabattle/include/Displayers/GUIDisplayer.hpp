#ifndef GUI_DISPLAYER_HPP
#define GUI_DISPLAYER_HPP

#include "GameMapViewModel.hpp"

#include <SFML/Graphics.hpp>

namespace seabattle
{

class GUIDisplayer {

public:
    GUIDisplayer();
    
    void render(GameMapViewModel& game_map_view_model);

    void renderGameMap(GameMapViewModel& game_map_view_model, int type);

private:
    sf::RenderWindow window_;
    int cell_size_;
    int line_width_;
    
    void renderUnionGameMap(GameMapViewModel& game_map_view_model);
    
    void renderEnemyGameMap(GameMapViewModel& game_map_view_model);
};

} // namespace seabattle

#endif // GUI_DISPLAYER_HPP