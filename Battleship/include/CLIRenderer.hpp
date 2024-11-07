#ifndef CLI_RENDERER_HPP_
#define CLI_RENDERER_HPP_

#include "GameMapViewModel.hpp"
#include "ShipManager.hpp"

namespace battleship
{

class CLIRenderer {

public:
    CLIRenderer();

    ~CLIRenderer();

    void renderShipInfo(ShipManager& ship_manager);

    void render(GameMapViewModel& game_map_view_model);

private:
    void renderGameMap(GameMapViewModel& game_map_view_model, int type);

    void renderUnionGameMap(GameMapViewModel& game_map_view_model);

    void renderEnemyGameMap(GameMapViewModel& game_map_view_model);

};

} // battleship

#endif // CLI_RENDERER_HPP_